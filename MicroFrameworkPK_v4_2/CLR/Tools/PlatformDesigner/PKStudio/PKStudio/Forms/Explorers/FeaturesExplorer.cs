using System.Windows.Forms;
using System.Collections.Generic;
using PKStudio.TreeNodes;
using System;
using PKStudio.ItemWrappers;
using PKStudio.Tree;
using System.Collections;
using Aga.Controls.Tree;
using PKStudio.Tree.Nodes;

namespace PKStudio.Forms.Explorers
{
    public partial class FeaturesExplorer : InventoryExplorer
    {
        public FeaturesExplorer()
        {
            InitializeComponent();
            
            PK.Wrapper.LoadFeaturesAsyncCompleteEvent += new EventHandler(OnLoadInventoryComplete);

        }

        protected override void OnLoadInventoryComplete(object sender, EventArgs e)
        {
            SetModel(InventoryBrowserModel.FeaturesModel);
        }


        protected override void OnAction(BaseNode node, NodeAction action)
        {
            switch (action)
            {
                case NodeAction.New:
                    MessageBox.Show(string.Format("New Feature with default group \"{0}\"", node.GetRootNodeName<GroupsNode>()));
                    break;
                case NodeAction.Remove:
                    FeatureNode feature = node as FeatureNode;
                    if (feature != null)
                    {
                        MessageBox.Show(string.Format("Remove Feature {0} from Inventory", feature.Name));
                    }
                    break;
                default:
                    base.OnAction(node, action);
                    break;
            }
        }

    }
}
