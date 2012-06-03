using PKStudio.ItemWrappers;

namespace PKStudio.Forms.Editors.Pages.LibraryCategory
{
    public partial class MainPage : LibraryCategoryPageBase
    {
        public MainPage()
        {
            InitializeComponent();
        }

        public MainPage(LibraryCategoryWrapper LibCat)
            :base(LibCat)
        {
            InitializeComponent();

            GroupsCb.Items.Clear();
            GroupsCb.Items.Add("");

            foreach (LibraryCategoryWrapper libCat in PK.Wrapper.GetLibraryCategories())
            {
                if (!GroupsCb.Items.Contains(libCat.Groups))
                {
                    GroupsCb.Items.Add(libCat.Groups);
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
            this.Wrapper.Name = NameTb.Text + LevelLbl.Text;

            this.Wrapper.Groups = GroupsCb.Text;

            this.Wrapper.Level = (LibraryLevelWrapper)LevelCb.SelectedItem;

            return true;
        }

        protected override void RefreshControl()
        {
            string name = "";
            if (Wrapper.Name.Contains("_HAL"))
            {
                name = Wrapper.Name.Replace("_HAL", "");
            }
            else if (Wrapper.Name.Contains("_PAL"))
            {
                name = Wrapper.Name.Replace("_PAL", "");
            }
            else if (Wrapper.Name.Contains("_CLR"))
            {
                name = Wrapper.Name.Replace("_CLR", "");
            }
            else if (Wrapper.Name.Contains("_Support"))
            {
                name = Wrapper.Name.Replace("_Support", "");
            }
            else
            {
                name = Wrapper.Name;
            }

            NameTb.Text = name;

            if (GroupsCb.Items.Contains(Wrapper.Groups)) GroupsCb.SelectedItem = Wrapper.Groups;
            else
            {
                if (GroupsCb.Items.Count > 0) GroupsCb.SelectedIndex = 0;
            }

            LevelCb.SelectedItem = Wrapper.Level;
        }

        #endregion

        

        private void LevelCb_SelectedIndexChanged(object sender, System.EventArgs e)
        {
            LevelLbl.Text = "_" + LevelCb.Text;
            ModifiedChange();
        }

        private void NameTb_TextChanged(object sender, System.EventArgs e)
        {
            ModifiedChange();
        }

        private void GroupsCb_TextUpdate(object sender, System.EventArgs e)
        {
            ModifiedChange();
        }

        private void GroupsCb_SelectedIndexChanged(object sender, System.EventArgs e)
        {
            ModifiedChange();
        }
    }
}
