using System;
using System.ComponentModel;
using XsdInventoryFormatObject;
using PKStudio.ItemWrappers.Converters;
using PKStudio.Tree.Nodes;
using System.Diagnostics;
using System.Text;

namespace PKStudio.ItemWrappers
{
    [DefaultProperty("Name"), Serializable]
    public class ComponentWrapper : BaseTypedWrapper<MFComponent> , IName, IGuid, IConditional, IGroups, IChecked, IProjectPath
    {
        private ComponentWrapper(MFComponent component)
            : base(component)
        {
        }

        protected override BaseNode OnGetTreeNode(BaseNode parent)
        {
            return new ComponentNode(this, parent);
        }

        public static ComponentWrapper GetComponentWrapper(BaseWrapper wrapper)
        {
            if (wrapper is FeatureWrapper)
                return GetComponentWrapper(wrapper as FeatureWrapper);
            if (wrapper is LibraryWrapper)
                return GetComponentWrapper(wrapper as LibraryWrapper);
            if (wrapper is LibraryCategoryWrapper)
                return GetComponentWrapper(wrapper as LibraryCategoryWrapper);
            if (wrapper is ProcessorWrapper)
                return GetComponentWrapper(wrapper as ProcessorWrapper);
            else
            {
                Debug.Assert(false);
                return null;
            }
        }


        public static ComponentWrapper GetComponentWrapper(ComponentTypeWrapper type)
        {
            return BaseWrapper.Wrap<ComponentWrapper>(new MFComponent((MFComponentType)type));
        }

        public static ComponentWrapper GetComponentWrapper(FeatureWrapper feature)
        {
            return GetComponentWrapper(feature, ComponentTypeWrapper.Feature);
        }

        public static ComponentWrapper GetComponentWrapper(LibraryCategoryWrapper librarycat)
        {
            return GetComponentWrapper(librarycat, ComponentTypeWrapper.LibraryCategory);
        }

        public static ComponentWrapper GetComponentWrapper(LibraryWrapper lib)
        {
            return GetComponentWrapper(lib, ComponentTypeWrapper.Library);
        }

        public static ComponentWrapper GetComponentWrapper(ProcessorWrapper proc)
        {
            return GetComponentWrapper(proc, ComponentTypeWrapper.Processor);
        }

        public static ComponentWrapper GetComponentWrapper(SolutionWrapper solution)
        {
            return GetComponentWrapper(solution, ComponentTypeWrapper.MFSolution);
        }

        public static ComponentWrapper GetComponentWrapper(AssemblyWrapper assembly)
        {
            return GetComponentWrapper(assembly, ComponentTypeWrapper.MFAssembly);
        }

        public static ComponentWrapper GetComponentWrapper(BuildToolWrapper_ buildTool)
        {
            return GetComponentWrapper(buildTool, ComponentTypeWrapper.BuildTool);
        }

        public static ComponentWrapper GetComponentWrapper(ISAWrapper isa)
        {
            return GetComponentWrapper(isa, ComponentTypeWrapper.ISA);
        }

        public static ComponentWrapper GetComponentWrapper(ProjectWrapper project)
        {
            return GetComponentWrapper(project, ComponentTypeWrapper.Unknown);
        }

        public static void Copy(ComponentWrapper dst, ComponentWrapper src)
        {
            dst.Checked = src.Checked;
            dst.Conditional = src.Conditional;
        }

        public static ComponentWrapper GetComponentWrapper(BaseWrapper wrapper, ComponentTypeWrapper type)
        {
            ComponentWrapper component = BaseWrapper.Wrap<ComponentWrapper>(new MFComponent((MFComponentType)type, wrapper.InnerName, wrapper.InnerGuid, wrapper.InnerProjectPath, wrapper.InnerConditional));
            component.Groups = wrapper.InnerGroups;
            component.InnerComponentType = wrapper.GetType();
            return component;
        }
        
        public bool IsSameGuid(string guid)
        {
            return (string.Compare(this.Guid, guid, true) == 0);
        }

        public bool IsSameGuid(object obj)
        {
            IGuid component = obj as IGuid;
            return ((component != null) && (IsSameGuid(component.Guid) == true));
        }
        
        public override bool Equals(object obj)
        {
            ComponentWrapper component = obj as ComponentWrapper;
            return ((component != null) && (IsSameGuid(component.Guid) == true));
        }

        public override int GetHashCode()
        {
            return base.GetHashCode();
        }

        [Category("General")]
        [TypeConverter(typeof(ExpandableObjectConverterEx))]
        public ComponentTypeWrapper ComponentType
        {
            get
            {
                return (ComponentTypeWrapper)this.InnerObject.ComponentType;
            }
            set
            {
                this.InnerObject.ComponentType = (MFComponentType)value;
            }
        }

        [Browsable(false)]
        public Type InnerComponentType { get; private set; }

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
        public int RefCount
        {
            get
            {
                return this.InnerObject.RefCount;
            }
            set
            {
                this.InnerObject.RefCount = value;
            }
        }

        [Category("General")]
        public bool RefCountSpecified
        {
            get
            {
                return this.InnerObject.RefCountSpecified;
            }
            set
            {
                this.InnerObject.RefCountSpecified = value;
            }
        }

        [Category("General")]
        [TypeConverter(typeof(ExpandableObjectConverterEx))]
        public VersionWrapper VersionDependency
        {
            get
            {
                if (this.InnerObject.VersionDependency != null)
                    return BaseWrapper.Wrap < VersionWrapper >(this.InnerObject.VersionDependency);
                else
                    return null;
            }
            set
            {
                if (value != null)
                    this.InnerObject.VersionDependency = value.InnerObject;
                else
                    this.InnerObject.VersionDependency = null;
            }
        }

        [Category("General")]
        public string Groups { get; set; }


        private bool _checked = false;
        [Browsable(false)]
        public bool Checked
        {
            get
            {
                return this._checked;
            }
            set
            {
                bool notify = this._checked != value;
                this._checked = value;
                if (notify == true)
                {
                    OnPropertyChange("Checked");
                }
            }
        }

        [Browsable(false)]
        public string BriefDescription
        {
            get
            {
                BaseWrapper wrapper = this;
                StringBuilder sb = new StringBuilder();
                switch (this.ComponentType)
                {
                    case ComponentTypeWrapper.Library:
                        sb.Append("Library\r\n");
                        wrapper = PK.Wrapper.FindLibrary(this);
                        break;
                    case ComponentTypeWrapper.LibraryCategory:
                        sb.Append("LibraryCategory\r\n");
                        wrapper = PK.Wrapper.FindLibraryCategory(this.Guid);
                        break;
                    case ComponentTypeWrapper.Feature:
                        sb.Append("Feature\r\n");
                        wrapper = PK.Wrapper.FindFeature(this.Guid);
                        break;
                    case ComponentTypeWrapper.MFAssembly:
                    case ComponentTypeWrapper.MFSolution:
                    case ComponentTypeWrapper.Processor:
                    case ComponentTypeWrapper.OperatingSystem:
                    case ComponentTypeWrapper.BuildTool:
                    case ComponentTypeWrapper.ISA:
                    case ComponentTypeWrapper.BuildParameter:
                    case ComponentTypeWrapper.Unknown:
                    default:
                        sb.AppendFormat("ComponentType       : {0}\r\n", this.ComponentType);
                    break;
                }
                if (wrapper != null)
                {
                    sb.AppendFormat("Name              : {0}\r\n", wrapper.InnerName);
                    sb.AppendFormat("Description       : {0}\r\n", wrapper.InnerDescription);
                    sb.AppendFormat("Documentation     : {0}\r\n", wrapper.InnerDocumentation);
                    sb.AppendFormat("Groups            : {0}\r\n", wrapper.InnerGroups);
                    sb.AppendFormat("Guid              : {0}\r\n", wrapper.InnerGuid);
                    sb.AppendFormat("ProjectPath       : {0}\r\n", wrapper.InnerProjectPath);
                }
                return sb.ToString();
            }
        }

    }
}
