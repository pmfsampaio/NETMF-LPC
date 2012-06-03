using System;
using System.ComponentModel;
using XsdInventoryFormatObject;

namespace PKStudio.ItemWrappers
{
    [DefaultProperty("Exec"), Serializable]
    public class BuildToolDefineWrapper : BaseTypedWrapper<BuildToolDefine>, IConditional
    {
        private BuildToolDefineWrapper(BuildToolDefine tool_define)
            : base(tool_define)
        {
        }
        [Category("General")]
        public string Conditional
        {
            get
            {
                return this.InnerObject.Conditional;
            }
            set
            {
                this.InnerObject.Conditional = value;
            }
        }

        [Category("General")]
        public string Description
        {
            get
            {
                return this.InnerObject.Description;
            }
            set
            {
                this.InnerObject.Description = value;
            }
        }

        [Category("General")]
        public string Exec
        {
            get
            {
                return this.InnerObject.Exec;
            }
            set
            {
                this.InnerObject.Exec = value;
            }
        }
    }
}
