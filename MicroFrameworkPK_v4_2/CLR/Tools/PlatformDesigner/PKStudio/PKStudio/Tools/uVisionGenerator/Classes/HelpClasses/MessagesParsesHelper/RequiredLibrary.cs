using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace PKStudio.Tools.uVisionGenerator.Classes.HelpClasses.MessagesParsesHelper
{
    class RequiredLibrary : RequiredBase
    {

        public RequiredLibrary(string Name, RequiredBase Parent)
            : base(Name, Parent)
        {
         
        }

        #region fields
        private List<string> _OptionsString = new List<string>();
        private SortedList<int, RequiredLibrary> _InputLibraries = new SortedList<int, RequiredLibrary>();
        private SortedList<int, RequiredObject> _InputObjects = new SortedList<int, RequiredObject>();
        private SortedList<int, RequiredBase> _AllInputs = new SortedList<int, RequiredBase>();
        #endregion

        public List<string> OptionsString { get { return this._OptionsString; } }
        public SortedList<int, RequiredLibrary> InputLibraries { get { return this._InputLibraries; } }
        public SortedList<int, RequiredObject> InputObjects { get { return this._InputObjects; } }
        public SortedList<int, RequiredBase> AllInputs { get { return this._AllInputs; } }

        public bool CheckItems()
        {
            return this.CheckItems(this);
        }

        public List<RequiredLibrary> GetRequiredLibraries()
        {
            List<RequiredLibrary> result = new List<RequiredLibrary>();
            foreach (RequiredLibrary reqlib in InputLibraries.Values)
            {
                result.Add(reqlib);
                result.AddRange(reqlib.GetRequiredLibraries());
            }
            return result;
        }

        private bool CheckItems(RequiredLibrary reqlib)
        {
            if (this.ParamCollection == null) return false;

            foreach (RequiredObject obj in reqlib.InputObjects.Values)
            {
                if (obj.ParamCollection == null) return false;
            }

            foreach (RequiredLibrary lib in reqlib.InputLibraries.Values)
            {
                if (!this.CheckItems(lib)) return false;
            }
            return true;
        }
    }
}
