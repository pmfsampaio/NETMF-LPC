using OptionsHelper.Options;
using PKStudio.Forms.Options.Options;
using Microsoft.Win32;
using System.Windows.Forms;
using System.Diagnostics;

namespace PKStudio.Forms.Options.Pages
{
    public partial class EnvironmentOptionsPage : OptionsControlBase
    {
        public EnvironmentOptionsPage(OptionsBase option)
        {
            InitializeComponent();
            this.controlledOption = option;

            ToolCB.Items.Clear();

            ToolCB.Items.Add("Visual Studio 10");
            ToolCB.Items.Add("Visual Studio 9");
            ToolCB.Items.Add("SHC 9.2");
            ToolCB.Items.Add("RVDS 4.0");
            ToolCB.Items.Add("RVDS 3.1");
            ToolCB.Items.Add("RVDS 3.0");
            ToolCB.Items.Add("MDK 3.80a");
            ToolCB.Items.Add("MDK 3.1");
            ToolCB.Items.Add("GCC 4.2");
            ToolCB.Items.Add("ADI5.0");

            ToolCB.SelectedIndex = 6;
            UpdatePath();
            this.Modified = false;
        }

        #region Override

        public override string NodeName
        {
            get
            {
                return Strings.ENVIRONMENT;
            }
        }
        public override bool OnApplyChanges()
        {
            return this.controlledOption.OnApplyChanges();
        }

        protected override void OnInitialized()
        {
            this.controlledOption.OnInitialized();
            this.RefreshControl();
        }

        public override void SetOption(OptionsBase option)
        {
            base.SetOption(option);
            ((EnvironmentOption)option).OnApplyChanges();
            this.RefreshControl();

            ModifiedChange();
        }

        private void RefreshControl()
        {
            EnvironmentOption eo = (EnvironmentOption)this.controlledOption;

            PathTB.Text = eo.Path;
            ToolCB.SelectedIndex = (int)eo.Tool;            
            this.Modified = false;
        }
        #endregion

        private void BrowseBtn_Click(object sender, System.EventArgs e)
        {
            if (folderBrowserDialog1.ShowDialog(this) == System.Windows.Forms.DialogResult.OK)
            {
                PathTB.Text = folderBrowserDialog1.SelectedPath;
            }
        }

        private void ToolCB_SelectedIndexChanged(object sender, System.EventArgs e)
        {
            EnvironmentOption eo = (EnvironmentOption)this.controlledOption;
            eo.Tool = (EnvironmentOption.TOOL)ToolCB.SelectedIndex;

            UpdatePath();

            ModifiedChange();
        }

        private void UpdatePath()
        {
            if (!string.IsNullOrEmpty(PathTB.Text))
            {
                switch ((EnvironmentOption.TOOL)ToolCB.SelectedIndex)
                {
                    case EnvironmentOption.TOOL.VS10:
                        break;
                    case EnvironmentOption.TOOL.VS9:
                        break;
                    case EnvironmentOption.TOOL.SHC:
                        break;
                    case EnvironmentOption.TOOL.RVDS4_0:
                        break;
                    case EnvironmentOption.TOOL.RVDS3_1:
                        break;
                    case EnvironmentOption.TOOL.RVDS3_0:
                        break;
                    case EnvironmentOption.TOOL.MDK3_80a:
                        RegistryKey key = null;
                        key = Registry.LocalMachine.OpenSubKey(@"SOFTWARE\Keil\Products\RLARM");
                        if (key != null)
                        {
                            PathTB.Text = (string)key.GetValue("Path", "");
                            break;
                        }
                        key = Registry.LocalMachine.OpenSubKey(@"SOFTWARE\Keil\Products\MDK");
                        if (key != null)
                        {
                            PathTB.Text = (string)key.GetValue("Path", "");
                            break;
                        }
                        break;
                    case EnvironmentOption.TOOL.MDK3_1:
                        break;
                    case EnvironmentOption.TOOL.GCC:
                        break;
                    case EnvironmentOption.TOOL.BLACKFIN:
                        break;
                    case EnvironmentOption.TOOL.RVDS4_1:
                        break;
                    default:
                        break;
                }

                //ModifiedChange();
            }
        }

        private void PathTB_TextChanged(object sender, System.EventArgs e)
        {
            EnvironmentOption eo = (EnvironmentOption)this.controlledOption;
            eo.Path = PathTB.Text;
            ModifiedChange();
        }
    }
}
