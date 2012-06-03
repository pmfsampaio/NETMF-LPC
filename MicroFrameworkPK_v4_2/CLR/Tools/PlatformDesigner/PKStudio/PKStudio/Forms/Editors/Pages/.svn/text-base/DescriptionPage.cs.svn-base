using PKStudio.ItemWrappers;

namespace PKStudio.Forms.Editors.Pages
{
    public partial class DescriptionPage : GenericPageBase
    {
        public DescriptionPage(BaseWrapper wrapper)
            : base(wrapper)
        {
            InitializeComponent();
            this.NodeName = Strings.Description;
            HeaderLbl.Text = this.NodeName;
        }

        #region Override

 
        public override bool OnApplyChanges()
        {
            this.Wrapper.InnerDescription = DescriptionRtb.Text;
            return true;
        }

        protected override void RefreshControl()
        {
            DescriptionRtb.Text = this.Wrapper.InnerDescription;
        }

        #endregion

        private void DescriptionRtb_TextChanged(object sender, System.EventArgs e)
        {
            ModifiedChange();
        }
    }
}
