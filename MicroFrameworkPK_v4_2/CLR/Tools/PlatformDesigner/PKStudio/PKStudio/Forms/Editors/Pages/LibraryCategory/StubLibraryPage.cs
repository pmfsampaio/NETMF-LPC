using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using PKStudio.ItemWrappers;
using PKStudio.Tree;

namespace PKStudio.Forms.Editors.Pages.LibraryCategory
{
    public partial class StubLibraryPage : LibraryCategoryPropertyPageBase
    {
        public StubLibraryPage()
            : base()
        {
        }
        public StubLibraryPage(LibraryCategoryWrapper Wrapper)
            : base(Wrapper, Strings.StubLibrary)
        {
        }

        protected override void RefreshControl()
        {
            if (this.Wrapper.StubLibrary != null)
            {
                if (!string.IsNullOrEmpty(this.Wrapper.StubLibrary.Guid))
                    SetModel(InventoryBrowserModel.GetModel(this.Wrapper.StubLibrary));
            }
        }
    }
}
