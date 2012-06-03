using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using PKStudio.TreeNodes;
using PKStudio.ItemWrappers;

namespace PKStudio.Tools.KeilGenerator.Wizard.Pages
{
    public partial class SelectProjectPage : BasePage
    {
        public SelectProjectPage() :base()
        {
            InitializeComponent();
        }

        public SelectProjectPage(SolutionWrapper sol, ConvertConfig config)
            : base(sol, config)
        {
            InitializeComponent();
            foreach (ProjectWrapper proj in sol.Projects)
	        {
                TreeNode node = new TreeNode();
                node.Tag = proj;
                node.Text = proj.Name;
                node.Checked = true;
                //node.ImageIndex
                treeView1.Nodes.Add(node);
	        }
            
        }

        public override string PageName
        {
            get
            {
                return "Select project";
            }
        }

        public override string PageDescription
        {
            get
            {
                return "Select Projects to add in uVision solution.";
            }
        }
    }
}
