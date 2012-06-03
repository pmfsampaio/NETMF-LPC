using System.IO;
using PKParser.Arg;
using System.Collections.Generic;

namespace PKStudio.Tools.uVisionGenerator.Classes.HelpClasses.MessagesParsesHelper
{
    class RequiredBase
    {
        public RequiredBase(string Name, RequiredBase Parent)
        {
            if (string.IsNullOrEmpty(Path.GetPathRoot(Name)))
                this.Name = Name;
            else
            {
                this.OutputFileMSBuild = Name;
                this.Name = Path.GetFileName(Name);
            }

            this._Parent = Parent;
        }

        #region fields
        protected List<string> _PreBuildCmds = new List<string>();
        protected List<string> _PostBuildCmds = new List<string>();
        protected string _Name = string.Empty;
        protected string _ConsoleString = string.Empty;
        protected string _CurrentDir = string.Empty;
        protected List<string> _BuildList = new List<string>();
        protected string _OutputFileMSBuild = string.Empty;
        protected string _OutputFileuVision = string.Empty;
        protected ParamCollection _ParamCollection = null;
        protected RequiredBase _Parent = null;

        #endregion

        public string Name
        {
            get { return this._Name; }
            set
            {
                if (string.IsNullOrEmpty(Path.GetPathRoot(value)))
                    this._Name = value;
                else
                {
                    this.OutputFileMSBuild = value;
                    this._Name = Path.GetFileName(value);
                }
            }
        }
        public string ConsoleString { get { return this._ConsoleString; } set { this._ConsoleString = value; } }
        public string CurrentDir { get { return this._CurrentDir; } set { this._CurrentDir = value; } }
        public string OutputFileMSBuild { get { return this._OutputFileMSBuild; } set { this._OutputFileMSBuild = value; } }
        public string OutputFileuVision { get { return this._OutputFileuVision; } set { this._OutputFileuVision = value; } }
        public ParamCollection ParamCollection { get { return this._ParamCollection; } set { this._ParamCollection = value; } }
        public List<string> PreBuildCmds { get { return this._PreBuildCmds; } }
        public List<string> PostBuildCmds { get { return this._PostBuildCmds; } }
        public List<string> BuildList { get { return this._BuildList; } }
        public RequiredBase Parent { get { return this._Parent; } }
    }
}
