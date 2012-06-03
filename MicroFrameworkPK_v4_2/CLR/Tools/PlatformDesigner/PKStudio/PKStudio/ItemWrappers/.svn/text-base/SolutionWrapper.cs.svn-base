using System;
using System.Collections.Generic;
using System.ComponentModel;
using XsdInventoryFormatObject;
using PKStudio.Tree.Nodes;
using PKStudio.ItemWrappers.Converters;
using System.Collections.ObjectModel;
using System.IO;

namespace PKStudio.ItemWrappers
{
    [DefaultProperty("Name"), Serializable]
    public class SolutionWrapper : BaseTypedWrapper<MFSolution>, IName, IGuid, IVersion, IProjectPath
    {
        private SolutionWrapper(MFSolution solution)
            : base(solution)
        {
        }

        protected override BaseNode OnGetTreeNode(Tree.Nodes.BaseNode parent)
        {
            return new SolutionNode(this, parent);
        }
        
        [Category("General")]
        public string Author
        {
            get
            {
                return this.InnerObject.Author;
            }
            set
            {
                this.InnerObject.Author = value;
            }
        }

        [Category("General")]
        [TypeConverter(typeof(ExpandableObjectConverterEx))]
        public BuildToolRefWrapper BuildTool
        {
            get
            {
                if (this.InnerObject.BuildTool != null)
                    return BaseWrapper.Wrap < BuildToolRefWrapper >(this.InnerObject.BuildTool);
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
        public string DebuggerPort
        {
            get
            {
                return this.InnerObject.DebuggerPort;
            }
            set
            {
                this.InnerObject.DebuggerPort = value;
            }
        }

        [Category("General")]
        [TypeConverter(typeof(ExpandableObjectConverterEx))]
        public ComponentWrapper DefaultISA
        {
            get
            {
                if (this.InnerObject.DefaultISA != null)
                    return BaseWrapper.Wrap < ComponentWrapper >(this.InnerObject.DefaultISA);
                else
                    return null;
            }
            set
            {
                if (value != null)
                    this.InnerObject.DefaultISA = value.InnerObject;
                else
                    this.InnerObject.DefaultISA = null;
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
        public string ENDIANNESS
        {
            get
            {
                return this.InnerObject.ENDIANNESS;
            }
            set
            {
                this.InnerObject.ENDIANNESS = value;
            }
        }

        [Category("General")]
        [TypeConverter(typeof(UInt32HexTypeConverter))]
        public int FlashBase
        {
            get
            {
                return this.InnerObject.FlashBase;
            }
            set
            {
                this.InnerObject.FlashBase = value;
            }
        }

        [Category("General")]
        [TypeConverter(typeof(UInt32HexTypeConverter))]
        public int FlashLength
        {
            get
            {
                return this.InnerObject.FlashLength;
            }
            set
            {
                this.InnerObject.FlashLength = value;
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
        [TypeConverter(typeof(ExpandableCollectionConverter<BuildFileWrapper, MFBuildFile>))]
        public CollectionWrapper<BuildFileWrapper, MFBuildFile> Items
        {
            get
            {
                return WrapList<BuildFileWrapper, MFBuildFile>(this.InnerObject.Items);
            }
            set
            {
                this.InnerObject.Items = UnWrapList<BuildFileWrapper, MFBuildFile>(value);
            }
        }

        [Category("General")]
        public string MemoryProfile
        {
            get
            {
                return this.InnerObject.MemoryProfile;
            }
            set
            {
                this.InnerObject.MemoryProfile = value;
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
        public ComponentWrapper Processor
        {
            get
            {
                if (this.InnerObject.Processor != null)
                    return BaseWrapper.Wrap < ComponentWrapper >(this.InnerObject.Processor);
                else
                    return null;
            }
            set
            {
                if (value != null)
                    this.InnerObject.Processor = value.InnerObject;
                else
                    this.InnerObject.Processor = null;
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
        [TypeConverter(typeof(ExpandableCollectionConverter<ProjectWrapper, MFProject>))]
        public CollectionWrapper<ProjectWrapper, MFProject> Projects
        {
            get
            {
                return WrapList<ProjectWrapper, MFProject>(this.InnerObject.Projects);
            }
            set
            {
                this.InnerObject.Projects = UnWrapList<ProjectWrapper, MFProject>(value);
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
        [TypeConverter(typeof(UInt32HexTypeConverter))]
        public int RamBase
        {
            get
            {
                return this.InnerObject.RamBase;
            }
            set
            {
                this.InnerObject.RamBase = value;
            }
        }

        [Category("General")]
        [TypeConverter(typeof(UInt32HexTypeConverter))]
        public int RamLength
        {
            get
            {
                return this.InnerObject.RamLength;
            }
            set
            {
                this.InnerObject.RamLength = value;
            }
        }

        [Category("General")]
        public int SlowClockSpeed
        {
            get
            {
                return this.InnerObject.SlowClockSpeed;
            }
            set
            {
                this.InnerObject.SlowClockSpeed = value;
            }
        }

        [Category("General")]
        public int SystemClockSpeed
        {
            get
            {
                return this.InnerObject.SystemClockSpeed;
            }
            set
            {
                this.InnerObject.SystemClockSpeed = value;
            }
        }

        [Category("General")]
        [TypeConverter(typeof(ExpandableObjectConverterEx))]
        public LibraryCategoryWrapper TransportType
        {
            get
            {
                if (this.InnerObject.TransportType != null)
                    return BaseWrapper.Wrap < LibraryCategoryWrapper >(this.InnerObject.TransportType);
                else
                    return null;
            }
            set
            {
                if (value != null)
                    this.InnerObject.TransportType = value.InnerObject;
                else
                    this.InnerObject.TransportType = null;
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

        private Collection<BuildFileWrapper> _headerFiles;
        [Category("Files")]
        [TypeConverter(typeof(ExpandableCollectionConverter<BuildFileWrapper, MFBuildFile>))]
        public Collection<BuildFileWrapper> HeaderFiles
        {
            get
            {
                if (this._headerFiles == null)
                {
                    this._headerFiles = new Collection<BuildFileWrapper>();
                    MFBuildFile platform_selector = new MFBuildFile();
                    platform_selector.File = Path.Combine(Path.GetDirectoryName(this.ProjectPath), "platform_selector.h");
                    platform_selector.ItemName = "platform_selector.h";
                    this._headerFiles.Add(BaseWrapper.Wrap<BuildFileWrapper>(platform_selector));
                }
                return this._headerFiles;
            }
            set
            {
            }
        }

        public bool IsReference(LibraryWrapper library)
        {
            string libpath = Path.GetDirectoryName(PK.Wrapper.ExpandPath(library.ProjectPath));
            string projpath = Path.GetDirectoryName(PK.Wrapper.ExpandPath(this.ProjectPath));
            return !libpath.StartsWith(projpath, StringComparison.OrdinalIgnoreCase);
        }
    
    }
}
