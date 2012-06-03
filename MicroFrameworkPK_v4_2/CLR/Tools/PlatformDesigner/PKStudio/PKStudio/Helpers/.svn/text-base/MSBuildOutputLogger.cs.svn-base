using System;
using Microsoft.Build.Framework;
using Microsoft.Build.Utilities;
using Microsoft.Build.Evaluation;
using Microsoft.Build.Construction;
using System.Collections.Generic;
using PKParser.PKMessParser;
using PKStudio.ItemWrappers;
using System.Threading;
using System.ComponentModel;
using System.Windows.Forms;
using System.Collections;

namespace PKStudio.Helpers
{
    public class MSBuildOutputLogger : Logger, ILoggable, IDisposable
    {
        private string currentTargets = string.Empty;
        private Queue<BuildMessage> messagesQueue;
        private AutoResetEvent newEvent;
        private BackgroundWorker m_worker;
        private ErrorsAndWarningsList mEWList;
        private int level;

        public MSBuildOutputLogger()
        {
            this.messagesQueue = new Queue<BuildMessage>();
            this.newEvent = new AutoResetEvent(false);
            this.level = 0;
            this.mEWList = new ErrorsAndWarningsList();

            this.m_worker = new BackgroundWorker();
            this.m_worker.DoWork += new DoWorkEventHandler(WorkerThread);
            this.m_worker.RunWorkerCompleted += new RunWorkerCompletedEventHandler(WorkerDone);
        }

        void WorkerDone(object sender, RunWorkerCompletedEventArgs e)
        {
            if (e.Error != null)
            {
                MessageBox.Show(e.Error.Message, Strings.Error, MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void WorkerThread(object sender, DoWorkEventArgs e)
        {
            List<BuildMessage> messageList = new List<BuildMessage>();
            bool shutdown = false;
            do
            {
                this.newEvent.WaitOne();
                lock (this.messagesQueue)
                {
                    while (this.messagesQueue.Count != 0)
                    {
                        messageList.Add(this.messagesQueue.Dequeue());
                    }
                }
                foreach (BuildMessage message in messageList)
                {
                    switch (message.Type)
                    {
                        case MessageType.BuildStarted:
                            eventSource_BuildStarted(message.Sender, message.Args as BuildStartedEventArgs);
                            break;
                        case MessageType.BuildFinished:
                            eventSource_BuildFinished(message.Sender, message.Args as BuildFinishedEventArgs);
                            break;
                        case MessageType.ProjectStarted:
                            eventSource_ProjectStarted(message.Sender, message.Args as ProjectStartedEventArgs);
                            break;
                        case MessageType.ProjectFinished:
                            eventSource_ProjectFinished(message.Sender, message.Args as ProjectFinishedEventArgs);
                            break;
                        case MessageType.TargetStarted:
                            eventSource_TargetStarted(message.Sender, message.Args as TargetStartedEventArgs);
                            break;
                        case MessageType.TargetFinished:
                            eventSource_TargetFinished(message.Sender, message.Args as TargetFinishedEventArgs);
                            break;
                        case MessageType.TaskStarted:
                            eventSource_TaskStarted(message.Sender, message.Args as TaskStartedEventArgs);
                            break;
                        case MessageType.TaskFinished:
                            eventSource_TaskFinished(message.Sender, message.Args as TaskFinishedEventArgs);
                            break;
                        case MessageType.ErrorRaised:
                            eventSource_ErrorRaised(message.Sender, message.Args as BuildErrorEventArgs);
                            break;
                        case MessageType.WarningRaised:
                            eventSource_WarningRaised(message.Sender, message.Args as BuildWarningEventArgs);
                            break;
                        case MessageType.MessageRaised:
                            eventSource_MessageRaised(message.Sender, message.Args as BuildMessageEventArgs);
                            break;
                        case MessageType.StatusEventRaised:
                            eventSource_StatusEventRaised(message.Sender, message.Args as BuildStatusEventArgs);
                            break;
                        case MessageType.CustomEventRaised:
                            eventSource_CustomEventRaised(message.Sender, message.Args as CustomBuildEventArgs);
                            break;
                        case MessageType.Shutdown:
                            shutdown = true;
                            break;
                        default:
                            break;
                    }
                }
                messageList.Clear();
            } while (shutdown == false);
        }

        #region Build Start/Finish

        void eventSource_BuildFinished_add(object sender, BuildFinishedEventArgs e)
        {
            AddMessage(sender, e, MessageType.BuildFinished);
        }
        
        void eventSource_BuildFinished(object sender, BuildFinishedEventArgs e)
        {
            //WriteLine(e.Message);
            //OnAddText(tmpstr);           

            //OnAddText("    SenderName  :       " + e.SenderName + "\n");
            //OnAddText("    Timestamp   :       " + e.Timestamp.ToString() + "\n");
            //OnAddText("    Message     :       " + e.Message + "\n");
            //OnAddText("    HelpKeyword :       " + e.HelpKeyword + "\n");
            //OnAddText("    Succeeded   :       " + e.Succeeded.ToString() + "\n");
            //OnAddText("    ThreadId    :       " + e.ThreadId.ToString() + "\n\n");
            //if (e.BuildEventContext != null)
            //{
            //    OnAddText("    BuildEventContext.BuildRequestId    :       " + e.BuildEventContext.BuildRequestId.ToString() + "\n");
            //    OnAddText("    BuildEventContext.NodeId            :       " + e.BuildEventContext.NodeId.ToString() + "\n");
            //    OnAddText("    BuildEventContext.ProjectContextId  :       " + e.BuildEventContext.ProjectContextId.ToString() + "\n");
            //    OnAddText("    BuildEventContext.ProjectInstanceId :       " + e.BuildEventContext.ProjectInstanceId.ToString() + "\n");
            //    OnAddText("    BuildEventContext.SubmissionId      :       " + e.BuildEventContext.SubmissionId.ToString() + "\n");
            //    OnAddText("    BuildEventContext.TargetId          :       " + e.BuildEventContext.TargetId.ToString() + "\n");
            //    OnAddText("    BuildEventContext.TaskId            :       " + e.BuildEventContext.TaskId.ToString() + "\n");
            //}

            WriteLine("\r\n");

            string str = "========== " + currentTargets + " " + Strings.Complete + " ";
            str += " -- " + (mEWList.ErrorsCount) + " errors, " + (mEWList.WarningsCount) + " warnings";
            WriteLine(str);
            WriteLine("\r\n");

            OnLogFinished(mEWList);
        }

        void eventSource_BuildStarted_add(object sender, BuildStartedEventArgs e)
        {
            if (this.m_worker.IsBusy == false)
            {
                this.m_worker.RunWorkerAsync();
            }
            AddMessage(sender, e, MessageType.BuildStarted);
        }

        void eventSource_BuildStarted(object sender, BuildStartedEventArgs e)
        {
            mEWList.ClearAll();

            OnLogStarted();

            //WriteLine(e.Message);
            //WriteLine("    SenderName  :       " + e.SenderName + "\n");
            //WriteLine("    Timestamp   :       " + e.Timestamp.ToString() + "\n");
            //WriteLine("    Message     :       " + e.Message + "\n");
            //WriteLine("    HelpKeyword :       " + e.HelpKeyword + "\n");
            //WriteLine("    ThreadId    :       " + e.ThreadId.ToString() + "\n\n");
            //if (e.BuildEventContext != null)
            //{
            //    WriteLine("    BuildEventContext.BuildRequestId    :       " + e.BuildEventContext.BuildRequestId.ToString() + "\n");
            //    WriteLine("    BuildEventContext.NodeId            :       " + e.BuildEventContext.NodeId.ToString() + "\n");
            //    WriteLine("    BuildEventContext.ProjectContextId  :       " + e.BuildEventContext.ProjectContextId.ToString() + "\n");
            //    WriteLine("    BuildEventContext.ProjectInstanceId :       " + e.BuildEventContext.ProjectInstanceId.ToString() + "\n");
            //    WriteLine("    BuildEventContext.SubmissionId      :       " + e.BuildEventContext.SubmissionId.ToString() + "\n");
            //    WriteLine("    BuildEventContext.TargetId          :       " + e.BuildEventContext.TargetId.ToString() + "\n");
            //    WriteLine("    BuildEventContext.TaskId            :       " + e.BuildEventContext.TaskId.ToString() + "\n");
            //}
            //WriteLine("\n    BuildEnvironment (Count: " + e.BuildEnvironment.Count.ToString() + ")\n");
            //foreach (string key in e.BuildEnvironment.Keys)
            //{
            //    WriteLine("        " + key + "    :       " + e.BuildEnvironment[key] + "\n");
            //}
        }
        #endregion

        #region Project Start/Finish

        void eventSource_ProjectFinished_add(object sender, ProjectFinishedEventArgs e)
        {
            AddMessage(sender, e, MessageType.ProjectFinished);
        }
        
        void eventSource_ProjectFinished(object sender, ProjectFinishedEventArgs e)
        {
            //object obj = GetMFObjectFromProjectFile(e.ProjectFile);

            //if (obj == null)
            //{
            //}
            //else
            //{
            //    //string str = "------ "  + Strings.Finished + " ";



            //    if (obj.GetType() == typeof(SolutionWrapper))
            //    {
            //    //    //SolutionWrapper sol = (SolutionWrapper)obj;
            //    //    //str += "Solution: " + sol.Name + " Succeeded: " + e.Succeeded;
            //    }
            //    else if (obj.GetType() == typeof(ProjectWrapper))
            //    {
            //    //    //ProjectWrapper proj = (ProjectWrapper)obj;
            //    //    //str += "Project: " + proj.Name + " Succeeded: " + e.Succeeded;

            //    }
            //    else if (obj.GetType() == typeof(LibraryWrapper))
            //    {
            //        //    //Library lib = (Library)obj;
            //        //    //str += "Library: " + lib.Name;
            //        //    return;
            //    }
            //    else
            //    {
            //        return;
            //    }

            //    //str += " -- " + LocalErrorCount + " errors, " + LocalWarningCount + " warnings";

            //    //WriteLine("\r\n");

            //    //str += " ------";
            //    //WriteLineWithIntent(str);
            //    level--;

            //}
        }


        void eventSource_ProjectStarted_add(object sender, ProjectStartedEventArgs e)
        {
            AddMessage(sender, e, MessageType.ProjectStarted);
        }
        
        void eventSource_ProjectStarted(object sender, ProjectStartedEventArgs e)
        {

            //object obj = GetMFObjectFromProjectFile(e.ProjectFile);

            //if (obj == null)
            //{
            //}
            //else
            //{
                string str = "------ " + e.TargetNames + " " /*+ Strings.Started + " "*/;

                currentTargets = e.TargetNames;

                string name = string.Empty;
                string type = string.Empty;
                foreach (DictionaryEntry property in e.Properties)
                {
                    if (property.Key as string == "OutputType")
                    {
                        type = property.Value as string;
                    }
                    if (property.Key as string == "AssemblyName")
                    {
                        name = property.Value as string;
                    }
                }

                if ((e.TargetNames == string.Empty) || (name == string.Empty))
                    return;

                str += string.Format("{0}: {1}", type, name);

            //    if (obj.GetType() == typeof(SolutionWrapper))
            //    {
            //        SolutionWrapper sol = (SolutionWrapper)obj;
            //        str += "Solution: " + sol.Name;
            //    }
            //    else if (obj.GetType() == typeof(ProjectWrapper))
            //    {
            //        //WriteLine("\r\n");
            //        ProjectWrapper proj = (ProjectWrapper)obj;
            //        str += "Project: " + proj.Name;
            //    }
            //    else if (obj.GetType() == typeof(LibraryWrapper))
            //    {
            //        LibraryWrapper lib = (LibraryWrapper)obj;
            //        str += "Library: " + lib.Name;
            //    }
            //    else
            //    {
            //        return;
            //    }

            //    str += " ------";

                WriteLineWithIntent(str);
            //    level++;
            //}
        }
        #endregion

        #region Target Start/Finish

        void eventSource_TargetFinished_add(object sender, TargetFinishedEventArgs e)
        {
            AddMessage(sender, e, MessageType.TargetFinished);
        }
        
        void eventSource_TargetFinished(object sender, TargetFinishedEventArgs e)
        {
            //throw new NotImplementedException();
        }

        void eventSource_TargetStarted_add(object sender, TargetStartedEventArgs e)
        {
            AddMessage(sender, e, MessageType.TargetStarted);
        }

        void eventSource_TargetStarted(object sender, TargetStartedEventArgs e)
        {
            //throw new NotImplementedException();
        }
        #endregion

        #region Task Start/Finish

        void eventSource_TaskFinished_add(object sender, TaskFinishedEventArgs e)
        {
            AddMessage(sender, e, MessageType.TaskFinished);
        }
        
        void eventSource_TaskFinished(object sender, TaskFinishedEventArgs e)
        {
            //throw new NotImplementedException();
        }

        void eventSource_TaskStarted_add(object sender, TaskStartedEventArgs e)
        {
            AddMessage(sender, e, MessageType.TaskStarted);
        }

        void eventSource_TaskStarted(object sender, TaskStartedEventArgs e)
        {
            //throw new NotImplementedException();
            OnBuildStep();
        }
        #endregion


        void eventSource_ErrorRaised_add(object sender, BuildErrorEventArgs e)
        {
            AddMessage(sender, e, MessageType.ErrorRaised);
        }
        
        void eventSource_ErrorRaised(object sender, BuildErrorEventArgs e)
        {
            //string line = string.Empty;
            //if (e.File == "EXEC")
            //{
            //    line = Strings.Error + " " + e.Message;
            //}
            //else
            //{
            //    line = e.File + "(" + e.LineNumber + "," + e.ColumnNumber + "): " + Strings.Error + " " + e.Code + ": " + e.Message;
            //}

            WEMessage message = new WEMessage();
            message.Code = e.Code;
            FileMessageObject FMO = new FileMessageObject();
            message.MessageObject = FMO;
            FMO.ColumnNumber = e.ColumnNumber;
            FMO.EndColumnNumber = e.EndColumnNumber;
            FMO.LineNumber = e.LineNumber;
            FMO.EndLineNumber = e.EndLineNumber;
            FMO.File = e.File;
            message.Message = e.Message;

            if (mEWList.AddError(message))
            {
                WriteIntent();
                this.OnError(message);
            }
        }

        void eventSource_WarningRaised_add(object sender, BuildWarningEventArgs e)
        {
            AddMessage(sender, e, MessageType.WarningRaised);
        }

        
        void eventSource_WarningRaised(object sender, BuildWarningEventArgs e)
        {
            //string line = string.Empty;
            //if (e.File == "EXEC")
            //{
            //    line = Strings.Warning + " "+ e.Message;
            //}
            //else
            //{
            //    line = e.File + "(" + e.LineNumber + "," + e.ColumnNumber + "): " + Strings.Warning + " " + e.Code + ": " + e.Message;
            //}


            WEMessage message = new WEMessage();
            message.Code = e.Code;
            FileMessageObject FMO = new FileMessageObject();
            message.MessageObject = FMO;
            FMO.ColumnNumber = e.ColumnNumber;
            FMO.EndColumnNumber = e.EndColumnNumber;
            FMO.LineNumber = e.LineNumber;
            FMO.EndLineNumber = e.EndLineNumber;
            FMO.File = e.File;
            message.Message = e.Message;


            if (mEWList.AddWarning(message))
            {
                WriteIntent();
                this.OnWarning(message);
            }
        }

        void eventSource_MessageRaised_add(object sender, BuildMessageEventArgs e)
        {
            AddMessage(sender, e, MessageType.MessageRaised);
        }

        
        void eventSource_MessageRaised(object sender, BuildMessageEventArgs e)
        {
            //if ((e.Importance == MessageImportance.High && IsVerbosityAtLeast(LoggerVerbosity.Minimal))
            //    || (e.Importance == MessageImportance.Normal && IsVerbosityAtLeast(LoggerVerbosity.Normal))
            //    || (e.Importance == MessageImportance.Low && IsVerbosityAtLeast(LoggerVerbosity.Detailed))
            //    )
            //{
            //WriteLineWithSenderAndMessage(String.Empty, e);
            //}

            //WriteLineWithIntent(e.Message);
            //this.OnMessage(e.Message);
            MessInfo Messinfo = new MessInfo(e.Message);
            if (Messinfo.Success)
            {
                WEMessage message = new WEMessage();
                message.Code = Messinfo.Error;
                FileMessageObject FMO = new FileMessageObject();
                message.MessageObject = FMO;
                FMO.ColumnNumber = 0;
                FMO.EndColumnNumber = 0;
                FMO.LineNumber = Messinfo.Line;
                FMO.EndLineNumber = 0;
                FMO.File = Messinfo.File;
                message.Message = Messinfo.Message;

                //string line = string.Empty;

                switch (Messinfo.Cond)
                {
                    case MessInfo.Level.Error:
                        //line = message.File + "(" + message.LineNumber + "," + message.ColumnNumber + "): " + Strings.Error + " " + message.Code + ": " + message.Message;
                        if (mEWList.AddError(message))
                        {
                            WriteIntent();
                            this.OnError(message);
                        }
                        break;
                    case MessInfo.Level.Warning:
                        //line = message.File + "(" + message.LineNumber + "," + message.ColumnNumber + "): " + Strings.Warning + " " + message.Code + ": " + message.Message;
                        if (mEWList.AddWarning(message))
                        {
                            WriteIntent();
                            this.OnWarning(message);
                        }
                        break;
                }

                //if(line != string.Empty)
                //WriteLineWithIntent(line);
            }


            //if (e.Message.ToLower().Contains("error:"))
            //{

            //}

            //if (e.Message.ToLower().Contains("warning:"))
            //{
            //    WriteLineWithIntent(e.Message);
            //}

            if (e.GetType() == typeof(TaskCommandLineEventArgs))
            {
                if (e.Message.ToLower().Contains("error:"))
                {
                    WriteLineWithIntent(Strings.ConsoleError + ":   " + e.Message);
                }

                if (e.Message.ToLower().Contains("warning:"))
                {
                    WriteLineWithIntent(Strings.ConsoleError + ":   " + e.Message);
                }
            }

        }

        void eventSource_StatusEventRaised_add(object sender, BuildStatusEventArgs e)
        {
            AddMessage(sender, e, MessageType.StatusEventRaised);
        }


        void eventSource_StatusEventRaised(object sender, BuildStatusEventArgs e)
        {
            //WriteLineWithSenderAndMessage(String.Empty, e);
        }

        void eventSource_CustomEventRaised_add(object sender, CustomBuildEventArgs e)
        {
            AddMessage(sender, e, MessageType.CustomEventRaised);
        }


        void eventSource_CustomEventRaised(object sender, CustomBuildEventArgs e)
        {
            //WriteLineWithSenderAndMessage(String.Empty, e);            
        }



        /// <summary>
        /// Write a line to the log, adding the SenderName and Message
        /// (these parameters are on all MSBuild event argument objects)
        /// </summary>
        private void WriteLineWithSenderAndMessage(string line, BuildEventArgs e)
        {
            if (0 == String.Compare(e.SenderName, "MSBuild", true /*ignore case*/))
            {
                // Well, if the sender name is MSBuild, let's leave it out for prettiness
                WriteLine(line, e);
            }
            else
            {
                WriteLine(e.SenderName + ": " + line, e);
            }
        }


        private void WriteLineWithIntent(string line)
        {
            WriteIntent();
            WriteLine(line + "\r\n");
        }

        private void WriteIntent()
        {
            for (int i = level; i > 0; i--)
            {
                WriteLine("\t");
            }
        }

        /// <summary>
        /// Just write a line to the log
        /// </summary>
        private void WriteLine(string line, BuildEventArgs e)
        {
            for (int i = level; i > 0; i--)
            {
                WriteLine("\t");
            }
            WriteLine(line + e.Message + "\r\n");
        }

        private void WriteLine(string str)
        {
            OnMessage(str);
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
            if (lib != null)
                return lib;

            foreach (var item in PK.Wrapper.Solution.Projects)
            {
                if (item.Guid == guid)
                {
                    project = item;
                    return project;
                }
            }


            //Ru: смотрим солюшен ли это
            //En: Is this solution?
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



        #region ILogger Members

        public override void Initialize(IEventSource eventSource)
        {
            eventSource.BuildStarted += new BuildStartedEventHandler(eventSource_BuildStarted_add);
            eventSource.BuildFinished += new BuildFinishedEventHandler(eventSource_BuildFinished_add);

            eventSource.ProjectStarted += new ProjectStartedEventHandler(eventSource_ProjectStarted_add);
            eventSource.ProjectFinished += new ProjectFinishedEventHandler(eventSource_ProjectFinished_add);

            eventSource.TargetStarted += new TargetStartedEventHandler(eventSource_TargetStarted_add);
            eventSource.TargetFinished += new TargetFinishedEventHandler(eventSource_TargetFinished_add);

            eventSource.TaskStarted += new TaskStartedEventHandler(eventSource_TaskStarted_add);
            eventSource.TaskFinished += new TaskFinishedEventHandler(eventSource_TaskFinished_add);

            eventSource.ErrorRaised += new BuildErrorEventHandler(eventSource_ErrorRaised_add);
            eventSource.WarningRaised += new BuildWarningEventHandler(eventSource_WarningRaised_add);
            eventSource.MessageRaised += new BuildMessageEventHandler(eventSource_MessageRaised_add);

            eventSource.StatusEventRaised += new BuildStatusEventHandler(eventSource_StatusEventRaised_add);

            eventSource.CustomEventRaised += new CustomBuildEventHandler(eventSource_CustomEventRaised_add);

            //eventSource.BuildStarted += new BuildStartedEventHandler(eventSource_BuildStarted);
            //eventSource.BuildFinished += new BuildFinishedEventHandler(eventSource_BuildFinished);

            //eventSource.ProjectStarted += new ProjectStartedEventHandler(eventSource_ProjectStarted);
            //eventSource.ProjectFinished += new ProjectFinishedEventHandler(eventSource_ProjectFinished);

            //eventSource.TargetStarted += new TargetStartedEventHandler(eventSource_TargetStarted);
            //eventSource.TargetFinished += new TargetFinishedEventHandler(eventSource_TargetFinished);

            //eventSource.TaskStarted += new TaskStartedEventHandler(eventSource_TaskStarted);
            //eventSource.TaskFinished += new TaskFinishedEventHandler(eventSource_TaskFinished);

            //eventSource.ErrorRaised += new BuildErrorEventHandler(eventSource_ErrorRaised);
            //eventSource.WarningRaised += new BuildWarningEventHandler(eventSource_WarningRaised);
            //eventSource.MessageRaised += new BuildMessageEventHandler(eventSource_MessageRaised);

            //eventSource.StatusEventRaised += new BuildStatusEventHandler(eventSource_StatusEventRaised);

            //eventSource.CustomEventRaised += new CustomBuildEventHandler(eventSource_CustomEventRaised);
        
        }

        public override void Shutdown()
        {
            AddMessage(null, EventArgs.Empty, MessageType.Shutdown);
            if (m_worker.IsBusy)
            {
                while (m_worker.IsBusy)
                {
                //    Application.DoEvents();
                }
            }
        }

        #endregion

        private enum MessageType
        {
            BuildStarted,
            BuildFinished,
            ProjectStarted,
            ProjectFinished,
            TargetStarted,
            TargetFinished,
            TaskStarted,
            TaskFinished,
            ErrorRaised,
            WarningRaised,
            MessageRaised,
            StatusEventRaised,
            CustomEventRaised,
            Shutdown
        }
        private class BuildMessage
        {
            public BuildMessage(object Sender, EventArgs Args, MessageType Type)
            {
                this.Sender = Sender;
                this.Args = Args;
                this.Type = Type;

            }

            public EventArgs Args { get; set; }
            public MessageType Type { get; set; }
            public object Sender { get; set; }
        }

        private void AddMessage(object sender, EventArgs args, MessageType type)
        {
            lock(this.messagesQueue)
            {
                this.messagesQueue.Enqueue(new BuildMessage(sender, args, type));
                newEvent.Set();
            }
        }

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

        public event EventHandler BuildStepEvent;
        protected void OnBuildStep()
        {
            if (BuildStepEvent != null)
            {
                BuildStepEvent(this, new EventArgs());
            }
        }

        public event EventHandler<WarningEventArgs> WarningEvent;
        protected void OnWarning(WEMessage Warning)
        {
            if (WarningEvent != null)
            {
                WarningEvent(this, new WarningEventArgs(Warning));
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
    }
}
