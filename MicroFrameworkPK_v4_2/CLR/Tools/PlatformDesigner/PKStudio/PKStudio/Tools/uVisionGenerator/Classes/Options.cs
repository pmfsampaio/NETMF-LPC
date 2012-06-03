using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace PKStudio.uVision.Project
{
    /// <summary>
    /// Булевы опции из 3х состояний
    /// </summary>
    public enum THREE_STATE_BOOL : int
    {
        DISABLED = 0,
        ENABLED = 1,
        DEFAULT = 2,
    }

    public enum TWO_STATE_BOOL : int
    {
        DISABLED = 0,
        ENABLED = 1,
    }

    public enum STOP_CODE : int
    {
        /// <summary>
        /// Never
        /// </summary>
        Never = 0,
        /// <summary>
        /// Translator Warnings (Exit Code >= 1)
        /// </summary>
        ExitCode_GE_1 = 1,
        /// <summary>
        /// Translator Errors (Exit Code >= 2)
        /// </summary>
        ExitCode_GE_2 = 2,
        /// <summary>
        /// Translator Fatal Errors (Exit Code >= 3)
        /// </summary>
        ExitCode_GE_3 = 3,
        /// <summary>
        /// Custom Exit Code >= 4
        /// </summary>
        ExitCode_GE_4 = 4,
        /// <summary>
        /// Custom Exit Code >= 5
        /// </summary>
        ExitCode_GE_5 = 5,
        /// <summary>
        /// Custom Exit Code >= 6
        /// </summary>
        ExitCode_GE_6 = 6,
        /// <summary>
        /// Custom Exit Code >= 7
        /// </summary>
        ExitCode_GE_7 = 7,
        /// <summary>
        /// Custom Exit Code >= 8
        /// </summary>
        ExitCode_GE_8 = 8,
        /// <summary>
        /// Custom Exit Code >= 9
        /// </summary>
        ExitCode_GE_9 = 9,
        /// <summary>
        /// Custom Exit Code >= 10
        /// </summary>
        ExitCode_GE_10 = 10,
        /// <summary>
        /// Not Specified
        /// </summary>
        NotSecified = 11,

    }

    /// <summary>
    /// Optimisation
    /// </summary>
    public enum OPTIMIZATION : int
    {
        Default = 0,
        Level0 = 1,
        Level1 = 2,
        Level2 = 3,
        Level3 = 4,
    }

    /// <summary>
    /// Warnings
    /// </summary>
    public enum WARNINGS : int
    {
        Unspecified = 0,
        NoWarnings = 1,
        AllWarnings = 2,
    }


    public class ADSCCFLG_TYPE
    {
        #region fields
        /// <summary>
        /// Enable ARM/Thumb Interworking
        /// </summary>
        private THREE_STATE_BOOL _ARM_Thumb_Interworking = THREE_STATE_BOOL.DEFAULT;
        /// <summary>
        /// Optimisation
        /// </summary>
        private OPTIMIZATION _Optimisation = OPTIMIZATION.Default;
        /// <summary>
        /// Optimize for time
        /// </summary>
        private THREE_STATE_BOOL _Optimize_for_time = THREE_STATE_BOOL.DEFAULT;
        /// <summary>
        /// Split Load and Store Multiple
        /// </summary>
        private THREE_STATE_BOOL _Split_Load_and_Store_Multiple = THREE_STATE_BOOL.DEFAULT;
        /// <summary>
        /// One EFL Section per Function
        /// </summary>
        private THREE_STATE_BOOL _One_EFL_Section_per_Function = THREE_STATE_BOOL.DEFAULT;
        /// <summary>
        /// Strict ANSI C
        /// </summary>
        private THREE_STATE_BOOL _Strict_ANSI_C = THREE_STATE_BOOL.DEFAULT;
        /// <summary>
        /// Enum Container always int
        /// </summary>
        private THREE_STATE_BOOL _Enum_Container_always_int = THREE_STATE_BOOL.DEFAULT;
        /// <summary>
        /// Plain Char is Signed
        /// </summary>
        private THREE_STATE_BOOL _Plain_Char_is_Signed = THREE_STATE_BOOL.DEFAULT;
        /// <summary>
        /// Read-Only Position Independent
        /// </summary>
        private THREE_STATE_BOOL _ReadOnly_Position_Independent = THREE_STATE_BOOL.DEFAULT;
        /// <summary>
        /// Read-Write Position Independent
        /// </summary>
        private THREE_STATE_BOOL _ReadWrite_Position_Independent = THREE_STATE_BOOL.DEFAULT;
        /// <summary>
        /// Warnings
        /// </summary>
        private WARNINGS _Warnings = WARNINGS.Unspecified;
        /// <summary>
        /// Thumb Mode
        /// </summary>
        private THREE_STATE_BOOL _Thumb_Mode = THREE_STATE_BOOL.DEFAULT;
        #endregion

        #region properties
        /// <summary>
        /// Enable ARM/Thumb Interworking
        /// </summary>
        public THREE_STATE_BOOL ARM_Thumb_Interworking { get { return _ARM_Thumb_Interworking; } set { this._ARM_Thumb_Interworking = value; } }
        /// <summary>
        /// Optimisation
        /// </summary>
        public OPTIMIZATION Optimisation { get { return _Optimisation; } set { this._Optimisation = value; } }
        /// <summary>
        /// Optimize for time
        /// </summary>
        public THREE_STATE_BOOL Optimize_for_time { get { return _Optimize_for_time; } set { this._Optimize_for_time = value; } }
        /// <summary>
        /// Split Load and Store Multiple
        /// </summary>
        public THREE_STATE_BOOL Split_Load_and_Store_Multiple { get { return _Split_Load_and_Store_Multiple; } set { this._Split_Load_and_Store_Multiple = value; } }
        /// <summary>
        /// One EFL Section per Function
        /// </summary>
        public THREE_STATE_BOOL One_EFL_Section_per_Function { get { return _One_EFL_Section_per_Function; } set { this._One_EFL_Section_per_Function = value; } }
        /// <summary>
        /// Strict ANSI C
        /// </summary>
        public THREE_STATE_BOOL Strict_ANSI_C { get { return _Strict_ANSI_C; } set { this._Strict_ANSI_C = value; } }
        /// <summary>
        /// Enum Container always int
        /// </summary>
        public THREE_STATE_BOOL Enum_Container_always_int { get { return _Enum_Container_always_int; } set { this._Enum_Container_always_int = value; } }
        /// <summary>
        /// Plain Char is Signed
        /// </summary>
        public THREE_STATE_BOOL Plain_Char_is_Signed { get { return _Plain_Char_is_Signed; } set { this._Plain_Char_is_Signed = value; } }
        /// <summary>
        /// Read-Only Position Independent
        /// </summary>
        public THREE_STATE_BOOL ReadOnly_Position_Independent { get { return _ReadOnly_Position_Independent; } set { this._ReadOnly_Position_Independent = value; } }
        /// <summary>
        /// Read-Write Position Independent
        /// </summary>
        public THREE_STATE_BOOL ReadWrite_Position_Independent { get { return _ReadWrite_Position_Independent; } set { this._ReadWrite_Position_Independent = value; } }
        /// <summary>
        /// Warnings
        /// </summary>
        public WARNINGS Warnings { get { return _Warnings; } set { this._Warnings = value; } }
        /// <summary>
        /// Thumb Mode
        /// </summary>
        public THREE_STATE_BOOL Thumb_Mode { get { return _Thumb_Mode; } set { this._Thumb_Mode = value; } }
        #endregion


        #region Metods
        public string GetString()
        {
            string result = string.Empty;
            byte bt = 0;

            switch (this._ARM_Thumb_Interworking)
            {
                case THREE_STATE_BOOL.DISABLED:
                    bt = (byte)(bt & (byte)0xFC);
                    break;
                case THREE_STATE_BOOL.ENABLED:
                    bt = (byte)(bt & (byte)0xFC);
                    bt = (byte)(bt | (byte)0x01);
                    break;
                case THREE_STATE_BOOL.DEFAULT:
                    bt = (byte)(bt & (byte)0xFC);
                    bt = (byte)(bt | (byte)0x02);
                    break;
            }

            switch (this._Optimisation)
            {
                case OPTIMIZATION.Default:
                    bt = (byte)(bt & (byte)0xE3);
                    break;
                case OPTIMIZATION.Level0:
                    bt = (byte)(bt & (byte)0xE3);
                    bt = (byte)(bt | (byte)0x04);
                    break;
                case OPTIMIZATION.Level1:
                    bt = (byte)(bt & (byte)0xE3);
                    bt = (byte)(bt | (byte)0x08);
                    break;
                case OPTIMIZATION.Level2:
                    bt = (byte)(bt & (byte)0xE3);
                    bt = (byte)(bt | (byte)0x0C);
                    break;
                case OPTIMIZATION.Level3:
                    bt = (byte)(bt & (byte)0xE3);
                    bt = (byte)(bt | (byte)0x10);
                    break;
                default:
                    break;
            }

            result = bt.ToString() + ",";

            bt = 0;

            switch (this._Optimize_for_time)
            {
                case THREE_STATE_BOOL.DISABLED:
                    bt = (byte)(bt & (byte)0xF9);
                    break;
                case THREE_STATE_BOOL.ENABLED:
                    bt = (byte)(bt & (byte)0xF9);
                    bt = (byte)(bt | (byte)0x02);
                    break;
                case THREE_STATE_BOOL.DEFAULT:
                    bt = (byte)(bt & (byte)0xF9);
                    bt = (byte)(bt | (byte)0x04);
                    break;
            }
            switch (this._Split_Load_and_Store_Multiple)
            {
                case THREE_STATE_BOOL.DISABLED:
                    bt = (byte)(bt & (byte)0xE7);
                    break;
                case THREE_STATE_BOOL.ENABLED:
                    bt = (byte)(bt & (byte)0xE7);
                    bt = (byte)(bt | (byte)0x08);
                    break;
                case THREE_STATE_BOOL.DEFAULT:
                    bt = (byte)(bt & (byte)0xE7);
                    bt = (byte)(bt | (byte)0x10);
                    break;
            }
            switch (this._One_EFL_Section_per_Function)
            {
                case THREE_STATE_BOOL.DISABLED:
                    bt = (byte)(bt & (byte)0x9F);
                    break;
                case THREE_STATE_BOOL.ENABLED:
                    bt = (byte)(bt & (byte)0x9F);
                    bt = (byte)(bt | (byte)0x20);
                    break;
                case THREE_STATE_BOOL.DEFAULT:
                    bt = (byte)(bt & (byte)0x9F);
                    bt = (byte)(bt | (byte)0x40);
                    break;
            }
            switch (this._Strict_ANSI_C)
            {
                case THREE_STATE_BOOL.DISABLED:
                    bt = (byte)(bt & (byte)0x7E);
                    break;
                case THREE_STATE_BOOL.ENABLED:
                    bt = (byte)(bt & (byte)0x7E);
                    bt = (byte)(bt | (byte)0x80);
                    break;
            }
            result += bt.ToString() + ",";
            bt = 0;
            switch (this._Strict_ANSI_C)
            {
                case THREE_STATE_BOOL.DEFAULT:
                    bt = (byte)(bt & (byte)0x7E);
                    bt = (byte)(bt | (byte)0x01);
                    break;
            }

            switch (this._Enum_Container_always_int)
            {
                case THREE_STATE_BOOL.DISABLED:
                    bt = (byte)(bt & (byte)0xF9);
                    break;
                case THREE_STATE_BOOL.ENABLED:
                    bt = (byte)(bt & (byte)0xF9);
                    bt = (byte)(bt | (byte)0x02);
                    break;
                case THREE_STATE_BOOL.DEFAULT:
                    bt = (byte)(bt & (byte)0xF9);
                    bt = (byte)(bt | (byte)0x04);
                    break;
            }
            switch (this._Plain_Char_is_Signed)
            {
                case THREE_STATE_BOOL.DISABLED:
                    bt = (byte)(bt & (byte)0xE7);
                    break;
                case THREE_STATE_BOOL.ENABLED:
                    bt = (byte)(bt & (byte)0xE7);
                    bt = (byte)(bt | (byte)0x08);
                    break;
                case THREE_STATE_BOOL.DEFAULT:
                    bt = (byte)(bt & (byte)0xE7);
                    bt = (byte)(bt | (byte)0x10);
                    break;
            }
            switch (this._ReadOnly_Position_Independent)
            {
                case THREE_STATE_BOOL.DISABLED:
                    bt = (byte)(bt & (byte)0x9F);
                    break;
                case THREE_STATE_BOOL.ENABLED:
                    bt = (byte)(bt & (byte)0x9F);
                    bt = (byte)(bt | (byte)0x20);
                    break;
                case THREE_STATE_BOOL.DEFAULT:
                    bt = (byte)(bt & (byte)0x9F);
                    bt = (byte)(bt | (byte)0x40);
                    break;
            }
            switch (this._ReadWrite_Position_Independent)
            {
                case THREE_STATE_BOOL.DISABLED:
                    bt = (byte)(bt & (byte)0x7E);
                    break;
                case THREE_STATE_BOOL.ENABLED:
                    bt = (byte)(bt & (byte)0x7E);
                    bt = (byte)(bt | (byte)0x80);
                    break;
            }
            result += bt.ToString() + ",";
            bt = 0;

            switch (this._ReadWrite_Position_Independent)
            {
                case THREE_STATE_BOOL.DEFAULT:
                    bt = (byte)(bt & (byte)0x7E);
                    bt = (byte)(bt | (byte)0x01);
                    break;
            }

            switch (this._Warnings)
            {
                case WARNINGS.Unspecified:
                    bt = (byte)(bt & (byte)0xF9);
                    break;
                case WARNINGS.NoWarnings:
                    bt = (byte)(bt & (byte)0xF9);
                    bt = (byte)(bt | (byte)0x02);
                    break;
                case WARNINGS.AllWarnings:
                    bt = (byte)(bt & (byte)0xF9);
                    bt = (byte)(bt | (byte)0x04);
                    break;
                default:
                    break;
            }
            switch (this._Thumb_Mode)
            {
                case THREE_STATE_BOOL.DISABLED:
                    bt = (byte)(bt & (byte)0xCF);
                    break;
                case THREE_STATE_BOOL.ENABLED:
                    bt = (byte)(bt & (byte)0xCF);
                    bt = (byte)(bt | (byte)0x10);
                    break;
                case THREE_STATE_BOOL.DEFAULT:
                    bt = (byte)(bt & (byte)0xCF);
                    bt = (byte)(bt | (byte)0x20);
                    break;
            }
            result += bt.ToString() + ",";
            result += "0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0";

            //5,0,0,0,|0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0

            return result;
        }
        #endregion

    }


    public class RUN_USER_TYPE
    {
        public RUN_USER_TYPE()
        {
            Command = "";
            Run = TWO_STATE_BOOL.DISABLED;
        }

        public TWO_STATE_BOOL Run { get; set; }
        public string Command { get; set; }

        public string GetString()
        {
            return ((int)this.Run).ToString() + " " + this.Command;
        }
    }

    public class FileOptions
    {
        #region fields
        //private Target target =  null;

        private File file = new File();

        /// <summary>
        /// PropFld - некие настройки проекта
        /// </summary>
        private string _PropFld = "2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0";

        /// <summary>
        /// Include in Target Build
        /// </summary>
        private THREE_STATE_BOOL _IncBld = THREE_STATE_BOOL.DEFAULT;

        /// <summary>
        /// Always Build
        /// </summary>
        private THREE_STATE_BOOL _AlwaysBuild = THREE_STATE_BOOL.DEFAULT;

        private THREE_STATE_BOOL _GenAsm = THREE_STATE_BOOL.DEFAULT;

        private THREE_STATE_BOOL _AsmAsm = THREE_STATE_BOOL.DEFAULT;

        private THREE_STATE_BOOL _PublicsOnly = THREE_STATE_BOOL.DEFAULT;

        /// <summary>
        /// Stop on Exit Code
        /// </summary>
        private STOP_CODE _StopCode = STOP_CODE.NotSecified;

        /// <summary>
        /// Custom Arguments
        /// </summary>
        private List<string> _CustArgs = new List<string>();

        /// <summary>
        /// Library Moduls
        /// </summary>
        private List<string> _LibMods = new List<string>();


        private string _ADSASFLG = "170,42,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0";
        private ADSCCFLG_TYPE _ADSCCFLG = new ADSCCFLG_TYPE();
        private List<string> _Define = new List<string>();
        private List<string> _UnDefine = new List<string>();
        private List<string> _Include = new List<string>();
        private List<string> _Misc = new List<string>();
        #endregion

        #region Properties

        //public Target Target { get { return this.target; } set { this.target = value; } }

        public File File { get { return this.file; } set { this.file = value; } }

        /// <summary>
        /// PropFld
        /// </summary>
        public string PropFld { get { return _PropFld; } set { this._PropFld = value; } }
        /// <summary>
        /// Include in Target Build
        /// </summary>
        public THREE_STATE_BOOL IncBld { get { return _IncBld; } set { this._IncBld = value; } }
        /// <summary>
        /// Always Build
        /// </summary>
        public THREE_STATE_BOOL AlwaysBuild { get { return _AlwaysBuild; } set { this._AlwaysBuild = value; } }
        /// <summary>
        /// GenAsm
        /// </summary>
        public THREE_STATE_BOOL GenAsm { get { return _GenAsm; } set { this._GenAsm = value; } }
        /// <summary>
        /// AsmAsm
        /// </summary>
        public THREE_STATE_BOOL AsmAsm { get { return _AsmAsm; } set { this._AsmAsm = value; } }
        /// <summary>
        /// PublicsOnly
        /// </summary>
        public THREE_STATE_BOOL PublicsOnly { get { return _PublicsOnly; } set { this._PublicsOnly = value; } }
        /// <summary>
        /// Stop on Exit Code
        /// </summary>
        public STOP_CODE StopCode { get { return _StopCode; } set { this._StopCode = value; } }
        /// <summary>
        /// Custom Arguments
        /// </summary>
        public List<string> CustArgs { get { return _CustArgs; } }
        /// <summary>
        /// Library Moduls
        /// </summary>
        public List<string> LibMods { get { return _LibMods; } }
        /// <summary>
        /// ADSCCFLG
        /// </summary>
        public ADSCCFLG_TYPE ADSCCFLG { get { return _ADSCCFLG; } set { this._ADSCCFLG = value; } }

        public string ADSASFLG { get { return _ADSASFLG; } set { this._ADSASFLG = value; } }
        /// <summary>
        /// ADSCDEFN
        /// </summary>
        public List<string> Define { get { return _Define; } }
        /// <summary>
        /// ADSCUDEF
        /// </summary>
        public List<string> UnDefine { get { return _UnDefine; } }
        /// <summary>
        /// ADSCINCD
        /// </summary>
        public List<string> Include { get { return _Include; } }
        /// <summary>
        /// ADSCMISC
        /// </summary>
        public List<string> Misc { get { return _Misc; } }

        #endregion

        public FileOptions()
        {
        }

        public FileOptions(File file)
        {
            this.file = file;
        }


        /// <summary>
        /// Использовать ли опции по умолчанию
        /// </summary>
        /// <returns>true</returns>
        public bool IsDefault()
        {
            if (this.PropFld != "2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0") return false;
            if (this.AlwaysBuild != THREE_STATE_BOOL.DEFAULT) return false;
            if (this.IncBld != THREE_STATE_BOOL.DEFAULT) return false;
            if (this.GenAsm != THREE_STATE_BOOL.DEFAULT) return false;
            if (this.AsmAsm != THREE_STATE_BOOL.DEFAULT) return false;
            if (this.PublicsOnly != THREE_STATE_BOOL.DEFAULT) return false;
            if (this.StopCode != STOP_CODE.NotSecified) return false;
            if (this.CustArgs.Count > 0) return false;
            if (this.LibMods.Count > 0) return false;
            if (this.ADSCCFLG.GetString() != "2,84,85,33,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0") return false;
            if (this.ADSASFLG != "170,42,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0") return false;
            if (this.Define.Count > 0) return false;
            if (this.UnDefine.Count > 0) return false;
            if (this.Include.Count > 0) return false;
            if (this.Misc.Count > 0) return false;
            return true;
        }

        public List<string> GetFileOptionsStrings(int TargetNum)
        {
            List<string> result = new List<string>();
            if (!this.IsDefault())
            {
                string str = string.Empty;
                result.Add("Options " + TargetNum + "," + this.file.Group.Num + "," + this.file.Num + "  // File '" + this.file.Name + "'");
                result.Add(" PropFld { " + this.PropFld + " }");
                result.Add(" IncBld=" + (int)this.IncBld);
                result.Add(" AlwaysBuild=" + (int)this.AlwaysBuild);
                result.Add(" GenAsm=" + (int)this.GenAsm);
                result.Add(" AsmAsm=" + (int)this.AsmAsm);
                result.Add(" PublicsOnly=" + (int)this.PublicsOnly);
                result.Add(" StopCode=" + (int)this.StopCode);
                str = " CustArgs (";
                if (this.CustArgs.Count > 0)
                {
                    for (int i = 0; i < this.CustArgs.Count - 1; i++)
                    {
                        str += this.CustArgs[i] + " ";
                    }
                    str += this.CustArgs[this.CustArgs.Count - 1];
                }
                str += ")";
                result.Add(str);

                str = " LibMods (";
                if (this.LibMods.Count > 0)
                {
                    for (int i = 0; i < this.LibMods.Count - 1; i++)
                    {
                        str += this.LibMods[i] + " ";
                    }
                    str += this.LibMods[this.LibMods.Count - 1];
                }
                str += ")";
                result.Add(str);

                string flg = string.Empty;
                string misc = string.Empty;
                string def = string.Empty;
                string undef = string.Empty;
                string inc = string.Empty;

                switch (this.file.Type)
                {
                    case PKStudio.uVision.Project.File.FILE_TYPE.C_FILE:
                    case PKStudio.uVision.Project.File.FILE_TYPE.CPP_FILE:
                        flg = "ADSCCFLG";
                        misc = "ADSCMISC";
                        def = "ADSCDEFN";
                        undef = "ADSCUDEF";
                        inc = "ADSCINCD";
                        break;
                    case PKStudio.uVision.Project.File.FILE_TYPE.ASM_FILE:
                        flg = "ADSASFLG";
                        misc = "ADSAMISC";
                        def = "ADSADEFN";
                        undef = "ADSAUDEF";
                        inc = "ADSAINCD";
                        break;
                }
                if (misc != string.Empty)
                {
                    if (flg == "ADSCCFLG")
                        result.Add(" " + flg + " { " + this.ADSCCFLG.GetString() + " }");
                    if (flg == "ADSASFLG")
                        result.Add(" " + flg + " { " + this.ADSCCFLG + " }");
                    str = " " + misc + " (";
                    if (this.Misc.Count > 0)
                    {
                        for (int i = 0; i < this.Misc.Count - 1; i++)
                        {
                            str += this.Misc[i] + " ";
                        }
                        str += this.Misc[this.Misc.Count - 1];
                    }
                    str += ")";
                    result.Add(str);

                    str = " " + def + " (";
                    if (this.Define.Count > 0)
                    {
                        for (int i = 0; i < this.Define.Count - 1; i++)
                        {
                            str += this.Define[i] + ", ";
                        }
                        str += this.Define[this.Define.Count - 1];
                    }
                    str += ")";
                    result.Add(str);

                    str = " " + undef + " (";
                    if (this.UnDefine.Count > 0)
                    {
                        for (int i = 0; i < this.UnDefine.Count - 1; i++)
                        {
                            str += this.UnDefine[i] + ", ";
                        }
                        str += this.UnDefine[this.UnDefine.Count - 1];
                    }
                    str += ")";
                    result.Add(str);

                    str = " " + inc + " (";
                    if (this.Include.Count > 0)
                    {
                        for (int i = 0; i < this.Include.Count - 1; i++)
                        {
                            str += this.Include[i] + ";";
                        }
                        str += this.Include[this.Include.Count - 1];
                    }
                    str += ")";
                    result.Add(str);
                }
                result.Add("EndOpt");
            }

            return result;
        }
    }

    /// <summary>
    /// Класс описывающий настройки всего проекта
    /// </summary>
    public class TargetOptions
    {
        #region Fields

        /// <summary>
        /// Device name
        /// </summary>
        private string _Device = string.Empty;
        /// <summary>
        /// Vendor name
        /// </summary>
        private string _Vendor = string.Empty;
        /// <summary>
        /// CPU settings
        /// </summary>
        private string _Cpu = string.Empty;
        /// <summary>
        /// Flash utility
        /// </summary>
        private string _FlashUt = string.Empty;
        /// <summary>
        /// Startup file
        /// </summary>
        private string _StupF = string.Empty;
        /// <summary>
        /// 
        /// </summary>
        private string _FlashDR = string.Empty;
        /// <summary>
        /// Device ID
        /// </summary>
        private string _DevID = string.Empty;
        /// <summary>
        /// Registers definition file
        /// </summary>
        private string _Rgf = string.Empty;
        /// <summary>
        /// 
        /// </summary>
        private string _Mem = string.Empty;
        /// <summary>
        /// 
        /// </summary>
        private string _C = string.Empty;
        /// <summary>
        /// 
        /// </summary>
        private string _A = string.Empty;
        /// <summary>
        /// 
        /// </summary>
        private string _RL = string.Empty;
        /// <summary>
        /// 
        /// </summary>
        private string _OH = string.Empty;
        /// <summary>
        /// 
        /// </summary>
        private string _DBC_IFX = string.Empty;
        /// <summary>
        /// 
        /// </summary>
        private string _DBC_CMS = string.Empty;
        /// <summary>
        /// 
        /// </summary>
        private string _DBC_AMS = string.Empty;
        /// <summary>
        /// 
        /// </summary>
        private string _DBC_LMS = string.Empty;
        /// <summary>
        /// 
        /// </summary>
        private string _UseEnv = string.Empty;
        /// <summary>
        /// 
        /// </summary>
        private string _EnvBin = string.Empty;
        /// <summary>
        /// 
        /// </summary>
        private string _EnvInc = string.Empty;
        /// <summary>
        /// 
        /// </summary>
        private string _EnvLib = string.Empty;
        /// <summary>
        /// 
        /// </summary>
        private string _EnvReg = string.Empty;
        /// <summary>
        /// 
        /// </summary>
        private string _OrgReg = string.Empty;
        /// <summary>
        /// 
        /// </summary>
        private string _TgStat = string.Empty;
        /// <summary>
        /// 
        /// </summary>
        private string _OutDir = string.Empty;
        /// <summary>
        /// 
        /// </summary>
        private string _OutName = string.Empty;
        /// <summary>
        /// 
        /// </summary>
        private TWO_STATE_BOOL _GenApp = TWO_STATE_BOOL.DISABLED;
        /// <summary>
        /// 
        /// </summary>
        private TWO_STATE_BOOL _GenLib = TWO_STATE_BOOL.ENABLED;
        /// <summary>
        /// 
        /// </summary>
        private string _GenHex = string.Empty;
        /// <summary>
        /// 
        /// </summary>
        private string _Debug = string.Empty;
        /// <summary>
        /// 
        /// </summary>
        private string _Browse = string.Empty;
        /// <summary>
        /// 
        /// </summary>
        private string _LstDir = string.Empty;
        /// <summary>
        /// 
        /// </summary>
        private string _HexSel = string.Empty;
        /// <summary>
        /// 
        /// </summary>
        private string _MG32K = string.Empty;
        /// <summary>
        /// 
        /// </summary>
        private string _TGMORE = string.Empty;
        /// <summary>
        /// 
        /// </summary>
        private RUN_USER_TYPE _RunUsr_0 = new RUN_USER_TYPE();
        /// <summary>
        /// 
        /// </summary>
        private RUN_USER_TYPE _RunUsr_1 = new RUN_USER_TYPE();
        /// <summary>
        /// 
        /// </summary>
        private RUN_USER_TYPE _BrunUsr_0 = new RUN_USER_TYPE();
        /// <summary>
        /// 
        /// </summary>
        private RUN_USER_TYPE _BrunUsr_1 = new RUN_USER_TYPE();
        /// <summary>
        /// 
        /// </summary>
        private RUN_USER_TYPE _CrunUsr_0 = new RUN_USER_TYPE();
        /// <summary>
        /// 
        /// </summary>
        private RUN_USER_TYPE _CrunUsr_1 = new RUN_USER_TYPE();
        /// <summary>
        /// 
        /// </summary>
        private string _SVCSID = string.Empty;
        /// <summary>
        /// 
        /// </summary>
        private string _GLFLAGS = string.Empty;
        /// <summary>
        /// 
        /// </summary>
        private string _ADSFLGA = string.Empty;
        /// <summary>
        /// 
        /// </summary>
        private string _ACPUTYP = string.Empty;
        /// <summary>
        /// 
        /// </summary>
        private string _RVDEV = string.Empty;
        /// <summary>
        /// 
        /// </summary>
        private string _ADSTFLGA = string.Empty;
        /// <summary>
        /// 
        /// </summary>
        private string _OCMADSOCM = string.Empty;
        /// <summary>
        /// 
        /// </summary>
        private string _OCMADSIRAM = string.Empty;
        /// <summary>
        /// 
        /// </summary>
        private string _OCMADSIROM = string.Empty;
        /// <summary>
        /// 
        /// </summary>
        private string _OCMADSXRAM = string.Empty;
        /// <summary>
        /// 
        /// </summary>
        private string _OCR_RVCT = string.Empty;
        /// <summary>
        /// 
        /// </summary>
        private string _RV_STAVEC = string.Empty;
        /// <summary>
        /// C/CPP Flags
        /// </summary>
        private ADSCCFLG_TYPE _ADSCCFLG = new ADSCCFLG_TYPE();
        /// <summary>
        /// C/CPP Misc
        /// </summary>
        private List<string> _ADSCMISC = new List<string>();
        /// <summary>
        /// C/CPP Definitions
        /// </summary>
        private List<string> _ADSCDEFN = new List<string>();
        /// <summary>
        /// C/CPP UnDefinitions
        /// </summary>
        private List<string> _ADSCUDEF = new List<string>();
        /// <summary>
        /// C/CPP Includes
        /// </summary>
        private List<string> _ADSCINCD = new List<string>();
        /// <summary>
        /// ASM Flags
        /// </summary>
        private string _ADSASFLG = string.Empty;
        /// <summary>
        /// ASM Misc
        /// </summary>
        private List<string> _ADSAMISC = new List<string>();
        /// <summary>
        /// ASM Definitions
        /// </summary>
        private List<string> _ADSADEFN = new List<string>();
        /// <summary>
        /// ASM UnDefinitions
        /// </summary>
        private List<string> _ADSAUDEF = new List<string>();
        /// <summary>
        /// ASM Includes
        /// </summary>
        private List<string> _ADSAINCD = new List<string>();
        /// <summary>
        /// 
        /// </summary>
        private string _PropFld = string.Empty;
        /// <summary>
        /// Include in Target Build
        /// </summary>
        private THREE_STATE_BOOL _IncBld = THREE_STATE_BOOL.DEFAULT;

        /// <summary>
        /// Always Build
        /// </summary>
        private THREE_STATE_BOOL _AlwaysBuild = THREE_STATE_BOOL.DEFAULT;

        private THREE_STATE_BOOL _GenAsm = THREE_STATE_BOOL.DEFAULT;

        private THREE_STATE_BOOL _AsmAsm = THREE_STATE_BOOL.DEFAULT;

        private THREE_STATE_BOOL _PublicsOnly = THREE_STATE_BOOL.DEFAULT;

        /// <summary>
        /// Stop on Exit Code
        /// </summary>
        private STOP_CODE _StopCode = STOP_CODE.NotSecified;

        /// <summary>
        /// Custom Arguments
        /// </summary>
        private List<string> _CustArgs = new List<string>();

        /// <summary>
        /// Library Moduls
        /// </summary>
        private List<string> _LibMods = new List<string>();

        /// <summary>
        /// 
        /// </summary>
        private string _ADSLDFG = string.Empty;
        /// <summary>
        /// 
        /// </summary>
        private string _ADSLDTA = string.Empty;
        /// <summary>
        /// 
        /// </summary>
        private string _ADSLDDA = string.Empty;
        /// <summary>
        /// 
        /// </summary>
        private string _ADSLDSC = string.Empty;
        /// <summary>
        /// 
        /// </summary>
        private string _ADSLDIB = string.Empty;
        /// <summary>
        /// 
        /// </summary>
        private string _ADSLDIC = string.Empty;
        /// <summary>
        /// 
        /// </summary>
        private List<string> _ADSLDMC = new List<string>();
        /// <summary>
        /// 
        /// </summary>
        private string _ADSLDIF = string.Empty;
        /// <summary>
        /// 
        /// </summary>
        private string _ADSLDDW = string.Empty;
        /// <summary>
        /// 
        /// </summary>
        private string _OPTDL = string.Empty;
        /// <summary>
        /// 
        /// </summary>
        private string _OPTDBG = string.Empty;
        /// <summary>
        /// 
        /// </summary>
        private string _FLASH1 = string.Empty;
        /// <summary>
        /// 
        /// </summary>
        private string _FLASH2 = string.Empty;
        /// <summary>
        /// 
        /// </summary>
        private string _FLASH3 = string.Empty;
        /// <summary>
        /// 
        /// </summary>
        private string _FLASH4 = string.Empty;


        #endregion

        #region Properties

        /// <summary>
        /// Device name
        /// </summary>
        public string Device { get { return _Device; } set { this._Device = value; } }
        /// <summary>
        /// Vendor name
        /// </summary>
        public string Vendor { get { return _Vendor; } set { this._Vendor = value; } }
        /// <summary>
        /// CPU settings
        /// </summary>
        public string Cpu { get { return _Cpu; } set { this._Cpu = value; } }
        /// <summary>
        /// Flash utility
        /// </summary>
        public string FlashUt { get { return _FlashUt; } set { this._FlashUt = value; } }
        /// <summary>
        /// Startup file
        /// </summary>
        public string StupF { get { return _StupF; } set { this._StupF = value; } }
        /// <summary>
        /// 
        /// </summary>
        public string FlashDR { get { return _FlashDR; } set { this._FlashDR = value; } }
        /// <summary>
        /// Device ID
        /// </summary>
        public string DevID { get { return _DevID; } set { this._DevID = value; } }
        /// <summary>
        /// Registers definition file
        /// </summary>
        public string Rgf { get { return _Rgf; } set { this._Rgf = value; } }
        /// <summary>
        /// 
        /// </summary>
        public string Mem { get { return _Mem; } set { this._Mem = value; } }
        /// <summary>
        /// 
        /// </summary>
        public string C { get { return _C; } set { this._C = value; } }
        /// <summary>
        /// 
        /// </summary>
        public string A { get { return _A; } set { this._A = value; } }
        /// <summary>
        /// 
        /// </summary>
        public string RL { get { return _RL; } set { this._RL = value; } }
        /// <summary>
        /// 
        /// </summary>
        public string OH { get { return _OH; } set { this._OH = value; } }
        /// <summary>
        /// 
        /// </summary>
        public string DBC_IFX { get { return _DBC_IFX; } set { this._DBC_IFX = value; } }
        /// <summary>
        /// 
        /// </summary>
        public string DBC_CMS { get { return _DBC_CMS; } set { this._DBC_CMS = value; } }
        /// <summary>
        /// 
        /// </summary>
        public string DBC_AMS { get { return _DBC_AMS; } set { this._DBC_AMS = value; } }
        /// <summary>
        /// 
        /// </summary>
        public string DBC_LMS { get { return _DBC_LMS; } set { this._DBC_LMS = value; } }
        /// <summary>
        /// 
        /// </summary>
        public string UseEnv { get { return _UseEnv; } set { this._UseEnv = value; } }
        /// <summary>
        /// 
        /// </summary>
        public string EnvBin { get { return _EnvBin; } set { this._EnvBin = value; } }
        /// <summary>
        /// 
        /// </summary>
        public string EnvInc { get { return _EnvInc; } set { this._EnvInc = value; } }
        /// <summary>
        /// 
        /// </summary>
        public string EnvLib { get { return _EnvLib; } set { this._EnvLib = value; } }
        /// <summary>
        /// 
        /// </summary>
        public string EnvReg { get { return _EnvReg; } set { this._EnvReg = value; } }
        /// <summary>
        /// 
        /// </summary>
        public string OrgReg { get { return _OrgReg; } set { this._OrgReg = value; } }
        /// <summary>
        /// 
        /// </summary>
        public string TgStat { get { return _TgStat; } set { this._TgStat = value; } }
        /// <summary>
        /// 
        /// </summary>
        public string OutDir { get { return _OutDir; } set { this._OutDir = value; } }
        /// <summary>
        /// 
        /// </summary>
        public string OutName { get { return _OutName; } set { this._OutName = value; } }
        /// <summary>
        /// 
        /// </summary>
        public TWO_STATE_BOOL GenApp { get { return _GenApp; } set { this._GenApp = value; } }
        /// <summary>
        /// 
        /// </summary>
        public TWO_STATE_BOOL GenLib { get { return _GenLib; } set { this._GenLib = value; } }
        /// <summary>
        /// 
        /// </summary>
        public string GenHex { get { return _GenHex; } set { this._GenHex = value; } }
        /// <summary>
        /// 
        /// </summary>
        public string Debug { get { return _Debug; } set { this._Debug = value; } }
        /// <summary>
        /// 
        /// </summary>
        public string Browse { get { return _Browse; } set { this._Browse = value; } }
        /// <summary>
        /// 
        /// </summary>
        public string LstDir { get { return _LstDir; } set { this._LstDir = value; } }
        /// <summary>
        /// 
        /// </summary>
        public string HexSel { get { return _HexSel; } set { this._HexSel = value; } }
        /// <summary>
        /// 
        /// </summary>
        public string MG32K { get { return _MG32K; } set { this._MG32K = value; } }
        /// <summary>
        /// 
        /// </summary>
        public string TGMORE { get { return _TGMORE; } set { this._TGMORE = value; } }
        /// <summary>
        /// 
        /// </summary>
        public RUN_USER_TYPE RunUsr_0 { get { return _RunUsr_0; } set { this._RunUsr_0 = value; } }
        /// <summary>
        /// 
        /// </summary>
        public RUN_USER_TYPE RunUsr_1 { get { return _RunUsr_1; } set { this._RunUsr_1 = value; } }
        /// <summary>
        /// 
        /// </summary>
        public RUN_USER_TYPE BrunUsr_0 { get { return _BrunUsr_0; } set { this._BrunUsr_0 = value; } }
        /// <summary>
        /// 
        /// </summary>
        public RUN_USER_TYPE BrunUsr_1 { get { return _BrunUsr_1; } set { this._BrunUsr_1 = value; } }
        /// <summary>
        /// 
        /// </summary>
        public RUN_USER_TYPE CrunUsr_0 { get { return _CrunUsr_0; } set { this._CrunUsr_0 = value; } }
        /// <summary>
        /// 
        /// </summary>
        public RUN_USER_TYPE CrunUsr_1 { get { return _CrunUsr_1; } set { this._CrunUsr_1 = value; } }
        /// <summary>
        /// 
        /// </summary>
        public string SVCSID { get { return _SVCSID; } set { this._SVCSID = value; } }
        /// <summary>
        /// 
        /// </summary>
        public string GLFLAGS { get { return _GLFLAGS; } set { this._GLFLAGS = value; } }
        /// <summary>
        /// 
        /// </summary>
        public string ADSFLGA { get { return _ADSFLGA; } set { this._ADSFLGA = value; } }
        /// <summary>
        /// 
        /// </summary>
        public string ACPUTYP { get { return _ACPUTYP; } set { this._ACPUTYP = value; } }
        /// <summary>
        /// 
        /// </summary>
        public string RVDEV { get { return _RVDEV; } set { this._RVDEV = value; } }
        /// <summary>
        /// 
        /// </summary>
        public string ADSTFLGA { get { return _ADSTFLGA; } set { this._ADSTFLGA = value; } }
        /// <summary>
        /// 
        /// </summary>
        public string OCMADSOCM { get { return _OCMADSOCM; } set { this._OCMADSOCM = value; } }
        /// <summary>
        /// 
        /// </summary>
        public string OCMADSIRAM { get { return _OCMADSIRAM; } set { this._OCMADSIRAM = value; } }
        /// <summary>
        /// 
        /// </summary>
        public string OCMADSIROM { get { return _OCMADSIROM; } set { this._OCMADSIROM = value; } }
        /// <summary>
        /// 
        /// </summary>
        public string OCMADSXRAM { get { return _OCMADSXRAM; } set { this._OCMADSXRAM = value; } }
        /// <summary>
        /// 
        /// </summary>
        public string OCR_RVCT { get { return _OCR_RVCT; } set { this._OCR_RVCT = value; } }
        /// <summary>
        /// 
        /// </summary>
        public string RV_STAVEC { get { return _RV_STAVEC; } set { this._RV_STAVEC = value; } }
        /// <summary>
        /// C/CPP Flags
        /// </summary>
        public ADSCCFLG_TYPE ADSCCFLG { get { return _ADSCCFLG; } set { this._ADSCCFLG = value; } }
        /// <summary>
        /// C/CPP Misc
        /// </summary>
        public List<string> ADSCMISC { get { return _ADSCMISC; } }
        /// <summary>
        /// C/CPP Definitions
        /// </summary>
        public List<string> ADSCDEFN { get { return _ADSCDEFN; } }
        /// <summary>
        /// C/CPP UnDefinitions
        /// </summary>
        public List<string> ADSCUDEF { get { return _ADSCUDEF; } }
        /// <summary>
        /// C/CPP Includes
        /// </summary>
        public List<string> ADSCINCD { get { return _ADSCINCD; } }
        /// <summary>
        /// ASM Flags
        /// </summary>
        public string ADSASFLG { get { return _ADSASFLG; } set { this._ADSASFLG = value; } }
        /// <summary>
        /// ASM Misc
        /// </summary>
        public List<string> ADSAMISC { get { return _ADSAMISC; } }
        /// <summary>
        /// ASM Definitions
        /// </summary>
        public List<string> ADSADEFN { get { return _ADSADEFN; } }
        /// <summary>
        /// ASM UnDefinitions
        /// </summary>
        public List<string> ADSAUDEF { get { return _ADSAUDEF; } }
        /// <summary>
        /// ASM Includes
        /// </summary>
        public List<string> ADSAINCD { get { return _ADSAINCD; } }
        /// <summary>
        /// 
        /// </summary>
        public string PropFld { get { return _PropFld; } set { this._PropFld = value; } }
        /// <summary>
        /// Include in Target Build
        /// </summary>
        public THREE_STATE_BOOL IncBld { get { return _IncBld; } set { this._IncBld = value; } }
        /// <summary>
        /// Always Build
        /// </summary>
        public THREE_STATE_BOOL AlwaysBuild { get { return _AlwaysBuild; } set { this._AlwaysBuild = value; } }
        /// <summary>
        /// GenAsm
        /// </summary>
        public THREE_STATE_BOOL GenAsm { get { return _GenAsm; } set { this._GenAsm = value; } }
        /// <summary>
        /// AsmAsm
        /// </summary>
        public THREE_STATE_BOOL AsmAsm { get { return _AsmAsm; } set { this._AsmAsm = value; } }
        /// <summary>
        /// PublicsOnly
        /// </summary>
        public THREE_STATE_BOOL PublicsOnly { get { return _PublicsOnly; } set { this._PublicsOnly = value; } }
        /// <summary>
        /// Stop on Exit Code
        /// </summary>
        public STOP_CODE StopCode { get { return _StopCode; } set { this._StopCode = value; } }
        /// <summary>
        /// Custom Arguments
        /// </summary>
        public List<string> CustArgs { get { return _CustArgs; } }
        /// <summary>
        /// Library Moduls
        /// </summary>
        public List<string> LibMods { get { return _LibMods; } }
        /// <summary>
        /// 
        /// </summary>
        public string ADSLDFG { get { return _ADSLDFG; } set { this._ADSLDFG = value; } }
        /// <summary>
        /// 
        /// </summary>
        public string ADSLDTA { get { return _ADSLDTA; } set { this._ADSLDTA = value; } }
        /// <summary>
        /// 
        /// </summary>
        public string ADSLDDA { get { return _ADSLDDA; } set { this._ADSLDDA = value; } }
        /// <summary>
        /// 
        /// </summary>
        public string ADSLDSC { get { return _ADSLDSC; } set { this._ADSLDSC = value; } }
        /// <summary>
        /// 
        /// </summary>
        public string ADSLDIB { get { return _ADSLDIB; } set { this._ADSLDIB = value; } }
        /// <summary>
        /// 
        /// </summary>
        public string ADSLDIC { get { return _ADSLDIC; } set { this._ADSLDIC = value; } }
        /// <summary>
        /// 
        /// </summary>
        public List<string> ADSLDMC { get { return _ADSLDMC; } set { this._ADSLDMC = value; } }
        /// <summary>
        /// 
        /// </summary>
        public string ADSLDIF { get { return _ADSLDIF; } set { this._ADSLDIF = value; } }
        /// <summary>
        /// 
        /// </summary>
        public string ADSLDDW { get { return _ADSLDDW; } set { this._ADSLDDW = value; } }
        /// <summary>
        /// 
        /// </summary>
        public string OPTDL { get { return _OPTDL; } set { this._OPTDL = value; } }
        /// <summary>
        /// 
        /// </summary>
        public string OPTDBG { get { return _OPTDBG; } set { this._OPTDBG = value; } }
        /// <summary>
        /// 
        /// </summary>
        public string FLASH1 { get { return _FLASH1; } set { this._FLASH1 = value; } }
        /// <summary>
        /// 
        /// </summary>
        public string FLASH2 { get { return _FLASH2; } set { this._FLASH2 = value; } }
        /// <summary>
        /// 
        /// </summary>
        public string FLASH3 { get { return _FLASH3; } set { this._FLASH3 = value; } }
        /// <summary>
        /// 
        /// </summary>
        public string FLASH4 { get { return _FLASH4; } set { this._FLASH4 = value; } }


        #endregion


        //private List<string> armCinc = new List<string>();
        //private List<string> armAinc = new List<string>();

        //private List<string> armCdef = new List<string>();
        //private List<string> armAdef = new List<string>();

        //public string Device { get; set; }
        //public string Vendor { get; set; }

        ////public int CPU { get; set; }
        ////public int FlashUT { get; set; }
        ////public int StupF { get; set; }
        ////public int FlashDR { get; set; }
        ////public int FlashUT { get; set; }

        ////ADSCINCD 
        //public List<string> ArmCInclude { get { return armCinc; } }
        ////ADSAINCD
        //public List<string> ArmAInclude { get { return armAinc; } }

        ////ADSCDEFN  
        //public List<string> ArmCDefine { get { return armCdef; } }
        ////ADSADEFN
        //public List<string> ArmADefine { get { return armAdef; } }
    }
}
