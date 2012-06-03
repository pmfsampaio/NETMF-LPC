using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using PKStudio.Tree;
using Aga.Controls.Tree;
using PKStudio.Tree.Nodes;

namespace PKStudio.Forms.Explorers
{
    public partial class AssembliesExplorer : InventoryExplorer
    {
        public AssembliesExplorer()
        {
            InitializeComponent();
            PK.Wrapper.LoadFeaturesAsyncCompleteEvent += new EventHandler(OnLoadInventoryComplete);
            _treeView.SetSelectedNodeEvent += new EventHandler<SetSelectedNodeArgs>(_treeView_SetSelectedNodeEvent);
        }

        void _treeView_SetSelectedNodeEvent(object sender, SetSelectedNodeArgs e)
        {
            e.Result = (e.Node.Parent as RootNode != null);
        }

        protected override void OnLoadInventoryComplete(object sender, EventArgs e)
        {
            SetModel(InventoryBrowserModel.AssembliesModel);
        }

    }
}
