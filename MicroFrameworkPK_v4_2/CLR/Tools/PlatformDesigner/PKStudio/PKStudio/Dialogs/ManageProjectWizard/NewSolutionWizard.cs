using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using PKStudio.Dialogs.ManageProjectWizard.Pages;
using PKStudio.ItemWrappers;
using System.Collections.ObjectModel;

namespace PKStudio.Dialogs.ManageProjectWizard
{
    public partial class NewSolutionWizard : WizardBase
    {
        WizardParams Param = new WizardParams();

        List<BasePage> mBackupPageList = new List<BasePage>();

        public NewSolutionWizard()
        {
            InitializeComponent();

            Param.Solution = null;
            Param.OldProject = null;
            Param.NewProject = null;
            Param.FeaturesInfo = null;

            mPageList.Add(new SolutionDescriptionPage(Param));
            mPageList.Add(new ProcessorPage(Param));
            mPageList.Add(new ProcessorPropertiesPage(Param));
            mPageList.Add(new TransportPage(Param));
            mPageList.Add(new SolutionProjectsPage(Param));
            mPageList.Add(new NewSolutionSummaryPage(Param));

            mBackupPageList.AddRange(mPageList);

            foreach (BasePage bp in mPageList)
            {
                bp.ShowBackBtnEvent += new EventHandler<ShowBtnEventArgs>(bp_ShowBackBtnEvent);
                bp.ShowNextBtnEvent += new EventHandler<ShowBtnEventArgs>(bp_ShowNextBtnEvent);
            }

            this.Initialize();
        }

        void bp_ShowNextBtnEvent(object sender, ShowBtnEventArgs e)
        {
            this.SetNextButtonEnable(e.Show);
            if (sender is SolutionProjectsPage)
            {
                mPageList.Clear();
                mPageList.AddRange(mBackupPageList);
                foreach (ProjectWrapper PW in Param.Solution.Projects)
                {
                    BasePage bp = null;
                    if (PW.IsClrProject)
                    {
                        bp = new ManageFeaturesPage(Param, PW);
                        bp.PageDescription = ManageProjectAndSolutionWizardsStrings.IDS_PAGE_DESCRIPTION_FEATURES + " \"" + PW.Name + "\"";
                        mPageList.Insert(mPageList.Count - 1, bp);
                    }

                    bp = new ManageLibrariesPage(Param, PW);
                    bp.PageDescription = ManageProjectAndSolutionWizardsStrings.IDS_PAGE_DESCRIPTION_LIBRARIES + " for the project \"" + PW.Name + "\"";
                    mPageList.Insert(mPageList.Count - 1, bp);

                }
            }
        }

        void bp_ShowBackBtnEvent(object sender, ShowBtnEventArgs e)
        {
            this.SetBackButtonEnable(e.Show);
        }

        protected override void Finish()
        {

            try
            {
                PK.Wrapper.GenerateSolution(this.Param.Solution);
            }
            catch (Exception exception)
            {
                MessageBox.Show(this, "An error occured during the creation of the Solution.  The Solution may not build properly. " + exception.ToString(), "Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
            }
        }

    }
}
