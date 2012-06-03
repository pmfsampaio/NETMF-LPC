using System;
using System.ComponentModel;
using XsdInventoryFormatObject;

namespace PKStudio.ItemWrappers
{
    [DefaultProperty("NameValue"), Serializable]
    public class EnvVarWrapper : BaseTypedWrapper<EnvVar>, IConditional, IName
    {
        private EnvVarWrapper(EnvVar var)
            : base(var)
        {
        }

        [Browsable(false)]
        public string NameValue 
        {
            get
            {
                return string.Format("{0} = {1}", this.Name, this.Value);
            }
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
        public string Name
        {
            get
            {
                return this.InnerObject.Name;
            }
            set
            {
                this.InnerObject.Name = value;
            }
        }

        [Category("General")]
        public string Value
        {
            get
            {
                return this.InnerObject.Value;
            }
            set
            {
                this.InnerObject.Value = value;
            }
        }
    }
}
