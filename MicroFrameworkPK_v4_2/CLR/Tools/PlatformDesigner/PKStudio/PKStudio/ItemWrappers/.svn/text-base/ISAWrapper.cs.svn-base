using System;
using System.ComponentModel;
using XsdInventoryFormatObject;
using PKStudio.ItemWrappers.Converters;

namespace PKStudio.ItemWrappers
{
    [DefaultProperty("Name"), Serializable]
    public class ISAWrapper : BaseTypedWrapper<ISA>, IGuid, IName, IVersion
    {
        private ISAWrapper(ISA isa)
            : base(isa)
        {
        }
        [Category("General")]
        [TypeConverter(typeof(ExpandableObjectConverterEx))]
        public ToolChainOptionsWrapper BuildToolOptions
        {
            get
            {
                if (this.InnerObject.BuildToolOptions != null)
                    return BaseWrapper.Wrap < ToolChainOptionsWrapper >(this.InnerObject.BuildToolOptions);
                else
                    return null;
            }
            set
            {
                if (value != null)
                    this.InnerObject.BuildToolOptions = value.InnerObject;
                else
                    this.InnerObject.BuildToolOptions = null;
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
        public string Documentation
        {
            get
            {
                return this.InnerObject.Documentation;
            }
            set
            {
                this.InnerObject.Documentation = value;
            }
        }

        [Category("General")]
        public string Guid
        {
            get
            {
                return this.InnerObject.Guid;
            }
            set
            {
                this.InnerObject.Guid = value;
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
        [TypeConverter(typeof(ExpandableObjectConverterEx))]
        public VersionWrapper Version
        {
            get
            {
                if (this.InnerObject.Version != null)
                    return BaseWrapper.Wrap < VersionWrapper >(this.InnerObject.Version);
                else
                    return null;
            }
            set
            {
                if (value != null)
                    this.InnerObject.Version = value.InnerObject;
                else
                    this.InnerObject.Version = null;
            }
        }

    }
}
