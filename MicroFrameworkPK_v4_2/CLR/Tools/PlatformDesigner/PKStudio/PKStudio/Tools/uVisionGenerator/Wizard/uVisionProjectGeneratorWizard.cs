using System;
using System.Collections.Generic;
using System.Windows.Forms;
using PKStudio.ItemWrappers;
using PKStudio.Tools.uVisionGenerator.Classes.HelpClasses;
using PKStudio.Tools.uVisionGenerator.Wizard.Pages;

namespace PKStudio.Tools.uVisionGenerator.Wizard
{
    public partial class uVisionProjectGeneratorWizard : Form
    {
        //private SolutionWrapper Sol;
        private ConvertConfig config = new ConvertConfig();
        private ConvertationPage cp = null;

        List<Wizard.Pages.BasePage> mPageList = new List<Wizard.Pages.BasePage>();

        public uVisionProjectGeneratorWizard()
        {
            InitializeComponent();
        }

        /// <summary>
        /// Sets MFProject for generation
        /// </summary>
        /// <param name="LibCat"></param>
        public void SetSolution(SolutionWrapper Sol)
        {
            cp = new Wizard.Pages.ConvertationPage(Sol, config);
            cp.BuildStartEvent += new EventHandler(cp_BuildStartEvent);
            cp.BuildStopEvent += new EventHandler(cp_BuildStopEvent);
            cp.ConvertationStartEvent += new EventHandler(cp_ConvertationStartEvent);
            cp.ConvertationStopEvent += new EventHandler<ConvertationStopEventArgs>(cp_ConvertationStopEvent);

            //mPageList.Add(new Wizard.Pages.IntroPage());
            //mPageList.Add(new Wizard.Pages.SelectProjectPage(Sol, config));
            mPageList.Add(new Wizard.Pages.ProjectsAndConfigurationsPage(Sol, config));
            mPageList.Add(new Wizard.Pages.SelectPathPage(Sol, config));
            mPageList.Add(new Wizard.Pages.ProcessorPage(Sol, config));
            mPageList.Add(new Wizard.Pages.SummaryPage(Sol, config));            
            mPageList.Add(cp);
            mPageList.Add(new Wizard.Pages.ResultPage(Sol, config));

            panel1.Controls.Add(mPageList[0]);
            NameLbl.Text = mPageList[0].PageName;
            DescriptionLbl.Text = mPageList[0].PageDescription;

            Backbtn.Enabled = false;
        }

        void cp_ConvertationStopEvent(object sender, ConvertationStopEventArgs e)
        {
            if (!e.Error)
            {
                NextPage();
                SetButtonEnable(Backbtn, false);
                SetButtonEnable(NextBtn, false);
            }
            SetButtonText(CancelBtn,KeilWizardStrings.IDS_DONE);
        }

        void cp_ConvertationStartEvent(object sender, EventArgs e)
        {
            SetButtonEnable(Backbtn, false);
            SetButtonEnable(NextBtn, false);
        }

        void cp_BuildStopEvent(object sender, EventArgs e)
        {
            SetButtonEnable(CancelBtn, true);
        }

        void cp_BuildStartEvent(object sender, EventArgs e)
        {
            SetButtonEnable(CancelBtn,false);
        }


        private void NextPage()
        {
            try
            {
                int pageindex = mPageList.IndexOf((Wizard.Pages.BasePage)panel1.Controls[0]);

                if (pageindex == mPageList.Count - 1) return;

                mPageList[pageindex].BeforeCloseOnNext();

                ClearPanel();

                //mPageList[pageindex + 1].BeforeShow();
                CallBeforeShow(mPageList[pageindex + 1]);

                AddControlToPanel(mPageList[pageindex + 1]);
                SetLabelText(NameLbl,mPageList[pageindex + 1].PageName);
                SetLabelText(DescriptionLbl,mPageList[pageindex + 1].PageDescription);

                //mPageList[pageindex + 1].AfterShow();
                CallAfterShow(mPageList[pageindex + 1]);

                if (pageindex >= 0) SetButtonEnable(Backbtn,true);
                if (pageindex + 1 >= mPageList.Count - 1) SetButtonEnable(NextBtn,false);
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(this, ex.Message, KeilWizardStrings.IDS_ERROR, MessageBoxButtons.OK, MessageBoxIcon.Error);
            }

        }

        private void PrevPage()
        {
            try
            {
                int pageindex = mPageList.IndexOf((Wizard.Pages.BasePage)panel1.Controls[0]);

                if (pageindex <= 0) return;

                mPageList[pageindex].BeforeCloseOnBack();

                panel1.Controls.Clear();

                mPageList[pageindex - 1].BeforeShow();

                panel1.Controls.Add(mPageList[pageindex - 1]);
                NameLbl.Text = mPageList[pageindex - 1].PageName;
                DescriptionLbl.Text = mPageList[pageindex - 1].PageDescription;

                mPageList[pageindex - 1].AfterShow();

                if (pageindex - 1 < mPageList.Count - 1) NextBtn.Enabled = true;
                if (pageindex - 1 == 0) Backbtn.Enabled = false;
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(this, ex.Message,KeilWizardStrings.IDS_ERROR, MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void CancelBtn_Click(object sender, System.EventArgs e)
        {
            this.Close();
        }

        private void NextBtn_Click(object sender, System.EventArgs e)
        {
            NextPage();
        }

        private void Backbtn_Click(object sender, System.EventArgs e)
        {
            PrevPage();
        }

        private void uVisionProjectGeneratorWizard_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (CancelBtn.Enabled == false)
            {
                e.Cancel = true;
            }
        }


        private delegate void CallAfterShowCallback(BasePage page);
        private void CallAfterShow(BasePage page)
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
        private void CallBeforeShow(BasePage page)
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

        private delegate void SetButtonEnableCallback(Button b, bool value);
        private void SetButtonEnable(Button b, bool value)
        {
            if (b.InvokeRequired)
            {
                SetButtonEnableCallback d = new SetButtonEnableCallback(SetButtonEnable);
                b.BeginInvoke(d, new object[] { b, value });
            }
            else
            {
                b.Enabled = value;
            }
        }

        private delegate void ClearPanelCallback();
        private void ClearPanel()
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
        private void AddControlToPanel(Control control)
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
        private void SetButtonText(Button b, string value)
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
        private void SetLabelText(Label b, string value)
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
}
