using System;
using System.Collections.Generic;
using System.ComponentModel;
using XsdInventoryFormatObject;
using PKStudio.ItemWrappers.Converters;
using System.Collections.ObjectModel;

namespace PKStudio.ItemWrappers
{
    [Serializable]//[DefaultProperty("")]
    public class ToolOptionsWrapper : BaseTypedWrapper<ToolOptions>
    {
        private ToolOptionsWrapper(ToolOptions options)
            : base(options)
        {
        }

        [Category("General")]
        [TypeConverter(typeof(ExpandableObjectConverterEx))]
        public BuildToolParametersWrapper BuildToolParameters
        {
            get
            {
                if (this.InnerObject.BuildToolParameters != null)
                    return BaseWrapper.Wrap < BuildToolParametersWrapper>(this.InnerObject.BuildToolParameters);
                else
                    return null;
            }
            set
            {
                if (value != null)
                    this.InnerObject.BuildToolParameters = value.InnerObject;
                else
                    this.InnerObject.BuildToolParameters = null;
            }
        }

        [Category("General")]
        [TypeConverter(typeof(ExpandableCollectionConverter<ToolFlagWrapper , ToolFlag>))]
        public CollectionWrapper<ToolFlagWrapper , ToolFlag> ToolFlags
        {
            get
            {
                return WrapList<ToolFlagWrapper, ToolFlag>(this.InnerObject.ToolFlags);
            }
            set
            {
                this.InnerObject.ToolFlags = UnWrapList<ToolFlagWrapper, ToolFlag>(value);
            }
        }

    }
}
