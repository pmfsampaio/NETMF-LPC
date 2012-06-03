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
    public partial class NewProjectWizard : WizardBase
    {
        WizardParams Param = new WizardParams();

        ProjectDescriptionPage mPDP = null;
        ManageFeaturesPage mMFP = null;

        public NewProjectWizard(SolutionWrapper Solution)
        {
            InitializeComponent();

            Param.Solution = Solution;
            Param.OldProject = null;

            MFProject tmpProj = new MFProject();
            Param.NewProject = ProjectWrapper.Wrap<ProjectWrapper>(tmpProj);

            mPDP = new ProjectDescriptionPage(Param);
            mPDP.IsCLREvent += new EventHandler<IsCLREventArgs>(mPDP_IsCLREvent);

            mMFP = new ManageFeaturesPage(Param);

            mPageList.Add(new ProjectTemplatePage(Param));
            mPageList.Add(mPDP);
            mPageList.Add(mMFP);
            mPageList.Add(new ManageLibrariesPage(Param));

            foreach (BasePage bp in mPageList)
            {
                bp.ShowBackBtnEvent += new EventHandler<ShowBtnEventArgs>(bp_ShowBackBtnEvent);
                bp.ShowNextBtnEvent += new EventHandler<ShowBtnEventArgs>(bp_ShowNextBtnEvent);
            }

            this.Initialize();
        }

        void mPDP_IsCLREvent(object sender, IsCLREventArgs e)
        {
            mMFP.ToShow = e.IsCLR;
        }

        void bp_ShowNextBtnEvent(object sender, ShowBtnEventArgs e)
        {
            this.SetNextButtonEnable(e.Show);
        }

        void bp_ShowBackBtnEvent(object sender, ShowBtnEventArgs e)
        {
            this.SetBackButtonEnable(e.Show);
        }
    }

    
}
