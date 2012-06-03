using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using PKStudio.ItemWrappers;
using XsdInventoryFormatObject;
using PKStudio.Dialogs.ManageProjectWizard.Pages;

namespace PKStudio.Dialogs.ManageProjectWizard
{
    public partial class ManageProjectWizard : WizardBase
    {
        WizardParams Param = new WizardParams();

        public ManageProjectWizard()
        {
            InitializeComponent();
        }


        public void SetProject(SolutionWrapper Solution, ProjectWrapper Project)
        {

            MFProject tmpProj = new MFProject();

            Project.InnerObject.CopyTo(tmpProj, Solution.Name);

            Param.NewProject = ProjectWrapper.Wrap<ProjectWrapper>(tmpProj);
            Param.OldProject = Project;
            Param.Solution = Solution;

            if (Project.IsClrProject)
                mPageList.Add(new ManageFeaturesPage(Param));
            mPageList.Add(new ManageLibrariesPage(Param));
            //mPageList.Add(new ManageLibrariesPageTest(Solution, Project, NewProject));

            this.Initialize();
        }
    }
}
