
using PKStudio.ItemWrappers;
namespace PKStudio.Forms.Editors.Pages.Feature
{
    public partial class FlagsPage : FeaturePageBase
    {
        public FlagsPage(FeatureWrapper Feat)
            : base(Feat)
        {
            InitializeComponent();
            this.NodeName = Strings.Flags;
            HeaderLbl.Text = this.NodeName;
        }

        #region Override

        public override bool OnApplyChanges()
        {
            this.Wrapper.IsSolutionWizardVisible = IsSolutionWizardVisibleCB.Checked;
            this.Wrapper.Hidden = HiddenCheckBox.Checked;
            this.Wrapper.Required = RequiredCheckBox.Checked;

            return true;
        }

        protected override void RefreshControl()
        {
            IsSolutionWizardVisibleCB.Checked = this.Wrapper.IsSolutionWizardVisible;
            HiddenCheckBox.Checked = this.Wrapper.Hidden;
            RequiredCheckBox.Checked = this.Wrapper.Required;
        }

        #endregion

        private void IgnoreDefaultLibPathCheckBox_CheckedChanged(object sender, System.EventArgs e)
        {
            ModifiedChange();
        }

        private void IsTransportCheckBox_CheckedChanged(object sender, System.EventArgs e)
        {
            ModifiedChange();
        }

        private void RequiredCheckBox_CheckedChanged(object sender, System.EventArgs e)
        {
            ModifiedChange();
        }
    }
}
