using System;
using PKStudio.Forms.BaseForms;
using System.Windows.Forms;
using System.IO;
using PKStudio.Helpers;
using System.Collections.Generic;

namespace PKStudio.Forms.Output
{
    public partial class ErrorListForm : BasePKInventoryForm
    {
        private int index = 0;

        private List<ILoggable> mLoggesList = new List<ILoggable>();

        private ErrorsAndWarningsList ErrorsAndWarningsList = new ErrorsAndWarningsList();

        public ErrorListForm()
        {
            InitializeComponent();
        }

        public void AttachLogger(ILoggable Logger)
        {
            mLoggesList.Add(Logger);
            Logger.LogStartedEvent += new EventHandler(Logger_LogStartedEvent);
            Logger.LogFinishedEvent += new EventHandler<LogFinishedEventArgs>(Logger_LogFinishedEvent);
            Logger.ErrorEvent += new EventHandler<PKStudio.Helpers.ErrorEventArgs>(Logger_ErrorEvent);
            Logger.WarningEvent += new EventHandler<WarningEventArgs>(Logger_WarningEvent);
        }

        public void detachLogger(ILoggable Logger)
        {
            mLoggesList.Remove(Logger);
            Logger.LogStartedEvent -= new EventHandler(Logger_LogStartedEvent);
            Logger.LogFinishedEvent -= new EventHandler<LogFinishedEventArgs>(Logger_LogFinishedEvent);
            Logger.ErrorEvent -= new EventHandler<PKStudio.Helpers.ErrorEventArgs>(Logger_ErrorEvent);
            Logger.WarningEvent -= new EventHandler<WarningEventArgs>(Logger_WarningEvent);
        }



        void Logger_WarningEvent(object sender, WarningEventArgs e)
        {
            if (this.WarningsBtn.Checked)
            {
                AddWarning(e.Warning);
            }
            this.ErrorsAndWarningsList.AddWarning(e.Warning);
            LVColumnsResize();
            SetBtnText(WarningsBtn, ErrorsAndWarningsList.WarningsCount + " Warnings");
        }

        void Logger_ErrorEvent(object sender, PKStudio.Helpers.ErrorEventArgs e)
        {
            if (this.ErrorsBtn.Checked)
            {
                AddError(e.Error);
            }
            this.ErrorsAndWarningsList.AddError(e.Error);
            LVColumnsResize();
            SetBtnText(ErrorsBtn, ErrorsAndWarningsList.ErrorsCount + " Errors");
        }

        void Logger_LogFinishedEvent(object sender, LogFinishedEventArgs e)
        {
            //RefreshAllItems((ILoggable)sender);
            //LVColumnsResize();
        }

        void Logger_LogStartedEvent(object sender, EventArgs e)
        {
            ErrorsAndWarningsList.ClearAll();
            LVItemsClear();
            SetBtnText(ErrorsBtn, "0 Errors");
            SetBtnText(WarningsBtn, "0 Warnings");
            index = 1;
        }

        private void RefreshAllItems()
        {
            LVItemsClear();
            index = 1;
            if (this.ErrorsBtn.Checked)
            {
                foreach (WEMessage item in ErrorsAndWarningsList.GetErrors())
                {
                    AddError(item);
                }
            }
            if (this.WarningsBtn.Checked)
            {
                foreach (WEMessage item in ErrorsAndWarningsList.GetWarnings())
                {
                    AddWarning(item);
                }
            }

            LVColumnsResize();

            SetBtnText(ErrorsBtn, ErrorsAndWarningsList.ErrorsCount + " Errors");
            SetBtnText(WarningsBtn, ErrorsAndWarningsList.WarningsCount + " Warnings");
        }

        private void AddError(WEMessage Error)
        {
            ListViewItem LVitem = new ListViewItem("", 0);
            LVitem.SubItems.Add(index.ToString());
            LVitem.SubItems.Add(Error.Message);
            if ((Error.MessageObject as FileMessageObject) != null)
            {
                FileMessageObject FMO = Error.MessageObject as FileMessageObject;
                if (FMO.File != "EXEC")
                {
                    LVitem.SubItems.Add(Path.GetFileName(FMO.File));
                    LVitem.SubItems.Add(FMO.LineNumber.ToString());
                    //LVitem.SubItems.Add(item.ColumnNumber.ToString());
                }
            }
            if ((Error.MessageObject as ComponentMessageObject) != null)
            {
                ComponentMessageObject CMO = Error.MessageObject as ComponentMessageObject;
                LVitem.SubItems.Add(Path.GetFileName(CMO.Component.Name));
            }
            LVitem.Tag = Error;
            AddLVItem(LVitem);
            index++;
        }

        private void AddWarning(WEMessage Warning)
        {
            ListViewItem LVitem = new ListViewItem("", 1);
            LVitem.SubItems.Add(index.ToString());
            LVitem.SubItems.Add(Warning.Message);
            if ((Warning.MessageObject as FileMessageObject) != null)
            {
                FileMessageObject FMO = Warning.MessageObject as FileMessageObject;
                if (FMO.File != "EXEC")
                {
                    LVitem.SubItems.Add(Path.GetFileName(FMO.File));
                    LVitem.SubItems.Add(FMO.LineNumber.ToString());
                    //LVitem.SubItems.Add(item.ColumnNumber.ToString());
                }
            }
            if ((Warning.MessageObject as ComponentMessageObject) != null)
            {
                ComponentMessageObject CMO = Warning.MessageObject as ComponentMessageObject;
                LVitem.SubItems.Add(Path.GetFileName(CMO.Component.Name));
            }
            LVitem.Tag = Warning;
            AddLVItem(LVitem);
            index++;
        }

        private void ErrorsBtn_Click(object sender, EventArgs e)
        {
            this.ErrorsBtn.Checked = !this.ErrorsBtn.Checked;
            if (ErrorsBtn.Checked)
                RefreshAllItems();
            else
                LVItemsClear();
        }

        private void WarningsBtn_Click(object sender, EventArgs e)
        {
            this.WarningsBtn.Checked = !this.WarningsBtn.Checked;
            if (WarningsBtn.Checked)
                RefreshAllItems();
            else
                LVItemsClear();

        }

        private delegate void LVColumnsResizeCallback();
        private void LVColumnsResize()
        {
            if (listView1.InvokeRequired)
            {
                LVColumnsResizeCallback d = new LVColumnsResizeCallback(LVColumnsResize);
                listView1.BeginInvoke(d, new object[] { });
            }
            else
            {
                listView1.Columns[1].AutoResize(ColumnHeaderAutoResizeStyle.ColumnContent);
                listView1.Columns[3].AutoResize(ColumnHeaderAutoResizeStyle.ColumnContent);
                listView1.Columns[4].AutoResize(ColumnHeaderAutoResizeStyle.ColumnContent);
                if (listView1.Columns[4].Width < 35) listView1.Columns[4].Width = 35;
                listView1.Columns[2].Width = listView1.ClientRectangle.Width - listView1.Columns[0].Width - listView1.Columns[1].Width - listView1.Columns[3].Width - listView1.Columns[4].Width - 4;
            }
        }

        private delegate void SetBtnTextCallback(ToolStripButton button, string text);
        private void SetBtnText(ToolStripButton button, string text)
        {
            if (toolStrip1.InvokeRequired)
            {
                SetBtnTextCallback d = new SetBtnTextCallback(SetBtnText);
                toolStrip1.BeginInvoke(d, new object[] { button, text });
            }
            else
            {
                button.Text = text;
            }
        }

        private delegate void AddLVItemCallback(ListViewItem item);
        private void AddLVItem(ListViewItem item)
        {
            if (listView1.InvokeRequired)
            {
                AddLVItemCallback d = new AddLVItemCallback(AddLVItem);
                listView1.BeginInvoke(d, new object[] { item });
            }
            else
            {
                listView1.Items.Add(item);
            }
        }

        private delegate void InsertLVItemCallback(ListViewItem item, int index);
        private void InserLVItem(ListViewItem item, int index)
        {
            if (listView1.InvokeRequired)
            {
                InsertLVItemCallback d = new InsertLVItemCallback(InserLVItem);
                listView1.BeginInvoke(d, new object[] { item, index });
            }
            else
            {
                listView1.Items.Insert(index, item);
            }
        }

        private delegate void LVItemsClearCallback();
        public void LVItemsClear()
        {
            if (listView1.InvokeRequired)
            {
                LVItemsClearCallback d = new LVItemsClearCallback(LVItemsClear);
                listView1.BeginInvoke(d, new object[] { });
            }
            else
            {
                listView1.Items.Clear();
            }
        }

        public void ClearAll()
        {
            LVItemsClear();
            ErrorsAndWarningsList.ClearAll();
            index = 0;
        }

        private void listView1_SizeChanged(object sender, EventArgs e)
        {
            if (listView1.Columns.Count > 0)
                listView1.Columns[2].Width = listView1.ClientRectangle.Width - listView1.Columns[0].Width - listView1.Columns[1].Width - listView1.Columns[3].Width - listView1.Columns[4].Width - 4;
        }

        private void listView1_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            if (listView1.SelectedItems.Count > 0)
            {
                WEMessage mes = (WEMessage)listView1.SelectedItems[0].Tag;
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
