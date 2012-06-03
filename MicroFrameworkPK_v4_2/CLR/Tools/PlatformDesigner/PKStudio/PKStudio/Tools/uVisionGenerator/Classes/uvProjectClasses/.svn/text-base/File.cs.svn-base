using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace PKStudio.Tools.uVisionGenerator.Classes.uvProjectClasses
{
    /// <summary>
    /// uVision project File
    /// </summary>
    public class File
    {
        /// <summary>
        /// Тип файла
        /// </summary>
        public enum FILE_TYPE : int
        {
            /// <summary>
            /// Unknown file
            /// </summary>
            UNKNOWN = 0,
            /// <summary>
            /// C source file
            /// </summary>
            C_FILE = 1,
            /// <summary>
            /// Assembly language file
            /// </summary>
            ASM_FILE = 2,
            /// <summary>
            /// Object file
            /// </summary>
            OBJ_FILE = 3,
            /// <summary>
            /// Library file
            /// </summary>
            LIB_FILE = 4,
            /// <summary>
            /// Text Document file (h file)
            /// </summary>
            TEXT_DOCUMENT_FILE = 5,
            /// <summary>
            /// Custom file
            /// </summary>
            CUSTOM_FILE = 7,
            /// <summary>
            /// C++ source file
            /// </summary>
            CPP_FILE = 8,
        }

        #region fields
        ///// <summary>
        ///// File personal settings
        ///// </summary>
        //List<FileOptions> options = new List<FileOptions>();

        /// <summary>
        /// File group
        /// </summary>
        Group group = new Group();

        #endregion

        #region Properties
        /// <summary>
        /// Тип файла
        /// </summary>
        public FILE_TYPE Type { get; set; }
        /// <summary>
        /// File group
        /// </summary>
        public Group Group { get { return this.group; } set { this.group = value; } }
        /// <summary>
        /// File path
        /// </summary>
        public string Path { get; set; }
        /// <summary>
        /// File name
        /// </summary>
        public string Name { get; set; }
        /// <summary>
        /// File number
        /// </summary>
        public int Num { get; set; }

        ///// <summary>
        ///// File personal settings
        ///// </summary>
        //public List<FileOptions> Options { get { return this.options; } }
        #endregion

        /// <summary>
        /// Gets file description string
        /// </summary>
        /// <returns></returns>
        public override string ToString()
        {
            return "File " + this.Group.Num.ToString() + "," + (int)this.Type + ",<" + this.Path + "><" + this.Name + ">";
        }
    }
}
