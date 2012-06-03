using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Aga.Controls.Tree;
using PKStudio.Tree.Nodes;
using PKStudio.ItemWrappers;
using PKStudio.Forms.BaseForms;
using Aga.Controls.Tree.NodeControls;
using System.Collections.ObjectModel;
using System.Collections;
using System.IO;

namespace PKStudio.Tree
{
    public partial class InventoryTree : UserControl, IEventComponent
    {
        public event EventHandler<NodeEventArgs> NodeActionEvent;
        public event EventHandler<SetSelectedNodeArgs> SetSelectedNodeEvent;
        NodeTextBox textControl = null;
        NodeIcon iconControl = null;
        NodeCheckBox checkControl = null;

        public InventoryTree()
        {
            InitializeComponent();
        }

        private void AddNodeControl(string dataPropertyName, BindableControl control)
        {
            control.DataPropertyName = dataPropertyName;
            _treeView.NodeControls.Add(control);
        }

        public NodeTextBox AddTextBoxControl(string dataPropertyName)
        {
            textControl = new NodeTextBox();
            textControl.IncrementalSearchEnabled = true;
            textControl.LeftMargin = 3;
            textControl.ParentColumn = null;
            AddNodeControl(dataPropertyName, textControl);
            return textControl;
        }

        public NodeIcon AddIconControl(string dataPropertyName)
        {
            iconControl = new NodeIcon();
            iconControl.LeftMargin = 1;
            iconControl.ParentColumn = null;
            iconControl.ScaleMode = ImageScaleMode.Clip;
            AddNodeControl(dataPropertyName, iconControl);
            return iconControl;
        }

        public NodeCheckBox AddCheckBoxControl(string dataPropertyName)
        {
            checkControl = new NodeCheckBox();
            checkControl.LeftMargin = 0;
            checkControl.ParentColumn = null;
            checkControl.EditEnabled = true;
            AddNodeControl(dataPropertyName, checkControl);
            return checkControl;
        }

        [Browsable(false)]
        public IEnumerable<BaseNode> AllNodes
        {
            get
            {
                foreach (TreeNodeAdv node in _treeView.AllNodes)
                {
                    yield return node.Tag as BaseNode;
                }
            }
        }

        protected void ExpandRootNode()
        {
            foreach (TreeNodeAdv node in _treeView.AllNodes)
            {
                if ((node.Tag is RootNode) || (node.Tag is SolutionNode))
                    node.Expand();
            }
        }

        [Browsable(false)]
        public TreeNodeAdv TreeSelectedNode
        {
            get
            {
                return _treeView.SelectedNode;
            }
            set
            {
                _treeView.SelectedNode = value;
            }
        }
        
        [Browsable(false)]
        private BaseNode SelectedNode
        {
            get
            {
                if (_treeView.SelectedNode != null)
                    return _treeView.SelectedNode.Tag as BaseNode;
                else
                    return null;
            }
        }

        [Browsable(false)]
        public Collection<NodeControl> NodeControls
        {
            get
            {
                return this._treeView.NodeControls;
            }
        }


        [DefaultValue(true), Category("Behavior")]
        public bool ShowLines
        {
            get
            {
                return this._treeView.ShowLines;
            }
            set
            {
                this._treeView.ShowLines = value;
            }
        }

        [DefaultValue(true), Category("Behavior")]
        public bool ShowPlusMinus
        {
            get
            {
                return this._treeView.ShowPlusMinus;
            }
            set
            {
                this._treeView.ShowPlusMinus = value;
            }
        }


        public BaseWrapper SelectedWrapper
        {
            get
            {
                if (this.SelectedNode != null)
                {
                    BaseContentInventoryNode node = this.SelectedNode as BaseContentInventoryNode;
                    if (node != null)
                        return node.Content;
                }
                return null;
            }
        }

        private object SelectedObject
        {
            get
            {
                if (this.SelectedWrapper != null)
                    return this.SelectedWrapper;
                if (this.SelectedNode != null)
                {
                    return this.SelectedNode;
                }
                return null;
            }
        }

        private bool OnSetSelectedNode(object sender, BaseNode component)
        {
            SetSelectedNodeArgs args = new SetSelectedNodeArgs(component);
            if (this.SetSelectedNodeEvent != null)
            {
                this.SetSelectedNodeEvent(sender, args);
            }
            return args.Result;
        }

        protected TreeNodeAdv FindNode(ComponentWrapper component)
        {
            return this.FindNode(component, _treeView.AllNodes);
        }

        protected TreeNodeAdv FindNode(ComponentWrapper component, IEnumerable<TreeNodeAdv> nodes)
        {
            foreach (TreeNodeAdv node in nodes)
            {
                if (OnSetSelectedNode(this, node.Tag as BaseNode))
                {
                    BaseContentInventoryNode invNode = node.Tag as BaseContentInventoryNode;
                    if (invNode != null)
                    {
                        if (component.IsSameGuid(invNode.Content))
                        {
                            return node;
                        }
                    }
                }
            }
            return null;
        }

        public void SetSelectedComponent(ComponentWrapper component)
        {
            TreeNodeAdv node = this.FindNode(component);
            if (node != null)
            {
                _treeView.SelectedNode = node;
            }
        }

        protected void GetChildrens(TreeNodeAdv node, Collection<TreeNodeAdv> collection)
        {
            foreach (TreeNodeAdv child in node.Children)
            {
                collection.Add(child);
                GetChildrens(child, collection);
            }
        }

        protected IEnumerable<TreeNodeAdv> AllChildren(TreeNodeAdv node)
        {
            Collection<TreeNodeAdv> collection = new Collection<TreeNodeAdv>();
            GetChildrens(node, collection);
            return collection;
        }

        private void SetBuildFile(BuildFileWrapper file, IEnumerable nodes)
        {
            foreach (TreeNodeAdv child in nodes)
            {
                BuildFileNode invNode = child.Tag as BuildFileNode;
                if (invNode != null)
                {
                    if (string.Compare(file.FullPath, invNode.TypedContent.FullPath, true) == 0)
                    {
                        _treeView.SelectedNode = child;
                        break;
                    }
                }
            }
        }
        
        public void SetSelectedComponent(ComponentWrapper component, BuildFileWrapper file)
        {
            TreeNodeAdv node = this.FindNode(component);
            if (node != null)
            {
                this.SetBuildFile(file, AllChildren(node));
            }
        }

        public void SetSelectedComponent(ComponentWrapper parent, ComponentWrapper component)
        {
            TreeNodeAdv node = this.FindNode(parent);
            if (node != null)
            {
                node = this.FindNode(component, AllChildren(node));
                if (node != null)
                {
                    _treeView.SelectedNode = node;
                }
            }
        }

        public void SetSelectedComponent(BuildFileWrapper file)
        {
            this.SetBuildFile(file, _treeView.AllNodes);
        }


        public void SetModel(ITreeModel model, bool expandRoot)
        {
            if (_treeView.Model == null)
                expandRoot = true;
            string selectedTreePath = null;
            Dictionary<string, bool> collapsing = new Dictionary<string, bool>();

            if (this.SelectedNode != null)
                selectedTreePath = this.SelectedNode.TreePath;

            if (expandRoot == false)
            {
                foreach (TreeNodeAdv node in _treeView.AllNodes)
                {
                    BaseNode tag = node.Tag as BaseNode;
                    if (tag != null)
                    {
                        try
                        {
                            if (node.IsLeaf == false)
                                collapsing.Add(tag.TreePath, node.IsExpanded);
                        }
                        catch
                        {
                        }
                    }
                }
            }

            _treeView.Model = model;

            if (expandRoot)
                ExpandRootNode();
            else
            {
                TreeNodeAdv selectedNode = null;
                _treeView.SuspendLayout();
                foreach (TreeNodeAdv node in _treeView.AllNodes)
                {
                    BaseNode tag = node.Tag as BaseNode;
                    if (tag != null)
                    {
                        if (selectedTreePath != null)
                        {
                            if (selectedTreePath == tag.TreePath)
                            {
                                selectedNode = node;
                            }
                        }
                        bool isExpanded;
                        if (collapsing.TryGetValue(tag.TreePath, out isExpanded))
                            node.IsExpanded = isExpanded;
                    }
                }
                if (selectedNode != null)
                    _treeView.SelectedNode = selectedNode;
                else
                    ExpandRootNode();

                _treeView.ResumeLayout();
            }
        }

        private bool AskConfirmDelete(string what)
        {
            return MessageBox.Show(this, string.Format(Resources.IDS_WILL_BE_DELETED_PERMANENTLY, what), string.Empty, MessageBoxButtons.OKCancel, MessageBoxIcon.Warning) == DialogResult.OK;
        }

        private void OnContextMenuClick(object sender, EventArgs e)
        {
            NodeEventArgs arg = e as NodeEventArgs;
            if (arg != null)
            {                
                switch (arg.Action)
                {
                    case NodeAction.Properties:
                        OnShowPropertiesEvent(this.SelectedObject);
                        break;
                    case NodeAction.Edit:
                        OnEditEvent(this.SelectedObject);
                        break;
                    case NodeAction.References:
                        OnShowReferencesDiagramEvent(this.SelectedObject);
                        break;
                    case NodeAction.Remove:
                        if (this.SelectedNode != null)
                        {
                            if (AskConfirmDelete(this.SelectedNode.Name))
                            {
                                OnAction(this.SelectedNode, arg.Action);
                            }
                        }
                        break;
                    case NodeAction.Exclude:
                    case NodeAction.New:
                    case NodeAction.Manage:
                    case NodeAction.Build:
                    case NodeAction.Rebuild:
                        if (this.SelectedNode != null)
                        {
                            OnAction(this.SelectedNode, arg.Action);
                        }
                        break;
                    case NodeAction.OpenFolder:
                        if (this.SelectedWrapper != null)
                        {
                            string path = string.Empty;
                            BaseWrapper wrapper = this.SelectedWrapper;
                            if (wrapper is BuildFileWrapper)
                            {
                                path = (wrapper as BuildFileWrapper).FullPath;
                            }
                            if (wrapper is IProjectPath)
                            {
                                path = PK.Wrapper.ExpandPath((wrapper as IProjectPath).ProjectPath);
                            }
                            if (string.IsNullOrEmpty(path) != true)
                            {
                                OnOpenContainingFolderEvent(path);
                            }
                        }
                        break;
                    default:
                        break;
                }
            }
        }

        protected virtual void OnAction(BaseNode node, NodeAction action)
        {
            if (this.NodeActionEvent != null)
            {
                this.NodeActionEvent(node, new NodeEventArgs(action));
            }
        }

        [Category("Behavior")]
        public override ContextMenuStrip ContextMenuStrip
        {
            get
            {
                return this._treeView.ContextMenuStrip;
            }
            set
            {
                this._treeView.ContextMenuStrip = value;
            }
        }

        [Category("Behavior")]
        public bool LoadOnDemand
        {
            get
            {
                return this._treeView.LoadOnDemand;
            }
            set
            {
                this._treeView.LoadOnDemand = value;
            }
        }

        private void _treeView_SelectionChanged(object sender, EventArgs e)
        {
            if (this.SelectedNode != null)
            {
                if (_treeView.ContextMenuStrip != null)
                {
                    _treeView.ContextMenuStrip.Items.Clear();
                    _treeView.ContextMenuStrip.Items.AddRange(this.SelectedNode.GetToolStripItems(OnContextMenuClick));
                }
            }
            OnSelectionChangeEvent(this.SelectedObject);
        }

        [Category("Behavior")]
        public event EventHandler<TreeNodeAdvMouseEventArgs> NodeMouseDoubleClick
        {
            add
            {
                this._treeView.NodeMouseDoubleClick += value;
            }
            remove
            {
                this._treeView.NodeMouseDoubleClick -= value;
            }
        }



        #region IEventComponent Members

        public event EventHandler<ObjectEventArgs> SelectionChangedEvent;

        public void OnSelectionChangeEvent(object obj)
        {
            if (this.SelectionChangedEvent != null)
            {
                this.SelectionChangedEvent(this, new ObjectEventArgs( obj));
            }
        }

        #endregion

        #region IEventComponent Members


        public event EventHandler<ObjectEventArgs> ShowPropertiesEvent;

        public void OnShowPropertiesEvent(object obj)
        {
            if (this.ShowPropertiesEvent != null)
            {
                this.ShowPropertiesEvent(this, new ObjectEventArgs(obj));
            }
        }

        public event EventHandler<ObjectEventArgs> ShowReferencesDiagramEvent;

        public void OnShowReferencesDiagramEvent(object obj)
        {
            if (this.ShowReferencesDiagramEvent != null)
            {
                this.ShowReferencesDiagramEvent(this, new ObjectEventArgs(obj));
            }
        }

        public event EventHandler<ObjectEventArgs> EditEvent;

        public void OnEditEvent(object obj)
        {
            if (this.EditEvent != null)
            {
                this.EditEvent(this, new ObjectEventArgs(obj));
            }
        }

        public event EventHandler<PathEventArgs> OpenContainingFolderEvent;

        public void OnOpenContainingFolderEvent(string path)
        {
            if (OpenContainingFolderEvent != null)
            {
                OpenContainingFolderEvent(this, new PathEventArgs(path));
            }
        }

        #endregion

        private void _treeView_NodeMouseDoubleClick(object sender, TreeNodeAdvMouseEventArgs e)
        {
            if (e.Button == System.Windows.Forms.MouseButtons.Left)
            {
                OnEditEvent(this.SelectedObject);
            }
        }
    }
    public class SetSelectedNodeArgs : EventArgs
    {
        public bool Result { get; set; }
        public BaseNode Node { get; private set; }
        public SetSelectedNodeArgs(BaseNode Node)
        {
            this.Node = Node;
            this.Result = true;
        }
    }
}
