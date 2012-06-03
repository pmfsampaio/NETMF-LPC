using System.Collections.Generic;
using PKStudio.ItemWrappers;
using PKStudio.Tools.uVisionGenerator.Classes.uvProjectClasses;
using System.Collections.ObjectModel;

namespace PKStudio.Tools.uVisionGenerator.Classes.HelpClasses
{
    public class ConvertConfig
    {
        private Collection<ConvertableMFProject> mProjectList = new Collection<ConvertableMFProject>();
        private string mSolutionPath = string.Empty;
        private TargetOptions mProcessor = null;
        private string mName = string.Empty;

        private uVisionMultiProjectWorkspace mResult = null;

        public Collection<ConvertableMFProject> ProjectList { get { return this.mProjectList; } }
        public string SolutionPath { get { return this.mSolutionPath; } set { this.mSolutionPath = value; } }
        public TargetOptions Processor { get { return this.mProcessor; } set { this.mProcessor = value; } }
        public string Name { get { return this.mName; } set { this.mName = value; } }
        public uVisionMultiProjectWorkspace Result { get { return this.mResult; } set { this.mResult = value; } }

        public bool ContainsProject(ProjectWrapper proj)
        {
            foreach (ConvertableMFProject cp in mProjectList)
            {
                if (cp.Project == proj) return true;
            }
            return false;
        }

        public void RemoveProject(ProjectWrapper proj)
        {
            ConvertableMFProject tmp = null;
            foreach (ConvertableMFProject cp in mProjectList)
            {
                if (cp.Project == proj) tmp = cp;
            }

            if (tmp != null)
            {
                mProjectList.Remove(tmp);
            }
        }
    }
}
