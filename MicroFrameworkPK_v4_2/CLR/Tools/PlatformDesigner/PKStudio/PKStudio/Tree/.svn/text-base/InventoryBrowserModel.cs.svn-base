#pragma warning disable 67  // Event never used
using System;
using System.Collections;
using System.Collections.Generic;
using Aga.Controls.Tree;
using PKStudio.ItemWrappers;
using PKStudio.Tree.Nodes;
using System.Collections.ObjectModel;
using XsdInventoryFormatObject;
using ComponentObjectModel;

namespace PKStudio.Tree
{
    public class InventoryBrowserModel : ITreeModel
    {

        private static RootNode GetComponentsRoot(InventoryBrowserModel owner, string name, Array items, OnAddItemHandler onAddItem)
        {
            return new RootNode(owner, name, items, onAddItem);
        }

        private static RootNode GetFeaturesRoot(InventoryBrowserModel owner)
        {
            return new RootNode(owner, "Features", PK.Wrapper.GetFeatures());
        }

        private static RootNode GetLibraryCategoriesRoot(InventoryBrowserModel owner)
        {
            return new RootNode(owner, "LibraryCategory", PK.Wrapper.GetLibraryCategories());
        }

        private static RootNode GetLibrariesRoot(InventoryBrowserModel owner)
        {
            return new RootNode(owner, "Libraries", PK.Wrapper.GetLibraries());
        }

        private static RootNode GetProcessorsRoot(InventoryBrowserModel owner)
        {
            return new RootNode(owner, "Processors", PK.Wrapper.GetProcessors(), Resources.Processor);
        }

        private static RootNode GetAssembliesRoot(InventoryBrowserModel owner)
        {
            return new RootNode(owner, "Assemblies", PK.Wrapper.GetAssembies(), Resources.Assembly);
        }

        private static RootNode GetISARoot(InventoryBrowserModel owner)
        {
            return new RootNode(owner, "ISAs", PK.Wrapper.GetISAs());
        }


        public static InventoryBrowserModel GetModel(CollectionWrapper<ComponentDescriptorWrapper, MFComponentDescriptor> components)
        {
            InventoryBrowserModel model = new InventoryBrowserModel();
            foreach (ComponentDescriptorWrapper component in components)
            {
                model.Roots.Add(new ComponentDescriptorNode(component, null));
            }
            return model;
        }

        public static InventoryBrowserModel GetProjectTemplatesModel(Collection<ProjectWrapper> projects)
        {
            InventoryBrowserModel model = new InventoryBrowserModel();
            foreach (ProjectWrapper component in projects)
            {
                model.Roots.Add(new ProjectDescriptorNode(component, null));
            }
            return model;
        }

        public static InventoryBrowserModel GetModel(Array components, OnAddItemHandler onAddItem)
        {
            InventoryBrowserModel model = new InventoryBrowserModel();
            foreach (BaseWrapper component in components)
            {
                if (onAddItem(component))
                    model.Roots.Add(component.GetTreeNode(null));
            }
            return model;
        }

        public static InventoryBrowserModel GetComponentNodeModel<T>(Array components) where T : BaseWrapper
        {
            InventoryBrowserModel model = new InventoryBrowserModel();
            foreach (T component in components)
            {
                model.Roots.Add(new ComponentNode(ComponentWrapper.GetComponentWrapper(component), null));
            }
            return model;
        }

        public static InventoryBrowserModel GetModel(Collection<ComponentNode> components)
        {
            InventoryBrowserModel model = new InventoryBrowserModel();
            foreach (ComponentNode component in components)
            {
                if (component.OnAddItem(component.TypedContent))
                    model.Roots.Add(component);
            }
            return model;
        }

        public static InventoryBrowserModel GetModel(Collection<RootNode> roots)
        {
            InventoryBrowserModel model = new InventoryBrowserModel();
            foreach (RootNode root in roots)
            {
                root.Model = model;
                model.Roots.Add(root);
            }
            return model;
        }

       
        public static InventoryBrowserModel GetModel(CollectionWrapper<ComponentWrapper, MFComponent> components)
        {
            InventoryBrowserModel model = new InventoryBrowserModel();
            foreach (ComponentWrapper component in components)
            {
                model.Roots.Add(new ComponentNode(component, null));
            }
            return model;
        }

        public static InventoryBrowserModel GetModel(ComponentWrapper component)
        {
            InventoryBrowserModel model = new InventoryBrowserModel();
            model.Roots.Add(new ComponentNode(component, null));
            return model;
        }


        public static InventoryBrowserModel GetModel(Array components, OnAddItemHandler onAddItem, string root)
        {
            InventoryBrowserModel model = new InventoryBrowserModel();
            model.Roots.Add(GetComponentsRoot(model, root, components, onAddItem));
            return model;
        }

        public static InventoryBrowserModel SolutionsNamesModel
        {
            get
            {
                return GetModel(PK.Wrapper.GetAvailableSolutions());
            }
        }

        public static InventoryBrowserModel FeaturesModel
        {
            get
            {
                InventoryBrowserModel model = new InventoryBrowserModel();
                model.Roots.Add(GetFeaturesRoot(model));
                return model;
            }
        }

        public static InventoryBrowserModel LibrariesModel
        {
            get
            {
                InventoryBrowserModel model = new InventoryBrowserModel();
                model.Roots.Add(GetLibrariesRoot(model));
                return model;
            }
        }

        public static InventoryBrowserModel LibraryCategoriesModel
        {
            get
            {
                InventoryBrowserModel model = new InventoryBrowserModel();
                model.Roots.Add(GetLibraryCategoriesRoot(model));
                return model;
            }
        }

        public static InventoryBrowserModel ProcessorsModel 
        { 
            get
            {
                InventoryBrowserModel model = new InventoryBrowserModel();
                model.Roots.Add(GetProcessorsRoot(model));
                return model;
            }
        }

        public static InventoryBrowserModel AssembliesModel 
        {
            get
            {
                InventoryBrowserModel model = new InventoryBrowserModel();
                model.Roots.Add(GetAssembliesRoot(model));
                return model;
            }
        }

        public static InventoryBrowserModel ISAModel
        {
            get
            {
                InventoryBrowserModel model = new InventoryBrowserModel();
                model.Roots.Add(GetISARoot(model));
                return model;
            }
        }

        
        private InventoryBrowserModel()
        {
            this.Roots = new List<BaseNode>();
        }

        private List<BaseNode> Roots { get; set; }

        public InventoryBrowserModel(BaseNode root)
            : this(new Collection<BaseNode>() { root })
        {
        }

        public InventoryBrowserModel(Collection<BaseNode> roots)
        {
            this.Roots = new List<BaseNode>(roots);
        }

        public TreePath GetPath(BaseNode item)
        {
            if (item == null)
                return TreePath.Empty;
            else
            {
                Stack<object> stack = new Stack<object>();
                while (item != null)
                {
                    stack.Push(item);
                    item = item.Parent;
                }
                return new TreePath(stack.ToArray());
            }
        }

        #region ITreeModel Members

        public IEnumerable GetChildren(TreePath treePath)
        {
            List<BaseNode> items = null;
            List<string> pathList = new List<string>();
            if (treePath.IsEmpty())
            {
                items = this.Roots;
                foreach (BaseNode item in items)
                {
                    item.Model = this;
                }
            }
            else
            {
                BaseNode parent = treePath.LastNode as BaseNode;
                if (parent != null)
                {
                    Collection<BaseNode> childs = parent.GetChildren(treePath);
                    if (childs != null)
                    {
                        items = new List<BaseNode>(childs);
                        foreach (BaseNode item in items)
                        {
                            item.TreePath = item.TreePath + parent.TreePath;
                        }
                    }
                }
            }
            foreach (BaseNode item in items)
            {
                item.TreePath = item.TreePath + item.Name;
                int repeating = 1;
                while (pathList.Contains(item.TreePath) == true)
                {
                    item.TreePath = string.Format("{0}#{1}", item.TreePath, repeating++);
                }
                pathList.Add(item.TreePath);
            }
            items.Sort(new NodeComparer());
            return items;
        }

        public bool IsLeaf(TreePath treePath)
        {
            BaseNode node = treePath.LastNode as BaseNode;
            if (node != null)
            {
                return node.IsLeaf;
            }
            else
            {
                return false;
            }
        }

        public event EventHandler<TreeModelEventArgs> NodesChanged;

        internal void OnNodesChanged(BaseNode item)
        {
            if (NodesChanged != null)
            {
                TreePath path = GetPath(item.Parent);
                NodesChanged(this, new TreeModelEventArgs(path, new object[] { item }));
            }
        }

        public event EventHandler<TreeModelEventArgs> NodesInserted;

        public event EventHandler<TreeModelEventArgs> NodesRemoved;

        public event EventHandler<TreePathEventArgs> StructureChanged;

        public void OnStructureChanged()
        {
            if (StructureChanged != null)
                StructureChanged(this, new TreePathEventArgs());
        }

        #endregion
    }
}
