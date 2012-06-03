using System;
using System.IO;
using System.Windows.Forms;
using PKStudio.ItemWrappers;
namespace PKStudio.Forms.Editors
{
    public partial class SourceFileEditor : PKStudio.Forms.BaseForms.EditorBaseForm
    {

        protected string _editingFilePath;

        protected System.Windows.Forms.ToolStripMenuItem OpenFolderToolStripMenuItem = null;

        public SourceFileEditor()
        {
            InitializeComponent();

            scintilla1.NativeInterface.UsePopUp(false);

            scintilla1.AutoComplete.List.Clear();
            scintilla1.Margins[2].Width = 20;
            scintilla1.ModifiedChanged += new EventHandler(scintilla1_ModifiedChanged);
            //scintilla1.ConfigurationManager.CustomLocation = "ScintillaNET.xml";

            OpenFolderToolStripMenuItem = new ToolStripMenuItem();

            OpenFolderToolStripMenuItem.Name = "openFolderToolStripMenuItem";
            OpenFolderToolStripMenuItem.Text = Strings.OpenContainingFolder;
            OpenFolderToolStripMenuItem.Click += new EventHandler(OpenFolderToolStripMenuItem_Click);

            this.TabContextMenu.Items.Add(OpenFolderToolStripMenuItem);
        }

        void SearchTextMenuItem_Click(object sender, EventArgs e)
        {
            throw new NotImplementedException();
        }

        void OpenFolderToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OnOpenContainingFolderEvent(this.EditingFilePath);
        }

        public bool SetFile(string FilePath)
        {
            try
            {
                _editingFilePath = FilePath;

                using (StreamReader sr = new StreamReader(FilePath))
                {
                    scintilla1.Text = sr.ReadToEnd();
                }
                scintilla1.Modified = false;
                scintilla1.UndoRedo.EmptyUndoBuffer();

                string extencion = Path.GetExtension(FilePath).ToLower();
                switch (extencion)
                {
                    case ".cpp":
                    case ".h":
                    case ".c":
                        scintilla1.ConfigurationManager.Language = "cpp";
                        break;
                    case ".cs":
                        scintilla1.ConfigurationManager.Language = "cs";
                        break;
                    case ".s":
                        scintilla1.ConfigurationManager.Language = "asm";
                        break;
                    default:
                        break;
                }
                UpdateCaretPositionLabels();
                ZoomCB.SelectedIndex = 1;
                FormText = Path.GetFileName(FilePath);
                ModifiedFormText = Path.GetFileName(FilePath) + " *";

                scintilla1.Modified = false;
                SetModified(scintilla1.Modified);
            }
            catch (Exception ex)
            {
                MessageBox.Show(this, ex.Message, Strings.Error, MessageBoxButtons.OK, MessageBoxIcon.Error);
                return false;
            }
            return true;
        }

        public void GotoLine(int line)
        {
            scintilla1.GoTo.Line(line);
            scintilla1.Lines[line].Select();
        }


        #region Properties
        /// <summary>
        /// Editing file path 
        /// </summary>
        public string EditingFilePath { get { return this._editingFilePath; } }


        public override BaseWrapper EditComponent
        {
            get
            {
                return BuildFileWrapper.GetWrapper(this._editingFilePath);
            }
        }

        #endregion

        public override void Save()
        {
            this.SaveFile(this.EditingFilePath);
        }

        #region Helpers
        /// <summary>
        /// Ru: Обновляет Labels с позицией carret
        /// En: Updates Labels with carret position
        /// </summary>
        private void UpdateCaretPositionLabels()
        {
            LnLbl.Text = "Ln " + (scintilla1.Caret.LineNumber + 1).ToString();
            ColLbl.Text = "Col " + (scintilla1.Caret.Position - scintilla1.Lines[scintilla1.Caret.LineNumber].StartPosition + 1).ToString();
            PosLbl.Text = "Pos " + (scintilla1.Caret.Position + 1).ToString();
        }

        public void SaveFile(string path)
        {
            try
            {
                if (this.modified)
                {
                    FileInfo FI = new FileInfo(path);

                    if ((FI.Attributes & FileAttributes.ReadOnly) == FileAttributes.ReadOnly)
                    {
                        string str = "The file " + Path.GetFileName(path) + " cannot be saved because it is write-protected.\r\nPKStudio can attempt to remove the write-protection and overwrite the file in its current location.";
                        if (MessageBox.Show(this, str, "Save of Read-Only File", MessageBoxButtons.YesNo, MessageBoxIcon.Warning) == System.Windows.Forms.DialogResult.Yes)
                        {
                            FI.Attributes -= FileAttributes.ReadOnly;

                            using (StreamWriter sw = File.CreateText(path))
                            {
                                sw.Write(scintilla1.Text);
                            }
                            scintilla1.Modified = false;
                        }
                    }
                    else
                    {
                        using (StreamWriter sw = File.CreateText(path))
                        {
                            sw.Write(scintilla1.Text);
                        }
                        scintilla1.Modified = false;
                    }
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(this, ex.Message, Strings.Error, MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        #endregion

        #region EventHandlers

        private void ZoomCB_SelectedIndexChanged(object sender, EventArgs e)
        {
            switch (ZoomCB.SelectedIndex)
            {
                case 0: //Small
                    scintilla1.Zoom = -3;
                    break;
                case 1: //Normal
                    scintilla1.Zoom = 0;
                    break;
                case 2: //Large
                    scintilla1.Zoom = 5;
                    break;
                default:
                    break;
            }
        }

        void scintilla1_ModifiedChanged(object sender, EventArgs e)
        {
            SetModified(scintilla1.Modified);
        }

        private void scintilla1_SelectionChanged(object sender, EventArgs e)
        {
            UpdateCaretPositionLabels();
        }

        #endregion

        private void scintilla1_MouseClick(object sender, MouseEventArgs e)
        {
            if (e.Button == System.Windows.Forms.MouseButtons.Right)
            {
                try
                {


                    int position = scintilla1.PositionFromPoint(e.X, e.Y);

                    ScintillaNet.Line line = scintilla1.Lines.FromPosition(position);

                    int StartIndex = position - line.StartPosition;
                    int EndIndex = position - line.StartPosition;

                    while (StartIndex >= 0)
                    {
                        char s = line.Text[StartIndex];
                        if ((!char.IsLetterOrDigit(s) && (s != '_')) || (StartIndex == 0))
                        {
                            if (StartIndex != 0) StartIndex++;
                            break;
                        }
                        StartIndex--;
                    }

                    while (EndIndex >= 0)
                    {
                        char s = line.Text[EndIndex];
                        if ((!char.IsLetterOrDigit(s) && (s != '_')) || (EndIndex == line.Text.Length)) break;
                        EndIndex++;
                    }

                    string word = line.Text.Substring(StartIndex, EndIndex - StartIndex);

                    if (!string.IsNullOrEmpty(word))
                    {
                        if (word.Length < 50)
                            searchToolStripMenuItem.Text = Strings.Search + " \"" + word + "\"";
                        else
                            searchToolStripMenuItem.Text = Strings.Search + " \"" + word.Substring(0, 47) + "...\"";

                        searchToolStripMenuItem.Visible = true;
                        searchToolStripMenuItem.Tag = word;
                        SearchSeparator.Visible = true;
                    }
                    else
                    {
                        searchToolStripMenuItem.Visible = false;
                        SearchSeparator.Visible = false;
                    }
                    contextMenuStrip1.Show(scintilla1.PointToScreen(new System.Drawing.Point(e.X, e.Y)));
                }
                catch
                {
                    searchToolStripMenuItem.Visible = false;
                    SearchSeparator.Visible = false;
                    contextMenuStrip1.Show(scintilla1.PointToScreen(new System.Drawing.Point(e.X, e.Y)));
                }
            }
        }

        private void searchToolStripMenuItem_Click(object sender, EventArgs e)
        {
            try
            {
                PK.Wrapper.Search(PortingKitWrapper.SearchType.TextInFiles, PortingKitWrapper.SearchWhere.All, (string)searchToolStripMenuItem.Tag, false, false);
            }
            catch (Exception)
            {
            }
        }

        private void undoToolStripMenuItem_Click(object sender, EventArgs e)
        {
            scintilla1.UndoRedo.Undo();
        }

        private void redoToolStripMenuItem_Click(object sender, EventArgs e)
        {
            scintilla1.UndoRedo.Redo();
        }

        private void selectAllToolStripMenuItem_Click(object sender, EventArgs e)
        {
            scintilla1.Selection.SelectAll();
        }

        private void cutToolStripMenuItem_Click(object sender, EventArgs e)
        {
            scintilla1.Clipboard.Cut();
        }

        private void copyToolStripMenuItem_Click(object sender, EventArgs e)
        {
            scintilla1.Clipboard.Copy();
        }

        private void pasteToolStripMenuItem_Click(object sender, EventArgs e)
        {
            scintilla1.Clipboard.Paste();
        }
    }
}
