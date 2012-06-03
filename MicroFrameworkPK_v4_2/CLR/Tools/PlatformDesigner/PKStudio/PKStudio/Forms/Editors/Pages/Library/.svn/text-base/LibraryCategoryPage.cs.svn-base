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

namespace PKStudio.Forms.Editors.Pages.Library
{
	public partial class LibraryCategoryPage: LibraryPropertyPageBase
	{
        public LibraryCategoryPage()
            : base()
        {
        }
        public LibraryCategoryPage(LibraryWrapper Wrapper)
            : base(Wrapper, Strings.LibraryCategory)
        {
        }

        protected override void RefreshControl()
        {
            if (this.Wrapper.LibraryCategory != null)
            {
                if (!string.IsNullOrEmpty(this.Wrapper.LibraryCategory.Guid))
                    SetModel(InventoryBrowserModel.GetModel(this.Wrapper.LibraryCategory));
            }
        }
	}
}
