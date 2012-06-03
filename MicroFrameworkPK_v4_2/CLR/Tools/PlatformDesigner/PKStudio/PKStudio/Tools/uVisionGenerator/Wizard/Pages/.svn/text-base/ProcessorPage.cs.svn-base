using System;
using System.Collections.Generic;
using System.IO;
using System.Windows.Forms;
using PKStudio.ItemWrappers;
using PKStudio.Tools.uVisionGenerator.Classes.HelpClasses;
using PKStudio.Tools.uVisionGenerator.Classes.uvProjectClasses;

namespace PKStudio.Tools.uVisionGenerator.Wizard.Pages
{
    public partial class ProcessorPage : BasePage
    {
        TargetOptions SelectedProc = null;
        List<TargetOptions> TOList = new List<TargetOptions>();

        public ProcessorPage(SolutionWrapper sol, ConvertConfig config)
            : base(sol, config)
        {
            InitializeComponent();
        }

        public override void BeforeCloseOnNext()
        {
            if (SelectedProc == null) throw new ArgumentNullException(KeilWizardStrings.IDS_ERROR_SELECT_PROCESSOR, "SelectedProc");
            config.Processor = SelectedProc;
            base.BeforeCloseOnNext();
        }

        public override void BeforeShow()
        {

            RefreshDialog();

            if (config.Processor != null)
            {
                SelectedProc = config.Processor;
                TreeNode DeviceNode = GetDeviceNode(SelectedProc.Device);
                DeviceNode.EnsureVisible();
                treeView1.SelectedNode = DeviceNode;
            }
            else
            {
                ProcessorWrapper proc = PK.Wrapper.FindProcessor(sol.Processor.Guid);
                TreeNode DeviceNode = GetDeviceNode(proc.Name);
                if (DeviceNode != null)
                {
                    DeviceNode.EnsureVisible();
                    treeView1.SelectedNode = DeviceNode;
                }
            }

            base.BeforeShow();
        }

        private void RefreshDialog()
        {
            TOList.Clear();
            treeView1.Nodes.Clear();
            LoadOptions(Application.StartupPath + @"\Tools\uVisionGenerator\Processors");

            foreach (TargetOptions to in TOList)
            {
                TreeNode VendorNode = GetVendorNode(to.Vendor);
                if (VendorNode == null)
                {
                    VendorNode = new TreeNode(to.Vendor);
                    treeView1.Nodes.Add(VendorNode);
                }
                VendorNode.Collapse();
                VendorNode.SelectedImageIndex = 0;
                VendorNode.ImageIndex = 0;

                TreeNode DeviceNode = new TreeNode(to.Device);
                DeviceNode.SelectedImageIndex = 2;
                DeviceNode.ImageIndex = 2;
                DeviceNode.Tag = to;

                VendorNode.Nodes.Add(DeviceNode);                
            }
            treeView1.Sort();
        }

        private TreeNode GetVendorNode(string name)
        {
            foreach (TreeNode tn in treeView1.Nodes)
            {
                if (tn.Text == name) return tn;
            }
            return null;
        }

        private TreeNode GetDeviceNode(string name)
        {
            foreach (TreeNode tn in treeView1.Nodes)
            {
                foreach (TreeNode n in tn.Nodes)
                {
                    if (n.Text.ToLower().Contains(name.ToLower())) return n;
                }
            }
            return null;
        }

        public void LoadOptions(string path)
        {
            string[] files = Directory.GetFiles(path);

            foreach (string file in files)
            {
                try
                {
                    TOList.Add(TargetOptions.DesirializeXLM(file));
                }
                catch { }
            }

            string[] directories = Directory.GetDirectories(path);
            foreach (string dir in directories)
            {
                this.LoadOptions(dir);
            }
        }

        public override string PageName
        {
            get
            {
                return KeilWizardStrings.IDS_PAGE_NAME_SELECT_PROCESSOR;
            }
        }

        public override string PageDescription
        {
            get
            {
                return KeilWizardStrings.IDS_PAGE_DESCRIPTION_SELECT_PROCESSOR;
            }
        }

        private void treeView1_AfterExpand(object sender, TreeViewEventArgs e)
        {
            e.Node.SelectedImageIndex = 1;
            e.Node.ImageIndex = 1;
        }

        private void treeView1_AfterCollapse(object sender, TreeViewEventArgs e)
        {
            e.Node.SelectedImageIndex = 0;
            e.Node.ImageIndex = 0;
        }

        private void treeView1_AfterSelect(object sender, TreeViewEventArgs e)
        {
            if (e.Node != null)
                if (e.Node.Tag != null)
                {
                    SelectedProc = (TargetOptions)e.Node.Tag;
                    ShowProcDetales(SelectedProc);
                }
                else
                {
                    SelectedProc = null;
                    DetalesRTB.Clear();
                }
        }

        private void ShowProcDetales(TargetOptions opts)
        {
            DetalesRTB.Clear();
            DetalesRTB.AppendText("Vendor:\t" + opts.Vendor + "\r\n");
            DetalesRTB.AppendText("Device:\t" + opts.Device + "\r\n");
            DetalesRTB.AppendText("CPU Type:\t" + opts.ACPUTYP + "\r\n");
            DetalesRTB.AppendText("Name:\t\t" + opts.Name + "\r\n");
            DetalesRTB.AppendText("Description:\t" + opts.Description + "\r\n");
        }

        private void ImportBtn_Click(object sender, EventArgs e)
        {
            using (ImportProcessorSettingsDialog ID = new ImportProcessorSettingsDialog())
            {
                if (ID.ShowDialog(this) == DialogResult.OK)
                {
                    RefreshDialog();
                }
            }
        }
    }
}
