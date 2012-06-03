using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using Microsoft.Build.Construction;
using Microsoft.Build.Evaluation;
using PKParser.Arg;
using PKStudio.ItemWrappers;
using PKStudio.Tools.uVisionGenerator.Classes.HelpClasses.MessagesParsesHelper;
using PKStudio.Tools.uVisionGenerator.Classes.uvProjectClasses;
using PKStudio.Tools.uVisionGenerator.Wizard;

namespace PKStudio.Tools.uVisionGenerator.Classes.HelpClasses
{
    [Serializable]
    public class MessagesParserException : Exception
    {
        public MessagesParserException() { }
        public MessagesParserException(string message) : base(message) { }
        public MessagesParserException(string message, Exception inner) : base(message, inner) { }
        protected MessagesParserException(
          System.Runtime.Serialization.SerializationInfo info,
          System.Runtime.Serialization.StreamingContext context)
            : base(info, context) { }
    }
    class MessagesParser
    {
        //private BackgroundWorker m_worker;

        private SortedList<int, LogQueueItem> LogQueue = new SortedList<int, LogQueueItem>();

        private uVisionProject uVisionProject = null;

        private SortedList<int, ParCollContainer> ARMLink = new SortedList<int, ParCollContainer>();
        private SortedList<int, ParCollContainer> ARMAR = new SortedList<int, ParCollContainer>();
        private SortedList<int, ParCollContainer> ARMCCandARMASM = new SortedList<int, ParCollContainer>();
        //private SortedList<int, ParCollContainer> ARMASM = new SortedList<int, ParCollContainer>();
        private SortedList<int, ParCollContainer> FROMELF = new SortedList<int, ParCollContainer>();

        /// <summary>
        /// uVision project generation path
        /// </summary>
        private string uVisionProjectPath = @"D:\testProject\test";

        private string uVisionTargetsPath = @"targets";

        private string ARMCCPath = string.Empty;
        private string ARMASMPath = string.Empty;
        private string ARMLINKPath = string.Empty;
        private string ARMARPath = string.Empty;
        private string ARMFROMELFPath = string.Empty;

        private int sleeptime = 1000;


        //private class WorkerParams
        //{
        //    public SortedList<int, LogQueueItem> messages { get; set; }
        //    public IDictionary EnvVars { get; set; }
        //}

        public class LogQueueItem
        {
            public LogQueueItem(string Message, string CurrentDir, List<string> ProjectBuildContext)
            {
                this.Message = Message;
                this.CurrentDir = CurrentDir;
                this.ProjectBuildContext = new List<string>(ProjectBuildContext);

            }
            public string Message { get; set; }
            public string CurrentDir { get; set; }
            public List<string> ProjectBuildContext { get; set; }
        }

        private class ParCollContainer
        {
            public ParCollContainer(ParamCollection ParamCollection, string Message, List<string> ProjectBuildContext, string CurrentDir)
            {
                this.ParamCollection = ParamCollection;
                this.Message = Message;
                this.ProjectBuildContext = new List<string>(ProjectBuildContext);
                this.CurrentDir = CurrentDir;
            }
            public ParamCollection ParamCollection { get; set; }
            public string Message { get; set; }
            public List<string> ProjectBuildContext { get; set; }
            public string CurrentDir { get; set; }
        }



        public MessagesParser(uVisionProject UVProject, string path)
        {
            uVisionProject = UVProject;
            uVisionProjectPath = path;

            //this.m_worker = new BackgroundWorker();
            //this.m_worker.DoWork += new DoWorkEventHandler(m_worker_DoWork);
            //this.m_worker.RunWorkerCompleted += new RunWorkerCompletedEventHandler(m_worker_RunWorkerCompleted);
        }

        #region Event



        public delegate void LogEventDelegate(GeneratingLogMessage mess);
        public event LogEventDelegate LogEvent;
        protected void OnLog(GeneratingLogMessage mess)
        {
            if (LogEvent != null)
            {
                LogEvent(mess);
            }
        }
        #endregion

        private void AnalizeInputLibraries(SortedList<int, RequiredLibrary> Libraryes, IList<LogQueueItem> LogMessages)
        {
            //PKParser.Arg.PKArgParser ArgParser = new PKParser.Arg.PKArgParser();
            int index = 0;
            foreach (RequiredLibrary lib in Libraryes.Values)
            {
                index++;
                OnLog(new GeneratingLogMessage(KeilWizardStrings.IDS_ANALYSE_LYBRARIES_LINKS, GeneratingLogMessage.WORK_TYPE.CREATE_PROJECT_TREE, GeneratingLogMessage.WORK_STATE.WORKING, (int)((index * 100) / Libraryes.Values.Count)));

                foreach (ParCollContainer container in ARMAR.Values)
                {
                    ParamCollection par = container.ParamCollection;
                    if (par == null) continue;

                    bool Found = false;

                    foreach (ArgCollection arg in par.Values)
                    {
                        if (arg.Tag == "archive")
                        {
                            if (String.Compare(Path.GetFileName(arg.Name), lib.Name, StringComparison.InvariantCultureIgnoreCase) == 0) Found = true;
                        }
                    }

                    if (!Found) continue;

                    lib.ConsoleString = container.Message;
                    lib.ParamCollection = par;
                    lib.BuildList.AddRange(container.ProjectBuildContext);
                    lib.OutputFileuVision = uVisionProjectPath + "\\" + uVisionTargetsPath + "\\" + Path.GetFileNameWithoutExtension(lib.Name) + "\\" + Path.GetFileName(lib.Name);

                    string LIB_EXT = string.Empty;
                    string OBJ_EXT = string.Empty;

                    using (ProjectCollection LocalProjColl = new ProjectCollection())
                    {
                        Project MSBProj = LocalProjColl.LoadProject(container.ProjectBuildContext[container.ProjectBuildContext.Count - 1]);
                        LIB_EXT = MSBProj.GetPropertyValue("LIB_EXT");
                        OBJ_EXT = MSBProj.GetPropertyValue("OBJ_EXT");
                    }

                    foreach (string file in par.Files.Values)
                    {
                        RequiredLibrary libr = null;
                        RequiredObject obj = null;

                        if (Path.GetExtension(file).ToLower() == "." + LIB_EXT.ToLower())
                        {
                            libr = new RequiredLibrary(file, lib);
                            lib.InputLibraries.Add(lib.InputLibraries.Count + 1, libr);
                        }

                        if (Path.GetExtension(file).ToLower() == "." + OBJ_EXT.ToLower())
                        {
                            obj = new RequiredObject(file, lib);
                            lib.InputObjects.Add(lib.InputObjects.Count + 1, obj);
                        }
                        if (libr != null) lib.AllInputs.Add(lib.AllInputs.Count + 1, libr);
                        if (obj != null) lib.AllInputs.Add(lib.AllInputs.Count + 1, obj);
                    }

                    foreach (ArgCollection arg in par.Values)
                    {
                        switch (arg.Tag)
                        {
                            case "options":
                                if (arg.Count > 0)
                                    foreach (string s in arg)
                                    {
                                        lib.OptionsString.Add(arg.Name + " " + s);
                                    }
                                else
                                    lib.OptionsString.Add(arg.Name);
                                break;
                            case "archive":
                                lib.OutputFileMSBuild = arg.Name;
                                break;
                        }
                    }
                }
                if (lib.InputLibraries.Count > 0) this.AnalizeInputLibraries(lib.InputLibraries, LogMessages);
            }
            OnLog(new GeneratingLogMessage(KeilWizardStrings.IDS_ANALYSE_LYBRARIES_LINKS, GeneratingLogMessage.WORK_TYPE.CREATE_PROJECT_TREE, GeneratingLogMessage.WORK_STATE.WORKING, 100));
            System.Threading.Thread.Sleep(sleeptime);
        }

        private void AnalizeInputObjects(SortedList<int, RequiredObject> Objects)//, IList<LogQueueItem> LogMessages)
        {
            //PKParser.Arg.PKArgParser ArgParser = new PKParser.Arg.PKArgParser();
            int index = 0;

            foreach (RequiredObject obj in Objects.Values)
            {
                index++;
                OnLog(new GeneratingLogMessage(KeilWizardStrings.IDS_ANALYSE_OBJECTS_LINKS, GeneratingLogMessage.WORK_TYPE.CREATE_PROJECT_TREE, GeneratingLogMessage.WORK_STATE.WORKING, (int)((index * 100) / Objects.Values.Count)));

                //foreach (LogQueueItem item in LogMessages)
                //{
                //    string s = ArgParser.GetUtil(item.Message);
                //    if (s == null) continue;
                //    if ((String.Compare(ARMCCPath, s, StringComparison.InvariantCultureIgnoreCase) == 0) || (String.Compare(ARMASMPath, s, StringComparison.InvariantCultureIgnoreCase) == 0))
                //    //if (item.Message.ToLower().Contains(ARMCCPath) || item.Message.ToLower().Contains(ARMASMPath))
                foreach (ParCollContainer container in ARMCCandARMASM.Values)
                {
                    ParamCollection par = container.ParamCollection;
                    if (par == null) continue;

                    bool Found = false;

                    foreach (ArgCollection arg in par.Values)
                    {
                        if (arg.Name == "-o")
                        {
                            if (obj.OutputFileMSBuild != string.Empty)
                            {
                                if (String.Compare(arg[0], obj.OutputFileMSBuild, StringComparison.InvariantCultureIgnoreCase) == 0) Found = true;
                            }
                            else
                            {
                                if (String.Compare(Path.GetFileName(arg[0]), obj.Name, StringComparison.InvariantCultureIgnoreCase) == 0) Found = true;                                
                            }
                        }
                    }

                    if (!Found) continue;

                    obj.ConsoleString = container.Message;
                    obj.CurrentDir = container.CurrentDir;
                    obj.ParamCollection = par;
                    obj.BuildList.AddRange(container.ProjectBuildContext);
                    obj.OutputFileuVision = uVisionProjectPath + "\\" + uVisionTargetsPath + "\\" + Path.GetFileNameWithoutExtension(obj.Name) + "\\" + Path.GetFileNameWithoutExtension(obj.Name) + ".o";

                    obj.InputFiles.AddRange(par.Files.Values);

                }
            }
            OnLog(new GeneratingLogMessage(KeilWizardStrings.IDS_ANALYSE_OBJECTS_LINKS, GeneratingLogMessage.WORK_TYPE.CREATE_PROJECT_TREE, GeneratingLogMessage.WORK_STATE.WORKING, 100));
            System.Threading.Thread.Sleep(sleeptime);
        }

        private void CheckCryptoLib(SortedList<int, RequiredLibrary> Libraryes, IList<LogQueueItem> LogMessages)
        {
            //PKParser.Arg.PKArgParser ArgParser = new PKParser.Arg.PKArgParser();

            foreach (RequiredLibrary lib in Libraryes.Values)
            {
                if (lib.Name.ToLower() == "crypto.lib")
                {
                    if (lib.ParamCollection != null) return;

                    //foreach (LogQueueItem item in LogMessages)
                    //{
                    //    string util = ArgParser.GetUtil(item.Message);
                    //    if (util == null) continue;
                    //    if (String.Compare(ARMARPath, util, StringComparison.InvariantCultureIgnoreCase) == 0)
                    //if (item.Message.ToLower().Contains(ARMARPath))
                    //{
                    //ParamCollection par = ArgParser.Add(item.Message);
                    foreach (ParCollContainer container in ARMAR.Values)
                    {
                        ParamCollection par = container.ParamCollection;
                        if (par == null) continue;

                        bool Found = false;

                        foreach (ArgCollection arg in par.Values)
                        {
                            if (arg.Tag == "archive")
                            {
                                if (Path.GetFileName(arg.Name).ToLower() == "crypto_stub.lib") Found = true;
                            }
                        }

                        if (!Found) continue;

                        lib.ConsoleString = container.Message;
                        lib.ParamCollection = par;
                        lib.BuildList.AddRange(container.ProjectBuildContext);
                        lib.OutputFileuVision = uVisionProjectPath + "\\" + uVisionTargetsPath + "\\" + Path.GetFileNameWithoutExtension(lib.Name) + "\\" + Path.GetFileName(lib.Name);

                        string LIB_EXT = string.Empty;
                        string OBJ_EXT = string.Empty;

                        using (ProjectCollection LocalProjColl = new ProjectCollection())
                        {
                            Project MSBProj = LocalProjColl.LoadProject(container.ProjectBuildContext[container.ProjectBuildContext.Count - 1]);
                            LIB_EXT = MSBProj.GetPropertyValue("LIB_EXT");
                            OBJ_EXT = MSBProj.GetPropertyValue("OBJ_EXT");
                        }


                        foreach (string file in par.Files.Values)
                        {
                            RequiredLibrary libr = null;
                            RequiredObject obj = null;
                            if (Path.GetExtension(file).ToLower() == "." + LIB_EXT.ToLower())
                            {
                                libr = new RequiredLibrary(file, lib);
                                lib.InputLibraries.Add(lib.InputLibraries.Count + 1, libr);
                            }

                            if (Path.GetExtension(file).ToLower() == "." + OBJ_EXT.ToLower())
                            {
                                obj = new RequiredObject(file, lib);
                                lib.InputObjects.Add(lib.InputObjects.Count + 1, obj);
                            }
                            if (libr != null) lib.AllInputs.Add(lib.AllInputs.Count + 1, libr);
                            if (obj != null) lib.AllInputs.Add(lib.AllInputs.Count + 1, obj);
                        }


                        foreach (ArgCollection arg in par.Values)
                        {
                            switch (arg.Tag)
                            {
                                case "options":
                                    if (arg.Count > 0)
                                        foreach (string s in arg)
                                        {
                                            lib.OptionsString.Add(arg.Name + " " + s);
                                        }
                                    else
                                        lib.OptionsString.Add(arg.Name);
                                    break;
                                case "archive":
                                    lib.OutputFileMSBuild = arg.Name;
                                    break;
                            }
                        }
                        //}
                    }
                    if (lib.InputLibraries.Count > 0) this.AnalizeInputLibraries(lib.InputLibraries, LogMessages);
                }
            }
        }


        private void CheckSocketsLibs(SortedList<int, RequiredLibrary> Libraryes, IList<LogQueueItem> LogMessages)
        {
            //PKParser.Arg.PKArgParser ArgParser = new PKParser.Arg.PKArgParser();

            foreach (RequiredLibrary lib in Libraryes.Values)
            {
                #region sockets_hal.lib
                if (lib.Name.ToLower() == "sockets_hal.lib")
                {
                    if (lib.ParamCollection != null) return;

                    //foreach (LogQueueItem item in LogMessages)
                    //{
                    //    string util = ArgParser.GetUtil(item.Message);
                    //    if (util == null) continue;
                    //    if (String.Compare(ARMARPath, util, StringComparison.InvariantCultureIgnoreCase) == 0)
                    //if (item.Message.ToLower().Contains(ARMARPath))
                    //{
                    //ParamCollection par = ArgParser.Add(item.Message);
                    foreach (ParCollContainer container in ARMAR.Values)
                    {
                        ParamCollection par = container.ParamCollection;
                        if (par == null) continue;

                        bool Found = false;

                        foreach (ArgCollection arg in par.Values)
                        {
                            if (arg.Tag == "archive")
                            {
                                if (Path.GetFileName(arg.Name).ToLower() == "sockets_hal_stubs.lib") Found = true;
                            }
                        }

                        if (!Found) continue;

                        lib.ConsoleString = container.Message;
                        lib.ParamCollection = par;
                        lib.BuildList.AddRange(container.ProjectBuildContext);
                        lib.OutputFileuVision = uVisionProjectPath + "\\" + uVisionTargetsPath + "\\" + Path.GetFileNameWithoutExtension(lib.Name) + "\\" + Path.GetFileName(lib.Name);

                        string LIB_EXT = string.Empty;
                        string OBJ_EXT = string.Empty;

                        using (ProjectCollection LocalProjColl = new ProjectCollection())
                        {
                            Project MSBProj = LocalProjColl.LoadProject(container.ProjectBuildContext[container.ProjectBuildContext.Count - 1]);
                            LIB_EXT = MSBProj.GetPropertyValue("LIB_EXT");
                            OBJ_EXT = MSBProj.GetPropertyValue("OBJ_EXT");
                        }


                        foreach (string file in par.Files.Values)
                        {
                            RequiredLibrary libr = null;
                            RequiredObject obj = null;
                            if (Path.GetExtension(file).ToLower() == "." + LIB_EXT.ToLower())
                            {
                                libr = new RequiredLibrary(file, lib);
                                lib.InputLibraries.Add(lib.InputLibraries.Count + 1, libr);
                            }

                            if (Path.GetExtension(file).ToLower() == "." + OBJ_EXT.ToLower())
                            {
                                obj = new RequiredObject(file, lib);
                                lib.InputObjects.Add(lib.InputObjects.Count + 1, obj);
                            }
                            if (libr != null) lib.AllInputs.Add(lib.AllInputs.Count + 1, libr);
                            if (obj != null) lib.AllInputs.Add(lib.AllInputs.Count + 1, obj);
                        }


                        foreach (ArgCollection arg in par.Values)
                        {
                            switch (arg.Tag)
                            {
                                case "options":
                                    if (arg.Count > 0)
                                        foreach (string s in arg)
                                        {
                                            lib.OptionsString.Add(arg.Name + " " + s);
                                        }
                                    else
                                        lib.OptionsString.Add(arg.Name);
                                    break;
                                case "archive":
                                    lib.OutputFileMSBuild = arg.Name;
                                    break;
                            }
                        }
                        //}
                    }
                    if (lib.InputLibraries.Count > 0) this.AnalizeInputLibraries(lib.InputLibraries, LogMessages);
                }
                #endregion
                #region sockets_dhcp.lib
                if (lib.Name.ToLower() == "sockets_dhcp.lib")
                {
                    if (lib.ParamCollection != null) return;

                    //foreach (LogQueueItem item in LogMessages)
                    //{
                    //    string util = ArgParser.GetUtil(item.Message);
                    //    if (util == null) continue;
                    //    if (String.Compare(ARMARPath, util, StringComparison.InvariantCultureIgnoreCase) == 0)
                    //if (item.Message.ToLower().Contains(ARMARPath))
                    //{
                    //ParamCollection par = ArgParser.Add(item.Message);
                    foreach (ParCollContainer container in ARMAR.Values)
                    {
                        ParamCollection par = container.ParamCollection;
                        if (par == null) continue;

                        bool Found = false;

                        foreach (ArgCollection arg in par.Values)
                        {
                            if (arg.Tag == "archive")
                            {
                                if (Path.GetFileName(arg.Name).ToLower() == "sockets_dhcp_stubs.lib") Found = true;
                            }
                        }

                        if (!Found) continue;

                        lib.ConsoleString = container.Message;
                        lib.ParamCollection = par;
                        lib.BuildList.AddRange(container.ProjectBuildContext);
                        lib.OutputFileuVision = uVisionProjectPath + "\\" + uVisionTargetsPath + "\\" + Path.GetFileNameWithoutExtension(lib.Name) + "\\" + Path.GetFileName(lib.Name);

                        string LIB_EXT = string.Empty;
                        string OBJ_EXT = string.Empty;

                        using (ProjectCollection LocalProjColl = new ProjectCollection())
                        {
                            Project MSBProj = LocalProjColl.LoadProject(container.ProjectBuildContext[container.ProjectBuildContext.Count - 1]);
                            LIB_EXT = MSBProj.GetPropertyValue("LIB_EXT");
                            OBJ_EXT = MSBProj.GetPropertyValue("OBJ_EXT");
                        }


                        foreach (string file in par.Files.Values)
                        {
                            RequiredLibrary libr = null;
                            RequiredObject obj = null;
                            if (Path.GetExtension(file).ToLower() == "." + LIB_EXT.ToLower())
                            {
                                libr = new RequiredLibrary(file, lib);
                                lib.InputLibraries.Add(lib.InputLibraries.Count + 1, libr);
                            }

                            if (Path.GetExtension(file).ToLower() == "." + OBJ_EXT.ToLower())
                            {
                                obj = new RequiredObject(file, lib);
                                lib.InputObjects.Add(lib.InputObjects.Count + 1, obj);
                            }
                            if (libr != null) lib.AllInputs.Add(lib.AllInputs.Count + 1, libr);
                            if (obj != null) lib.AllInputs.Add(lib.AllInputs.Count + 1, obj);
                        }


                        foreach (ArgCollection arg in par.Values)
                        {
                            switch (arg.Tag)
                            {
                                case "options":
                                    if (arg.Count > 0)
                                        foreach (string s in arg)
                                        {
                                            lib.OptionsString.Add(arg.Name + " " + s);
                                        }
                                    else
                                        lib.OptionsString.Add(arg.Name);
                                    break;
                                case "archive":
                                    lib.OutputFileMSBuild = arg.Name;
                                    break;
                            }
                        }
                        //}
                    }
                    if (lib.InputLibraries.Count > 0) this.AnalizeInputLibraries(lib.InputLibraries, LogMessages);
                }
                #endregion
                #region sockets_hal_udp.lib
                if (lib.Name.ToLower() == "sockets_hal_udp.lib")
                {
                    if (lib.ParamCollection != null) return;

                    //foreach (LogQueueItem item in LogMessages)
                    //{
                    //    string util = ArgParser.GetUtil(item.Message);
                    //    if (util == null) continue;
                    //    if (String.Compare(ARMARPath, util, StringComparison.InvariantCultureIgnoreCase) == 0)
                    //if (item.Message.ToLower().Contains(ARMARPath))
                    //{
                    //ParamCollection par = ArgParser.Add(item.Message);
                    foreach (ParCollContainer container in ARMAR.Values)
                    {
                        ParamCollection par = container.ParamCollection;
                        if (par == null) continue;

                        bool Found = false;

                        foreach (ArgCollection arg in par.Values)
                        {
                            if (arg.Tag == "archive")
                            {
                                if (Path.GetFileName(arg.Name).ToLower() == "sockets_hal_udp_stubs.lib") Found = true;
                            }
                        }

                        if (!Found) continue;

                        lib.ConsoleString = container.Message;
                        lib.ParamCollection = par;
                        lib.BuildList.AddRange(container.ProjectBuildContext);
                        lib.OutputFileuVision = uVisionProjectPath + "\\" + uVisionTargetsPath + "\\" + Path.GetFileNameWithoutExtension(lib.Name) + "\\" + Path.GetFileName(lib.Name);

                        string LIB_EXT = string.Empty;
                        string OBJ_EXT = string.Empty;

                        using (ProjectCollection LocalProjColl = new ProjectCollection())
                        {
                            Project MSBProj = LocalProjColl.LoadProject(container.ProjectBuildContext[container.ProjectBuildContext.Count - 1]);
                            LIB_EXT = MSBProj.GetPropertyValue("LIB_EXT");
                            OBJ_EXT = MSBProj.GetPropertyValue("OBJ_EXT");
                        }


                        foreach (string file in par.Files.Values)
                        {
                            RequiredLibrary libr = null;
                            RequiredObject obj = null;
                            if (Path.GetExtension(file).ToLower() == "." + LIB_EXT.ToLower())
                            {
                                libr = new RequiredLibrary(file, lib);
                                lib.InputLibraries.Add(lib.InputLibraries.Count + 1, libr);
                            }

                            if (Path.GetExtension(file).ToLower() == "." + OBJ_EXT.ToLower())
                            {
                                obj = new RequiredObject(file, lib);
                                lib.InputObjects.Add(lib.InputObjects.Count + 1, obj);
                            }
                            if (libr != null) lib.AllInputs.Add(lib.AllInputs.Count + 1, libr);
                            if (obj != null) lib.AllInputs.Add(lib.AllInputs.Count + 1, obj);
                        }


                        foreach (ArgCollection arg in par.Values)
                        {
                            switch (arg.Tag)
                            {
                                case "options":
                                    if (arg.Count > 0)
                                        foreach (string s in arg)
                                        {
                                            lib.OptionsString.Add(arg.Name + " " + s);
                                        }
                                    else
                                        lib.OptionsString.Add(arg.Name);
                                    break;
                                case "archive":
                                    lib.OutputFileMSBuild = arg.Name;
                                    break;
                            }
                        }
                        //}
                    }
                    if (lib.InputLibraries.Count > 0) this.AnalizeInputLibraries(lib.InputLibraries, LogMessages);
                }
                #endregion
                #region sockets_ssl.lib
                if (lib.Name.ToLower() == "sockets_ssl.lib")
                {
                    if (lib.ParamCollection != null) return;

                    //foreach (LogQueueItem item in LogMessages)
                    //{
                    //    string util = ArgParser.GetUtil(item.Message);
                    //    if (util == null) continue;
                    //    if (String.Compare(ARMARPath, util, StringComparison.InvariantCultureIgnoreCase) == 0)
                    //if (item.Message.ToLower().Contains(ARMARPath))
                    //{
                    //ParamCollection par = ArgParser.Add(item.Message);
                    foreach (ParCollContainer container in ARMAR.Values)
                    {
                        ParamCollection par = container.ParamCollection;
                        if (par == null) continue;

                        bool Found = false;

                        foreach (ArgCollection arg in par.Values)
                        {
                            if (arg.Tag == "archive")
                            {
                                if (Path.GetFileName(arg.Name).ToLower() == "sockets_ssl_stubs.lib") Found = true;
                            }
                        }

                        if (!Found) continue;

                        lib.ConsoleString = container.Message;
                        lib.ParamCollection = par;
                        lib.BuildList.AddRange(container.ProjectBuildContext);
                        lib.OutputFileuVision = uVisionProjectPath + "\\" + uVisionTargetsPath + "\\" + Path.GetFileNameWithoutExtension(lib.Name) + "\\" + Path.GetFileName(lib.Name);

                        string LIB_EXT = string.Empty;
                        string OBJ_EXT = string.Empty;

                        using (ProjectCollection LocalProjColl = new ProjectCollection())
                        {
                            Project MSBProj = LocalProjColl.LoadProject(container.ProjectBuildContext[container.ProjectBuildContext.Count - 1]);
                            LIB_EXT = MSBProj.GetPropertyValue("LIB_EXT");
                            OBJ_EXT = MSBProj.GetPropertyValue("OBJ_EXT");
                        }


                        foreach (string file in par.Files.Values)
                        {
                            RequiredLibrary libr = null;
                            RequiredObject obj = null;
                            if (Path.GetExtension(file).ToLower() == "." + LIB_EXT.ToLower())
                            {
                                libr = new RequiredLibrary(file, lib);
                                lib.InputLibraries.Add(lib.InputLibraries.Count + 1, libr);
                            }

                            if (Path.GetExtension(file).ToLower() == "." + OBJ_EXT.ToLower())
                            {
                                obj = new RequiredObject(file, lib);
                                lib.InputObjects.Add(lib.InputObjects.Count + 1, obj);
                            }
                            if (libr != null) lib.AllInputs.Add(lib.AllInputs.Count + 1, libr);
                            if (obj != null) lib.AllInputs.Add(lib.AllInputs.Count + 1, obj);
                        }


                        foreach (ArgCollection arg in par.Values)
                        {
                            switch (arg.Tag)
                            {
                                case "options":
                                    if (arg.Count > 0)
                                        foreach (string s in arg)
                                        {
                                            lib.OptionsString.Add(arg.Name + " " + s);
                                        }
                                    else
                                        lib.OptionsString.Add(arg.Name);
                                    break;
                                case "archive":
                                    lib.OutputFileMSBuild = arg.Name;
                                    break;
                            }
                        }
                        //}
                    }
                    if (lib.InputLibraries.Count > 0) this.AnalizeInputLibraries(lib.InputLibraries, LogMessages);
                }
                #endregion
                #region sockets_sntp.lib
                if (lib.Name.ToLower() == "sockets_sntp.lib")
                {
                    if (lib.ParamCollection != null) return;

                    //foreach (LogQueueItem item in LogMessages)
                    //{
                    //    string util = ArgParser.GetUtil(item.Message);
                    //    if (util == null) continue;
                    //    if (String.Compare(ARMARPath, util, StringComparison.InvariantCultureIgnoreCase) == 0)
                    //if (item.Message.ToLower().Contains(ARMARPath))
                    //{
                    //ParamCollection par = ArgParser.Add(item.Message);
                    foreach (ParCollContainer container in ARMAR.Values)
                    {
                        ParamCollection par = container.ParamCollection;
                        if (par == null) continue;

                        bool Found = false;

                        foreach (ArgCollection arg in par.Values)
                        {
                            if (arg.Tag == "archive")
                            {
                                if (Path.GetFileName(arg.Name).ToLower() == "sockets_sntp_stubs.lib") Found = true;
                            }
                        }

                        if (!Found) continue;

                        lib.ConsoleString = container.Message;
                        lib.ParamCollection = par;
                        lib.BuildList.AddRange(container.ProjectBuildContext);
                        lib.OutputFileuVision = uVisionProjectPath + "\\" + uVisionTargetsPath + "\\" + Path.GetFileNameWithoutExtension(lib.Name) + "\\" + Path.GetFileName(lib.Name);

                        string LIB_EXT = string.Empty;
                        string OBJ_EXT = string.Empty;

                        using (ProjectCollection LocalProjColl = new ProjectCollection())
                        {
                            Project MSBProj = LocalProjColl.LoadProject(container.ProjectBuildContext[container.ProjectBuildContext.Count - 1]);
                            LIB_EXT = MSBProj.GetPropertyValue("LIB_EXT");
                            OBJ_EXT = MSBProj.GetPropertyValue("OBJ_EXT");
                        }


                        foreach (string file in par.Files.Values)
                        {
                            RequiredLibrary libr = null;
                            RequiredObject obj = null;
                            if (Path.GetExtension(file).ToLower() == "." + LIB_EXT.ToLower())
                            {
                                libr = new RequiredLibrary(file, lib);
                                lib.InputLibraries.Add(lib.InputLibraries.Count + 1, libr);
                            }

                            if (Path.GetExtension(file).ToLower() == "." + OBJ_EXT.ToLower())
                            {
                                obj = new RequiredObject(file, lib);
                                lib.InputObjects.Add(lib.InputObjects.Count + 1, obj);
                            }
                            if (libr != null) lib.AllInputs.Add(lib.AllInputs.Count + 1, libr);
                            if (obj != null) lib.AllInputs.Add(lib.AllInputs.Count + 1, obj);
                        }


                        foreach (ArgCollection arg in par.Values)
                        {
                            switch (arg.Tag)
                            {
                                case "options":
                                    if (arg.Count > 0)
                                        foreach (string s in arg)
                                        {
                                            lib.OptionsString.Add(arg.Name + " " + s);
                                        }
                                    else
                                        lib.OptionsString.Add(arg.Name);
                                    break;
                                case "archive":
                                    lib.OutputFileMSBuild = arg.Name;
                                    break;
                            }
                        }
                        //}
                    }
                    if (lib.InputLibraries.Count > 0) this.AnalizeInputLibraries(lib.InputLibraries, LogMessages);
                }
                #endregion
                #region sockets_hal_tcp.lib
                if (lib.Name.ToLower() == "sockets_hal_tcp.lib")
                {
                    if (lib.ParamCollection != null) return;

                    //foreach (LogQueueItem item in LogMessages)
                    //{
                    //    string util = ArgParser.GetUtil(item.Message);
                    //    if (util == null) continue;
                    //    if (String.Compare(ARMARPath, util, StringComparison.InvariantCultureIgnoreCase) == 0)
                    //if (item.Message.ToLower().Contains(ARMARPath))
                    //{
                    //ParamCollection par = ArgParser.Add(item.Message);
                    foreach (ParCollContainer container in ARMAR.Values)
                    {
                        ParamCollection par = container.ParamCollection;
                        if (par == null) continue;

                        bool Found = false;

                        foreach (ArgCollection arg in par.Values)
                        {
                            if (arg.Tag == "archive")
                            {
                                if (Path.GetFileName(arg.Name).ToLower() == "sockets_hal_tcp_stubs.lib") Found = true;
                            }
                        }

                        if (!Found) continue;

                        lib.ConsoleString = container.Message;
                        lib.ParamCollection = par;
                        lib.BuildList.AddRange(container.ProjectBuildContext);
                        lib.OutputFileuVision = uVisionProjectPath + "\\" + uVisionTargetsPath + "\\" + Path.GetFileNameWithoutExtension(lib.Name) + "\\" + Path.GetFileName(lib.Name);

                        string LIB_EXT = string.Empty;
                        string OBJ_EXT = string.Empty;

                        using (ProjectCollection LocalProjColl = new ProjectCollection())
                        {
                            Project MSBProj = LocalProjColl.LoadProject(container.ProjectBuildContext[container.ProjectBuildContext.Count - 1]);
                            LIB_EXT = MSBProj.GetPropertyValue("LIB_EXT");
                            OBJ_EXT = MSBProj.GetPropertyValue("OBJ_EXT");
                        }


                        foreach (string file in par.Files.Values)
                        {
                            RequiredLibrary libr = null;
                            RequiredObject obj = null;
                            if (Path.GetExtension(file).ToLower() == "." + LIB_EXT.ToLower())
                            {
                                libr = new RequiredLibrary(file, lib);
                                lib.InputLibraries.Add(lib.InputLibraries.Count + 1, libr);
                            }

                            if (Path.GetExtension(file).ToLower() == "." + OBJ_EXT.ToLower())
                            {
                                obj = new RequiredObject(file, lib);
                                lib.InputObjects.Add(lib.InputObjects.Count + 1, obj);
                            }
                            if (libr != null) lib.AllInputs.Add(lib.AllInputs.Count + 1, libr);
                            if (obj != null) lib.AllInputs.Add(lib.AllInputs.Count + 1, obj);
                        }


                        foreach (ArgCollection arg in par.Values)
                        {
                            switch (arg.Tag)
                            {
                                case "options":
                                    if (arg.Count > 0)
                                        foreach (string s in arg)
                                        {
                                            lib.OptionsString.Add(arg.Name + " " + s);
                                        }
                                    else
                                        lib.OptionsString.Add(arg.Name);
                                    break;
                                case "archive":
                                    lib.OutputFileMSBuild = arg.Name;
                                    break;
                            }
                        }
                        //}
                    }
                    if (lib.InputLibraries.Count > 0) this.AnalizeInputLibraries(lib.InputLibraries, LogMessages);
                }
                #endregion
            }
        }

        private void AddObjFile(RequiredObject reqobj)
        {
            string DefaultWorkingDir = Directory.GetCurrentDirectory();
            Directory.SetCurrentDirectory(reqobj.CurrentDir);
            foreach (string file in reqobj.InputFiles)
            {
                string path = Path.GetFullPath(ExpandPath(file));
                if (!System.IO.File.Exists(path))
                {
                    throw new FileNotFoundException(KeilWizardStrings.IDS_FILE + " \"" + path + "\" " + KeilWizardStrings.IDS_MISSING, path);
                }

                if (!uVisionProject.ContainsFile(path))
                {
                    List<BuildFileWrapper> source_list = new List<BuildFileWrapper>();

                    object obj = GetMFObjectFromProjectFile(reqobj.BuildList[reqobj.BuildList.Count - 1]);

                    string group = Path.GetFileNameWithoutExtension(reqobj.Parent.Name);

                    if (obj == null)
                    {
                        uVisionProject.AddFile(path, group);
                        continue;
                    }
                    else
                    {

                        if (obj.GetType() == typeof(SolutionWrapper))
                        {
                            //MFSolution sol = (MFSolution)obj;
                        }
                        else if (obj.GetType() == typeof(ProjectWrapper))
                        {
                            ProjectWrapper proj = (ProjectWrapper)obj;
                            source_list.AddRange(proj.FastCompileFiles);
                            source_list.AddRange(proj.HeaderFiles);
                            source_list.AddRange(proj.SourceFiles);
                        }
                        else if (obj.GetType() == typeof(LibraryWrapper))
                        {
                            LibraryWrapper lib = (LibraryWrapper)obj;
                            source_list.AddRange(lib.FastCompileFiles);
                            source_list.AddRange(lib.HeaderFiles);
                            source_list.AddRange(lib.SourceFiles);
                        }
                    }

                    if (CheckFile(path, source_list))
                    {
                        AddHFiles(group, source_list, uVisionProject);
                        uVisionProject.AddFile(path, group);
                        continue;
                    }
                    else
                    {
                        uVisionProject.AddFile(path, group);
                    }
                }
            }
            Directory.SetCurrentDirectory(DefaultWorkingDir);
        }

        private void CreateLibraryTartet(RequiredLibrary lib)
        {
            Target target = new Target(uVisionProject.DefaultOptions);

            //Setting default options
            //target.Set_AT91SAM7S16_DefaultOptions();
            //target.Options.SerializeXLM(@"AT91SAM7S16.xml");
            //target.LoadOptions(@"text.xml");


            target.Name = Path.GetFileNameWithoutExtension(lib.Name);
            target.Options.OutDir += uVisionTargetsPath + "\\" + target.Name + "\\";
            target.Options.OutName = Path.GetFileNameWithoutExtension(lib.Name);

            target.Options.GenApp = TWO_STATE_BOOL.DISABLED;
            target.Options.GenLib = TWO_STATE_BOOL.ENABLED;

            target.Options.ADSFLGA = "226,31,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0";

            target.Options.ADSCCFLG.ARM_Thumb_Interworking = THREE_STATE_BOOL.DISABLED;
            target.Options.ADSCCFLG.Optimisation = OPTIMIZATION.Level0;
            target.Options.ADSCCFLG.Optimize_for_time = THREE_STATE_BOOL.DISABLED;
            target.Options.ADSCCFLG.Split_Load_and_Store_Multiple = THREE_STATE_BOOL.DISABLED;
            target.Options.ADSCCFLG.One_EFL_Section_per_Function = THREE_STATE_BOOL.DISABLED;
            target.Options.ADSCCFLG.Strict_ANSI_C = THREE_STATE_BOOL.DISABLED;
            target.Options.ADSCCFLG.Enum_Container_always_int = THREE_STATE_BOOL.DISABLED;
            target.Options.ADSCCFLG.Plain_Char_is_Signed = THREE_STATE_BOOL.DISABLED;
            target.Options.ADSCCFLG.ReadOnly_Position_Independent = THREE_STATE_BOOL.DISABLED;
            target.Options.ADSCCFLG.ReadWrite_Position_Independent = THREE_STATE_BOOL.DISABLED;
            target.Options.ADSCCFLG.Thumb_Mode = THREE_STATE_BOOL.DISABLED;


            target.Options.ADSASFLG = "0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0";
            target.Options.Debug = "1";
            target.Options.Browse = "1";


            //Exclude files from building
            foreach (PKStudio.Tools.uVisionGenerator.Classes.uvProjectClasses.File f in uVisionProject.FileList.Values)
            {
                PKStudio.Tools.uVisionGenerator.Classes.uvProjectClasses.FileOptions fileopt = new PKStudio.Tools.uVisionGenerator.Classes.uvProjectClasses.FileOptions(f);
                fileopt.IncBld = THREE_STATE_BOOL.DISABLED;
                target.FilesOpton.Add(fileopt);
            }

            foreach (RequiredObject obj in lib.InputObjects.Values)
            {
                this.AddCompileFile(obj, target);
            }

            foreach (RequiredLibrary reqlib in lib.InputLibraries.Values)
            {
                PKStudio.Tools.uVisionGenerator.Classes.uvProjectClasses.FileOptions fileOpt = target.FindFileOptions(reqlib.OutputFileuVision);
                if (fileOpt == null) throw new MessagesParserException(KeilWizardStrings.IDS_ERROR_INTERNAL + " " + reqlib.OutputFileMSBuild + ": " + KeilWizardStrings.IDS_ERROR_CANT_FIND_LIBRARY_FILE_OPTIONS);
                fileOpt.IncBld = THREE_STATE_BOOL.ENABLED;
                this.CreateLibraryTartet(reqlib);
            }

            target.Num = uVisionProject.TargetList.Count + 1;
            if (!uVisionProject.ContainsTarget(target))
                uVisionProject.TargetList.Add(target.Num, target);

            if (target.BeforeBuild.Count > 0)
            {
                target.Options.BrunUsr_0.Run = TWO_STATE_BOOL.ENABLED;
                target.Options.BrunUsr_0.Command = ".\\BatFiles\\Prebuild" + @"\" + target.Name + ".bat";
            }

            if (target.AfterBuild.Count > 0)
            {
                target.Options.RunUsr_0.Run = TWO_STATE_BOOL.ENABLED;
                target.Options.RunUsr_0.Command = ".\\BatFiles\\Postbuild" + @"\" + target.Name + ".bat";
            }
        }

        private void CreateObjectTartet(RequiredObject obj)
        {
            Target target = new Target(uVisionProject.DefaultOptions);
            //Setting default options
            //target.SeTLPC2478DefaultOptions();

            target.Name = Path.GetFileNameWithoutExtension(obj.Name);
            target.Options.OutDir += uVisionTargetsPath + "\\" + target.Name + "\\";
            target.Options.OutName = Path.GetFileNameWithoutExtension(obj.Name);

            target.Options.GenApp = TWO_STATE_BOOL.DISABLED;
            target.Options.GenLib = TWO_STATE_BOOL.ENABLED;

            target.Options.ADSFLGA = "226,31,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0";

            target.Options.ADSCCFLG.ARM_Thumb_Interworking = THREE_STATE_BOOL.DISABLED;
            target.Options.ADSCCFLG.Optimisation = OPTIMIZATION.Level0;
            target.Options.ADSCCFLG.Optimize_for_time = THREE_STATE_BOOL.DISABLED;
            target.Options.ADSCCFLG.Split_Load_and_Store_Multiple = THREE_STATE_BOOL.DISABLED;
            target.Options.ADSCCFLG.One_EFL_Section_per_Function = THREE_STATE_BOOL.DISABLED;
            target.Options.ADSCCFLG.Strict_ANSI_C = THREE_STATE_BOOL.DISABLED;
            target.Options.ADSCCFLG.Enum_Container_always_int = THREE_STATE_BOOL.DISABLED;
            target.Options.ADSCCFLG.Plain_Char_is_Signed = THREE_STATE_BOOL.DISABLED;
            target.Options.ADSCCFLG.ReadOnly_Position_Independent = THREE_STATE_BOOL.DISABLED;
            target.Options.ADSCCFLG.ReadWrite_Position_Independent = THREE_STATE_BOOL.DISABLED;
            target.Options.ADSCCFLG.Thumb_Mode = THREE_STATE_BOOL.DISABLED;

            target.Options.ADSASFLG = "0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0";

            target.Options.Debug = "1";
            target.Options.Browse = "1";

            //Exclude files from building
            foreach (PKStudio.Tools.uVisionGenerator.Classes.uvProjectClasses.File f in uVisionProject.FileList.Values)
            {
                PKStudio.Tools.uVisionGenerator.Classes.uvProjectClasses.FileOptions fileopt = new PKStudio.Tools.uVisionGenerator.Classes.uvProjectClasses.FileOptions(f);
                fileopt.IncBld = THREE_STATE_BOOL.DISABLED;
                target.FilesOpton.Add(fileopt);
            }

            this.AddCompileFile(obj, target);


            target.Num = uVisionProject.TargetList.Count + 1;
            uVisionProject.TargetList.Add(target.Num, target);

            if (target.BeforeBuild.Count > 0)
            {
                target.Options.BrunUsr_0.Run = TWO_STATE_BOOL.ENABLED;
                target.Options.BrunUsr_0.Command = ".\\BatFiles\\Prebuild" + @"\" + target.Name + ".bat";
            }

            if (target.AfterBuild.Count > 0)
            {
                target.Options.RunUsr_0.Run = TWO_STATE_BOOL.ENABLED;
                target.Options.RunUsr_0.Command = ".\\BatFiles\\Postbuild" + @"\" + target.Name + ".bat";
            }
        }

        private void CreateLinkTarget(Link link)//, IList<LogQueueItem> messages)
        {
            Target target = new Target(uVisionProject.DefaultOptions);
            //Setting default options
            //target.SeTLPC2478DefaultOptions();

            target.Name = Path.GetFileNameWithoutExtension(link.Name);

            target.Options.GenApp = TWO_STATE_BOOL.ENABLED;
            target.Options.GenLib = TWO_STATE_BOOL.DISABLED;

            target.Options.ADSFLGA = "226,31,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0";

            target.Options.ADSCCFLG.ARM_Thumb_Interworking = THREE_STATE_BOOL.DISABLED;
            target.Options.ADSCCFLG.Optimisation = OPTIMIZATION.Level0;
            target.Options.ADSCCFLG.Optimize_for_time = THREE_STATE_BOOL.DISABLED;
            target.Options.ADSCCFLG.Split_Load_and_Store_Multiple = THREE_STATE_BOOL.DISABLED;
            target.Options.ADSCCFLG.One_EFL_Section_per_Function = THREE_STATE_BOOL.DISABLED;
            target.Options.ADSCCFLG.Strict_ANSI_C = THREE_STATE_BOOL.DISABLED;
            target.Options.ADSCCFLG.Enum_Container_always_int = THREE_STATE_BOOL.DISABLED;
            target.Options.ADSCCFLG.Plain_Char_is_Signed = THREE_STATE_BOOL.DISABLED;
            target.Options.ADSCCFLG.ReadOnly_Position_Independent = THREE_STATE_BOOL.DISABLED;
            target.Options.ADSCCFLG.ReadWrite_Position_Independent = THREE_STATE_BOOL.DISABLED;
            target.Options.ADSCCFLG.Thumb_Mode = THREE_STATE_BOOL.DISABLED;

            target.Options.ADSASFLG = "0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0";

            target.Options.ADSLDFG = "0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0";

            target.Options.ADSLDTA = "";
            target.Options.ADSLDDA = "";
            target.Options.Debug = "1";
            target.Options.Browse = "1";


            //Exclude files from building
            foreach (PKStudio.Tools.uVisionGenerator.Classes.uvProjectClasses.File f in uVisionProject.FileList.Values)
            {
                //if ((f.Type == uVision.Project.File.FILE_TYPE.C_FILE) || (f.Type == uVision.Project.File.FILE_TYPE.CPP_FILE) || (f.Type == uVision.Project.File.FILE_TYPE.ASM_FILE))
                //{
                PKStudio.Tools.uVisionGenerator.Classes.uvProjectClasses.FileOptions fileopt = new PKStudio.Tools.uVisionGenerator.Classes.uvProjectClasses.FileOptions(f);
                fileopt.IncBld = THREE_STATE_BOOL.DISABLED;
                target.FilesOpton.Add(fileopt);
                //}
            }

            target.Options.OutDir = Path.GetDirectoryName(link.OutputFileMSBuild) + "\\";
            target.Options.OutName = Path.GetFileNameWithoutExtension(link.OutputFileMSBuild);
            link.OutputFileuVision = link.OutputFileMSBuild;

            foreach (RequiredObject obj in link.InputObjects.Values)
            {
                this.AddCompileFile(obj, target);
            }


            foreach (RequiredLibrary lib in link.InputLibraries.Values)
            {
                PKStudio.Tools.uVisionGenerator.Classes.uvProjectClasses.FileOptions fileOpt = target.FindFileOptions(lib.OutputFileuVision);
                fileOpt.IncBld = THREE_STATE_BOOL.ENABLED;
            }

            //string LinkString = ARMLINKPath;

            foreach (ArgCollection arg in link.ParamCollection.Values)
            {
                if (arg.Tag == "options")
                {
                    switch (arg.Name)
                    {
                        //no need process this because all paths will be contained in file list
                        case "--userlibpath":
                            break;
                        case "--scatter":
                            //target.Options.ADSLDSC = arg[0];
                            target.Options.ADSLDSC = uVisionProject.ProjectPath + @"\" + Path.GetFileName(arg[0]);
                            string line;

                            using (StreamReader infile = new StreamReader(arg[0]))
                            {
                                while ((line = infile.ReadLine()) != null)
                                {
                                    uVisionProject.Scatter.Add(uVisionProject.Scatter.Count + 1, line);
                                }

                            }
                            //uVisionProject
                            break;
                        case "--device":
                            break;
                        case "--output":
                            break;
                        default:
                            if (arg.Count > 0)
                            {
                                foreach (string s in arg)
                                {
                                    //LinkString += " " + arg.Name + " " + s;
                                    target.Options.ADSLDMC.Add(arg.Name + " " + s);
                                }
                            }
                            //else LinkString += " " + arg.Name;
                            else target.Options.ADSLDMC.Add(arg.Name);
                            break;
                    }
                }
            }

            //foreach (BuildBase bb in link.AllInputs.Values)
            //{
            //    LinkString += " " + bb.OutputFileuVision;
            //}

            //target.AfterBuild.Add(LinkString);

            //PKArgParser ArgParser = new PKArgParser();

            //Adds fromelf
            foreach (ParCollContainer container in FROMELF.Values)
            {
                if (container.Message.ToLower().Contains(link.OutputFileMSBuild.ToLower()))
                {
                    target.AfterBuild.Add(container.Message);
                }
            }

            target.Num = uVisionProject.TargetList.Count + 1;
            uVisionProject.TargetList.Add(target.Num, target);

            if (target.BeforeBuild.Count > 0)
            {
                target.Options.BrunUsr_0.Run = TWO_STATE_BOOL.ENABLED;
                target.Options.BrunUsr_0.Command = ".\\BatFiles\\Prebuild" + @"\" + target.Name + ".bat";
            }

            if (target.AfterBuild.Count > 0)
            {
                target.Options.RunUsr_0.Run = TWO_STATE_BOOL.ENABLED;
                target.Options.RunUsr_0.Command = ".\\BatFiles\\Postbuild" + @"\" + target.Name + ".bat";
            }

        }

        private void AddCompileFile(RequiredObject obj, Target target)
        {
            string DefaultWorkingDir = Directory.GetCurrentDirectory();
            Directory.SetCurrentDirectory(obj.CurrentDir);
            foreach (string path in obj.ParamCollection.Files.Values)
            {
                PKStudio.Tools.uVisionGenerator.Classes.uvProjectClasses.FileOptions fileOpt = target.FindFileOptions(Path.GetFullPath(ExpandPath(path)));
                if (fileOpt == null) throw new MessagesParserException(KeilWizardStrings.IDS_ERROR_INTERNAL + " " + path + ": " + KeilWizardStrings.IDS_ERROR_CANT_FIND_COMPILE_FILE_OPTIONS);


                fileOpt.IncBld = THREE_STATE_BOOL.ENABLED;

                foreach (ArgCollection arg in obj.ParamCollection.Values)
                {
                    if (arg.Tag != "options") continue;
                    switch (arg.Name)
                    {
                        case "-I":
                            foreach (string include in arg)
                            {
                                fileOpt.Include.Add(include);
                            }
                            break;
                        case "-D":

                            foreach (string def in arg)
                            {
                                if (!def.Contains("="))
                                    fileOpt.Define.Add(def);
                                else
                                    fileOpt.Misc.Add("-D" + def);
                            }

                            break;
                        case "--PD":
                            foreach (string def in arg)
                            {
                                if (fileOpt.File.Type == PKStudio.Tools.uVisionGenerator.Classes.uvProjectClasses.File.FILE_TYPE.ASM_FILE)
                                    fileOpt.Misc.Add("--PD " + def);
                            }
                            break;
                        case "--split_sections":
                            fileOpt.ADSCCFLG.One_EFL_Section_per_Function = THREE_STATE_BOOL.ENABLED;
                            break;
                        //case "--fpu":
                        //    fileOpt.Misc.Add("--fpu " + arg[0]);
                        //    break;
                        case "--littleend":
                            fileOpt.Misc.Add("--littleend");
                            break;
                        case "-c":
                            break;
                        case "--cpp":
                            fileOpt.Misc.Add("--cpp");
                            break;
                        case "-O":
                            OPTIMIZATION tmp = OPTIMIZATION.Default;
                            switch (arg[0])
                            {
                                case "0":
                                    tmp = OPTIMIZATION.Level0;
                                    break;
                                case "1":
                                    tmp = OPTIMIZATION.Level1;
                                    break;
                                case "2":
                                    tmp = OPTIMIZATION.Level2;
                                    break;
                                case "3":
                                    tmp = OPTIMIZATION.Level3;
                                    break;
                                default:
                                    break;
                            }
                            fileOpt.ADSCCFLG.Optimisation = tmp;
                            break;
                        case "--diag_suppress":
                            foreach (string item in arg)
                            {
                                //if (!target.Options.ADSCMISC.Contains("--diag_suppress " + item))
                                //{
                                fileOpt.Misc.Add("--diag_suppress " + item);
                                //}
                            }

                            break;
                        //Ignored. uVision IDE sets it by default
                        case "--device":
                            break;
                        //Special process for this param
                        case "-o":
                            //obj.OutputFileuVision = uVisionProjectPath + target.Options.OutDir.Replace(".", "") + Path.GetFileNameWithoutExtension(arg[0]) + ".o ";
                            break;
                        case "--LIST":
                        case "--list":
                            //s = "IF NOT EXIST " + Path.GetDirectoryName(arg[0]) + " md " + Path.GetDirectoryName(arg[0]);
                            //if (!target.BeforeBuild.Contains(s))
                            //    target.BeforeBuild.Add(s);
                            break;
                        default:
                            string str = arg.Name;
                            foreach (string item in arg)
                            {
                                str += " " + item;
                            }
                            fileOpt.Misc.Add(str);
                            break;
                    }
                }
            }
            Directory.SetCurrentDirectory(DefaultWorkingDir);
        }

        public void Convert(string ProjectPath)
        {
            using (ProjectCollection LocalProjColl = new ProjectCollection())
            {
                Project MSBProj = LocalProjColl.LoadProject(PK.Wrapper.ExpandEnvVars(ProjectPath, ""));

                ARMCCPath = MSBProj.GetPropertyValue("CC").ToLower();
                ARMASMPath = MSBProj.GetPropertyValue("AS").ToLower();
                ARMLINKPath = MSBProj.GetPropertyValue("LINK").ToLower();
                ARMARPath = MSBProj.GetPropertyValue("AR").ToLower();
                ARMFROMELFPath = MSBProj.GetPropertyValue("FromELF").ToLower();
            }

            PKParser.Arg.PKArgParser ArgParser = new PKParser.Arg.PKArgParser();

            int index = 0;

            Link Link = new Link("Link", null);

            Link.LogEvent += new MessagesParsesHelper.Link.LogEventDelegate(Link_LogEvent);

            OnLog(new GeneratingLogMessage("", GeneratingLogMessage.WORK_TYPE.CREATE_PROJECT_TREE, GeneratingLogMessage.WORK_STATE.START));

            foreach (LogQueueItem item in LogQueue.Values)
            {
                index++;
                OnLog(new GeneratingLogMessage(KeilWizardStrings.IDS_ANALYSE_LINKS, GeneratingLogMessage.WORK_TYPE.CREATE_PROJECT_TREE, GeneratingLogMessage.WORK_STATE.WORKING, (int)((index * 100) / LogQueue.Values.Count)));

                string s = ArgParser.GetUtil(item.Message);
                if (s == null) continue;
                if (String.Compare(ARMLINKPath, s, StringComparison.InvariantCultureIgnoreCase) == 0)
                {
                    //ArmLink
                    ARMLink.Add(ARMLink.Count + 1, new ParCollContainer(ArgParser.Add(item.Message), item.Message, item.ProjectBuildContext, item.CurrentDir));
                }
                else if (String.Compare(ARMCCPath, s, StringComparison.InvariantCultureIgnoreCase) == 0)
                {
                    //ArmCC 
                    ARMCCandARMASM.Add(ARMCCandARMASM.Count + 1, new ParCollContainer(ArgParser.Add(item.Message), item.Message, item.ProjectBuildContext, item.CurrentDir));
                }
                else if (String.Compare(ARMASMPath, s, StringComparison.InvariantCultureIgnoreCase) == 0)
                {
                    //ArmAsm
                    ARMCCandARMASM.Add(ARMCCandARMASM.Count + 1, new ParCollContainer(ArgParser.Add(item.Message), item.Message, item.ProjectBuildContext, item.CurrentDir));
                }
                else if (String.Compare(ARMARPath, s, StringComparison.InvariantCultureIgnoreCase) == 0)
                {
                    //ArmAr
                    ARMAR.Add(ARMAR.Count + 1, new ParCollContainer(ArgParser.Add(item.Message), item.Message, item.ProjectBuildContext, item.CurrentDir));
                }
                else if (String.Compare(ARMFROMELFPath, s, StringComparison.InvariantCultureIgnoreCase) == 0)
                {
                    //FROMElf
                    FROMELF.Add(FROMELF.Count + 1, new ParCollContainer(ArgParser.Add(item.Message), item.Message, item.ProjectBuildContext, item.CurrentDir));
                }
            }

            ArgParser.Clear();

            //Construct project tree

            ParCollContainer container = ARMLink.Values[ARMLink.Values.Count - 1];
            if (container.ParamCollection == null) throw new MessagesParserException(KeilWizardStrings.IDS_ERROR_CANT_PASRSE_LINK);
            Link.ParamCollection = container.ParamCollection;

            string LIB_EXT = string.Empty;
            string OBJ_EXT = string.Empty;

            using (ProjectCollection LocalProjColl = new ProjectCollection())
            {
                Project MSBProj = LocalProjColl.LoadProject(container.ProjectBuildContext[container.ProjectBuildContext.Count - 1]);

                LIB_EXT = MSBProj.GetPropertyValue("LIB_EXT");
                OBJ_EXT = MSBProj.GetPropertyValue("OBJ_EXT");
            }

            foreach (ArgCollection arg in container.ParamCollection.Values)
            {
                if (arg.Name == "--output")
                {
                    Link.Name = arg[0];
                }
            }

            foreach (string file in container.ParamCollection.Files.Values)
            {
                RequiredLibrary lib = null;
                RequiredObject obj = null;

                if (Path.GetExtension(file).ToLower() == "." + LIB_EXT.ToLower())
                {
                    lib = new RequiredLibrary(file, Link);
                    Link.InputLibraries.Add(Link.InputLibraries.Count + 1, lib);
                }

                if (Path.GetExtension(file).ToLower() == "." + OBJ_EXT.ToLower())
                {
                    obj = new RequiredObject(file, Link);
                    Link.InputObjects.Add(Link.InputObjects.Count + 1, obj);
                }
                if (lib != null) Link.AllInputs.Add(Link.AllInputs.Count + 1, lib);
                if (obj != null) Link.AllInputs.Add(Link.AllInputs.Count + 1, obj);
            }
            OnLog(new GeneratingLogMessage(KeilWizardStrings.IDS_ANALYSE_LINKS, GeneratingLogMessage.WORK_TYPE.CREATE_PROJECT_TREE, GeneratingLogMessage.WORK_STATE.WORKING, 100));
            System.Threading.Thread.Sleep(sleeptime);



            //using (StreamWriter outfile =
            //            new StreamWriter(Path.GetFileNameWithoutExtension(Link.Name) + ".input"))
            //{
            //    outfile.WriteLine(PK.Wrapper.Solution.ProjectPath);
            //    outfile.WriteLine(uVisionProjectPath);
            //    outfile.WriteLine(ProjectPath);                

            //    foreach (ArgCollection arg in Link.ParamCollection.Values)
            //    {
            //        if (arg.Name == "--scatter")
            //            outfile.WriteLine(arg[0]);
            //    }
            //    outfile.WriteLine(LogQueue.Values.Count);
            //    foreach (LogQueueItem item in LogQueue.Values)
            //    {
            //        outfile.WriteLine(item.Message);
            //        outfile.WriteLine(item.CurrentDir);
            //        outfile.WriteLine(item.ProjectBuildContext.Count);
            //        foreach (string s in item.ProjectBuildContext)
            //        {
            //            outfile.WriteLine(s);
            //        }
            //    }
            //}



            ArgParser.Clear();
            //Analysing libraries
            this.AnalizeInputLibraries(Link.InputLibraries, LogQueue.Values);

            //Checking Crypto.Lib
            this.CheckCryptoLib(Link.InputLibraries, LogQueue.Values);

            //Checking Sockets Libs
            this.CheckSocketsLibs(Link.InputLibraries, LogQueue.Values);            

            //Analysing Files
            SortedList<int, RequiredObject> ReqObjs = Link.GetAllRequiredObjects();
            this.AnalizeInputObjects(ReqObjs);//, LogQueue.Values);

            if (!Link.CheckItems())
            {
                throw new MessagesParserException(KeilWizardStrings.IDS_ERROR_FAIL_LINK_ANALYSE);
            }

            OnLog(new GeneratingLogMessage("", GeneratingLogMessage.WORK_TYPE.CREATE_PROJECT_TREE, GeneratingLogMessage.WORK_STATE.DONE));
            OnLog(new GeneratingLogMessage("", GeneratingLogMessage.WORK_TYPE.CREATE_FILE_LIST, GeneratingLogMessage.WORK_STATE.START));
            index = 0;
            //Collects required files
            List<RequiredLibrary> ReqLib = Link.GetAllSubRequiredLibraries();

            foreach (RequiredObject obj in ReqObjs.Values)
            {
                index++;
                OnLog(new GeneratingLogMessage(KeilWizardStrings.IDS_CREATING_FILE_LIST, GeneratingLogMessage.WORK_TYPE.CREATE_FILE_LIST, GeneratingLogMessage.WORK_STATE.WORKING, (int)((index * 100) / (ReqObjs.Values.Count + ReqLib.Count))));
                this.AddObjFile(obj);
            }
            foreach (RequiredLibrary lib in ReqLib)
            {
                index++;
                OnLog(new GeneratingLogMessage(KeilWizardStrings.IDS_CREATING_FILE_LIST, GeneratingLogMessage.WORK_TYPE.CREATE_FILE_LIST, GeneratingLogMessage.WORK_STATE.WORKING, (int)((index * 100) / (ReqObjs.Values.Count + ReqLib.Count))));
                uVisionProject.AddFile(lib.OutputFileuVision, Path.GetFileNameWithoutExtension(lib.Parent.Name));
            }

            //Sorting groups
            uVisionProject.SortGroups();

            foreach (RequiredLibrary lib in Link.InputLibraries.Values)
            {
                uVisionProject.AddFile(lib.OutputFileuVision, Path.GetFileNameWithoutExtension(Link.Name));
            }
            OnLog(new GeneratingLogMessage(KeilWizardStrings.IDS_CREATING_FILE_LIST, GeneratingLogMessage.WORK_TYPE.CREATE_FILE_LIST, GeneratingLogMessage.WORK_STATE.WORKING, 100));
            System.Threading.Thread.Sleep(sleeptime);
            OnLog(new GeneratingLogMessage("", GeneratingLogMessage.WORK_TYPE.CREATE_FILE_LIST, GeneratingLogMessage.WORK_STATE.DONE));
            OnLog(new GeneratingLogMessage("", GeneratingLogMessage.WORK_TYPE.CREATE_TARGETS, GeneratingLogMessage.WORK_STATE.START));
            //Create targets
            index = 0;
            foreach (RequiredLibrary lib in Link.InputLibraries.Values)
            {
                index++;
                OnLog(new GeneratingLogMessage(KeilWizardStrings.IDS_CREATING_TARGETS, GeneratingLogMessage.WORK_TYPE.CREATE_TARGETS, GeneratingLogMessage.WORK_STATE.WORKING, (int)((index * 100) / (Link.InputLibraries.Count))));

                this.CreateLibraryTartet(lib);
            }

            this.CreateLinkTarget(Link);//, LogQueue.Values);

            OnLog(new GeneratingLogMessage(KeilWizardStrings.IDS_CREATING_TARGETS, GeneratingLogMessage.WORK_TYPE.CREATE_TARGETS, GeneratingLogMessage.WORK_STATE.WORKING, 100));
            System.Threading.Thread.Sleep(sleeptime);
            OnLog(new GeneratingLogMessage("", GeneratingLogMessage.WORK_TYPE.CREATE_TARGETS, GeneratingLogMessage.WORK_STATE.DONE));

            //using (StreamWriter outfile = new StreamWriter(Path.GetFileNameWithoutExtension(Link.Name) + ".result"))
            //{
            //    List<string> strs = uVisionProject.GetAllProjectStrings();
            //    foreach (string s in strs)
            //    {
            //        outfile.WriteLine(s);
            //    }
            //}
        }

        void Link_LogEvent(GeneratingLogMessage mess)
        {
            this.OnLog(mess);
        }

        public void EnqueueItem(string Message, string CurrentDirectory, List<string> ProjectBuildContext)
        {
            this.LogQueue.Add(this.LogQueue.Count + 1, new LogQueueItem(Message, CurrentDirectory, ProjectBuildContext));
        }

        private string ExpandPath(string path)
        {
            string result = string.Empty;

            string srcDirEnvVar = Environment.GetEnvironmentVariable("SRC_DIR");
            if (srcDirEnvVar != null)
            {
            }
            result = PK.Wrapper.ExpandEnvVars(path, "");

            if (result.Contains("%SRC_DIR%\\"))
                result = result.Replace("%SRC_DIR%\\", "");

            return result;
        }

        private bool CheckFile(string filePath, List<BuildFileWrapper> list)
        {
            foreach (BuildFileWrapper mfbf in list)
            {
                string path = this.ExpandPath(mfbf.FullPath);

                if (System.IO.File.Exists(path))
                {
                    if (String.Compare(Path.GetFullPath(path).TrimEnd('\\'), Path.GetFullPath(filePath).TrimEnd('\\'), StringComparison.InvariantCultureIgnoreCase) == 0)
                    {

                        return true;
                    }
                }
                else
                {
                    //throw new Exception("File missing");
                }
            }
            return false;
        }

        private void AddHFiles(string group, List<BuildFileWrapper> list, uVisionProject project)
        {
            foreach (BuildFileWrapper mfbf in list)
            {
                string path = this.ExpandPath(mfbf.FullPath);

                if (System.IO.File.Exists(path))
                {
                    if (string.Compare(System.IO.Path.GetExtension(path), ".h", StringComparison.InvariantCultureIgnoreCase) == 0)
                        project.AddFile(path, group);
                }
                else
                {
                    //throw new Exception("File missing");
                }
            }
        }

        private object GetMFObjectFromProjectFile(string path)
        {
            Project proj = PK.Wrapper.LoadProject(path);

            string guid = string.Empty;
            string settingsFile = string.Empty;

            foreach (ProjectPropertyGroupElement PG in proj.Xml.PropertyGroups)
            {
                foreach (ProjectPropertyElement prop in PG.Properties)
                {
                    if (prop.Name == "ProjectGuid")
                    {
                        guid = prop.Value;
                    }
                    if (prop.Name == "MFSettingsFile")
                    {
                        settingsFile = prop.Value;
                    }
                }
            }

            LibraryWrapper lib = null;
            ProjectWrapper project = null;

            //if(guid == string.Empty) return null;

            lib = PK.Wrapper.FindLibrary(guid);
            //lib = PK.Wrapper.LoadLibraryProj(path,"");
            if (lib != null) return lib;

            foreach (var item in PK.Wrapper.Solution.Projects)
            {
                if (item.Guid == guid)
                {
                    project = item;
                    return project;
                }
            }


            //Is this Solution?
            if (!string.IsNullOrEmpty(settingsFile))
            {
                proj = PK.Wrapper.LoadProject(PK.Wrapper.ExpandEnvVars(settingsFile, ""));

                foreach (ProjectPropertyGroupElement PG in proj.Xml.PropertyGroups)
                {
                    foreach (ProjectPropertyElement prop in PG.Properties)
                    {
                        if (prop.Name == "PlatformGuid")
                        {
                            guid = prop.Value;
                            if (PK.Wrapper.Solution.Guid == guid) return PK.Wrapper.Solution;
                        }
                    }
                }
            }
            return null;
        }
    }
}
