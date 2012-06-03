using System;
using System.Collections.Generic;
using System.ComponentModel;
using XsdInventoryFormatObject;
using PKStudio.ItemWrappers.Converters;
using System.Collections.ObjectModel;

namespace PKStudio.ItemWrappers
{
    [Serializable]//[DefaultProperty("")]
    public class BuildToolParametersWrapper : BaseTypedWrapper<BuildToolParameters>
    {
        private BuildToolParametersWrapper(BuildToolParameters parameters)
            : base(parameters)
        {
        }
        [Category("General")]
        [TypeConverter(typeof(ExpandableCollectionConverter<BuildScriptWrapper, BuildScript>))]
        public CollectionWrapper<BuildScriptWrapper, BuildScript> Parameters
        {
            get
            {
                return WrapList < BuildScriptWrapper, BuildScript>(this.InnerObject.Parameters);
            }
            set
            {
                this.InnerObject.Parameters = UnWrapList <BuildScriptWrapper, BuildScript>(value);
            }
        }

        [Category("General")]
        [TypeConverter(typeof(ExpandableCollectionConverter<BuildScriptWrapper, BuildScript>))]
        public CollectionWrapper<BuildScriptWrapper, BuildScript> PostBuild
        {
            get
            {
                return WrapList<BuildScriptWrapper, BuildScript>(this.InnerObject.PostBuild);
            }
            set
            {
                this.InnerObject.Parameters = UnWrapList<BuildScriptWrapper, BuildScript>(value);
            }
        }

        [Category("General")]
        [TypeConverter(typeof(ExpandableCollectionConverter<BuildScriptWrapper, BuildScript>))]
        public CollectionWrapper<BuildScriptWrapper, BuildScript> PreBuild
        {
            get
            {
                return WrapList<BuildScriptWrapper, BuildScript>(this.InnerObject.PreBuild);
            }
            set
            {
                this.InnerObject.Parameters = UnWrapList<BuildScriptWrapper, BuildScript>(value);
            }
        }

    }
}
