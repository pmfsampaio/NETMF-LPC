using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using ComponentObjectModel;
using WeifenLuo.WinFormsUI.Docking;
using System.IO;
using System.Reflection;
using PKStudio.ItemWrappers;
using Microsoft.Build.Framework;
using PKStudio.Helpers;
using System.Diagnostics;
using PKStudio.Forms.BaseForms;

namespace PKStudio
{
    public partial class MainForm : Form
    {


        private DeserializeDockContent m_deserializeDockContent;

        private PKStudio.Helpers.EditorsFormsController mEditorsController;

        private PKStudio.Helpers.MSBuildHelper mMSBuildHelper = new Helpers.MSBuildHelper();

        private Forms.Properties mProperties;
        private Forms.Tools.FindComponentForm mFindComponentForm;
        private Forms.Tools.FindResultsForm mFindResultsForm;
        private PKStudio.Helpers.MSBuildOutputLogger mMSBuildLogger;
        private Forms.Tools.ComponentReferencesDiagramForm mComponentReferencesDiagramForm;
        private PKStudio.Forms.Output.OutputForm mOutputForm;
        private PKStudio.Forms.Output.ErrorListForm mErrorListForm;
        
        private Forms.Explorers.SolutionExplorer mSolutionExplorer;
        private Forms.Explorers.LibraryCategoriesExplorer mLibraryCategoriesExplorer;
        private Forms.Explorers.FeaturesExplorer mFeaturesExplorer;
        private Forms.Explorers.LibrariesExplorer mLibrariesExplorer;
        private Forms.Explorers.ProcessorExplorer mProcessorsExplorer;
        private Forms.Explorers.AssembliesExplorer mAssembliesExplorer;

        private List<Forms.BaseForms.BasePKInventoryForm> mExplorersList = new List<Forms.BaseForms.BasePKInventoryForm>();

        private Dialogs.AboutDialog mAboutDialog = null;
        private Tools.uVisionGenerator.Wizard.uVisionProjectGeneratorWizard mKeilGeneratorTool = null;
        VerificationHelper mVereficationHelper = new VerificationHelper();

        //private Forms.Editors.LibraryCategoryEditor mLibraryCategoryEditor;
        //private Forms.Editors.LibraryEditor mLibraryEditor;
        //private Forms.Editors.FeatureEditor mFeatureEditor;
        //private Forms.Editors.SourceFileEditor mCodeFileEditor;

        //private Dictionary<int, Forms.Editors.SourceFileEditor> mSourceFileEditorsDictionaty = new Dictionary<int, Forms.Editors.SourceFileEditor>();

        private Dialogs.ApplicationLoading mApplicationLoading;

        /// <summary>
        /// Ru: Переменная которая считает сколько обращении PerformStep прогресс бара значение ProgressBar value = maximum.
        /// Это необходимо чтобы полоса прогресс бара доходила до конца прежде чем сброситься в 0
        /// En: Using for correct progressbar work.
        /// </summary>
        int ProgressBarFillTimes = 0;

        /// <summary>
        /// Ru: Используется для добавления элементов меню в run time
        /// En: Using for updating menu elements in runtime
        /// </summary>
        ToolStripMenuItem ToolStripMenuItem = null;


        public MainForm()
        {
            InitializeComponent();

            InventoryHelper.ExhaustiveLibrarySearch = true;

            PK.Wrapper.AsyncProgressChanged += new ProgressChangedEventHandler(m_worker_ProgressChanged);
            PK.Wrapper.SearchComplitedEvent += new EventHandler<PortingKitWrapper.SearchComplitedEventArgs>(PKWrapper_SearchComplitedEvent);
            PK.Wrapper.LoadSolutionAsyncCompleteEvent += new EventHandler<PortingKitWrapper.LoadSolutionAsyncCompletedEventArgs>(Wrapper_LoadSolutionAsyncCompleteEvent);

            ProgressBar.Minimum = 0;
            ProgressBar.Maximum = 100;
            ProgressBar.Step = 1;
            ProgressBar.Value = 0;
            ProgressLabel.Text = "";

            mProperties = new Forms.Properties();
            mFindComponentForm = new Forms.Tools.FindComponentForm();
            mFindResultsForm = new Forms.Tools.FindResultsForm();
            mFindResultsForm.EditEvent += new EventHandler<Forms.BaseForms.ObjectEventArgs>(OnEditEvent);
            mFindResultsForm.OpenContainingFolderEvent += new EventHandler<Forms.BaseForms.PathEventArgs>(explorer_OpenContainingFolderEvent);


            mMSBuildLogger = new Helpers.MSBuildOutputLogger();
            mMSBuildLogger.Verbosity = LoggerVerbosity.Diagnostic;

            mOutputForm = new Forms.Output.OutputForm();
            mOutputForm.AttachLogger(mMSBuildLogger);
            mOutputForm.AttachLogger(mVereficationHelper);
            mErrorListForm = new Forms.Output.ErrorListForm();
            mErrorListForm.AttachLogger(mMSBuildLogger);
            mErrorListForm.AttachLogger(mVereficationHelper);


            mMSBuildLogger.LogStartedEvent += new EventHandler(Logger_LogStartedEvent);
            mMSBuildLogger.BuildStepEvent += new EventHandler(MSBuildLogger_BuildStepEvent);
            mMSBuildLogger.LogFinishedEvent += new EventHandler<LogFinishedEventArgs>(Logger_LogFinishedEvent);
            //MSBuildLogger.OpenContainingFolderEvent += new EventHandler<Forms.BaseForms.PathEventArgs>(explorer_OpenContainingFolderEvent);

            mErrorListForm.EditEvent += new EventHandler<Forms.BaseForms.ObjectEventArgs>(OnEditEvent);
            mErrorListForm.OpenContainingFolderEvent += new EventHandler<Forms.BaseForms.PathEventArgs>(explorer_OpenContainingFolderEvent);

            mOutputForm.EditEvent += new EventHandler<Forms.BaseForms.ObjectEventArgs>(OnEditEvent);
            mOutputForm.OpenContainingFolderEvent += new EventHandler<Forms.BaseForms.PathEventArgs>(explorer_OpenContainingFolderEvent);
            mMSBuildHelper.Loggers.Add(mMSBuildLogger);

            mApplicationLoading = new Dialogs.ApplicationLoading();

            mComponentReferencesDiagramForm = new Forms.Tools.ComponentReferencesDiagramForm();
            mComponentReferencesDiagramForm.SelectionChangedEvent += new EventHandler<Forms.BaseForms.ObjectEventArgs>(OnSelectionChangedEvent);
            mComponentReferencesDiagramForm.ShowPropertiesEvent += new EventHandler<Forms.BaseForms.ObjectEventArgs>(OnShowPropertiesEvent);
            mComponentReferencesDiagramForm.EditEvent += new EventHandler<Forms.BaseForms.ObjectEventArgs>(OnEditEvent);
            mComponentReferencesDiagramForm.OpenContainingFolderEvent += new EventHandler<Forms.BaseForms.PathEventArgs>(explorer_OpenContainingFolderEvent);

            //mInventoryTree = new Forms.InventoryTree(m_inv);
            mSolutionExplorer = new Forms.Explorers.SolutionExplorer();
            mLibraryCategoriesExplorer = new Forms.Explorers.LibraryCategoriesExplorer();
            mFeaturesExplorer = new Forms.Explorers.FeaturesExplorer();
            mLibrariesExplorer = new Forms.Explorers.LibrariesExplorer();
            mProcessorsExplorer = new Forms.Explorers.ProcessorExplorer();
            mAssembliesExplorer = new Forms.Explorers.AssembliesExplorer();

            mExplorersList.Add(mSolutionExplorer);
            mExplorersList.Add(mLibraryCategoriesExplorer);
            mExplorersList.Add(mFeaturesExplorer);
            mExplorersList.Add(mLibrariesExplorer);
            mExplorersList.Add(mProcessorsExplorer);
            mExplorersList.Add(mAssembliesExplorer);

            foreach (Forms.BaseForms.BasePKInventoryForm explorer in mExplorersList)
            {
                explorer.GenerateEvent += new EventHandler<Forms.BaseForms.GenerateEventArgs>(OnGenerateEvent);
                explorer.OpenContainingFolderEvent += new EventHandler<Forms.BaseForms.PathEventArgs>(explorer_OpenContainingFolderEvent);
                explorer.WrapperActionEvent += new EventHandler<Forms.BaseForms.WrapperActionArgs>(explorer_WrapperActionEvent);
                RegisterEventComponent(explorer);
            }

            mEditorsController = new Helpers.EditorsFormsController(dockPanel1);

            this.mEditorsController.ShowEditorEvent += new EditorsFormsController.ShowEditorEventHandler(mEditorsController_ShowEditorEvent);

            //mLibraryCategoryEditor = new Forms.Editors.LibraryCategoryEditor();
            //mLibraryEditor = new Forms.Editors.LibraryEditor();
            //mFeatureEditor = new Forms.Editors.FeatureEditor();
            //mCodeFileEditor = new Forms.Editors.CodeFileEditor();


            Helper.AssemblyInfoHelper asmhelper = new Helper.AssemblyInfoHelper(Assembly.GetExecutingAssembly());

            this.Text = asmhelper.Title;
            aboutToolStripMenuItem.Text += " " + asmhelper.Title;

            buildToolStripMenuItem.Visible = false;

            BuildTypeCB.Visible = false;
            BuildToolStripSeparator.Visible = false;
            BuildMediaTypeCB.Visible = false;

            uVisionProjectGenerationToolStripMenuItem.Visible = false;

        }

        void mEditorsController_ShowEditorEvent(object sender, EditorsFormsController.ShowEditorEditorEventArgs e)
        {
            this.RegisterEventComponent(e.Editor);
        }

        void RegisterEventComponent(IEventComponent component)
        {
            if (component != null)
            {
                component.ShowPropertiesEvent += new EventHandler<Forms.BaseForms.ObjectEventArgs>(OnShowPropertiesEvent);
                component.EditEvent += new EventHandler<Forms.BaseForms.ObjectEventArgs>(OnEditEvent);
                component.SelectionChangedEvent += new EventHandler<Forms.BaseForms.ObjectEventArgs>(OnSelectionChangedEvent);
                component.ShowReferencesDiagramEvent += new EventHandler<Forms.BaseForms.ObjectEventArgs>(OnShowReferencesDiagramEvent);
            }
        }

        void explorer_WrapperActionEvent(object sender, Forms.BaseForms.WrapperActionArgs e)
        {
            switch (e.Action)
            {
                case PKStudio.Tree.NodeAction.Build:
                    this.Build(e.Wrapper, "Build");
                    break;
                case PKStudio.Tree.NodeAction.Rebuild:
                    this.Build(e.Wrapper, "Rebuild");
                    break;
                default:
                    break;
            }
        }

        delegate void ToolStropMenuItemClickHandler(object sender, EventArgs e);
        private void AddToolStripMenuItem(ToolStripMenuItem MenuItem, string Text, object Tag, ToolStropMenuItemClickHandler ClickHandler)
        {
            AddToolStripMenuItem(MenuItem, Text, Tag, ClickHandler, false);
        }
        private void AddToolStripMenuItem(ToolStripMenuItem MenuItem, string Text, object Tag, ToolStropMenuItemClickHandler ClickHandler, bool AddSeparator)
        {
            ToolStripMenuItem = new ToolStripMenuItem();
            ToolStripMenuItem.Text = Text;
            ToolStripMenuItem.Click += new EventHandler(ClickHandler);
            ToolStripMenuItem.Tag = Tag;
            MenuItem.DropDownItems.Add(ToolStripMenuItem);
            if (AddSeparator) MenuItem.DropDownItems.Add(new ToolStripSeparator());
        }


        void Wrapper_LoadSolutionAsyncCompleteEvent(object sender, PKStudio.PortingKitWrapper.LoadSolutionAsyncCompletedEventArgs e)
        {
            mSolutionExplorer.Show(dockPanel1, DockState.DockLeft);


            uVisionProjectGenerationToolStripMenuItem.Visible = true;

            buildToolStripMenuItem1.DropDownItems.Clear();
            rebuildToolStripMenuItem.DropDownItems.Clear();

            //BuildAllItem
            AddToolStripMenuItem(buildToolStripMenuItem1, "All Projects", "Build", BuildAllItem_Click, true);

            //BuildLocalAllItem
            AddToolStripMenuItem(buildLocalToolStripMenuItem, "All Projects", "BuildLocal", BuildAllItem_Click, true);

            //FastBuildAllItem
            AddToolStripMenuItem(fastBuildToolStripMenuItem, "All Projects", "FastBuild", BuildAllItem_Click, true);

            //ReBuildAllItem
            AddToolStripMenuItem(rebuildToolStripMenuItem, "All Projects", "Rebuild", BuildAllItem_Click, true);

            foreach (ProjectWrapper proj in e.Solution.Projects)
            {

                //BuildItem
                AddToolStripMenuItem(buildToolStripMenuItem1, proj.Name, proj, BuildItem_Click);

                //BuildLocalItem
                AddToolStripMenuItem(buildLocalToolStripMenuItem, proj.Name, proj, BuildLocalItem_Click);

                //FastBuildItem
                AddToolStripMenuItem(fastBuildToolStripMenuItem, proj.Name, proj, FastBuildItem_Click);

                //ReBuildItem
                AddToolStripMenuItem(rebuildToolStripMenuItem, proj.Name, proj, ReBuildItem_Click);
            }

            buildToolStripMenuItem.Visible = true;

            BuildTypeCB.Items.Clear();
            BuildTypeCB.Items.Add("Debug");
            BuildTypeCB.Items.Add("Release");
            BuildTypeCB.Items.Add("RTM");
            BuildTypeCB.SelectedIndex = 0;
            BuildTypeCB.Visible = true;

            BuildMediaTypeCB.Items.Clear();
            BuildMediaTypeCB.Items.Add("FLASH");
            BuildMediaTypeCB.Items.Add("RAM");
            BuildMediaTypeCB.SelectedIndex = 0;
            BuildMediaTypeCB.Visible = true;

            BuildToolStripSeparator.Visible = true;

            mOutputForm.ClearAll();
            mErrorListForm.ClearAll();
        }

        #region Build

        void Logger_LogStartedEvent(object sender, EventArgs e)
        {
            SetProgressLabelText(Strings.BuildProgress);
            EnableToolStripControl(toolStrip1, BuildTypeCB, false);
            EnableToolStripControl(toolStrip1, BuildMediaTypeCB, false);
            EnableMenuStripItem(menuStrip1, buildToolStripMenuItem, false);
            EnableMenuStripItem(menuStrip1, solutionToolStripMenuItem, false);
            this.SetProgressBarParams(ProgressBar, 0, 1000, 1);
            this.SetProgressBarValue(ProgressBar, 0);
            this.SetProgressBarVisible(ProgressBar, true);
        }

        void MSBuildLogger_BuildStepEvent(object sender, EventArgs e)
        {
            this.ProgressBarPerformStep(ProgressBar);
        }

        void Logger_LogFinishedEvent(object sender, LogFinishedEventArgs e)
        {
            SetProgressLabelText(Strings.Ready);
            EnableToolStripControl(toolStrip1, BuildTypeCB, true);
            EnableToolStripControl(toolStrip1, BuildMediaTypeCB, true);
            EnableMenuStripItem(menuStrip1, buildToolStripMenuItem, true);
            EnableMenuStripItem(menuStrip1, solutionToolStripMenuItem, true);
            this.SetProgressBarValue(ProgressBar, ProgressBar.Maximum);
            this.SetProgressBarVisible(ProgressBar, false);
            this.SetProgressBarParams(ProgressBar, 0, 100, 1);
        }

        private void Build(BaseWrapper wrapper, string target)
        {
            if (wrapper is SolutionWrapper)
            {
                this.Build(wrapper as SolutionWrapper, target);
            }
            else if (wrapper is ProjectWrapper)
            {
                this.Build(wrapper as ProjectWrapper, target);
            }
            else
                Debug.Assert(false);
        }

        private void Build(SolutionWrapper solution, string target)
        {
            this.Build(PK.Wrapper.ExpandEnvVars(Path.GetDirectoryName(solution.ProjectPath) + "\\dotnetmf.proj", ""), target);
        }

        private void Build(ProjectWrapper project, string target)
        {
            this.Build(PK.Wrapper.ExpandEnvVars(project.ProjectPath, ""), target);
        }

        private void Build(string Path, string target)
        {
            mEditorsController.SaveAllModifiedEditors();
            mOutputForm.Show(dockPanel1);
            mOutputForm.Focus();

            mMSBuildHelper.Build(Path, target, BuildTypeCB.Text, BuildMediaTypeCB.Text);
        }

        void BuildAllItem_Click(object sender, EventArgs e)
        {
            string s = ((ToolStripMenuItem)sender).Tag.ToString();
            this.Build(PK.Wrapper.Solution, s);
        }

        void BuildItem_Click(object sender, EventArgs e)
        {
            ProjectWrapper proj = (ProjectWrapper)((ToolStripMenuItem)sender).Tag;
            Debug.Assert(proj != null);
            this.Build(proj, "Build");
        }

        void BuildLocalItem_Click(object sender, EventArgs e)
        {
            ProjectWrapper proj = (ProjectWrapper)((ToolStripMenuItem)sender).Tag;
            Debug.Assert(proj != null);
            this.Build(proj, "BuildLocal");
        }

        void FastBuildItem_Click(object sender, EventArgs e)
        {
            ProjectWrapper proj = (ProjectWrapper)((ToolStripMenuItem)sender).Tag;
            Debug.Assert(proj != null);
            this.Build(proj, "FastBuild");
        }

        void ReBuildItem_Click(object sender, EventArgs e)
        {
            ProjectWrapper proj = (ProjectWrapper)((ToolStripMenuItem)sender).Tag;
            Debug.Assert(proj != null);
            this.Build(proj, "Rebuild");
        }
        #endregion Build


        void OnShowReferencesDiagramEvent(object sender, PKStudio.Forms.BaseForms.ObjectEventArgs e)
        {
            mComponentReferencesDiagramForm.SetObject(e.Object);
            mComponentReferencesDiagramForm.Show(dockPanel1);
        }

        void OnSelectionChangedEvent(object sender, PKStudio.Forms.BaseForms.ObjectEventArgs e)
        {
            mProperties.SetObject(e.Object);
        }

        void PKWrapper_SearchComplitedEvent(object sender, PKStudio.PortingKitWrapper.SearchComplitedEventArgs e)
        {
            mFindResultsForm.Show(dockPanel1);
            ProgressBar.Value = 100;
            SetProgressLabelText(Strings.Ready);
        }

        void OnGenerateEvent(object sender, PKStudio.Forms.BaseForms.GenerateEventArgs e)
        {
            switch (e.Type)
            {
                case PKStudio.Forms.BaseForms.GenerateTypes.KeilProject:
                    //mKeilGeneratorTool.SetProject((MFSolution)obj);
                    //mKeilGeneratorTool.Show(dockPanel1, DockState.Document);
                    break;
                default:
                    break;
            }
        }

        void OnEditEvent(object sender, PKStudio.Forms.BaseForms.ObjectEventArgs e)
        {
            if (e.Object is ComponentWrapper)
            {
                ComponentWrapper comp = (ComponentWrapper)e.Object;
                OpenComponentEditor(comp);
            }
            else if (e.Object is PortingKitWrapper.SearchResultsHolder.ComponentDescriptor)
            {
                PortingKitWrapper.SearchResultsHolder.ComponentDescriptor compDesc = (PortingKitWrapper.SearchResultsHolder.ComponentDescriptor)e.Object;

                if (compDesc.File != null)
                {
                    if ((compDesc.Parent.Parent == null))   //En: have received file and library that contains it. Ru: получены файл и библиотека его содержащая
                    {
                        mLibrariesExplorer.SetSelectedComponent(compDesc.Parent.Component, compDesc.File);
                        mLibrariesExplorer.Show(dockPanel1);
                    }
                    else //En: Library have Parent - it's Project. Ru: У Library есть Parent - проект
                    {
                        mSolutionExplorer.SetSelectedComponent(compDesc.File);
                        mSolutionExplorer.Show(dockPanel1);
                    }
                    if (compDesc.Line != null)
                    {
                        PKStudio.Helpers.EditorsFormsController.EditFileDescriptor desc = new EditorsFormsController.EditFileDescriptor();
                        desc.Path = compDesc.File.FullPath;
                        desc.Line = compDesc.Line.Num;
                        mEditorsController.ShowEditor(desc);
                    }
                }
                if (compDesc.Component != null)
                {
                    if (compDesc.Parent != null)
                    {
                        mSolutionExplorer.SetSelectedComponent(compDesc.Parent.Component, compDesc.Component);
                        mSolutionExplorer.Show(dockPanel1);
                    }
                    else
                    {
                        OpenComponentEditor(compDesc.Component);
                    }
                }
            }
            else
            {
                mEditorsController.ShowEditor(e.Object);
                //mLibrariesExplorer.SetSelectedComponent(e.Object);
            }
        }

        private void OpenComponentEditor(ComponentWrapper comp)
        {
            switch (comp.ComponentType)
            {
                case ComponentTypeWrapper.Library:
                    if (PK.Wrapper.Solution != null)
                    {
                        LibraryWrapper LW = PK.Wrapper.FindLibrary(comp);
                        if ((LW != null) && (!PK.Wrapper.Solution.IsReference(LW)))
                        {
                            mSolutionExplorer.Show(dockPanel1);
                            mSolutionExplorer.SetSelectedComponent(comp);
                        }
                        else
                        {
                            mLibrariesExplorer.Show(dockPanel1);
                            mLibrariesExplorer.SetSelectedComponent(comp);
                        }
                    }
                    else
                    {
                        mLibrariesExplorer.Show(dockPanel1);
                        mLibrariesExplorer.SetSelectedComponent(comp);
                    }
                    break;
                case ComponentTypeWrapper.Feature:
                    mFeaturesExplorer.Show(dockPanel1);
                    mFeaturesExplorer.SetSelectedComponent(comp);
                    break;
                case ComponentTypeWrapper.LibraryCategory:
                    mLibraryCategoriesExplorer.Show(dockPanel1);
                    mLibraryCategoriesExplorer.SetSelectedComponent(comp);
                    break;
                case ComponentTypeWrapper.MFAssembly:
                    mAssembliesExplorer.Show(dockPanel1);
                    mAssembliesExplorer.SetSelectedComponent(comp);
                    break;
                case ComponentTypeWrapper.MFSolution:
                case ComponentTypeWrapper.Processor:
                case ComponentTypeWrapper.OperatingSystem:
                case ComponentTypeWrapper.BuildTool:
                case ComponentTypeWrapper.ISA:
                case ComponentTypeWrapper.BuildParameter:
                case ComponentTypeWrapper.Unknown:
                default:
                    //mEditorsController.ShowEditor(e.Object);
                    break;
            }
        }

        void OnShowPropertiesEvent(object sender, PKStudio.Forms.BaseForms.ObjectEventArgs e)
        {
            mProperties.SetObject(e.Object);
            mProperties.Show(dockPanel1);
        }

        void explorer_OpenContainingFolderEvent(object sender, Forms.BaseForms.PathEventArgs e)
        {
            if (string.IsNullOrEmpty(e.Path)) return;
            string path = PK.Wrapper.ExpandEnvVars(e.Path, "");
            if (File.Exists(Path.GetFullPath(path)))
            {
                System.Diagnostics.Process.Start("explorer.exe", "/select, \"" + Path.GetFullPath(path) + "\"");
            }
        }

        void m_worker_ProgressChanged(object sender, ProgressChangedEventArgs e)
        {
            ProgressBar.Value = e.ProgressPercentage;
            SetProgressLabelText(e.UserState.ToString());
            if (e.ProgressPercentage < 100) this.SetProgressBarVisible(ProgressBar, true);
            else this.SetProgressBarVisible(ProgressBar, false);
        }



        #region DockHelpers
        private IDockContent GetContentFromPersistString(string persistString)
        {
            if (persistString == typeof(Forms.Explorers.SolutionExplorer).ToString())
                return mSolutionExplorer;
            else if (persistString == typeof(Forms.Properties).ToString())
                return mProperties;
            else if (persistString == typeof(Forms.Explorers.LibraryCategoriesExplorer).ToString())
                return mLibraryCategoriesExplorer;
            else if (persistString == typeof(Forms.Explorers.FeaturesExplorer).ToString())
                return mFeaturesExplorer;
            else if (persistString == typeof(Forms.Explorers.LibrariesExplorer).ToString())
                return mLibrariesExplorer;
            else if (persistString == typeof(Forms.Explorers.ProcessorExplorer).ToString())
                return mProcessorsExplorer;
            else if (persistString == typeof(Forms.Explorers.AssembliesExplorer).ToString())
                return mAssembliesExplorer;
            else if (persistString == typeof(Forms.Tools.FindComponentForm).ToString())
                return mFindComponentForm;
            else if (persistString == typeof(Forms.Tools.FindResultsForm).ToString())
                return mFindResultsForm;
            else if (persistString == typeof(PKStudio.Forms.Output.OutputForm).ToString())
                return mOutputForm;
            else if (persistString == typeof(PKStudio.Forms.Output.ErrorListForm).ToString())
                return mErrorListForm;

            //else if (persistString == typeof(Forms.Tools.ComponentReferencesDiagramForm).ToString())
            //    return mComponentReferencesDiagramForm;
            else
            {
                return null;
            }
        }

        /// <summary>
        /// En: Save forms configuration
        /// Ru: Сохраняет текущее формы
        /// </summary>
        private void SaveState()
        {
            string docksPath = Application.StartupPath + "\\Docks.xml";

            if (File.Exists(docksPath))
            {
                FileInfo FI = new FileInfo(docksPath);

                if ((FI.Attributes & FileAttributes.ReadOnly) == FileAttributes.ReadOnly)
                {
                    FI.Attributes -= FileAttributes.ReadOnly;

                    dockPanel1.SaveAsXml(docksPath);
                }
                else
                {
                    dockPanel1.SaveAsXml(docksPath);
                }
            }
            else
            {
                dockPanel1.SaveAsXml(docksPath);
            }

            mEditorsController.SaveEditorsFormsState();

        }

        /// <summary>
        /// En: Load forms configuration
        /// Ru: Загружает состояние формы
        /// </summary>
        private void LoadState()
        {
            //en: Load main window configuration
            //ru: Загрузка Основных окон
            m_deserializeDockContent = new DeserializeDockContent(GetContentFromPersistString);
            if (File.Exists(Application.StartupPath + "\\Docks.xml"))
            {
                try
                {
                    dockPanel1.LoadFromXml(Application.StartupPath + "\\Docks.xml", m_deserializeDockContent);
                }
                catch (Exception)
                {
                    File.Delete(Application.StartupPath + "\\Docks.xml");

                }
            }
            else
            {
                mSolutionExplorer.Show(dockPanel1, DockState.DockLeft);
                mProperties.Show(dockPanel1, DockState.DockRight);
            }

            //en: attach forms to dockPanel for avoid cross-thread exception. TODO: Find another way
            //ru: Принудительно цепляем формы к dockPanel для того чтобы избежать Exeption из-за кросс-потоковости
            mOutputForm.Show(dockPanel1);
            //mOutputForm.Hide();
            mErrorListForm.Show(dockPanel1, DockState.DockBottom);
            //mErrorListForm.Hide();

            mEditorsController.LoadEditorFormsState();
        }

        #endregion


        private void MainFormNew_Load(object sender, EventArgs e)
        {
            if (mApplicationLoading.ShowDialog(this) != System.Windows.Forms.DialogResult.OK)
            {
                this.Close();
            }

            LoadState();

            CheckSaveButtonToolTip();
        }



        private void MainFormNew_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (mEditorsController.CheckModified())
            {
                using (PKStudio.Dialogs.SaveChangesDialog SCDlg = new Dialogs.SaveChangesDialog())
                {
                    DialogResult res = SCDlg.ShowDialog(this, mEditorsController.ModifiedComponents);

                    switch (res)
                    {
                        case DialogResult.Cancel:
                            e.Cancel = true;
                            break;
                        case DialogResult.No:
                            SaveState();
                            break;
                        case DialogResult.Yes:
                            mEditorsController.SaveAllModifiedEditors();
                            SaveState();
                            break;
                        default:
                            SaveState();
                            break;
                    }
                }
            }
            else
                SaveState();
        }

        #region Menu Handlers

        private void solutionToolStripMenuItem_Click(object sender, EventArgs e)
        {
            using (Dialogs.OpenSolutionDialog os = new Dialogs.OpenSolutionDialog())
            {
                if (os.ShowDialog(this) == System.Windows.Forms.DialogResult.OK)
                {
                    if (os.SelectedSolution != null)
                    {
                        //mSolutionExplorer.UpdateTree(os.SelectedSolution);
                        PK.Wrapper.LoadSolutionAsync(os.SelectedSolution);
                    }
                }
            }
        }

        private void propertiesWindowToolStripMenuItem_Click(object sender, EventArgs e)
        {
            mProperties.Show(dockPanel1);
        }

        private void libraryCategoriesExplorerToolStripMenuItem_Click(object sender, EventArgs e)
        {
            mLibraryCategoriesExplorer.Show(dockPanel1);
        }

        private void featuresExplorerToolStripMenuItem_Click(object sender, EventArgs e)
        {
            mFeaturesExplorer.Show(dockPanel1);
        }

        private void libraryExplorerToolStripMenuItem_Click(object sender, EventArgs e)
        {
            mLibrariesExplorer.Show(dockPanel1);
        }

        private void findResiltsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            mFindResultsForm.Show(dockPanel1);
        }

        private void findComponentToolStripMenuItem_Click(object sender, EventArgs e)
        {
            mFindComponentForm.Show(dockPanel1);
        }
        private void solutionTreeToolStripMenuItem_Click(object sender, EventArgs e)
        {
            mSolutionExplorer.Show(dockPanel1);
        }

        private void processorsExplorerToolStripMenuItem_Click(object sender, EventArgs e)
        {
            mProcessorsExplorer.Show(dockPanel1);
        }


        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void aboutToolStripMenuItem_Click(object sender, EventArgs e)
        {
            mAboutDialog = new Dialogs.AboutDialog();
            mAboutDialog.ShowDialog(this);
        }

        private void outputToolStripMenuItem_Click(object sender, EventArgs e)
        {
            mOutputForm.Show(dockPanel1);
        }

        private void errorListToolStripMenuItem_Click(object sender, EventArgs e)
        {
            mErrorListForm.Show(dockPanel1);
        }

        #endregion

        private void FindStripButton_Click(object sender, EventArgs e)
        {
            mFindComponentForm.Show(dockPanel1);
        }
        private void SaveAllToolStripButton_Click(object sender, EventArgs e)
        {
            mEditorsController.SaveAllModifiedEditors();
        }

        private void SaveToolStripButton_Click(object sender, EventArgs e)
        {
            mEditorsController.SaveActiveEditor();
        }

        private void dockPanel1_ActiveContentChanged(object sender, EventArgs e)
        {
            CheckSaveButtonToolTip();
        }

        #region Helpers

        private void CheckSaveButtonToolTip()
        {
            if (!string.IsNullOrEmpty(mEditorsController.ActivedEditorName))
            {
                SaveToolStripButton.ToolTipText = Strings.Save + " " + mEditorsController.ActivedEditorName;
                SaveToolStripButton.Enabled = true;
            }
            else
            {
                SaveToolStripButton.Enabled = false;
                SaveToolStripButton.ToolTipText = "";
            }
        }

        private delegate void EnableToolStripControlCallback(ToolStrip toolstrip, ToolStripComboBox cb, bool enable);
        private void EnableToolStripControl(ToolStrip toolstrip, ToolStripComboBox cb, bool enable)
        {
            if (toolstrip.InvokeRequired)
            {
                EnableToolStripControlCallback d = new EnableToolStripControlCallback(EnableToolStripControl);
                toolstrip.BeginInvoke(d, new object[] { toolstrip, cb, enable });
            }
            else
            {
                cb.Enabled = enable;
            }
        }

        private delegate void EnableMenuStripItemCallback(MenuStrip menustrip, ToolStripMenuItem menu, bool enable);
        private void EnableMenuStripItem(MenuStrip menustrip, ToolStripMenuItem menu, bool enable)
        {
            if (menustrip.InvokeRequired)
            {
                EnableMenuStripItemCallback d = new EnableMenuStripItemCallback(EnableMenuStripItem);
                menustrip.BeginInvoke(d, new object[] { menustrip, menu, enable });
            }
            else
            {
                menu.Enabled = enable;
            }
        }

        private delegate void SetProgressLabelTextCallback(string text);
        private void SetProgressLabelText(string text)
        {
            if (this.statusStrip1.InvokeRequired)
            {
                SetProgressLabelTextCallback d = new SetProgressLabelTextCallback(SetProgressLabelText);
                statusStrip1.BeginInvoke(d, new object[] { text });
            }
            else
            {
                this.ProgressLabel.Text = text;
            }
        }

        private delegate void ProgressBarPerformStepCallback(ToolStripProgressBar pb);
        private void ProgressBarPerformStep(ToolStripProgressBar pb)
        {
            // InvokeRequired required compares the thread ID of the
            // calling thread to the thread ID of the creating thread.
            // If these threads are different, it returns true.
            if (statusStrip1.InvokeRequired)
            {
                ProgressBarPerformStepCallback d = new ProgressBarPerformStepCallback(ProgressBarPerformStep);
                statusStrip1.BeginInvoke(d, new object[] { pb });
            }
            else
            {
                if (pb.Value == pb.Maximum)
                    ProgressBarFillTimes++;

                if (ProgressBarFillTimes == 100)
                {
                    pb.Value = pb.Minimum;
                    ProgressBarFillTimes = 0;
                }
                pb.PerformStep();
            }
        }

        private delegate void SetProgressBarValueCallback(ToolStripProgressBar pb, int value);
        private void SetProgressBarValue(ToolStripProgressBar pb, int value)
        {
            // InvokeRequired required compares the thread ID of the
            // calling thread to the thread ID of the creating thread.
            // If these threads are different, it returns true.
            if (statusStrip1.InvokeRequired)
            {
                SetProgressBarValueCallback d = new SetProgressBarValueCallback(SetProgressBarValue);
                statusStrip1.BeginInvoke(d, new object[] { pb, value });
            }
            else
            {
                pb.Value = value;
            }
        }

        private delegate void SetProgressBarVisibleCallback(ToolStripProgressBar pb, bool value);
        private void SetProgressBarVisible(ToolStripProgressBar pb, bool value)
        {
            // InvokeRequired required compares the thread ID of the
            // calling thread to the thread ID of the creating thread.
            // If these threads are different, it returns true.
            if (statusStrip1.InvokeRequired)
            {
                SetProgressBarVisibleCallback d = new SetProgressBarVisibleCallback(SetProgressBarVisible);
                statusStrip1.BeginInvoke(d, new object[] { pb, value });
            }
            else
            {
                pb.Visible = value;
            }
        }

        private delegate void SetProgressBarParamsCallback(ToolStripProgressBar pb, int minimum, int maximum, int step);
        private void SetProgressBarParams(ToolStripProgressBar pb, int minimum, int maximum, int step)
        {
            // InvokeRequired required compares the thread ID of the
            // calling thread to the thread ID of the creating thread.
            // If these threads are different, it returns true.
            if (statusStrip1.InvokeRequired)
            {
                SetProgressBarParamsCallback d = new SetProgressBarParamsCallback(SetProgressBarParams);
                statusStrip1.BeginInvoke(d, new object[] { pb, minimum, maximum, step });
            }
            else
            {
                ProgressBarFillTimes = 0;
                pb.Minimum = minimum;
                pb.Maximum = maximum;
                pb.Step = step;
            }
        }

        #endregion

        private void uVisionProjectGenerationToolStripMenuItem_Click(object sender, EventArgs e)
        {
            mKeilGeneratorTool = new Tools.uVisionGenerator.Wizard.uVisionProjectGeneratorWizard();
            mKeilGeneratorTool.SetSolution(PK.Wrapper.Solution);
            mKeilGeneratorTool.Show();
        }

        private void verifyToolStripMenuItem_Click(object sender, EventArgs e)
        {
            mVereficationHelper.Verify();
        }

        private void verifyToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            mVereficationHelper.Verify();
        }

        private void assembliesExplorerToolStripMenuItem_Click(object sender, EventArgs e)
        {
            mAssembliesExplorer.Show(dockPanel1);
        }

        private void solutionToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            using (PKStudio.Dialogs.ManageProjectWizard.NewSolutionWizard mNewSolutionWizard = new Dialogs.ManageProjectWizard.NewSolutionWizard())
            {
                mNewSolutionWizard.ShowDialog(this);
            }
        }

        private void optionsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            PKStudio.Forms.Options.PKOptions mOptionsForm = new Forms.Options.PKOptions();

            mOptionsForm.ShowDialog(this);
            mOptionsForm.Focus();
        }

        private void MainForm_Shown(object sender, EventArgs e)
        {
            PKStudio.Forms.Options.PKOptions mOptionsForm = new Forms.Options.PKOptions();

            if (!mOptionsForm.OptionsLoaded)
            {
                mOptionsForm.ShowDialog(this);
                mOptionsForm.Focus();
            }
        }
    }
}
