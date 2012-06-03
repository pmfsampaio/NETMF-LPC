using System;
using System.Collections.Generic;
using Aga.Controls.Tree;
using PKStudio.Forms.BaseForms;
using PKStudio.ItemWrappers;
using PKStudio.Tree;
using PKStudio.Tree.Nodes;
using System.Windows.Forms;
using Aga.Controls.Tree.NodeControls;

namespace PKStudio.Forms.Explorers
{
    public partial class InventoryExplorer : BasePKInventoryForm
    {
        public InventoryExplorer()
        {
            InitializeComponent();
            _treeView.AddIconControl("Icon");
            _treeView.AddTextBoxControl("Name");
            _treeView.NodeActionEvent += new EventHandler<Tree.NodeEventArgs>(_treeView_NodeActionEvent);
            _treeView.OpenContainingFolderEvent += new EventHandler<PathEventArgs>(_treeView_OpenContainingFolderEvent);
            PK.Wrapper.LoadInventoryAsyncCompleteEvent += new EventHandler(OnLoadInventoryComplete);
       }

        void _treeView_OpenContainingFolderEvent(object sender, PathEventArgs e)
        {
            OnOpenContainingFolderEvent(e.Path);
        }

        void _treeView_NodeActionEvent(object sender, Tree.NodeEventArgs e)
        {
            if (sender is BaseNode)
            {
                OnAction(sender as BaseNode, e.Action);
            }
        }

        protected virtual void OnLoadInventoryComplete(object sender, EventArgs e)
        {
        }

        protected virtual void OnAction(BaseNode node, NodeAction action)
        {
            BaseContentInventoryNode contentNode = node as BaseContentInventoryNode;
            if (contentNode != null)
            {
                this.OnWrapperActionEvent(contentNode.Content, action);
            }
        }

        protected void SetModel(ITreeModel model)
        {
            _treeView.SetModel(model, false);
        }

        private void _treeView_NodeMouseDoubleClick(object sender, TreeNodeAdvMouseEventArgs e)
        {
            if (e.Button == System.Windows.Forms.MouseButtons.Left)
            {
                BaseContentInventoryNode node = e.Node.Tag as BaseContentInventoryNode;
                if (node != null)
                {
                    e.Handled = true;
                    EditNode(node.Content);
                }
            }
        }

        protected void EditNode(BaseWrapper content)
        {
            OnEditEvent(content);
        }

        public void SetSelectedComponent(BuildFileWrapper file)
        {
            _treeView.SetSelectedComponent(file);
        }

        public void SetSelectedComponent(ComponentWrapper component)
        {
            _treeView.SetSelectedComponent(component);
        }

        public void SetSelectedComponent(ComponentWrapper component, BuildFileWrapper file)
        {
            _treeView.SetSelectedComponent(component, file);
        }

        public void SetSelectedComponent(ComponentWrapper Parent, ComponentWrapper component)
        {
            _treeView.SetSelectedComponent(Parent, component);
        }

        private void _treeView_EditEvent(object sender, ObjectEventArgs e)
        {
            OnEditEvent(e.Object);
        }

        private void _treeView_SelectionChangedEvent(object sender, ObjectEventArgs e)
        {
            OnSelectionChangeEvent(e.Object);
        }

        private void _treeView_ShowPropertiesEvent(object sender, ObjectEventArgs e)
        {
            OnShowPropertiesEvent(e.Object);
        }

        private void _treeView_ShowReferencesDiagramEvent(object sender, ObjectEventArgs e)
        {
            OnShowReferencesDiagramEvent(e.Object);
        }

        private void _treeView_MouseDoubleClick(object sender, MouseEventArgs e)
        {

        }
    }
}
