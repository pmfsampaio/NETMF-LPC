using System;
using System.Collections.Generic;
using System.ComponentModel;
using PKStudio.ItemWrappers.Converters;
using XsdInventoryFormatObject;
using System.Collections.ObjectModel;

namespace PKStudio.ItemWrappers
{
    [DefaultProperty("Name"), Serializable]
    public class MemorySectionWrapper : BaseTypedWrapper<MemorySection>, IName, IConditional
    {
        private MemorySectionWrapper(MemorySection section)
            : base(section)
        {
        }
        [Category("General")]
        public string Address
        {
            get
            {
                return this.InnerObject.Address;
            }
            set
            {
                this.InnerObject.Address = value;
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

        [Category("General")]
        public string Size
        {
            get
            {
                return this.InnerObject.Size;
            }
            set
            {
                this.InnerObject.Size = value;
            }
        }

        [Category("General")]
        [TypeConverter(typeof(ExpandableCollectionConverter<MemorySymbolWrapper, MemorySymbol>))]
        public CollectionWrapper<MemorySymbolWrapper, MemorySymbol> Symbols
        {
            get
            {
                return WrapList<MemorySymbolWrapper, MemorySymbol>( this.InnerObject.Symbols);
            }
            set
            {
                this.InnerObject.Symbols = UnWrapList<MemorySymbolWrapper, MemorySymbol>(value);
            }
        }
    }
}
