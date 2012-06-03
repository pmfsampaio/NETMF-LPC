using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using PKStudio.ItemWrappers;
using PKStudio.Tools.uVisionGenerator.Classes.HelpClasses;
using PKStudio.Tools.uVisionGenerator.Classes.uvProjectClasses;
using System.IO;

namespace PKStudio.Tools.uVisionGenerator.Wizard.Pages
{
    public partial class ResultPage : BasePage
    {
        public ResultPage(SolutionWrapper sol, ConvertConfig config)
            : base(sol, config)
        {
            InitializeComponent();
        }

        public override string PageName
        {
            get
            {
                return KeilWizardStrings.IDS_PAGE_NAME_RESULTS;
            }
        }

        public override string PageDescription
        {
            get
            {
                return KeilWizardStrings.IDS_PAGE_DESCRIPTION_RESULTS;
            }
        }

        public override void BeforeShow()
        {
            //this.ShowSummary();
        }

        public override void AfterShow()
        {
            this.ShowSummary();
        }


        private void ShowSummary()
        {
            ClearText();
            if (config.Result != null)
            {
                AppendText(KeilWizardStrings.IDS_CONVERT_COLPETED + "\r\n");

                AppendText("Multi project workspace:\r\n");
                AppendLink(config.SolutionPath + @"\" + config.Result.Name + ".mpw\r\n\r\n");

                AppendText("\r\nProjects:\r\n");
                foreach (uVisionProject proj in config.Result.Projects)
                {
                    AppendText("\r\n" + proj.Name.Trim() + ":\r\n");
                    AppendText(KeilWizardStrings.IDS_FILES + @":  " + proj.FileList.Count + "\r\n");
                    AppendText(KeilWizardStrings.IDS_TARGETS + @":  " + proj.TargetList.Count + "\r\n");
                    AppendLink(proj.ProjectPath + @"\" + proj.Name + ".Uv2" + "\r\n");
                    //AppendText(".........................................\r\n");
                }
            }
            else
            {
                AppendText(KeilWizardStrings.IDS_CONVERT_FAILED + "\r\n");
            }
        }

        private delegate void ClearTextCallback();
        private void ClearText()
        {
            if (ResultsRTB.InvokeRequired)
            {
                ClearTextCallback d = new ClearTextCallback(ClearText);
                ResultsRTB.BeginInvoke(d, new object[] { });
            }
            else
            {
                ResultsRTB.Clear();
            }
        }


        private delegate void AppendTextCallback(string text);
        private void AppendText(string text)
        {
            if (ResultsRTB.InvokeRequired)
            {
                AppendTextCallback d = new AppendTextCallback(AppendText);
                ResultsRTB.BeginInvoke(d, new object[] { text });
            }
            else
            {
                ResultsRTB.AppendText(text);
            }
        }

        private delegate void AppendLinkCallback(string text);
        private void AppendLink(string text)
        {
            if (ResultsRTB.InvokeRequired)
            {
                AppendLinkCallback d = new AppendLinkCallback(AppendLink);
                ResultsRTB.BeginInvoke(d, new object[] { text});
            }
            else
            {
                ResultsRTB.InsertLink(text);
            }
        }

        private void ResultsRTB_LinkClicked(object sender, LinkClickedEventArgs e)
        {
            if (string.IsNullOrEmpty(e.LinkText)) return;
            string path = PK.Wrapper.ExpandEnvVars(e.LinkText, "");
            if (System.IO.File.Exists(Path.GetFullPath(path)))
            {
                System.Diagnostics.Process.Start("explorer.exe", "/select, \"" + Path.GetFullPath(path) + "\"");
            }
            else if (Directory.Exists(Path.GetFullPath(path)))
            {
                System.Diagnostics.Process.Start("explorer.exe", "\"" + Path.GetFullPath(path) + "\"");
            }
        }
    }
}
