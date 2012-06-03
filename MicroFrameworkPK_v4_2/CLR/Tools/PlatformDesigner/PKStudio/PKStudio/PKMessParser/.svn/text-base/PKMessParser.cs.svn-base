using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;

namespace PKParser.PKMessParser
{
    public class MessInfo
    {
        public MessInfo(string s)
        {
            const string FILE = "file";
            const string LINE = "line";
            const string COND = "cond";
            const string ERROR = "error";
            const string MESSAGE = "message";
            Regex rex = new Regex(@"""?(?<" + FILE + @">[a-zA-Z]:\\(?:[^\\/:*?<>|\r\n]+\\)*(?:[^\\/:*?""<>|\r\n]+))""?,\sline\s(?<" + LINE + @">[0-9]+):\s(?<" + COND + @">Error|Warning):[^#]+#(?<"+ERROR+@">[0-9]+(?:-\D)?):\s*(?<"+MESSAGE+@">.+)\z");
            Match m = rex.Match(s);
            if (m.Success)
            {
                try
                {
                    this.File = m.Groups[FILE].Value;
                    this.Line = int.Parse(m.Groups[LINE].Value);
                    this.Cond = (Level)Enum.Parse(typeof(Level), m.Groups[COND].Value);
                    this.Error = m.Groups[ERROR].Value;
                    this.Message = m.Groups[MESSAGE].Value;
                    this.Success = true;
                }
                catch
                {
                    this.Success = false;
                }
            }
        }
        public enum Level
        {
            Error,
            Warning
        }
        public string File { get; private set; }
        public int Line { get; private set; }
        public Level Cond { get; private set; }
        public string Error { get; private set; }
        public string Message { get; private set; }
        public bool Success { get; private set; }
    }
}
