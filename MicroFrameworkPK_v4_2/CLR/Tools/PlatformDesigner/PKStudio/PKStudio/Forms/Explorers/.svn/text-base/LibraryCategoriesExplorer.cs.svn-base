using System;
using System.Collections.Generic;
using System.Windows.Forms;
using PKStudio.TreeNodes;
using PKStudio.ItemWrappers;
using PKStudio.Tree;
using PKStudio.Tree.Nodes;

namespace PKStudio.Forms.Explorers
{
    public partial class LibraryCategoriesExplorer : InventoryExplorer
    {
        public LibraryCategoriesExplorer()
        {
            InitializeComponent();

            PK.Wrapper.LoadLibrariesAsyncCompleteEvent += new EventHandler(OnLoadInventoryComplete);
        }

        protected override void OnLoadInventoryComplete(object sender, EventArgs e)
        {
            SetModel(InventoryBrowserModel.LibraryCategoriesModel);
        }

        protected override void OnAction(BaseNode node, NodeAction action)
        {
            switch (action)
            {
                case NodeAction.New:
                    MessageBox.Show(string.Format("New Library Category with default group \"{0}\"", node.GetRootNodeName<GroupsNode>()));
                    break;
                case NodeAction.Remove:
                    LibraryCategoryNode libcat = node as LibraryCategoryNode;
                    if (libcat != null)
                    {
                        MessageBox.Show(string.Format("Remove Library Category {0} from Inventory", libcat.Name));
                    }
                    break;
                default:
                    base.OnAction(node, action);
                    break;
            }
        }

        //#region helpers

        ///// <summary>
        ///// РЎРѕР·РґР°РµС‚ РЅРѕРІСѓСЋ Library category
        ///// </summary>
        //private void NewLibCat()
        //{
        //    Dialogs.NewLibraryCategoryDialog NLCD = new Dialogs.NewLibraryCategoryDialog();
        //    Type nodeType = this.GetSelectedNode().GetType();
        //    if ((nodeType == typeof(MFDirectoryTreeNode)) ||
        //        (nodeType == typeof(MFRootTreeNode)
        //        ))
        //    {
        //        if (NLCD.ShowDialog(this, this.GetSelectedNode().Text) == System.Windows.Forms.DialogResult.OK)
        //            this.SelectedNodeKey = NLCD.LibraryCategory.Name;
        //    }
        //    else if (nodeType == typeof(MFLibCatTreeNode))
        //    {
        //        if (NLCD.ShowDialog(this, this.GetSelectedNode().Parent.Text) == System.Windows.Forms.DialogResult.OK)
        //            this.SelectedNodeKey = NLCD.LibraryCategory.Name;
        //    }
        //}


        ///// <summary>
        ///// РљР»РѕРЅРёСЂСѓРµС‚ LibraryCategory
        ///// </summary>
        //private void CloneLibCat()
        //{
        //    MFLibCatTreeNode libCatNode = this.GetSelectedNode() as MFLibCatTreeNode;
        //    if (libCatNode != null)
        //    {
        //        Dialogs.NewLibraryCategoryDialog NLCD = new Dialogs.NewLibraryCategoryDialog();
        //        if (NLCD.ShowDialog(this, libCatNode.LibCat) == System.Windows.Forms.DialogResult.OK)
        //            this.SelectedNodeKey = NLCD.LibraryCategory.Name;
        //    }
        //}

        ///// <summary>
        ///// РЈРґР°Р»СЏРµС‚ Library category
        ///// </summary>
        //private void DeleteLibCat()
        //{
        //    Type nodeType = this.GetSelectedNode().GetType();
        //    if (nodeType == typeof(MFLibCatTreeNode))
        //    {
        //        LibraryCategoryWrapper cat = (LibraryCategoryWrapper)this.GetSelectedNode().Tag;
        //        if (MessageBox.Show(this, Strings.DeleteLibraryCategory + " \"" + cat.Name + "\" ?", Strings.Warning + "!", MessageBoxButtons.YesNo, MessageBoxIcon.Warning) == System.Windows.Forms.DialogResult.Yes)
        //        {
        //            PK.Wrapper.DeleteLibraryCategory(cat);
        //            this.SelectedNodeKey = this.GetSelectedNode().Parent.Text;
        //        }
        //    }
        //}

        //#endregion

    }
}
