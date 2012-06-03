using System.Collections.Generic;
using System.Windows.Forms;
using PKStudio.TreeNodes;
using System;
using PKStudio.ItemWrappers;
using PKStudio.Tree;

namespace PKStudio.Dialogs
{
    public partial class SelectComponentDialog : Form
    {
        /// <summary>
        /// Libraries filter
        /// </summary>
        public class LibFilter
        {
            public LibFilter()
            {
                this.IsStub = false;
            }
            /// <summary>
            ///Get only IsStub Libraries
            /// </summary>
            public bool IsStub { get; set; }
        }

        ComponentWrapper selectedComponent;

        private LibFilter _libraryFilter;

        public SelectComponentDialog(ComponentTypeWrapper componentType)
        {
            InitializeComponent();
            switch (componentType)
            {
                case ComponentTypeWrapper.Library:
                    break;
                case ComponentTypeWrapper.Feature:
                    break;
                case ComponentTypeWrapper.MFAssembly:
                    break;
                case ComponentTypeWrapper.MFSolution:
                    break;
                case ComponentTypeWrapper.Processor:
                    break;
                case ComponentTypeWrapper.OperatingSystem:
                    break;
                case ComponentTypeWrapper.BuildTool:
                    break;
                case ComponentTypeWrapper.ISA:
                    break;
                case ComponentTypeWrapper.BuildParameter:
                    break;
                case ComponentTypeWrapper.LibraryCategory:
                    break;
                case ComponentTypeWrapper.Unknown:
                    break;
                default:
                    break;
            }
        }

        public SelectComponentDialog(
            bool Library,
            bool Feature,
            bool MFAssembly,
            bool MFSolution,
            bool Processor,
            bool OperatingSystem,
            bool BuildTool,
            bool ISA,
            bool BuildParameter,
            bool LibraryCategory
            )
        {
            InitializeComponent();

            this._libraryFilter = new LibFilter();

            if (Library) TypeCb.Items.Add(ComponentTypeWrapper.Library);
            if (Feature) TypeCb.Items.Add(ComponentTypeWrapper.Feature);
            if (MFAssembly) TypeCb.Items.Add(ComponentTypeWrapper.MFAssembly);
            if (MFSolution) TypeCb.Items.Add(ComponentTypeWrapper.MFSolution);
            if (Processor) TypeCb.Items.Add(ComponentTypeWrapper.Processor);
            if (OperatingSystem) TypeCb.Items.Add(ComponentTypeWrapper.OperatingSystem);
            if (BuildTool) TypeCb.Items.Add(ComponentTypeWrapper.BuildTool);
            if (ISA) TypeCb.Items.Add(ComponentTypeWrapper.ISA);
            if (BuildParameter) TypeCb.Items.Add(ComponentTypeWrapper.BuildParameter);
            if (LibraryCategory) TypeCb.Items.Add(ComponentTypeWrapper.LibraryCategory);

            if (TypeCb.Items.Count != 0)
                TypeCb.SelectedIndex = 0;

            selectedComponent = null;
        }

        public LibFilter LibraryFilter { get { return _libraryFilter; } }

        public ComponentWrapper SelectedComponent
        {
            get { return selectedComponent; }
        }

        public void UpdateDialog()
        {
            switch ((ComponentTypeWrapper)TypeCb.SelectedItem)
            {
                case ComponentTypeWrapper.Library:
                    this.ShowLibraries();
                    break;
                case ComponentTypeWrapper.Feature:
                    this.ShowFeatures();
                    break;
                case ComponentTypeWrapper.MFAssembly:
                    
                    break;
                case ComponentTypeWrapper.MFSolution:
                    break;
                case ComponentTypeWrapper.OperatingSystem:
                    break;
                case ComponentTypeWrapper.BuildTool:
                    break;
                case ComponentTypeWrapper.ISA:
                    this.ShowISAs();
                    break;
                case ComponentTypeWrapper.BuildParameter:
                    break;
                case ComponentTypeWrapper.LibraryCategory:
                    this.ShowLibraryCategories();
                    break;
                case ComponentTypeWrapper.Unknown:
                    break;
                default:
                    break;
            }

            
        }

        private void TypeCb_SelectedIndexChanged(object sender, System.EventArgs e)
        {
            UpdateDialog();
        }

        private void ShowLibraries()
        {
            _treeView.SetModel(InventoryBrowserModel.LibrariesModel, false);

            ////Groups Dictionary
            //SortedDictionary<string, TreeNode> GroupsDict = new SortedDictionary<string, TreeNode>();
            //SortedList<string, TreeNode> VoidGroupsList = new SortedList<string, TreeNode>();


            //treeView1.Nodes.Clear();

            //LibraryWrapper[] libarr = PK.Wrapper.GetLibraries();

            //foreach (LibraryWrapper lib in libarr)
            //{
            //    LibraryWrapper CurrentLib = null;
            //    if (this.LibraryFilter.IsStub)
            //    {
            //        if (lib.IsStub)
            //        {
            //            CurrentLib = lib;
            //        }
            //    }
            //    else CurrentLib = lib;

            //    if (CurrentLib != null)
            //    {
            //        MFTreeNodeBase LibNode = new MFLibraryTreeNode(CurrentLib);//new MFTreeNodeBase(CurrentLib.Name);

            //        if (!string.IsNullOrEmpty(CurrentLib.Groups))
            //        {
            //            if (!GroupsDict.ContainsKey(CurrentLib.Groups))
            //            {
            //                MFTreeNodeBase GroupNode = new MFDirectoryTreeNode(CurrentLib.Groups);//new MFTreeNodeBase(CurrentLib.Groups);
            //                GroupNode.Nodes.Add(LibNode);
            //                GroupsDict.Add(CurrentLib.Groups, GroupNode);
            //            }
            //            else
            //            {
            //                GroupsDict[CurrentLib.Groups].Nodes.Add(LibNode);
            //            }
            //        }
            //        else
            //        {
            //            //LibraryCategoriesNode.Nodes.Add(CatNode);                    
            //            VoidGroupsList.Add(LibNode.Text, LibNode);
            //        }
            //    }
            //}

            //foreach (TreeNode tn in VoidGroupsList.Values)
            //{
            //    treeView1.Nodes.Add(tn);
            //}

            //foreach (TreeNode tn in GroupsDict.Values)
            //{
            //    treeView1.Nodes.Add(tn);
            //}
        }

        private void ShowLibraryCategories()
        {
            _treeView.SetModel(InventoryBrowserModel.LibraryCategoriesModel, false);

            ////Groups dictionary
            //SortedDictionary<string, TreeNode> GroupsDict = new SortedDictionary<string, TreeNode>();
            //SortedList<string, TreeNode> VoidGroupsList = new SortedList<string, TreeNode>();


            //treeView1.Nodes.Clear();

            //LibraryCategoryWrapper[] libcatarr = PK.Wrapper.GetLibraryCategories();

            //foreach (LibraryCategoryWrapper cat in libcatarr)
            //{
            //    MFTreeNodeBase CatNode = new MFLibCatTreeNode(cat);//new MFTreeNodeBase(cat.Name);

            //    if (!string.IsNullOrEmpty(cat.Groups))
            //    {
            //        if (!GroupsDict.ContainsKey(cat.Groups))
            //        {
            //            MFTreeNodeBase GroupNode = new MFDirectoryTreeNode(cat.Groups);//new MFTreeNodeBase(cat.Groups);
            //            GroupNode.Nodes.Add(CatNode);
            //            GroupsDict.Add(cat.Groups, GroupNode);
            //        }
            //        else
            //        {
            //            GroupsDict[cat.Groups].Nodes.Add(CatNode);
            //        }
            //    }
            //    else
            //    {
            //        //LibraryCategoriesNode.Nodes.Add(CatNode);                    
            //        VoidGroupsList.Add(CatNode.Text, CatNode);
            //    }
            //}

            //foreach (TreeNode tn in VoidGroupsList.Values)
            //{
            //    treeView1.Nodes.Add(tn);
            //}

            //foreach (TreeNode tn in GroupsDict.Values)
            //{
            //    treeView1.Nodes.Add(tn);
            //}
        }

        private void ShowFeatures()
        {
            _treeView.SetModel(InventoryBrowserModel.FeaturesModel, false);
            ////Groups dictionary
            //SortedDictionary<string, TreeNode> GroupsDict = new SortedDictionary<string, TreeNode>();
            //SortedList<string, TreeNode> VoidGroupsList = new SortedList<string, TreeNode>();


            //treeView1.Nodes.Clear();

            //FeatureWrapper[] featarr = PK.Wrapper.GetFeatures();

            //foreach (FeatureWrapper feat in featarr)
            //{
            //    MFTreeNodeBase FeatNode = new MFFeatureTreeNode(feat);//new MFTreeNodeBase(feat.Name);

            //    if (!string.IsNullOrEmpty(feat.Groups))
            //    {
            //        if (!GroupsDict.ContainsKey(feat.Groups))
            //        {
            //            MFTreeNodeBase GroupNode = new MFDirectoryTreeNode(feat.Groups);//new MFTreeNodeBase(feat.Groups);
            //            GroupNode.Nodes.Add(FeatNode);
            //            GroupsDict.Add(feat.Groups, GroupNode);
            //        }
            //        else
            //        {
            //            GroupsDict[feat.Groups].Nodes.Add(FeatNode);
            //        }
            //    }
            //    else
            //    {
            //        //LibraryCategoriesNode.Nodes.Add(CatNode);                    
            //        VoidGroupsList.Add(FeatNode.Text, FeatNode);
            //    }
            //}

            //foreach (TreeNode tn in VoidGroupsList.Values)
            //{
            //    treeView1.Nodes.Add(tn);
            //}

            //foreach (TreeNode tn in GroupsDict.Values)
            //{
            //    treeView1.Nodes.Add(tn);
            //}
        }

        private void ShowISAs()
        {
            _treeView.SetModel(InventoryBrowserModel.ISAModel, false);
            //treeView1.Nodes.Clear();

            //ISAWrapper[] isaarr = PK.Wrapper.GetISAs();
            //foreach (ISAWrapper isa in isaarr)
            //{
            //    MFTreeNodeBase ISANode = new MFISATreeNode(isa);//new MFTreeNodeBase(isa.Name);
            //    treeView1.Nodes.Add(ISANode);
            //}
        }


        private void CancelBtn_Click(object sender, System.EventArgs e)
        {
            this.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.Close();
        }

        private void SelectComponent()
        {
            //if (treeView1.SelectedNode != null)
            //{
            //    Type nodeType = treeView1.SelectedNode.GetType();

            //    if (nodeType == typeof(MFLibCatTreeNode))
            //    {
            //        LibraryCategoryWrapper[] lcs = PK.Wrapper.GetLibraryCategories();
            //        foreach (LibraryCategoryWrapper lc in lcs)
            //        {
            //            if (lc.Name == treeView1.SelectedNode.Text)
            //            {
            //                this.selectedComponent = ComponentWrapper.GetComponentWrapper(lc);
            //                this.DialogResult = System.Windows.Forms.DialogResult.OK;
            //                return;
            //            }
            //        }
            //    }
            //    else if (nodeType == typeof(MFLibraryTreeNode))
            //    {
            //        LibraryWrapper[] ls = PK.Wrapper.GetLibraries();
            //        foreach (LibraryWrapper l in ls)
            //        {
            //            if (l.Name == treeView1.SelectedNode.Text)
            //            {
            //                this.selectedComponent = ComponentWrapper.GetComponentWrapper(l);
            //                this.DialogResult = System.Windows.Forms.DialogResult.OK;
            //                return;
            //            }
            //        }
            //    }
            //    else if (nodeType == typeof(MFFeatureTreeNode))
            //    {
            //        FeatureWrapper[] fs = PK.Wrapper.GetFeatures();
            //        foreach (FeatureWrapper f in fs)
            //        {
            //            if (f.Name == treeView1.SelectedNode.Text)
            //            {
            //                this.selectedComponent = ComponentWrapper.GetComponentWrapper(f);
            //                this.DialogResult = System.Windows.Forms.DialogResult.OK;
            //                return;
            //            }
            //        }
            //    }
            //    else if (nodeType == typeof(MFISATreeNode))
            //    {
            //        ISAWrapper[] isas = PK.Wrapper.GetISAs();
            //        foreach (ISAWrapper i in isas)
            //        {
            //            if (i.Name == treeView1.SelectedNode.Text)
            //            {
            //                this.selectedComponent = ComponentWrapper.GetComponentWrapper(i);
            //                this.DialogResult = System.Windows.Forms.DialogResult.OK;
            //                return;
            //            }
            //        }
            //    }

            //}
        }

        private void OkBtn_Click(object sender, System.EventArgs e)
        {
            this.SelectComponent();
            this.Close();
        }

        private void treeView1_AfterSelect(object sender, TreeViewEventArgs e)
        {
            //DescriptionRTB.Clear();
            //if (treeView1.SelectedNode != null)
            //{
            //    Type nodeType = treeView1.SelectedNode.GetType();

            //    if ((nodeType == typeof(MFLibCatTreeNode) ) ||
            //        (nodeType == typeof(MFLibraryTreeNode)) ||
            //        (nodeType == typeof(MFFeatureTreeNode)) ||
            //        (nodeType == typeof(MFISATreeNode)))
                    
            //    {
            //        ShowDescription((ComponentTypeWrapper)TypeCb.SelectedItem);
            //            OkBtn.Enabled = true;
            //    }

            //}
            //else OkBtn.Enabled = false;
        }

        private void ShowDescription(ComponentTypeWrapper type)
        {
            //DescriptionRTB.Clear();

            //switch (type)
            //{
            //    case ComponentTypeWrapper.Library:
            //        LibraryWrapper[] libs = PK.Wrapper.GetLibraries();
            //        foreach (LibraryWrapper l in libs)
            //        {
            //            if (l.Name == treeView1.SelectedNode.Text)
            //            {
            //                DescriptionRTB.AppendText("Name            : " + l.Name + "\r\n");
            //                DescriptionRTB.AppendText("Groups          : " + l.Groups + "\r\n");
            //                DescriptionRTB.AppendText("Description     : " + l.Description + "\r\n");
            //                DescriptionRTB.AppendText("Documentation   : " + l.Documentation + "\r\n");
            //                DescriptionRTB.AppendText("ProjectPath     : " + l.ProjectPath + "\r\n");
            //                DescriptionRTB.AppendText("Guid            : " + l.Guid.ToString() + "\r\n");
            //            }
            //        }
            //        break;
            //    case ComponentTypeWrapper.Feature:
            //        FeatureWrapper[] fs = PK.Wrapper.GetFeatures();
            //        foreach (FeatureWrapper f in fs)
            //        {
            //            if (f.Name == treeView1.SelectedNode.Text)
            //            {
            //                DescriptionRTB.AppendText("Name            : " + f.Name + "\r\n");
            //                DescriptionRTB.AppendText("Groups          : " + f.Groups + "\r\n");
            //                DescriptionRTB.AppendText("Description     : " + f.Description + "\r\n");
            //                DescriptionRTB.AppendText("Documentation   : " + f.Documentation + "\r\n");
            //                DescriptionRTB.AppendText("ProjectPath     : " + f.ProjectPath + "\r\n");
            //                DescriptionRTB.AppendText("Guid            : " + f.Guid.ToString() + "\r\n");
            //            }
            //        }
            //        break;
            //    case ComponentTypeWrapper.MFAssembly:
            //        break;
            //    case ComponentTypeWrapper.MFSolution:
            //        break;
            //    case ComponentTypeWrapper.Processor:
            //        ProcessorWrapper[] procs = PK.Wrapper.GetProcessors();
            //        foreach (ProcessorWrapper p in procs)
            //        {
            //            if (p.Name == treeView1.SelectedNode.Text)
            //            {
            //                DescriptionRTB.AppendText("Name            : " + p.Name + "\r\n");
            //                DescriptionRTB.AppendText("Description     : " + p.Description + "\r\n");
            //                DescriptionRTB.AppendText("Documentation   : " + p.Documentation + "\r\n");
            //                DescriptionRTB.AppendText("ProjectPath     : " + p.ProjectPath + "\r\n");
            //                DescriptionRTB.AppendText("Guid            : " + p.Guid.ToString() + "\r\n");
            //            }
            //        }
            //        break;
            //    case ComponentTypeWrapper.OperatingSystem:
            //        break;
            //    case ComponentTypeWrapper.BuildTool:
            //        break;
            //    case ComponentTypeWrapper.ISA:
            //        ISAWrapper[] isas = PK.Wrapper.GetISAs();
            //        foreach (ISAWrapper i in isas)
            //        {
            //            if (i.Name == treeView1.SelectedNode.Text)
            //            {
            //                DescriptionRTB.AppendText("Name            : " + i.Name + "\r\n");
            //                DescriptionRTB.AppendText("Description     : " + i.Description + "\r\n");
            //                DescriptionRTB.AppendText("Documentation   : " + i.Documentation + "\r\n");
            //                DescriptionRTB.AppendText("Guid            : " + i.Guid.ToString() + "\r\n");
            //            }
            //        }
            //        break;
            //    case ComponentTypeWrapper.BuildParameter:
            //        break;
            //    case ComponentTypeWrapper.LibraryCategory:
            //        LibraryCategoryWrapper[] libCats = PK.Wrapper.GetLibraryCategories();
            //        foreach (LibraryCategoryWrapper lc in libCats)
            //        {
            //            if (lc.Name == treeView1.SelectedNode.Text)
            //            {
            //                DescriptionRTB.AppendText("Name            : " + lc.Name + "\r\n");
            //                DescriptionRTB.AppendText("Groups          : " + lc.Groups + "\r\n");
            //                DescriptionRTB.AppendText("Description     : " + lc.Description + "\r\n");
            //                DescriptionRTB.AppendText("Documentation   : " + lc.Documentation + "\r\n");
            //                DescriptionRTB.AppendText("ProjectPath     : " + lc.ProjectPath + "\r\n");
            //                DescriptionRTB.AppendText("Guid            : " + lc.Guid.ToString() + "\r\n");
            //            }
            //        }
            //        break;
            //    case ComponentTypeWrapper.Unknown:
            //        break;
            //    default:
            //        break;
            //}
        }

        private void treeView1_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            SelectComponent();
            this.Close();
        }
    }
}
