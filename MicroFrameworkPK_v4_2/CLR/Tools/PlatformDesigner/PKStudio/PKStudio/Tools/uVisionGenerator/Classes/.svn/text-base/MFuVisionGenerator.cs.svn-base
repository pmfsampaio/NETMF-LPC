using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.IO;
using Microsoft.Build.Construction;
using Microsoft.Build.Evaluation;
using PKParser.Arg;
using PKStudio.uVision.Project;
using XsdInventoryFormatObject;
using PKStudio.Tools.KeilGenerator.Classes.GeneratorHelper;
using PKStudio.ItemWrappers;
namespace PKStudio.Tools.KeilGenerator.Classes
{
    class MFuVisionGenerator
    {
        private BackgroundWorker m_worker;

        private SortedList<int, LogQueueItem> LogQueue = new SortedList<int, LogQueueItem>();

        //private MFProject MFproject = null;

        private uVisionProject uVisionProject = new uVisionProject();

        //private string CurrentProjectPath = string.Empty;

        /// <summary>
        /// Путь куда будет сохраняться проект uVision
        /// </summary>
        private string uVisionProjectPath = @"D:\testProject\test";

        private string uVisionTargetsPath = @"targets";

        private string ARMCCPath = string.Empty;
        private string ARMASMPath = string.Empty;
        private string ARMLINKPath = string.Empty;
        private string ARMARPath = string.Empty;
        private string ARMFROMELFPath = string.Empty;


        private class WorkerParams
        {
            public SortedList<int, LogQueueItem> messages { get; set; }
            public IDictionary EnvVars { get; set; }
        }

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

        public MFuVisionGenerator()
        {
            this.m_worker = new BackgroundWorker();
            this.m_worker.DoWork += new DoWorkEventHandler(m_worker_DoWork);
            this.m_worker.RunWorkerCompleted += new RunWorkerCompletedEventHandler(m_worker_RunWorkerCompleted);
        }

        #region Event
        public delegate void CompletedEventDelegate(List<string> result);

        public event CompletedEventDelegate CompletedEvent;

        protected void OnCompletedt(List<string> result)
        {
            if (CompletedEvent != null)
            {
                CompletedEvent(result);
            }
        }

        public delegate void LogEventDelegate(string str);

        public event LogEventDelegate LogEvent;

        protected void OnLogText(string str)
        {
            if (LogEvent != null)
            {
                LogEvent(str);
            }
        }
        #endregion

        void m_worker_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            if (e.Error != null)
            {
            }
        }

        void m_worker_DoWork(object sender, DoWorkEventArgs e)
        {

            //if (Directory.Exists(uVisionProjectPath)) Directory.Delete(uVisionProjectPath, true);

            OnLogText("start analize");

            //ObjectList.Clear();

            Directory.CreateDirectory(uVisionProjectPath);

            WorkerParams pars = (WorkerParams)e.Argument;

            PKParser.Arg.PKArgParser ArgParser = new PKParser.Arg.PKArgParser();

            //string DefaultWorkingDir = Directory.GetCurrentDirectory();

            //List<UsedItem> LibList = new List<UsedItem>();
            //List<UsedItem> SourceList = new List<UsedItem>();

            Link Link = new Link("Link", null);

            //Собираем дерево проекта

            foreach (LogQueueItem item in pars.messages.Values)
            {
                if (item.Message.ToLower().Contains(ARMLINKPath))
                {
                    Link.ConsoleString = item.Message;
                    ParamCollection par = ArgParser.Add(item.Message);
                    if (par == null) throw new Exception(KeilWizardStrings);
                    Link.ParamCollection = par;

                    ProjectCollection LocalProjColl = new ProjectCollection();
                    Project MSBProj = LocalProjColl.LoadProject(item.ProjectBuildContext[item.ProjectBuildContext.Count - 1]);
                    string LIB_EXT = MSBProj.GetPropertyValue("LIB_EXT");
                    string OBJ_EXT = MSBProj.GetPropertyValue("OBJ_EXT");

                    foreach (ArgCollection arg in par.Values)
                    {
                        if (arg.Name == "--output")
                        {
                            Link.Name = arg[0];
                        }
                    }

                    foreach (string file in par.Files.Values)
                    {
                        RequiredLibrary lib = null;
                        RequiredObject obj = null;
                        if (Path.GetExtension(file).ToLower() == "." + LIB_EXT.ToLower())
                        {
                            lib =new RequiredLibrary(file, Link);
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
                }
            }
            ArgParser.Clear();
            //Идем по требуемым библиотекам
            this.AnalizeInputLibraries(Link.InputLibraries, pars.messages.Values);

            //Проверка Crypto.Lib
            this.CheckCryptoLib(Link.InputLibraries, pars.messages.Values);

            //Идем по всем требуемым файлам
            SortedList<int, RequiredObject> ReqObjs = Link.GetAllRequiredObjects();
            this.AnalizeInputObjects(ReqObjs, pars.messages.Values);

            if (!Link.CheckItems())
            {
                throw new Exception("Not all Link Items founded");
            }


            //Собираем необходимые для проекта файлы
            List<RequiredLibrary> ReqLib = Link.GetAllSubRequiredLibraries();

            foreach (RequiredObject obj in ReqObjs.Values)
            {
                this.AddObjFile(obj);
            }
            foreach (RequiredLibrary lib in ReqLib)
            {
                uVisionProject.AddFile(lib.OutputFileuVision, Path.GetFileNameWithoutExtension(lib.Parent.Name));
            }

            //Сортируем группы
            uVisionProject.SortGroups();

            foreach (RequiredLibrary lib in Link.InputLibraries.Values)
            {
                uVisionProject.AddFile(lib.OutputFileuVision,Path.GetFileNameWithoutExtension(Link.Name));
            }

            //Создаем таргеты
            foreach (RequiredLibrary lib in Link.InputLibraries.Values)
            {
                if (lib.Name.ToLower().Contains("crypto"))
                {
                }
                this.CreateLibraryTartet(lib);
            }

            //foreach (RequiredObject obj in Link.InputObjects.Values)
            //{
            //    this.CreateObjectTartet(obj);
            //}

            this.CreateLinkTarget(Link, pars.messages.Values);

            //this.CreateBrowseTarget(Link);

            OnLogText("Writing files");
            ///ProjectFile
            List<string> resultstrings = uVisionProject.GetAllProjectStrings();

            using (StreamWriter outfile =
                    new StreamWriter(uVisionProjectPath + @"\generated.Uv2"))
            {
                foreach (string s in resultstrings)
                {
                    outfile.WriteLine(s);
                }

            }

            ///MultiProjectFile
            using (StreamWriter outfile =
                    new StreamWriter(uVisionProjectPath + @"\project.mpw"))
            {
                outfile.WriteLine("[WORKSPACE]\r");
                outfile.WriteLine(" MPW_NAME=\"WorkSpace\"\r");
                outfile.WriteLine(" Project=\".\\generated.Uv2\",A,X,B\r\r");
            }

            ///BatFiles
            //try
            //{
                if (Directory.Exists(uVisionProjectPath + "\\BatFiles\\Prebuild\\"))
                    Directory.Delete(uVisionProjectPath + "\\BatFiles\\Prebuild\\", true);

                if (Directory.Exists(uVisionProjectPath + "\\BatFiles\\Postbuild\\"))
                    Directory.Delete(uVisionProjectPath + "\\BatFiles\\Postbuild\\", true);

                Directory.CreateDirectory(uVisionProjectPath + "\\BatFiles\\Prebuild\\");

                Directory.CreateDirectory(uVisionProjectPath + "\\BatFiles\\Postbuild\\");
            //}
           // catch
            //{
            //}



            foreach (Target t in uVisionProject.TargetList.Values)
            {
                //PreBuild
                if (t.BeforeBuild.Count > 0)
                {
                    using (StreamWriter outfile =
                        new StreamWriter(uVisionProjectPath + "\\BatFiles\\Prebuild" + @"\" + t.Name + ".bat"))
                    {
                        foreach (string s in t.BeforeBuild)
                        {
                            outfile.WriteLine(s);
                        }

                    }
                }

                if (t.AfterBuild.Count > 0)
                {
                    using (StreamWriter outfile =
                        new StreamWriter(uVisionProjectPath + "\\BatFiles\\Postbuild" + @"\" + t.Name + ".bat"))
                    {
                        foreach (string s in t.AfterBuild)
                        {
                            outfile.WriteLine(s);
                        }

                    }
                }
            }

            OnLogText("Done");

            e.Result = resultstrings;
        }


        private void AnalizeInputLibraries(SortedList<int, RequiredLibrary> Libraryes, IList<LogQueueItem> LogMessages)
        {
            PKParser.Arg.PKArgParser ArgParser = new PKParser.Arg.PKArgParser();

            foreach (RequiredLibrary lib in Libraryes.Values)
            {
                foreach (LogQueueItem item in LogMessages)
                {
                    if (item.Message.ToLower().Contains(ARMARPath))
                    {
                        ParamCollection par = ArgParser.Add(item.Message);
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

                        lib.ConsoleString = item.Message;
                        lib.ParamCollection = par;
                        lib.BuildList.AddRange(item.ProjectBuildContext);
                        lib.OutputFileuVision = uVisionProjectPath + "\\" + uVisionTargetsPath + "\\" + Path.GetFileNameWithoutExtension(lib.Name) + "\\" + Path.GetFileName(lib.Name);

                        ProjectCollection LocalProjColl = new ProjectCollection();
                        Project MSBProj = LocalProjColl.LoadProject(item.ProjectBuildContext[item.ProjectBuildContext.Count - 1]);
                        string LIB_EXT = MSBProj.GetPropertyValue("LIB_EXT");
                        string OBJ_EXT = MSBProj.GetPropertyValue("OBJ_EXT");

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
                }
                if (lib.InputLibraries.Count > 0) this.AnalizeInputLibraries(lib.InputLibraries, LogMessages);
            }
        }

        private void AnalizeInputObjects(SortedList<int, RequiredObject> Objects, IList<LogQueueItem> LogMessages)
        {
            PKParser.Arg.PKArgParser ArgParser = new PKParser.Arg.PKArgParser();

            foreach (RequiredObject obj in Objects.Values)
            {
                foreach (LogQueueItem item in LogMessages)
                {
                    if (item.Message.ToLower().Contains(ARMCCPath) || item.Message.ToLower().Contains(ARMASMPath))
                    {
                        ParamCollection par = ArgParser.Add(item.Message);
                        if (par == null) continue;

                        bool Found = false;

                        foreach (ArgCollection arg in par.Values)
                        {
                            if (arg.Name == "-o")
                            {
                                if (String.Compare(arg[0], obj.OutputFileMSBuild, StringComparison.InvariantCultureIgnoreCase) == 0) Found = true;
                            }
                        }

                        if (!Found) continue;

                        obj.ConsoleString = item.Message;
                        obj.CurrentDir = item.CurrentDir;
                        obj.ParamCollection = par;
                        obj.BuildList.AddRange(item.ProjectBuildContext);
                        obj.OutputFileuVision = uVisionProjectPath + "\\" + uVisionTargetsPath + "\\" + Path.GetFileNameWithoutExtension(obj.Name) + "\\" + Path.GetFileNameWithoutExtension(obj.Name) + ".o";

                        obj.InputFiles.AddRange(par.Files.Values);
                    }
                }
            }
        }

        private void CheckCryptoLib(SortedList<int, RequiredLibrary> Libraryes, IList<LogQueueItem> LogMessages)
        {
            PKParser.Arg.PKArgParser ArgParser = new PKParser.Arg.PKArgParser();

            foreach (RequiredLibrary lib in Libraryes.Values)
            {
                if (lib.Name.ToLower() == "crypto.lib")
                {
                    if (lib.ParamCollection != null) return;

                    foreach (LogQueueItem item in LogMessages)
                    {
                        if (item.Message.ToLower().Contains(ARMARPath))
                        {
                            ParamCollection par = ArgParser.Add(item.Message);
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

                            lib.ConsoleString = item.Message;
                            lib.ParamCollection = par;
                            lib.BuildList.AddRange(item.ProjectBuildContext);
                            lib.OutputFileuVision = uVisionProjectPath + "\\" + uVisionTargetsPath + "\\" + Path.GetFileNameWithoutExtension(lib.Name) + "\\" + Path.GetFileName(lib.Name);

                            ProjectCollection LocalProjColl = new ProjectCollection();
                            Project MSBProj = LocalProjColl.LoadProject(item.ProjectBuildContext[item.ProjectBuildContext.Count - 1]);
                            string LIB_EXT = MSBProj.GetPropertyValue("LIB_EXT");
                            string OBJ_EXT = MSBProj.GetPropertyValue("OBJ_EXT");


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
                    }
                    if (lib.InputLibraries.Count > 0) this.AnalizeInputLibraries(lib.InputLibraries, LogMessages);
                }
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
                    throw new Exception("File missing");
                }

                if (!uVisionProject.ContainsFile(path))
                {
                    List<MFBuildFile> source_list = new List<MFBuildFile>();

                    object obj = GetMFObjectFromProjectFile(reqobj.BuildList[reqobj.BuildList.Count - 1]);

                    string group = Path.GetFileNameWithoutExtension(reqobj.Parent.Name);

                    if (obj == null)
                    {
                        uVisionProject.AddFile(path, group);
                        continue;
                    }
                    else
                    {

                        if (obj.GetType() == typeof(MFSolution))
                        {
                            //MFSolution sol = (MFSolution)obj;
                        }
                        else if (obj.GetType() == typeof(MFProject))
                        {
                            MFProject proj = (MFProject)obj;
                            source_list.AddRange(proj.FastCompileFiles);
                            source_list.AddRange(proj.HeaderFiles);
                            source_list.AddRange(proj.SourceFiles);
                        }
                        else if (obj.GetType() == typeof(Library))
                        {
                            Library lib = (Library)obj;
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
            Target target = new Target();
            //Установка опций по умолчанию
            target.SeTLPC2478DefaultOptions();

            target.Name = Path.GetFileNameWithoutExtension(lib.Name);
            target.Options.OutDir += uVisionTargetsPath + "\\" + target.Name + "\\";
            target.Options.OutName = Path.GetFileNameWithoutExtension(lib.Name);

            target.Options.GenApp = TWO_STATE_BOOL.DISABLED;
            target.Options.GenLib = TWO_STATE_BOOL.ENABLED;

            target.Options.ADSFLGA = "226,31,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0";

            target.Options.ADSCCFLG.ARM_Thumb_Interworking = uVision.Project.THREE_STATE_BOOL.DISABLED;
            target.Options.ADSASFLG = "0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0";
            target.Options.Debug = "1";
            target.Options.Browse = "1";


            //Исключаем все файлы из построения
            foreach (PKStudio.uVision.Project.File f in uVisionProject.FileList.Values)
            {
                PKStudio.uVision.Project.FileOptions fileopt = new uVision.Project.FileOptions(f);
                fileopt.IncBld = THREE_STATE_BOOL.DISABLED;
                target.FilesOpton.Add(fileopt);
            }

            foreach (RequiredObject obj in lib.InputObjects.Values)
            {
                this.AddCompileFile(obj, target);
            }

            foreach (RequiredLibrary reqlib in lib.InputLibraries.Values)
            {
                PKStudio.uVision.Project.FileOptions fileOpt = target.FindFileOptions(reqlib.OutputFileuVision);
                if (fileOpt == null) throw new Exception("Can't find lib file options");
                fileOpt.IncBld = THREE_STATE_BOOL.ENABLED;
                this.CreateLibraryTartet(reqlib);
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

        private void CreateObjectTartet(RequiredObject obj)
        {
            Target target = new Target();
            //Установка опций по умолчанию
            target.SeTLPC2478DefaultOptions();

            target.Name = Path.GetFileNameWithoutExtension(obj.Name);
            target.Options.OutDir += uVisionTargetsPath + "\\" + target.Name + "\\";
            target.Options.OutName = Path.GetFileNameWithoutExtension(obj.Name);

            target.Options.GenApp = TWO_STATE_BOOL.DISABLED;
            target.Options.GenLib = TWO_STATE_BOOL.ENABLED;

            target.Options.ADSFLGA = "226,31,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0";

            target.Options.ADSCCFLG.ARM_Thumb_Interworking = uVision.Project.THREE_STATE_BOOL.DISABLED;
            target.Options.ADSASFLG = "0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0";

            target.Options.Debug = "1";
            target.Options.Browse = "1";

            //Исключаем все файлы из построения
            foreach (PKStudio.uVision.Project.File f in uVisionProject.FileList.Values)
            {
                PKStudio.uVision.Project.FileOptions fileopt = new uVision.Project.FileOptions(f);
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

        private void CreateLinkTarget(Link link, IList<LogQueueItem> messages)
        {
            Target target = new Target();
            //Установка опций по умолчанию
            target.SeTLPC2478DefaultOptions();

            target.Name = Path.GetFileNameWithoutExtension(link.Name);

            target.Options.GenApp = TWO_STATE_BOOL.ENABLED;
            target.Options.GenLib = TWO_STATE_BOOL.DISABLED;

            target.Options.ADSFLGA = "226,31,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0";

            //target.Options.OCR_RVCT = "1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,8,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,64,0,0,1,0,0,0,0,224,127,0,64,0,0";
            target.Options.ADSCCFLG.ARM_Thumb_Interworking = uVision.Project.THREE_STATE_BOOL.DISABLED;
            target.Options.ADSASFLG = "0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0";
            
            target.Options.ADSLDFG = "0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0";

            target.Options.ADSLDTA = "";
            target.Options.ADSLDDA = "";
            target.Options.Debug = "1";
            target.Options.Browse = "1";


            //Исключаем все файлы из построения
            foreach (PKStudio.uVision.Project.File f in uVisionProject.FileList.Values)
            {
                //if ((f.Type == uVision.Project.File.FILE_TYPE.C_FILE) || (f.Type == uVision.Project.File.FILE_TYPE.CPP_FILE) || (f.Type == uVision.Project.File.FILE_TYPE.ASM_FILE))
                //{
                PKStudio.uVision.Project.FileOptions fileopt = new uVision.Project.FileOptions(f);
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
                PKStudio.uVision.Project.FileOptions fileOpt = target.FindFileOptions(lib.OutputFileuVision);
                fileOpt.IncBld = THREE_STATE_BOOL.ENABLED;
            }

            //string LinkString = ARMLINKPath;

            foreach (ArgCollection arg in link.ParamCollection.Values)
            {
                if (arg.Tag == "options")
                {
                    switch (arg.Name)
                    {
                        //Ничего не надо записывать, так ккак все пути будут содержаться в файл листе
                        case "--userlibpath":
                            break;
                        case "--scatter":
                            target.Options.ADSLDSC = arg[0];
                            break;
                        case "--device":
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


            //Добавляем fromelf
            foreach (LogQueueItem item in messages)
            {
                if (item.Message.ToLower().Contains(ARMFROMELFPath))
                {
                    target.AfterBuild.Add(item.Message);
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

        //private void CreateBrowseTarget(Link link)
        //{
        //    Target target = new Target();
        //    //Установка опций по умолчанию
        //    target.SeTLPC2478DefaultOptions();

        //    target.Name = "Browse";
        //    target.Options.OutDir += uVisionTargetsPath + "\\" + target.Name + "\\";
        //    target.Options.OutName = Path.GetFileNameWithoutExtension(target.Name);

        //    target.Options.GenApp = TWO_STATE_BOOL.DISABLED;
        //    target.Options.GenLib = TWO_STATE_BOOL.DISABLED;

        //    target.Options.ADSFLGA = "226,31,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0";

        //    target.Options.ADSCCFLG.ARM_Thumb_Interworking = uVision.Project.THREE_STATE_BOOL.DISABLED;
        //    target.Options.ADSASFLG = "0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0";

        //    target.Options.Debug = "0";
        //    target.Options.Browse = "0";


        //    //Исключаем все файлы из построения
        //    foreach (PKStudio.uVision.Project.File f in uVisionProject.FileList.Values)
        //    {
        //        PKStudio.uVision.Project.FileOptions fileopt = new uVision.Project.FileOptions(f);
        //        fileopt.IncBld = THREE_STATE_BOOL.DISABLED;
        //        target.FilesOpton.Add(fileopt);
        //    }

        //    SortedList<int, RequiredObject> ReqObjs = link.GetAllRequiredObjects();

        //    foreach (RequiredObject obj in ReqObjs.Values)
        //    {
        //        this.AddCompileFile(obj, target);
        //    }

        //    target.Num = uVisionProject.TargetList.Count + 1;
        //    uVisionProject.TargetList.Add(target.Num, target);
        //}

        //private void CreateLinkTarget(Link link, IList<LogQueueItem> messages)
        //{
        //    Target target = new Target();
        //    //Установка опций по умолчанию
        //    target.SeTLPC2478DefaultOptions();

        //    target.Name = "Link";

        //    target.Options.GenApp = TWO_STATE_BOOL.DISABLED;
        //    target.Options.GenLib = TWO_STATE_BOOL.DISABLED;

        //    target.Options.ADSFLGA = "226,31,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0";

        //    //target.Options.OCR_RVCT = "1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,8,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,64,0,0,1,0,0,0,0,224,127,0,64,0,0";

        //    //target.Options.ADSLDFG = "0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0";

        //    target.Options.ADSLDTA = "";
        //    target.Options.ADSLDDA = "";

        //    //Исключаем все файлы из построения
        //    foreach (PKStudio.uVision.Project.File f in uVisionProject.FileList.Values)
        //    {
        //        if ((f.Type == uVision.Project.File.FILE_TYPE.C_FILE) || (f.Type == uVision.Project.File.FILE_TYPE.CPP_FILE) || (f.Type == uVision.Project.File.FILE_TYPE.ASM_FILE))
        //        {
        //            PKStudio.uVision.Project.FileOptions fileopt = new uVision.Project.FileOptions(f);
        //            fileopt.IncBld = THREE_STATE_BOOL.DISABLED;
        //            target.FilesOpton.Add(fileopt);
        //        }
        //    }

        //    target.Options.OutDir = Path.GetDirectoryName(link.OutputFileMSBuild) + "\\";
        //    target.Options.OutName = Path.GetFileNameWithoutExtension(link.OutputFileMSBuild);
        //    link.OutputFileuVision = link.OutputFileMSBuild;

        //    string LinkString = ARMLINKPath;

        //    foreach (ArgCollection arg in link.ParamCollection.Values)
        //    {
        //        if (arg.Tag == "options")
        //        {
        //            switch (arg.Name)
        //            {
        //                //Ничего не надо записывать, так ккак все пути будут содержаться в файл листе
        //                case "--userlibpath":
        //                    break;
        //                default:
        //                    if (arg.Count > 0)
        //                    {
        //                        foreach (string s in arg)
        //                        {
        //                            LinkString += " " + arg.Name + " " + s;
        //                        }
        //                    }
        //                    else LinkString += " " + arg.Name;
        //                    break;
        //            }
        //        }
        //    }
        //    //foreach (RequiredLibrary lib in link.InputLibraries)
        //    //{
        //    //    LinkString += " --userlibpath " + Path.GetDirectoryName(lib.OutputFileuVision);
        //    //}

        //    //foreach (RequiredObject obj in link.InputObjects)
        //    //{
        //    //    LinkString += " --userlibpath " + Path.GetDirectoryName(obj.OutputFileuVision);
        //    //}

        //    //foreach (RequiredLibrary lib in link.InputLibraries)
        //    //{
        //    //    LinkString += " " + Path.GetFileName(lib.OutputFileuVision);
        //    //}

        //    //foreach (RequiredObject obj in link.InputObjects)
        //    //{
        //    //    LinkString += " " + Path.GetFileName(obj.OutputFileuVision);
        //    //}

        //    foreach (BuildBase bb in link.AllInputs.Values)
        //    {
        //        LinkString += " " + bb.OutputFileuVision;
        //    }

        //    //foreach (RequiredLibrary lib in link.InputLibraries)
        //    //{
        //    //    LinkString += " " + lib.OutputFileuVision;
        //    //}

        //    //foreach (RequiredObject obj in link.InputObjects)
        //    //{
        //    //    LinkString += " " + obj.OutputFileuVision;
        //    //}

        //    target.AfterBuild.Add(LinkString);


        //    //Добавляем fromelf
        //    foreach (LogQueueItem item in messages)
        //    {
        //        if (item.Message.ToLower().Contains(ARMFROMELFPath))
        //        {
        //            target.AfterBuild.Add(item.Message);
        //        }
        //    }

        //    target.Num = uVisionProject.TargetList.Count + 1;
        //    uVisionProject.TargetList.Add(target.Num, target);

        //    if (target.BeforeBuild.Count > 0)
        //    {
        //        target.Options.BrunUsr_0.Run = TWO_STATE_BOOL.ENABLED;
        //        target.Options.BrunUsr_0.Command = ".\\BatFiles\\Prebuild\\" + @"\" + target.Name + ".bat";
        //    }

        //    if (target.AfterBuild.Count > 0)
        //    {
        //        target.Options.RunUsr_0.Run = TWO_STATE_BOOL.ENABLED;
        //        target.Options.RunUsr_0.Command = ".\\BatFiles\\Postbuild\\" + @"\" + target.Name + ".bat";
        //    }

        //}

        private void AddCompileFile(RequiredObject obj, Target target)
        {
            string DefaultWorkingDir = Directory.GetCurrentDirectory();
            Directory.SetCurrentDirectory(obj.CurrentDir);
            foreach (string path in obj.ParamCollection.Files.Values)
            {
                PKStudio.uVision.Project.FileOptions fileOpt = target.FindFileOptions(Path.GetFullPath(ExpandPath(path)));
                if (fileOpt == null) throw new Exception("Can't find file options");


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
                                if (fileOpt.File.Type == uVision.Project.File.FILE_TYPE.ASM_FILE)
                                    fileOpt.Misc.Add("--PD " + def);
                            }
                            break;
                        case "--split_sections":
                            fileOpt.ADSCCFLG.One_EFL_Section_per_Function = uVision.Project.THREE_STATE_BOOL.ENABLED;
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
                            PKStudio.uVision.Project.OPTIMIZATION tmp = PKStudio.uVision.Project.OPTIMIZATION.Default;
                            switch (arg[0])
                            {
                                case "0":
                                    tmp = PKStudio.uVision.Project.OPTIMIZATION.Level0;
                                    break;
                                case "1":
                                    tmp = PKStudio.uVision.Project.OPTIMIZATION.Level1;
                                    break;
                                case "2":
                                    tmp = PKStudio.uVision.Project.OPTIMIZATION.Level2;
                                    break;
                                case "3":
                                    tmp = PKStudio.uVision.Project.OPTIMIZATION.Level3;
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
                        //Этот параметр игнорируем, така uVision IDE его подставляет по умолчанию
                        case "--device":
                            break;
                        //Этот параметр обраюатываем особо
                        case "-o":
                            //obj.OutputFileuVision = uVisionProjectPath + target.Options.OutDir.Replace(".", "") + Path.GetFileNameWithoutExtension(arg[0]) + ".o ";
                            break;
                        //case "--LIST":
                        //case "--list":
                        //s = "IF NOT EXIST " + Path.GetDirectoryName(arg[0]) + " md " + Path.GetDirectoryName(arg[0]);
                        //if (!target.BeforeBuild.Contains(s))
                        //    target.BeforeBuild.Add(s);
                        //break;
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

        //private void TargetPropertiesGeneralization(Target target)
        //{
        //    List<PKStudio.uVision.Project.FileOptions> filesList = new List<uVision.Project.FileOptions>();

        //    int CFilesCount = 0;
        //    int AsmFilesCount = 0;


        //    List<string> IncludeList = new List<string>();

        //    List<string> DefineCList = new List<string>();

        //    List<string> DefineAsmList = new List<string>();

        //    List<string> MiscAsmList = new List<string>();
        //    List<string> MiscCList = new List<string>();


        //    //int splitSectionsCount = 0;
        //    //int littleendCount = 0;

        //    //int cppCount = 0;

        //    //int OptimizeCount = 0;
        //    //string DefaultOptLevel = "";

        //    //int DiagSupressCount = 0;
        //    //List<string> DefaultDiagSupress = new List<string>();


        //    foreach (PKStudio.uVision.Project.FileOptions fo in target.FilesOpton)
        //    {
        //        if (fo.IncBld == THREE_STATE_BOOL.ENABLED)
        //        {
        //            filesList.Add(fo);
        //            if (fo.File.Type == uVision.Project.File.FILE_TYPE.ASM_FILE)
        //            {
        //                AsmFilesCount++;
        //                foreach (string s in fo.Define)
        //                {
        //                    if (!DefineAsmList.Contains(s)) DefineAsmList.Add(s);
        //                }

        //                foreach (string s in fo.Misc)
        //                {
        //                    if (!MiscAsmList.Contains(s)) MiscAsmList.Add(s);
        //                }
        //            }
        //            if ((fo.File.Type == uVision.Project.File.FILE_TYPE.C_FILE) || (fo.File.Type == uVision.Project.File.FILE_TYPE.CPP_FILE))
        //            {
        //                CFilesCount++;
        //                foreach (string s in fo.Define)
        //                {
        //                    if (!DefineCList.Contains(s)) DefineCList.Add(s);
        //                }
        //                foreach (string s in fo.Misc)
        //                {
        //                    if (!MiscCList.Contains(s)) MiscCList.Add(s);
        //                }
        //            }

        //            foreach (string s in fo.Include)
        //            {
        //                if (!IncludeList.Contains(s)) IncludeList.Add(s);
        //            }
        //        }
        //    }

        //    //includes
        //    #region Includes
        //    foreach (string path in IncludeList)
        //    {
        //        int ARMCIncludeOccurrences = 0;
        //        int ARMAIncludeOccurrences = 0;

        //        foreach (PKStudio.uVision.Project.FileOptions fo in target.FilesOpton)
        //        {
        //            foreach (string s in fo.Include)
        //            {
        //                if (s == path)
        //                {
        //                    if ((fo.File.Type == uVision.Project.File.FILE_TYPE.C_FILE) || (fo.File.Type == uVision.Project.File.FILE_TYPE.CPP_FILE))
        //                        ARMCIncludeOccurrences++;
        //                    if (fo.File.Type == uVision.Project.File.FILE_TYPE.ASM_FILE)
        //                        ARMAIncludeOccurrences++;
        //                }
        //            }
        //        }

        //        if ((ARMCIncludeOccurrences == CFilesCount) && (CFilesCount > 0))
        //        {
        //            target.Options.ADSCINCD.Add(path);
        //            foreach (PKStudio.uVision.Project.FileOptions fo in filesList)
        //            {
        //                fo.Include.Remove(path);
        //            }
        //        }

        //        if ((ARMAIncludeOccurrences == AsmFilesCount) && (AsmFilesCount > 0))
        //        {
        //            target.Options.ADSAINCD.Add(path);
        //            foreach (PKStudio.uVision.Project.FileOptions fo in filesList)
        //            {
        //                fo.Include.Remove(path);
        //            }
        //        }
        //    }
        //    #endregion
        //    #region Defines C
        //    foreach (string def in DefineCList)
        //    {
        //        int ARMCOccurrences = 0;

        //        foreach (PKStudio.uVision.Project.FileOptions fo in target.FilesOpton)
        //        {
        //            if ((fo.File.Type == uVision.Project.File.FILE_TYPE.C_FILE) || (fo.File.Type == uVision.Project.File.FILE_TYPE.CPP_FILE))
        //            {
        //                foreach (string s in fo.Define)
        //                {
        //                    if (s == def)
        //                    {
        //                        ARMCOccurrences++;
        //                    }
        //                }
        //            }
        //        }

        //        if ((ARMCOccurrences == CFilesCount) && (CFilesCount > 0))
        //        {
        //            target.Options.ADSCDEFN.Add(def);
        //            foreach (PKStudio.uVision.Project.FileOptions fo in filesList)
        //            {
        //                if ((fo.File.Type == uVision.Project.File.FILE_TYPE.C_FILE) || (fo.File.Type == uVision.Project.File.FILE_TYPE.CPP_FILE))
        //                {
        //                    fo.Define.Remove(def);
        //                }
        //            }
        //        }
        //    }
        //    #endregion

        //    #region Misc C
        //    foreach (string misc in MiscCList)
        //    {
        //        int ARMCOccurrences = 0;

        //        foreach (PKStudio.uVision.Project.FileOptions fo in target.FilesOpton)
        //        {
        //            if ((fo.File.Type == uVision.Project.File.FILE_TYPE.C_FILE) || (fo.File.Type == uVision.Project.File.FILE_TYPE.CPP_FILE))
        //            {
        //                foreach (string s in fo.Misc)
        //                {
        //                    if (s == misc)
        //                    {
        //                        ARMCOccurrences++;
        //                    }
        //                }
        //            }
        //        }

        //        if ((ARMCOccurrences == CFilesCount) && (CFilesCount > 0))
        //        {
        //            target.Options.ADSCMISC.Add(misc);
        //            foreach (PKStudio.uVision.Project.FileOptions fo in filesList)
        //            {
        //                if ((fo.File.Type == uVision.Project.File.FILE_TYPE.C_FILE) || (fo.File.Type == uVision.Project.File.FILE_TYPE.CPP_FILE))
        //                {
        //                    fo.Misc.Remove(misc);
        //                }
        //            }
        //        }
        //    }
        //    #endregion

        //    #region Defines Asm
        //    foreach (string def in DefineAsmList)
        //    {
        //        int Occurrences = 0;

        //        foreach (PKStudio.uVision.Project.FileOptions fo in target.FilesOpton)
        //        {
        //            if (fo.File.Type == uVision.Project.File.FILE_TYPE.ASM_FILE)
        //            {
        //                foreach (string s in fo.Define)
        //                {
        //                    if (s == def)
        //                    {
        //                        Occurrences++;
        //                    }
        //                }
        //            }
        //        }

        //        if ((Occurrences == AsmFilesCount) && (AsmFilesCount > 0))
        //        {
        //            target.Options.ADSADEFN.Add(def);
        //            foreach (PKStudio.uVision.Project.FileOptions fo in filesList)
        //            {
        //                if (fo.File.Type == uVision.Project.File.FILE_TYPE.ASM_FILE)
        //                {
        //                    fo.Define.Remove(def);
        //                }
        //            }
        //        }
        //    }
        //    #endregion

        //    #region Misc Asm
        //    foreach (string misc in MiscAsmList)
        //    {
        //        int Occurrences = 0;

        //        foreach (PKStudio.uVision.Project.FileOptions fo in target.FilesOpton)
        //        {
        //            if (fo.File.Type == uVision.Project.File.FILE_TYPE.ASM_FILE)
        //            {
        //                foreach (string s in fo.Misc)
        //                {
        //                    if (s == misc)
        //                    {
        //                        Occurrences++;
        //                    }
        //                }
        //            }
        //        }

        //        if ((Occurrences == AsmFilesCount) && (AsmFilesCount > 0))
        //        {
        //            target.Options.ADSAMISC.Add(misc);
        //            foreach (PKStudio.uVision.Project.FileOptions fo in filesList)
        //            {
        //                if (fo.File.Type == uVision.Project.File.FILE_TYPE.ASM_FILE)
        //                {
        //                    fo.Misc.Remove(misc);
        //                }
        //            }
        //        }
        //    }
        //    #endregion

        //}


        //private void AnalizeLinkTarget(SortedList<int, LogQueueItem> consolecalls, Target target)
        //{
        //    //Установка опций по умолчанию
        //    target.SeTLPC2478DefaultOptions();

        //    target.Options.GenApp = TWO_STATE_BOOL.ENABLED;
        //    target.Options.GenLib = TWO_STATE_BOOL.DISABLED;

        //    target.Options.ADSFLGA = "226,31,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0";

        //    target.Options.OCR_RVCT = "1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,8,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,64,0,0,1,0,0,0,0,224,127,0,64,0,0";

        //    target.Options.ADSLDFG = "0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0";

        //    target.Options.ADSLDTA = "";
        //    target.Options.ADSLDDA = "";


        //    //Исключаем все файлы из построения
        //    foreach (PKStudio.uVision.Project.File f in uVisionProject.FileList.Values)
        //    {
        //        if ((f.Type == uVision.Project.File.FILE_TYPE.C_FILE) || (f.Type == uVision.Project.File.FILE_TYPE.CPP_FILE) || (f.Type == uVision.Project.File.FILE_TYPE.ASM_FILE))
        //        {
        //            PKStudio.uVision.Project.FileOptions fileopt = new uVision.Project.FileOptions(f);
        //            fileopt.IncBld = THREE_STATE_BOOL.DISABLED;
        //            target.FilesOpton.Add(fileopt);
        //        }
        //    }

        //    PKParser.Arg.PKArgParser parser = new PKArgParser();

        //    bool compileStarted = false;
        //    bool compileFinished = false;

        //    //string ObjDir = string.Empty;

        //    foreach (LogQueueItem item in consolecalls.Values)
        //    {

        //        if (item.CurrentDir != null) Directory.SetCurrentDirectory(item.CurrentDir);

        //        ParamCollection par = parser.Add(item.Message);
        //        if (par == null)
        //        {
        //            if (!compileStarted)
        //            {
        //                //Команды до компиляции
        //                //target.BeforeBuild.Add(item.Message);
        //            }
        //            else if (compileFinished)
        //            {
        //                //Команды после компиляции
        //                //target.AfterBuild.Add(item.Message);
        //            }
        //        }
        //        else
        //        {
        //            switch (par.Name)
        //            {
        //                case "armcc.exe":
        //                case "armasm.exe":
        //                    compileStarted = true;
        //                    break;
        //                case "armar.exe":
        //                    break;
        //                case "armlink.exe":
        //                    compileStarted = true;
        //                    compileFinished = true;
        //                    //Смотрим на наличие Crypto.lib
        //                    foreach (ArgCollection arg in par.Values)
        //                    {
        //                        //if (arg.Tag == "input-file-list")
        //                        //{
        //                        //    if (arg.Name.ToLower().Contains("crypto.lib"))
        //                        //    {
        //                        //        foreach (ArgCollection arg2 in par.Values)
        //                        //        {
        //                        //            if (arg2.Name == "--userlibpath")
        //                        //            {
        //                        //                foreach (string str in arg2)
        //                        //                {
        //                        //                    string s = "IF EXIST " + str + "\\crypto_stub.lib " + "copy /Y " + str + "\\crypto_stub.lib " + str + "\\crypto.lib";
        //                        //                    if (!target.BeforeBuild.Contains(s))
        //                        //                        target.BeforeBuild.Add(s);
        //                        //                }
        //                        //            }
        //                        //        }
        //                        //    }
        //                        //}

        //                        //if ((arg.Name == "--symdefs") || (arg.Name == "--list") || (arg.Name == "--scatter") || (arg.Name == "--output"))
        //                        //{
        //                        //    string s = string.Empty;
        //                        //    s = "IF NOT EXIST " + Path.GetDirectoryName(arg[0]) + " md " + Path.GetDirectoryName(arg[0]);
        //                        //    if (!target.BeforeBuild.Contains(s))
        //                        //        target.BeforeBuild.Add(s);
        //                        //}
        //                        if (arg.Name == "--output")
        //                        {
        //                            target.Options.OutDir = Path.GetDirectoryName(arg[0]) + "\\";
        //                            target.Options.OutName = Path.GetFileNameWithoutExtension(arg[0]);
        //                        }

        //                        switch (arg.Name)
        //                        {
        //                            //case "--output":
        //                            //    target.Options.OutDir = Path.GetDirectoryName(arg[0]) + "\\";
        //                            //    target.Options.OutName = Path.GetFileNameWithoutExtension(arg[0]);
        //                            //    break;

        //                            //case "--scatter":
        //                            //    target.Options.ADSLDSC = arg[0];
        //                            //    break;

        //                            case "--userlibpath":
        //                                //foreach (string s in arg)
        //                                //{
        //                                //    string str = arg.Name;
        //                                //    str += " " + s;
        //                                //    target.Options.ADSLDMC.Insert(0, str);
        //                                //}
        //                                break;

        //                            default:
        //                                string strs = arg.Name;
        //                                foreach (string s in arg)
        //                                {
        //                                    strs += " " + s;
        //                                }
        //                                if (arg.Tag == "input-file-list")
        //                                {
        //                                    if (Path.GetDirectoryName(strs) != string.Empty)
        //                                    {
        //                                        foreach (ObjectListItem OLI in ObjectList)
        //                                        {
        //                                            if (strs == OLI.MSBuildPath)
        //                                                target.Options.ADSLDMC.Add(OLI.KeilPath);
        //                                        }
        //                                    }
        //                                    else
        //                                        target.Options.ADSLDMC.Add(Path.GetFileName(strs));
        //                                }
        //                                else
        //                                    target.Options.ADSLDMC.Insert(0, strs);
        //                                break;
        //                        }


        //                    }
        //                    //target.AfterBuild.Add(item.Message);
        //                    break;
        //                default:
        //                    break;
        //            }
        //        }
        //    }

        //    foreach (Target t in uVisionProject.TargetList.Values)
        //    {
        //        target.Options.ADSLDMC.Insert(0, "--userlibpath " + uVisionProjectPath + t.Options.OutDir.Replace(".", ""));
        //    }

        //    target.Name = "Link";

        //    if (target.BeforeBuild.Count > 0)
        //    {
        //        target.Options.BrunUsr_0.Run = TWO_STATE_BOOL.ENABLED;
        //        target.Options.BrunUsr_0.Command = ".\\BatFiles\\Prebuild\\" + @"\" + target.Name + ".bat";
        //    }

        //    if (target.AfterBuild.Count > 0)
        //    {
        //        target.Options.RunUsr_0.Run = TWO_STATE_BOOL.ENABLED;
        //        target.Options.RunUsr_0.Command = ".\\BatFiles\\Postbuild\\" + @"\" + target.Name + ".bat";
        //    }
        //}

        public void NewProject(string ProjectPath)
        {
            LogQueue.Clear();
            uVisionProject = new uVisionProject();

            ProjectCollection LocalProjColl = new ProjectCollection();
            Project MSBProj = LocalProjColl.LoadProject(ProjectPath);

            ARMCCPath = MSBProj.GetPropertyValue("CC").ToLower();
            ARMASMPath = MSBProj.GetPropertyValue("AS").ToLower();
            ARMLINKPath = MSBProj.GetPropertyValue("LINK").ToLower();
            ARMARPath = MSBProj.GetPropertyValue("AR").ToLower();
            ARMFROMELFPath = MSBProj.GetPropertyValue("FromELF").ToLower();

        }

        public void EnqueueItem(string Message, string CurrentDirectory, List<string> ProjectBuildContext)
        {
            this.LogQueue.Add(this.LogQueue.Count + 1, new LogQueueItem(Message, CurrentDirectory, ProjectBuildContext));
        }

        public void Generate()
        {
            WorkerParams pars = new WorkerParams();
            pars.messages = LogQueue;
            pars.EnvVars = Environment.GetEnvironmentVariables();
            m_worker.RunWorkerAsync(pars);
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

        private bool CheckFile(string filePath, List<MFBuildFile> list)
        {
            foreach (MFBuildFile mfbf in list)
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

        private void AddHFiles(string group, List<MFBuildFile> list, uVisionProject project)
        {
            foreach (MFBuildFile mfbf in list)
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


            //смотрим солюшен ли это
            if (settingsFile != string.Empty)
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
