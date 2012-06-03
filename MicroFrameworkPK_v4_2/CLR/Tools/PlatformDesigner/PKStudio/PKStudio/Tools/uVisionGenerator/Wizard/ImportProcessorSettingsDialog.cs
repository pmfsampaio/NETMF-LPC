using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using PKStudio.Tools.uVisionGenerator.Classes.HelpClasses;
using PKStudio.Tools.uVisionGenerator.Classes.uvProjectClasses;
using System.IO;

namespace PKStudio.Tools.uVisionGenerator.Wizard
{
    public partial class ImportProcessorSettingsDialog : Form
    {
        TargetOptions TO = null;

        public ImportProcessorSettingsDialog()
        {
            InitializeComponent();
            AddBtn.Enabled = false;
        }

        private void SelectBtn_Click(object sender, EventArgs e)
        {
            FileTb.Text = string.Empty;
            DeviceLbl.Text = "Device: ";
            VendorLbl.Text = "Vendor: ";
            NameTb.Text = string.Empty;
            DescTb.Text = string.Empty;
            AddBtn.Enabled = false;

            if (openFileDialog1.ShowDialog(this) == DialogResult.OK)
            {
                try
                {
                    TO = null;

                    switch (Path.GetExtension(openFileDialog1.FileName).ToLower())
                    {
                        case".uv2":
                            TO = uVisionProjectSettingsImporter.ImportUV3Project(openFileDialog1.FileName);
                            break;
                        case ".uvproj":
                        default:
                            throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);                            
                    }
                    if (TO != null)
                    {
                        FileTb.Text = openFileDialog1.FileName;
                        NameTb.Text = TO.Device;
                        DeviceLbl.Text = "Device: " + TO.Device;
                        VendorLbl.Text = "Vendor: " + TO.Vendor;
                        AddBtn.Enabled = true;
                    }
                }
                catch (Exception ex)
                {
                    MessageBox.Show(this, ex.Message, KeilWizardStrings.IDS_ERROR, MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
        }

        private void CancelBtn_Click(object sender, EventArgs e)
        {
            this.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.Close();
        }

        private void AddBtn_Click(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(NameTb.Text))
            {
                MessageBox.Show(this, KeilWizardStrings.IDS_NAME_FIELD_EMPTY, KeilWizardStrings.IDS_ERROR, MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
            if (TO != null)
            {
                try
                {
                    string path = Application.StartupPath + @"\Tools\uVisionGenerator\Processors\" + NameTb.Text+".xml";

                    if (System.IO.File.Exists(path))
                    {
                        MessageBox.Show(this, KeilWizardStrings.IDS_FILE + "\"" + NameTb.Text + "\"" + KeilWizardStrings.IDS_ALREADY_EXIST, KeilWizardStrings.IDS_ERROR, MessageBoxButtons.OK, MessageBoxIcon.Error);
                        return;
                    }
                    else
                    {
                        TO.Name = NameTb.Text;
                        TO.Description = DescTb.Text;
                        TO.SerializeXLM(path);
                    }
                }
                catch (Exception ex)
                {
                    MessageBox.Show(this, ex.Message, KeilWizardStrings.IDS_ERROR, MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }
                this.DialogResult = System.Windows.Forms.DialogResult.OK;
                this.Close();
            }
        }
    }
}
