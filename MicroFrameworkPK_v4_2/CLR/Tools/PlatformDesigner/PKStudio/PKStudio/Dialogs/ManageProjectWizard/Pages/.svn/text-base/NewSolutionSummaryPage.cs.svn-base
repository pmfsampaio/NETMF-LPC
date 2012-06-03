using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using PKStudio.ItemWrappers;

namespace PKStudio.Dialogs.ManageProjectWizard.Pages
{
    public partial class NewSolutionSummaryPage : BasePage
    {
        public NewSolutionSummaryPage(WizardParams Params)
            : base(Params)
        {
            InitializeComponent();
        }

        public override string PageName
        {
            get
            {
                return ManageProjectAndSolutionWizardsStrings.IDS_PAGE_NAME_NEW_SOLUTION_SUMMARY;
            }
        }

        public override string PageDescription
        {
            get
            {
                return ManageProjectAndSolutionWizardsStrings.IDS_PAGE_DESCRIPTION_NEW_SOLUTION_SUMMARY;
            }
        }

        public override void BeforeShow()
        {
            SummaryRTB.Clear();
            SummaryRTB.AppendText("Solution summary:\r\n\r\n");

            SummaryRTB.AppendText("\tSolution:\t\t\t"+Params.Solution.Name+"\r\n");
            SummaryRTB.AppendText("\tAuthor:\t\t\t" + Params.Solution.Author + "\r\n");
            SummaryRTB.AppendText("\tPath:\t\t\t\t" + PK.Wrapper.SpoClientPath + @"Solutions\" + Params.Solution.Name + "\r\n");
            SummaryRTB.AppendText("\tDebugger Port:\t\t" + Params.Solution.DebuggerPort + "\r\n\r\n");

            SummaryRTB.AppendText("\tProcessor:\t\t\t" + Params.Solution.Processor.Name + "\r\n");
            SummaryRTB.AppendText("\tMemory Profile:\t\t" + Params.Solution.MemoryProfile + "\r\n");
            SummaryRTB.AppendText("\tRAM Memory Base:\t\t" + "0x" + Params.Solution.RamBase.ToString("X08") + "\r\n");
            SummaryRTB.AppendText("\tRAM Memory Size:\t\t" + "0x" + Params.Solution.RamLength.ToString("X08") + "\r\n");
            SummaryRTB.AppendText("\tFlash Memory Base:\t\t" + "0x" + Params.Solution.FlashBase.ToString("X08") + "\r\n");
            SummaryRTB.AppendText("\tFlash Memory Size:\t\t" + "0x" + Params.Solution.FlashLength.ToString("X08") + "\r\n");
            SummaryRTB.AppendText("\tSystem Clock (Hz):\t\t" + Params.Solution.SystemClockSpeed + "\r\n");
            SummaryRTB.AppendText("\tSlow Clock (Hz):\t\t" + Params.Solution.SlowClockSpeed + "\r\n");
            

            SummaryRTB.AppendText("\r\n\r\n");



            foreach (ProjectWrapper PW in Params.Solution.Projects)
            {
                SummaryRTB.AppendText("Project " + PW.Name+ "\r\n");
                SummaryRTB.AppendText("\tDescription:\t\t\t" + PW.Description + "\r\n");
                SummaryRTB.AppendText("\tPath:\t\t\t\t" + PK.Wrapper.ExpandEnvVars(PW.ProjectPath,"") + "\r\n\r\n");
            }
        }
    }
}
