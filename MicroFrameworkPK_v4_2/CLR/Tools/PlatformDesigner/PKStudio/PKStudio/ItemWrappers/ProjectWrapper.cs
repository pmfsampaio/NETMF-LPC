using System;
using System.Collections.Generic;
using System.ComponentModel;
using Microsoft.Build.Construction;
using PKStudio.ItemWrappers.Converters;
using XsdInventoryFormatObject;
using System.Collections.ObjectModel;
using PKStudio.Tree.Nodes;
using System.IO;

namespace PKStudio.ItemWrappers
{
    [DefaultProperty("Name"), Serializable]
    public class ProjectWrapper : BaseTypedWrapper<MFProject>, IGuid, IName , IVersion, IProjectPath
    {
        private ProjectWrapper(MFProject project)
            : base(project)
        {
        }

        protected override BaseNode OnGetTreeNode(BaseNode parent)
        {
            return new ProjectNode(this, parent);
        }

        public bool IsBootloaderProject()
        {
            return this.InnerObject.IsBootloaderProject();
        }

        [Category("General")]
        [TypeConverter(typeof(ExpandableObjectConverterEx))]
        public BuildToolRef BuildTool
        {
            get
            {
                return this.InnerObject.BuildTool;
            }
            set
            {
                this.InnerObject.BuildTool = value;
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
        public string Directory
        {
            get
            {
                return this.InnerObject.Directory;
            }
            set
            {
                this.InnerObject.Directory = value;
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
        [TypeConverter(typeof(ExpandableCollectionConverter<string>))]
        public Collection<string> ExtraAssemblies
        {
            get
            {
                return new Collection<string>(this.InnerObject.ExtraAssemblies);
            }
            set
            {
                this.InnerObject.ExtraAssemblies = new List<string>( value);
            }
        }

        [Category("Files")]
        [TypeConverter(typeof(ExpandableCollectionConverter<BuildFileWrapper, MFBuildFile>))]
        public CollectionWrapper<BuildFileWrapper, MFBuildFile> FastCompileFiles
        {
            get
            {
                return WrapList < BuildFileWrapper , MFBuildFile>(this.InnerObject.FastCompileFiles);
            }
            set
            {
                this.InnerObject.FastCompileFiles = UnWrapList < BuildFileWrapper , MFBuildFile>(value);
            }
        }

        [Category("General")]
        [TypeConverter(typeof(ExpandableCollectionConverter<ComponentWrapper, MFComponent>))]
        public CollectionWrapper<ComponentWrapper, MFComponent> Features
        {
            get
            {
                return WrapList < ComponentWrapper , MFComponent>(this.InnerObject.Features);
            }
            set
            {
                this.InnerObject.Features = UnWrapList <ComponentWrapper, MFComponent>(value);
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

        [Category("Files")]
        [TypeConverter(typeof(ExpandableCollectionConverter<BuildFileWrapper, MFBuildFile>))]
        public CollectionWrapper<BuildFileWrapper, MFBuildFile> HeaderFiles
        {
            get
            {
                return WrapList<BuildFileWrapper, MFBuildFile>(this.InnerObject.HeaderFiles);
            }
            set
            {
                this.InnerObject.HeaderFiles = UnWrapList<BuildFileWrapper, MFBuildFile>(value);
            }
        }

        [Category("General")]
        [TypeConverter(typeof(ExpandableCollectionConverter<BuildFileWrapper, MFBuildFile>))]
        public CollectionWrapper<BuildFileWrapper, MFBuildFile> IncludePaths
        {
            get
            {
                return WrapList<BuildFileWrapper, MFBuildFile>(this.InnerObject.IncludePaths);
            }
            set
            {
                this.InnerObject.IncludePaths = UnWrapList<BuildFileWrapper, MFBuildFile>(value); ;
            }
        }

        [Category("General")]
        [TypeConverter(typeof(ExpandableCollectionConverter<string>))]
        public Collection<string> InteropFeatures
        {
            get
            {
                return new Collection<string>(this.InnerObject.InteropFeatures);
            }
            set
            {
                this.InnerObject.InteropFeatures = new List<string>(value);
            }
        }

        [Category("General")]
        public bool IsClrProject
        {
            get
            {
                return this.InnerObject.IsClrProject;
            }
            set
            {
                this.InnerObject.IsClrProject = value;
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
        [TypeConverter(typeof(ExpandableCollectionConverter<ComponentWrapper, MFComponent>))]
        public CollectionWrapper<ComponentWrapper, MFComponent> Libraries
        {
            get
            {
                return WrapList < ComponentWrapper , MFComponent>(this.InnerObject.Libraries);
            }
            set
            {
                this.InnerObject.Libraries = UnWrapList<ComponentWrapper, MFComponent>(value);
            }
        }

        [Category("General")]
        [TypeConverter(typeof(ExpandableCollectionConverter<ComponentWrapper, MFComponent>))]
        public CollectionWrapper<ComponentWrapper, MFComponent> LibraryCategories
        {
            get
            {
                return WrapList < ComponentWrapper , MFComponent>( this.InnerObject.LibraryCategories);
            }
            set
            {
                this.InnerObject.LibraryCategories = UnWrapList < ComponentWrapper , MFComponent>( value);
            }
        }

        [Category("General")]
        [TypeConverter(typeof(ExpandableObjectConverterEx))]
        public MemoryMapWrapper MemoryMap
        {
            get
            {
                if (this.InnerObject.MemoryMap != null)
                    return BaseWrapper.Wrap < MemoryMapWrapper >(this.InnerObject.MemoryMap);
                else
                    return null;
            }
            set
            {
                if (value != null)
                    this.InnerObject.MemoryMap = value.InnerObject;
                else
                    this.InnerObject.MemoryMap = null;
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

        [Category("Files")]
        [TypeConverter(typeof(ExpandableCollectionConverter<BuildFileWrapper, MFBuildFile>))]
        public CollectionWrapper<BuildFileWrapper, MFBuildFile> OtherFiles
        {
            get
            {
                return WrapList < BuildFileWrapper , MFBuildFile>( this.InnerObject.OtherFiles);
            }
            set
            {
                this.InnerObject.OtherFiles = UnWrapList<BuildFileWrapper , MFBuildFile>( value);
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
                return WrapList < PropertyWrapper , MFProperty>( this.InnerObject.Properties);
            }
            set
            {
                this.InnerObject.Properties = UnWrapList<PropertyWrapper , MFProperty>( value);
            }
        }

        [Category("Files")]
        [TypeConverter(typeof(ExpandableObjectConverterEx))]
        public BuildFileWrapper ScatterFile
        {
            get
            {
                return BaseWrapper.Wrap<BuildFileWrapper>(this.InnerObject.ScatterFile);
            }
            set
            {
                if (value != null)
                    this.InnerObject.ScatterFile = value.InnerObject;
                else
                    this.InnerObject.ScatterFile = null;
            }
        }

        [Category("General")]
        public string SettingsFile
        {
            get
            {
                return this.InnerObject.SettingsFile;
            }
            set
            {
                this.InnerObject.SettingsFile = value;
            }
        }

        [Category("Files")]
        [TypeConverter(typeof(ExpandableCollectionConverter<BuildFileWrapper, MFBuildFile>))]
        public CollectionWrapper<BuildFileWrapper, MFBuildFile> SourceFiles
        {
            get
            {
                return WrapList < BuildFileWrapper , MFBuildFile>( this.InnerObject.SourceFiles);
            }
            set
            {
                this.InnerObject.SourceFiles = UnWrapList<BuildFileWrapper , MFBuildFile>( value);
            }
        }

        [Category("General")]
        [TypeConverter(typeof(ExpandableCollectionConverter<ProjectTargetElementWrapper, ProjectTargetElement>))]
        public CollectionWrapper< ProjectTargetElementWrapper , ProjectTargetElement> Targets
        {
            get
            {
                return WrapList < ProjectTargetElementWrapper , ProjectTargetElement> (this.InnerObject.Targets);
            }
            set
            {
                this.InnerObject.Targets = UnWrapList<ProjectTargetElementWrapper , ProjectTargetElement>( value);
            }
        }

        [Category("General")]
        [TypeConverter(typeof(ExpandableObjectConverterEx))]
        public VersionWrapper Version
        {
            get
            {
                if (this.InnerObject.Version != null)
                    return BaseWrapper.Wrap < VersionWrapper >( this.InnerObject.Version);
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
