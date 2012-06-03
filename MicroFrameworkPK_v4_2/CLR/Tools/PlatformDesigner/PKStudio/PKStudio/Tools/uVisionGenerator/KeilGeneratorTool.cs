using System.Windows.Forms;
using WeifenLuo.WinFormsUI.Docking;
using XsdInventoryFormatObject;
using System.IO;
using Scripts;
using System.ComponentModel;

namespace PKStudio.Tools.KeilGenerator
{
    public partial class KeilGeneratorTool : DockContent
    {
        protected MFProject Proj;

        private BackgroundWorker m_worker;

        public KeilGeneratorTool()
        {
            InitializeComponent();

            this.m_worker = new BackgroundWorker();
            this.m_worker.DoWork += new DoWorkEventHandler(m_worker_DoWork);
            this.m_worker.RunWorkerCompleted += new RunWorkerCompletedEventHandler(m_worker_RunWorkerCompleted);
            this.m_worker.WorkerReportsProgress = true;
        }

        /// <summary>
        /// Устанавливает MFProject для генерации
        /// </summary>
        /// <param name="LibCat"></param>
        public void SetProject(MFProject Proj)
        {
            this.Proj = Proj;
            LogRtb.Clear();
            LogAddText(Strings.MFProject + ": " + Proj.Name + "\r\n");
            LogAddText(Strings.Description + ": " + Proj.Description + "\r\n");
            LogAddText(Strings.Documentation + ": " + Proj.Documentation + "\r\n");
            LogAddText(Strings.ProjectPath + ": " + Proj.ProjectPath + "\r\n");

            GeneratedTextTB.Clear();

            m_worker.RunWorkerAsync(this.Proj);
        }

        void m_worker_DoWork(object sender, DoWorkEventArgs e)
        {
            //GenerateMDKProj((MFProject)e.Argument);
        }

        void m_worker_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
        }

        



        private delegate void SetTextCallback(RichTextBox tb, string text);
        private void SetText(RichTextBox tb, string text)
        {
            // InvokeRequired required compares the thread ID of the
            // calling thread to the thread ID of the creating thread.
            // If these threads are different, it returns true.
            if (tb.InvokeRequired)
            {
                SetTextCallback d = new SetTextCallback(SetText);
                this.BeginInvoke(d, new object[] { tb, text });
            }
            else
            {
                tb.AppendText(text);
                tb.ScrollToCaret();
            }
        }

        /// <summary>
        /// Добавить такст в лог
        /// </summary>
        /// <param name="text">Текст для добавления</param>
        public void LogAddText(string text)
        {
            this.SetText(LogRtb, text);
        }

        /// <summary>
        /// Добавить такст в сгенерированный проект
        /// </summary>
        /// <param name="text">Текст для добавления</param>
        public void GeneratedAddText(string text)
        {
            this.SetText(GeneratedTextTB, text);
        }

        private void copyToolStripMenuItem_Click(object sender, System.EventArgs e)
        {
            GeneratedTextTB.Copy();
        }

        private void selectAllToolStripMenuItem_Click(object sender, System.EventArgs e)
        {
            GeneratedTextTB.SelectAll();
        }
    }
}
