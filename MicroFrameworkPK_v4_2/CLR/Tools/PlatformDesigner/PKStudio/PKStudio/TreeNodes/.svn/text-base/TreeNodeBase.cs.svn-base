using System.Windows.Forms;
using System;
using System.Collections.Generic;
using System.IO;
using System.Diagnostics;
using PKStudio.ItemWrappers;
using System.Runtime.Serialization;
using System.Collections.ObjectModel;
using XsdInventoryFormatObject;

namespace PKStudio.TreeNodes
{
    [Serializable]
    public class MFTreeNodeBase : TreeNode
    {
        public enum ImageKeysEnum : int
        {
            ExpandedDirectory = 0,
            CollapsedDirectory = 1,
            Directory = 2,
            Library = 3,
            Project = 4,
            Solution = 5,
            Processor = 6,
            LibraryCategory = 7,
            Feature = 8,
            Components = 9,
            ISA = 10,
            Header = 11,
            C = 12,
            CPP = 13,
            CS = 14,
            Unknown = 15,
            Missing = 16,
            Asm = 17,
        }

        public static Type ConvertTypes(ComponentTypeWrapper type)
        {
            Type retval = null;
            return retval;
        }

        public MFTreeNodeBase(string Name, ImageKeysEnum key) : base(Name) { this.SelectedImageIndex = (int)key; this.ImageIndex = (int)key; this.Name = Name; }

        public MFTreeNodeBase() : base() { }

        protected MFTreeNodeBase(SerializationInfo serializationInfo, StreamingContext context) : base(serializationInfo, context) { }

        private bool _modified = false;

        public bool Modified { get { return this._modified; } set { this._modified = value; } }

        public override object Clone()
        {
            TreeNode tn = (TreeNode)base.Clone();

            //PKStudio.Forms.BaseForms.ExplorerBaseForm.CompareNodesExpand(this, tn);

            return tn;
        }

        protected void AddFileList(CollectionWrapper<BuildFileWrapper, MFBuildFile> source_list, string path)
        {
            List<string> unicue_path_list = new List<string>();

            foreach (BuildFileWrapper source_file in source_list)
            {

                string text = ExpandPath(source_file.File);

                if (!File.Exists(text))
                {
                    text = Path.GetFullPath(text);
                }
                if (!File.Exists(text))
                {
                    text = Path.GetFullPath(ExpandPath(Path.GetDirectoryName(path) + "\\" + ExpandPath(source_file.File)));
                }
                if (!File.Exists(text))
                {
                }

                if (!unicue_path_list.Contains(text))
                {
                    source_file.FullPath = text;
                    unicue_path_list.Add(text);
                    MFTreeNodeBase SourceNode = new MFSourceFileTreeNode(source_file);//this.NewNode(Path.GetFileName(source_file.File), MFTreeNodeBase.TreeNodeType.SourceFile, source_file, key);
                    this.Nodes.Add(SourceNode);
                }
                else
                {

                }
            }
        }


        private string ExpandPath(string path)
        {
            string result = string.Empty;

            //string srcDirEnvVar = Environment.GetEnvironmentVariable("SRC_DIR");
            //if (srcDirEnvVar != null)
            //{
            //}
            result = PK.Wrapper.ExpandEnvVars(path, "");

            if (result.Contains("%SRC_DIR%\\"))
                result = result.Replace("%SRC_DIR%\\", "");

            return Environment.ExpandEnvironmentVariables(result);
        }
    }
}
