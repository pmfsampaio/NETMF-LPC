using System;
using System.Collections.Generic;
using Microsoft.Build.Framework;
using Microsoft.Build.Evaluation;
using System.Diagnostics;
using System.ComponentModel;

namespace PKStudio.Helpers
{
    class MSBuildHelper : IDisposable
    {
        private List<ILogger> mLoggers = new List<ILogger>();

        private BackgroundWorker m_worker;

        private class WorkerRunArgument
        {
            public string Path { get; set; }
            public string Target { get; set; }
            public string BuildType { get; set; }
            public string MediaType { get; set; }
        }

        public MSBuildHelper()
        {
            this.m_worker = new BackgroundWorker();
            this.m_worker.DoWork += new DoWorkEventHandler(m_worker_DoWork);
            this.m_worker.RunWorkerCompleted += new RunWorkerCompletedEventHandler(m_worker_RunWorkerCompleted);
            //this.m_worker.WorkerReportsProgress = true;
        }

        void m_worker_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            //throw new NotImplementedException();
        }

        void m_worker_DoWork(object sender, DoWorkEventArgs e)
        {
            WorkerRunArgument argument = (WorkerRunArgument)e.Argument;


            using (ProjectCollection BuildCollection = new ProjectCollection())
            {

                Project BuildProject = BuildCollection.LoadProject(argument.Path);

                BuildProject.SetProperty("flavor", argument.BuildType);
                BuildProject.SetProperty("memory", argument.MediaType);

                BuildProject.Build(argument.Target, mLoggers);
            }
        }

        public void Build(string Path, string target, string buildType, string mediaType)
        {
            if (m_worker.IsBusy == false)
            {
                WorkerRunArgument argument = new WorkerRunArgument();
                argument.Path = Path;
                argument.Target = target;
                argument.BuildType = buildType;
                argument.MediaType = mediaType;
                m_worker.RunWorkerAsync(argument);
            }
        }

        public List<ILogger> Loggers { get { return this.mLoggers; } }

        #region IDisposable Members

        public void Dispose()
        {
            m_worker.Dispose();
        }


        #endregion
    }
}
