using System;
using System.ComponentModel;
using XsdInventoryFormatObject;
using System.IO;

namespace PKStudio.ItemWrappers
{
    [DefaultProperty("File"), Serializable]
    public class BuildFileWrapper : BaseTypedWrapper<MFBuildFile>, IName
    {
        private BuildFileWrapper(MFBuildFile buildFile)
            : base(buildFile)
        {

        }
        public static BuildFileWrapper GetWrapper(string Path)
        {
            return GetWrapper(Path, string.Empty, string.Empty);
        }
        public static BuildFileWrapper GetWrapper(string Path, string Name)
        {
            return GetWrapper(Path, Name, string.Empty);
        }
        public static BuildFileWrapper GetWrapper(string Path, string Name, string Condition)
        {
            MFBuildFile buildFile = new MFBuildFile();
            buildFile.File = Path;
            buildFile.ItemName = Name;
            buildFile.Condition = Condition;
            return BaseWrapper.Wrap<BuildFileWrapper>(buildFile);
        }


        [Browsable(false)]
        public string Name
        {
            get
            {
                
                try
                {
                    return Path.GetFileName(this.File);
                }
                catch (Exception)
                {

                    return this.File;
                }
            }
            set
            {
                this.File = string.Format(@"{0}\{1}", Path.GetDirectoryName(this.File), Path.GetFileName(value));
            }
        }

        [Category("General")]
        public string Condition
        {
            get
            {
                return this.InnerObject.Condition;
            }
            set
            {
                this.InnerObject.Condition = value;
            }
        }

        [Category("General")]
        public string File
        {
            get
            {
                return this.InnerObject.File;
            }
            set
            {
                this.InnerObject.File = value;
            }
        }

        [Category("General")]
        public string ItemName
        {
            get
            {
                return this.InnerObject.ItemName;
            }
            set
            {
                this.InnerObject.ItemName = value;
            }
        }


        [Category("General")]
        public string FullPath { get; set; }
    }
}
