using System;
using System.Collections.Generic;
using System.ComponentModel;
using PKStudio.ItemWrappers.Converters;
using XsdInventoryFormatObject;
using System.Collections.ObjectModel;

namespace PKStudio.ItemWrappers
{
    [DefaultProperty("Name"), Serializable]
    public class MemoryMapWrapper : BaseTypedWrapper<MemoryMap>, IName , IConditional
    {        
        private MemoryMapWrapper(MemoryMap map)
            : base(map)
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
        [TypeConverter(typeof(ExpandableObjectConverterEx))]
        public EnvVarsWrapper EnvironmentVariables
        {
            get
            {
                if (this.InnerObject.EnvironmentVariables != null)
                    return BaseWrapper.Wrap < EnvVarsWrapper>(this.InnerObject.EnvironmentVariables);
                else
                    return null;
            }
            set
            {
                if (value != null)
                    this.InnerObject.EnvironmentVariables = value.InnerObject;
                else
                    this.InnerObject.EnvironmentVariables = null;
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
        [TypeConverter(typeof(ExpandableCollectionConverter<MemoryRegionWrapper, MemoryRegion>))]
        public CollectionWrapper<MemoryRegionWrapper, MemoryRegion> Regions
        {
            get
            {
                return WrapList < MemoryRegionWrapper , MemoryRegion> (this.InnerObject.Regions);
            }
            set
            {
                this.InnerObject.Regions = UnWrapList <MemoryRegionWrapper, MemoryRegion>(value);
            }
        }
    }
}
