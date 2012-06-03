using PKStudio.ItemWrappers;
namespace PKStudio.Forms.Editors.Pages.LibraryCategory
{
    public partial class TemplatesPage : LibraryCategoryPageBase
    {
        public TemplatesPage(LibraryCategoryWrapper LibCat)
            : base(LibCat)
        {
            InitializeComponent();

            this.NodeName = Strings.LibraryProjCache;
            HeaderLbl.Text = this.NodeName;
        }

        #region Override

        public override bool OnApplyChanges()
        {
           

            return true;
        }

        protected override void RefreshControl()
        {
            TemplatesRtb.Clear();
            foreach (ApiTemplateWrapper s in this.Wrapper.Templates)
            {
                TemplatesRtb.AppendText("FilePath: " + s.FilePath + "\r\n");
                TemplatesRtb.AppendText("Description: " + s.Description + "\r\n\r\n");
            }
        }

        #endregion
    }
}
