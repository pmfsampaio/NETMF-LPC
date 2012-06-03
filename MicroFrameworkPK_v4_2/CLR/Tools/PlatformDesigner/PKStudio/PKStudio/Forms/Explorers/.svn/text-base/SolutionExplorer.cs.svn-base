using System.Windows.Forms;
using System.Collections.Generic;
using PKStudio.TreeNodes;
using System;
using PKStudio.ItemWrappers;
using PKStudio.Tree;
using PKStudio.Tree.Nodes;

namespace PKStudio.Forms.Explorers
{
    public partial class SolutionExplorer : InventoryExplorer
    {
        public SolutionExplorer()
        {
            InitializeComponent();
            PK.Wrapper.LoadSolutionAsyncCompleteEvent += new EventHandler<PortingKitWrapper.LoadSolutionAsyncCompletedEventArgs>(PKWrapper_LoadSolutionAsyncCompleteEvent);

        }

        void PKWrapper_LoadSolutionAsyncCompleteEvent(object sender, PKStudio.PortingKitWrapper.LoadSolutionAsyncCompletedEventArgs e)
        {
            SetModel(new InventoryBrowserModel(new SolutionNode(e.Solution, null)));
        }
        protected override void OnAction(BaseNode node, NodeAction action)
        {
            switch (action)
            {
                case NodeAction.Manage:
                    using (PKStudio.Dialogs.ManageProjectWizard.ManageProjectWizard mManageProjectComponentsWizard = new Dialogs.ManageProjectWizard.ManageProjectWizard())
                    {
                        ProjectNode PN = node.GetRoot<ProjectNode>();
                        SolutionNode SN = node.GetRoot<SolutionNode>();
                        if ((PN != null) && (SN != null))
                        {
                            mManageProjectComponentsWizard.SetProject(SN.TypedContent, PN.TypedContent);
                            mManageProjectComponentsWizard.ShowDialog(this);
                        }
                    }
                    break;
                case NodeAction.New:
                    SolutionNode solution = node as SolutionNode;
                    if (solution != null)
                    {
                        //MessageBox.Show(string.Format("Add Project in Solution {0}", solution.Name));

                        using (PKStudio.Dialogs.ManageProjectWizard.NewProjectWizard mNewProjectWizard = new Dialogs.ManageProjectWizard.NewProjectWizard(solution.TypedContent))
                        {
                            mNewProjectWizard.ShowDialog(this);
                        }
                    }
                    break;
                case NodeAction.Remove:
                    ProjectNode project = node as ProjectNode;
                    if (project != null)
                    {
                        MessageBox.Show(string.Format("Remove Project {0} from Solution", project.Name));
                    }
                    break;
                default:
                    base.OnAction(node, action);
                    break;
            }
        }


    }
}
