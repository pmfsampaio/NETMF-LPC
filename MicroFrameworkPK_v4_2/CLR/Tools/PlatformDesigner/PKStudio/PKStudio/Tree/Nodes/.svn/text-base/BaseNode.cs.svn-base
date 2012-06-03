using PKStudio.ItemWrappers;
using System.Drawing;
using System.Collections;
using Aga.Controls.Tree;
using System;
using System.Collections.Generic;
using System.IO;
using System.Windows.Forms;
using System.ComponentModel;
using System.Diagnostics;
using System.Collections.ObjectModel;
using XsdInventoryFormatObject;

namespace PKStudio.Tree.Nodes
{
    public delegate bool OnAddItemHandler(BaseWrapper item);

    public abstract class BaseNode
    {
        public string Name { get; protected set; }
        [Browsable(false)]
        public BaseNode Parent { get; set; }
        [Browsable(false)]
        public Image Icon { get; protected set; }
        [Browsable(false)]
        public string TreePath { get; set; }
        [Browsable(false)]
        public InventoryBrowserModel Model { get; set; }

        protected static Image GetIcon(ComponentWrapper content)
        {
            Image icon = null;
            switch (content.ComponentType)
            {
                case ComponentTypeWrapper.Library:
                    icon = PKStudio.Tree.Resources.LibraryComponent;
                    break;
                case ComponentTypeWrapper.Feature:
                    icon = PKStudio.Tree.Resources.FeatureComponent;
                    break;
                case ComponentTypeWrapper.MFAssembly:
                    icon = PKStudio.Tree.Resources.Assembly;
                    break;
                case ComponentTypeWrapper.MFSolution:
                    icon = PKStudio.Tree.Resources.Solution;
                    break;
                case ComponentTypeWrapper.Processor:
                    icon = PKStudio.Tree.Resources.Processor;
                    break;
                case ComponentTypeWrapper.LibraryCategory:
                    icon = PKStudio.Tree.Resources.LibraryCategoryComponent;
                    break;
                case ComponentTypeWrapper.Unknown:
                default:
                    if (content.InnerComponentType == typeof(ProjectWrapper))
                        icon = PKStudio.Tree.Resources.Project;
                    else
                        icon = PKStudio.Tree.Resources.unknown;
                    break;
            }
            return icon;
        }

        
        public static readonly OnAddItemHandler OnItemDefault = (x) => true;

        public void OnPropertyChanged(object sender, PropertyChangedEventArgs e)
        {
            this.NotifyModel();
        }

        #region Tool Strip Menu Items

        //private Dictionary<ToolStripMenuItem, BaseNode> menuItems = new Dictionary<ToolStripMenuItem, BaseNode>();

        [Browsable(false)]
        protected BaseNode Root
        {
            get
            {
                BaseNode value = this;
                while (value.Parent != null)
                {
                    Debug.Assert(value.Equals(value.Parent) == false);
                    value = value.Parent;
                }
                return value;
            }
        }

        public string GetRootNodeName<T>() where T : BaseNode
        {
            string name = string.Empty;
            T itemsRoot = this.GetRoot<T>();
            if (itemsRoot != null)
            {
                name = itemsRoot.Name;
            }
            return name;
        }

        public T GetRoot<T>() where T : BaseNode
        {
            BaseNode value = this;
            while (value != null)
            {
                Debug.Assert(value.Equals(value.Parent) == false);
                if (value is T)
                    break;
                value = value.Parent;
            }
            return value as T;
        }

        protected ToolStripMenuItem GetMIViewReferencesDiagram(EventHandler onClick)
        {
            return new NodeToolStripMenuItem(Resources.IDS_TREE_MENU_ITEM_REFERENCES, Resources.References_diagram, onClick, NodeEventArgs.References);
        }
        #endregion


        [Browsable(false)]
        public virtual bool IsLeaf
        {
            get
            {
                return true;
            }
        }

        public abstract Collection<BaseNode> GetChildren(TreePath treePath);

        [Browsable(false)]
        public ToolStripItem[] GetToolStripItems(EventHandler onClick)
        {
            List<ToolStripItem> items = new List<ToolStripItem>();
            if (OnGetToolStripItems(ref items, onClick))
            {
                if (this is BaseContentInventoryNode)
                {
                    items.Add(new ToolStripSeparator());
                    items.Add(NodeToolStripMenuItem.GetMIOpenFilder(onClick));
                }
                items.Add(new ToolStripSeparator());
                items.Add(NodeToolStripMenuItem.GetMIProperties(onClick));
            }
            return items.ToArray();
        }

        public virtual bool OnGetToolStripItems(ref List<ToolStripItem> items, EventHandler onClick)
        {
            return false;
        }

        private InventoryBrowserModel FindModel()
        {
            BaseNode node = this;
            while (node != null)
            {
                if (node.Model != null)
                    return node.Model;
                node = node.Parent;
            }
            return null;
        }

        protected void NotifyModel()
        {
            InventoryBrowserModel model = FindModel();
            if (model != null)
            {
                model.OnNodesChanged(this);
            }
        }

    }

    public abstract class ItemsNode : BaseNode
    {
        [Browsable(false)]
        public OnAddItemHandler OnAddItem { get; set; }

        [Browsable(false)]
        public Array Wrappers { get; set; }

        protected ItemsNode(Array wrappers, OnAddItemHandler onAddItem)
        {
            this.Wrappers = wrappers;
            this.OnAddItem = onAddItem;
        }

        protected ItemsNode(Array wrappers)
            : this(wrappers, OnItemDefault)
        {
            this.Wrappers = wrappers;
        }

        public override Collection<BaseNode> GetChildren(TreePath treePath)
        {
            Collection<BaseNode> items = new Collection<BaseNode>();
            List<string> groups = new List<string>();
            foreach (BaseWrapper item in this.Wrappers)
            {
                if (OnAddItem(item) == false)
                    continue;
                if (item as IGroups != null)
                {
                    string group_name = item.InnerGroups;
                    if (string.IsNullOrEmpty(group_name))
                    {
                        items.Add(item.GetTreeNode(this));
                    }
                    else
                    {
                        group_name = group_name.ToUpperInvariant();
                        if (groups.Contains(group_name) == false)
                        {
                            items.Add(new GroupsNode(item.InnerGroups, this, this.Wrappers));
                            groups.Add(group_name);
                        }
                    }
                }
                else
                {
                   items.Add(item.GetTreeNode(this));
                }
            }
            return items;
        }
        public override bool IsLeaf
        {
            get
            {
                if (this.Wrappers.Length == 0)
                    return base.IsLeaf;
                else
                    return !base.IsLeaf;
            }
        }
    }

    public class NodeComparer : Comparer<BaseNode>
    {
        public override int Compare(BaseNode x, BaseNode y)
        {
            if ((x is FolderNode) && !(y is FolderNode))
                return -1;
            if (!(x is FolderNode) && (y is FolderNode))
                return 1;
            return x.Name.CompareTo(y.Name);
        }
    }

    public class RootNode : ItemsNode
    {

        public RootNode(InventoryBrowserModel owner, string text, Array items, Image icon, OnAddItemHandler onAddItem)
            : base(items, onAddItem)
        {
            this.Name = text;
            this.Icon = icon;
            this.Model = owner;
        }
        
        public RootNode(InventoryBrowserModel owner, string text, Array items, Image icon)
            : this(owner,text, items, icon, ItemsNode.OnItemDefault)
        {
        }

        public RootNode(InventoryBrowserModel owner, string text, Array items, OnAddItemHandler onAddItem)
            : this(owner, text, items, Resources.CompFolder, onAddItem)
        {
        }

        public RootNode(InventoryBrowserModel owner, string text, Array items)
            : this(owner, text, items, Resources.CompFolder)
        {
        }

        public override bool OnGetToolStripItems(ref List<ToolStripItem> items, EventHandler onClick)
        {
            bool ret = base.OnGetToolStripItems(ref items, onClick);
            if (this.Wrappers is FeatureWrapper[])
            {
                items.Add(NodeToolStripMenuItem.GetMIFeatureNew(onClick));
                ret = true;
            }
            if (this.Wrappers is LibraryWrapper[])
            {
                items.Add(NodeToolStripMenuItem.GetMILibraryNew(onClick));
                ret = true;
            }
            if (this.Wrappers is LibraryCategoryWrapper[])
            {
                items.Add(NodeToolStripMenuItem.GetMILibraryCategoryNew(onClick));
                ret = true;
            }
            return ret;
        }

    }

    
    public class FolderNode : ItemsNode
    {
        public FolderNode(string text, BaseNode parent, Array wrappers, Image icon)
            : base(wrappers)
        {
            this.Name = text;
            this.Parent = parent;
            this.Icon = icon;
        }

        public override bool OnGetToolStripItems(ref List<ToolStripItem> items, EventHandler onClick)
        {
            bool ret = base.OnGetToolStripItems(ref items, onClick);
            BaseContentInventoryNode invNode = this.Parent as BaseContentInventoryNode;
            if (invNode != null)
            {
                ret |= invNode.OnGetFolderToolStripItems(ref items, this, onClick);
            }
            return ret;
        }

    }

    public class FileFolderNode : FolderNode
    {
        public string Path { get; set; }

        public FileFolderNode(string text, BaseNode parent, CollectionWrapper<BuildFileWrapper, MFBuildFile> files, string path)
            : base(text, parent, new List<BuildFileWrapper>(files).ToArray(), Resources.Folder)
        {
            this.Path = path;
        }
        public override Collection<BaseNode> GetChildren(TreePath treePath)
        {
            List<BaseNode> items = new List<BaseNode>();
            List<string> filenames = new List<string>();
            foreach (BuildFileWrapper file in this.Wrappers)
            {

                BuildFileNode fileNode = new BuildFileNode(file, this, this.Path);
                if (filenames.Contains(fileNode.TypedContent.FullPath) == false)
                {
                    items.Add(fileNode);
                    filenames.Add(file.FullPath);
                }
            }
            items.Sort(new NodeComparer());
            return new Collection<BaseNode>(items);
        }
        public override bool OnGetToolStripItems(ref List<ToolStripItem> items, EventHandler onClick)
        {
            bool ret = base.OnGetToolStripItems(ref items, onClick);
            items.Add(NodeToolStripMenuItem.GetMIFileNew(onClick));
            ret = true;
            return ret;
        }

    }

    public class GroupsNode : FolderNode
    {
        public GroupsNode(string text, BaseNode parent, Array wrappers)
            : base(text, parent, wrappers, Resources.Folder)
        {
        }

        public override Collection<BaseNode> GetChildren(TreePath treePath)
        {
            List<BaseNode> items = new List<BaseNode>();
            foreach (BaseWrapper item in this.Wrappers)
            {
                if (item is IGroups)
                {
                    if (item.InnerGroups == this.Name)
                        items.Add(item.GetTreeNode(this));
                }
            }
            items.Sort(new NodeComparer());
            return new Collection<BaseNode>(items);
        }
        public override bool OnGetToolStripItems(ref List<ToolStripItem> items, EventHandler onClick)
        {
            bool ret = base.OnGetToolStripItems(ref items, onClick);
            if (this.Parent is ItemsNode)
            {
                ret |= this.Parent.OnGetToolStripItems(ref items, onClick);
            }
            return ret;
        }
    }


    public abstract class BaseContentInventoryNode : BaseNode
    {
        
        [Browsable(false)]
        public bool Checked
        {
            get
            {
                return this.Content.InnerChecked;
            }
            set
            {
                this.Content.InnerChecked = value;
            }
        }

        protected BaseContentInventoryNode(BaseWrapper content)
        {
            this.Content = content;
            this.Content.PropertyChanged+=new PropertyChangedEventHandler(OnPropertyChanged);
        }
        public BaseWrapper Content { get; protected set; }

        public override bool OnGetToolStripItems(ref List<ToolStripItem> items, EventHandler onClick)
        {
            bool ret = base.OnGetToolStripItems(ref items, onClick);
            items.Add(NodeToolStripMenuItem.GetMIEdit(onClick));
            ret = true;
            return ret;
        }
        public virtual bool OnGetFolderToolStripItems(ref List<ToolStripItem> items, ItemsNode node, EventHandler onClick)
        {
            return false;
        }
    }

    public class BaseInventoryNode<T> : BaseContentInventoryNode where T : BaseWrapper
    {

        public T TypedContent
        {
            get
            {
                return this.Content as T;
            }
        }

        public BaseInventoryNode(T content, BaseNode parent, Image icon)
            : base(content)
        {
            this.Parent = parent;
            this.Icon = icon;
            this.Name = content.InnerName;
        }

        public override Collection<BaseNode> GetChildren(TreePath treePath)
        {
            Collection<BaseNode> items = null;
            return items;
        }

        protected Collection<BaseNode> AddFiles(ref List<string> filenames, CollectionWrapper<BuildFileWrapper, MFBuildFile> files, string path)
        {
            List<BaseNode> items = new List<BaseNode>();
            foreach (BuildFileWrapper file in files)
            {
                BuildFileNode fileNode = new BuildFileNode(file, this, path);
                if (filenames.Contains(fileNode.TypedContent.FullPath) == false)
                {
                    items.Add(fileNode);
                    filenames.Add(file.FullPath);
                }
            }
            return new Collection<BaseNode>(items);
        }

        protected string ExpandPath(string path)
        {
            return PK.Wrapper.ExpandPath(path);
        }

        private string ExpandName(string name, string path)
        {
            return PK.Wrapper.ExpandVars(name, path);
        }
  
    }

    public class LibraryNode : BaseInventoryNode<LibraryWrapper>
    {
        public LibraryNode(LibraryWrapper content, BaseNode parent)
            : base(content, parent, Resources.Library)
        {
        }
        public override Collection<BaseNode> GetChildren(TreePath treePath)
        {
            List<BaseNode> items = new List<BaseNode>();
            items.Add(new FileFolderNode("Header Files", this, this.TypedContent.HeaderFiles, this.TypedContent.ProjectPath));
            items.Add(new FileFolderNode("Source Files", this, this.TypedContent.SourceFiles, this.TypedContent.ProjectPath));
            items.Add(new FileFolderNode("Fast Compile Files", this, this.TypedContent.FastCompileFiles, this.TypedContent.ProjectPath));
            //if (this.TypedContent.OtherFiles != null)
            //    items.Add(new FileFolderNode("Other Files", this, this.TypedContent.OtherFiles, this.TypedContent.ProjectPath));
            
            
            //List<string> filenames = new List<string>();
            //items.AddRange(AddFiles(ref filenames, this.TypedContent.HeaderFiles, this.TypedContent.ProjectPath));
            //items.AddRange(AddFiles(ref filenames, this.TypedContent.SourceFiles, this.TypedContent.ProjectPath));
            //items.AddRange(AddFiles(ref filenames, this.TypedContent.FastCompileFiles, this.TypedContent.ProjectPath));
            //items.Sort(new NodeComparer());
            return new Collection<BaseNode>(items);
        }
        public override bool OnGetToolStripItems(ref List<ToolStripItem> items, EventHandler onClick)
        {
            bool ret = base.OnGetToolStripItems(ref items, onClick);
            items.Add(GetMIViewReferencesDiagram(onClick));
            items.Add(NodeToolStripMenuItem.GetMIRemove(onClick));
            ret = true;
            return ret;
        }

        public override bool IsLeaf
        {
            get
            {
                return !base.IsLeaf;
            }
        }
    }

    public class SolutionNode : BaseInventoryNode<SolutionWrapper>
    {
        public SolutionNode(SolutionWrapper content, BaseNode parent)
            : base(content, parent, Resources.Solution)
        {
        }

        public override bool OnGetToolStripItems(ref List<ToolStripItem> items, EventHandler onClick)
        {
            bool ret = base.OnGetToolStripItems(ref items, onClick);
            items.Add(NodeToolStripMenuItem.GetMIProjectNew(onClick));
            items.Add(NodeToolStripMenuItem.GetMIBuild(onClick));
            items.Add(NodeToolStripMenuItem.GetMIRebuild(onClick));
            ret = true;
            return ret;
        }

        public BaseWrapper[] GetLibraries(ProjectWrapper project)
        {
            List<BaseWrapper> libs = new List<BaseWrapper>();
            foreach (ComponentWrapper comp in project.Libraries)
            {
                LibraryWrapper lib = PK.Wrapper.FindLibrary(comp.Guid);
                if (lib != null)
                {
                    bool isReference = !this.TypedContent.IsReference(lib);
                    if (isReference)
                    {
                        libs.Add(lib);
                    }
                }
            }
            return libs.ToArray();
        }


        public override Collection<BaseNode> GetChildren(TreePath treePath)
        {
            Collection<BaseNode> items = new Collection<BaseNode>();
            List<BaseWrapper> libraries = new List<BaseWrapper>();
            foreach (ProjectWrapper project in this.TypedContent.Projects)
            {
                ProjectNode node = new ProjectNode(project, this);
                items.Add(node);
                foreach (BaseWrapper library in this.GetLibraries(project))
                {
                    if (libraries.Contains(library) == false)
                        libraries.Add(library);
                }
            }
            items.Add(new FolderNode("Device Code", this, libraries.ToArray(), Resources.CompFolder));
            items.Add(new FileFolderNode("Header Files", this, this.TypedContent.HeaderFiles, this.TypedContent.ProjectPath));
            return items;
        }
        public override bool IsLeaf
        {
            get
            {
                return !base.IsLeaf;
            }
        }
    }

    public class ProjectDescriptorNode : BaseInventoryNode<ProjectWrapper>
    {
        public ProjectDescriptorNode(ProjectWrapper content, BaseNode parent)
            : base(content, parent, Resources.Project)
        {
        }
    }
    
    public class ProjectNode : BaseInventoryNode<ProjectWrapper>
    {
        public ProjectNode(ProjectWrapper content, BaseNode parent)
            : base(content, parent, Resources.Project)
        {
        }
        public override Collection<BaseNode> GetChildren(TreePath treePath)
        {
            List<BaseNode> items = new List<BaseNode>();
            if (this.TypedContent.IsClrProject)
            {
                items.Add(new FolderNode("Features", this, this.GetFeatures(), Resources.CompFolder));
            }
            //items.Add(new FolderNode("Library Categories", this, this.GetLibraryCategories(), Resources.CompFolder));
            items.Add(new FolderNode("Libraries", this, this.GetLibraries(), Resources.CompFolder));
            items.Add(new FileFolderNode("Source Files", this, this.TypedContent.SourceFiles, this.TypedContent.ProjectPath));
            
            //List<string> filenames = new List<string>();
            
            //items.AddRange(AddFiles(ref filenames, this.TypedContent.SourceFiles, this.TypedContent.ProjectPath));
            
            //items.AddRange(AddFiles(ref filenames, this.TypedContent.OtherFiles, this.TypedContent.ProjectPath));
            //items.Add(new BuildFileNode(this.TypedContent.ScatterFile, this, this.TypedContent.ProjectPath));
            return new Collection<BaseNode>(items);
        }

        private bool GetGenericToolStripItems(ref List<ToolStripItem> items, EventHandler onClick)
        {
            bool ret = true;
            //ToolStripMenuItem add = NodeToolStripMenuItem.GetMISelect(onClick);
            //if (this.TypedContent.IsClrProject)
                //add.DropDownItems.Add(NodeToolStripMenuItem.GetMIFeatureSelect(onClick));
            //add.DropDownItems.Add(NodeToolStripMenuItem.GetMILibrarySelect(onClick));
            //items.Add(add);
            items.Add(NodeToolStripMenuItem.GetMIManage(onClick));
            return ret;
        }

        public override bool OnGetToolStripItems(ref List<ToolStripItem> items, EventHandler onClick)
        {
            bool ret = base.OnGetToolStripItems(ref items, onClick);
            items.Add(NodeToolStripMenuItem.GetMIBuild(onClick));
            items.Add(NodeToolStripMenuItem.GetMIRebuild(onClick));
            ret |= GetGenericToolStripItems(ref items, onClick);
            items.Add(NodeToolStripMenuItem.GetMIRemove(onClick));
            ret = true;
            return ret;
        }

        public override bool OnGetFolderToolStripItems(ref List<ToolStripItem> items, ItemsNode node, EventHandler onClick)
        {
            return GetGenericToolStripItems(ref items, onClick);
        }

        protected BaseWrapper[] GetFeatures()
        {
            List<BaseWrapper> feats = new List<BaseWrapper>();
            foreach (ComponentWrapper comp in this.TypedContent.Features)
            {
                FeatureWrapper feat = PK.Wrapper.FindFeature(comp.Guid);
                if (feat != null)
                {
                    feats.Add(ComponentWrapper.GetComponentWrapper(feat));
                }
            }
            return feats.ToArray();
        }

        protected BaseWrapper[] GetLibraries()
        {
            List<BaseWrapper> libs = new List<BaseWrapper>();
            foreach (ComponentWrapper comp in this.TypedContent.Libraries)
            {
                LibraryWrapper library = PK.Wrapper.FindLibrary(comp.Guid);
                if (library != null)
                {
                    libs.Add(ComponentWrapper.GetComponentWrapper(library));
                }
            }
            return libs.ToArray();
        }

        //protected LibraryCategoryWrapper[] GetLibraryCategories()
        //{
        //    List<LibraryCategoryWrapper> libcats = new List<LibraryCategoryWrapper>();
        //    foreach (ComponentWrapper comp in this.TypedContent.LibraryCategories)
        //    {
        //        LibraryCategoryWrapper libcat = PK.Wrapper.FindLibraryCategory(comp.Guid);
        //        if (libcat != null)
        //        {
        //            libcats.Add(libcat);
        //        }
        //    }
        //    return libcats.ToArray();
        //}

        public override bool IsLeaf
        {
            get
            {
                return !base.IsLeaf;
            }
        }
    }


    public class BuildFileNode : BaseInventoryNode<BuildFileWrapper>
    {
        static Dictionary<string, Image> _images = new Dictionary<string, Image> { 
                { ".cpp".ToUpperInvariant(), Resources.cpp } 
              , { ".c".ToUpperInvariant(), Resources.c } 
              , { ".h".ToUpperInvariant(), Resources.h } 
              , { ".cs".ToUpperInvariant(), Resources.csharp } 
              , { ".s".ToUpperInvariant(), Resources.s } 
        };

        private static Image GetIcon(string file)
        {
            Image image;
            if (!_images.TryGetValue(Path.GetExtension(file).ToUpperInvariant(), out image))
                image = Resources.unknown;
            return image;
        }

        public override bool OnGetToolStripItems(ref List<ToolStripItem> items, EventHandler onClick)
        {
            bool ret = base.OnGetToolStripItems(ref items, onClick);
            items.Add(NodeToolStripMenuItem.GetMIExclude(onClick));
            items.Add(NodeToolStripMenuItem.GetMIRemove(onClick));
            ret = true;
            return ret;
        }

        public BuildFileNode(BuildFileWrapper content, BaseNode parent, string path)
            : base(content, parent, GetIcon(content.File))
        {
            string fullPath = ExpandPath(content.File);
            path = Path.GetDirectoryName(ExpandPath(path));

            if (!File.Exists(fullPath))
            {
                if (Directory.Exists(path))
                    fullPath = Path.GetFullPath(Path.Combine(path, fullPath));
            }
            if (!File.Exists(fullPath))
            {
                this.Icon = Resources.missing;
            }
            this.TypedContent.FullPath = fullPath;

        }
    }

    public class ProcessorNode : BaseInventoryNode<ProcessorWrapper>
    {
        public ProcessorNode(ProcessorWrapper content, BaseNode parent)
            : base(content, parent, Resources.Processor)
        {
        }
        public override Collection<BaseNode> GetChildren(TreePath treePath)
        {
            Collection<BaseNode> items = new Collection<BaseNode>();
            items.Add(new FolderNode("Build Tools", this, new List<BuildToolRefWrapper>(this.TypedContent.BuildToolOptions).ToArray(), Resources.Gears));
            return items;
        }
        public override bool IsLeaf
        {
            get
            {
                return !base.IsLeaf;
            }
        }
    }

    public class LibraryCategoryNode : BaseInventoryNode<LibraryCategoryWrapper>
    {
        public LibraryCategoryNode(LibraryCategoryWrapper content, BaseNode parent)
            : base(content, parent, Resources.LibraryCategory)
        {
        }
        public override bool OnGetToolStripItems(ref List<ToolStripItem> items, EventHandler onClick)
        {
            bool ret = base.OnGetToolStripItems(ref items, onClick);
            items.Add(GetMIViewReferencesDiagram(onClick));
            items.Add(NodeToolStripMenuItem.GetMIRemove(onClick));
            ret = true;
            return ret;
        }
    }

    public class FeatureNode : BaseInventoryNode<FeatureWrapper>
    {
        public FeatureNode(FeatureWrapper content, BaseNode parent)
            : base(content, parent, Resources.Feature)
        {
        }
        public override bool OnGetToolStripItems(ref List<ToolStripItem> items, EventHandler onClick)
        {
            bool ret = base.OnGetToolStripItems(ref items, onClick);
            items.Add(GetMIViewReferencesDiagram(onClick));
            items.Add(NodeToolStripMenuItem.GetMIRemove(onClick));
            ret = true;
            return ret;
        }
    }

    public class BuildToolRefNode : BaseInventoryNode<BuildToolRefWrapper>
    {
        public BuildToolRefNode(BuildToolRefWrapper content, BaseNode parent)
            : base(content, parent, Resources.Gear)
        {
        }
    }

    public class ComponentDescriptorNode : BaseInventoryNode<ComponentDescriptorWrapper>
    {
        public ComponentDescriptorNode(ComponentDescriptorWrapper content, BaseNode parent)
            : base(content, parent, GetIcon(content.Component))
        {
        }
    }

    public class ComponentNode : BaseInventoryNode<ComponentWrapper>
    {
        [Browsable(false)]
        public OnAddItemHandler OnAddItem { get; private set; }


        public ComponentNode(ComponentWrapper content, BaseNode parent)
            : this(content, parent, BaseNode.OnItemDefault)
        {
        }

        public ComponentNode(ComponentWrapper content, BaseNode parent, OnAddItemHandler OnAddItem)
            : base(content, parent, GetIcon(content))
        {
            this.OnAddItem = OnAddItem;
        }
        public override bool OnGetToolStripItems(ref List<ToolStripItem> items, EventHandler onClick)
        {
            bool ret = base.OnGetToolStripItems(ref items, onClick);
            items.Add(GetMIViewReferencesDiagram(onClick));
            ret = true;
            return ret;
        }
    }

    public class ComponentReferencesNode : ComponentNode
    {
        public ReferenceData RefData { get; set; }
        public ComponentReferencesNode(ComponentWrapper content, BaseNode parent, ReferenceInfo RefInfo, OnAddItemHandler OnAddItem)
            : base(content, parent, OnAddItem)
        {
            this.RefData = RefInfo[content];
        }
    }

    public class ComponentRealizationNode : ComponentReferencesNode
    {
        public ComponentRealizationNode(ComponentWrapper content, BaseNode parent, ReferenceInfo RefInfo, OnAddItemHandler OnAddItem)
            : base(content, parent, RefInfo, OnAddItem)
        {
        }

        public override Collection<BaseNode> GetChildren(TreePath treePath)
        {
            Collection<BaseNode> items = new Collection<BaseNode>();
            foreach (ComponentWrapper item in this.RefData.Realization)
            {
                if (this.OnAddItem(item))
                    items.Add(new ComponentNode(item, this));
            }
            return items;
        }

        public override bool IsLeaf
        {
            get
            {
                return (this.RefData.Realization.Count == 0) ? base.IsLeaf : !base.IsLeaf;
            }
        }
    }
    
    public class AssemblyNode : BaseInventoryNode<AssemblyWrapper>
    {
        public AssemblyNode(AssemblyWrapper content, BaseNode parent)
            : base(content, parent, Resources.Assembly)
        {
        }
        public override Collection<BaseNode> GetChildren(TreePath treePath)
        {
            Collection<BaseNode> items = new Collection<BaseNode>();
            items.Add(new FolderNode("References", this, this.GetReferences(), Resources.Folder));
            return items;
        }


        protected AssemblyWrapper[] GetReferences()
        {
            List<AssemblyWrapper> asms = new List<AssemblyWrapper>();
            foreach (ComponentWrapper comp in this.TypedContent.References)
            {
                AssemblyWrapper asmbly = null;
                if (!string.IsNullOrEmpty(comp.Guid))
                {
                    asmbly = PK.Wrapper.FindAssembly(comp.Guid);
                }
                else if (!string.IsNullOrEmpty(comp.Name))
                {
                    asmbly = PK.Wrapper.FindAssemblyByName(comp.Name);
                }
                if (asmbly != null)
                {
                    asms.Add(asmbly);
                }
            }
            return asms.ToArray();
        }

        public override bool IsLeaf
        {
            get
            {
                return !base.IsLeaf;
            }
        }
    }
}
