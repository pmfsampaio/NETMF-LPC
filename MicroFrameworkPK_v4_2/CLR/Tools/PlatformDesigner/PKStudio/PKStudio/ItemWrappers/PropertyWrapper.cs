using System;
using System.ComponentModel;
using XsdInventoryFormatObject;

namespace PKStudio.ItemWrappers
{
    [DefaultProperty("NameValue"), Serializable]
    public class PropertyWrapper : BaseTypedWrapper<MFProperty> ,IName
    {
        private PropertyWrapper(MFProperty property)
            : base(property)
        {
        }
        [Category("General")]
        public string Condition
        {
            get
            {
                return this.InnerObject.Condition;
            }
            set
            {
                this.InnerObject.Condition = value;
            }
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
