using System;
using System.Collections.Generic;
using System.ComponentModel;
using XsdInventoryFormatObject;
using PKStudio.ItemWrappers.Converters;
using System.Collections.ObjectModel;

namespace PKStudio.ItemWrappers
{
    [DefaultProperty("ToolName"), Serializable]
    public class ToolChainOptionsWrapper : BaseTypedWrapper<ToolChainOptions>
    {
        private ToolChainOptionsWrapper(ToolChainOptions wrapper)
            : base(wrapper)
        {
        }
        [Category("General")]
        [TypeConverter(typeof(ExpandableObjectConverterEx))]
        public ToolOptionsWrapper ArchiverFlags
        {
            get
            {
                if (this.InnerObject.ArchiverFlags != null)
                    return BaseWrapper.Wrap < ToolOptionsWrapper >(this.InnerObject.ArchiverFlags);
                else
                    return null;
            }
            set
            {
                if (value != null)
                    this.InnerObject.ArchiverFlags = value.InnerObject;
                else
                    this.InnerObject.ArchiverFlags = null;
            }
        }

        [Category("General")]
        [TypeConverter(typeof(ExpandableObjectConverterEx))]
        public ToolOptionsWrapper AsmFlags
        {
            get
            {
                if (this.InnerObject.AsmFlags != null)
                    return BaseWrapper.Wrap < ToolOptionsWrapper >(this.InnerObject.AsmFlags);
                else
                    return null;
            }
            set
            {
                if (value != null)
                    this.InnerObject.AsmFlags = value.InnerObject;
                else
                    this.InnerObject.AsmFlags = null;
            }
        }

        [Category("General")]
        [TypeConverter(typeof(ExpandableCollectionConverter<ToolFlagWrapper , ToolFlag>))]
        public CollectionWrapper<ToolFlagWrapper , ToolFlag> C_CppFlags
        {
            get
            {
                return WrapList < ToolFlagWrapper , ToolFlag> (this.InnerObject.C_CppFlags);
            }
            set
            {
                this.InnerObject.C_CppFlags = UnWrapList<ToolFlagWrapper , ToolFlag>( value);
            }
        }

        [Category("General")]
        [TypeConverter(typeof(ExpandableObjectConverterEx))]
        public ToolOptionsWrapper CFlags
        {
            get
            {
                if (this.InnerObject.CFlags != null)
                    return BaseWrapper.Wrap < ToolOptionsWrapper >(this.InnerObject.CFlags);
                else
                    return null;
            }
            set
            {
                if (value != null)
                    this.InnerObject.CFlags = value.InnerObject;
                else
                    this.InnerObject.CFlags = null;
            }
        }

        [Category("General")]
        [TypeConverter(typeof(ExpandableCollectionConverter<ToolFlagWrapper , ToolFlag>))]
        public CollectionWrapper<ToolFlagWrapper , ToolFlag> CommonFlags
        {
            get
            {
                return WrapList<ToolFlagWrapper, ToolFlag>(this.InnerObject.CommonFlags);
            }
            set
            {
                this.InnerObject.CommonFlags = UnWrapList<ToolFlagWrapper, ToolFlag>(value);
            }
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

        [Category("General")]
        [TypeConverter(typeof(ExpandableObjectConverterEx))]
        public ToolOptionsWrapper CppFlags
        {
            get
            {
                if (this.InnerObject.CppFlags != null)
                    return BaseWrapper.Wrap < ToolOptionsWrapper >(this.InnerObject.CppFlags);
                else
                    return null;
            }
            set
            {
                this.InnerObject.CppFlags = value.InnerObject;
            }
        }

        [Category("General")]
        public string DeviceType
        {
            get
            {
                return this.InnerObject.DeviceType;
            }
            set
            {
                this.InnerObject.DeviceType = value;
            }
        }

        [Category("General")]
        [TypeConverter(typeof(ExpandableCollectionConverter<EnvVarWrapper, EnvVar>))]
        public CollectionWrapper<EnvVarWrapper, EnvVar> EnvironmentVariables
        {
            get
            {
                return WrapList<EnvVarWrapper, EnvVar>(this.InnerObject.EnvironmentVariables);
            }
            set
            {
                this.InnerObject.EnvironmentVariables = UnWrapList<EnvVarWrapper, EnvVar>(value);
            }
        }

        [Category("General")]
        [TypeConverter(typeof(ExpandableObjectConverterEx))]
        public ToolOptionsWrapper LinkerFlags
        {
            get
            {
                if (this.InnerObject.LinkerFlags != null)
                    return BaseWrapper.Wrap < ToolOptionsWrapper >(this.InnerObject.LinkerFlags);
                else
                    return null;
            }
            set
            {
                this.InnerObject.LinkerFlags = value.InnerObject;
            }
        }

        [Category("General")]
        public string ToolName
        {
            get
            {
                return this.InnerObject.ToolName;
            }
            set
            {
                this.InnerObject.ToolName = value;
            }
        }
    }
}
