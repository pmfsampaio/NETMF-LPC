using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace PKStudio.Helpers
{
    public class ErrorEventArgs : EventArgs
    {
        public ErrorEventArgs(WEMessage Error)
        {
            this.Error = Error;
        }
        public WEMessage Error { get; set; }
    }

    public class MessageEventArgs : EventArgs
    {
        public MessageEventArgs(string Message)
        {
            this.Message = Message;
        }
        public string Message { get; set; }
    }

    public class WarningEventArgs : EventArgs
    {
        public WarningEventArgs(WEMessage Warning)
        {
            this.Warning = Warning;
        }
        public WEMessage Warning { get; set; }
    }

    public class LogFinishedEventArgs : EventArgs
    {
        public LogFinishedEventArgs(ErrorsAndWarningsList ErrorsAndWarningsList)
        {
            this.ErrorsAndWarningsList = ErrorsAndWarningsList;
        }
        public ErrorsAndWarningsList ErrorsAndWarningsList { get; set; }
    }



    public interface ILoggable
    {
        event EventHandler LogStartedEvent;
        event EventHandler<LogFinishedEventArgs> LogFinishedEvent;
        event EventHandler<MessageEventArgs> MessageEvent;
        event EventHandler<WarningEventArgs> WarningEvent;
        event EventHandler<ErrorEventArgs> ErrorEvent;
    }
}
