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
	public partial class ComponentDependenciesPage: FeatureDependenciesPageBase
	{
        public ComponentDependenciesPage()
            : base()
        {
            InitializeComponent();
        }
        public ComponentDependenciesPage(FeatureWrapper Wrapper)
            : base(Wrapper, Strings.ComponentDependencies)
        {
            InitializeComponent();
        }

        protected override void RefreshControl()
        {
            this.SetModel(InventoryBrowserModel.GetModel(this.Wrapper.ComponentDependencies));
        }

    }
}
