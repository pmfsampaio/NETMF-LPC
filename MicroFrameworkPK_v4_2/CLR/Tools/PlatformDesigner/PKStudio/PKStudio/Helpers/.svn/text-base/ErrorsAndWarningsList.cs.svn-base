using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using PKStudio.ItemWrappers;

namespace PKStudio.Helpers
{
    public abstract class MessageObject { }

    public class FileMessageObject : MessageObject
    {
        public int LineNumber { get; set; }
        public int EndLineNumber { get; set; }
        public int ColumnNumber { get; set; }
        public int EndColumnNumber { get; set; }
        public string File { get; set; }
    }

    public class ComponentMessageObject : MessageObject
    {
        public ComponentWrapper Component { get; set; }
    }

    public class WEMessage
    {
        public string Code { get; set; }
        public MessageObject MessageObject { get; set; }
        public string Message { get; set; }
    }

    public class ErrorsAndWarningsList
    {

        private List<WEMessage> mMSBuildErrors = new List<WEMessage>();
        private List<WEMessage> mMSBuildWarnings = new List<WEMessage>();

        //public List<WEMessage> MSBuildErrors { get { return mMSBuildErrors; } }
        //public List<WEMessage> MSBuildWarnings { get { return mMSBuildWarnings; } }

        public void ClearAll()
        {
            mMSBuildErrors.Clear();
            mMSBuildWarnings.Clear();
        }

        public bool AddWarning(WEMessage warning)
        {
            bool contains = false;

            foreach (WEMessage item in mMSBuildWarnings)
            {
                if (item.Message == warning.Message) contains = true;
            }
            if (!contains)
            {
                this.mMSBuildWarnings.Add(warning);
                return true;
            }
            return false;
        }

        public bool AddError(WEMessage error)
        {
            bool contains = false;

            foreach (WEMessage item in mMSBuildErrors)
            {
                if (item.Message == error.Message) contains = true;
            }
            if (!contains)
            {
                this.mMSBuildErrors.Add(error);
                return true;
            }
            return false;
        }

        public int WarningsCount { get { return mMSBuildWarnings.Count; } }
        public int ErrorsCount { get { return mMSBuildErrors.Count; } }

        public WEMessage[] GetErrors() { return mMSBuildErrors.ToArray(); }
        public WEMessage[] GetWarnings() { return mMSBuildWarnings.ToArray(); }


    }
}
