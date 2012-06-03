using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.IO;
using ComponentObjectModel;
using Microsoft.Build.Evaluation;
using PKStudio.ItemWrappers;
using XsdInventoryFormatObject;
using System.Collections.ObjectModel;

namespace PKStudio
{
    public class PortingKitWrapper : IDisposable
    {
        #region Help types

        public class ElementFindedEventArgs : EventArgs
        {
            public ElementFindedEventArgs(SearchResultsHolder.ComponentDescriptor ComponentDescriptor)
            {
                this.ComponentDescriptor = ComponentDescriptor;
            }
            public SearchResultsHolder.ComponentDescriptor ComponentDescriptor { get; set; }
        }

        public class SearchComplitedEventArgs : EventArgs
        {
            public SearchComplitedEventArgs(SearchResultsHolder SearchResults)
            {
                this.SearchResults = SearchResults;
            }
            public SearchResultsHolder SearchResults { get; set; }
        }

        public class SearchStartedEventArgs : EventArgs
        {
            public SearchStartedEventArgs(SearchParams SearchParams)
            {
                this.SearchParams = SearchParams;
            }
            public SearchParams SearchParams { get; set; }
        }

        public class LoadSolutionAsyncCompletedEventArgs : EventArgs
        {
            public LoadSolutionAsyncCompletedEventArgs(SolutionWrapper Solution)
            {
                this.Solution = Solution;
            }
            public SolutionWrapper Solution { get; set; }
        }

        private enum BackgroundWorkerType
        {
            LoadFeatures,
            LoadDefaultFeatures,
            LoadSolutions,
            LoadSolution,
            LoadProjects,
            LoadDefaultLibraries,
            LoadLibraries,
            LoadDefaultLibraryCategories,
            LoadProcessors,
            LoadAll,
            LoadInventory,
        }

        public enum SearchType
        {
            AllComponents,
            Libraries,
            LibraryCategories,
            Features,
            Files,
            TextInFiles,
        }

        public enum SearchWhere
        {
            All,
            PKDatabase,
            Solution
        }

        public class SearchParams
        {
            public SearchParams(SearchType type, SearchWhere where, string what, bool MatchCase, bool MatchWholeWord)
            {
                this.Type = type;
                this.Where = where;
                this.What = what;
                this.MatchCase = MatchCase;
                this.MatchWholeWord = MatchWholeWord;
            }
            public SearchType Type { get; set; }
            public SearchWhere Where { get; set; }
            public string What { get; set; }
            public bool MatchCase { get; set; }
            public bool MatchWholeWord { get; set; }
        }

        public class SearchResultsHolder
        {
            public class ComponentDescriptor
            {
                public class LineDescriptor
                {
                    public LineDescriptor(int Num, string Text)
                    {
                        this.Num = Num;
                        this.Text = Text;
                    }
                    public int Num { get; set; }
                    public string Text { get; set; }
                }
                public ComponentDescriptor()
                {
                    this.Parent = null;
                    this.Component = null;
                    this.File = null;
                    this.Line = null;
                }

                public ComponentDescriptor(ComponentWrapper Component)
                {
                    this.Parent = null;
                    this.Component = Component;
                    this.File = null;
                    this.Line = null;
                }

                public ComponentDescriptor(BuildFileWrapper File)
                {
                    this.Parent = null;
                    this.Component = null;
                    this.File = File;
                    this.Line = null;
                }

                public ComponentDescriptor(ComponentDescriptor Parent, ComponentWrapper Component)
                {
                    this.Parent = Parent;
                    this.Component = Component;
                    this.File = null;
                    this.Line = null;
                }
                public ComponentDescriptor(ComponentDescriptor Parent, BuildFileWrapper File)
                {
                    this.Parent = Parent;
                    this.Component = null;
                    this.File = File;
                    this.Line = null;
                }

                public ComponentDescriptor(ComponentDescriptor Parent, BuildFileWrapper File, LineDescriptor Line)
                {
                    this.Parent = Parent;
                    this.Component = null;
                    this.File = File;
                    this.Line = Line;
                }

                public ComponentDescriptor Parent { get; set; }
                public ComponentWrapper Component { get; set; }
                public BuildFileWrapper File { get; set; }
                public LineDescriptor Line { get; set; }
            }

            public SearchResultsHolder()
            {
                FindedComponents = new List<ComponentDescriptor>();
            }
            public List<ComponentDescriptor> FindedComponents { get; set; }

            /// <summary>
            /// Всего просмотрено компонентов
            /// </summary>
            public int TotalComponentsSearched { get; set; }

            public SearchParams SearchParams { get; set; }
        }

        //public class BuildFileDescriptor
        //{
        //    public BuildFileDescriptor()
        //    {
        //        this.File = null;
        //        this.Parent = null;
        //    }
        //    public BuildFileDescriptor(BuildFileWrapper File, ComponentWrapper Parent)
        //    {
        //        this.File = File;
        //        this.Parent = Parent;
        //    }
        //    public BuildFileWrapper File { get; set; }
        //    public ComponentWrapper Parent { get; set; }
        //}

        #endregion

        #region fields
        private InventoryWrapper m_inv;
        private InventoryHelperWrapper m_helper;
        private MsBuildWrapper m_bw;

        private string m_spoClientPath;

        private ComponentDescriptorWrapper m_selectedSolution;
        private SolutionWrapper m_solution;

        private BackgroundWorker m_worker;
        private BackgroundWorker m_SearchWorker;

        private SearchResultsHolder m_SearchResults = new SearchResultsHolder();

        #endregion


        public PortingKitWrapper()
        {
            this.m_inv = new InventoryWrapper(new Inventory());
            this.m_helper = new InventoryHelperWrapper(new InventoryHelperWrapper(new InventoryWrapper[] { this.m_inv }));
            this.m_bw = new MsBuildWrapper(this.m_inv.InnerObject);

            this.m_spoClientPath = "";

            this.m_worker = new BackgroundWorker();
            this.m_worker.DoWork += new DoWorkEventHandler(m_worker_DoWork);
            this.m_worker.RunWorkerCompleted += new RunWorkerCompletedEventHandler(m_worker_RunWorkerCompleted);
            this.m_worker.WorkerReportsProgress = true;

            this.m_SearchWorker = new BackgroundWorker();
            this.m_SearchWorker.DoWork += new DoWorkEventHandler(m_SearchWorker_DoWork);
            this.m_SearchWorker.RunWorkerCompleted += new RunWorkerCompletedEventHandler(m_SearchWorker_RunWorkerCompleted);
            this.m_SearchWorker.WorkerReportsProgress = true;
        }


        #region BackgroundWorker

        void m_worker_DoWork(object sender, DoWorkEventArgs e)
        {
            lock (this.m_bw)
            {
                switch (((BackgroundWorkerType)e.Argument))
                {
                    //Load inventory without solutions
                    case BackgroundWorkerType.LoadInventory:
                        m_worker.ReportProgress(0, "Load Default Build Targets...");
                        this.m_bw.LoadDefaultBuildTargets(this.m_spoClientPath);
                        m_worker.ReportProgress(10, "Load Default Processors...");
                        this.m_bw.LoadDefaultProcessors(this.m_spoClientPath);
                        m_worker.ReportProgress(20, "Load Default Library Categories...");
                        this.m_bw.LoadDefaultLibraryCategories(this.m_spoClientPath);
                        m_worker.ReportProgress(30, "Load Default Libraries...");
                        this.m_bw.LoadDefaultLibraries(this.m_spoClientPath);
                        m_worker.ReportProgress(60, "Load Default Assemblies...");
                        this.m_bw.LoadDefaultAssemblies(this.m_spoClientPath);
                        m_worker.ReportProgress(70, "Load Default Features...");
                        this.m_bw.LoadDefaultFeatures(this.m_spoClientPath);

                        //m_worker.ReportProgress(80, "Load Solutions...");
                        //this.m_bw.LoadSolutions(Path.Combine(this.m_spoClientPath, "Solutions"));
                        break;
                    case BackgroundWorkerType.LoadDefaultLibraryCategories:
                        this.m_helper.DefaultInventory.LibraryCategories.Clear();
                        m_worker.ReportProgress(0, "Load Default Library Categories...");
                        m_bw.LoadDefaultLibraryCategories(this.m_spoClientPath);
                        break;
                    case BackgroundWorkerType.LoadDefaultFeatures:
                        this.m_helper.DefaultInventory.Features.Clear();
                        m_worker.ReportProgress(0, "Load Default Features...");
                        m_bw.LoadDefaultFeatures(this.m_spoClientPath);
                        break;
                    case BackgroundWorkerType.LoadDefaultLibraries:
                        this.m_helper.DefaultInventory.Libraries.Clear();
                        m_worker.ReportProgress(40, "Load Default Libraries...");
                        this.m_bw.LoadDefaultLibraries(this.m_spoClientPath);
                        if (this.m_solution != null)
                        {
                            m_worker.ReportProgress(30, "Load Solution Libraries...");
                            this.m_bw.LoadLibraries(this.m_solution.ProjectPath);
                        }
                        break;

                    case BackgroundWorkerType.LoadSolution:
                        m_worker.ReportProgress(0, "Load Solution Proj...");
                        this.m_solution = BaseWrapper.Wrap<SolutionWrapper>(this.m_bw.LoadSolutionProj(this.m_selectedSolution.Component.ProjectPath, ""));
                        m_worker.ReportProgress(30, "Load Libraries...");
                        this.m_bw.LoadLibraries(this.m_solution.ProjectPath);
                        m_worker.ReportProgress(60, "Load Default Library Categories...");
                        this.m_bw.LoadDefaultLibraryCategories(this.m_spoClientPath);
                        this.SetSolutionTransportType(this.m_solution);
                        break;


                    //case BackgroundWorkerType.LoadFeatures:
                    //    m_worker.ReportProgress(0, "Load Features...");
                    //    if ((this.m_solution == null) && (this.m_selectedSolution != null))
                    //    {
                    //        m_worker.ReportProgress(10, "Load Solution Proj...");
                    //        this.m_solution = this.m_bw.LoadSolutionProj(this.m_selectedSolution.Component.ProjectPath, "");
                    //    }
                    //    if (Helper.IsWindowsSolution(this.m_solution))
                    //    {
                    //        m_worker.ReportProgress(30, "Load Default Libraries...");
                    //        this.m_bw.LoadDefaultLibraries(this.m_spoClientPath);
                    //        m_worker.ReportProgress(40, "Load Default Library Categories...");
                    //        this.m_bw.LoadDefaultLibraryCategories(this.m_spoClientPath);
                    //        m_worker.ReportProgress(50, "Load Default Manifest Files...");
                    //        this.m_bw.LoadDefaultManifestFiles(this.m_spoClientPath);
                    //    }
                    //    m_worker.ReportProgress(80, "Load Default Features...");
                    //    this.m_bw.LoadDefaultFeatures(this.m_spoClientPath);
                    //    break;

                    //case BackgroundWorkerType.LoadSolution:
                    //    m_worker.ReportProgress(0, "Load Solution Proj...");
                    //    this.m_solution = this.m_bw.LoadSolutionProj(this.m_selectedSolution.Component.ProjectPath, "");
                    //    m_worker.ReportProgress(30, "Load Libraries...");
                    //    this.m_bw.LoadLibraries(this.m_solution.ProjectPath);
                    //    m_worker.ReportProgress(60, "Load Default Library Categories...");
                    //    this.m_bw.LoadDefaultLibraryCategories(this.m_spoClientPath);
                    //    break;

                    //case BackgroundWorkerType.LoadProjects:
                    //    if (this.m_inv.ProjectTemplates.Count == 0)
                    //    {
                    //        m_worker.ReportProgress(0, "Load Template Projects...");
                    //        this.m_bw.LoadTemplateProjects(this.m_spoClientPath + @"\ProjectTemplates");
                    //    }
                    //    break;

                    //case BackgroundWorkerType.LoadLibraries:
                    //    m_worker.ReportProgress(0, "Load Default Libraries...");
                    //    this.m_bw.LoadDefaultLibraries(this.m_spoClientPath);
                    //    m_worker.ReportProgress(20, "Load Default Manifest Files...");
                    //    this.m_bw.LoadDefaultManifestFiles(this.m_spoClientPath);
                    //    m_worker.ReportProgress(40, "Load Default Library Categories...");
                    //    this.m_bw.LoadDefaultLibraryCategories(this.m_spoClientPath);
                    //    m_worker.ReportProgress(80, "Load Default Features...");
                    //    this.m_bw.LoadDefaultFeatures(this.m_spoClientPath);
                    //    break;

                    //case BackgroundWorkerType.LoadProcessors:
                    //    m_worker.ReportProgress(0, "Load Processors...");
                    //    this.m_bw.LoadProcessors(this.m_spoClientPath + @"\DeviceCode\Targets\Native");
                    //    this.m_bw.LoadProcessors(this.m_spoClientPath + @"\DeviceCode\Targets\OS");
                    //    break;

                    //case BackgroundWorkerType.LoadAll:
                    //    m_worker.ReportProgress(0, "Load Default Build Targets...");
                    //    this.m_bw.LoadDefaultBuildTargets(this.m_spoClientPath);
                    //    m_worker.ReportProgress(20, "Load Default Processors...");
                    //    this.m_bw.LoadDefaultProcessors(this.m_spoClientPath);
                    //    m_worker.ReportProgress(30, "Load Default Library Categories...");
                    //    this.m_bw.LoadDefaultLibraryCategories(this.m_spoClientPath);
                    //    m_worker.ReportProgress(40, "Load Default Libraries...");
                    //    this.m_bw.LoadDefaultLibraries(this.m_spoClientPath);
                    //    m_worker.ReportProgress(50, "Load Default Assemblies...");
                    //    this.m_bw.LoadDefaultAssemblies(this.m_spoClientPath);
                    //    m_worker.ReportProgress(60, "Load Default Features...");
                    //    this.m_bw.LoadDefaultFeatures(this.m_spoClientPath);
                    //    //m_worker.ReportProgress(80, "Load Solutions...");
                    //    //this.m_bw.LoadSolutions(this.m_spoClientPath + @"\Solutions");
                    //    break;
                }
            }
            e.Result = e.Argument;
            m_worker.ReportProgress(100, "Ready");
        }

        void m_worker_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            switch (((BackgroundWorkerType)e.Result))
            {
                case BackgroundWorkerType.LoadInventory:
                    OnLoadInventoryComplete();
                    break;
                case BackgroundWorkerType.LoadDefaultLibraryCategories:
                    OnLoadLibraryCategoriesComplete();
                    break;
                case BackgroundWorkerType.LoadDefaultFeatures:
                    OnLoadFeaturesComplete();
                    break;
                case BackgroundWorkerType.LoadDefaultLibraries:
                    OnLoadLibraryesComplete();
                    break;
                case BackgroundWorkerType.LoadSolutions:
                    OnLoadSolutionsComplete();
                    break;
                case BackgroundWorkerType.LoadSolution:
                    OnLoadSolutionComplete();
                    break;
                //case BackgroundWorkerType.LoadFeatures:
                //    break;
                //case BackgroundWorkerType.LoadSolutions:
                //    Dialogs.OpenSolutionForm os = new Dialogs.OpenSolutionForm(m_solutionRefs);
                //    if (os.ShowDialog(this) == System.Windows.Forms.DialogResult.OK)
                //    {
                //        m_selectedSolution = os.selectedSolution;
                //        this.m_worker.RunWorkerAsync(BackgroundWorkerType.LoadSolution);
                //    }
                //    break;
                //case BackgroundWorkerType.LoadSolution:
                //    mSolutionTree.UpdateTree(m_solution);
                //    mSolutionTree.Show(dockPanel1, DockState.DockLeft);
                //    break;
                //case BackgroundWorkerType.LoadProjects:
                //    break;
                //case BackgroundWorkerType.LoadLibraries:
                //    break;
                //case BackgroundWorkerType.LoadProcessors:
                //    break;
                //case BackgroundWorkerType.LoadAll:
                //    mInventoryTree.UpdateTree();
                //    mInventoryTree.Show(dockPanel1, DockState.DockLeft);

                //    mLibraryCategoriesExplorer.UpdateTree();
                //    mLibraryCategoriesExplorer.Show(dockPanel1, DockState.DockLeft);
                //    break;
                default:
                    break;
            }
        }

        void m_SearchWorker_DoWork(object sender, DoWorkEventArgs e)
        {
            SearchParams pars = (SearchParams)e.Argument;

            OnSearchStarted(pars);

            m_SearchResults.FindedComponents.Clear();
            m_SearchResults.TotalComponentsSearched = 0;
            m_SearchResults.SearchParams = pars;

            m_SearchWorker.ReportProgress(0, "Search started");

            switch (pars.Type)
            {
                case SearchType.AllComponents:
                    SearchInLibraries(pars.Where, pars.What, pars.MatchCase, pars.MatchWholeWord);
                    SearchInLibraryCategories(pars.Where, pars.What, pars.MatchCase, pars.MatchWholeWord);
                    SearchInFeatures(pars.Where, pars.What, pars.MatchCase, pars.MatchWholeWord);
                    SearchFiles(pars.Where, pars.What, pars.MatchCase, pars.MatchWholeWord);
                    break;
                case SearchType.Libraries:
                    SearchInLibraries(pars.Where, pars.What, pars.MatchCase, pars.MatchWholeWord);
                    break;
                case SearchType.LibraryCategories:
                    SearchInLibraryCategories(pars.Where, pars.What, pars.MatchCase, pars.MatchWholeWord);
                    break;
                case SearchType.Features:
                    SearchInFeatures(pars.Where, pars.What, pars.MatchCase, pars.MatchWholeWord);
                    break;
                case SearchType.Files:
                    SearchFiles(pars.Where, pars.What, pars.MatchCase, pars.MatchWholeWord);
                    break;
                case SearchType.TextInFiles:
                    SearchTextInFiles(pars.Where, pars.What, pars.MatchCase, pars.MatchWholeWord);
                    break;
                default:
                    break;
            }
            //m_SearchWorker.ReportProgress(100, "Search finished");
        }

        void m_SearchWorker_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            OnSearchComplited(this.m_SearchResults);
        }

        #endregion

        #region Properties

        /// <summary>
        /// Porting Kit Path
        /// </summary>
        public string SpoClientPath
        {
            get { return m_spoClientPath; }
            set { m_spoClientPath = value; }
        }

        public SolutionWrapper Solution { get { return this.m_solution; } }

        public SearchResultsHolder SearchResults { get { return this.m_SearchResults; } }

        #endregion

        #region Metods

        #region AsyncLoad
        /// <summary>
        /// Async loading of Inventory
        /// </summary>
        public void LoadInventoryAsync()
        {
            this.m_worker.RunWorkerAsync(BackgroundWorkerType.LoadInventory);
        }

        /// <summary>
        /// Async loading of default Library Catigories
        /// </summary>
        public void LoadDefaultLibraryCatigoriesAsync()
        {
            this.m_worker.RunWorkerAsync(BackgroundWorkerType.LoadDefaultLibraryCategories);
        }

        /// <summary>
        /// Async loading of default Features
        /// </summary>
        public void LoadDefaultFeaturesAsync()
        {
            this.m_worker.RunWorkerAsync(BackgroundWorkerType.LoadDefaultFeatures);
        }

        /// <summary>
        /// Async loading of default Libraries
        /// </summary>
        public void LoadDefaultLibrariesAsync()
        {
            this.m_worker.RunWorkerAsync(BackgroundWorkerType.LoadDefaultLibraries);
        }

        /// <summary>
        /// Async loading of all Solutions
        /// </summary>
        public void LoadSolutionsAsync()
        {
            this.m_worker.RunWorkerAsync(BackgroundWorkerType.LoadSolutions);
        }

        /// <summary>
        /// Async loading of Solution
        /// </summary>
        public void LoadSolutionAsync(ComponentDescriptorWrapper selectedsolution)
        {
            this.m_selectedSolution = selectedsolution;
            this.m_worker.RunWorkerAsync(BackgroundWorkerType.LoadSolution);
        }

        #endregion

        #region SyncLoad
        /// <summary>
        /// Sync loading of inventory
        /// </summary>
        public void LoadInventory()
        {
            this.m_bw.LoadDefaultBuildTargets(this.m_spoClientPath);
            this.m_bw.LoadDefaultProcessors(this.m_spoClientPath);
            this.m_bw.LoadDefaultLibraryCategories(this.m_spoClientPath);
            this.m_bw.LoadDefaultLibraries(this.m_spoClientPath);
            this.m_bw.LoadDefaultAssemblies(this.m_spoClientPath);
            this.m_bw.LoadDefaultFeatures(this.m_spoClientPath);
        }

        /// <summary>
        /// Sync loading of default Library Catigories
        /// </summary>
        public LibraryCategoryWrapper[] LoadDefaultLibraryCatigories()
        {
            this.m_bw.LoadDefaultLibraryCategories(this.m_spoClientPath);
            return m_helper.LibraryCategories;
        }

        /// <summary>
        /// Sync loading of default Features
        /// </summary>
        public FeatureWrapper[] LoadDefaultFeatures()
        {
            this.m_bw.LoadDefaultFeatures(this.m_spoClientPath);
            return m_helper.Features;
        }

        /// <summary>
        /// Sync loading of default Libraries
        /// </summary>
        public LibraryWrapper[] LoadDefaultLibraries()
        {
            this.m_bw.LoadDefaultLibraries(this.m_spoClientPath);
            return m_helper.Libraries;
        }

        public CollectionWrapper<ComponentDescriptorWrapper, MFComponentDescriptor> GetAvailableSolutions()
        {
            return BaseWrapper.WrapList<ComponentDescriptorWrapper, MFComponentDescriptor>(this.m_bw.GetAvailableSolutions(this.m_spoClientPath));
        }

        public List<ProjectWrapper> LoadTemplateProjects()
        {
            this.m_bw.LoadTemplateProjects(this.m_spoClientPath + @"\ProjectTemplates");
            return new List<ProjectWrapper>(this.m_inv.ProjectTemplates);
        }

        /// <summary>
        /// Sync loading of Solution
        /// </summary>
        public SolutionWrapper LoadSolution(ComponentDescriptorWrapper selectedsolution)
        {
            this.m_selectedSolution = selectedsolution;
            this.m_solution = BaseWrapper.Wrap<SolutionWrapper>(this.m_bw.LoadSolutionProj(this.m_selectedSolution.Component.ProjectPath, ""));
            this.m_bw.LoadLibraries(this.m_solution.ProjectPath);
            this.m_bw.LoadDefaultLibraryCategories(this.m_spoClientPath);
            this.SetSolutionTransportType(this.m_solution);
            return this.m_solution;
        }

        #endregion

        #region Features

        public FeatureWrapper[] GetFeatures()
        {
            return m_helper.Features;
        }

        public FeatureWrapper[] GetRequiredFeatures()
        {
            return m_helper.GetRequiredFeatures();
        }

        public FeatureWrapper FindFeature(string featureGuid)
        {
            return m_helper.FindFeature(featureGuid);
        }

        public FeatureWrapper FindFeatureByName(string name)
        {
            return m_helper.FindFeatureByName(name);
        }

        public FeatureWrapper FindFeatureByProject(string featProject)
        {
            return m_helper.FindFeatureByProject(featProject);
        }

        public void SaveFeatureProj(Feature feat)
        {
            m_bw.SaveFeatureProj(feat);
            this.m_helper.DefaultInventory.Features.Clear();
            this.LoadDefaultFeaturesAsync();
        }

        #endregion

        #region Library Category

        /// <summary>
        /// Checks Library Category name for uniqueness
        /// </summary>
        /// <param name="name"></param>
        /// <returns>True - if name is unique, else - false</returns>
        public bool CheckLibraryCategoryName(string name)
        {
            bool res = true;
            foreach (LibraryCategoryWrapper libcat in m_helper.LibraryCategories)
            {
                if (libcat.Name == name) res = false;
            }
            return res;
        }

        /// <summary>
        /// Generates Library Category new unique library name based on BaseName
        /// </summary>
        /// <param name="BaseName">Base name for generation</param>
        /// <returns>Result name</returns>
        public string GenerateNewLibraryCategoryName(string BaseName)
        {
            string defaultName = "";
            string currentName = "";
            string suffix = "";
            string resultName = "";

            if (BaseName.Contains("_HAL"))
            {
                defaultName = BaseName.Replace("_HAL", "");
                currentName = BaseName;
                suffix = "_HAL";
            }
            else if (BaseName.Contains("_PAL"))
            {
                defaultName = BaseName.Replace("_PAL", "");
                currentName = BaseName;
                suffix = "_PAL";
            }
            else if (BaseName.Contains("_CLR"))
            {
                defaultName = BaseName.Replace("_CLR", "");
                currentName = BaseName;
                suffix = "_CLR";
            }
            else if (BaseName.Contains("_Support"))
            {
                defaultName = BaseName.Replace("_Support", "");
                currentName = BaseName;
                suffix = "_Support";
            }
            else
            {
                defaultName = BaseName;
                currentName = BaseName;
                suffix = "";
            }

            if (char.IsDigit(defaultName, defaultName.Length - 1))
            {
                defaultName = defaultName.Remove(defaultName.Length - 1);
            }

            int i = 1;
            resultName = defaultName;

            while (this.CheckLibraryCategoryName(currentName))
            {
                resultName = defaultName + i.ToString();
                currentName = resultName + suffix;
                i++;
            }
            return resultName;
        }

        public LibraryCategoryWrapper[] GetLibraryCategories()
        {
            return m_helper.LibraryCategories;
        }

        public List<LibraryCategoryWrapper> GetTransports()
        {
            return m_helper.GetTransports();
        }

        public LibraryCategoryWrapper FindLibraryCategory(string LibraryCategoryGuid)
        {
            return m_helper.FindLibraryCategory(LibraryCategoryGuid);
        }

        public LibraryCategoryWrapper FindLibraryCategoryByName(string LibraryCategoryName)
        {
            return m_helper.FindLibraryCategoryByName(LibraryCategoryName);
        }

        public LibraryCategoryWrapper CloneLibraryCategory(BaseTypedWrapper<LibraryCategory> BaseLibCat, string NewName, string NewGroups, LibraryLevelWrapper NewLevel)
        {
            LibraryCategory LibCat = new LibraryCategory();
            BaseLibCat.InnerObject.CopyTo(LibCat);

            LibCat.Name = NewName;
            LibCat.Groups = NewGroups;
            LibCat.Level = (LibraryLevel)NewLevel;
            LibCat.ProjectPath = "$(SPOCLIENT)\\Framework\\Features\\" + LibCat.Name + ".libcatproj";

            //LibCat.Description = BaseLibCat.Description;
            //LibCat.Documentation = BaseLibCat.Documentation;
            //LibCat.FeatureAssociations = BaseLibCat.FeatureAssociations;
            //LibCat.Groups = NewGroups;
            //LibCat.IgnoreDefaultLibPath = BaseLibCat.IgnoreDefaultLibPath;
            //LibCat.IsTranport = BaseLibCat.IsTranport;
            //LibCat.Level = NewLevel;
            //LibCat.LibraryProjCache = BaseLibCat.LibraryProjCache;
            //LibCat.Name = NewName;
            //LibCat.ProjectPath = "$(SPOCLIENT)\\Framework\\Features\\" + LibCat.Name + ".libcatproj";
            //LibCat.Required = BaseLibCat.Required;
            //LibCat.StubLibrary = BaseLibCat.StubLibrary;
            //LibCat.Templates = BaseLibCat.Templates;

            m_bw.SaveLibraryCategoryProj(LibCat);

            this.m_helper.DefaultInventory.LibraryCategories.Clear();
            this.LoadDefaultLibraryCatigoriesAsync();

            return BaseWrapper.Wrap<LibraryCategoryWrapper>(LibCat);
        }

        public LibraryCategoryWrapper CreateLibraryCategory(string name, string groups, LibraryLevelWrapper level)
        {
            LibraryCategory LibCat = new LibraryCategory();
            LibCat.Name = name;
            LibCat.Groups = groups;
            LibCat.Level = (LibraryLevel)level;
            LibCat.ProjectPath = "$(SPOCLIENT)\\Framework\\Features\\" + LibCat.Name + ".libcatproj";


            m_bw.SaveLibraryCategoryProj(LibCat);

            this.m_helper.DefaultInventory.LibraryCategories.Clear();
            this.LoadDefaultLibraryCatigoriesAsync();

            return BaseWrapper.Wrap<LibraryCategoryWrapper>(LibCat);
        }

        public bool SaveLibraryCategoryProj(LibraryCategoryWrapper libCat)
        {
            bool result = m_bw.SaveLibraryCategoryProj(libCat.InnerObject);

            if (result)
            {
                this.m_helper.DefaultInventory.LibraryCategories.Clear();
                this.LoadDefaultLibraryCatigoriesAsync();
            }
            return result;
        }

        public void DeleteLibraryCategoryProj(LibraryCategoryWrapper libcat)
        {
            string path = MsBuildWrapper.ExpandEnvVars(libcat.InnerObject.ProjectPath, "");
            File.Delete(path);

            this.m_helper.DefaultInventory.LibraryCategories.Clear();
            this.LoadDefaultLibraryCatigoriesAsync();
        }


        public LibraryCategoryWrapper[] GetRequiredLibraryCategories()
        {
            return m_helper.GetRequiredLibraryCategories();
        }

        #endregion

        #region Library

        public LibraryWrapper[] GetLibraries()
        {
            return m_helper.Libraries;
        }


        /// <summary>
        ///  Generates Library new unique library name based on BaseName
        /// </summary>
        /// <param name="BaseName">Base name for generation</param>
        /// <returns>Result name</returns>
        public string GenerateNewLibraryName(string BaseName)
        {
            string defaultName = "";
            string currentName = "";
            string suffix = "";
            string resultName = "";

            if (BaseName.Contains("test"))
            {
                defaultName = BaseName.Replace("test", "");
                currentName = BaseName;
                suffix = "test";
            }
            else if (BaseName.Contains("_stub"))
            {
                defaultName = BaseName.Replace("_stub", "");
                currentName = BaseName;
                suffix = "_stub";
            }
            else if (BaseName.Contains("_stubs"))
            {
                defaultName = BaseName.Replace("_stubs", "");
                currentName = BaseName;
                suffix = "_stubs";
            }
            else
            {
                defaultName = BaseName;
                currentName = BaseName;
                suffix = "";
            }

            if (char.IsDigit(defaultName, defaultName.Length - 1))
            {
                defaultName = defaultName.Remove(defaultName.Length - 1);
            }

            int i = 1;
            resultName = defaultName;

            while (this.CheckLibraryName(currentName))
            {
                resultName = defaultName + i.ToString();
                currentName = resultName + suffix;
                i++;
            }
            return resultName;
        }

        /// <summary>
        /// Checks Library name for uniqueness
        /// </summary>
        /// <param name="name"></param>
        /// <returns>True - if name is unique, else - false</returns>
        public bool CheckLibraryName(string name)
        {
            bool res = true;
            foreach (LibraryWrapper lib in m_helper.Libraries)
            {
                if (lib.Name == name) res = false;
            }
            return res;
        }

        public bool CheckLibrarProjName(string path)
        {
            return File.Exists(path);
        }

        public LibraryWrapper CreateLibrary(string name, string groups, string path, LibraryLevelWrapper level, bool isStub)
        {
            Library Lib = new Library
            {
                Name = name,
                Groups = groups,
                ProjectPath = path,
                Level = (LibraryLevel)level,
                IsStub = isStub,
                LibraryFile = name + ".$(LIB_EXT)",
                ManifestFile = name + ".$(LIB_EXT).manifest"
            };

            return BaseWrapper.Wrap<LibraryWrapper>(Lib);
        }

        public LibraryWrapper CreateLibrary(string Name, LibraryLevelWrapper Level, string Description, string ProjectPath, bool IsTemplate, ComponentWrapper LibraryCategory)
        {
            Library library = new Library
            {
                Name = Name,
                Level = (LibraryLevel)Level,
                Description = Description,
                ProjectPath = ProjectPath
            };
            LibraryWrapper wrapper = BaseWrapper.Wrap<LibraryWrapper>(library);
            wrapper.LibraryCategory = LibraryCategory;
            wrapper.IsTemplate = IsTemplate;
            return wrapper;
        }


        public LibraryWrapper CloneLibrary(LibraryWrapper BaseLib, string NewName, string NewGroups, string NewPath, LibraryLevelWrapper NewLevel, bool NewIsStub)
        {
            Library Lib = new Library();
            BaseLib.InnerObject.CopyTo(Lib);

            Lib.Name = NewName;
            Lib.Groups = NewGroups;
            Lib.ProjectPath = NewPath;
            Lib.Level = (LibraryLevel)NewLevel;
            Lib.IsStub = NewIsStub;
            Lib.LibraryFile = Lib.Name + ".$(LIB_EXT)";
            Lib.ManifestFile = Lib.Name + ".$(LIB_EXT).manifest";
            Lib.Properties.Clear();

            return BaseWrapper.Wrap<LibraryWrapper>(Lib);
        }

        public LibraryWrapper FindLibrary(string libraryGuid)
        {
            return this.m_helper.FindLibrary(libraryGuid);
        }

        public LibraryWrapper FindLibrary(ComponentWrapper comp)
        {
            return this.m_helper.FindLibrary(comp);
        }

        public LibraryWrapper FindLibraryByFile(string libraryFile)
        {
            return this.m_helper.FindLibraryByFile(libraryFile);
        }

        public LibraryWrapper FindLibraryByName(string libraryName)
        {
            return this.m_helper.FindLibraryByName(libraryName);
        }

        public LibraryWrapper FindLibraryByProject(string libraryProj)
        {
            return this.m_helper.FindLibraryByProject(libraryProj);
        }

        public void SaveLibraryProj(LibraryWrapper lib)
        {
            lib.Properties.Clear();
            m_bw.SaveLibraryProj(lib.InnerObject);
            this.LoadDefaultLibrariesAsync();
        }

        public void DeleteLibrary(LibraryWrapper lib)
        {
            string path = MsBuildWrapper.ExpandEnvVars(lib.ProjectPath, "");
            File.Delete(path);

            this.LoadDefaultLibrariesAsync();
        }

        public LibraryWrapper LoadLibraryProj(string libProjFile, string path)
        {
            return BaseWrapper.Wrap<LibraryWrapper>(this.m_bw.LoadLibraryProj(libProjFile, path));
        }

        public LibraryWrapper[] GetRequiredLibraries()
        {
            return m_helper.GetRequiredLibraries();
        }

        #endregion

        #region Processor

        public ProcessorWrapper[] GetProcessors()
        {
            return m_helper.Processors;
        }

        public ProcessorWrapper FindProcessor(string processorGuid)
        {
            return this.m_helper.FindProcessor(processorGuid);
        }

        public ProcessorWrapper FindProcessorByName(string procName)
        {
            return this.m_helper.FindProcessorByName(procName);
        }
        #endregion

        #region ISA

        public ISAWrapper[] GetISAs()
        {
            return m_helper.ISAs;
        }

        public ISAWrapper FindISA(string ISAGuid)
        {
            return this.m_helper.FindISA(ISAGuid);
        }

        #endregion

        #region Assemblies

        public AssemblyWrapper[] GetAssembies()
        {
            return m_helper.Assemblies;
        }

        public AssemblyWrapper FindAssembly(string asmGuid)
        {
            return this.m_helper.FindAssembly(asmGuid);
        }

        public AssemblyWrapper FindAssemblyByName(string asmName)
        {
            return this.m_helper.FindAssemblyByName(asmName);
        }

        #endregion

        #region Solutions

        public SolutionWrapper[] GetSolutions()
        {
            return m_helper.Solutions;
        }

        public SolutionWrapper CreateSolution(string Name, string Description, string Author, bool IsSolutionWizardVisible)
        {
            MFSolution solution = new MFSolution();
            solution.Name = Name;
            solution.Description = Description;
            solution.Author = Author;
            solution.IsSolutionWizardVisible = IsSolutionWizardVisible;

            return SolutionWrapper.Wrap<SolutionWrapper>(solution);
        }

        private void SetSolutionTransportType(SolutionWrapper solution)
        {
            //0_0  Hardcode from solution wizrad... Can't find any other way
            string str = "";
            string DebuggerPort = this.m_solution.DebuggerPort.ToUpper();
            if (DebuggerPort.StartsWith("COM"))
            {
                str = "USART";
            }
            else if (DebuggerPort.StartsWith("USB"))
            {
                str = "USB";
            }
            else if (DebuggerPort.StartsWith("COM_SOCKET_DBG"))
            {
                str = "SOCKETS";
            }

            foreach (LibraryCategoryWrapper LCW in this.m_helper.GetTransports())
            {
                string Name = LCW.Name.ToUpper().Replace("_PAL", "");
                if (string.Compare(Name, str, true) == 0)
                {
                    solution.TransportType = LCW;
                    break;
                }
            }
        }

        public void CopyTemplateFiles(LibraryCategoryWrapper libcat, SolutionWrapper solution, ComponentWrapper template)
        {
            this.m_bw.CopyTemplateFiles(libcat.InnerObject, solution.InnerObject, template.InnerObject);
        }

        public void GenerateSolution(SolutionWrapper solution)
        {
            if (string.IsNullOrEmpty(solution.ProjectPath))
            {
                solution.ProjectPath = @"$(SPOCLIENT)\Solutions\" + solution.Name + @"\" + solution.Name + ".settings";
            }
            PK.Wrapper.SaveSolutionProj(solution);
            PK.Wrapper.CreateSolutionDirProj(solution);
            foreach (ProjectWrapper project in solution.Projects)
            {
                PK.Wrapper.SaveProjectProj(project);
                PK.Wrapper.CopyProjFilesFromClone(project, solution);
            }
        }

        public void SaveSolutionProj(SolutionWrapper solution)
        {
            this.m_bw.SaveSolutionProj(solution.InnerObject);
        }

        public void CreateSolutionDirProj(SolutionWrapper solution)
        {
            this.m_bw.CreateSolutionDirProj(solution.InnerObject);
        }

        #endregion

        #region Project

        public void SaveProjectProj(ProjectWrapper mfproj)
        {
            this.m_bw.SaveProjectProj(mfproj.InnerObject);
        }

        #endregion

        #region Helpers
        public void CopyProjFilesFromClone(ProjectWrapper proj, SolutionWrapper solution)
        {
            this.m_bw.CopyProjFilesFromClone(proj.InnerObject, solution.InnerObject);
        }

        #endregion

        #region BuildTools

        public BuildToolWrapper_[] GetBuildTools()
        {
            return m_helper.BuildTools;
        }
        #endregion

        #region ProjectTemplates
        public List<ProjectWrapper> GetProjectTemplates()
        {
            return new List<ProjectWrapper>(this.m_inv.ProjectTemplates);
        }
        #endregion


        #region helpers


        public Project LoadProject(string fullpath)
        {
            return m_bw.LoadProject(fullpath);
        }

        public string ConvertPathToEnv(string fullpath)
        {
            return m_bw.ConvertPathToEnv(fullpath);
        }

        public string ExpandEnvVars(string text, string path)
        {
            return MsBuildWrapper.ExpandEnvVars(text, path);
        }

        public string ExpandPath(string path)
        {
            string result = string.Empty;

            result = this.ExpandEnvVars(path, "");

            if (result.Contains("%SRC_DIR%\\"))
                result = result.Replace("%SRC_DIR%\\", "");

            return Environment.ExpandEnvironmentVariables(result);
        }

        public string ExpandVars(string text, string path)
        {
            return ExpandVars(text, path);
        }


        /// <summary>
        /// Searchs components in inventory
        /// </summary>
        /// <param name="type">Search type</param>
        /// <param name="what">Search what</param>
        /// <param name="MatchCase">Match case</param>
        /// <param name="MatchWholeWord">Match whiole word</param>
        public void Search(SearchType type, SearchWhere where, string what, bool MatchCase, bool MatchWholeWord)
        {
            if (!this.m_SearchWorker.IsBusy)
                this.m_SearchWorker.RunWorkerAsync(new SearchParams(type, where, what, MatchCase, MatchWholeWord));
        }

        #region Libraries Search

        /// <summary>
        /// Searchs in Libraries
        /// </summary>
        /// <param name="what"></param>
        /// <param name="MatchCase"></param>
        /// <param name="MatchWholeWord"></param>
        private void SearchInLibraries(SearchWhere where, string what, bool MatchCase, bool MatchWholeWord)
        {
            if ((where == SearchWhere.All) || (where == SearchWhere.PKDatabase))
            {
                foreach (LibraryWrapper LW in m_inv.Libraries)
                {
                    if (Solution != null)
                    {
                        if (Solution.IsReference(LW))
                        {
                            this.CheckLibrary(LW, what, MatchCase, MatchWholeWord);
                        }
                    }
                    else
                    {
                        this.CheckLibrary(LW, what, MatchCase, MatchWholeWord);
                    }
                }
            }

            if ((where == SearchWhere.All) || (where == SearchWhere.Solution))
            {
                if (Solution != null)
                {
                    foreach (ProjectWrapper PW in Solution.Projects)
                    {
                        foreach (ComponentWrapper CW in PW.Libraries)
                        {
                            LibraryWrapper LW = this.FindLibrary(CW);
                            if ((LW != null))// && (!Libs.Contains(LW)))
                            {
                                SearchResultsHolder.ComponentDescriptor ProjectDesc = new SearchResultsHolder.ComponentDescriptor();
                                ProjectDesc.Component = ComponentWrapper.GetComponentWrapper(PW);
                                ProjectDesc.Parent = new SearchResultsHolder.ComponentDescriptor(null, ComponentWrapper.GetComponentWrapper(Solution));
                                this.CheckLibrary(ProjectDesc, LW, what, MatchCase, MatchWholeWord);
                            }
                        }
                    }
                }
            }
        }
        private void CheckLibrary(LibraryWrapper lib, string what, bool MatchCase, bool MatchWholeWord)
        {
            CheckLibrary(null, lib, what, MatchCase, MatchWholeWord);
        }
        private void CheckLibrary(SearchResultsHolder.ComponentDescriptor ProjectDesc, LibraryWrapper lib, string what, bool MatchCase, bool MatchWholeWord)
        {
            SearchResultsHolder.ComponentDescriptor CompDesc = new SearchResultsHolder.ComponentDescriptor(ComponentWrapper.GetComponentWrapper(lib));
            if (ProjectDesc != null)
                CompDesc.Parent = ProjectDesc;

            m_SearchResults.TotalComponentsSearched++;            

            if (MatchWholeWord)
            {
                if (MatchCase)
                {
                    if (lib.Name == what)
                    {
                        m_SearchResults.FindedComponents.Add(CompDesc);
                        OnElementFinded(CompDesc);
                    }
                }
                else
                {
                    if (lib.Name.ToLower() == what.ToLower())
                    {
                        m_SearchResults.FindedComponents.Add(CompDesc);
                        OnElementFinded(CompDesc);
                    }
                }
            }
            else
            {
                if (MatchCase)
                {
                    if (lib.Name.Contains(what))
                    {
                        m_SearchResults.FindedComponents.Add(CompDesc);
                        OnElementFinded(CompDesc);
                    }
                }
                else
                {
                    if (lib.Name.ToLower().Contains(what.ToLower()))
                    {
                        m_SearchResults.FindedComponents.Add(CompDesc);
                        OnElementFinded(CompDesc);
                    }
                }
            }
        }
        #endregion

        #region LibraryCategories Search
        /// <summary>
        /// Searchs in LibraryCategories
        /// </summary>
        /// <param name="what"></param>
        /// <param name="MatchCase"></param>
        /// <param name="MatchWholeWord"></param>
        private void SearchInLibraryCategories(SearchWhere where, string what, bool MatchCase, bool MatchWholeWord)
        {
            if ((where == SearchWhere.All) || (where == SearchWhere.PKDatabase))
            {
                foreach (LibraryCategoryWrapper LCW in m_inv.LibraryCategories)
                {
                    this.CheckLibraryCategory(LCW, what, MatchCase, MatchWholeWord);
                }
            }

            if ((where == SearchWhere.All) || (where == SearchWhere.Solution))
            {
                if (Solution != null)
                {
                    foreach (ProjectWrapper PW in Solution.Projects)
                    {
                        foreach (ComponentWrapper CW in PW.LibraryCategories)
                        {
                            LibraryCategoryWrapper LCW = this.FindLibraryCategory(CW.Guid);
                            if ((LCW != null))// && (!Libs.Contains(LW)))
                            {
                                SearchResultsHolder.ComponentDescriptor ProjectDesc = new SearchResultsHolder.ComponentDescriptor();
                                ProjectDesc.Component = ComponentWrapper.GetComponentWrapper(PW);
                                ProjectDesc.Parent = new SearchResultsHolder.ComponentDescriptor(null, ComponentWrapper.GetComponentWrapper(Solution));
                                this.CheckLibraryCategory(ProjectDesc, LCW, what, MatchCase, MatchWholeWord);
                            }
                        }
                    }
                }
            }
        }

        private void CheckLibraryCategory(LibraryCategoryWrapper libcat, string what, bool MatchCase, bool MatchWholeWord)
        {
            CheckLibraryCategory(null, libcat, what, MatchCase, MatchWholeWord);
        }
        private void CheckLibraryCategory(SearchResultsHolder.ComponentDescriptor ProjectDesc, LibraryCategoryWrapper libcat, string what, bool MatchCase, bool MatchWholeWord)
        {
            SearchResultsHolder.ComponentDescriptor CompDesc = new SearchResultsHolder.ComponentDescriptor(ComponentWrapper.GetComponentWrapper(libcat));
            if (ProjectDesc != null)
                CompDesc.Parent = ProjectDesc;

            m_SearchResults.TotalComponentsSearched++;

            if (MatchWholeWord)
            {
                if (MatchCase)
                {
                    if (libcat.Name == what)
                    {
                        m_SearchResults.FindedComponents.Add(CompDesc);
                        OnElementFinded(CompDesc);
                    }
                }
                else
                {
                    if (libcat.Name.ToLower() == what.ToLower())
                    {
                        m_SearchResults.FindedComponents.Add(CompDesc);
                        OnElementFinded(CompDesc);
                    }
                }
            }
            else
            {
                if (MatchCase)
                {
                    if (libcat.Name.Contains(what))
                    {
                        m_SearchResults.FindedComponents.Add(CompDesc);
                        OnElementFinded(CompDesc);
                    }
                }
                else
                {
                    if (libcat.Name.ToLower().Contains(what.ToLower()))
                    {
                        m_SearchResults.FindedComponents.Add(CompDesc);
                        OnElementFinded(CompDesc);
                    }
                }
            }
        }

        #endregion

        #region Features Search

        /// <summary>
        /// Searchs in Features
        /// </summary>
        /// <param name="what"></param>
        /// <param name="MatchCase"></param>
        /// <param name="MatchWholeWord"></param>
        private void SearchInFeatures(SearchWhere where, string what, bool MatchCase, bool MatchWholeWord)
        {
            if ((where == SearchWhere.All) || (where == SearchWhere.PKDatabase))
            {
                foreach (FeatureWrapper FW in m_inv.Features)
                {
                    this.CheckFeature(FW, what, MatchCase, MatchWholeWord);
                }
            }

            if ((where == SearchWhere.All) || (where == SearchWhere.Solution))
            {
                if (Solution != null)
                {
                    foreach (ProjectWrapper PW in Solution.Projects)
                    {
                        foreach (ComponentWrapper CW in PW.Features)
                        {
                            FeatureWrapper FW = this.FindFeature(CW.Guid);
                            if ((FW != null))// && (!Libs.Contains(LW)))
                            {
                                SearchResultsHolder.ComponentDescriptor ProjectDesc = new SearchResultsHolder.ComponentDescriptor();
                                ProjectDesc.Component = ComponentWrapper.GetComponentWrapper(PW);
                                ProjectDesc.Parent = new SearchResultsHolder.ComponentDescriptor(null, ComponentWrapper.GetComponentWrapper(Solution));
                                this.CheckFeature(ProjectDesc, FW, what, MatchCase, MatchWholeWord);
                            }
                        }
                    }
                }
            }
        }

        private void CheckFeature(FeatureWrapper feat, string what, bool MatchCase, bool MatchWholeWord)
        {
            CheckFeature(null, feat, what, MatchCase, MatchWholeWord);
        }
        private void CheckFeature(SearchResultsHolder.ComponentDescriptor ProjectDesc, FeatureWrapper feat, string what, bool MatchCase, bool MatchWholeWord)
        {
            SearchResultsHolder.ComponentDescriptor CompDesc = new SearchResultsHolder.ComponentDescriptor(ComponentWrapper.GetComponentWrapper(feat));
            if (ProjectDesc != null)
                CompDesc.Parent = ProjectDesc;

            m_SearchResults.TotalComponentsSearched++;

            if (MatchWholeWord)
            {
                if (MatchCase)
                {
                    if (feat.Name == what)
                    {
                        m_SearchResults.FindedComponents.Add(CompDesc);
                        OnElementFinded(CompDesc);
                    }
                }
                else
                {
                    if (feat.Name.ToLower() == what.ToLower())
                    {
                        m_SearchResults.FindedComponents.Add(CompDesc);
                        OnElementFinded(CompDesc);
                    }
                }
            }
            else
            {
                if (MatchCase)
                {
                    if (feat.Name.Contains(what))
                    {
                        m_SearchResults.FindedComponents.Add(CompDesc);
                        OnElementFinded(CompDesc);
                    }
                }
                else
                {
                    if (feat.Name.ToLower().Contains(what.ToLower()))
                    {
                        m_SearchResults.FindedComponents.Add(CompDesc);
                        OnElementFinded(CompDesc);
                    }
                }
            }
        }

        #endregion

        #region Files Search

        /// <summary>
        /// Serarchs files
        /// </summary>
        /// <param name="what"></param>
        /// <param name="MatchCase"></param>
        /// <param name="MatchWholeWord"></param>
        private void SearchFiles(SearchWhere where, string what, bool MatchCase, bool MatchWholeWord)
        {
            List<BuildFileWrapper> FilesList = new List<BuildFileWrapper>();

            List<LibraryWrapper> CheckedLibrariesList = new List<LibraryWrapper>();

            if ((where == SearchWhere.All) || (where == SearchWhere.PKDatabase))
            {
                foreach (LibraryWrapper LW in m_inv.Libraries)
                {
                    FilesList.Clear();

                    if (Solution != null)
                    {
                        if (Solution.IsReference(LW))
                        {
                            FilesList.AddRange(LW.FastCompileFiles);
                            FilesList.AddRange(LW.HeaderFiles);
                            FilesList.AddRange(LW.OtherFiles);
                            FilesList.AddRange(LW.SourceFiles);
                        }
                    }
                    else
                    {
                        FilesList.AddRange(LW.FastCompileFiles);
                        FilesList.AddRange(LW.HeaderFiles);
                        FilesList.AddRange(LW.OtherFiles);
                        FilesList.AddRange(LW.SourceFiles);
                    }

                    SearchResultsHolder.ComponentDescriptor LibraryDesc = new SearchResultsHolder.ComponentDescriptor(ComponentWrapper.GetComponentWrapper(LW));

                    foreach (BuildFileWrapper file in FilesList)
                    {
                        this.CheckFile(LibraryDesc, file, what, MatchCase, MatchWholeWord);
                    }
                }
            }

            if ((where == SearchWhere.All) || (where == SearchWhere.Solution))
            {
                if (Solution != null)
                {
                    foreach (ProjectWrapper PW in Solution.Projects)
                    {
                        foreach (ComponentWrapper CW in PW.Libraries)
                        {
                            LibraryWrapper LW = this.FindLibrary(CW.Guid);
                            if ((LW != null))// && (!Libs.Contains(LW)))
                            {

                                if (CheckedLibrariesList.Contains(LW)) continue;

                                CheckedLibrariesList.Add(LW);

                                FilesList.Clear();
                                FilesList.AddRange(LW.FastCompileFiles);
                                FilesList.AddRange(LW.HeaderFiles);
                                FilesList.AddRange(LW.OtherFiles);
                                FilesList.AddRange(LW.SourceFiles);

                                //SearchResultsHolder.ComponentDescriptor ProjectDesc = new SearchResultsHolder.ComponentDescriptor();
                                //ProjectDesc.Component = ComponentWrapper.GetComponentWrapper(PW);
                                //ProjectDesc.Parent = new SearchResultsHolder.ComponentDescriptor(null, ComponentWrapper.GetComponentWrapper(Solution));

                                //SearchResultsHolder.ComponentDescriptor LibraryDesc = new SearchResultsHolder.ComponentDescriptor(ProjectDesc, ComponentWrapper.GetComponentWrapper(LW));

                                SearchResultsHolder.ComponentDescriptor LibraryDesc = new SearchResultsHolder.ComponentDescriptor(new SearchResultsHolder.ComponentDescriptor(null, ComponentWrapper.GetComponentWrapper(Solution)), ComponentWrapper.GetComponentWrapper(LW));

                                if (!Solution.IsReference(LW))
                                {
                                    foreach (BuildFileWrapper file in FilesList)
                                    {
                                        this.CheckFile(LibraryDesc, file, what, MatchCase, MatchWholeWord);
                                    }
                                }
                            }
                        }
                    }
                }
            }




            //List<LibraryWrapper> Libs = new List<LibraryWrapper>();

            ////ProjectWrapper ParentProject = null;

            //switch (where)
            //{
            //    case SearchWhere.PKDatabase:
            //        Libs.AddRange(m_inv.Libraries);
            //        SearchFileInLibraryList(Libs, what, MatchCase, MatchWholeWord);
            //        break;
            //    case SearchWhere.Solution:
            //        if (Solution != null)
            //        {
            //            foreach (ProjectWrapper PW in Solution.Projects)
            //            {
            //                Libs.Clear();
            //                foreach (ComponentWrapper CW in PW.Libraries)
            //                {
            //                    LibraryWrapper LW = this.FindLibrary(CW);
            //                    if ((LW != null) && (!Libs.Contains(LW)))
            //                        Libs.Add(LW);
            //                }
            //                SearchFileInLibraryList(PW, Libs, what, MatchCase, MatchWholeWord);
            //            }
            //        }
            //        break;
            //}
        }

        private void CheckFile(BuildFileWrapper file, string what, bool MatchCase, bool MatchWholeWord)
        {
            CheckFile(null, file, what, MatchCase, MatchWholeWord);
        }
        private void CheckFile(SearchResultsHolder.ComponentDescriptor ProjectDesc, BuildFileWrapper file, string what, bool MatchCase, bool MatchWholeWord)
        {
            SearchResultsHolder.ComponentDescriptor CompDesc = new SearchResultsHolder.ComponentDescriptor(file);
            if (ProjectDesc != null)
                CompDesc.Parent = ProjectDesc;

            m_SearchResults.TotalComponentsSearched++;

            if (MatchWholeWord)
            {
                if (MatchCase)
                {
                    if (file.Name == what)
                    {
                        if (!m_SearchResults.FindedComponents.Contains(CompDesc))
                        {
                            m_SearchResults.FindedComponents.Add(CompDesc);
                            OnElementFinded(CompDesc);
                        }
                    }
                }
                else
                {
                    if (file.Name.ToLower() == what.ToLower())
                    {
                        if (!m_SearchResults.FindedComponents.Contains(CompDesc))
                        {
                            m_SearchResults.FindedComponents.Add(CompDesc);
                            OnElementFinded(CompDesc);
                        }
                    }
                }
            }
            else
            {
                if (MatchCase)
                {
                    if (file.Name.Contains(what))
                    {
                        if (!m_SearchResults.FindedComponents.Contains(CompDesc))
                        {
                            m_SearchResults.FindedComponents.Add(CompDesc);
                            OnElementFinded(CompDesc);
                        }
                    }
                }
                else
                {
                    if (file.Name.ToLower().Contains(what.ToLower()))
                    {
                        if (!m_SearchResults.FindedComponents.Contains(CompDesc))
                        {
                            m_SearchResults.FindedComponents.Add(CompDesc);
                            OnElementFinded(CompDesc);
                        }
                    }
                }
            }
        }

        #endregion

        #region SearchInFiles
        private void SearchTextInFiles(SearchWhere where, string what, bool MatchCase, bool MatchWholeWord)
        {
            List<BuildFileWrapper> FilesList = new List<BuildFileWrapper>();

            List<LibraryWrapper> CheckedLibrariesList = new List<LibraryWrapper>();

            if ((where == SearchWhere.All) || (where == SearchWhere.PKDatabase))
            {
                foreach (LibraryWrapper LW in m_inv.Libraries)
                {
                    FilesList.Clear();

                    if (Solution != null)
                    {
                        if (Solution.IsReference(LW))
                        {
                            FilesList.AddRange(LW.FastCompileFiles);
                            FilesList.AddRange(LW.HeaderFiles);
                            FilesList.AddRange(LW.OtherFiles);
                            FilesList.AddRange(LW.SourceFiles);
                        }
                    }
                    else
                    {
                        FilesList.AddRange(LW.FastCompileFiles);
                        FilesList.AddRange(LW.HeaderFiles);
                        FilesList.AddRange(LW.OtherFiles);
                        FilesList.AddRange(LW.SourceFiles);
                    }

                    SearchResultsHolder.ComponentDescriptor LibraryDesc = new SearchResultsHolder.ComponentDescriptor(ComponentWrapper.GetComponentWrapper(LW));

                    foreach (BuildFileWrapper file in FilesList)
                    {
                        this.CheckTextInFile(LibraryDesc, file, what, MatchCase, MatchWholeWord);
                    }
                }
            }

            if ((where == SearchWhere.All) || (where == SearchWhere.Solution))
            {
                if (Solution != null)
                {
                    foreach (ProjectWrapper PW in Solution.Projects)
                    {
                        foreach (ComponentWrapper CW in PW.Libraries)
                        {
                            LibraryWrapper LW = this.FindLibrary(CW.Guid);
                            if ((LW != null))// && (!Libs.Contains(LW)))
                            {
                                if (CheckedLibrariesList.Contains(LW)) continue;

                                CheckedLibrariesList.Add(LW);

                                FilesList.Clear();
                                FilesList.AddRange(LW.FastCompileFiles);
                                FilesList.AddRange(LW.HeaderFiles);
                                FilesList.AddRange(LW.OtherFiles);
                                FilesList.AddRange(LW.SourceFiles);

                                //SearchResultsHolder.ComponentDescriptor ProjectDesc = new SearchResultsHolder.ComponentDescriptor();
                                //ProjectDesc.Component = ComponentWrapper.GetComponentWrapper(PW);
                                //ProjectDesc.Parent = new SearchResultsHolder.ComponentDescriptor(null, ComponentWrapper.GetComponentWrapper(Solution));

                                //SearchResultsHolder.ComponentDescriptor LibraryDesc = new SearchResultsHolder.ComponentDescriptor(ProjectDesc, ComponentWrapper.GetComponentWrapper(LW));

                                SearchResultsHolder.ComponentDescriptor LibraryDesc = new SearchResultsHolder.ComponentDescriptor(new SearchResultsHolder.ComponentDescriptor(null, ComponentWrapper.GetComponentWrapper(Solution)), ComponentWrapper.GetComponentWrapper(LW));

                                if (!Solution.IsReference(LW))
                                {
                                    foreach (BuildFileWrapper file in FilesList)
                                    {
                                        this.CheckTextInFile(LibraryDesc, file, what, MatchCase, MatchWholeWord);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        private void CheckTextInFile(BuildFileWrapper file, string what, bool MatchCase, bool MatchWholeWord)
        {
            CheckTextInFile(null, file, what, MatchCase, MatchWholeWord);
        }
        private void CheckTextInFile(SearchResultsHolder.ComponentDescriptor ProjectDesc, BuildFileWrapper file, string what, bool MatchCase, bool MatchWholeWord)
        {
            if (!File.Exists(file.FullPath)) return;
            
            m_SearchResults.TotalComponentsSearched++;

            using (StreamReader tr = new StreamReader(file.FullPath))
            {

                int LineNum = 0;

                while (!tr.EndOfStream)
                {
                    LineNum++;
                    string Line = tr.ReadLine();

                    SearchResultsHolder.ComponentDescriptor CompDesc = new SearchResultsHolder.ComponentDescriptor(file);
                    if (ProjectDesc != null)
                        CompDesc.Parent = ProjectDesc;

                    CompDesc.Line = new SearchResultsHolder.ComponentDescriptor.LineDescriptor(LineNum, Line);

                    //if (MatchWholeWord)
                    //{
                    //    if (MatchCase)
                    //    {
                    //        if (file.Name == what)
                    //        {
                    //            m_SearchResults.FindedComponents.Add(CompDesc);
                    //            OnElementFinded(CompDesc);
                    //        }
                    //    }
                    //    else
                    //    {
                    //        if (file.Name.ToLower() == what.ToLower())
                    //        {
                    //            m_SearchResults.FindedComponents.Add(CompDesc);
                    //            OnElementFinded(CompDesc);
                    //        }
                    //    }
                    //}
                    //else
                    //{
                    if (MatchCase)
                    {
                        if (Line.Contains(what))
                        {
                            m_SearchResults.FindedComponents.Add(CompDesc);
                            OnElementFinded(CompDesc);
                        }
                    }
                    else
                    {
                        if (Line.ToLower().Contains(what.ToLower()))
                        {
                            m_SearchResults.FindedComponents.Add(CompDesc);
                            OnElementFinded(CompDesc);
                        }
                    }
                    //}
                }
            }
        }

        #endregion
        #endregion

        #endregion

        #region events

        /// <summary>
        /// Async operations progress
        /// </summary>
        public event ProgressChangedEventHandler AsyncProgressChanged
        {
            add
            {
                if (m_worker != null)
                {
                    m_worker.ProgressChanged += value;
                    m_SearchWorker.ProgressChanged += value;
                }
            }
            remove
            {
                if (m_worker != null)
                {
                    m_worker.ProgressChanged -= value;
                    m_SearchWorker.ProgressChanged -= value;
                }
            }
        }

        #region Element Finded event

        /// <summary>
        /// Finded next element
        /// </summary>
        public event EventHandler<ElementFindedEventArgs> ElementFindedEvent;

        private void OnElementFinded(SearchResultsHolder.ComponentDescriptor component)
        {
            if (ElementFindedEvent != null)
            {
                ElementFindedEvent(this, new ElementFindedEventArgs(component));
            }
        }

        #endregion

        #region Search complited event

        /// <summary>
        /// Search competed
        /// </summary>
        public event EventHandler<SearchComplitedEventArgs> SearchComplitedEvent;

        private void OnSearchComplited(SearchResultsHolder searchResults)
        {
            if (SearchComplitedEvent != null)
            {
                SearchComplitedEvent(this, new SearchComplitedEventArgs(searchResults));
            }
        }

        #endregion


        #region Search started event

        /// <summary>
        /// Search started
        /// </summary>
        public event EventHandler<SearchStartedEventArgs> SearchStartedEvent;

        private void OnSearchStarted(SearchParams SearchParams)
        {
            if (SearchStartedEvent != null)
            {
                SearchStartedEvent(this, new SearchStartedEventArgs(SearchParams));
            }
        }

        #endregion

        #region Load Inventory Async Complete event

        /// <summary>
        /// Incentory loading compleated
        /// </summary>
        public event EventHandler LoadInventoryAsyncCompleteEvent;

        private void OnLoadInventoryComplete()
        {
            if (LoadInventoryAsyncCompleteEvent != null)
            {
                LoadInventoryAsyncCompleteEvent(this, EventArgs.Empty);
            }
        }

        #endregion

        #region Load Library Categories Async Complete event

        /// <summary>
        /// Library Categories loading compleated
        /// </summary>
        public event EventHandler LoadLibraryCategoriesAsyncCompleteEvent;

        private void OnLoadLibraryCategoriesComplete()
        {
            if (LoadLibraryCategoriesAsyncCompleteEvent != null)
            {
                LoadLibraryCategoriesAsyncCompleteEvent(this, EventArgs.Empty);
            }
        }

        #endregion

        #region Load Features Async Complete event

        /// <summary>
        /// Features loading compleated
        /// </summary>
        public event EventHandler LoadFeaturesAsyncCompleteEvent;

        private void OnLoadFeaturesComplete()
        {
            if (LoadFeaturesAsyncCompleteEvent != null)
            {
                LoadFeaturesAsyncCompleteEvent(this, EventArgs.Empty);
            }
        }

        #endregion

        #region Load Libraryes Async Complete event

        /// <summary>
        /// Libraryes loading compleated
        /// </summary>
        public event EventHandler LoadLibrariesAsyncCompleteEvent;

        private void OnLoadLibraryesComplete()
        {
            if (LoadLibrariesAsyncCompleteEvent != null)
            {
                LoadLibrariesAsyncCompleteEvent(this, EventArgs.Empty);
            }
        }

        #endregion

        #region Load SolutionRefs Async Complete event

        /// <summary>
        /// Solutions loading compleated
        /// </summary>
        public event EventHandler LoadSolutionsAsyncCompleteEvent;

        private void OnLoadSolutionsComplete()
        {
            if (LoadSolutionsAsyncCompleteEvent != null)
            {
                LoadSolutionsAsyncCompleteEvent(this, EventArgs.Empty);
            }
        }

        #endregion

        #region Load Solution Async Complete event

        /// <summary>
        /// Solutions loading compleated
        /// </summary>
        public event EventHandler<LoadSolutionAsyncCompletedEventArgs> LoadSolutionAsyncCompleteEvent;

        private void OnLoadSolutionComplete()
        {
            if (LoadSolutionAsyncCompleteEvent != null)
            {
                LoadSolutionAsyncCompleteEvent(this, new LoadSolutionAsyncCompletedEventArgs(this.m_solution));
            }
        }

        #endregion

        #endregion


        #region IDisposable Members


        protected virtual void Dispose(bool disposing)
        {
            if (disposing)
            {
                m_worker.Dispose();
                m_SearchWorker.Dispose();
            }
        }


        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        #endregion
    }
}
