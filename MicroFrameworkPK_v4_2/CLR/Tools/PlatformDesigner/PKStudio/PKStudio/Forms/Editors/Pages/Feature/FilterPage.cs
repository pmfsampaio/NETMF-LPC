
using PKStudio.ItemWrappers;
namespace PKStudio.Forms.Editors.Pages.Feature
{
    public partial class FilterPage : FeaturePageBase
    {
        public FilterPage(FeatureWrapper Feat)
            : base(Feat)
        {
            InitializeComponent();
            this.NodeName = Strings.Filter;
            HeaderLbl.Text = this.NodeName;
        }

        #region Override

        public override bool OnApplyChanges()
        {
            this.Wrapper.Filter = FilterRtb.Text;

            return true;
        }

        protected override void RefreshControl()
        {
            FilterRtb.Text = this.Wrapper.Filter;
        }

        #endregion

        private void FilterRtb_TextChanged(object sender, System.EventArgs e)
        {
            ModifiedChange();
        }
    }
}
