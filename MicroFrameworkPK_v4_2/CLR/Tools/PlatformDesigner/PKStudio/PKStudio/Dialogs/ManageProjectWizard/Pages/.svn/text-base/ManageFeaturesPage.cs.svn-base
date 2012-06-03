using PKStudio.ItemWrappers;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System;
using PKStudio.TreeNodes;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using PKStudio.Tree;
using Aga.Controls.Tree.NodeControls;
using PKStudio.Tree.Nodes;
using Aga.Controls.Tree;
using System.Collections;
using System.Diagnostics;

namespace PKStudio.Dialogs.ManageProjectWizard.Pages
{
    public partial class ManageFeaturesPage : BaseTreePage
    {
        private string _pageName = ManageProjectAndSolutionWizardsStrings.IDS_PAGE_NAME_FEATURES;
        private string _pageDescription = ManageProjectAndSolutionWizardsStrings.IDS_PAGE_DESCRIPTION_FEATURES;

        ProjectWrapper project = null;

        public ManageFeaturesPage(WizardParams Params)
            : base(Params)
        {
            InitializeComponent();
        }

        public ManageFeaturesPage(WizardParams Params, ProjectWrapper project)
            : base(Params)
        {
            InitializeComponent();
            this.project = project;
        }

        protected override ReferenceInfo GetReferenceInfo()
        {
            if (this.project == null)
                return this.Params.FeaturesInfo = new FeatureReferenceInfo(Params.NewProject, Params.Solution);
            else
                return this.Params.FeaturesInfo = new FeatureReferenceInfo(project, Params.Solution);
        }

        protected override bool OnCheckBoxVisible(ComponentNode node)
        {
            switch (node.TypedContent.ComponentType)
            {
                case ComponentTypeWrapper.Feature:
                    return true;
            }
            return false;
        }
   
        public override string PageName
        {
            get
            {
                return _pageName;
            }
            set
            {
                _pageName = value;
            }
        }

        public override string PageDescription
        {
            get
            {
                return _pageDescription;
            }
            set
            {
                _pageDescription = value;
            }
        }

    }
}
