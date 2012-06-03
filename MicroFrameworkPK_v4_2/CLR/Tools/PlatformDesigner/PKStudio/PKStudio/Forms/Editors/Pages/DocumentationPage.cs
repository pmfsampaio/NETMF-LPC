
using PKStudio.ItemWrappers;
namespace PKStudio.Forms.Editors.Pages
{
    public partial class DocumentationPage : GenericPageBase
    {
        public DocumentationPage(BaseWrapper Wrapper)
            : base(Wrapper)
        {
            InitializeComponent();
            this.NodeName = Strings.Documentation;
            HeaderLbl.Text = this.NodeName;
        }

        #region Override

        public override bool OnApplyChanges()
        {
            this.Wrapper.InnerDocumentation = DocumentationRtb.Text;

            return true;
        }

        protected override void RefreshControl()
        {
            DocumentationRtb.Text = this.Wrapper.InnerDocumentation;
        }

        #endregion

        private void DocumentationRtb_TextChanged(object sender, System.EventArgs e)
        {
            ModifiedChange();
        }
    }
}
