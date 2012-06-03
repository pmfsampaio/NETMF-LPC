using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using Microsoft.Win32;
using PKStudio;
using System.Diagnostics;
using PKStudio.Forms.Options.Options;


namespace OptionsHelper.Options
{
    /// <summary>
    /// Options form
    /// </summary>
    public partial class OptionsForm : Form
    {
        /// <summary>
        /// Default constructor
        /// </summary>
        public OptionsForm()
        {
            InitializeComponent();
        }


        #region Fields
        /// <summary>
        /// Options controls list
        /// </summary>
        private List<OptionsControlBase> mPages;

        /// <summary>
        /// Currently editing control
        /// </summary>
        OptionsControlBase mCurrent = null;
        #endregion

        #region Properties
        /// <summary>
        /// Options controls list
        /// </summary>
        public List<OptionsControlBase> Pages
        {
            get
            {
                if (this.mPages == null)
                    this.mPages = new List<OptionsControlBase>();
                return this.mPages;
            }
        }

        public Button AboutButton { get { return this.AboutBtn; } }
        //public Button CancelButton { get { return this.CancelBtn; } }
        //public Button OkButton { get { return this.OKBtn; } }
        public Button LoadButton { get { return this.LoadBtn; } }
        public Button SaveButton { get { return this.SaveBtn; } }
        public Button ApplyButton { get { return this.ApplyBtn; } }

        #endregion

        #region Metods
        /// <summary>
        /// Ru: Инициализирует форму. Просматривает все добавленные контролы опций, добавляет их в дерево и производит их инициализацию.
        /// En: Initializes the form. Viewing the complete list of options controls, adds them to a tree and produces their initialization.
        /// </summary>
        public void Initialize()
        {
            treeView1.Nodes.Clear();
            foreach (OptionsControlBase page in this.Pages)
            {
                TreeNode node = new TreeNode(page.NodeName);
                node.Tag = page;
                page.Initialize();
                page.ModifiedEvent += new EventHandler(OptionModifiedEvent);
                treeView1.Nodes.Add(node);
            }
            if (treeView1.Nodes.Count > 0)
            {
                treeView1.SelectedNode = treeView1.Nodes[0];
            }

            ApplyBtn.Enabled = false;

            foreach (OptionsControlBase oc in Pages)
            {
                if (oc.Modified) ApplyBtn.Enabled = true;
            }

        }

        /// <summary>
        /// Ru: Сохранить изменения в открытом контроле
        /// En: Save changes in active(focused) control
        /// </summary>
        /// <returns> if all changes are saved - ture,else - false</returns>
        private bool ApplyChanges()
        {
            this.OnBeforeApplyChanges();
            bool result = false;
            //if (mCurrent != null)
            //    result |= mCurrent.ApplyChanges();
            foreach (OptionsControlBase oc in Pages)
            {
                result |= oc.ApplyChanges();
                if (result) break;
            }
            this.OnAfterApplyChanges();
            return result;
        }

        #endregion

        #region EventHandlers
        private void OptionModifiedEvent(object sender, EventArgs e)
        {
            ApplyBtn.Enabled = true;
        }

        private void CancelBtn_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void ApplyBtn_Click(object sender, EventArgs e)
        {
            ApplyBtn.Enabled = ApplyChanges();
        }

        private void OKBtn_Click(object sender, EventArgs e)
        {
            if (ApplyBtn.Enabled)
                if (ApplyChanges() == true)
                    return;
            this.Close();
        }

        private void treeView1_AfterSelect(object sender, TreeViewEventArgs e)
        {
            OptionsControlBase page = e.Node.Tag as OptionsControlBase;
            if (mCurrent != null)
            {
                if (page != null)
                {
                    if (mCurrent != page)
                    {
                        //if (mCurrent.Modified)
                        //{
                        //    if (MessageBox.Show(this, Strings.IDS_OPTIONS_PAGE_CHANGED, Strings.IDS_CONFIRM, MessageBoxButtons.OKCancel, MessageBoxIcon.Question, MessageBoxDefaultButton.Button2) == DialogResult.OK)
                        //        ApplyChanges();
                        //    else
                        //        mCurrent.Initialize();
                        //    ApplyBtn.Enabled = false;
                        //}
                    }
                }
            }
            if (page != null)
            {
                //page.Initialize();
                panel1.Controls.Clear();
                panel1.Controls.Add(page);
                page.Dock = DockStyle.Fill;
                mCurrent = page;
            }
        }

        #endregion


        /// <summary>
        /// Ru: Вызывается, перед применением изменений
        /// En: fires befor apply changes
        /// </summary>
        public event EventHandler BeforeApplyChangesEvent;

        private void OnBeforeApplyChanges()
        {
            if (BeforeApplyChangesEvent != null)
            {
                BeforeApplyChangesEvent(this, new EventArgs());
            }
        }

        /// <summary>
        /// Ru: Вызывается, после применения изменений
        /// En: Fires after apply changes
        /// </summary>
        public event EventHandler AfterApplyChangesEvent;

        private void OnAfterApplyChanges()
        {
            if (AfterApplyChangesEvent != null)
            {
                AfterApplyChangesEvent(this, new EventArgs());
            }
        }


        private void SaveBtn_Click(object sender, EventArgs e)
        {
            SaveOptions();
        }

        public void SaveOptions()
        {
            if (saveFileDialog1.ShowDialog(this) == DialogResult.OK)
            {
                this.SaveOptions(saveFileDialog1.FileName);
            }
        }

        public void SaveOptions(string path)
        {
            try
            {
                OptionsSerializer os = new OptionsSerializer();
                bool restart = false;
                foreach (OptionsControlBase page in mPages)
	            {
                    os.SOptions.Add(page.ControlledOption);
                    if ((page.ControlledOption is EnvironmentOption))
                    {
                        restart = true;
                    }
	            }
                os.SaveState(path);
                if (restart)
                {
                    if (MessageBox.Show(this, "Environment has been changed. Restart Application?", "Environment setting", MessageBoxButtons.OKCancel, MessageBoxIcon.Question, MessageBoxDefaultButton.Button2) == DialogResult.OK)
                    {
                        Environment.SetEnvironmentVariable("SPOCLIENT","");
                        Application.Exit();
                        Process.Start(".\\PKStudioLauncher.exe");
                    }
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(Strings.ERROR_CANT_SAVE_OPTIONS + ": " + ex.Message, Strings.Error + "!", MessageBoxButtons.OK, MessageBoxIcon.Error);
                //throw;
            }
        }

        private void LoadBtn_Click(object sender, EventArgs e)
        {
            this.LoadOptions();
        }

        public void LoadOptions()
        {
            if (openFileDialog1.ShowDialog(this) == DialogResult.OK)
            {
                this.LoadOptions(openFileDialog1.FileName);
            }
        }

        public void LoadOptions(string path)
        {
            try
            {
                OptionsSerializer os = OptionsSerializer.BackState(path);

                for (int i = 0; i < mPages.Count; i++)
                {
                    for (int j = 0; j < os.SOptions.Count; j++)
                    {
                        if (mPages[i].ControlledOption.GetType() == os.SOptions[j].GetType())
                        {
                            //mPages[i].Option = os.SOptions[j];
                            mPages[i].SetOption(os.SOptions[j]);
                        }
                    }
                }
            }
            catch (Exception)
            {
                //MessageBox.Show(Strings.ERROR_CANT_LOAD_OPTIONS, Strings.Error + "!", MessageBoxButtons.OK, MessageBoxIcon.Error);
                throw;
            }
        }
    }
}