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
    public partial class LibraryDependenciesPage : LibraryDependenciesPageBase
    {
        public LibraryDependenciesPage()
            : base()
        {
            InitializeComponent();
        }
        public LibraryDependenciesPage(LibraryWrapper Wrapper)
            : base(Wrapper, Strings.Dependencies)
        {
            InitializeComponent();
        }

        protected override void RefreshControl()
        {
            this.SetModel(InventoryBrowserModel.GetModel(this.Wrapper.InnerDependencies));
        }
    }
}
