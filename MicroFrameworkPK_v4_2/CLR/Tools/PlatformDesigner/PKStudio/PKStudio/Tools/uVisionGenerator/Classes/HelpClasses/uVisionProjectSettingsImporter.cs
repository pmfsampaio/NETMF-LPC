using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using PKStudio.Tools.uVisionGenerator.Classes.uvProjectClasses;
using System.IO;
using System.Text.RegularExpressions;
using PKStudio.Tools.uVisionGenerator.Wizard;

namespace PKStudio.Tools.uVisionGenerator.Classes.HelpClasses
{
    class uVisionProjectSettingsImporter
    {
        public static TargetOptions ImportUV3Project(string path)
        {
            TargetOptions result = new TargetOptions();

            using (StreamReader tr = new StreamReader(path))
            {
                try
                {


                    string s = string.Empty;
                    Regex r = null;
                    Regex RType1 = new Regex(@"\A\s*(?<name>[^(\s]*?)\s*\((?<value>.*)\)", RegexOptions.IgnoreCase | RegexOptions.Singleline); //%name% (%value%)
                    Regex RType2 = new Regex(@"\A\s*(?<name>[^\s=]*)\s*=\s*(?<value>[0-9]*)", RegexOptions.IgnoreCase | RegexOptions.Singleline); //%name%=%value%
                    Regex RType3 = new Regex(@"\A\s*(?<name>RunUsr|BrunUsr|CrunUsr)\s(?<seq>0|1)\s(?<enable>0|1)\s<(?<value>.*)>", RegexOptions.IgnoreCase | RegexOptions.Singleline); //%name% %seq% %enable% <%value%>
                    Regex RType4 = new Regex(@"\A\s*(?<name>[^<\s]*?)\s*<(?<value>.*)>", RegexOptions.IgnoreCase | RegexOptions.Singleline); //%name% <%value%>
                    Regex RType5 = new Regex(@"\A\s(?<name>[^{]*)\s{(?<values>\s*(?:[0-9]+,?\s*)+)+}", RegexOptions.IgnoreCase | RegexOptions.Singleline); //%name% { %values% }
                    Regex RType6 = new Regex(@"\A\s*(?<name>[^\s]+)\s*(?<value>.*?)\s*\z", RegexOptions.IgnoreCase | RegexOptions.Singleline); //%name% %value%


                    Match m = null;

                    #region header

                    s = tr.ReadLine(); //### uVision2 Project, (C) Keil Software
                    r = new Regex("(### uVision2 Project)", RegexOptions.IgnoreCase | RegexOptions.Singleline);
                    m = r.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    s = tr.ReadLine(); //### Do not modify !
                    s = tr.ReadLine(); //empty string

                    #endregion

                    #region ToolType

                    s = tr.ReadLine(); //Target (Target 1), 0x0004 // Tools: 'ARM-ADS'
                    r = new Regex("(Target).*?\\d+.*?\\d+.*?(\\d+)", RegexOptions.IgnoreCase | RegexOptions.Singleline);
                    m = r.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    switch ((TargetOptions.TOOL_TYPE)int.Parse(m.Groups[2].ToString()))
                    {
                        case TargetOptions.TOOL_TYPE.ARM_ADS:
                            result.ToolType = TargetOptions.TOOL_TYPE.ARM_ADS;
                            break;
                        case TargetOptions.TOOL_TYPE.NONE:
                        case TargetOptions.TOOL_TYPE.MCS_51:
                        default:
                            throw new Exception(KeilWizardStrings.IDS_NOT_SUPPORTED_TOOL);
                    }

                    #endregion

                    #region Device

                    s = tr.ReadLine();
                    while (!s.Contains("Options 1,0,0"))
                    {
                        s = tr.ReadLine();
                    }

                    s = tr.ReadLine();
                    m = RType1.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    if (m.Groups["name"].ToString() == "Device") result.Device = m.Groups["value"].ToString();
                    else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    #region Vendor

                    s = tr.ReadLine();
                    m = RType1.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    if (m.Groups["name"].ToString() == "Vendor") result.Vendor = m.Groups["value"].ToString();
                    else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    #region Cpu

                    s = tr.ReadLine();
                    m = RType1.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    if (m.Groups["name"].ToString() == "Cpu") result.Cpu = m.Groups["value"].ToString();
                    else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    #region FlashUt

                    s = tr.ReadLine();
                    m = RType1.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    if (m.Groups["name"].ToString() == "FlashUt") result.FlashUt = m.Groups["value"].ToString();
                    else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    #region StupF

                    s = tr.ReadLine();
                    m = RType1.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    if (m.Groups["name"].ToString() == "StupF") result.StupF = m.Groups["value"].ToString();
                    else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    #region FlashDR

                    s = tr.ReadLine();
                    m = RType1.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    if (m.Groups["name"].ToString() == "FlashDR") result.FlashDR = m.Groups["value"].ToString();
                    else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    #region DevID

                    s = tr.ReadLine();
                    m = RType1.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    if (m.Groups["name"].ToString() == "DevID") result.DevID = m.Groups["value"].ToString();
                    else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    #region Rgf

                    s = tr.ReadLine();
                    m = RType1.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    if (m.Groups["name"].ToString() == "Rgf") result.Rgf = m.Groups["value"].ToString();
                    else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    #region Mem

                    s = tr.ReadLine();
                    m = RType1.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    if (m.Groups["name"].ToString() == "Mem") result.Mem = m.Groups["value"].ToString();
                    else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    #region C

                    s = tr.ReadLine();
                    m = RType1.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    if (m.Groups["name"].ToString() == "C") result.C = m.Groups["value"].ToString();
                    else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    #region A

                    s = tr.ReadLine();
                    m = RType1.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    if (m.Groups["name"].ToString() == "A") result.A = m.Groups["value"].ToString();
                    else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    #region RL

                    s = tr.ReadLine();
                    m = RType1.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    if (m.Groups["name"].ToString() == "RL") result.RL = m.Groups["value"].ToString();
                    else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    #region OH

                    s = tr.ReadLine();
                    m = RType1.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    if (m.Groups["name"].ToString() == "OH") result.OH = m.Groups["value"].ToString();
                    else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    #region DBC_IFX

                    s = tr.ReadLine();
                    m = RType1.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    if (m.Groups["name"].ToString() == "DBC_IFX") result.DBC_IFX = m.Groups["value"].ToString();
                    else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    #region DBC_CMS

                    s = tr.ReadLine();
                    m = RType1.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    if (m.Groups["name"].ToString() == "DBC_CMS") result.DBC_CMS = m.Groups["value"].ToString();
                    else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    #region DBC_AMS

                    s = tr.ReadLine();
                    m = RType1.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    if (m.Groups["name"].ToString() == "DBC_AMS") result.DBC_AMS = m.Groups["value"].ToString();
                    else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    #region DBC_LMS

                    s = tr.ReadLine();
                    m = RType1.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    if (m.Groups["name"].ToString() == "DBC_LMS") result.DBC_LMS = m.Groups["value"].ToString();
                    else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    #region UseEnv

                    s = tr.ReadLine();
                    m = RType2.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    if (m.Groups["name"].ToString() == "UseEnv") result.UseEnv = m.Groups["value"].ToString();
                    else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    #region EnvBin

                    s = tr.ReadLine();
                    m = RType1.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    if (m.Groups["name"].ToString() == "EnvBin") result.EnvBin = m.Groups["value"].ToString();
                    else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    #region EnvInc

                    s = tr.ReadLine();
                    m = RType1.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    if (m.Groups["name"].ToString() == "EnvInc") result.EnvInc = m.Groups["value"].ToString();
                    else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    #region EnvLib

                    s = tr.ReadLine();
                    m = RType1.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    if (m.Groups["name"].ToString() == "EnvLib") result.EnvLib = m.Groups["value"].ToString();
                    else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    #region EnvReg

                    s = tr.ReadLine();
                    m = RType1.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    if (m.Groups["name"].ToString() == "EnvReg") result.EnvReg = m.Groups["value"].ToString();
                    else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    #region OrgReg

                    s = tr.ReadLine();
                    m = RType1.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    if (m.Groups["name"].ToString() == "OrgReg") result.OrgReg = m.Groups["value"].ToString();
                    else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    #region TgStat

                    s = tr.ReadLine();
                    m = RType2.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    if (m.Groups["name"].ToString() == "TgStat") result.TgStat = m.Groups["value"].ToString();
                    else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    #region OutDir

                    s = tr.ReadLine();
                    //Use defaults
                    result.OutDir = @".\";
                    //m = RType1.Match(s);
                    //if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    //if (m.Groups["name"].ToString() == "OutDir") result.OutDir = m.Groups["value"].ToString();
                    //else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    #region OutName

                    s = tr.ReadLine();
                    //Use defaults
                    result.OutName = result.Device;

                    //m = RType1.Match(s);
                    //if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    //if (m.Groups["name"].ToString() == "OutName") result.OutName = m.Groups["value"].ToString();
                    //else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    #region GenApp

                    s = tr.ReadLine();
                    m = RType2.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    if (m.Groups["name"].ToString() == "GenApp")
                    {
                        switch ((TWO_STATE_BOOL)int.Parse(m.Groups["value"].ToString()))
                        {
                            case TWO_STATE_BOOL.DISABLED:
                                result.GenApp = TWO_STATE_BOOL.DISABLED;
                                break;
                            case TWO_STATE_BOOL.ENABLED:
                                result.GenApp = TWO_STATE_BOOL.ENABLED;
                                break;
                            default:
                                throw new Exception(KeilWizardStrings.IDS_NOT_SUPPORTED_TOOL);
                        }
                    }
                    else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    #region GenLib

                    s = tr.ReadLine();
                    m = RType2.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    if (m.Groups["name"].ToString() == "GenLib")
                    {
                        switch ((TWO_STATE_BOOL)int.Parse(m.Groups["value"].ToString()))
                        {
                            case TWO_STATE_BOOL.DISABLED:
                                result.GenLib = TWO_STATE_BOOL.DISABLED;
                                break;
                            case TWO_STATE_BOOL.ENABLED:
                                result.GenLib = TWO_STATE_BOOL.ENABLED;
                                break;
                            default:
                                throw new Exception(KeilWizardStrings.IDS_NOT_SUPPORTED_TOOL);
                        }
                    }
                    else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    #region GenHex

                    s = tr.ReadLine();
                    m = RType2.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    if (m.Groups["name"].ToString() == "GenHex") result.GenHex = m.Groups["value"].ToString();
                    else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    #region Debug

                    s = tr.ReadLine();
                    m = RType2.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    if (m.Groups["name"].ToString() == "Debug") result.Debug = m.Groups["value"].ToString();
                    else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    #region Browse

                    s = tr.ReadLine();
                    m = RType2.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    if (m.Groups["name"].ToString() == "Browse") result.Browse = m.Groups["value"].ToString();
                    else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    #region LstDir

                    s = tr.ReadLine();
                    m = RType1.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    if (m.Groups["name"].ToString() == "LstDir") result.LstDir = m.Groups["value"].ToString();
                    else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    #region HexSel

                    s = tr.ReadLine();
                    m = RType2.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    if (m.Groups["name"].ToString() == "HexSel") result.HexSel = m.Groups["value"].ToString();
                    else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    #region MG32K

                    s = tr.ReadLine();
                    m = RType2.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    if (m.Groups["name"].ToString() == "MG32K") result.MG32K = m.Groups["value"].ToString();
                    else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    #region TGMORE

                    s = tr.ReadLine();
                    m = RType2.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    if (m.Groups["name"].ToString() == "TGMORE") result.TGMORE = m.Groups["value"].ToString();
                    else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    #region RunUsr_0

                    s = tr.ReadLine();
                    m = RType3.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    if ((m.Groups["name"].ToString() == "RunUsr") && (m.Groups["seq"].ToString() == "0"))
                    {
                        result.RunUsr_0 = new RUN_USER_TYPE();

                        switch ((TWO_STATE_BOOL)int.Parse(m.Groups["enable"].ToString()))
                        {
                            case TWO_STATE_BOOL.DISABLED:
                                result.RunUsr_0.Run = TWO_STATE_BOOL.DISABLED;
                                break;
                            case TWO_STATE_BOOL.ENABLED:
                                result.RunUsr_0.Run = TWO_STATE_BOOL.ENABLED;
                                break;
                            default:
                                throw new Exception(KeilWizardStrings.IDS_NOT_SUPPORTED_TOOL);
                        }

                        result.RunUsr_0.Command = m.Groups["value"].ToString();
                    }
                    else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    #region RunUsr_1

                    s = tr.ReadLine();
                    m = RType3.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    if ((m.Groups["name"].ToString() == "RunUsr") && (m.Groups["seq"].ToString() == "1"))
                    {
                        result.RunUsr_1 = new RUN_USER_TYPE();

                        switch ((TWO_STATE_BOOL)int.Parse(m.Groups["enable"].ToString()))
                        {
                            case TWO_STATE_BOOL.DISABLED:
                                result.RunUsr_1.Run = TWO_STATE_BOOL.DISABLED;
                                break;
                            case TWO_STATE_BOOL.ENABLED:
                                result.RunUsr_1.Run = TWO_STATE_BOOL.ENABLED;
                                break;
                            default:
                                throw new Exception(KeilWizardStrings.IDS_NOT_SUPPORTED_TOOL);
                        }

                        result.RunUsr_1.Command = m.Groups["value"].ToString();
                    }
                    else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    #region BrunUsr_0

                    s = tr.ReadLine();
                    m = RType3.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    if ((m.Groups["name"].ToString() == "BrunUsr") && (m.Groups["seq"].ToString() == "0"))
                    {
                        result.BrunUsr_0 = new RUN_USER_TYPE();

                        switch ((TWO_STATE_BOOL)int.Parse(m.Groups["enable"].ToString()))
                        {
                            case TWO_STATE_BOOL.DISABLED:
                                result.BrunUsr_0.Run = TWO_STATE_BOOL.DISABLED;
                                break;
                            case TWO_STATE_BOOL.ENABLED:
                                result.BrunUsr_0.Run = TWO_STATE_BOOL.ENABLED;
                                break;
                            default:                                
                                throw new Exception(KeilWizardStrings.IDS_NOT_SUPPORTED_TOOL);
                        }

                        result.BrunUsr_0.Command = m.Groups["value"].ToString();
                    }
                    else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    #region BrunUsr_1

                    s = tr.ReadLine();
                    m = RType3.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    if ((m.Groups["name"].ToString() == "BrunUsr") && (m.Groups["seq"].ToString() == "1"))
                    {
                        result.BrunUsr_1 = new RUN_USER_TYPE();

                        switch ((TWO_STATE_BOOL)int.Parse(m.Groups["enable"].ToString()))
                        {
                            case TWO_STATE_BOOL.DISABLED:
                                result.BrunUsr_1.Run = TWO_STATE_BOOL.DISABLED;
                                break;
                            case TWO_STATE_BOOL.ENABLED:
                                result.BrunUsr_1.Run = TWO_STATE_BOOL.ENABLED;
                                break;
                            default:                                
                                throw new Exception(KeilWizardStrings.IDS_NOT_SUPPORTED_TOOL);
                        }

                        result.BrunUsr_1.Command = m.Groups["value"].ToString();
                    }
                    else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    #region CrunUsr_0

                    s = tr.ReadLine();
                    m = RType3.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    if ((m.Groups["name"].ToString() == "CrunUsr") && (m.Groups["seq"].ToString() == "0"))
                    {
                        result.CrunUsr_0 = new RUN_USER_TYPE();

                        switch ((TWO_STATE_BOOL)int.Parse(m.Groups["enable"].ToString()))
                        {
                            case TWO_STATE_BOOL.DISABLED:
                                result.CrunUsr_0.Run = TWO_STATE_BOOL.DISABLED;
                                break;
                            case TWO_STATE_BOOL.ENABLED:
                                result.CrunUsr_0.Run = TWO_STATE_BOOL.ENABLED;
                                break;
                            default:                                
                                throw new Exception(KeilWizardStrings.IDS_NOT_SUPPORTED_TOOL);
                        }

                        result.CrunUsr_0.Command = m.Groups["value"].ToString();
                    }
                    else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    #region CrunUsr_1

                    s = tr.ReadLine();
                    m = RType3.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    if ((m.Groups["name"].ToString() == "CrunUsr") && (m.Groups["seq"].ToString() == "1"))
                    {
                        result.CrunUsr_1 = new RUN_USER_TYPE();

                        switch ((TWO_STATE_BOOL)int.Parse(m.Groups["enable"].ToString()))
                        {
                            case TWO_STATE_BOOL.DISABLED:
                                result.CrunUsr_1.Run = TWO_STATE_BOOL.DISABLED;
                                break;
                            case TWO_STATE_BOOL.ENABLED:
                                result.CrunUsr_1.Run = TWO_STATE_BOOL.ENABLED;
                                break;
                            default:                                
                                throw new Exception(KeilWizardStrings.IDS_NOT_SUPPORTED_TOOL);
                        }

                        result.CrunUsr_1.Command = m.Groups["value"].ToString();
                    }
                    else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    #region SVCSID

                    s = tr.ReadLine();
                    m = RType4.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    if (m.Groups["name"].ToString() == "SVCSID") result.SVCSID = m.Groups["value"].ToString();
                    else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    #region GLFLAGS

                    s = tr.ReadLine();
                    m = RType2.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    if (m.Groups["name"].ToString() == "GLFLAGS") result.GLFLAGS = m.Groups["value"].ToString();
                    else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    #region ADSFLGA

                    s = tr.ReadLine();
                    m = RType5.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    if (m.Groups["name"].ToString() == "ADSFLGA") result.ADSFLGA = m.Groups["values"].ToString().Trim();
                    else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    #region ACPUTYP

                    s = tr.ReadLine();
                    m = RType1.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    if (m.Groups["name"].ToString() == "ACPUTYP") result.ACPUTYP = m.Groups["value"].ToString();
                    else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    #region RVDEV

                    s = tr.ReadLine();
                    m = RType1.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    if (m.Groups["name"].ToString() == "RVDEV") result.RVDEV = m.Groups["value"].ToString();
                    else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    #region ADSTFLGA

                    s = tr.ReadLine();
                    m = RType5.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    if (m.Groups["name"].ToString() == "ADSTFLGA") result.ADSTFLGA = m.Groups["values"].ToString().Trim();
                    else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    #region OCMADSOCM

                    s = tr.ReadLine();
                    m = RType5.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    if (m.Groups["name"].ToString() == "OCMADSOCM") result.OCMADSOCM = m.Groups["values"].ToString().Trim();
                    else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    #region OCMADSIRAM

                    s = tr.ReadLine();
                    m = RType5.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    if (m.Groups["name"].ToString() == "OCMADSIRAM") result.OCMADSIRAM = m.Groups["values"].ToString().Trim();
                    else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    #region OCMADSIROM

                    s = tr.ReadLine();
                    m = RType5.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    if (m.Groups["name"].ToString() == "OCMADSIROM") result.OCMADSIROM = m.Groups["values"].ToString().Trim();
                    else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    #region OCMADSXRAM

                    s = tr.ReadLine();
                    m = RType5.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    if (m.Groups["name"].ToString() == "OCMADSXRAM") result.OCMADSXRAM = m.Groups["values"].ToString().Trim();
                    else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    #region OCR_RVCT

                    s = tr.ReadLine();
                    m = RType5.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    if (m.Groups["name"].ToString() == "OCR_RVCT") result.OCR_RVCT = m.Groups["values"].ToString().Trim();
                    else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    #region RV_STAVEC

                    s = tr.ReadLine();
                    m = RType1.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    if (m.Groups["name"].ToString() == "RV_STAVEC") result.RV_STAVEC = m.Groups["value"].ToString();
                    else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    #region ADSCCFLG

                    s = tr.ReadLine();
                    m = RType5.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    if (m.Groups["name"].ToString() == "ADSCCFLG")
                    {
                        result.ADSCCFLG = new ADSCCFLG_TYPE(m.Groups["values"].ToString());
                    }
                    else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    s = tr.ReadLine(); //ADSCMISC 
                    s = tr.ReadLine(); //ADSCDEFN 
                    s = tr.ReadLine(); //ADSCUDEF 
                    s = tr.ReadLine(); //ADSCINCD 

                    #region ADSASFLG

                    s = tr.ReadLine();
                    m = RType5.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    if (m.Groups["name"].ToString() == "ADSASFLG")
                    {
                        result.ADSASFLG = m.Groups["values"].ToString().Trim();
                    }
                    else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    s = tr.ReadLine(); //ADSAMISC 
                    s = tr.ReadLine(); //ADSADEFN 
                    s = tr.ReadLine(); //ADSAUDEF 
                    s = tr.ReadLine(); //ADSAINCD 

                    #region PropFld

                    s = tr.ReadLine();
                    m = RType5.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    if (m.Groups["name"].ToString() == "PropFld")
                    {
                        result.PropFld = m.Groups["values"].ToString().Trim();
                    }
                    else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    #region IncBld

                    s = tr.ReadLine();
                    m = RType2.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    if (m.Groups["name"].ToString() == "IncBld")
                    {
                        switch ((THREE_STATE_BOOL)int.Parse(m.Groups["value"].ToString()))
                        {
                            case THREE_STATE_BOOL.DISABLED:
                                result.IncBld = THREE_STATE_BOOL.DISABLED;
                                break;
                            case THREE_STATE_BOOL.ENABLED:
                                result.IncBld = THREE_STATE_BOOL.ENABLED;
                                break;
                            case THREE_STATE_BOOL.DEFAULT:
                                result.IncBld = THREE_STATE_BOOL.DEFAULT;
                                break;
                            default:                                
                                throw new Exception(KeilWizardStrings.IDS_NOT_SUPPORTED_TOOL);
                        }
                    }
                    else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    #region AlwaysBuild

                    s = tr.ReadLine();
                    m = RType2.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    if (m.Groups["name"].ToString() == "AlwaysBuild")
                    {
                        switch ((THREE_STATE_BOOL)int.Parse(m.Groups["value"].ToString()))
                        {
                            case THREE_STATE_BOOL.DISABLED:
                                result.AlwaysBuild = THREE_STATE_BOOL.DISABLED;
                                break;
                            case THREE_STATE_BOOL.ENABLED:
                                result.AlwaysBuild = THREE_STATE_BOOL.ENABLED;
                                break;
                            case THREE_STATE_BOOL.DEFAULT:
                                result.AlwaysBuild = THREE_STATE_BOOL.DEFAULT;
                                break;
                            default:                                
                                throw new Exception(KeilWizardStrings.IDS_NOT_SUPPORTED_TOOL);
                        }
                    }
                    else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    #region GenAsm

                    s = tr.ReadLine();
                    m = RType2.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    if (m.Groups["name"].ToString() == "GenAsm")
                    {
                        switch ((THREE_STATE_BOOL)int.Parse(m.Groups["value"].ToString()))
                        {
                            case THREE_STATE_BOOL.DISABLED:
                                result.GenAsm = THREE_STATE_BOOL.DISABLED;
                                break;
                            case THREE_STATE_BOOL.ENABLED:
                                result.GenAsm = THREE_STATE_BOOL.ENABLED;
                                break;
                            case THREE_STATE_BOOL.DEFAULT:
                                result.GenAsm = THREE_STATE_BOOL.DEFAULT;
                                break;
                            default:                                
                                throw new Exception(KeilWizardStrings.IDS_NOT_SUPPORTED_TOOL);
                        }
                    }
                    else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    #region AsmAsm

                    s = tr.ReadLine();
                    m = RType2.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    if (m.Groups["name"].ToString() == "AsmAsm")
                    {
                        switch ((THREE_STATE_BOOL)int.Parse(m.Groups["value"].ToString()))
                        {
                            case THREE_STATE_BOOL.DISABLED:
                                result.AsmAsm = THREE_STATE_BOOL.DISABLED;
                                break;
                            case THREE_STATE_BOOL.ENABLED:
                                result.AsmAsm = THREE_STATE_BOOL.ENABLED;
                                break;
                            case THREE_STATE_BOOL.DEFAULT:
                                result.AsmAsm = THREE_STATE_BOOL.DEFAULT;
                                break;
                            default:                                
                                throw new Exception(KeilWizardStrings.IDS_NOT_SUPPORTED_TOOL);
                        }
                    }
                    else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    #region PublicsOnly

                    s = tr.ReadLine();
                    m = RType2.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    if (m.Groups["name"].ToString() == "PublicsOnly")
                    {
                        switch ((THREE_STATE_BOOL)int.Parse(m.Groups["value"].ToString()))
                        {
                            case THREE_STATE_BOOL.DISABLED:
                                result.PublicsOnly = THREE_STATE_BOOL.DISABLED;
                                break;
                            case THREE_STATE_BOOL.ENABLED:
                                result.PublicsOnly = THREE_STATE_BOOL.ENABLED;
                                break;
                            case THREE_STATE_BOOL.DEFAULT:
                                result.PublicsOnly = THREE_STATE_BOOL.DEFAULT;
                                break;
                            default:                                
                                throw new Exception(KeilWizardStrings.IDS_NOT_SUPPORTED_TOOL);
                        }
                    }
                    else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    #region StopCode

                    s = tr.ReadLine();
                    m = RType2.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    if (m.Groups["name"].ToString() == "StopCode")
                    {
                        switch ((STOP_CODE)int.Parse(m.Groups["value"].ToString()))
                        {
                            case STOP_CODE.ExitCode_GE_1:
                                result.StopCode = STOP_CODE.ExitCode_GE_1;
                                break;
                            case STOP_CODE.ExitCode_GE_10:
                                result.StopCode = STOP_CODE.ExitCode_GE_10;
                                break;
                            case STOP_CODE.ExitCode_GE_2:
                                result.StopCode = STOP_CODE.ExitCode_GE_2;
                                break;
                            case STOP_CODE.ExitCode_GE_3:
                                result.StopCode = STOP_CODE.ExitCode_GE_3;
                                break;
                            case STOP_CODE.ExitCode_GE_4:
                                result.StopCode = STOP_CODE.ExitCode_GE_4;
                                break;
                            case STOP_CODE.ExitCode_GE_5:
                                result.StopCode = STOP_CODE.ExitCode_GE_5;
                                break;
                            case STOP_CODE.ExitCode_GE_6:
                                result.StopCode = STOP_CODE.ExitCode_GE_6;
                                break;
                            case STOP_CODE.ExitCode_GE_7:
                                result.StopCode = STOP_CODE.ExitCode_GE_7;
                                break;
                            case STOP_CODE.ExitCode_GE_8:
                                result.StopCode = STOP_CODE.ExitCode_GE_8;
                                break;
                            case STOP_CODE.ExitCode_GE_9:
                                result.StopCode = STOP_CODE.ExitCode_GE_9;
                                break;
                            case STOP_CODE.Never:
                                result.StopCode = STOP_CODE.Never;
                                break;
                            case STOP_CODE.NotSecified:
                                result.StopCode = STOP_CODE.NotSecified;
                                break;
                            default:                                
                                throw new Exception(KeilWizardStrings.IDS_NOT_SUPPORTED_TOOL);
                        }
                    }
                    else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    //#region CustArgs
                    //Don't know what is it. Let it be by default

                    s = tr.ReadLine(); //CustArgs
                    //m = RType1.Match(s);
                    //if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    //if (m.Groups["name"].ToString() == "CustArgs") result.CustArgs = m.Groups["value"].ToString();
                    //else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    //#endregion

                    //#region LibMods
                    //Don't know what is it. Let it be by default

                    s = tr.ReadLine(); //LibMods
                    //m = RType1.Match(s);
                    //if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    //if (m.Groups["name"].ToString() == "LibMods") result.LibMods = m.Groups["value"].ToString();
                    //else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    //#endregion

                    #region ADSLDFG

                    s = tr.ReadLine();
                    m = RType5.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    if (m.Groups["name"].ToString() == "ADSLDFG")
                    {
                        result.ADSLDFG = m.Groups["values"].ToString().Trim();
                    }
                    else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    #region ADSLDTA

                    s = tr.ReadLine();
                    m = RType1.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    if (m.Groups["name"].ToString() == "ADSLDTA") result.ADSLDTA = m.Groups["value"].ToString();
                    else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    #region ADSLDDA

                    s = tr.ReadLine();
                    m = RType1.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    if (m.Groups["name"].ToString() == "ADSLDDA") result.ADSLDDA = m.Groups["value"].ToString();
                    else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    #region ADSLDSC

                    s = tr.ReadLine();
                    m = RType1.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    if (m.Groups["name"].ToString() == "ADSLDSC") result.ADSLDSC = m.Groups["value"].ToString();
                    else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    #region ADSLDIB

                    s = tr.ReadLine();
                    m = RType1.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    if (m.Groups["name"].ToString() == "ADSLDIB") result.ADSLDIB = m.Groups["value"].ToString();
                    else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    #region ADSLDIC

                    s = tr.ReadLine();
                    m = RType1.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    if (m.Groups["name"].ToString() == "ADSLDIC") result.ADSLDIC = m.Groups["value"].ToString();
                    else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    //#region ADSLDMC

                    s = tr.ReadLine(); //ADSLDMC
                    //m = RType1.Match(s);
                    //if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    //if (m.Groups["name"].ToString() == "ADSLDMC") result.ADSLDMC = m.Groups["value"].ToString();
                    //else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    //#endregion

                    #region ADSLDIF

                    s = tr.ReadLine();
                    m = RType1.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    if (m.Groups["name"].ToString() == "ADSLDIF") result.ADSLDIF = m.Groups["value"].ToString();
                    else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    #region ADSLDDW

                    s = tr.ReadLine();
                    m = RType1.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    if (m.Groups["name"].ToString() == "ADSLDDW") result.ADSLDDW = m.Groups["value"].ToString();
                    else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    #region OPTDL

                    s = tr.ReadLine();
                    m = RType6.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    if (m.Groups["name"].ToString() == "OPTDL") result.OPTDL = m.Groups["value"].ToString();
                    else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    #region OPTDBG

                    s = tr.ReadLine();
                    m = RType6.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    if (m.Groups["name"].ToString() == "OPTDBG") result.OPTDBG = m.Groups["value"].ToString();
                    else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    #region FLASH1

                    s = tr.ReadLine();
                    m = RType5.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    if (m.Groups["name"].ToString() == "FLASH1")
                    {
                        result.FLASH1 = m.Groups["values"].ToString().Trim();
                    }
                    else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    #region FLASH2

                    s = tr.ReadLine();
                    m = RType1.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    if (m.Groups["name"].ToString() == "FLASH2")
                    {
                        result.FLASH2 = m.Groups["value"].ToString();
                    }
                    else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    #region FLASH3

                    s = tr.ReadLine();
                    m = RType1.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    if (m.Groups["name"].ToString() == "FLASH3")
                    {
                        result.FLASH3 = m.Groups["value"].ToString();
                    }
                    else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    #region FLASH4

                    s = tr.ReadLine();
                    m = RType1.Match(s);
                    if (!m.Success) throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);
                    if (m.Groups["name"].ToString() == "FLASH4")
                    {
                        result.FLASH4 = m.Groups["value"].ToString();
                    }
                    else throw new Exception(KeilWizardStrings.IDS_WRONG_FILE_FORMAT);

                    #endregion

                    tr.Close();
                }
                catch (Exception)
                {
                    tr.Close();
                    throw;
                }
            }

            return result;
        }
    }
}
