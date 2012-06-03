using System;
using System.Windows.Forms;
using System.IO;
using PKStudio.ItemWrappers;

namespace PKStudio.Dialogs
{
    public partial class NewLibraryDialog : Form
    {
        public NewLibraryDialog()
        {
            InitializeComponent();
            this.Library = null;

        }

        public LibraryWrapper Library { get; set; }
        
        public DialogResult ShowDialog(IWin32Window owner, LibraryWrapper Lib)
        {
            this.Text = Strings.CloneLibraryCategory;
            this.Library = Lib;
            FillFields();

            if (GroupsCb.Items.Contains(Lib.Groups)) GroupsCb.SelectedItem = Lib.Groups;
            else
            {
                if (GroupsCb.Items.Count > 0) GroupsCb.SelectedIndex = 0;
            }

            string projname = Path.GetFileNameWithoutExtension(Lib.ProjectPath);

            if (Lib.Name.Contains("test") && projname.Contains("_test"))
            {   
                TestCb.Checked = true;
            }
            else TestCb.Checked = false;

            IsStubCb.Checked = Lib.IsStub;

            NameTb.Text = PK.Wrapper.GenerateNewLibraryName(Lib.Name);

            LevelCb.SelectedItem = Lib.Level;

            DirectoryTb.Text = Path.GetDirectoryName(Lib.ProjectPath);
            ProjNameTb.Text = GenerateNewProjName(projname);
            
            SetSuffixs();

            return this.ShowDialog(owner);
        }

        public DialogResult ShowDialog(IWin32Window owner, string groups)
        {
            this.Text = Strings.NewLibraryCategory;
            this.Library = null;
            FillFields();

            if (GroupsCb.Items.Contains(groups)) GroupsCb.SelectedItem = groups;
            else
            {
                if (GroupsCb.Items.Count > 0) GroupsCb.SelectedIndex = 0;
            }

            ProjNameTb.Text = "dotNetMF";
            //DirectoryTb.Text = PK.Wrapper.SpoClientPath;
            DirectoryTb.Text = "$(SPOCLIENT)";

            TestCb.Checked = false;
            IsStubCb.Checked = false;

            SetSuffixs();

            NameTb.Text = PK.Wrapper.GenerateNewLibraryName("NewLibrary" + nameSuffixLbl.Text);

            return this.ShowDialog(owner);
        }
        
        #region helpers
        private void SetSuffixs()
        {
            if (TestCb.Checked)
            {
                nameSuffixLbl.Text = "test";
                projSuffixLbl.Text = "_test";
            }
            else
            {
                projSuffixLbl.Text = "";
                if (IsStubCb.Checked)
                {
                    nameSuffixLbl.Text = "_stubs";
                    if (!DirectoryTb.Text.Contains("\\stubs"))
                    {
                        DirectoryTb.Text = DirectoryTb.Text + "\\stubs";
                    }
                }
                else
                {
                    nameSuffixLbl.Text = "";
                    if (DirectoryTb.Text.Contains("\\stubs"))
                    {
                        DirectoryTb.Text = DirectoryTb.Text.Replace("\\stubs","");
                    }
                }
            }
        }

        private void FillFields()
        {
            GroupsCb.Items.Clear();
            GroupsCb.Items.Add("");

            foreach (LibraryWrapper lib in PK.Wrapper.GetLibraries())
            {
                if (!GroupsCb.Items.Contains(lib.Groups))
                {
                    GroupsCb.Items.Add(lib.Groups);
                }
            }

            LevelCb.Items.Clear();
            LevelCb.Items.Add(LibraryLevelWrapper.CLR);
            LevelCb.Items.Add(LibraryLevelWrapper.HAL);
            LevelCb.Items.Add(LibraryLevelWrapper.PAL);
            LevelCb.Items.Add(LibraryLevelWrapper.Support);
            LevelCb.SelectedItem = LibraryLevelWrapper.CLR;
        }

        public string GenerateNewProjName(string BaseName)
        {
            string defaultName = "";
            string currentName = "";
            string suffix = "";
            string resultName = "";

            if (BaseName.Contains("_test"))
            {
                defaultName = BaseName.Replace("_test", "");
                currentName = BaseName;
                suffix = "_test";
            }
            else
            {
                defaultName = BaseName;
                currentName = BaseName;
                suffix = "";
            }

            if (char.IsDigit(defaultName, defaultName.Length - 1))
            {
                defaultName = defaultName.Remove(defaultName.Length - 1);
            }

            int i = 1;
            resultName = defaultName;

            while (PK.Wrapper.CheckLibrarProjName(PK.Wrapper.ExpandEnvVars(DirectoryTb.Text, "") + "\\" + currentName + ".proj"))
            {
                resultName = defaultName + i.ToString();
                currentName = resultName + suffix;
                i++;
            }
            return resultName;
        }

        #endregion



        private void IsStubCb_CheckedChanged(object sender, EventArgs e)
        {
            bool chk = IsStubCb.Checked;
            if (TestCb.Checked) TestCb.Checked = false;
            IsStubCb.Checked = chk;
            SetSuffixs();
        }

        private void TestCb_CheckedChanged(object sender, EventArgs e)
        {
            bool chk = TestCb.Checked;
            if (IsStubCb.Checked) IsStubCb.Checked = false;
            TestCb.Checked = chk;
            SetSuffixs();
        }
        
        private void CancelBtn_Click(object sender, EventArgs e)
        {
            this.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.Close();
        }

        private void OtBtn_Click(object sender, EventArgs e)
        {
            try
            {
                if (string.IsNullOrEmpty(DirectoryTb.Text)) throw new DirectoryNotFoundException(Strings.VoidDirectoryField+ ".");
                
                if (PK.Wrapper.CheckLibraryName(NameTb.Text + nameSuffixLbl.Text))
                    throw new ArgumentException(Strings.Library + " \"" + NameTb.Text + nameSuffixLbl.Text + "\"" + Strings.AlreadyExist + ".");

                string path = PK.Wrapper.ExpandEnvVars(DirectoryTb.Text, "") +"\\"+ ProjNameTb.Text + projSuffixLbl.Text+".proj";
                if (File.Exists(path))
                    throw new ArgumentException(Strings.File + "\r\n\"" + path + "\"\r\n" + Strings.AlreadyExist + ".");

                if (this.Library != null)
                {
                    this.Library = PK.Wrapper.CloneLibrary
                        (
                        this.Library,
                        NameTb.Text + nameSuffixLbl.Text,
                        GroupsCb.Text, DirectoryTb.Text + "\\" + ProjNameTb.Text + projSuffixLbl.Text + ".proj",
                        (LibraryLevelWrapper)LevelCb.SelectedItem,
                        IsStubCb.Checked
                        );
                }
                else
                {
                    this.Library = PK.Wrapper.CreateLibrary
                        (
                        NameTb.Text + nameSuffixLbl.Text, 
                        GroupsCb.Text,DirectoryTb.Text+"\\"+ProjNameTb.Text+projSuffixLbl.Text+".proj",
                        (LibraryLevelWrapper)LevelCb.SelectedItem,
                        IsStubCb.Checked
                        );
                }

                //        this.Library = PK.Wrapper.CreateLibrary(RealNameLbl.Text, GroupsCb.Text, this.DirectoryTb.Text);
                this.DialogResult = System.Windows.Forms.DialogResult.OK;
                this.Close();
                        
                        
                
                
            }
            catch (Exception ex)
            {
                MessageBox.Show(this, ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void BrowseBtn_Click(object sender, EventArgs e)
        {
            folderBrowserDialog1.SelectedPath = PK.Wrapper.ExpandEnvVars(DirectoryTb.Text,"");
            if (folderBrowserDialog1.ShowDialog(this) == System.Windows.Forms.DialogResult.OK)
            {
                DirectoryTb.Text = PK.Wrapper.ConvertPathToEnv(folderBrowserDialog1.SelectedPath);
            }
        }

        
    }
}
