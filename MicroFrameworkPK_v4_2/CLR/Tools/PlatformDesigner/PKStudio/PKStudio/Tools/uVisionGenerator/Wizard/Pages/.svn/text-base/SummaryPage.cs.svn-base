using PKStudio.Tools.uVisionGenerator.Classes.HelpClasses;
using PKStudio.ItemWrappers;

namespace PKStudio.Tools.uVisionGenerator.Wizard.Pages
{
    public partial class SummaryPage : BasePage
    {
        public SummaryPage(SolutionWrapper sol, ConvertConfig config)
            : base(sol, config)
        {
            InitializeComponent();
        }

        public override void BeforeCloseOnNext()
        {

        }

        public override void BeforeShow()
        {
            this.ShowSummary();
        }

        public override string PageName
        {
            get
            {
                return KeilWizardStrings.IDS_PAGE_NAME_SUMMARY;
            }
        }

        public override string PageDescription
        {
            get
            {
                return KeilWizardStrings.IDS_PAGE_DESCRIPTION_SUMMARY;
            }
        }

        private void ShowSummary()
        {
            SummaryRTB.Clear();
            SummaryRTB.AppendText("Solution\r\n");
            SummaryRTB.AppendText("--------\r\n");
            SummaryRTB.AppendText("Path:\t\t" + config.SolutionPath + "\r\n");
            SummaryRTB.AppendText("Name:\t\t" + config.Name + "\r\n");
            SummaryRTB.AppendText("Processor:\t" + config.Processor.Device + "\r\n");

            SummaryRTB.AppendText("\r\nProjects:\r\n");
            foreach (ConvertableMFProject proj in config.ProjectList)
            {
                SummaryRTB.AppendText(".........................................\r\n");
                SummaryRTB.AppendText("Name:\t\t" + proj.Project.Name.Trim() + "\r\n");
                SummaryRTB.AppendText("Build type:\t" + proj.BuildType + "\r\n");
                SummaryRTB.AppendText("Media type:\t" + proj.MediaType + "\r\n");
            }
            SummaryRTB.AppendText(".........................................\r\n");

            SummaryRTB.DetectUrls = true;



        }
    }
}
