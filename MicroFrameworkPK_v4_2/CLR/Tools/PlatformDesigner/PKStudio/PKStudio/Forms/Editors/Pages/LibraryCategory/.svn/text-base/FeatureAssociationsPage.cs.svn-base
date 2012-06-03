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
    public partial class FeatureAssocioationsPage : LibraryCategoryDependenciesPageBase
    {
        public FeatureAssocioationsPage()
            : base()
        {
            InitializeComponent();
        }
        public FeatureAssocioationsPage(LibraryCategoryWrapper Wrapper)
            : base(Wrapper, Strings.FeatureAssociations)
        {
            InitializeComponent();
        }

        protected override void RefreshControl()
        {
            this.SetModel(InventoryBrowserModel.GetModel(this.Wrapper.FeatureAssociations));
        }
    }

}
