using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Diagnostics;

namespace PKStudio.Forms.Options.Options
{
    [Serializable]
    public class EnvironmentOption : OptionsHelper.Options.OptionsBase
    {
        TOOL tool = TOOL.MDK3_80a;
        private string path = string.Empty;

        public TOOL Tool { get { return this.tool; } set { this.tool = value; } }
        public string Path { get { return this.path; } set { this.path = value; } }

        public override void OnInitialized()
        {

        }

        [Serializable]
        public enum TOOL : int
        {
            /// <summary>
            /// Visual Studio 10
            /// </summary>
            VS10 = 0,
            /// <summary>
            /// Visual Studio 9
            /// </summary>
            VS9 = 1,
            /// <summary>
            /// SHC 9.2
            /// </summary>
            SHC = 2,
            /// <summary>
            /// RVDS 4.0
            /// </summary>
            RVDS4_0 = 3,
            /// <summary>
            /// RVDS 3.1
            /// </summary>
            RVDS3_1 = 4,
            /// <summary>
            /// RVDS 3.0
            /// </summary>
            RVDS3_0 = 5,
            /// <summary>
            /// MDK 3.80a
            /// </summary>
            MDK3_80a = 6,
            /// <summary>
            /// MDK 3.1
            /// </summary>
            MDK3_1 = 7,
            /// <summary>
            /// GCC 4.2
            /// </summary>
            GCC = 8,
            /// <summary>
            /// ADI5.0
            /// </summary>
            BLACKFIN = 9,
            /// <summary>
            /// RVDS 4.1
            /// </summary>
            RVDS4_1 = 10,

        }

        public static string GetToolString(TOOL tool)
        {
            string compiler_tool_version = string.Empty;
            switch (tool)
            {
                case TOOL.VS10:
                    compiler_tool_version = "VS10";
                    break;
                case TOOL.VS9:
                    compiler_tool_version = "VS9";
                    break;
                case TOOL.SHC:
                    compiler_tool_version = "SHC9.2";
                    break;
                case TOOL.RVDS4_0:
                    compiler_tool_version = "RVDS4.0";
                    break;
                case TOOL.RVDS3_1:
                    compiler_tool_version = "RVDS3.1";
                    break;
                case TOOL.RVDS3_0:
                    compiler_tool_version = "RVDS3.0";
                    break;
                case TOOL.MDK3_80a:
                    compiler_tool_version = "MDK3.80a";
                    break;
                case TOOL.MDK3_1:
                    compiler_tool_version = "MDK3.1";
                    break;
                case TOOL.GCC:
                    compiler_tool_version = "GCC4.2";
                    break;
                case TOOL.BLACKFIN:
                    compiler_tool_version = "ADI5.0";
                    break;
                case TOOL.RVDS4_1:
                    compiler_tool_version = "RVDS4.1";
                    break;
                default:
                    break;
            }
            return compiler_tool_version;
        }

        public override bool OnApplyChanges()
        {
            return true;
        }
    }
}
