using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using PKStudio.Tree;
using PKStudio.ItemWrappers;

namespace PKStudio.Forms.Editors.Pages.Library
{
	public partial class ISASpecificPage: LibraryPropertyPageBase
	{
        public ISASpecificPage()
            : base()
        {
        }
        public ISASpecificPage(LibraryWrapper Wrapper)
            : base(Wrapper, Strings.ISASpecific)
        {
        }

        protected override void RefreshControl()
        {
            if (this.Wrapper.ISASpecific != null)
            {
                if (!string.IsNullOrEmpty(this.Wrapper.ISASpecific.Guid))
                    SetModel(InventoryBrowserModel.GetModel(this.Wrapper.ISASpecific));
            }
        }
	}
}
