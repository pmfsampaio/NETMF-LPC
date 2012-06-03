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
using System.Collections.ObjectModel;
using Aga.Controls.Tree.NodeControls;
using PKStudio.Tree.Nodes;
using XsdInventoryFormatObject;
using System.IO;

namespace PKStudio.Dialogs.ManageProjectWizard.Pages
{
    public partial class SolutionProjectsPage : BasePage
    {
        public SolutionProjectsPage(WizardParams Params)
            : base(Params)
        {
            InitializeComponent();

            if (PK.Wrapper.GetProjectTemplates().Count == 0)
            {
                PK.Wrapper.LoadTemplateProjects();
            }

            _treeView.NodeControls.Clear();
            NodeCheckBox checkBox = _treeView.AddCheckBoxControl("Checked");
            checkBox.IsVisibleValueNeeded += new EventHandler<NodeControlValueEventArgs>(checkBox_IsVisibleValueNeeded);
            checkBox.IsEditEnabledValueNeeded += new EventHandler<NodeControlValueEventArgs>(checkBox_IsVisibleValueNeeded);
            _treeView.AddIconControl("Icon");
            _treeView.AddTextBoxControl("Name");

            List<ComponentWrapper> nativeProjects = new List<ComponentWrapper>();
            List<ComponentWrapper> clrProjects = new List<ComponentWrapper>();
            foreach (ProjectWrapper project in PK.Wrapper.GetProjectTemplates())
            {
                ComponentWrapper component = ComponentWrapper.GetComponentWrapper(project);
                if (project.IsClrProject)
                    clrProjects.Add(component);
                else
                    nativeProjects.Add(component);
            }

            Collection<RootNode> roots = new Collection<RootNode>();
            roots.Add(new RootNode(null, "Native Projects", nativeProjects.ToArray()));
            roots.Add(new RootNode(null, "CLR Projects", clrProjects.ToArray()));
            _treeView.SetModel(InventoryBrowserModel.GetModel(roots), true);

        }

        void checkBox_IsVisibleValueNeeded(object sender, NodeControlValueEventArgs e)
        {
            e.Value = e.Node.Tag is ComponentNode;
        }

        public override string PageName
        {
            get
            {
                return ManageProjectAndSolutionWizardsStrings.IDS_PAGE_NAME_SOLUTION_PROJECTS;
            }
        }

        public override string PageDescription
        {
            get
            {
                return ManageProjectAndSolutionWizardsStrings.IDS_PAGE_DESCRIPTION_SOLUTION_PROJECTS;
            }
        }


        public override void BeforeCloseOnNext()
        {
            Params.Solution.Projects.Clear();
            foreach (BaseNode BN in _treeView.AllNodes)
            {
                ComponentNode CN = BN as ComponentNode;

                if (CN == null) continue;
                if (!CN.Checked) continue;
                else
                {
                    string str = @"$(SPOCLIENT)\Solutions\" + Params.Solution.Name + @"\";

                    ProjectWrapper Template = FindProjectTemplate(CN.TypedContent);

                    MFProject tmpProj = new MFProject();
                    Template.InnerObject.CopyTo(tmpProj, Params.Solution.Name);
                    if (tmpProj != null)
                    {
                        tmpProj.ProjectPath = str + Path.GetFileName(tmpProj.Directory) + @"\" + Path.GetFileName(tmpProj.ProjectPath);
                        tmpProj.SettingsFile = str + Params.Solution.Name + ".settings";
                        Params.Solution.Projects.Add(ProjectWrapper.Wrap<ProjectWrapper>(tmpProj));
                    }
                }
            }

            this.OnShowNextBtn(true);
        }


        private void ShowDescription(ProjectWrapper project)
        {
            DescriptionTB.Clear();
            DescriptionTB.AppendText("Name: " + project.Name + "\r\n\r\n");
            DescriptionTB.AppendText("Project Path:\r\n");
            DescriptionTB.AppendText(project.ProjectPath + "\r\n\r\n");
            DescriptionTB.AppendText("Description:\r\n");
            DescriptionTB.AppendText(project.Description + "\r\n\r\n");
        }

        private void _treeView_SelectionChangedEvent(object sender, Forms.BaseForms.ObjectEventArgs e)
        {
            ComponentWrapper CW = e.Object as ComponentWrapper;
            if (CW != null)
            {
                ShowDescription(FindProjectTemplate(CW));
                this.OnShowNextBtn(true);
            }
        }

        private ProjectWrapper FindProjectTemplate(ComponentWrapper CW)
        {
            foreach (ProjectWrapper project in PK.Wrapper.GetProjectTemplates())
            {
                if (string.Compare(project.Name, CW.Name, true) == 0)
                {
                    return project;
                }
            }
            return null;
        }
    }
}
