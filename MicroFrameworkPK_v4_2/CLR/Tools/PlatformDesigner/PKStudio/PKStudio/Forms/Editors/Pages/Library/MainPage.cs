using System.IO;
using PKStudio.ItemWrappers;
namespace PKStudio.Forms.Editors.Pages.Library
{
    public partial class MainPage : LibraryWrapperPageBase
    {
        public MainPage()
        {
            InitializeComponent();
        }
        public MainPage(LibraryWrapper Lib)
            : base(Lib)
        {
            InitializeComponent();

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

            this.NodeName = Strings.Main;
            HeaderLbl.Text = this.NodeName;
        }

        #region Override

        public override bool OnApplyChanges()
        {
            this.Wrapper.Name = NameTb.Text + nameSuffixLbl.Text;
            this.Wrapper.LibraryFile = Wrapper.Name + ".$(LIB_EXT)";
            this.Wrapper.ManifestFile = Wrapper.Name + ".$(LIB_EXT).manifest";
            this.Wrapper.Groups = GroupsCb.Text;
            this.Wrapper.Level = (LibraryLevelWrapper)LevelCb.SelectedItem;
            //this.Lib.ProjectPath = DirectoryTb.Text + "\\" + ProjNameTb.Text + projSuffixLbl.Text + ".proj";
            //this.Lib.IsStub = IsStubCb.Checked;

            return true;
        }

        protected override void RefreshControl()
        {
            if (GroupsCb.Items.Contains(Wrapper.Groups)) GroupsCb.SelectedItem = Wrapper.Groups;
            else
            {
                if (GroupsCb.Items.Count > 0) GroupsCb.SelectedIndex = 0;
            }

            string name = Wrapper.Name;
            string projname = Path.GetFileNameWithoutExtension(Wrapper.ProjectPath);

            if (Wrapper.Name.Contains("test") && projname.Contains("_test"))
            {
                TestCb.Checked = true;
            }
            else TestCb.Checked = false;

            IsStubCb.Checked = Wrapper.IsStub;

            if (Wrapper.Name.Contains("test"))
            {
                name = Wrapper.Name.Replace("test", "");
            }
            else if (Wrapper.Name.Contains("_stub"))
            {
                name = Wrapper.Name.Replace("_stub", "");
            }
            else if (Wrapper.Name.Contains("_stubs"))
            {
                name = Wrapper.Name.Replace("_stubs", "");
            }
            else
            {
                name = Wrapper.Name;
            }

            NameTb.Text = name;

            LevelCb.SelectedItem = Wrapper.Level;

            DirectoryTb.Text = Path.GetDirectoryName(Wrapper.ProjectPath);

            if (projname.Contains("_test"))
            {
                projname = projname.Replace("_test", "");                
            }

            ProjNameTb.Text = projname;

            SetSuffixs();
        }

        #endregion


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
                        DirectoryTb.Text = DirectoryTb.Text.Replace("\\stubs", "");
                    }
                }
            }
        }

        #endregion

        private void IsStubCb_CheckedChanged(object sender, System.EventArgs e)
        {
            bool chk = IsStubCb.Checked;
            if (TestCb.Checked) TestCb.Checked = false;
            IsStubCb.Checked = chk;
            SetSuffixs();
            ModifiedChange();
        }

        private void TestCb_CheckedChanged(object sender, System.EventArgs e)
        {
            bool chk = TestCb.Checked;
            if (IsStubCb.Checked) IsStubCb.Checked = false;
            TestCb.Checked = chk;
            SetSuffixs();
            ModifiedChange();
        }

        private void BrowseBtn_Click(object sender, System.EventArgs e)
        {
            folderBrowserDialog1.SelectedPath = PK.Wrapper.ExpandEnvVars(DirectoryTb.Text, "");
            if (folderBrowserDialog1.ShowDialog(this) == System.Windows.Forms.DialogResult.OK)
            {
                DirectoryTb.Text = PK.Wrapper.ConvertPathToEnv(folderBrowserDialog1.SelectedPath);
                ModifiedChange();
            }
        }

        private void NameTb_TextChanged(object sender, System.EventArgs e)
        {
            ModifiedChange();
        }

        private void GroupsCb_SelectedIndexChanged(object sender, System.EventArgs e)
        {
            ModifiedChange();
        }

        private void GroupsCb_TextUpdate(object sender, System.EventArgs e)
        {
            ModifiedChange();
        }

        private void LevelCb_SelectedIndexChanged(object sender, System.EventArgs e)
        {
            ModifiedChange();
        }

        private void DirectoryTb_TextChanged(object sender, System.EventArgs e)
        {
            ModifiedChange();
        }

        private void ProjNameTb_TextChanged(object sender, System.EventArgs e)
        {
            ModifiedChange();
        }
    }
}
