using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace PKStudio.Tools.uVisionGenerator.Classes.HelpClasses
{
    class GeneratingLogMessage
    {
        public enum WORK_TYPE
        {
            CONVERT_SOLUTION,
            CONVERT_PROJECT,
            BUILD_PROJECT,
            CREATE_PROJECT_TREE,
            CREATE_FILE_LIST,
            CREATE_TARGETS,
            WRITING_FILES,
            UNKNOWN,
        }
        public enum WORK_STATE
        {
            START,
            WORKING,
            DONE,
            ERROR,
        }
        public GeneratingLogMessage(string Message, WORK_TYPE WorkType, WORK_STATE WorkState)
        {
            this.Message = Message;
            this.WorkType = WorkType;
            this.WorkState = WorkState;
        }

        public GeneratingLogMessage(string Message, WORK_TYPE WorkType, WORK_STATE WorkState, int Progress)
        {
            this.Message = Message;
            this.WorkType = WorkType;
            this.WorkState = WorkState;
            this.Progress = Progress;
        }

        public string Message { get; set; }
        public WORK_TYPE WorkType { get; set; }
        public WORK_STATE WorkState { get; set; }
        public int Progress { get; set; }
    }
}
