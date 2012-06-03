using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace PKStudio
{
    public partial class SetSPOForm : Form
    {
        public SetSPOForm()
        {
            InitializeComponent();
        }

        private string mpath = "";

        public string Path { get { return mpath; } set { mpath = value;} }

        private void OpenForm_Load(object sender, EventArgs e)
        {
            string portingKitRegistryValue = Helper.GetPortingKitRegistryValue("", "InstallRoot");

            if (string.IsNullOrEmpty(portingKitRegistryValue) || !Directory.Exists(portingKitRegistryValue))
            {
                portingKitRegistryValue = Environment.GetEnvironmentVariable("SPOCLIENT");
            }
            if (!string.IsNullOrEmpty(portingKitRegistryValue) && Directory.Exists(portingKitRegistryValue))
            {
                this.textBoxSpoClientPath.Text = portingKitRegistryValue;
            }
            this.pidLabel.Text = "Product ID: " + Helper.GetProductId();            
        }

        private void OkBtn_Click(object sender, EventArgs e)
        {
            this.Path = this.textBoxSpoClientPath.Text;
            if (!Directory.Exists(this.Path) || !Directory.Exists(this.Path + @"\DeviceCode\Targets\"))
            {
                MessageBox.Show(this, Strings.InvalidPkDirectory, Strings.Error, MessageBoxButtons.OK, MessageBoxIcon.Hand);
                this.textBoxSpoClientPath.Select(0, -1);                
            }
            else
            {
                Environment.SetEnvironmentVariable("SPOCLIENT", this.Path);
                this.DialogResult = System.Windows.Forms.DialogResult.OK;
                this.Close();
            }
        }

        private void CancelBtn_Click(object sender, EventArgs e)
        {
            this.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.Close();
        }

        private void BrowseBtn_Click(object sender, EventArgs e)
        {
            if (folderBrowserDialog1.ShowDialog(this) == System.Windows.Forms.DialogResult.OK)
            {
                this.textBoxSpoClientPath.Text = folderBrowserDialog1.SelectedPath;
            }
        }        
    }
}
