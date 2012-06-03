using System.Collections.Generic;
using System.IO;
using Microsoft.Build.Construction;
using Microsoft.Build.Evaluation;
using Microsoft.Build.Framework;
using Microsoft.Build.Utilities;
using PKStudio.ItemWrappers;

namespace PKStudio.Tools.uVisionGenerator.Classes.HelpClasses
{
    /// <summary>
    /// Class for analysing MSBuild's logs. Gets required for generation messages
    /// </summary>
    class MessagesCollector : Logger
    {
        private List<string> ProjectBuildContext = new List<string>();
        private MessagesParser MFuVisionGenerator = null;
        //private List<string> ProjectNesting = new List<string>();


        #region LogStartedEvent
        public delegate void LogStartedEventDelegate();

        public event LogStartedEventDelegate LogStartedEvent;

        protected void OnLogStarted()
        {
            if (LogStartedEvent != null)
            {
                LogStartedEvent();
            }
        }
        #endregion

        #region LogFinishedEvent
        public delegate void LogFinishedEventDelegate(bool Succeeded);

        public event LogFinishedEventDelegate LogFinishedEvent;

        protected void OnLogFinished(bool Succeeded)
        {
            if (LogFinishedEvent != null)
            {
                LogFinishedEvent(Succeeded);
            }
        }
        #endregion

        #region MSBuildProjectStartedEvent
        public delegate void MSBuildProjectStartedEventDelegate();

        public event MSBuildProjectStartedEventDelegate MSBuildProjectStartedEvent;

        protected void OnMSBuildProjectStarted()
        {
            if (MSBuildProjectStartedEvent != null)
            {
                MSBuildProjectStartedEvent();
            }
        }
        #endregion


        public MessagesCollector(MessagesParser generator)
        {
            MFuVisionGenerator = generator;            
        }

        void eventSource_MessageRaised(object sender, BuildMessageEventArgs e)
        {
            if (e.GetType() == typeof(TaskCommandLineEventArgs))
            {
                TaskCommandLineEventArgs cl = (TaskCommandLineEventArgs)e;

                MFuVisionGenerator.EnqueueItem(cl.Message, Directory.GetCurrentDirectory(), this.ProjectBuildContext);
            }
        }

        void eventSource_BuildFinished(object sender, BuildFinishedEventArgs e)
        {
            OnLogFinished(e.Succeeded);
        }

        void eventSource_BuildStarted(object sender, BuildStartedEventArgs e)
        {
            OnLogStarted();
        }

        void eventSource_ProjectFinished(object sender, ProjectFinishedEventArgs e)
        {
            ProjectBuildContext.Remove(e.ProjectFile);
        }

        void eventSource_ProjectStarted(object sender, ProjectStartedEventArgs e)
        {
            ProjectBuildContext.Add(e.ProjectFile);
            OnMSBuildProjectStarted();
        }

        #region ILogger Members

        public override void Initialize(IEventSource eventSource)
        {
            eventSource.MessageRaised += new BuildMessageEventHandler(eventSource_MessageRaised);
            eventSource.BuildFinished += new BuildFinishedEventHandler(eventSource_BuildFinished);
            eventSource.BuildStarted += new BuildStartedEventHandler(eventSource_BuildStarted);
            eventSource.ProjectStarted += new ProjectStartedEventHandler(eventSource_ProjectStarted);
            eventSource.ProjectFinished += new ProjectFinishedEventHandler(eventSource_ProjectFinished);
        }

        public override void Shutdown()
        {
        }

        #endregion
    }
}
