using System.Windows.Forms;
using System.Collections.Generic;
using PKStudio.TreeNodes;
using System.Text.RegularExpressions;
using System.IO;
using PKStudio.Forms.BaseForms;
using System;
using PKStudio.ItemWrappers;
using PKStudio.Tree;
using PKStudio.Tree.Nodes;

namespace PKStudio.Forms.Explorers
{
    public partial class LibrariesExplorer : InventoryExplorer
    {

        public LibrariesExplorer()
        {
            InitializeComponent();

            PK.Wrapper.LoadLibrariesAsyncCompleteEvent += new EventHandler(OnLoadInventoryComplete);
            //PK.Wrapper.LoadSolutionAsyncCompleteEvent += new EventHandler<PortingKitWrapper.LoadSolutionAsyncCompletedEventArgs>(Wrapper_LoadSolutionAsyncCompleteEvent);
        }

        //void Wrapper_LoadSolutionAsyncCompleteEvent(object sender, PKStudio.PortingKitWrapper.LoadSolutionAsyncCompletedEventArgs e)
        //{
        //    SetModel(InventoryBrowserModel.LibrariesModel);
        //}

        protected override void OnLoadInventoryComplete(object sender, EventArgs e)
        {
            SetModel(InventoryBrowserModel.LibrariesModel);
        }

        protected override void OnAction(BaseNode node, NodeAction action)
        {
            switch (action)
            {
                case NodeAction.New:
                    FileFolderNode fileFolder = node as FileFolderNode;
                    if (fileFolder != null)
                    {
                        MessageBox.Show(string.Format("New File in group \"{0}\" In Library {1}", fileFolder.Name, fileFolder.GetRoot<LibraryNode>().Name));
                    }
                    else
                    {
                        MessageBox.Show(string.Format("New Library with default group \"{0}\"", node.GetRootNodeName<GroupsNode>()));
                    }
                    break;
                case NodeAction.Exclude:
                case NodeAction.Remove:
                    LibraryNode library = node as LibraryNode;
                    if (library != null)
                    {
                        MessageBox.Show(string.Format("Remove Library {0} from Inventory", library.Name));
                    }
                    BuildFileNode file = node as BuildFileNode;
                    if (file != null)
                    {
                        MessageBox.Show(string.Format("{0} BuildFile {1} from library {2} from group {3}", action, file.Name, file.GetRoot<LibraryNode>().Name, file.GetRoot<FileFolderNode>().Name));
                    }
                    break;
                default:
                    base.OnAction(node, action);
                    break;
            }
        }

         //#region helpers
 
         ///// <summary>
         ///// РЎРѕР·РґР°РµС‚ РЅРѕРІСѓСЋ Library
         ///// </summary>
         //private void NewLib()
         //{
         //    Dialogs.NewLibraryDialog NLD = new Dialogs.NewLibraryDialog();
         //    Type nodeType = this.GetSelectedNode().GetType();
         //    if ((nodeType == typeof(MFRootTreeNode)) || (nodeType == typeof(MFDirectoryTreeNode)))
         //    {
         //        if (NLD.ShowDialog(this, this.GetSelectedNode().Text) == System.Windows.Forms.DialogResult.OK)
         //            this.SelectedNodeKey = NLD.Library.Name;
         //    }
         //    else if (nodeType == typeof(MFLibraryTreeNode))
         //    {
         //        if (NLD.ShowDialog(this, this.GetSelectedNode().Parent.Text) == System.Windows.Forms.DialogResult.OK)
         //            this.SelectedNodeKey = NLD.Library.Name;
         //    }
         //}
 
         ///// <summary>
         ///// РљР»РѕРЅРёСЂСѓРµС‚ Library
         ///// </summary>
         //private void CloneLib()
         //{
         //    Type nodeType = this.GetSelectedNode().GetType();
         //    if (nodeType == typeof(MFLibraryTreeNode))
         //    {
         //        if (this.GetSelectedNode().Tag != null)
         //        {
         //            Dialogs.NewLibraryDialog NLD = new Dialogs.NewLibraryDialog();
         //            if (NLD.ShowDialog(this, (LibraryWrapper)this.GetSelectedNode().Tag) == System.Windows.Forms.DialogResult.OK)
         //                this.SelectedNodeKey = NLD.Library.Name;
         //        }
         //    }
         //}
 
         ///// <summary>
         ///// РЈРґР°Р»СЏРµС‚ Library
         ///// </summary>
         //private void DeleteLib()
         //{
         //    Type nodeType = this.GetSelectedNode().GetType();
         //    if (nodeType == typeof(MFLibraryTreeNode))
         //    {
         //        LibraryWrapper lib = (LibraryWrapper)this.GetSelectedNode().Tag;
         //        if (MessageBox.Show(this, Strings.DeleteLibrary + " \"" + lib.Name + "\" ?", Strings.Warning + "!", MessageBoxButtons.YesNo, MessageBoxIcon.Warning) == System.Windows.Forms.DialogResult.Yes)
         //        {
         //            PK.Wrapper.DeleteLibrary(lib);
         //            this.SelectedNodeKey = this.GetSelectedNode().Parent.Text;
         //        }
         //    }
         //}
 
 
         //#endregion
    }
}
