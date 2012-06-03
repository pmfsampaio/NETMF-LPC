using System;
using System.Collections.Generic;
using System.ComponentModel;
using PKStudio.ItemWrappers.Converters;
using XsdInventoryFormatObject;
using System.Collections.ObjectModel;

namespace PKStudio.ItemWrappers
{
    [DefaultProperty("Name"), Serializable]
    public class EnvVarsWrapper : BaseTypedWrapper<EnvVars>, IConditional, IName
    {
        private EnvVarsWrapper(EnvVars vars)
            : base(vars)
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
        [TypeConverter(typeof(ExpandableCollectionConverter<EnvVarWrapper, EnvVar>))]
        public CollectionWrapper<EnvVarWrapper, EnvVar> EnvVarCollection
        {
            get
            {
                return WrapList < EnvVarWrapper , EnvVar> (this.InnerObject.EnvVarCollection);
            }
            set
            {
                this.InnerObject.EnvVarCollection = UnWrapList < EnvVarWrapper , EnvVar>(value);
            }
        }

        [Category("General")]
        [TypeConverter(typeof(ExpandableCollectionConverter<EnvVarsWrapper, EnvVars>))]
        public CollectionWrapper< EnvVarsWrapper , EnvVars> EnvVarsCollection
        {
            get
            {
                return WrapList < EnvVarsWrapper , EnvVars> (this.InnerObject.EnvVarsCollection);
            }
            set
            {
                this.InnerObject.EnvVarsCollection = UnWrapList <EnvVarsWrapper, EnvVars> (value);
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
    }
}
