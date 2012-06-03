using System;
using System.ComponentModel;
using XsdInventoryFormatObject;

namespace PKStudio.ItemWrappers
{
    [Serializable]//[DefaultProperty("")]
    public class BuildScriptWrapper : BaseTypedWrapper<BuildScript>, IConditional
    {
        private BuildScriptWrapper(BuildScript script)
            : base(script)
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
        public string Script
        {
            get
            {
                return this.InnerObject.Script;
            }
            set
            {
                this.InnerObject.Script = value;
            }
        }

    }
}
