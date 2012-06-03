using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace PKStudio.uVision.Project
{
    /// <summary>
    /// Описывает файл в проекте uVision
    /// </summary>
    public class File
    {
        /// <summary>
        /// Тип файла
        /// </summary>
        public enum FILE_TYPE : byte
        {
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
        ///// Персональные настройки файла
        ///// </summary>
        //List<FileOptions> options = new List<FileOptions>();

        /// <summary>
        /// Группа в которую файл входит
        /// </summary>
        Group group = new Group();

        #endregion

        #region Properties
        /// <summary>
        /// Тип файла
        /// </summary>
        public FILE_TYPE Type { get; set; }
        /// <summary>
        /// Группа в которую файл входит
        /// </summary>
        public Group Group { get { return this.group; } set { this.group = value; } }
        /// <summary>
        /// Путь к файлу
        /// </summary>
        public string Path { get; set; }
        /// <summary>
        /// Имя файла
        /// </summary>
        public string Name { get; set; }
        /// <summary>
        /// Порядковый номер файла
        /// </summary>
        public int Num { get; set; }

        ///// <summary>
        ///// Персональные настройки файла
        ///// </summary>
        //public List<FileOptions> Options { get { return this.options; } }
        #endregion

        /// <summary>
        /// Возвращает строку, описывающую файл в текстовом виде
        /// </summary>
        /// <returns></returns>
        public string GetFileString()
        {
            return "File " + this.Group.Num.ToString() + "," + (int)this.Type + ",<" + this.Path + "><" + this.Name + ">";
        }

        //public List<string> GetFileOptionsStrings()
        //{
        //    List<string> result = new List<string>();

        //    foreach (FileOptions opt in this.Options)
        //    {
        //        if (!opt.IsDefault())
        //        {
        //            string str = string.Empty;
        //            result.Add("Options " + opt.Target.Num + "," + this.Group.Num + "," + this.Num + "  // File '" + this.Name + "'");
        //            result.Add(" PropFld { " + opt.PropFld + " }");
        //            result.Add(" IncBld=" + (int)opt.IncBld);
        //            result.Add(" AlwaysBuild=" + (int)opt.AlwaysBuild);
        //            result.Add(" GenAsm=" + (int)opt.GenAsm);
        //            result.Add(" AsmAsm=" + (int)opt.AsmAsm);
        //            result.Add(" PublicsOnly=" + (int)opt.PublicsOnly);
        //            result.Add(" StopCode=" + (int)opt.StopCode);
        //            str = " CustArgs (";
        //            if (opt.CustArgs.Count > 0)
        //            {
        //                for (int i = 0; i < opt.CustArgs.Count - 1; i++)
        //                {
        //                    str += opt.CustArgs[i] + " ";
        //                }
        //                str += opt.CustArgs[opt.CustArgs.Count - 1];
        //            }
        //            str += ")";
        //            result.Add(str);

        //            str = " LibMods (";
        //            if (opt.LibMods.Count > 0)
        //            {
        //                for (int i = 0; i < opt.LibMods.Count - 1; i++)
        //                {
        //                    str += opt.LibMods[i] + " ";
        //                }
        //                str += opt.LibMods[opt.LibMods.Count - 1];
        //            }
        //            str += ")";
        //            result.Add(str);

        //            string flg = string.Empty;
        //            string misc = string.Empty;
        //            string def = string.Empty;
        //            string undef = string.Empty;
        //            string inc = string.Empty;

        //            switch (this.Type)
        //            {
        //                case FILE_TYPE.C_FILE:
        //                case FILE_TYPE.CPP_FILE:
        //                    flg = "ADSCCFLG";
        //                    misc = "ADSCMISC";
        //                    def = "ADSCDEFN";
        //                    undef = "ADSCUDEF";
        //                    inc = "ADSCINCD";
        //                    break;
        //                case FILE_TYPE.ASM_FILE:
        //                    flg = "ADSASFLG";
        //                    misc = "ADSAMISC";
        //                    def = "ADSADEFN";
        //                    undef = "ADSAUDEF";
        //                    inc = "ADSAINCD";
        //                    break;
        //            }
        //            if (misc != string.Empty)
        //            {
        //                if (flg == "ADSCCFLG")
        //                    result.Add(" " + flg + " { " + opt.ADSCCFLG.GetString() + " }");
        //                if (flg == "ADSASFLG")
        //                    result.Add(" " + flg + " { " + opt.ADSCCFLG + " }");
        //                str = " " + misc + " (";
        //                if (opt.Misc.Count > 0)
        //                {
        //                    for (int i = 0; i < opt.Misc.Count - 1; i++)
        //                    {
        //                        str += opt.Misc[i] + " ";
        //                    }
        //                    str += opt.Misc[opt.Misc.Count - 1];
        //                }
        //                str += ")";
        //                result.Add(str);

        //                str = " " + def + " (";
        //                if (opt.Define.Count > 0)
        //                {
        //                    for (int i = 0; i < opt.Define.Count - 1; i++)
        //                    {
        //                        str += opt.Define[i] + ", ";
        //                    }
        //                    str += opt.Define[opt.Define.Count - 1];
        //                }
        //                str += ")";
        //                result.Add(str);

        //                str = " " + undef + " (";
        //                if (opt.UnDefine.Count > 0)
        //                {
        //                    for (int i = 0; i < opt.UnDefine.Count - 1; i++)
        //                    {
        //                        str += opt.UnDefine[i] + ", ";
        //                    }
        //                    str += opt.UnDefine[opt.UnDefine.Count - 1];
        //                }
        //                str += ")";
        //                result.Add(str);

        //                str = " " + inc + " (";
        //                if (opt.Include.Count > 0)
        //                {
        //                    for (int i = 0; i < opt.Include.Count - 1; i++)
        //                    {
        //                        str += opt.Include[i] + ";";
        //                    }
        //                    str += opt.Include[opt.Include.Count - 1];
        //                }
        //                str += ")";
        //                result.Add(str);
        //            }
        //            result.Add("EndOpt");
        //            result.Add("\r\n");
        //        }
        //    }

        //    return result;
        //}

    }
}
