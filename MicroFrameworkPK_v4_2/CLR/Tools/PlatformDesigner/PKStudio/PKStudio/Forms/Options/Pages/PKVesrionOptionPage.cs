using OptionsHelper.Options;
using System;
using Microsoft.Win32;
using PKStudio.Forms.Options.Options;
using System.IO;
using System.Windows.Forms;

namespace PKStudio.Forms.Options.Pages
{
    public partial class PKVesrionOptionPage : OptionsControlBase
    {
        public PKVesrionOptionPage(OptionsBase option)
        {
            InitializeComponent();
            this.controlledOption = option;

            VerCB.Items.Clear();

            VerCB.Items.Add(new PKVer("Manual select", string.Empty));
            //string s =  Environment.GetEnvironmentVariable("SPOCLIENT");
            //if (!string.IsNullOrEmpty(s))
            //{
            //    VerCB.Items.Add(new PKVer("Environment variable", s));
            //}

            using (RegistryKey key = Registry.LocalMachine.OpenSubKey(@"Software\Microsoft\.NETMicroFrameworkPortingKit"))
            {
                if (key != null)
                {
                    foreach (string str in key.GetSubKeyNames())
                    {
                        using (RegistryKey key1 = key.OpenSubKey(str))
                        {
                            if (key1 != null)
                            {
                                VerCB.Items.Add(new PKVer(str, key1.GetValue("InstallRoot").ToString()));
                            }
                            
                        }
                    }
                }
            }            


            VerCB.SelectedIndex = 0;
            string s =  Environment.GetEnvironmentVariable("SPOCLIENT");

            if (s[s.Length - 1] != '\\') s += "\\";

            if (!string.IsNullOrEmpty(s))
            {
                PathTB.Text = s;

                PKVersionOption po = this.controlledOption as PKVersionOption;

                for (int i = 1; i < VerCB.Items.Count; i++)
                {
                    PKVer ver = VerCB.Items[i] as PKVer;
                    if (ver != null)
                    {
                        if (String.Compare(ver.Path, s, true) == 0)
                        {
                            VerCB.SelectedIndex = i;
                        }
                    }
                }
            }
        }

        #region Override

        public override string NodeName
        {
            get
            {
                return Strings.PK_VERSION_OPTION;
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
            ((PKVersionOption)option).OnApplyChanges();
            this.RefreshControl();

            ModifiedChange();
        }
        #endregion

        private void RefreshControl()
        {
            PKVersionOption po = this.controlledOption as PKVersionOption;
            string s = Environment.GetEnvironmentVariable("SPOCLIENT");

            if (String.Compare(po.PKVersion.Path, s, true) == 0)
            {
                for (int i = 0; i < VerCB.Items.Count; i++)
                {
                    PKVer ver = VerCB.Items[i] as PKVer;
                    if (ver != null)
                    {
                        if (ver.Equals(po.PKVersion))
                        {
                            PathTB.Text = po.PKVersion.Path;
                            VerCB.SelectedIndex = i;
                        }
                    }
                }
            }
      
            //this.Modified = true;
        }

        private void VerCB_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (VerCB.SelectedIndex == 0)
            {
                PathTB.Enabled = true;
                BrowseBtn.Enabled = true;
            }
            else
            {
                PathTB.Enabled = false;
                BrowseBtn.Enabled = false;
            }

            PKVer selIt = VerCB.SelectedItem as PKVer;

            if (selIt != null)
            {
                if (selIt.Path != null)
                {
                    PathTB.Text = selIt.Path;
                    PKVersionOption po = this.controlledOption as PKVersionOption;
                    if (po != null) po.PKVersion = selIt;
                }
            }
            this.ModifiedChange();
        }

        private void PathTB_TextChanged(object sender, EventArgs e)
        {
            PKVer selIt = VerCB.SelectedItem as PKVer;

            if (selIt != null)
            {
                selIt.Path = PathTB.Text;
                PKVersionOption po = this.controlledOption as PKVersionOption;
                if (po != null) po.PKVersion = selIt;
            }
            this.ModifiedChange();
        }

        private void BrowseBtn_Click(object sender, EventArgs e)
        {
            if (folderBrowserDialog1.ShowDialog(this) == System.Windows.Forms.DialogResult.OK)
            {

                if (string.IsNullOrEmpty(folderBrowserDialog1.SelectedPath) || !Directory.Exists(folderBrowserDialog1.SelectedPath) || !Directory.Exists(folderBrowserDialog1.SelectedPath + @"\DeviceCode\Targets\"))
                {
                    MessageBox.Show(this, "Selected directory is not Porting Kit directory.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
                else
                {
                    PathTB.Text = folderBrowserDialog1.SelectedPath;
                }
            }
        }
    }

    
}
