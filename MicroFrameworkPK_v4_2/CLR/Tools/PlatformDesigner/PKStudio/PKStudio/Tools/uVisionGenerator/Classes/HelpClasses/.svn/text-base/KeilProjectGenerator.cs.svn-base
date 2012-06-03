using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;
using Microsoft.Build.Framework;
using PKStudio.Tools.uVisionGenerator.Classes.uvProjectClasses;
using Microsoft.Build.Evaluation;
using System.IO;

namespace PKStudio.Tools.uVisionGenerator.Classes.HelpClasses
{
    [Serializable]
    public class KeilProjectGeneratorException : Exception
    {
        public KeilProjectGeneratorException() { }
        public KeilProjectGeneratorException(string message) : base(message) { }
        public KeilProjectGeneratorException(string message, Exception inner) : base(message, inner) { }
        protected KeilProjectGeneratorException(
          System.Runtime.Serialization.SerializationInfo info,
          System.Runtime.Serialization.StreamingContext context)
            : base(info, context) { }
    }


    class KeilProjectGenerator : IDisposable
    {
        private class WorkerRunArgument
        {
            public ConvertConfig ConvertConfig { get; set; }
        }

        private ConvertConfig config = null;
        private uVisionProject UVProject = new uVisionProject();
        private int sleeptime = 1000;


        private BackgroundWorker m_worker;

        public KeilProjectGenerator()
        {
            this.m_worker = new BackgroundWorker();
            this.m_worker.DoWork += new DoWorkEventHandler(m_worker_DoWork);
        }

        void m_worker_DoWork(object sender, DoWorkEventArgs e)
        {
            WorkerRunArgument argument = (WorkerRunArgument)e.Argument;

            this.OnLog(new GeneratingLogMessage("", GeneratingLogMessage.WORK_TYPE.CONVERT_SOLUTION, GeneratingLogMessage.WORK_STATE.START));

            uVisionMultiProjectWorkspace uVisionMPW = new uVisionMultiProjectWorkspace();
            uVisionMPW.Name = argument.ConvertConfig.Name;

            GeneratingLogMessage.WORK_TYPE workType = GeneratingLogMessage.WORK_TYPE.UNKNOWN;

            try
            {
                foreach (ConvertableMFProject proj in argument.ConvertConfig.ProjectList)
                {

                    this.OnLog(new GeneratingLogMessage(proj.Project.Name.Trim(), GeneratingLogMessage.WORK_TYPE.CONVERT_PROJECT, GeneratingLogMessage.WORK_STATE.START));
                    UVProject = new uVisionProject();
                    UVProject.Name = proj.Project.Name.Trim();
                    UVProject.ProjectPath = config.SolutionPath + @"\" + UVProject.Name;
                    UVProject.DefaultOptions = argument.ConvertConfig.Processor;
                    string path = argument.ConvertConfig.SolutionPath + "\\" + proj.Project.Name.Trim();
                    MessagesParser mParser = new MessagesParser(UVProject, path);
                    MessagesCollector logger = new MessagesCollector(mParser);
                    logger.Verbosity = LoggerVerbosity.Diagnostic;
                    logger.MSBuildProjectStartedEvent += new MessagesCollector.MSBuildProjectStartedEventDelegate(logger_MSBuildProjectStartedEvent);
                    mParser.LogEvent += new MessagesParser.LogEventDelegate(mParser_LogEvent);

                    //Run project building
                    workType = GeneratingLogMessage.WORK_TYPE.BUILD_PROJECT;
                    this.OnLog(new GeneratingLogMessage(uVisionGenerator.Wizard.KeilWizardStrings.IDS_BUILDING, workType, GeneratingLogMessage.WORK_STATE.START));
                    if (!StartMSBuild(proj, logger))
                    {
                        //Cant't build project
                        throw new KeilProjectGeneratorException(uVisionGenerator.Wizard.KeilWizardStrings.IDS_BUILD_ERROR);
                    }
                    this.OnLog(new GeneratingLogMessage(uVisionGenerator.Wizard.KeilWizardStrings.IDS_BUILDING, workType, GeneratingLogMessage.WORK_STATE.DONE));
                    System.Threading.Thread.Sleep(sleeptime);

                    workType = GeneratingLogMessage.WORK_TYPE.CONVERT_PROJECT;

                    mParser.Convert(proj.Project.ProjectPath);

                    uVisionMPW.Projects.Add(UVProject);

                    this.OnLog(new GeneratingLogMessage(proj.Project.Name.Trim(), GeneratingLogMessage.WORK_TYPE.CONVERT_PROJECT, GeneratingLogMessage.WORK_STATE.DONE));
                    System.Threading.Thread.Sleep(sleeptime);
                }

                workType = GeneratingLogMessage.WORK_TYPE.WRITING_FILES;
                this.OnLog(new GeneratingLogMessage("", GeneratingLogMessage.WORK_TYPE.WRITING_FILES, GeneratingLogMessage.WORK_STATE.START));

                try
                {
                    if (Directory.Exists(config.SolutionPath)) Directory.Delete(config.SolutionPath, true);
                    Directory.CreateDirectory(config.SolutionPath);
                }
                catch { }

                int index = 0;
                foreach (uVisionProject proj in uVisionMPW.Projects)
                {
                    index++;
                    this.OnLog(new GeneratingLogMessage("", GeneratingLogMessage.WORK_TYPE.WRITING_FILES, GeneratingLogMessage.WORK_STATE.WORKING, (int)((index * 100) / uVisionMPW.Projects.Count)));

                    string projpath = proj.ProjectPath;

                    ///ProjectFile
                    List<string> resultstrings = proj.AllProjectStrings;

                    if (Directory.Exists(projpath))
                        Directory.Delete(projpath, true);
                    Directory.CreateDirectory(projpath);

                    using (StreamWriter outfile =
                        new StreamWriter(projpath + @"\" + proj.Name + ".Uv2"))
                    {
                        foreach (string s in resultstrings)
                        {
                            outfile.WriteLine(s);
                        }
                    }
                    ///Scatter file

                    foreach (Target t in proj.TargetList.Values)
                    {
                        if (!string.IsNullOrEmpty(t.Options.ADSLDSC))
                        {
                            using (StreamWriter outfile = new StreamWriter(t.Options.ADSLDSC))
                            {
                                foreach (string s in proj.Scatter.Values)
                                {
                                    outfile.WriteLine(s);
                                }

                            }
                        }
                    }

                    ///BatFiles
                    try
                    {
                        if (Directory.Exists(projpath + "\\BatFiles\\Prebuild\\"))
                            Directory.Delete(projpath + "\\BatFiles\\Prebuild\\", true);

                        if (Directory.Exists(projpath + "\\BatFiles\\Postbuild\\"))
                            Directory.Delete(projpath + "\\BatFiles\\Postbuild\\", true);

                        Directory.CreateDirectory(projpath + "\\BatFiles\\Prebuild\\");

                        Directory.CreateDirectory(projpath + "\\BatFiles\\Postbuild\\");
                    }
                    catch { }



                    foreach (Target t in proj.TargetList.Values)
                    {
                        //PreBuild
                        if (t.BeforeBuild.Count > 0)
                        {
                            using (StreamWriter outfile =
                                new StreamWriter(projpath + "\\BatFiles\\Prebuild" + @"\" + t.Name + ".bat"))
                            {
                                foreach (string s in t.BeforeBuild)
                                {
                                    outfile.WriteLine(s);
                                }

                            }
                        }
                        //PostBuild
                        if (t.AfterBuild.Count > 0)
                        {
                            using (StreamWriter outfile =
                                new StreamWriter(projpath + "\\BatFiles\\Postbuild" + @"\" + t.Name + ".bat"))
                            {
                                foreach (string s in t.AfterBuild)
                                {
                                    outfile.WriteLine(s);
                                }

                            }
                        }
                    }
                }

                ///MultiProjectFile
                using (StreamWriter outfile =
                        new StreamWriter(config.SolutionPath + @"\" + uVisionMPW.Name + ".mpw"))
                {
                    outfile.WriteLine("[WORKSPACE]\r");
                    outfile.WriteLine(" MPW_NAME=\"" + uVisionMPW.Name + "\"\r");
                    string s = string.Empty;
                    for (int i = 0; i < uVisionMPW.Projects.Count; i++)
                    {
                        uVisionProject proj = uVisionMPW.Projects[i];
                        if (i == 0)
                            s = " Project=\".\\" + proj.Name + "\\" + proj.Name + ".Uv2\",A\r\r";
                        else
                            s = " Project=\".\\" + proj.Name + "\\" + proj.Name + ".Uv2\"\r\r";
                        outfile.WriteLine(s);
                    }
                }

                config.Result = uVisionMPW;

                this.OnLog(new GeneratingLogMessage("", GeneratingLogMessage.WORK_TYPE.WRITING_FILES, GeneratingLogMessage.WORK_STATE.DONE));

                this.OnLog(new GeneratingLogMessage("", GeneratingLogMessage.WORK_TYPE.CONVERT_SOLUTION, GeneratingLogMessage.WORK_STATE.DONE));
            }
            catch (Exception ex)
            {
                this.OnLog(new GeneratingLogMessage(ex.Message, workType, GeneratingLogMessage.WORK_STATE.ERROR));
            }


        }

        void mParser_LogEvent(GeneratingLogMessage mess)
        {
            this.OnLog(mess);
        }

        void logger_MSBuildProjectStartedEvent()
        {
            this.OnLog(new GeneratingLogMessage(uVisionGenerator.Wizard.KeilWizardStrings.IDS_BUILDING, GeneratingLogMessage.WORK_TYPE.BUILD_PROJECT, GeneratingLogMessage.WORK_STATE.WORKING));
        }

        public void Generate(ConvertConfig cfg)
        {
            this.config = cfg;

            WorkerRunArgument argument = new WorkerRunArgument();
            argument.ConvertConfig = cfg;
            m_worker.RunWorkerAsync(argument);
        }

        /// <summary>
        /// Runs project building
        /// </summary>
        /// <param name="proj"></param>
        /// <param name="logger"></param>
        private bool StartMSBuild(ConvertableMFProject proj, ILogger logger)
        {
            List<ILogger> loggerList = new List<ILogger>();

            loggerList.Add(logger);
            using (ProjectCollection BuildCollection = new ProjectCollection())
            {
                Project BuildProject = BuildCollection.LoadProject(PK.Wrapper.ExpandEnvVars(proj.Project.ProjectPath, ""));

                BuildProject.SetProperty("flavor", proj.BuildType);
                BuildProject.SetProperty("memory", proj.MediaType);

                return BuildProject.Build("Rebuild", loggerList);
            }
        }


        #region Events
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

        #region IDisposable Members

        protected virtual void Dispose(bool disposing)
        {
            if (disposing)
            {
                // dispose managed resources
                m_worker.Dispose();
            }
            // free native resources
        }


        public void Dispose()
        {
            Dispose(true);
            //GC.SuppressFinalize(this);
        }

        #endregion
    }
}
