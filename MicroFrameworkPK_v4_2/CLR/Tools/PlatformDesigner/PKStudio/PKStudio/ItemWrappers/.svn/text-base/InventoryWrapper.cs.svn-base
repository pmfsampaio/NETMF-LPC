using System;
using System.Collections.Generic;
using System.ComponentModel;
using XsdInventoryFormatObject;
using System.Collections.ObjectModel;
using PKStudio.ItemWrappers.Converters;

namespace PKStudio.ItemWrappers
{
    [DefaultProperty("Name"), Serializable]
    public class InventoryWrapper : BaseTypedWrapper<Inventory>
    {
        public InventoryWrapper(Inventory inv)
            : base(inv)
        {
        }

        [Category("General")]
        [TypeConverter(typeof(ExpandableCollectionConverter<AssemblyWrapper, MFAssembly>))]
        public CollectionWrapper<AssemblyWrapper, MFAssembly> Assemblies
        {
            get
            {
                return WrapList<AssemblyWrapper, MFAssembly>(this.InnerObject.Assemblies);
            }
            set
            {
                this.InnerObject.Assemblies = UnWrapList<AssemblyWrapper, MFAssembly>(value);
            }
        }

        [Category("General")]
        [TypeConverter(typeof(ExpandableCollectionConverter<BuildParameterWrapper, BuildParameter>))]
        public CollectionWrapper<BuildParameterWrapper, BuildParameter> BuildParameters
        {
            get
            {
                return WrapList<BuildParameterWrapper, BuildParameter>(this.InnerObject.BuildParameters);
            }
            set
            {
                this.InnerObject.BuildParameters = UnWrapList<BuildParameterWrapper, BuildParameter>(value);
            }
        }

        [Category("General")]
        [TypeConverter(typeof(ExpandableCollectionConverter<BuildToolWrapper_, BuildTool>))]
        public CollectionWrapper<BuildToolWrapper_, BuildTool> BuildTools
        {
            get
            {
                return WrapList<BuildToolWrapper_, BuildTool>(this.InnerObject.BuildTools);
            }
            set
            {
                this.InnerObject.BuildTools = UnWrapList<BuildToolWrapper_, BuildTool>(value);
            }
        }

        [Category("General")]
        [TypeConverter(typeof(ExpandableCollectionConverter<FeatureWrapper, Feature>))]
        public CollectionWrapper<FeatureWrapper, Feature> Features
        {
            get
            {
                return WrapList<FeatureWrapper, Feature>(this.InnerObject.Features);
            }
            set
            {
                this.InnerObject.Features = UnWrapList<FeatureWrapper, Feature>(value);
            }
        }

        [Category("General")]
        public string File
        {
            get
            {
                return this.InnerObject.File;
            }
            set
            {
                this.InnerObject.File = value;
            }
        }

        [Category("General")]
        [TypeConverter(typeof(ExpandableCollectionConverter<LibraryWrapper, Library>))]
        public CollectionWrapper<LibraryWrapper, Library> Libraries
        {
            get
            {
                return WrapList<LibraryWrapper, Library>(this.InnerObject.Libraries);
            }
            set
            {
                this.InnerObject.Libraries = UnWrapList<LibraryWrapper, Library>(value);
            }
        }

        [Category("General")]
        [TypeConverter(typeof(ExpandableCollectionConverter<LibraryCategoryWrapper, LibraryCategory>))]
        public CollectionWrapper<LibraryCategoryWrapper, LibraryCategory> LibraryCategories
        {
            get
            {
                return WrapList<LibraryCategoryWrapper, LibraryCategory>(this.InnerObject.LibraryCategories);
            }
            set
            {
                this.InnerObject.LibraryCategories = UnWrapList<LibraryCategoryWrapper, LibraryCategory>(value);
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
        [TypeConverter(typeof(ExpandableCollectionConverter<ProcessorWrapper, Processor>))]
        public CollectionWrapper<ProcessorWrapper, Processor> Processors
        {
            get
            {
                return WrapList<ProcessorWrapper, Processor>(this.InnerObject.Processors);
            }
            set
            {
                this.InnerObject.Processors = UnWrapList<ProcessorWrapper, Processor>(value);
            }
        }

        [Category("General")]
        [TypeConverter(typeof(ExpandableCollectionConverter<ProjectWrapper, MFProject>))]
        public CollectionWrapper<ProjectWrapper, MFProject> ProjectTemplates
        {
            get
            {
                return WrapList<ProjectWrapper, MFProject>(this.InnerObject.ProjectTemplates);
            }
            set
            {
                this.InnerObject.ProjectTemplates = UnWrapList<ProjectWrapper, MFProject>(value);
            }
        }

        [Category("General")]
        [TypeConverter(typeof(ExpandableCollectionConverter<SolutionWrapper, MFSolution>))]
        public CollectionWrapper<SolutionWrapper, MFSolution> Solutions
        {
            get
            {
                return WrapList<SolutionWrapper, MFSolution>(this.InnerObject.Solutions);
            }
            set
            {
                this.InnerObject.Solutions = UnWrapList<SolutionWrapper, MFSolution>(value);
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
