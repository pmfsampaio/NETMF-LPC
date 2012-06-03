using System;
using System.Collections.Generic;
using System.ComponentModel;
using XsdInventoryFormatObject;
using PKStudio.ItemWrappers.Converters;
using PKStudio.Tree.Nodes;
using System.Collections.ObjectModel;

namespace PKStudio.ItemWrappers
{
    [DefaultProperty("Name"), Serializable]
    public class ProcessorWrapper : BaseTypedWrapper<Processor>, IGuid, IName, IVersion, IProjectPath
    {
        private ProcessorWrapper(Processor proc)
            : base(proc)
        { 
        }

        protected override BaseNode OnGetTreeNode(Tree.Nodes.BaseNode parent)
        {
            return new ProcessorNode(this, parent);
        }

        [Category("General")]
        [TypeConverter(typeof(ExpandableCollectionConverter<BuildToolRefWrapper, BuildToolRef>))]
        public CollectionWrapper<BuildToolRefWrapper, BuildToolRef> BuildToolOptions
        {
            get
            {
                return WrapList<BuildToolRefWrapper, BuildToolRef>(this.InnerObject.BuildToolOptions);
            }
            set
            {
                this.InnerObject.BuildToolOptions = UnWrapList<BuildToolRefWrapper, BuildToolRef>(value);
            }
        }

        [Category("General")]
        public string CpuName
        {
            get
            {
                return this.InnerObject.CpuName;
            }
            set
            {
                this.InnerObject.CpuName = value;
            }
        }

        [Category("General")]
        public string CustomFilter
        {
            get
            {
                return this.InnerObject.CustomFilter;
            }
            set
            {
                this.InnerObject.CustomFilter = value;
            }
        }

        [Category("General")]
        public string DefaultISA
        {
            get
            {
                return this.InnerObject.DefaultISA;
            }
            set
            {
                this.InnerObject.DefaultISA = value;
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
        public bool IsSolutionWizardVisible
        {
            get
            {
                return this.InnerObject.IsSolutionWizardVisible;
            }
            set
            {
                this.InnerObject.IsSolutionWizardVisible = value;
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
        public string PlatformFamily
        {
            get
            {
                return this.InnerObject.PlatformFamily;
            }
            set
            {
                this.InnerObject.PlatformFamily = value;
            }
        }

        [Category("General")]
        public string ProjectPath
        {
            get
            {
                return this.InnerObject.ProjectPath;
            }
            set
            {
                this.InnerObject.ProjectPath = value;
            }
        }

        [Category("General")]
        [TypeConverter(typeof(ExpandableCollectionConverter<PropertyWrapper, MFProperty>))]
        public CollectionWrapper<PropertyWrapper, MFProperty> Properties
        {
            get
            {
                return WrapList<PropertyWrapper, MFProperty>(this.InnerObject.Properties);
            }
            set
            {
                this.InnerObject.Properties = UnWrapList<PropertyWrapper, MFProperty>(value);
            }
        }

        [Category("General")]
        [TypeConverter(typeof(ExpandableCollectionConverter<ComponentWrapper, MFComponent>))]
        public CollectionWrapper<ComponentWrapper, MFComponent> SupportedISAs
        {
            get
            {
                return WrapList<ComponentWrapper, MFComponent>(this.InnerObject.SupportedISAs);
            }
            set
            {
                this.InnerObject.SupportedISAs = UnWrapList<ComponentWrapper, MFComponent>(value);
            }
        }

        [Category("General")]
        [TypeConverter(typeof(ExpandableObjectConverterEx))]
        public VersionWrapper Version
        {
            get
            {
                if (this.InnerObject.Version != null)
                    return BaseWrapper.Wrap < VersionWrapper>(this.InnerObject.Version);
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
