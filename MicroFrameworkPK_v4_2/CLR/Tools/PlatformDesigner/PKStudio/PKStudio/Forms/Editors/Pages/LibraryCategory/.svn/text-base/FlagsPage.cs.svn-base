
using PKStudio.ItemWrappers;
namespace PKStudio.Forms.Editors.Pages.LibraryCategory
{
    public partial class FlagsPage : LibraryCategoryPageBase
    {
        public FlagsPage(LibraryCategoryWrapper LibCat)
            : base(LibCat)
        {
            InitializeComponent();
            this.NodeName = Strings.Flags;
            HeaderLbl.Text = this.NodeName;
        }

        #region Override

        public override bool OnApplyChanges()
        {
            this.Wrapper.IgnoreDefaultLibPath = IgnoreDefaultLibPathCheckBox.Checked;
            this.Wrapper.IsTransport = IsTransportCheckBox.Checked;
            this.Wrapper.Required = RequiredCheckBox.Checked;

            return true;
        }

        protected override void RefreshControl()
        {
            IgnoreDefaultLibPathCheckBox.Checked = this.Wrapper.IgnoreDefaultLibPath;
            IsTransportCheckBox.Checked = this.Wrapper.IsTransport;
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
