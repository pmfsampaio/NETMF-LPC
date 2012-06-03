using System;
using System.IO;
using PKStudio.Tools.uVisionGenerator.Classes.HelpClasses;
using PKStudio.ItemWrappers;

namespace PKStudio.Tools.uVisionGenerator.Wizard.Pages
{
    public partial class SelectPathPage : BasePage
    {
        private string DefaultString = string.Empty;

        public SelectPathPage(SolutionWrapper sol, ConvertConfig config)
            : base(sol, config)
        {
            InitializeComponent();
            DefaultString = Path.GetDirectoryName(PK.Wrapper.ExpandEnvVars(sol.ProjectPath, "")) + "\\uv2mpw";
        }

        public override void BeforeCloseOnNext()
        {
            if (!Path.IsPathRooted(UV2PathTB.Text))
            {
                throw new DirectoryNotFoundException(KeilWizardStrings.IDS_ERROR_INVALID_PATH);
            }
            config.SolutionPath = UV2PathTB.Text;
        }

        public override void BeforeShow()
        {
            if (!string.IsNullOrEmpty(config.SolutionPath))
            {
                UV2PathTB.Text = config.SolutionPath;
            }
            else
            {
                UV2PathTB.Text = DefaultString;
            }
            base.BeforeShow();
        }

        public override string PageName
        {
            get
            {
                return KeilWizardStrings.IDS_PAGE_NAME_SELECT_DIRECTORY;
            }
        }

        public override string PageDescription
        {
            get
            {
                return KeilWizardStrings.IDS_PAGE_DESCRIPTION_SELECT_DIRECTORY;
            }
        }

        private void UV2SelectBtn_Click(object sender, EventArgs e)
        {
            folderBrowserDialog1.Description = KeilWizardStrings.IDS_SELECT_DIRECTORY;
            if (folderBrowserDialog1.ShowDialog(this) == System.Windows.Forms.DialogResult.OK)
            {
                this.UV2PathTB.Text = folderBrowserDialog1.SelectedPath;
            }
        }
    }
}
