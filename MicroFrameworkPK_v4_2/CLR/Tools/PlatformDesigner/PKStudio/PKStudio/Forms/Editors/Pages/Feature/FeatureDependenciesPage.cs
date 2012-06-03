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

namespace PKStudio.Forms.Editors.Pages.Feature
{
    public partial class FeatureDependenciesPage : FeatureDependenciesPageBase
	{
		public FeatureDependenciesPage()
		{
			InitializeComponent();
		}
        public FeatureDependenciesPage(FeatureWrapper Wrapper)
            : base(Wrapper, Strings.FeatureDependencies)
        {
            InitializeComponent();
        }

        protected override void RefreshControl()
        {
            SetModel(InventoryBrowserModel.GetModel(this.Wrapper.FeatureDependencies));
        }
    }
}
