using PKStudio.ItemWrappers;
using PKStudio.Tree;
using System.Collections.Generic;
using PKStudio.Tree.Nodes;
using System.Collections.ObjectModel;
using System.Windows.Forms;
using System;

namespace PKStudio.Dialogs.ManageProjectWizard.Pages
{
    public partial class ManageLibrariesPage : BaseTreePage
    {
        private string _pageName = ManageProjectAndSolutionWizardsStrings.IDS_PAGE_NAME_LIBRARIES;
        private string _pageDescription = ManageProjectAndSolutionWizardsStrings.IDS_PAGE_DESCRIPTION_LIBRARIES;

        ProjectWrapper project = null;

        public ManageLibrariesPage(WizardParams Params)
            : base(Params)
        {
            InitializeComponent();
        }

        public ManageLibrariesPage(WizardParams Params, ProjectWrapper project)
            : base(Params)
        {
            InitializeComponent();
            this.project = project;
        }

        protected override ReferenceInfo GetReferenceInfo()
        {
            if (this.project == null)
                return new LibrariesInfo(Params.NewProject, Params.Solution, Params.FeaturesInfo);
            else
                return new LibrariesInfo(project, Params.Solution, Params.FeaturesInfo);
        }

        protected override bool OnCheckBoxVisible(ComponentNode node)
        {
            switch (node.TypedContent.ComponentType)
            {
                //case ComponentTypeWrapper.LibraryCategory:
                case ComponentTypeWrapper.Library:
                    return true;
            }
            return false;
        }

        private enum ViewModeSelector
        {
            All,
            Unresolved
        } 

        private class ViewOptions
        {
            public OnAddComponentHandler Filter {get; set;}
            public string Text {get; set;}
        }

        private static Dictionary<ViewModeSelector, ViewOptions> viewModes = new Dictionary<ViewModeSelector, ViewOptions>() 
        { 
            { ViewModeSelector.All, new ViewOptions() {Filter = LibrariesInfo.AllComponents, Text = ManageProjectAndSolutionWizardsStrings.IDS_BTN_TEXT_UNRESOLVED}},
            { ViewModeSelector.Unresolved, new ViewOptions() {Filter = LibrariesInfo.UnresolvedComponents, Text = ManageProjectAndSolutionWizardsStrings.IDS_BTN_TEXT_ALL}},
        };

        private void SetView(ViewModeSelector mode, ToolStripButton btn)
        {
            ViewOptions viewOptions = viewModes[mode];
            btn.Text = viewOptions.Text;
            this.References.OnAddComponent = viewOptions.Filter;
        }

        protected override void btnShowComponents_CheckedChanged(object sender, EventArgs e)
        {
            ToolStripButton btn = sender as ToolStripButton;
            if (btn != null)
            {
                if (btn.Checked)
                {
                    this.SetView(ViewModeSelector.Unresolved, btn);
                }
                else
                {
                    this.SetView(ViewModeSelector.All, btn);
                }
                UpdateTree();
            }
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
