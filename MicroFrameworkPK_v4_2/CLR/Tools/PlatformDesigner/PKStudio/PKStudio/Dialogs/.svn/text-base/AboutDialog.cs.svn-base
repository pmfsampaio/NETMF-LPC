using System;
using System.Reflection;
using System.Windows.Forms;
using Microsoft.Win32;
using System.Diagnostics;

namespace PKStudio.Dialogs
{
    public partial class AboutDialog : Form
    {
        public AboutDialog()
        {
            InitializeComponent();
        }

        private void AboutDialog_Load(object sender, EventArgs e)
        {
            Helper.AssemblyInfoHelper asmhelper = new Helper.AssemblyInfoHelper(Assembly.GetExecutingAssembly());

            this.Text = Strings.About + " " + asmhelper.Title;
            TitleLbl.Text = asmhelper.Title;
            VersionLbl.Text = Strings.Version + " " + asmhelper.AssemblyVersion;
            CopyrightLbl.Text = asmhelper.Copyright;
            richTextBox1.Clear();

            RegistryKey key2 = Registry.LocalMachine.OpenSubKey(@"Software\Microsoft\.NETMicroFrameworkPortingKit");
            if (key2 != null)
            {
                string[] subkeys = key2.GetSubKeyNames();
                string path = string.Empty;
                string RegPath = string.Empty;

                richTextBox1.Clear();

                foreach (string s in subkeys)
	            {
                    RegistryKey key = key2.OpenSubKey(s);

                    RegPath = key.GetValue("InstallRoot").ToString();
                    path = PK.Wrapper.SpoClientPath;
                    if (path[path.Length - 1] != '\\') path += "\\";

                    if (string.Compare(RegPath, path, true) == 0)
                    {
                        richTextBox1.AppendText(Strings.Version + ": " + s + "\r\n");
                    }
	            }

                richTextBox1.AppendText(Strings.Location + ": " + PK.Wrapper.SpoClientPath);
            }
        }

        private void OkBtn_Click(object sender, EventArgs e)
        {
            this.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.Close();
        }

        private void mailtoLabel_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            if (sender is LinkLabel)
            {
                string link = string.Format("mailto:{0}", (sender as LinkLabel).Text);
                try
                {
                    Process.Start(link);
                }
                catch
                {
                }
            }
        }
    }
}
