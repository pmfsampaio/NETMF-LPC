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
	public partial class ProcessorSpecificPage: LibraryPropertyPageBase
	{
        public ProcessorSpecificPage()
            : base()
        {
        }
        public ProcessorSpecificPage(LibraryWrapper Wrapper)
            : base(Wrapper, Strings.ProcessorSpecific)
        {
        }

        protected override void RefreshControl()
        {
            if (this.Wrapper.ProcessorSpecific != null)
            {
                if (!string.IsNullOrEmpty(this.Wrapper.ProcessorSpecific.Guid))
                    SetModel(InventoryBrowserModel.GetModel(this.Wrapper.ProcessorSpecific));
            }
        }
	}
}
