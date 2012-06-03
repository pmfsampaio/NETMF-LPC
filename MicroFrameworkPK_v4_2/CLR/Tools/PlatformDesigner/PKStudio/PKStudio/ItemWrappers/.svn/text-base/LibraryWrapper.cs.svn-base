using System;
using System.Collections.Generic;
using System.ComponentModel;
using Microsoft.Build.Construction;
using PKStudio.ItemWrappers.Converters;
using XsdInventoryFormatObject;
using PKStudio.Tree.Nodes;
using System.Collections.ObjectModel;

namespace PKStudio.ItemWrappers
{
    [Serializable]
    public class LibraryWrapper : BaseTypedWrapper<Library>, IName, IGuid, IGroups, IVersion, IProjectPath, IDetailDescription, IDescription, IDocumentation, IDependencies
    {
        private LibraryWrapper(Library lib)
            : base(lib)
        {
        }

        protected override BaseNode OnGetTreeNode(Tree.Nodes.BaseNode parent)
        {
            return new LibraryNode(this, parent);
        }

        public bool IsBootloaderLibrary()
        {
            return this.InnerObject.IsBootloaderLibrary();
        }

        [Browsable(false)]
        public bool IsTemplate { get; set; }

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
        [TypeConverter(typeof(ExpandableCollectionConverter<ComponentWrapper, MFComponent>))]
        public CollectionWrapper<ComponentWrapper, MFComponent> Dependencies
        {
            get
            {
                return WrapList<ComponentWrapper, MFComponent>(this.InnerObject.Dependencies);
            }
            set
            {
                this.InnerObject.Dependencies = UnWrapList<ComponentWrapper, MFComponent>(value);
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

        [Category("Files")]
        [TypeConverter(typeof(ExpandableCollectionConverter<BuildFileWrapper, MFBuildFile>))]
        public CollectionWrapper<BuildFileWrapper, MFBuildFile> FastCompileFiles
        {
            get
            {
                return WrapList<BuildFileWrapper, MFBuildFile>(this.InnerObject.FastCompileFiles);
            }
            set
            {
                this.InnerObject.FastCompileFiles = UnWrapList<BuildFileWrapper, MFBuildFile>(value);
            }
        }

        [Category("General")]
        public string Groups
        {
            get
            {
                return this.InnerObject.Groups;
            }
            set
            {
                this.InnerObject.Groups = value;
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
        public bool HasLibraryCategory
        {
            get
            {
                return InnerObject.HasLibraryCategory;
            }
            set
            {
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
        public bool IgnoreDefaultLibPath
        {
            get
            {
                return this.InnerObject.IgnoreDefaultLibPath;
            }
            set
            {
                this.InnerObject.IgnoreDefaultLibPath = value;
            }
        }

        [Category("Files")]
        [TypeConverter(typeof(ExpandableCollectionConverter<BuildFileWrapper, MFBuildFile>))]
        public CollectionWrapper<BuildFileWrapper, MFBuildFile> IncludePaths
        {
            get
            {
                return WrapList<BuildFileWrapper, MFBuildFile>(this.InnerObject.IncludePaths);
            }
            set
            {
                this.InnerObject.IncludePaths = UnWrapList<BuildFileWrapper, MFBuildFile>( value);
            }
        }

        [Category("General")]
        [TypeConverter(typeof(ExpandableObjectConverterEx))]
        public ComponentWrapper ISASpecific
        {
            get
            {
                if (this.InnerObject.ISASpecific != null)
                    return BaseWrapper.Wrap < ComponentWrapper >(this.InnerObject.ISASpecific);
                else
                    return null;
            }
            set
            {
                if (value != null)
                    this.InnerObject.ISASpecific = value.InnerObject;
                else
                    this.InnerObject.ISASpecific = null;
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
        public bool IsStub
        {
            get
            {
                return this.InnerObject.IsStub;
            }
            set
            {
                this.InnerObject.IsStub = value;
            }
        }

        [Category("General")]
        public LibraryLevelWrapper Level
        {
            get
            {
                return (LibraryLevelWrapper)this.InnerObject.Level;
            }
            set
            {
                this.InnerObject.Level = (LibraryLevel)value;
            }
        }

        [Category("General")]
        [TypeConverter(typeof(ExpandableObjectConverterEx))]
        public ComponentWrapper LibraryCategory
        {
            get
            {
                if (this.InnerObject.LibraryCategory != null)
                    return BaseWrapper.Wrap < ComponentWrapper >(this.InnerObject.LibraryCategory);
                else
                    return null;
            }
            set
            {
                if (value != null)
                    this.InnerObject.LibraryCategory = value.InnerObject;
                else
                    this.InnerObject.LibraryCategory = null;
            }
        }

        [Category("General")]
        public string LibraryFile
        {
            get
            {
                return this.InnerObject.LibraryFile;
            }
            set
            {
                this.InnerObject.LibraryFile = value;
            }
        }

        [Category("General")]
        public string ManifestFile
        {
            get
            {
                return this.InnerObject.ManifestFile;
            }
            set
            {
                this.InnerObject.ManifestFile = value;
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
                return WrapList<BuildFileWrapper, MFBuildFile>(this.InnerObject.OtherFiles);
            }
            set
            {
                this.InnerObject.OtherFiles = UnWrapList<BuildFileWrapper, MFBuildFile>(value);
            }
        }

        [Category("General")]
        public bool PlatformIndependent
        {
            get
            {
                return this.InnerObject.PlatformIndependent;
            }
            set
            {
                this.InnerObject.PlatformIndependent = value;
            }
        }

        [Category("General")]
        [TypeConverter(typeof(ExpandableObjectConverterEx))]
        public ComponentWrapper ProcessorSpecific
        {
            get
            {
                if (this.InnerObject.ProcessorSpecific != null)
                    return BaseWrapper.Wrap < ComponentWrapper >(this.InnerObject.ProcessorSpecific);
                else
                    return null;
            }
            set
            {
                if (value != null)
                    this.InnerObject.ProcessorSpecific = value.InnerObject;
                else
                    this.InnerObject.ProcessorSpecific = null;
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
        public bool Required
        {
            get
            {
                return this.InnerObject.Required;
            }
            set
            {
                this.InnerObject.Required = value;
            }
        }

        [Category("General")]
        public string Size
        {
            get
            {
                return this.InnerObject.Size;
            }
            set
            {
                this.InnerObject.Size = value;
            }
        }

        [Category("Files")]
        [TypeConverter(typeof(ExpandableCollectionConverter<BuildFileWrapper, MFBuildFile>))]
        public CollectionWrapper<BuildFileWrapper, MFBuildFile> SourceFiles
        {
            get
            {
                return WrapList<BuildFileWrapper, MFBuildFile>(this.InnerObject.SourceFiles);
            }
            set
            {
                this.InnerObject.SourceFiles = UnWrapList<BuildFileWrapper, MFBuildFile>(value);
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
                this.InnerObject.Targets = UnWrapList< ProjectTargetElementWrapper , ProjectTargetElement>( value);
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
