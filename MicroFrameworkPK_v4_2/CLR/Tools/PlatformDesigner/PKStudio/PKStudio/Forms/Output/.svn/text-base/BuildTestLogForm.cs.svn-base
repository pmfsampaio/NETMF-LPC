using PKStudio.Forms.BaseForms;

namespace PKStudio.Forms.Build
{
    public partial class BuildTestLogForm : BasePKInventoryForm
    {
        private PKStudio.Helpers.MSBuildLogAnalizer mLogger = new Helpers.MSBuildLogAnalizer();

        public BuildTestLogForm()
        {
            InitializeComponent();
            mLogger.AddTextEvent +=new Helpers.MSBuildLogAnalizer.AddTextEventDelegate(mLogger_AddTextEvent);
            mLogger.LogStartedEvent += new Helpers.MSBuildLogAnalizer.LogStartedEventDelegate(mLogger_LogStartedEvent);
        }

        void mLogger_LogStartedEvent()
        {
            this.ClearAll();
        }

        public Microsoft.Build.Framework.ILogger MSBuildLogger { get { return mLogger; } }

        void mLogger_AddTextEvent(string text)
        {
            this.AppendText(text);
        }

        private void toolStripButton1_Click(object sender, System.EventArgs e)
        {
            this.ClearAll();
        }

        private delegate void SetTextCallback(string text);
        private void AppendText(string text)
        {
            if (richTextBox1.InvokeRequired)
            {
                SetTextCallback d = new SetTextCallback(AppendText);
                this.BeginInvoke(d, new object[] { text });
            }
            else
            {
                richTextBox1.AppendText(text);
                richTextBox1.ScrollToCaret();
                //Application.DoEvents();
            }
        }

        private delegate void ClearAllCallback();
        private void ClearAll()
        {
            if (richTextBox1.InvokeRequired)
            {
                ClearAllCallback d = new ClearAllCallback(ClearAll);
                this.BeginInvoke(d, new object[] { });
            }
            else
            {
                richTextBox1.Clear();
                richTextBox1.ScrollToCaret();
                //Application.DoEvents();
            }
        }
    }
}
