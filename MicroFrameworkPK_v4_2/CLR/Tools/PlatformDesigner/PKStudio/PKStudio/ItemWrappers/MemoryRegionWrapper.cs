using System;
using System.Collections.Generic;
using System.ComponentModel;
using PKStudio.ItemWrappers.Converters;
using XsdInventoryFormatObject;
using System.Collections.ObjectModel;

namespace PKStudio.ItemWrappers
{
    [DefaultProperty("Name"), Serializable]
    public class MemoryRegionWrapper : BaseTypedWrapper<MemoryRegion>, IName, IConditional
    {
        private MemoryRegionWrapper(MemoryRegion region)
            : base(region)
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
        [TypeConverter(typeof(ExpandableCollectionConverter<MemorySectionWrapper, MemorySection >))]
        public CollectionWrapper<MemorySectionWrapper, MemorySection> Sections
        {
            get
            {
                return WrapList < MemorySectionWrapper , MemorySection > (this.InnerObject.Sections);
            }
            set
            {
                this.InnerObject.Sections = UnWrapList < MemorySectionWrapper, MemorySection >(value);
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
    }
}
