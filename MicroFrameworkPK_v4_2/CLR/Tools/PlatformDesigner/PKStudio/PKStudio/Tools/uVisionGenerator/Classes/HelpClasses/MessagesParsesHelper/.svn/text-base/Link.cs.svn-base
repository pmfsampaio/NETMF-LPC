using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using PKParser.Arg;
using PKStudio.Tools.uVisionGenerator.Wizard;

namespace PKStudio.Tools.uVisionGenerator.Classes.HelpClasses.MessagesParsesHelper
{
    class Link : RequiredBase
    {
        public Link(string Name, RequiredBase Parent)
            : base(Name, Parent)
        {
        }
        #region fields
        private string _OptionsString = string.Empty;
        private SortedList<int, RequiredLibrary> _InputLibraries = new SortedList<int, RequiredLibrary>();
        private SortedList<int, RequiredObject> _InputObjects = new SortedList<int, RequiredObject>();
        private SortedList<int, RequiredBase> _AllInputs = new SortedList<int, RequiredBase>();
        //private string _OutputFile = string.Empty;
        #endregion

        public string OptionsString { get { return this._OptionsString; } set { this._OptionsString = value; } }
        public SortedList<int, RequiredLibrary> InputLibraries { get { return this._InputLibraries; } }
        public SortedList<int, RequiredObject> InputObjects { get { return this._InputObjects; } }
        public SortedList<int, RequiredBase> AllInputs { get { return this._AllInputs; } }
        //public string OutputFile { get { return this._OutputFile; } set { this._OutputFile = value; } }

        /// <summary>
        /// En: Check all input components for data validation.
        /// Ru: Проверяет все входящие компоненты на неободимую наполненность данными
        /// </summary>
        /// <returns></returns>
        public bool CheckItems()
        {
            int index = 0;
            foreach (RequiredObject obj in this.InputObjects.Values)
            {
                index++;
                OnLog(new GeneratingLogMessage(KeilWizardStrings.IDS_CHECK_LINKS, GeneratingLogMessage.WORK_TYPE.CREATE_PROJECT_TREE, GeneratingLogMessage.WORK_STATE.WORKING, (int)((index * 100) / (InputObjects.Values.Count + InputLibraries.Values.Count))));

                if (obj.ParamCollection == null) return false;
            }
            foreach (RequiredLibrary lib in this.InputLibraries.Values)
            {
                index++;
                OnLog(new GeneratingLogMessage(KeilWizardStrings.IDS_CHECK_LINKS, GeneratingLogMessage.WORK_TYPE.CREATE_PROJECT_TREE, GeneratingLogMessage.WORK_STATE.WORKING, (int)((index * 100) / (InputObjects.Values.Count + InputLibraries.Values.Count))));

                if (!lib.CheckItems()) return false;
            }
            OnLog(new GeneratingLogMessage(KeilWizardStrings.IDS_CHECK_LINKS, GeneratingLogMessage.WORK_TYPE.CREATE_PROJECT_TREE, GeneratingLogMessage.WORK_STATE.WORKING, 100));
            System.Threading.Thread.Sleep(500);
            return true;
        }

        public SortedList<int, RequiredObject> GetAllRequiredObjects()
        {
            SortedList<int, RequiredObject> result = new SortedList<int,RequiredObject>();

            foreach (RequiredObject o in this.InputObjects.Values)
            {
                result.Add(result.Count + 1, o);
            }

            foreach (RequiredLibrary lib in this.InputLibraries.Values)
            {
                SortedList<int, RequiredObject> tmplist = this.GetLibraryObjects(lib);

                foreach (RequiredObject o in tmplist.Values)
                {
                    result.Add(result.Count + 1, o);
                }
            }

           
            return result;
        }

        public List<RequiredLibrary> GetAllSubRequiredLibraries()
        {
            List<RequiredLibrary> result = new List<RequiredLibrary>();

            foreach (RequiredLibrary lib in this.InputLibraries.Values)
            {
                result.AddRange(lib.GetRequiredLibraries());
            }


            return result;
        }

        private SortedList<int, RequiredObject> GetLibraryObjects(RequiredLibrary lib)
        {
            SortedList<int, RequiredObject> result = new SortedList<int, RequiredObject>();

            foreach (RequiredObject o in lib.InputObjects.Values)
            {
                result.Add(result.Count + 1, o);
            }

            foreach (RequiredLibrary reqlib in lib.InputLibraries.Values)
            {
                SortedList<int, RequiredObject> tmplist = this.GetLibraryObjects(reqlib);

                foreach (RequiredObject o in tmplist.Values)
                {
                    result.Add(result.Count + 1, o);
                }
            }

            return result;
        }


        #region Events
        public delegate void LogEventDelegate(GeneratingLogMessage mess);

        public event LogEventDelegate LogEvent;

        protected void OnLog(GeneratingLogMessage mess)
        {
            if (LogEvent != null)
            {
                LogEvent(mess);
            }
        }
        #endregion

    }
}
