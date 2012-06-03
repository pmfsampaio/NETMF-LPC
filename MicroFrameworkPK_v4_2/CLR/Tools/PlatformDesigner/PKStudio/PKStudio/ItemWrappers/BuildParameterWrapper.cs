using System;
using System.ComponentModel;
using XsdInventoryFormatObject;

namespace PKStudio.ItemWrappers
{
    [DefaultProperty("Parameter"), Serializable]
    public class BuildParameterWrapper : BaseTypedWrapper<BuildParameter>
    {
        private BuildParameterWrapper(BuildParameter param)
            : base(param)
        {
        }
        
        [Category("General")]
        public string Action
        {
            get
            {
                return this.InnerObject.Action;
            }
            set
            {
                this.InnerObject.Action = value;
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
        public string Parameter
        {
            get
            {
                return this.InnerObject.Parameter;
            }
            set
            {
                this.InnerObject.Parameter = value;
            }
        }

    }
}
