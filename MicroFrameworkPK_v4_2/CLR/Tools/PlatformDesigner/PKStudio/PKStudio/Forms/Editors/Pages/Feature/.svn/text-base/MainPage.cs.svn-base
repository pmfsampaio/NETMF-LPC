using PKStudio.ItemWrappers;

namespace PKStudio.Forms.Editors.Pages.Feature
{
    public partial class MainPage : FeaturePageBase
    {
        public MainPage()
        {
            InitializeComponent();
        }

        public MainPage(FeatureWrapper Feat)
            :base(Feat)
        {
            InitializeComponent();

            GroupsCb.Items.Clear();
            GroupsCb.Items.Add("");

            foreach (FeatureWrapper feat in PK.Wrapper.GetFeatures())
            {
                if (!GroupsCb.Items.Contains(feat.Groups))
                {
                    GroupsCb.Items.Add(feat.Groups);
                }
            }
            this.NodeName = Strings.Main;
            HeaderLbl.Text = this.NodeName;
        }

        #region Override

        public override bool OnApplyChanges()
        {
            this.Wrapper.Name = NameTb.Text;

            this.Wrapper.Groups = GroupsCb.Text;

            return true;
        }

        protected override void RefreshControl()
        {

            NameTb.Text = Wrapper.Name;

            if (GroupsCb.Items.Contains(Wrapper.Groups)) GroupsCb.SelectedItem = Wrapper.Groups;
            else
            {
                if (GroupsCb.Items.Count > 0) GroupsCb.SelectedIndex = 0;
            }
        }

        #endregion

        
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
