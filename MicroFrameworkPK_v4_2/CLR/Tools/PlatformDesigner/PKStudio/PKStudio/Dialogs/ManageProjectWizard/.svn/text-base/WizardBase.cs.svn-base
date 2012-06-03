using System;
using System.Collections.Generic;
using System.Windows.Forms;
using PKStudio.Dialogs.ManageProjectWizard.Pages;
using PKStudio.ItemWrappers;
using XsdInventoryFormatObject;
using System.Collections.ObjectModel;

namespace PKStudio.Dialogs.ManageProjectWizard
{
    public partial class WizardBase : Form
    {

        protected List<BasePage> mPageList = new List<BasePage>();

        public WizardBase()
        {
            InitializeComponent();
        }

        protected void Initialize()
        {
            CallBeforeShow(mPageList[0]);
            NameLbl.Text = mPageList[0].PageName;
            DescriptionLbl.Text = mPageList[0].PageDescription;
            panel1.Controls.Add(mPageList[0]);
            CallAfterShow(mPageList[0]);


            Backbtn.Enabled = false;
            NextBtn.Tag = "next";
        }

        private void NextPage()
        {
            try
            {
                int OldPageindex = mPageList.IndexOf((BasePage)panel1.Controls[0]);

                if (OldPageindex == mPageList.Count - 1) return;

                mPageList[OldPageindex].BeforeCloseOnNext();

                int NewPageIndex = OldPageindex + 1;

                while (!mPageList[NewPageIndex].ToShow)
                {
                    NewPageIndex++;
                }

                ClearPanel();

                //mPageList[pageindex + 1].BeforeShow();
                CallBeforeShow(mPageList[NewPageIndex]);

                AddControlToPanel(mPageList[NewPageIndex]);
                SetLabelText(NameLbl, mPageList[NewPageIndex].PageName);
                SetLabelText(DescriptionLbl, mPageList[NewPageIndex].PageDescription);

                //mPageList[pageindex + 1].AfterShow();
                CallAfterShow(mPageList[NewPageIndex]);

                if (OldPageindex >= 0) SetBackButtonEnable(true);
                if (NewPageIndex >= mPageList.Count - 1)
                {
                    SetNextButtonFinish(true);
                }
                else
                {
                    SetNextButtonFinish(false);
                }
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(this, ex.Message, ManageProjectAndSolutionWizardsStrings.IDS_ERROR, MessageBoxButtons.OK, MessageBoxIcon.Error);
            }

        }

        private void PrevPage()
        {
            try
            {
                int OldPageindex = mPageList.IndexOf((BasePage)panel1.Controls[0]);

                if (OldPageindex <= 0) return;

                mPageList[OldPageindex].BeforeCloseOnBack();

                int NewPageIndex = OldPageindex - 1;

                while (!mPageList[NewPageIndex].ToShow) 
                {
                    NewPageIndex--;
                }

                panel1.Controls.Clear();

                mPageList[NewPageIndex].BeforeShow();

                panel1.Controls.Add(mPageList[NewPageIndex]);
                NameLbl.Text = mPageList[NewPageIndex].PageName;
                DescriptionLbl.Text = mPageList[NewPageIndex].PageDescription;

                mPageList[NewPageIndex].AfterShow();

                if (NewPageIndex < mPageList.Count - 1)
                {
                    SetNextButtonFinish(false);
                }
                else
                {
                    SetNextButtonFinish(true);
                }
                if (NewPageIndex == 0) Backbtn.Enabled = false;
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(this, ex.Message, ManageProjectAndSolutionWizardsStrings.IDS_ERROR, MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void CancelBtn_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void NextBtn_Click(object sender, EventArgs e)
        {
            if (NextBtn.Tag.ToString() == "next")
                NextPage();
            else if (NextBtn.Tag.ToString() == "finish")
            {
                int OldPageindex = mPageList.IndexOf((BasePage)panel1.Controls[0]);
                mPageList[OldPageindex].BeforeCloseOnNext();

                this.Finish();
                this.DialogResult = System.Windows.Forms.DialogResult.OK;
                //this.Close();
            }
        }

        private void Backbtn_Click(object sender, EventArgs e)
        {
            PrevPage();
        }

        protected virtual void Finish()
        {
        }


        //private ProjectWrapper CopyCroject(ProjectWrapper PW)
        //{
        //    MFProject innerProj = new MFProject();
        //    PW.InnerObject.BuildTool.CopyTo(innerProj.BuildTool);
        //    innerProj.Description = PW.Description;
        //    innerProj.Directory = PW.Directory;
        //    innerProj.ExtraAssemblies = new List<string>(PW.ExtraAssemblies);
        //    innerProj.FastCompileFiles = new List<MFBuildFile>(PW.InnerObject.FastCompileFiles);
        //    innerProj.Features = new List<MFComponent>(PW.InnerObject.Features);
        //    innerProj.Guid = PW.Guid;
        //    innerProj.HeaderFiles = new List<MFBuildFile>(PW.InnerObject.HeaderFiles);
        //    innerProj.IncludePaths = new List<MFBuildFile>(PW.InnerObject.IncludePaths);
        //    innerProj.InteropFeatures = new List<string>(PW.InnerObject.InteropFeatures);
        //    innerProj.IsClrProject = PW.IsClrProject;
        //    innerProj.IsSolutionWizardVisible = PW.IsSolutionWizardVisible;
        //    innerProj.Libraries = new List<MFComponent>(PW.InnerObject.Libraries);
        //    innerProj.LibraryCategories = new List<MFComponent>(PW.InnerObject.LibraryCategories);
        //    PW.InnerObject.MemoryMap.CopyTo(innerProj.MemoryMap);
        //    innerProj.Name = PW.Name;
        //    innerProj.OtherFiles = new List<MFBuildFile>(PW.InnerObject.OtherFiles);
        //    innerProj.ProjectPath = PW.ProjectPath;
        //    innerProj.Properties = new List<MFProperty>(PW.InnerObject.Properties);
        //    PW.InnerObject.ScatterFile.CopyTo(innerProj.ScatterFile);
        //    innerProj.SettingsFile = PW.SettingsFile;
        //    innerProj.SourceFiles = new List<MFBuildFile>(PW.InnerObject.SourceFiles);
        //    innerProj.Targets = new List<Microsoft.Build.Construction.ProjectTargetElement>(PW.InnerObject.Targets);
        //    PW.InnerObject.Version.CopyTo(innerProj.Version);

        //    return ProjectWrapper.Wrap<ProjectWrapper>(innerProj);
        //}



        private delegate void CallAfterShowCallback(BasePage page);
        protected void CallAfterShow(BasePage page)
        {
            if (panel1.InvokeRequired)
            {
                CallAfterShowCallback d = new CallAfterShowCallback(CallAfterShow);
                panel1.BeginInvoke(d, new object[] { page });
            }
            else
            {
                page.AfterShow();
            }
        }

        private delegate void CallBeforeShowCallback(BasePage page);
        protected void CallBeforeShow(BasePage page)
        {
            if (panel1.InvokeRequired)
            {
                CallBeforeShowCallback d = new CallBeforeShowCallback(CallBeforeShow);
                panel1.BeginInvoke(d, new object[] { page });
            }
            else
            {
                page.BeforeShow();
            }
        }

        private delegate void SetNextButtonEnableCallback( bool value);
        protected void SetNextButtonEnable(bool value)
        {
            if (NextBtn.InvokeRequired)
            {
                SetNextButtonEnableCallback d = new SetNextButtonEnableCallback(SetNextButtonEnable);
                NextBtn.BeginInvoke(d, new object[] { value });
            }
            else
            {
                NextBtn.Enabled = value;
            }
        }

        private delegate void SetBackButtonEnableCallback(bool value);
        protected void SetBackButtonEnable(bool value)
        {
            if (Backbtn.InvokeRequired)
            {
                SetBackButtonEnableCallback d = new SetBackButtonEnableCallback(SetBackButtonEnable);
                Backbtn.BeginInvoke(d, new object[] { value });
            }
            else
            {
                Backbtn.Enabled = value;
            }
        }

        private delegate void SetNextButtonFinishCallback(bool value);
        protected void SetNextButtonFinish(bool value)
        {
            if (NextBtn.InvokeRequired)
            {
                SetNextButtonFinishCallback d = new SetNextButtonFinishCallback(SetNextButtonEnable);
                NextBtn.BeginInvoke(d, new object[] { value });
            }
            else
            {
                if (value)
                {
                    NextBtn.Text = ManageProjectAndSolutionWizardsStrings.IDS_FINISH_BTN_NAME;
                    NextBtn.Tag = "finish";
                }
                else
                {
                    NextBtn.Text = ManageProjectAndSolutionWizardsStrings.IDS_NEXT_BTN_NAME;
                    NextBtn.Tag = "next";
                }
            }
        }

        private delegate void ClearPanelCallback();
        protected void ClearPanel()
        {
            if (panel1.InvokeRequired)
            {
                ClearPanelCallback d = new ClearPanelCallback(ClearPanel);
                panel1.BeginInvoke(d, new object[] { });
            }
            else
            {
                panel1.Controls.Clear();
            }
        }

        private delegate void AddControlToPanelCallback(Control control);
        protected void AddControlToPanel(Control control)
        {
            if (panel1.InvokeRequired)
            {
                AddControlToPanelCallback d = new AddControlToPanelCallback(AddControlToPanel);
                panel1.BeginInvoke(d, new object[] { control });
            }
            else
            {
                panel1.Controls.Add(control);
            }
        }

        private delegate void SetButtonTextCallback(Button b, string value);
        protected void SetButtonText(Button b, string value)
        {
            if (b.InvokeRequired)
            {
                SetButtonTextCallback d = new SetButtonTextCallback(SetButtonText);
                b.BeginInvoke(d, new object[] { b, value });
            }
            else
            {
                b.Text = value;
            }
        }

        private delegate void SetLabelTextCallback(Label b, string value);
        protected void SetLabelText(Label b, string value)
        {
            if (b.InvokeRequired)
            {
                SetLabelTextCallback d = new SetLabelTextCallback(SetLabelText);
                b.BeginInvoke(d, new object[] { b, value });
            }
            else
            {
                b.Text = value;
            }
        }
    }

    public class WizardParams
    {
        public ProjectWrapper OldProject { get; set; }
        public ProjectWrapper NewProject { get; set; }
        public SolutionWrapper Solution { get; set; }
        public FeatureReferenceInfo FeaturesInfo { get; set; }
    }
}
