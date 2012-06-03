using PKStudio.Forms.BaseForms;
using System.Windows.Forms;
using Microsoft.Build.Logging;
using System.Collections.Generic;
using System;
using System.IO;
using System.Drawing;
using PKStudio.Helpers;

namespace PKStudio.Forms.Output
{
    public partial class OutputForm : BasePKInventoryForm
    {

        private List<ILoggable> mLoggesList = new List<ILoggable>();

        private Dictionary<int, WEMessage> ErrorsAndWarningsDict = new Dictionary<int, WEMessage>();

        private int LastHighlitedLine = -1;

        public OutputForm()
        {
            InitializeComponent();

            VerbosityCB.Items.Clear();

            VerbosityCB.Items.Add("Quiet");
            VerbosityCB.Items.Add("Minimal");
            VerbosityCB.Items.Add("Normal");
            VerbosityCB.Items.Add("Detailed");
            VerbosityCB.Items.Add("Diagnostic");
            VerbosityCB.SelectedIndex = 1;
        }

        public void AttachLogger(ILoggable Logger)
        {
            mLoggesList.Add(Logger);
            Logger.LogStartedEvent += new EventHandler(Logger_LogStartedEvent);
            Logger.ErrorEvent += new EventHandler<PKStudio.Helpers.ErrorEventArgs>(Logger_ErrorEvent);
            Logger.WarningEvent += new EventHandler<WarningEventArgs>(Logger_WarningEvent);
            Logger.MessageEvent += new EventHandler<MessageEventArgs>(Logger_MessageEvent);
        }

        public void detachLogger(ILoggable Logger)
        {
            mLoggesList.Remove(Logger);
            Logger.LogStartedEvent -= new EventHandler(Logger_LogStartedEvent);
            Logger.ErrorEvent -= new EventHandler<PKStudio.Helpers.ErrorEventArgs>(Logger_ErrorEvent);
            Logger.WarningEvent -= new EventHandler<WarningEventArgs>(Logger_WarningEvent);
            Logger.MessageEvent -= new EventHandler<MessageEventArgs>(Logger_MessageEvent);
        }

        void Logger_MessageEvent(object sender, MessageEventArgs e)
        {
            this.AppendText(e.Message);
        }


        void Logger_WarningEvent(object sender, WarningEventArgs e)
        {
            string line = string.Empty;

            if ((e.Warning.MessageObject as FileMessageObject) != null)
            {
                FileMessageObject FMO = e.Warning.MessageObject as FileMessageObject;
                if (FMO.File == "EXEC")
                {
                    line = Strings.Warning + " " + e.Warning.Message;
                }
                else
                {
                    line = FMO.File + "(" + FMO.LineNumber + "," + FMO.ColumnNumber + "): " + Strings.Warning + " " + e.Warning.Code + ": " + e.Warning.Message;
                }
                
            }
            if ((e.Warning.MessageObject as ComponentMessageObject) != null)
            {
                ComponentMessageObject CMO = e.Warning.MessageObject as ComponentMessageObject;
                line = CMO.Component.Name + ": " + Strings.Warning + " " + e.Warning.Code + ": " + e.Warning.Message;
            }

            if (e.Warning.MessageObject == null)
            {
            }

            if (!string.IsNullOrEmpty(line))
            {
                this.AppendText(line + "\r\n");
                int linenum = GetOutputLinesCount() - 2; //En: -2 because last line always empty Ru: -2 потому что последняя линяя всегда пустая
                ErrorsAndWarningsDict.Add(linenum, e.Warning);
            }
        }

        void Logger_ErrorEvent(object sender, PKStudio.Helpers.ErrorEventArgs e)
        {
            string line = string.Empty;
            if ((e.Error.MessageObject as FileMessageObject) != null)
            {
                FileMessageObject FMO = e.Error.MessageObject as FileMessageObject;
                if (FMO.File == "EXEC")
                {
                    line = Strings.Error + " " + e.Error.Message;
                }
                else
                {
                    line = FMO.File + "(" + FMO.LineNumber + "," + FMO.ColumnNumber + "): " + Strings.Error + " " + e.Error.Code + ": " + e.Error.Message;
                }
            }
            if ((e.Error.MessageObject as ComponentMessageObject) != null)
            {
                ComponentMessageObject CMO = e.Error.MessageObject as ComponentMessageObject;
                line = CMO.Component.Name + ": " + Strings.Error + " " + e.Error.Code + ": " + e.Error.Message;
            }

            if (e.Error.MessageObject == null)
            {
            }

            if (!string.IsNullOrEmpty(line))
            {
                this.AppendText(line + "\r\n");
                int linenum = GetOutputLinesCount() - 2;//En: -2 because last line always empty Ru: -2 потому что последняя линяя всегда пустая
                ErrorsAndWarningsDict.Add(linenum, e.Error);
            }
        }

        void Logger_LogStartedEvent(object sender, EventArgs e)
        {
            this.ClearAll();
        }

        private void toolStripButton1_Click(object sender, System.EventArgs e)
        {
            this.ClearAll();
        }


        private delegate void SetTextCallback(string text);
        private void AppendText(string text)
        {
            if (OutputTextBox.InvokeRequired)
            {
                SetTextCallback d = new SetTextCallback(AppendText);
                OutputTextBox.BeginInvoke(d, new object[] { text });
            }
            else
            {
                OutputTextBox.AppendText(text);
                OutputTextBox.ScrollToCaret();
                //Application.DoEvents();
            }
        }


        private delegate void ClearAllCallback();
        public void ClearAll()
        {
            if (OutputTextBox.InvokeRequired)
            {
                ClearAllCallback d = new ClearAllCallback(ClearAll);
                OutputTextBox.BeginInvoke(d, new object[] { });
            }
            else
            {
                OutputTextBox.Clear();
                ErrorsAndWarningsDict.Clear();
                OutputTextBox.ScrollToCaret();
                LastHighlitedLine = -1;                
                //Application.DoEvents();
            }
        }


        private delegate int GetOutputLinesCountCallback();
        private int GetOutputLinesCount()
        {
            if (OutputTextBox.InvokeRequired)
            {
                GetOutputLinesCountCallback d = new GetOutputLinesCountCallback(GetOutputLinesCount);
                IAsyncResult result = OutputTextBox.BeginInvoke(d, new object[] { });
                result.AsyncWaitHandle.WaitOne();
                int returnValue = (int)this.EndInvoke(result);
                result.AsyncWaitHandle.Close();
                return returnValue;
            }
            else
            {
                return OutputTextBox.Lines.Length;
            }
        }

        private delegate void HighlightLineCallback(int line, Color BKColor, Color TextColor);
        public void HighlightLine(int line, Color BKColor, Color TextColor)
        {
            if (OutputTextBox.InvokeRequired)
            {
                HighlightLineCallback d = new HighlightLineCallback(HighlightLine);
                OutputTextBox.BeginInvoke(d, new object[] { line, BKColor, TextColor });
            }
            else
            {
                int oldSelStart = OutputTextBox.SelectionStart;
                int oldSelLen = OutputTextBox.SelectionLength;

                OutputTextBox.Select(OutputTextBox.GetFirstCharIndexFromLine(line), OutputTextBox.Lines[line].Length);
                OutputTextBox.SelectionBackColor = BKColor;
                OutputTextBox.SelectionColor = TextColor;

                OutputTextBox.Select(oldSelStart, oldSelLen);

                LastHighlitedLine = line;
            }
        }

        private delegate void CleanHighlightCallback(int line);
        public void CleanHighlight(int line)
        {
            if (OutputTextBox.InvokeRequired)
            {
                CleanHighlightCallback d = new CleanHighlightCallback(CleanHighlight);
                OutputTextBox.BeginInvoke(d, new object[] { line });
            }
            else
            {
                int oldSelStart = OutputTextBox.SelectionStart;
                int oldSelLen = OutputTextBox.SelectionLength;

                OutputTextBox.Select(OutputTextBox.GetFirstCharIndexFromLine(line), OutputTextBox.Lines[line].Length);
                OutputTextBox.SelectionBackColor = OutputTextBox.BackColor;
                OutputTextBox.SelectionColor = OutputTextBox.ForeColor;

                OutputTextBox.Select(oldSelStart, oldSelLen);
            }
        }

        private void VelocityCB_SelectedIndexChanged(object sender, System.EventArgs e)
        {
            //switch (VerbosityCB.SelectedIndex)
            //{
            //    case 0:
            //        mLogger.Verbosity = Microsoft.Build.Framework.LoggerVerbosity.Quiet;
            //        break;
            //    case 1:
            //        mLogger.Verbosity = Microsoft.Build.Framework.LoggerVerbosity.Minimal;
            //        break;
            //    case 2:
            //        mLogger.Verbosity = Microsoft.Build.Framework.LoggerVerbosity.Normal;
            //        break;
            //    case 3:
            //        mLogger.Verbosity = Microsoft.Build.Framework.LoggerVerbosity.Detailed;
            //        break;
            //    case 4:
            //        mLogger.Verbosity = Microsoft.Build.Framework.LoggerVerbosity.Diagnostic;
            //        break;
            //    default:
            //        break;
            //}
        }

        private void OutputTextBox_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            int Line = OutputTextBox.GetLineFromCharIndex(OutputTextBox.GetCharIndexFromPosition(e.Location));
            if (ErrorsAndWarningsDict.ContainsKey(Line))
            {
                if (LastHighlitedLine != -1) CleanHighlight(LastHighlitedLine);
                HighlightLine(Line, Color.Blue, Color.White);
                WEMessage mes = ErrorsAndWarningsDict[Line];
                if ((mes.MessageObject as FileMessageObject) != null)
                {
                    FileMessageObject FMO = mes.MessageObject as FileMessageObject;
                    if (File.Exists(FMO.File))
                    {
                        PKStudio.Helpers.EditorsFormsController.EditFileDescriptor comp = new PKStudio.Helpers.EditorsFormsController.EditFileDescriptor();
                        comp.Path = FMO.File;
                        comp.Line = FMO.LineNumber;
                        comp.Column = FMO.ColumnNumber;
                        this.OnEditEvent(comp);
                    }
                }
                if ((mes.MessageObject as ComponentMessageObject) != null)
                {
                    ComponentMessageObject CMO = mes.MessageObject as ComponentMessageObject;
                    this.OnEditEvent(CMO.Component);
                }
            }
        }
    }
}
