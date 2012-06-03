using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using PKStudio.ItemWrappers;
using System.Collections.ObjectModel;
using System.ComponentModel;

namespace PKStudio.Helpers
{
    public class VerificationHelper : ILoggable, IDisposable
    {
        private int ComponentsChecked = 0;

        private BackgroundWorker m_worker = null;


        public VerificationHelper()
        {
            this.m_worker = new BackgroundWorker();
            this.m_worker.DoWork += new DoWorkEventHandler(m_worker_DoWork);
        }

        void m_worker_DoWork(object sender, DoWorkEventArgs e)
        {
            this.OnLogStarted();
            this.OnMessage("Running Verification...\r\n\r\n");
            VerifyGUID();
            VerifyComponents();
            VerifyStubs();
            this.OnMessage("Verification Complete -- " + mEWList.ErrorsCount + " error(s), " + mEWList.WarningsCount + " warning(s)\r\n");
            this.OnLogFinished(mEWList);
        }

        public void Verify()
        {
            mEWList.ClearAll();
            m_worker.RunWorkerAsync();
        }

        private void VerifyGUID()
        {
            this.OnMessage("Running GUIDs Verification...\r\n");
            List<ComponentWrapper> CheckList = new List<ComponentWrapper>();

            LibraryWrapper[] LWS = PK.Wrapper.GetLibraries();
            foreach (LibraryWrapper LW in LWS)
            {
                CheckList.Add(ComponentWrapper.GetComponentWrapper(LW));
            }

            FeatureWrapper[] FWS = PK.Wrapper.GetFeatures();
            foreach (FeatureWrapper FW in FWS)
            {
                CheckList.Add(ComponentWrapper.GetComponentWrapper(FW));
            }

            AssemblyWrapper[] AWS = PK.Wrapper.GetAssembies();
            foreach (AssemblyWrapper AW in AWS)
            {
                CheckList.Add(ComponentWrapper.GetComponentWrapper(AW));
            }

            ProcessorWrapper[] PWS = PK.Wrapper.GetProcessors();
            foreach (ProcessorWrapper PW in PWS)
            {
                CheckList.Add(ComponentWrapper.GetComponentWrapper(PW));
            }

            BuildToolWrapper_[] BTWS = PK.Wrapper.GetBuildTools();
            foreach (BuildToolWrapper_ BTW in BTWS)
            {
                CheckList.Add(ComponentWrapper.GetComponentWrapper(BTW));
            }

            ISAWrapper[] IWS = PK.Wrapper.GetISAs();
            foreach (ISAWrapper IW in IWS)
            {
                CheckList.Add(ComponentWrapper.GetComponentWrapper(IW));
            }

            //   case ComponentTypeWrapper.BuildParameter:

            LibraryCategoryWrapper[] LCWS = PK.Wrapper.GetLibraryCategories();
            foreach (LibraryCategoryWrapper LCW in LCWS)
            {
                CheckList.Add(ComponentWrapper.GetComponentWrapper(LCW));
            }

            if (PK.Wrapper.Solution != null)
            {
                CheckList.Add(ComponentWrapper.GetComponentWrapper(PK.Wrapper.Solution));

                foreach (ProjectWrapper PW in PK.Wrapper.Solution.Projects)
                {
                    CheckList.Add(ComponentWrapper.GetComponentWrapper(PW));
                }
            }


            foreach (ComponentWrapper w1 in CheckList)
            {
                foreach (ComponentWrapper w2 in CheckList)
                {
                    if (w1 != w2)
                    {
                        if (string.Compare(w1.Guid, w2.Guid, true) == 0)
                        {
                            WEMessage message = new WEMessage();
                            message.Message = GetStringByComponentType(w1.ComponentType) + " \"" + w1.Name + "\" have same GUID as " + GetStringByComponentType(w2.ComponentType) + " \"" + w2.Name + "\"";
                            this.OnWarning(message);
                        }
                    }
                }
            }

            this.OnMessage("Verified " + CheckList.Count + " object(s).\r\n\r\n");
        }

        private void VerifyComponents()
        {
            this.OnMessage("Running Components Verification...\r\n");

            ComponentsChecked = 0;

            FeatureWrapper[] FWS = PK.Wrapper.GetFeatures();
            foreach (FeatureWrapper FW in FWS)
            {
                ComponentWrapper OwnerComponent = ComponentWrapper.GetComponentWrapper(FW);
                string text = "Feature \"" + FW.Name + "\" Assemblies: ";
                foreach (ComponentWrapper item in FW.Assemblies)
                {
                    CheckComponent(OwnerComponent, text, item);
                }
                text = "Feature \"" + FW.Name + "\" Component Dependencies: ";
                foreach (ComponentWrapper item in FW.ComponentDependencies)
                {
                    CheckComponent(OwnerComponent, text, item);
                }
                text = "Feature \"" + FW.Name + "\" Feature Dependencies: ";
                foreach (ComponentWrapper item in FW.FeatureDependencies)
                {
                    CheckComponent(OwnerComponent, text, item);
                }
            }

            LibraryWrapper[] LWS = PK.Wrapper.GetLibraries();
            foreach (LibraryWrapper LW in LWS)
            {
                ComponentWrapper OwnerComponent = ComponentWrapper.GetComponentWrapper(LW);
                string text = "Library \"" + LW.Name + "\" Dependencies: ";
                foreach (ComponentWrapper item in LW.Dependencies)
                {
                    CheckComponent(OwnerComponent, text, item);
                }
                if (LW.ISASpecific != null)
                {
                    text = "Library \"" + LW.Name + "\" ISASpecific: ";
                    CheckComponent(OwnerComponent, text, LW.ISASpecific);
                }

                if (LW.LibraryCategory != null)
                {
                    text = "Library \"" + LW.Name + "\" LibraryCategory: ";
                    CheckComponent(OwnerComponent, text, LW.LibraryCategory);
                }

                if (LW.ProcessorSpecific != null)
                {
                    text = "Library \"" + LW.Name + "\" ProcessorSpecific: ";
                    CheckComponent(OwnerComponent, text, LW.ProcessorSpecific);
                }
            }

            LibraryCategoryWrapper[] LCWS = PK.Wrapper.GetLibraryCategories();
            foreach (LibraryCategoryWrapper LCW in LCWS)
            {
                ComponentWrapper OwnerComponent = ComponentWrapper.GetComponentWrapper(LCW);
                string text = "Library Category \"" + LCW.Name + "\" FeatureAssociations: ";
                foreach (ComponentWrapper item in LCW.FeatureAssociations)
                {
                    CheckComponent(OwnerComponent, text, item);
                }
                if (LCW.StubLibrary != null)
                {
                    text = "Library Category \"" + LCW.Name + "\" StubLibrary: ";
                    CheckComponent(OwnerComponent, text, LCW.StubLibrary);
                }
            }

            AssemblyWrapper[] AWS = PK.Wrapper.GetAssembies();
            foreach (AssemblyWrapper AW in AWS)
            {
                ComponentWrapper OwnerComponent = ComponentWrapper.GetComponentWrapper(AW);
                string text = "Assembly \"" + AW.Name + "\" References: ";
                foreach (ComponentWrapper item in AW.References)
                {
                    CheckComponent(OwnerComponent, text, item);
                }
            }

            ProcessorWrapper[] PWS = PK.Wrapper.GetProcessors();
            foreach (ProcessorWrapper PW in PWS)
            {
                ComponentWrapper OwnerComponent = ComponentWrapper.GetComponentWrapper(PW);
                string text = "Processor \"" + PW.Name + "\" SupportedISAs: ";
                foreach (ComponentWrapper item in PW.SupportedISAs)
                {
                    CheckComponent(OwnerComponent, text, item);
                }
            }

            if (PK.Wrapper.Solution != null)
            {
                ComponentWrapper OwnerComponent = ComponentWrapper.GetComponentWrapper(PK.Wrapper.Solution);
                if (PK.Wrapper.Solution.DefaultISA != null)
                {
                    string text = "Solution \"" + PK.Wrapper.Solution.Name + "\" Default ISA: ";
                    CheckComponent(OwnerComponent, text, PK.Wrapper.Solution.DefaultISA);
                }

                if (PK.Wrapper.Solution.Processor != null)
                {
                    string text = "Solution \"" + PK.Wrapper.Solution.Name + "\" Processor: ";
                    CheckComponent(OwnerComponent, text, PK.Wrapper.Solution.Processor);
                }

                foreach (ProjectWrapper PW in PK.Wrapper.Solution.Projects)
                {
                    string text = "Project \"" + PW.Name + "\" Features: ";
                    foreach (ComponentWrapper item in PW.Features)
                    {
                        CheckComponent(OwnerComponent, text, item);
                    }

                    text = "Project \"" + PW.Name + "\" LibraryCategories: ";
                    foreach (ComponentWrapper item in PW.LibraryCategories)
                    {
                        CheckComponent(OwnerComponent, text, item);
                    }

                    text = "Project \"" + PW.Name + "\" Libraries: ";
                    foreach (ComponentWrapper item in PW.Libraries)
                    {
                        CheckComponent(OwnerComponent, text, item);
                    }
                }
            }

            this.OnMessage("Verified " + ComponentsChecked + " object(s).\r\n\r\n");
        }

        private void VerifyStubs()
        {
            this.OnMessage("Running Stubs Verification...\r\n");

            List<LibraryWrapper> CheckList = new List<LibraryWrapper>();

            LibraryWrapper[] LWS = PK.Wrapper.GetLibraries();
            foreach (LibraryWrapper LW in LWS)
            {
                if (LW.IsStub)
                    CheckList.Add(LW);
            }

            foreach (LibraryWrapper LW in CheckList)
            {
                ComponentMessageObject CMO = new ComponentMessageObject();
                CMO.Component = ComponentWrapper.GetComponentWrapper(LW);

                if (LW.HasLibraryCategory == false)
                {
                    WEMessage message = new WEMessage();
                    message.Message = "Stub " + GetStringByComponentType(ComponentTypeWrapper.Library) + " \"" + LW.Name + "\" has not have library category";
                    message.MessageObject = CMO;
                    this.OnWarning(message);
                }
                else
                {
                    LibraryCategoryWrapper LCW = PK.Wrapper.FindLibraryCategory(LW.LibraryCategory.Guid);
                    if (string.Compare(LCW.StubLibrary.Guid, LW.Guid, true) != 0)
                    {
                        WEMessage message = new WEMessage();
                        message.Message = "Stub " + GetStringByComponentType(ComponentTypeWrapper.Library) + " \"" + LW.Name + "\": " + GetStringByComponentType(ComponentTypeWrapper.LibraryCategory) + " \"" + LCW.Name + "\" has wrong GUID in it's StubLibrary field";
                        message.MessageObject = CMO;
                        this.OnWarning(message);
                    }

                    if (string.Compare(LCW.StubLibrary.Name, LW.Name, true) != 0)
                    {
                        WEMessage message = new WEMessage();
                        message.Message = "Stub " + GetStringByComponentType(ComponentTypeWrapper.Library) + " \"" + LW.Name + "\": " + GetStringByComponentType(ComponentTypeWrapper.LibraryCategory) + " \"" + LCW.Name + "\" has wrong NAME in it's StubLibrary field";
                        message.MessageObject = CMO;
                        this.OnWarning(message);
                    }

                    if (string.Compare(LCW.StubLibrary.ProjectPath, LW.ProjectPath, true) != 0)
                    {
                        WEMessage message = new WEMessage();
                        message.Message = "Stub " + GetStringByComponentType(ComponentTypeWrapper.Library) + " \"" + LW.Name + "\": " + GetStringByComponentType(ComponentTypeWrapper.LibraryCategory) + " \"" + LCW.Name + "\" has wrong ProjectPath in it's StubLibrary field";
                        message.MessageObject = CMO;
                        this.OnWarning(message);
                    }
                }
            }

            LibraryCategoryWrapper[] LCWS = PK.Wrapper.GetLibraryCategories();
            foreach (LibraryCategoryWrapper LCW in LCWS)
            {
                ComponentMessageObject CMO = new ComponentMessageObject();
                CMO.Component = ComponentWrapper.GetComponentWrapper(LCW);

                if (LCW.StubLibrary.Guid == null)
                {
                    WEMessage message = new WEMessage();
                    message.Message = GetStringByComponentType(ComponentTypeWrapper.LibraryCategory) + " \"" + LCW.Name + "\" has not have stub library";
                    message.MessageObject = CMO;
                    this.OnWarning(message);
                }
                else
                {
                    LibraryWrapper LW = PK.Wrapper.FindLibrary(LCW.StubLibrary.Guid);
                    if (LW == null)
                    {
                        WEMessage message = new WEMessage();
                        message.Message = GetStringByComponentType(ComponentTypeWrapper.LibraryCategory) + " \"" + LCW.Name + "\" Stub Library: Can't find library with GUID";
                        message.MessageObject = CMO;
                        this.OnWarning(message);
                    }
                    else
                    {
                        if (string.Compare(LCW.StubLibrary.Name, LW.Name, true) != 0)
                        {
                            WEMessage message = new WEMessage();
                            message.Message = GetStringByComponentType(ComponentTypeWrapper.LibraryCategory) + " \"" + LCW.Name + "\" Stub Library: Name mismatch. Stub component Name is \"" + LCW.StubLibrary.Name + "\" " + GetStringByComponentType(ComponentTypeWrapper.Library) + " Name is \"" + LW.Name + "\"";
                            message.MessageObject = CMO;
                            this.OnWarning(message);
                        }

                        if (string.Compare(LCW.StubLibrary.ProjectPath, LW.ProjectPath, true) != 0)
                        {
                            WEMessage message = new WEMessage();
                            message.Message = GetStringByComponentType(ComponentTypeWrapper.LibraryCategory) + " \"" + LCW.Name + "\" Stub Library: Project Path mismatch. Stub component Project Path is \"" + LCW.StubLibrary.Name + "\" " + GetStringByComponentType(ComponentTypeWrapper.Library) + " Project Path is \"" + LW.Name + "\"";
                            message.MessageObject = CMO;
                            this.OnWarning(message);
                        }
                    }
                }
            }

            this.OnMessage("Verified " + CheckList.Count + " object(s).\r\n\r\n");
        }

        private string GetStringByComponentType(ComponentTypeWrapper type)
        {

            string result = string.Empty;
            switch (type)
            {
                case ComponentTypeWrapper.Library:
                    result = "Library";
                    break;
                case ComponentTypeWrapper.Feature:
                    result = "Feature";
                    break;
                case ComponentTypeWrapper.MFAssembly:
                    result = "MF Assembly";
                    break;
                case ComponentTypeWrapper.MFSolution:
                    result = "MF Solution";
                    break;
                case ComponentTypeWrapper.Processor:
                    result = "Processor";
                    break;
                case ComponentTypeWrapper.OperatingSystem:
                    result = "Operating System";
                    break;
                case ComponentTypeWrapper.BuildTool:
                    result = "Build Tool";
                    break;
                case ComponentTypeWrapper.ISA:
                    result = "ISA";
                    break;
                case ComponentTypeWrapper.BuildParameter:
                    result = "Build Parameter";
                    break;
                case ComponentTypeWrapper.LibraryCategory:
                    result = "Library Category";
                    break;
                case ComponentTypeWrapper.Unknown:
                    result = "Unknown";
                    break;
                default:
                    result = "Unknown";
                    break;
            }
            return result;
        }

        private void CheckComponent(ComponentWrapper OwnerComponent, string text, ComponentWrapper component)
        {
            ComponentMessageObject CMO = new ComponentMessageObject();
            CMO.Component = OwnerComponent;

            ComponentsChecked++;
            switch (component.ComponentType)
            {
                #region Library
                case ComponentTypeWrapper.Library:
                    if (!CheckComponentGUID(component, text, CMO)) return;

                    LibraryWrapper LW = PK.Wrapper.FindLibrary(component.Guid);
                    if (LW == null)
                    {
                        CanTFindComponentsReference(component, text, CMO);
                        return;
                    }
                    CompareComponentName(component, LW.Name, text, CMO);
                    CompareComponentProjectPath(component, LW.ProjectPath, text, CMO);
                    break;
                #endregion
                #region Feature
                case ComponentTypeWrapper.Feature:
                    if (!CheckComponentGUID(component, text, CMO)) return;

                    FeatureWrapper FW = PK.Wrapper.FindFeature(component.Guid);
                    if (FW == null)
                    {
                        CanTFindComponentsReference(component, text, CMO);
                        return;
                    }
                    CompareComponentName(component, FW.Name, text, CMO);
                    CompareComponentProjectPath(component, FW.ProjectPath, text, CMO);
                    break;
                #endregion
                #region Assembly
                case ComponentTypeWrapper.MFAssembly:
                    if (!CheckComponentGUID(component, text, CMO)) return;

                    AssemblyWrapper AW = PK.Wrapper.FindAssembly(component.Guid);
                    if (AW == null)
                    {
                        CanTFindComponentsReference(component, text, CMO);
                        return;
                    }
                    CompareComponentName(component, AW.Name, text, CMO);
                    CompareComponentProjectPath(component, AW.ProjectPath, text, CMO);
                    break;
                #endregion
                case ComponentTypeWrapper.MFSolution:
                    break;
                #region Processors
                case ComponentTypeWrapper.Processor:
                    if (!CheckComponentGUID(component, text, CMO)) return;

                    ProcessorWrapper PW = PK.Wrapper.FindProcessor(component.Guid);
                    if (PW == null)
                    {
                        CanTFindComponentsReference(component, text, CMO);
                        return;
                    }
                    CompareComponentName(component, PW.Name, text, CMO);
                    CompareComponentProjectPath(component, PW.ProjectPath, text, CMO);
                    break;
                #endregion
                case ComponentTypeWrapper.OperatingSystem:
                    break;
                case ComponentTypeWrapper.BuildTool:
                    break;
                #region ISA
                case ComponentTypeWrapper.ISA:
                    if (!CheckComponentGUID(component, text, CMO)) return;

                    ISAWrapper IW = PK.Wrapper.FindISA(component.Guid);
                    if (IW == null)
                    {
                        CanTFindComponentsReference(component, text, CMO);
                        return;
                    }
                    CompareComponentName(component, IW.Name, text, CMO);
                    break;
                #endregion
                case ComponentTypeWrapper.BuildParameter:
                    break;
                #region LibraryCategory
                case ComponentTypeWrapper.LibraryCategory:
                    if (!CheckComponentGUID(component, text, CMO)) return;

                    LibraryCategoryWrapper LCW = PK.Wrapper.FindLibraryCategory(component.Guid);
                    if (LCW == null)
                    {
                        CanTFindComponentsReference(component, text, CMO);
                        return;
                    }

                    CompareComponentName(component, LCW.Name, text, CMO);

                    CompareComponentProjectPath(component, LCW.ProjectPath, text, CMO);
                    break;
                #endregion
                #region Unknown
                case ComponentTypeWrapper.Unknown:
                    WEMessage UMessage = new WEMessage();
                    UMessage.Message = text + "Component with \"Type\": " + GetStringByComponentType(component.ComponentType);
                    UMessage.MessageObject = CMO;
                    this.OnWarning(UMessage);
                    break;
                #endregion
                default:
                    break;
            }
        }

        private void CompareComponentProjectPath(ComponentWrapper component, string ProjectPath, string text, ComponentMessageObject CMO)
        {
            if (component.Name == "COM_PAL")
            {
            }
            if (string.Compare(component.ProjectPath, ProjectPath, true) != 0)
            {
                WEMessage message = new WEMessage();
                message.Message = text + "Project Path mismatch. Component Project Path: \"" + component.ProjectPath + "\" " + GetStringByComponentType(component.ComponentType) + " Project Path:\"" + ProjectPath + "\"";
                message.MessageObject = CMO;
                this.OnWarning(message);
            }
        }

        private void CompareComponentName(ComponentWrapper component, string Name, string text, ComponentMessageObject CMO)
        {
            if (string.Compare(component.Name, Name, StringComparison.Ordinal) != 0)
            {
                WEMessage message = new WEMessage();
                message.Message = text + "Name mismatch. Component Name: \"" + component.Name + "\" " + GetStringByComponentType(component.ComponentType) + " Name:\"" + Name + "\"";
                message.MessageObject = CMO;
                this.OnWarning(message);
            }
        }

        private void CanTFindComponentsReference(ComponentWrapper component, string text, ComponentMessageObject CMO)
        {
            WEMessage message = new WEMessage();
            message.Message = text + "Can't find " + GetStringByComponentType(component.ComponentType) + " with GUID " + component.Guid;
            message.MessageObject = CMO;
            this.OnWarning(message);
        }

        private bool CheckComponentGUID(ComponentWrapper component, string text, ComponentMessageObject CMO)
        {
            if (string.IsNullOrEmpty(component.Guid))
            {
                if (!string.IsNullOrEmpty(component.Name) || !string.IsNullOrEmpty(component.ProjectPath))
                {
                    WEMessage message = new WEMessage();
                    message.Message = text + "GUID missing in " + GetStringByComponentType(component.ComponentType);
                    message.MessageObject = CMO;
                    this.OnWarning(message);
                }
                return false;
            }
            return true;
        }

        #region ILogger

        private ErrorsAndWarningsList mEWList = new ErrorsAndWarningsList();

        public event EventHandler LogStartedEvent;
        protected void OnLogStarted()
        {
            if (LogStartedEvent != null)
            {
                LogStartedEvent(this, EventArgs.Empty);
            }
        }

        public event EventHandler<LogFinishedEventArgs> LogFinishedEvent;
        protected void OnLogFinished(ErrorsAndWarningsList ErrorsAndWarningsList)
        {
            if (LogFinishedEvent != null)
            {
                LogFinishedEvent(this, new LogFinishedEventArgs(ErrorsAndWarningsList));
            }
        }

        public event EventHandler<MessageEventArgs> MessageEvent;
        protected void OnMessage(string message)
        {
            if (MessageEvent != null)
            {
                MessageEvent(this, new MessageEventArgs(message));
            }
        }

        public event EventHandler<WarningEventArgs> WarningEvent;
        protected void OnWarning(WEMessage Warning)
        {
            if (this.mEWList.AddWarning(Warning))
            {
                if (WarningEvent != null)
                {
                    WarningEvent(this, new WarningEventArgs(Warning));
                }
            }
        }

        public event EventHandler<ErrorEventArgs> ErrorEvent;
        protected void OnError(WEMessage Error)
        {
            if (ErrorEvent != null)
            {
                ErrorEvent(this, new ErrorEventArgs(Error));
            }
        }


        public ErrorsAndWarningsList ErrorsAndWarningsList { get { return mEWList; } }

        #endregion

        #region IDisposable Members

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }


        protected virtual void Dispose(bool disposing)
        {
            if (disposing)
            {
                // free managed resources
                if (m_worker != null)
                {
                    m_worker.Dispose();
                    m_worker = null;
                }
            }
        }
        #endregion
    }
}
