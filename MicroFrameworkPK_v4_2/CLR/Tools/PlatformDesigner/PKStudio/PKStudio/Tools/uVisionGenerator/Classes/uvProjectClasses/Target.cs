using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Diagnostics;

namespace PKStudio.Tools.uVisionGenerator.Classes.uvProjectClasses
{
    public class Target
    {


        public Target()
        {
        }

        public Target(string name, int num)
        {
            this.name = name;
            this.num = num;
        }

        public Target(TargetOptions DefaultOptions)
        {
            this.options = new TargetOptions(DefaultOptions);
        }

        private string name;

        

        private int num;

        private TargetOptions options = new TargetOptions();

        private List<FileOptions> filesoptions = new List<FileOptions>();


        private List<string> beforeBuild = new List<string>();

        private List<string> afterBuild = new List<string>();



        public List<string> BeforeBuild { get { return this.beforeBuild; } }
        public List<string> AfterBuild { get { return this.afterBuild; } }

        /// <summary>
        /// Name
        /// </summary>
        public string Name { get { return this.name; } set { this.name = value; } }        

        public int Num { get { return this.num; } set { this.num = value; } }

        /// <summary>
        /// Target settings
        /// </summary>
        public TargetOptions Options { get { return this.options; } }

        /// <summary>
        /// Files settings
        /// </summary>
        public List<FileOptions> FilesOpton { get { return this.filesoptions; } }

        public void ClearAll()
        {
            this.name = "";
            this.num = 0;
            this.options = new TargetOptions();
            this.filesoptions = new List<FileOptions>();
        }

        public void LoadOptions(string path)
        {
            this.options = TargetOptions.DesirializeXLM(path);
        }

        [DebuggerBrowsable(DebuggerBrowsableState.Never)]
        public string TargetString 
        {
            get
            {
                string res = "";

                res = "Target (" + this.Name + "), " + "0x" + ((int)this.options.ToolType).ToString("X4") + "// Tools: '";

                switch (this.options.ToolType)
                {
                    case TargetOptions.TOOL_TYPE.MCS_51:
                        res += "MCS-51'";
                        break;
                    case TargetOptions.TOOL_TYPE.ARM_ADS:
                        res += "ARM-ADS'";
                        break;
                    default:
                        break;
                }

                return res;
            }
        }


        public FileOptions FindFileOptions(string path)
        {
            foreach (FileOptions fo in this.FilesOpton)
            {
                if (String.Compare(fo.File.Path, path, StringComparison.InvariantCultureIgnoreCase) == 0) return fo;
            }
            return null;
        }

        [DebuggerBrowsable(DebuggerBrowsableState.Never)]
        public List<string> SolutionOptionsStrings 
        {
            get
            {
                List<string> result = new List<string>();
                string str = string.Empty;

                result.Add("Options " + this.num + ",0,0  // Target '" + this.Name + "'");
                result.Add(" Device (" + this.Options.Device + ")");
                result.Add(" Vendor (" + this.Options.Vendor + ")");
                result.Add(" Cpu (" + this.Options.Cpu + ")");
                result.Add(" FlashUt (" + this.Options.FlashUt + ")");
                result.Add(" StupF (" + this.Options.StupF + ")");
                result.Add(" FlashDR (" + this.Options.FlashDR + ")");
                result.Add(" DevID (" + this.Options.DevID + ")");
                result.Add(" Rgf (" + this.Options.Rgf + ")");
                result.Add(" Mem (" + this.Options.Mem + ")");
                result.Add(" C (" + this.Options.C + ")");
                result.Add(" A (" + this.Options.A + ")");
                result.Add(" RL (" + this.Options.RL + ")");
                result.Add(" OH (" + this.Options.OH + ")");
                result.Add(" DBC_IFX (" + this.Options.DBC_IFX + ")");
                result.Add(" DBC_CMS (" + this.Options.DBC_CMS + ")");
                result.Add(" DBC_AMS (" + this.Options.DBC_AMS + ")");
                result.Add(" DBC_LMS (" + this.Options.DBC_LMS + ")");
                result.Add(" UseEnv=" + this.Options.UseEnv);
                result.Add(" EnvBin (" + this.Options.EnvBin + ")");
                result.Add(" EnvInc (" + this.Options.EnvInc + ")");
                result.Add(" EnvLib (" + this.Options.EnvLib + ")");
                result.Add(" EnvReg (" + this.Options.EnvReg + ")");
                result.Add(" OrgReg (" + this.Options.OrgReg + ")");
                result.Add(" TgStat=" + this.Options.TgStat);
                result.Add(" OutDir (" + this.Options.OutDir + ")");
                result.Add(" OutName (" + this.Options.OutName + ")");
                result.Add(" GenApp=" + (int)this.Options.GenApp);
                result.Add(" GenLib=" + (int)this.Options.GenLib);
                result.Add(" GenHex=" + this.Options.GenHex);
                result.Add(" Debug=" + this.Options.Debug);
                result.Add(" Browse=" + this.Options.Browse);
                result.Add(" LstDir (" + this.Options.LstDir + ")");
                result.Add(" HexSel=" + this.Options.HexSel);
                result.Add(" MG32K=" + this.Options.MG32K);
                result.Add(" TGMORE=" + this.Options.TGMORE);
                result.Add(" RunUsr 0 " + (int)this.Options.RunUsr_0.Run + " <" + this.Options.RunUsr_0.Command + ">");
                result.Add(" RunUsr 1 " + (int)this.Options.RunUsr_1.Run + " <" + this.Options.RunUsr_1.Command + ">");
                result.Add(" BrunUsr 0 " + (int)this.Options.BrunUsr_0.Run + " <" + this.Options.BrunUsr_0.Command + ">");
                result.Add(" BrunUsr 1 " + (int)this.Options.BrunUsr_1.Run + " <" + this.Options.BrunUsr_1.Command + ">");
                result.Add(" CrunUsr 0 " + (int)this.Options.CrunUsr_0.Run + " <" + this.Options.CrunUsr_0.Command + ">");
                result.Add(" CrunUsr 1 " + (int)this.Options.CrunUsr_1.Run + " <" + this.Options.CrunUsr_1.Command + ">");
                result.Add(" SVCSID <" + this.Options.SVCSID + ">");
                result.Add(" GLFLAGS=" + this.Options.GLFLAGS);
                result.Add(" ADSFLGA { " + this.Options.ADSFLGA + " }");
                result.Add(" ACPUTYP (" + this.Options.ACPUTYP + ")");
                result.Add(" RVDEV (" + this.Options.RVDEV + ")");
                result.Add(" ADSTFLGA { " + this.Options.ADSTFLGA + " }");
                result.Add(" OCMADSOCM { " + this.Options.OCMADSOCM + " }");
                result.Add(" OCMADSIRAM { " + this.Options.OCMADSIRAM + " }");
                result.Add(" OCMADSIROM { " + this.Options.OCMADSIROM + " }");
                result.Add(" OCMADSXRAM { " + this.Options.OCMADSXRAM + " }");
                result.Add(" OCR_RVCT { " + this.Options.OCR_RVCT + " }");
                result.Add(" RV_STAVEC (" + this.Options.RV_STAVEC + ")");
                result.Add(" ADSCCFLG { " + this.Options.ADSCCFLG.ToString() + " }");
                str = " ADSCMISC (";
                if (this.Options.ADSCMISC.Count > 0)
                {
                    for (int i = 0; i < this.Options.ADSCMISC.Count - 1; i++)
                    {
                        str += this.Options.ADSCMISC[i] + " ";
                    }
                    str += this.Options.ADSCMISC[this.Options.ADSCMISC.Count - 1];
                }
                str += ")";
                result.Add(str);
                str = " ADSCDEFN (";
                if (this.Options.ADSCDEFN.Count > 0)
                {
                    for (int i = 0; i < this.Options.ADSCDEFN.Count - 1; i++)
                    {
                        str += this.Options.ADSCDEFN[i] + ", ";
                    }
                    str += this.Options.ADSCDEFN[this.Options.ADSCDEFN.Count - 1];
                }
                str += ")";
                result.Add(str);
                str = " ADSCUDEF (";
                if (this.Options.ADSCUDEF.Count > 0)
                {
                    for (int i = 0; i < this.Options.ADSCUDEF.Count - 1; i++)
                    {
                        str += this.Options.ADSCUDEF[i] + ", ";
                    }
                    str += this.Options.ADSCUDEF[this.Options.ADSCUDEF.Count - 1];
                }
                str += ")";
                result.Add(str);
                str = " ADSCINCD (";
                if (this.Options.ADSCINCD.Count > 0)
                {
                    for (int i = 0; i < this.Options.ADSCINCD.Count - 1; i++)
                    {
                        str += this.Options.ADSCINCD[i] + ";";
                    }
                    str += this.Options.ADSCINCD[this.Options.ADSCINCD.Count - 1];
                }
                str += ")";
                result.Add(str);
                result.Add(" ADSASFLG { " + this.Options.ADSASFLG + " }");
                //result.Add(" ADSAMISC ()
                str = " ADSAMISC (";
                if (this.Options.ADSAMISC.Count > 0)
                {
                    for (int i = 0; i < this.Options.ADSAMISC.Count - 1; i++)
                    {
                        str += this.Options.ADSAMISC[i] + " ";
                    }
                    str += this.Options.ADSAMISC[this.Options.ADSAMISC.Count - 1];
                }
                str += ")";
                result.Add(str);
                str = " ADSADEFN (";
                if (this.Options.ADSADEFN.Count > 0)
                {
                    for (int i = 0; i < this.Options.ADSADEFN.Count - 1; i++)
                    {
                        str += this.Options.ADSADEFN[i] + ", ";
                    }
                    str += this.Options.ADSADEFN[this.Options.ADSADEFN.Count - 1];
                }
                str += ")";
                result.Add(str);
                str = " ADSAUDEF (";
                if (this.Options.ADSAUDEF.Count > 0)
                {
                    for (int i = 0; i < this.Options.ADSAUDEF.Count - 1; i++)
                    {
                        str += this.Options.ADSAUDEF[i] + ", ";
                    }
                    str += this.Options.ADSAUDEF[this.Options.ADSAUDEF.Count - 1];
                }
                str += ")";
                result.Add(str);
                str = " ADSAINCD (";
                if (this.Options.ADSAINCD.Count > 0)
                {
                    for (int i = 0; i < this.Options.ADSAINCD.Count - 1; i++)
                    {
                        str += this.Options.ADSAINCD[i] + ";";
                    }
                    str += this.Options.ADSAINCD[this.Options.ADSAINCD.Count - 1];
                }
                str += ")";
                result.Add(str);
                result.Add(" PropFld { " + this.Options.PropFld + " }");
                result.Add(" IncBld=" + (int)this.Options.IncBld);
                result.Add(" AlwaysBuild=" + (int)this.Options.AlwaysBuild);
                result.Add(" GenAsm=" + (int)this.Options.GenAsm);
                result.Add(" AsmAsm=" + (int)this.Options.AsmAsm);
                result.Add(" PublicsOnly=" + (int)this.Options.PublicsOnly);
                result.Add(" StopCode=" + (int)this.Options.StopCode);
                str = " CustArgs (";
                if (this.Options.CustArgs.Count > 0)
                {
                    for (int i = 0; i < this.Options.CustArgs.Count - 1; i++)
                    {
                        str += this.Options.CustArgs[i] + " ";
                    }
                    str += this.Options.CustArgs[this.Options.CustArgs.Count - 1];
                }
                str += ")";
                result.Add(str);
                str = " LibMods (";
                if (this.Options.LibMods.Count > 0)
                {
                    for (int i = 0; i < this.Options.LibMods.Count - 1; i++)
                    {
                        str += this.Options.LibMods[i] + " ";
                    }
                    str += this.Options.LibMods[this.Options.LibMods.Count - 1];
                }
                str += ")";
                result.Add(str);
                result.Add(" ADSLDFG { " + this.Options.ADSLDFG + " }");
                result.Add(" ADSLDTA (" + this.Options.ADSLDTA + ")");
                result.Add(" ADSLDDA (" + this.Options.ADSLDDA + ")");
                result.Add(" ADSLDSC (" + this.Options.ADSLDSC + ")");
                result.Add(" ADSLDIB (" + this.Options.ADSLDIB + ")");
                result.Add(" ADSLDIC (" + this.Options.ADSLDIC + ")");
                //result.Add(" ADSLDMC (" + this.Options.ADSLDMC + ")");

                str = " ADSLDMC (";
                if (this.Options.ADSLDMC.Count > 0)
                {
                    for (int i = 0; i < this.Options.ADSLDMC.Count - 1; i++)
                    {
                        str += this.Options.ADSLDMC[i] + " ";
                    }
                    str += this.Options.ADSLDMC[this.Options.ADSLDMC.Count - 1];
                }
                str += ")";
                result.Add(str);

                result.Add(" ADSLDIF (" + this.Options.ADSLDIF + ")");
                result.Add(" ADSLDDW (" + this.Options.ADSLDDW + ")");
                result.Add("  OPTDL " + this.Options.OPTDL);
                result.Add("  OPTDBG " + this.Options.OPTDBG);
                result.Add(" FLASH1 { " + this.Options.FLASH1 + " }");
                result.Add(" FLASH2 (" + this.Options.FLASH2 + ")");
                result.Add(" FLASH3 (" + this.Options.FLASH3 + ")");
                result.Add(" FLASH4 (" + this.Options.FLASH4 + ")");
                result.Add("EndOpt");

                return result;
            }
        }
        
        [DebuggerBrowsable(DebuggerBrowsableState.Never)]
        public List<string> FilesOptionsStrings 
        {
            get
            {
                List<string> result = new List<string>();

                foreach (FileOptions fo in this.FilesOpton)
                {
                    result.AddRange(fo.GetFileOptionsStrings(this.num));
                    result.Add("");
                }
                return result;
            }
        }


        public void SeTLPC2478DefaultOptions()
        {
            this.Options.ToolType = TargetOptions.TOOL_TYPE.ARM_ADS;

            this.Options.Device = "LPC2478";
            this.Options.Vendor = "NXP (founded by Philips)";
            this.Options.Cpu = "IRAM(0x40000000-0x4000FFFF) IRAM2(0x7FE00000-0x7FE03FFF) IROM(0-0x7FFFF) CLOCK(12000000) CPUTYPE(ARM7TDMI)";
            this.Options.FlashUt = "LPC210x_ISP.EXE (\"#H\" ^X $D COM1: 38400 1)";
            this.Options.StupF = "\"STARTUP\\Philips\\LPC2400.s\" (\"Philips LPC2400 Startup Code\")";
            this.Options.FlashDR = "UL2ARM(-U268761108 -O7 -S0 -C0 -FO15 -FD40000000 -FC800 -FN1 -FF0LPC_IAP2_512 -FS00 -FL07E000)";
            this.Options.DevID = "4307";
            this.Options.Rgf = "LPC23xx.H";
            this.Options.Mem = "";
            this.Options.C = "";
            this.Options.A = "";
            this.Options.RL = "";
            this.Options.OH = "";
            this.Options.DBC_IFX = "";
            this.Options.DBC_CMS = "";
            this.Options.DBC_AMS = "";
            this.Options.DBC_LMS = "";
            this.Options.UseEnv = "0";
            this.Options.EnvBin = "";
            this.Options.EnvInc = "";
            this.Options.EnvLib = "";
            this.Options.EnvReg = "Philips\\";
            this.Options.OrgReg = "Philips\\";
            this.Options.TgStat = "16";
            this.Options.OutDir = ".\\";
            this.Options.OutName = "LPC2478";
            this.Options.GenApp = TWO_STATE_BOOL.ENABLED;
            this.Options.GenLib = TWO_STATE_BOOL.DISABLED;
            this.Options.GenHex = "0";
            this.Options.Debug = "1";
            this.Options.Browse = "1";
            this.Options.LstDir = ".\\";
            this.Options.HexSel = "1";
            this.Options.MG32K = "0";
            this.Options.TGMORE = "0";
            this.Options.RunUsr_0 = new RUN_USER_TYPE();
            this.Options.RunUsr_1 = new RUN_USER_TYPE();
            this.Options.BrunUsr_0 = new RUN_USER_TYPE();
            this.Options.BrunUsr_1 = new RUN_USER_TYPE();
            this.Options.CrunUsr_0 = new RUN_USER_TYPE();
            this.Options.CrunUsr_1 = new RUN_USER_TYPE();
            this.Options.SVCSID = "";
            this.Options.GLFLAGS = "1790";
            this.Options.ADSFLGA = "243,31,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0";
            this.Options.ACPUTYP = "ARM7TDMI";
            this.Options.RVDEV = "";
            this.Options.ADSTFLGA = "0,12,16,2,99,0,64,66,0,0,0,0,0,0,0,0,0,0,0,0";
            this.Options.OCMADSOCM = "0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0";
            this.Options.OCMADSIRAM = "0,0,0,0,64,0,0,1,0";
            this.Options.OCMADSIROM = "1,0,0,0,0,0,0,8,0";
            this.Options.OCMADSXRAM = "0,0,0,0,0,0,0,0,0";
            this.Options.OCR_RVCT = "0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,64,0,0,1,0,0,0,0,224,127,0,64,0,0";
            this.Options.RV_STAVEC = "";
            //this.Options.ADSCCFLG = "5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0";
            this.Options.ADSCCFLG.ARM_Thumb_Interworking = THREE_STATE_BOOL.ENABLED;
            this.Options.ADSCCFLG.Optimisation = OPTIMIZATION.Level0;
            this.Options.ADSCCFLG.Optimize_for_time = THREE_STATE_BOOL.DISABLED;
            this.Options.ADSCCFLG.Split_Load_and_Store_Multiple = THREE_STATE_BOOL.DISABLED;
            this.Options.ADSCCFLG.One_EFL_Section_per_Function = THREE_STATE_BOOL.DISABLED;
            this.Options.ADSCCFLG.Strict_ANSI_C = THREE_STATE_BOOL.DISABLED;
            this.Options.ADSCCFLG.Enum_Container_always_int = THREE_STATE_BOOL.DISABLED;
            this.Options.ADSCCFLG.Plain_Char_is_Signed = THREE_STATE_BOOL.DISABLED;
            this.Options.ADSCCFLG.ReadOnly_Position_Independent = THREE_STATE_BOOL.DISABLED;
            this.Options.ADSCCFLG.ReadWrite_Position_Independent = THREE_STATE_BOOL.DISABLED;
            this.Options.ADSCCFLG.Warnings = WARNINGS.Unspecified;
            this.Options.ADSCCFLG.Thumb_Mode = THREE_STATE_BOOL.DISABLED;
            //this.Options.ADSCMISC { get { return _ADSCMISC; }}
            //this.Options.ADSCDEFN { get { return _ADSCDEFN; }}
            //this.Options.ADSCUDEF { get { return _ADSCUDEF; }}
            //this.Options.ADSCINCD { get { return _ADSCINCD; }}
            this.Options.ADSASFLG = "1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0";
            //this.Options.ADSAMISC { get { return _ADSAMISC; }}
            //this.Options.ADSADEFN { get { return _ADSADEFN; }}
            //this.Options.ADSAUDEF { get { return _ADSAUDEF; }}
            //this.Options.ADSAINCD { get { return _ADSAINCD; }}
            this.Options.PropFld = "0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0";
            this.Options.IncBld = THREE_STATE_BOOL.ENABLED;
            this.Options.AlwaysBuild = THREE_STATE_BOOL.DISABLED;
            this.Options.GenAsm = THREE_STATE_BOOL.DISABLED;
            this.Options.AsmAsm = THREE_STATE_BOOL.DISABLED;
            this.Options.PublicsOnly = THREE_STATE_BOOL.DISABLED;
            this.Options.StopCode = STOP_CODE.ExitCode_GE_3;
            //this.Options.CustArgs { get { return _CustArgs; } }
            //this.Options.LibMods { get { return _LibMods; } }        
            this.Options.ADSLDFG = "17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0";
            this.Options.ADSLDTA = "0x00000000";
            this.Options.ADSLDDA = "0x40000000";
            this.Options.ADSLDSC = "";
            this.Options.ADSLDIB = "";
            this.Options.ADSLDIC = "";
            this.Options.ADSLDMC = new List<string>();
            this.Options.ADSLDIF = "";
            this.Options.ADSLDDW = "";
            this.Options.OPTDL = "(SARM.DLL)(-cLPC24xx)(DARMP.DLL)(-pLPC2478)(SARM.DLL)()(TARMP.DLL)(-pLPC2478)";
            this.Options.OPTDBG = "48125,-1,()()()()()()()()()() ()()()()";
            this.Options.FLASH1 = "2,0,0,0,0,0,0,0,255,255,255,255,0,0,0,0,0,0,0,0";
            this.Options.FLASH2 = "";
            this.Options.FLASH3 = "LPC210x_ISP.EXE (\"#H\" ^X $D COM1: 38400 1)";
            this.Options.FLASH4 = "";
        }

        public void Set_AT91SAM7S16_DefaultOptions()
        {
            this.Options.ToolType = TargetOptions.TOOL_TYPE.ARM_ADS;
            this.Options.Device = "AT91SAM7S16";
            this.Options.Vendor = "Atmel";
            this.Options.Cpu = "IRAM(0x200000-0x200FFF) IROM(0x100000-0x107FFF) CLOCK(20000000) CPUTYPE(ARM7TDMI)";
            this.Options.FlashUt = "";
            this.Options.StupF = "\"STARTUP\\Atmel\\SAM7.s\" (\"Atmel AT91SAM7 Startup Code\")";
            this.Options.FlashDR = "UL2ARM(-U56240812 -O15 -S0 -C0 -D00(3F0F0F0F) -L00(4) -FO6 -FD200000 -FC800 -FN1 -FF0AT91SAM7_16 -FS0100000 -FL04000)";
            this.Options.DevID = "4612";
            this.Options.Rgf = "AT91SAM7S32.H";
            this.Options.Mem = "";
            this.Options.C = "";
            this.Options.A = "";
            this.Options.RL = "";
            this.Options.OH = "";
            this.Options.DBC_IFX = "";
            this.Options.DBC_CMS = "";
            this.Options.DBC_AMS = "";
            this.Options.DBC_LMS = "";
            this.Options.UseEnv = "0";
            this.Options.EnvBin = "";
            this.Options.EnvInc = "";
            this.Options.EnvLib = "";
            this.Options.EnvReg = "Atmel\\SAM7S\\";
            this.Options.OrgReg = "Atmel\\SAM7S\\";
            this.Options.TgStat = "16";
            this.Options.OutDir = ".\\";
            this.Options.OutName = "AT91SAM7X";
            this.Options.GenApp = TWO_STATE_BOOL.ENABLED;
            this.Options.GenLib = TWO_STATE_BOOL.DISABLED;
            this.Options.GenHex = "0";
            this.Options.Debug = "1";
            this.Options.Browse = "1";
            this.Options.LstDir = @".\";
            this.Options.HexSel = "1";
            this.Options.MG32K = "0";
            this.Options.TGMORE = "0";
            this.Options.RunUsr_0 = new RUN_USER_TYPE();
            this.Options.RunUsr_1 = new RUN_USER_TYPE();
            this.Options.BrunUsr_0 = new RUN_USER_TYPE();
            this.Options.BrunUsr_1 = new RUN_USER_TYPE();
            this.Options.CrunUsr_0 = new RUN_USER_TYPE();
            this.Options.CrunUsr_1 = new RUN_USER_TYPE();
            this.Options.SVCSID = "";
            this.Options.GLFLAGS = "1790";
            this.Options.ADSFLGA = "243,31,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0";
            this.Options.ACPUTYP = "ARM7TDMI";
            this.Options.RVDEV = "";
            this.Options.ADSTFLGA = "0,12,0,2,99,0,64,66,0,0,0,0,0,0,0,0,0,0,0,0";
            this.Options.OCMADSOCM = "0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0";
            this.Options.OCMADSIRAM = "0,0,0,32,0,0,16,0,0";
            this.Options.OCMADSIROM = "1,0,0,16,0,0,128,0,0";
            this.Options.OCMADSXRAM = "0,0,0,0,0,0,0,0,0";
            this.Options.OCR_RVCT = "0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,16,0,0,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,32,0,0,16,0,0,0,0,0,0,0,0,0,0,0";
            this.Options.RV_STAVEC = "";
            //this.Options.ADSCCFLG = "5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0";
            this.Options.ADSCCFLG.ARM_Thumb_Interworking = THREE_STATE_BOOL.ENABLED;
            this.Options.ADSCCFLG.Optimisation = OPTIMIZATION.Level0;
            this.Options.ADSCCFLG.Optimize_for_time = THREE_STATE_BOOL.DISABLED;
            this.Options.ADSCCFLG.Split_Load_and_Store_Multiple = THREE_STATE_BOOL.DISABLED;
            this.Options.ADSCCFLG.One_EFL_Section_per_Function = THREE_STATE_BOOL.DISABLED;
            this.Options.ADSCCFLG.Strict_ANSI_C = THREE_STATE_BOOL.DISABLED;
            this.Options.ADSCCFLG.Enum_Container_always_int = THREE_STATE_BOOL.DISABLED;
            this.Options.ADSCCFLG.Plain_Char_is_Signed = THREE_STATE_BOOL.DISABLED;
            this.Options.ADSCCFLG.ReadOnly_Position_Independent = THREE_STATE_BOOL.DISABLED;
            this.Options.ADSCCFLG.ReadWrite_Position_Independent = THREE_STATE_BOOL.DISABLED;
            this.Options.ADSCCFLG.Warnings = WARNINGS.Unspecified;
            this.Options.ADSCCFLG.Thumb_Mode = THREE_STATE_BOOL.DISABLED;
            //this.Options.ADSCMISC = "";
            //this.Options.ADSCDEFN = "";
            //this.Options.ADSCUDEF = "";
            //this.Options.ADSCINCD = "";
            this.Options.ADSASFLG = "1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0";
            //this.Options.ADSAMISC = "";
            //this.Options.ADSADEFN = "";
            //this.Options.ADSAUDEF = "";
            //this.Options.ADSAINCD = "";
            this.Options.PropFld = "0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0";
            this.Options.IncBld = THREE_STATE_BOOL.ENABLED;
            this.Options.AlwaysBuild = THREE_STATE_BOOL.DISABLED;
            this.Options.GenAsm = THREE_STATE_BOOL.DISABLED;
            this.Options.AsmAsm = THREE_STATE_BOOL.DISABLED;
            this.Options.PublicsOnly = THREE_STATE_BOOL.DISABLED;
            this.Options.StopCode = STOP_CODE.ExitCode_GE_3;
            //this.Options.CustArgs = "";
            //this.Options.LibMods = "";
            this.Options.ADSLDFG = "17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0";
            this.Options.ADSLDTA = "0x00100000";
            this.Options.ADSLDDA = "0x00200000";
            this.Options.ADSLDSC = "";
            this.Options.ADSLDIB = "";
            this.Options.ADSLDIC = "";
            //this.Options.ADSLDMC = "";
            this.Options.ADSLDIF = "";
            this.Options.ADSLDDW = "";
            this.Options.OPTDL = "(SARM.DLL)(-cAT91SAM7S)(DARMATS.DLL)(-p91SAM7S16)(SARM.DLL)()(TARMATS.DLL)(-p91SAM7S16)";
            this.Options.OPTDBG = "48125,0,()()()()()()()()()() ()()()()";
            this.Options.FLASH1 = " 9,0,0,0,0,0,0,0,255,255,255,255,0,0,0,0,0,0,0,0";
            this.Options.FLASH2 = "BIN\\UL2ARM.DLL";
            this.Options.FLASH3 = "";
            this.Options.FLASH4 = "";
        }


    }
}
