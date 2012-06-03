using System;
using System.ComponentModel;
using XsdInventoryFormatObject;

namespace PKStudio.ItemWrappers
{
    [DefaultProperty("Name"), Serializable]
    public class MemorySymbolWrapper : BaseTypedWrapper<MemorySymbol>, IName, IConditional
    {
        private MemorySymbolWrapper(MemorySymbol symbol)
            : base(symbol)
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
        public string Options
        {
            get
            {
                return this.InnerObject.Options;
            }
            set
            {
                this.InnerObject.Options = value;
            }
        }

        [Category("General")]
        public int Order
        {
            get
            {
                return this.InnerObject.Order;
            }
            set
            {
                this.InnerObject.Order = value;
            }
        }
    }
}
