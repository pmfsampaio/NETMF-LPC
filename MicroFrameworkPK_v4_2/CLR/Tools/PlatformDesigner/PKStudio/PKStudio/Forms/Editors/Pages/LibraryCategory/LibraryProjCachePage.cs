
using PKStudio.ItemWrappers;
namespace PKStudio.Forms.Editors.Pages.LibraryCategory
{
    public partial class LibraryProjCachePage : LibraryCategoryPageBase
    {
        public LibraryProjCachePage(LibraryCategoryWrapper LibCat)
            : base(LibCat)
        {
            InitializeComponent();
            this.NodeName = Strings.Templates;
            HeaderLbl.Text = this.NodeName;
        }

        #region Override

        public override bool OnApplyChanges()
        {


            return true;
        }

        protected override void RefreshControl()
        {
            ProjCacheListBox.Items.Clear();
            foreach (string s in Wrapper.LibraryProjCache)
            {
                ProjCacheListBox.Items.Add(s);
            }
        }

        #endregion
    }
}
