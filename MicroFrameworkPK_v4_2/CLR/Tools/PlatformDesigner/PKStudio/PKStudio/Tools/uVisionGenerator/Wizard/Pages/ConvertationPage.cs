using System;
using System.Windows.Forms;
using PKStudio.Tools.uVisionGenerator.Classes.HelpClasses;
using PKStudio.ItemWrappers;

namespace PKStudio.Tools.uVisionGenerator.Wizard.Pages
{
    public partial class ConvertationPage : BasePage
    {
        private enum IMAGE_KEYS : int
        {
            DONE = 0,
            RUN = 1,
            PAUSE = 2,
            FAIL = 3,
            APPLICATION = 4,
            APPLICATION_OK = 5,
            VOID = -1,
        }

        KeilProjectGenerator generator = new KeilProjectGenerator();


        private ListViewItem solutionItem = null;
        private ListViewItem projectLogItem = null;
        private ListViewItem currentLogItem = null;

        public ConvertationPage(SolutionWrapper sol, ConvertConfig config)
            : base(sol, config)
        {
            InitializeComponent();
            StatusLbl.Text = "";
            generator.LogEvent += new KeilProjectGenerator.LogEventDelegate(generator_LogEvent);
        }

        void generator_LogEvent(GeneratingLogMessage mess)
        {
            if (mess.WorkType == GeneratingLogMessage.WORK_TYPE.CONVERT_PROJECT)
            {
                switch (mess.WorkState)
                {
                    case GeneratingLogMessage.WORK_STATE.START:

                        ListViewItem tmp = this.AddLogItem("");
                        SetLogItemImageIndex(tmp, IMAGE_KEYS.VOID);

                        projectLogItem = this.AddLogItem(KeilWizardStrings.IDS_CONVERTING_PROJECT + " \"" + mess.Message + "\"");
                        SetLogItemImageIndex(projectLogItem, IMAGE_KEYS.APPLICATION);                        
                        break;
                    case GeneratingLogMessage.WORK_STATE.WORKING:
                        break;
                    case GeneratingLogMessage.WORK_STATE.DONE:
                        projectLogItem = this.AddLogItem(KeilWizardStrings.IDS_PROJECT + " \"" + mess.Message + "\" " + KeilWizardStrings.IDS_CONVERTED);
                        SetLogItemImageIndex(projectLogItem, IMAGE_KEYS.APPLICATION_OK);
                        break;
                    case GeneratingLogMessage.WORK_STATE.ERROR:
                        SetLogItemtext(currentLogItem, mess.Message);
                        SetLogItemImageIndex(currentLogItem, IMAGE_KEYS.FAIL);                        
                        break;
                    default:
                        break;
                }

            }
            else if (mess.WorkType == GeneratingLogMessage.WORK_TYPE.CONVERT_SOLUTION)
            {
                switch (mess.WorkState)
                {
                    case GeneratingLogMessage.WORK_STATE.START:
                        solutionItem = this.AddLogItem(KeilWizardStrings.IDS_CONVERTING_STARTED);
                        SetLogItemImageIndex(solutionItem, IMAGE_KEYS.VOID);
                        this.OnConvertationStart(this,EventArgs.Empty);
                        break;
                    case GeneratingLogMessage.WORK_STATE.WORKING:
                        break;
                    case GeneratingLogMessage.WORK_STATE.DONE:
                        ListViewItem tmp = this.AddLogItem("");
                        SetLogItemImageIndex(tmp, IMAGE_KEYS.VOID);

                        solutionItem = this.AddLogItem(KeilWizardStrings.IDS_CONVERTION_COMPLITED);
                        SetLogItemImageIndex(solutionItem, IMAGE_KEYS.VOID);
                        SetLabelText(StatusLbl, KeilWizardStrings.IDS_CONVERTION_COMPLITED);
                        this.OnConvertationStop(false);
                        break;
                    case GeneratingLogMessage.WORK_STATE.ERROR:
                        this.OnConvertationStop(true);
                        break;
                    default:
                        break;
                }
            }
            else
            {
                string s = string.Empty;
                switch (mess.WorkState)
                {
                    case GeneratingLogMessage.WORK_STATE.START:
                        switch (mess.WorkType)
                        {
                            case GeneratingLogMessage.WORK_TYPE.BUILD_PROJECT:
                                s = KeilWizardStrings.IDS_BUILDING;
                                SetProgressBarParams(progressBar1, 0, 100, 1);
                                this.OnBuildStart(this,EventArgs.Empty);
                                break;
                            case GeneratingLogMessage.WORK_TYPE.CREATE_PROJECT_TREE:
                                s = KeilWizardStrings.IDS_CREATING_PROJECT_TREE;
                                break;
                            case GeneratingLogMessage.WORK_TYPE.CREATE_FILE_LIST:
                                s = KeilWizardStrings.IDS_CREATING_FILE_LIST;
                                break;
                            case GeneratingLogMessage.WORK_TYPE.CREATE_TARGETS:
                                s = KeilWizardStrings.IDS_CREATING_TARGETS;
                                break;
                            case GeneratingLogMessage.WORK_TYPE.WRITING_FILES:
                                ListViewItem tmp = this.AddLogItem("");
                                SetLogItemImageIndex(tmp, IMAGE_KEYS.VOID);

                                s = KeilWizardStrings.IDS_WRITING_FILES;
                                break;
                            case GeneratingLogMessage.WORK_TYPE.UNKNOWN:
                                break;
                            default:
                                break;
                        }
                        currentLogItem = this.AddLogItem(s);
                        SetLogItemImageIndex(currentLogItem, IMAGE_KEYS.RUN);
                        break;
                    case GeneratingLogMessage.WORK_STATE.WORKING:

                        switch (mess.WorkType)
                        {
                            case GeneratingLogMessage.WORK_TYPE.BUILD_PROJECT:
                                SetLabelText(StatusLbl, mess.Message);
                                ProgressBarPerformStep(progressBar1);
                                break;
                            case GeneratingLogMessage.WORK_TYPE.CREATE_PROJECT_TREE:
                            case GeneratingLogMessage.WORK_TYPE.CREATE_FILE_LIST:
                            case GeneratingLogMessage.WORK_TYPE.CREATE_TARGETS:
                            case GeneratingLogMessage.WORK_TYPE.WRITING_FILES:
                                SetLabelText(StatusLbl, mess.Message);
                                SetProgressBarValue(progressBar1, mess.Progress);
                                break;
                            case GeneratingLogMessage.WORK_TYPE.UNKNOWN:
                                break;
                            default:
                                break;
                        }
                        break;
                    case GeneratingLogMessage.WORK_STATE.DONE:
                        switch (mess.WorkType)
                        {
                            case GeneratingLogMessage.WORK_TYPE.BUILD_PROJECT:
                                s = KeilWizardStrings.IDS_BUILDING + " " + KeilWizardStrings.IDS_DONE;
                                SetProgressBarValue(progressBar1, progressBar1.Maximum);
                                this.OnBuildStop(this, EventArgs.Empty);
                                break;
                            case GeneratingLogMessage.WORK_TYPE.CREATE_PROJECT_TREE:
                                s = KeilWizardStrings.IDS_CREATING_PROJECT_TREE + " " + KeilWizardStrings.IDS_DONE;
                                break;
                            case GeneratingLogMessage.WORK_TYPE.CREATE_FILE_LIST:
                                s = KeilWizardStrings.IDS_CREATING_FILE_LIST + " " + KeilWizardStrings.IDS_DONE;
                                break;
                            case GeneratingLogMessage.WORK_TYPE.CREATE_TARGETS:
                                s = KeilWizardStrings.IDS_CREATING_TARGETS + " " + KeilWizardStrings.IDS_DONE;
                                break;
                            case GeneratingLogMessage.WORK_TYPE.WRITING_FILES:
                                s = KeilWizardStrings.IDS_WRITING_FILES + " " + KeilWizardStrings.IDS_DONE;
                                break;
                        }
                        SetLogItemtext(currentLogItem, s);
                        SetLogItemImageIndex(currentLogItem, IMAGE_KEYS.DONE);
                        SetLabelText(StatusLbl, s);
                        break;
                    case GeneratingLogMessage.WORK_STATE.ERROR:
                        switch (mess.WorkType)
                        {
                            case GeneratingLogMessage.WORK_TYPE.BUILD_PROJECT:
                                s = KeilWizardStrings.IDS_BUILDING + " " + KeilWizardStrings.IDS_ERROR + ": " + mess.Message;
                                this.OnBuildStop(this, EventArgs.Empty);
                                break;
                            case GeneratingLogMessage.WORK_TYPE.CREATE_PROJECT_TREE:
                                s = KeilWizardStrings.IDS_CREATING_PROJECT_TREE + " " + KeilWizardStrings.IDS_ERROR + ": " + mess.Message;
                                break;
                            case GeneratingLogMessage.WORK_TYPE.CREATE_FILE_LIST:
                                s = KeilWizardStrings.IDS_CREATING_FILE_LIST + " " + KeilWizardStrings.IDS_ERROR + ": " + mess.Message;
                                break;
                            case GeneratingLogMessage.WORK_TYPE.CREATE_TARGETS:
                                s = KeilWizardStrings.IDS_CREATING_TARGETS + " " + KeilWizardStrings.IDS_ERROR + ": " + mess.Message;
                                break;
                            case GeneratingLogMessage.WORK_TYPE.WRITING_FILES:
                                s = KeilWizardStrings.IDS_WRITING_FILES + " " + KeilWizardStrings.IDS_ERROR + ": " + mess.Message;
                                break;
                            default:
                                s = mess.Message;
                                break;
                        }
                        SetLogItemtext(currentLogItem, s);
                        SetLogItemImageIndex(currentLogItem, IMAGE_KEYS.FAIL);
                        SetLabelText(StatusLbl, s);
                        SetProgressBarValue(progressBar1, progressBar1.Maximum);
                        this.OnConvertationStop(true);
                        break;
                    default:
                        break;
                }
            }
        }

        public override void BeforeCloseOnNext()
        {
            base.BeforeCloseOnNext();
        }

        public override void BeforeShow()
        {
            base.BeforeShow();
        }

        public override void AfterShow()
        {
            generator.Generate(config);
            ConvertLogLV.Items.Clear();
            base.AfterShow();
        }

        public override string PageName
        {
            get
            {
                return KeilWizardStrings.IDS_PAGE_NAME_CONVERTING;
            }
        }

        public override string PageDescription
        {
            get
            {
                return KeilWizardStrings.IDS_PAGE_DESCRIPTION_CONVERTING;
            }
        }


        #region AsyncCalls

        private delegate void SetLabelTextCallback(Label label, string text);
        private void SetLabelText(Label label, string text)
        {
            // InvokeRequired required compares the thread ID of the
            // calling thread to the thread ID of the creating thread.
            // If these threads are different, it returns true.
            if (label.InvokeRequired)
            {
                SetLabelTextCallback d = new SetLabelTextCallback(SetLabelText);
                label.BeginInvoke(d, new object[] { label, text });
            }
            else
            {
                label.Text = text;
            }
        }

        private delegate ListViewItem AddLogItemCallback(string text);
        private ListViewItem AddLogItem(string text)
        {

            if (ConvertLogLV.InvokeRequired)
            {
                AddLogItemCallback d = new AddLogItemCallback(AddLogItem);
                IAsyncResult result = ConvertLogLV.BeginInvoke(d, new object[] { text });
                result.AsyncWaitHandle.WaitOne();
                ListViewItem returnValue = (ListViewItem)this.EndInvoke(result);
                result.AsyncWaitHandle.Close();
                return returnValue;
            }
            else
            {
                ListViewItem result = ConvertLogLV.Items.Add(text);
                ConvertLogLV.AutoResizeColumns(ColumnHeaderAutoResizeStyle.ColumnContent);
                ConvertLogLV.EnsureVisible(result.Index);
                return result;
            }
        }

        private delegate void SetLogItemImageIndexCallback(ListViewItem item, IMAGE_KEYS index);
        private void SetLogItemImageIndex(ListViewItem item, IMAGE_KEYS index)
        {
            // InvokeRequired required compares the thread ID of the
            // calling thread to the thread ID of the creating thread.
            // If these threads are different, it returns true.
            if (ConvertLogLV.InvokeRequired)
            {
                SetLogItemImageIndexCallback d = new SetLogItemImageIndexCallback(SetLogItemImageIndex);
                ConvertLogLV.BeginInvoke(d, new object[] { item, index });
            }
            else
            {
                item.ImageIndex = (int)index;
                ConvertLogLV.AutoResizeColumns(ColumnHeaderAutoResizeStyle.ColumnContent);
            }
        }

        private delegate void SetLogItemtextCallback(ListViewItem item, string text);
        private void SetLogItemtext(ListViewItem item, string text)
        {
            // InvokeRequired required compares the thread ID of the
            // calling thread to the thread ID of the creating thread.
            // If these threads are different, it returns true.
            if (ConvertLogLV.InvokeRequired)
            {
                SetLogItemtextCallback d = new SetLogItemtextCallback(SetLogItemtext);
                ConvertLogLV.BeginInvoke(d, new object[] { item, text });
            }
            else
            {
                item.Text = text;
                ConvertLogLV.AutoResizeColumns(ColumnHeaderAutoResizeStyle.ColumnContent);
            }
        }

        private delegate void SetProgressBarParamsCallback(ProgressBar pb, int minimum, int maximum, int step);
        private void SetProgressBarParams(ProgressBar pb, int minimum, int maximum, int step)
        {
            // InvokeRequired required compares the thread ID of the
            // calling thread to the thread ID of the creating thread.
            // If these threads are different, it returns true.
            if (pb.InvokeRequired)
            {
                SetProgressBarParamsCallback d = new SetProgressBarParamsCallback(SetProgressBarParams);
                pb.BeginInvoke(d, new object[] { pb, minimum, maximum, step });
            }
            else
            {
                pb.Minimum = minimum;
                pb.Maximum = maximum;
                pb.Step = step;
            }
        }

        private delegate void ProgressBarPerformStepCallback(ProgressBar pb);
        private void ProgressBarPerformStep(ProgressBar pb)
        {
            // InvokeRequired required compares the thread ID of the
            // calling thread to the thread ID of the creating thread.
            // If these threads are different, it returns true.
            if (pb.InvokeRequired)
            {
                ProgressBarPerformStepCallback d = new ProgressBarPerformStepCallback(ProgressBarPerformStep);
                pb.BeginInvoke(d, new object[] { pb });
            }
            else
            {
                if (pb.Value >= pb.Maximum)
                {
                    pb.Value = pb.Minimum;
                }
                pb.PerformStep();
            }
        }

        private delegate void SetProgressBarValueCallback(ProgressBar pb, int value);
        private void SetProgressBarValue(ProgressBar pb, int value)
        {
            // InvokeRequired required compares the thread ID of the
            // calling thread to the thread ID of the creating thread.
            // If these threads are different, it returns true.
            if (pb.InvokeRequired)
            {
                SetProgressBarValueCallback d = new SetProgressBarValueCallback(SetProgressBarValue);
                pb.BeginInvoke(d, new object[] { pb, value });
            }
            else
            {
                pb.Value = value;
            }
        }

        #endregion


        #region events
        public event EventHandler ConvertationStartEvent;
        protected void OnConvertationStart(object sender, EventArgs e)
        {
            if (ConvertationStartEvent != null)
            {
                ConvertationStartEvent(sender, e);
            }
        }

        public event EventHandler<ConvertationStopEventArgs> ConvertationStopEvent;
        protected void OnConvertationStop(bool error)
        {
            if (ConvertationStopEvent != null)
            {
                ConvertationStopEvent(this, new ConvertationStopEventArgs(error));
            }
        }

        public event EventHandler BuildStartEvent;
        protected void OnBuildStart(object sender, EventArgs e)
        {
            if (BuildStartEvent != null)
            {
                BuildStartEvent(sender, e);
            }
        }

        public event EventHandler BuildStopEvent;
        protected void OnBuildStop(object sender, EventArgs e)
        {
            if (BuildStopEvent != null)
            {
                BuildStopEvent(sender, e);
            }
        }
        #endregion
    }

    public class ConvertationStopEventArgs : EventArgs
    {
        public ConvertationStopEventArgs(bool Error)
        {
            this.Error = Error;
        }
        public bool Error { get; set; }
    }
}
