using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace PKStudio.uVision.Project
{
    /// <summary>
    /// Описывает проект Keil uVision
    /// </summary>
    class uVisionProject
    {

        #region properties

        private SortedList<int, Target> targetList = new SortedList<int, Target>();

        private SortedList<int, Group> groupList = new SortedList<int, Group>();

        private SortedList<int, File> fileList = new SortedList<int, File>();

        #endregion


        public SortedList<int, Target> TargetList { get { return this.targetList; } set { this.targetList = value; } }

        public SortedList<int, Group> GroupList { get { return this.groupList; } set { this.groupList = value; } }

        public SortedList<int, File> FileList { get { return this.fileList; } set { this.fileList = value; } }




        #region Metods

        public void AddFile(string path, string group)//, ParamCollection pars)
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
                    throw new Exception("File missing");
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

            this.GroupList = new SortedList<int, Group>();
            foreach (Group g in tmplist)
            {
                g.Num = GroupList.Count+1;
                this.GroupList.Add(g.Num, g);
            }
        }


        #region strings

        public List<string> GetGroupsStrings()
        {
            List<string> result = new List<string>();

            foreach (Group group in this.GroupList.Values)
            {
                result.Add("Group (" + group.Name + ")");
            }

            result.Add("");

            return result;
        }

        public List<string> GetFilesStrings()
        {
            List<string> result = new List<string>();

            foreach (File file in this.FileList.Values)
            {
                result.Add(file.GetFileString());
            }

            result.Add("");

            return result;
        }

        public List<string> GetAllProjectStrings()
        {
            List<string> result = new List<string>();

            result.Add("### uVision2 Project, (C) Keil Software");
            result.Add("### Do not modify !");
            result.Add("");
            foreach (Target t in this.TargetList.Values)
            {
                result.Add(t.GetTargetString());
            }
            result.Add("");
            result.AddRange(this.GetGroupsStrings());
            result.Add("");
            result.AddRange(this.GetFilesStrings());
            result.Add("");
            foreach (Target t in this.TargetList.Values)
            {
                result.AddRange(t.GetSolutionOptionsStrings());
                result.Add("");
            }
            foreach (Target t in this.TargetList.Values)
            {
                result.AddRange(t.GetFilesOptionsStrings());                
            }
            result.Add("");
            return result;
        }

        #endregion

        #endregion

    }
}
