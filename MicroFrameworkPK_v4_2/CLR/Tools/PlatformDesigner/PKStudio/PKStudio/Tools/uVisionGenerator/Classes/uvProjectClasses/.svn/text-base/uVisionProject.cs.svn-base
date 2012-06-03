using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using PKStudio.Tools.uVisionGenerator.Wizard;
using System.Diagnostics;

namespace PKStudio.Tools.uVisionGenerator.Classes.uvProjectClasses
{
    /// <summary>
    /// Describes Keil uVision project
    /// </summary>
    public class uVisionProject
    {

        #region properties

        private SortedList<int, Target> targetList = new SortedList<int, Target>();

        private SortedList<int, Group> groupList = new SortedList<int, Group>();

        private SortedList<int, File> fileList = new SortedList<int, File>();

        private string mName = string.Empty;

        private string mProjectPath = string.Empty;

        private TargetOptions mDefaultOptions = null;

        private SortedList<int, string> mScatter = new SortedList<int, string>();

        #endregion


        public SortedList<int, Target> TargetList { get { return this.targetList; } }

        public SortedList<int, Group> GroupList { get { return this.groupList; } }

        public SortedList<int, File> FileList { get { return this.fileList; } }

        public string Name { get { return this.mName; } set { this.mName = value; } }
        public string ProjectPath { get { return this.mProjectPath; } set { this.mProjectPath = value; } }
        public TargetOptions DefaultOptions { get { return this.mDefaultOptions; } set { this.mDefaultOptions = value; } }

        public SortedList<int, string> Scatter { get { return this.mScatter; } }

        

        #region Metods

        public void AddFile(string path, string group)
        {
            string ext = System.IO.Path.GetExtension(path).Trim();
            if (!System.IO.File.Exists(path))
            {
                if (
                    (string.Compare(ext, ".lib", StringComparison.InvariantCultureIgnoreCase) != 0)
                    &&
                    (string.Compare(ext, ".o", StringComparison.InvariantCultureIgnoreCase) != 0)
                    &&
                    (string.Compare(ext, ".obj", StringComparison.InvariantCultureIgnoreCase) != 0)
                    )
                {
                    throw new FileNotFoundException(KeilWizardStrings.IDS_FILE + " \"" + path + "\" " + KeilWizardStrings.IDS_MISSING, path);
                }
            }

            if (this.ContainsFile(path)) return;

            File file = new File();

            file.Type = File.FILE_TYPE.TEXT_DOCUMENT_FILE;

            if (string.Compare(ext, ".cpp", StringComparison.InvariantCultureIgnoreCase) == 0)
                file.Type = File.FILE_TYPE.CPP_FILE;
            if (string.Compare(ext, ".c", StringComparison.InvariantCultureIgnoreCase) == 0)
                file.Type = File.FILE_TYPE.C_FILE;
            if (string.Compare(ext, ".h", StringComparison.InvariantCultureIgnoreCase) == 0)
                file.Type = File.FILE_TYPE.TEXT_DOCUMENT_FILE;
            if (string.Compare(ext, ".s", StringComparison.InvariantCultureIgnoreCase) == 0)
                file.Type = File.FILE_TYPE.ASM_FILE;
            if (string.Compare(ext, ".a", StringComparison.InvariantCultureIgnoreCase) == 0)
                file.Type = File.FILE_TYPE.ASM_FILE;
            if (string.Compare(ext, ".lib", StringComparison.InvariantCultureIgnoreCase) == 0)
                file.Type = File.FILE_TYPE.LIB_FILE;
            if (string.Compare(ext, ".o", StringComparison.InvariantCultureIgnoreCase) == 0)
                file.Type = File.FILE_TYPE.OBJ_FILE;
            if (string.Compare(ext, ".obj", StringComparison.InvariantCultureIgnoreCase) == 0)
                file.Type = File.FILE_TYPE.OBJ_FILE;

            file.Path = path;
            file.Name = System.IO.Path.GetFileName(path);
            file.Group = this.AddGroup(group);
            file.Num = this.FileList.Count + 1;

            this.FileList.Add(file.Num, file);
        }

        public bool ContainsFile(string path)
        {
            foreach (File f in this.FileList.Values)
            {
                if (String.Compare(Path.GetFullPath(path).TrimEnd('\\'), Path.GetFullPath(f.Path).TrimEnd('\\'), StringComparison.InvariantCultureIgnoreCase) == 0) return true;
            }
            return false;
        }

        private Group AddGroup(string name)
        {
            if (!this.ContainsGroup(name))
            {
                Group gt = new Group(name, this.GroupList.Count + 1);
                this.GroupList.Add(gt.Num, gt);
                return gt;
            }
            else
            {
                return this.FindGroup(name);
            }
        }

        public bool ContainsGroup(string name)
        {
            foreach (Group g in this.GroupList.Values)
            {
                if (g.Name == name) return true;
            }
            return false;
        }

        public Group FindGroup(string name)
        {
            if (!ContainsGroup(name)) return null;

            foreach (Group g in this.GroupList.Values)
            {
                if (g.Name == name) return g;
            }
            return null;
        }

        public File FindFile(string path)
        {
            foreach (File file in this.FileList.Values)
            {
                if (file.Path.Contains(path)) return file;
            }
            return null;
        }

        public void SortGroups()
        {
            List<Group> tmplist = new List<Group>(this.GroupList.Values);
            tmplist.Sort();

            this.GroupList.Clear();// = new SortedList<int, Group>();
            foreach (Group g in tmplist)
            {
                g.Num = GroupList.Count + 1;
                this.GroupList.Add(g.Num, g);
            }
        }

        public bool ContainsTarget(Target target)
        {
            foreach (Target t in this.TargetList.Values)
            {
                if ((t.Name == target.Name) && (t.Options.OutDir == target.Options.OutDir) && (t.Options.OutName == target.Options.OutName)) return true;
            }
            return false;
        }


        #region strings

        [DebuggerBrowsable(DebuggerBrowsableState.Never)]
        public List<string> GroupsStrings 
        {
            get
            {
                List<string> result = new List<string>();

                foreach (Group group in this.GroupList.Values)
                {
                    result.Add("Group (" + group.Name + ")");
                }

                result.Add("");

                return result;
            }
        }

        [DebuggerBrowsable(DebuggerBrowsableState.Never)]
        public List<string> FilesStrings 
        {
            get
            {
                List<string> result = new List<string>();

                foreach (File file in this.FileList.Values)
                {
                    result.Add(file.ToString());
                }

                result.Add("");

                return result;
            }
        }


        public List<string> AllProjectStrings 
        {
            get
            {
                List<string> result = new List<string>();

                result.Add("### uVision2 Project, (C) Keil Software");
                result.Add("### Do not modify !");
                result.Add("");
                foreach (Target t in this.TargetList.Values)
                {
                    result.Add(t.TargetString);
                }
                result.Add("");
                result.AddRange(this.GroupsStrings);
                result.Add("");
                result.AddRange(this.FilesStrings);
                result.Add("");
                foreach (Target t in this.TargetList.Values)
                {
                    result.AddRange(t.SolutionOptionsStrings);
                    result.Add("");
                }
                foreach (Target t in this.TargetList.Values)
                {
                    result.AddRange(t.FilesOptionsStrings);
                }
                result.Add("");
                return result;
            }
        }

        #endregion

        #endregion

    }
}
