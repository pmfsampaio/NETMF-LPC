using System;
using System.Collections.Generic;
using System.ComponentModel;
using XsdInventoryFormatObject;
using System.Collections.ObjectModel;
using PKStudio.ItemWrappers.Converters;

namespace PKStudio.ItemWrappers
{
    [DefaultProperty("Name"), Serializable]
    public class MiscBuildToolWrapper : BaseTypedWrapper<MiscBuildTool>, IGuid, IName
    {
        private MiscBuildToolWrapper(MiscBuildTool build_tool)
            : base(build_tool)
        {
        }
        [Category("General")]
        public BuildToolDefineWrapper BuildTool
        {
            get
            {
                if (this.InnerObject.BuildTool != null)
                    return BaseWrapper.Wrap < BuildToolDefineWrapper >(this.InnerObject.BuildTool);
                else
                    return null;
            }
            set
            {
                if (value != null)
                    this.InnerObject.BuildTool = value.InnerObject;
                else
                    this.InnerObject.BuildTool = null;
            }
        }

        [Category("General")]
        public ToolOptionsWrapper BuildToolOptions
        {
            get
            {
                if (this.InnerObject.BuildToolOptions != null)
                    return BaseWrapper.Wrap < ToolOptionsWrapper >(this.InnerObject.BuildToolOptions);
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
        public string BuildToolWrapper
        {
            get
            {
                return this.InnerObject.BuildToolWrapper;
            }
            set
            {
                this.InnerObject.BuildToolWrapper = value;
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
        public string ToolPath
        {
            get
            {
                return this.InnerObject.ToolPath;
            }
            set
            {
                this.InnerObject.ToolPath = value;
            }
        }
    }
}
