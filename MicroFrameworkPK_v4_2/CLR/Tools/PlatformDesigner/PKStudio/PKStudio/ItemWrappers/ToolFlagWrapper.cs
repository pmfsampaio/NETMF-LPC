using System;
using System.ComponentModel;
using XsdInventoryFormatObject;

namespace PKStudio.ItemWrappers
{
    [DefaultProperty("Flag"), Serializable]
    public class ToolFlagWrapper : BaseTypedWrapper<ToolFlag>, IConditional
    {
        private ToolFlagWrapper(ToolFlag flag)
            : base(flag)
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
        public string Flag
        {
            get
            {
                return this.InnerObject.Flag;
            }
            set
            {
                this.InnerObject.Flag = value;
            }
        }
    }
}
