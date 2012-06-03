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
using Aga.Controls.Tree.NodeControls;
using Aga.Controls.Tree;
using System.Collections.ObjectModel;
using XsdInventoryFormatObject;
using System.IO;

namespace PKStudio.Dialogs.ManageProjectWizard.Pages
{
    public partial class ProjectTemplatePage : BasePage
    {
        ProjectWrapper selectedProject = null;

        public ProjectTemplatePage(WizardParams Params)
            : base(Params)
        {
            InitializeComponent();

            if (PK.Wrapper.GetProjectTemplates().Count == 0)
            {
                PK.Wrapper.LoadTemplateProjects();
            }

            _treeView.NodeControls.Clear();
            _treeView.AddIconControl("Icon");
            _treeView.AddTextBoxControl("Name");

            Dictionary<string, ProjectWrapper> dictionary = new Dictionary<string, ProjectWrapper>();
            foreach (ProjectWrapper project in Params.Solution.Projects)
            {
                dictionary.Add(project.Name.ToUpper(),project);
            }

            Collection<ProjectWrapper> PWList = new Collection<ProjectWrapper>();

            foreach (ProjectWrapper PW in PK.Wrapper.GetProjectTemplates())
            {
                if (!dictionary.ContainsKey(PW.Name.ToUpper()))
                {
                    PWList.Add(PW);
                }
            }

            _treeView.SetModel(InventoryBrowserModel.GetProjectTemplatesModel(PWList), false);            
        }

        public override string PageName
        {
            get
            {
                return ManageProjectAndSolutionWizardsStrings.IDS_PAGE_NAME_TEMPLATE;
            }
        }

        public override string PageDescription
        {
            get
            {
                return ManageProjectAndSolutionWizardsStrings.IDS_PAGE_DESCRIPTION_TEMPLATE;
            }
        }


        public override void BeforeCloseOnNext()
        {
            if (selectedProject != null)
            {
                string str = @"$(SPOCLIENT)\Solutions\" + Params.Solution.Name + @"\";

                MFProject tmpProj = new MFProject();


                selectedProject.InnerObject.CopyTo(tmpProj, Params.Solution.Name);
                if (tmpProj != null)
                {
                    tmpProj.ProjectPath = str + Path.GetFileName(tmpProj.Directory) + @"\" + Path.GetFileName(tmpProj.ProjectPath);
                    tmpProj.SettingsFile = str + Params.Solution.Name + ".settings";                    
                }

                Params.NewProject = ProjectWrapper.Wrap<ProjectWrapper>(tmpProj);
            }
        }

        public override void BeforeShow()
        {
            base.BeforeShow();
            if (selectedProject == null)
            {
                this.OnShowNextBtn(false);
            }
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
            ProjectWrapper PW = e.Object as ProjectWrapper;
            if (PW != null)
            {
                ShowDescription(PW);
                selectedProject = PW;
                this.OnShowNextBtn(true);
            }
        }
    }
}
