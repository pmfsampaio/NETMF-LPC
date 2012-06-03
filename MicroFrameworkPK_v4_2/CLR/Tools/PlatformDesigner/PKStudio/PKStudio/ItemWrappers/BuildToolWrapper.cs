using System;
using System.Collections.Generic;
using System.ComponentModel;
using XsdInventoryFormatObject;
using PKStudio.ItemWrappers.Converters;
using System.Collections.ObjectModel;

namespace PKStudio.ItemWrappers
{
    [DefaultProperty("Name"), Serializable]
    public class BuildToolWrapper_ : BaseTypedWrapper<BuildTool>, IGuid, IName, IVersion, IProjectPath
    {
        private BuildToolWrapper_(BuildTool tool)
            : base(tool)
        {
        }
        [Category("General")]
        [TypeConverter(typeof(ExpandableObjectConverterEx))]
        public BuildToolDefineWrapper Archiver
        {
            get
            {
                if (this.InnerObject.Archiver != null)
                    return BaseWrapper.Wrap < BuildToolDefineWrapper >(this.InnerObject.Archiver);
                else
                    return null;
            }
            set
            {
                if (value != null)
                    this.InnerObject.Archiver = value.InnerObject;
                else
                    this.InnerObject.Archiver = null;
            }
        }

        [Category("General")]
        [TypeConverter(typeof(ExpandableObjectConverterEx))]
        public BuildToolDefineWrapper AsmCompiler
        {
            get
            {
                if (this.InnerObject.AsmCompiler != null)
                    return BaseWrapper.Wrap < BuildToolDefineWrapper >(this.InnerObject.AsmCompiler);
                else
                    return null;
            }
            set
            {
                if (value != null)
                    this.InnerObject.AsmCompiler = value.InnerObject;
                else
                    this.InnerObject.AsmCompiler = null;

            }
        }

        [Category("General")]
        public string BinExt
        {
            get
            {
                return this.InnerObject.BinExt;
            }
            set
            {
                this.InnerObject.BinExt = value;
            }
        }

        [Category("General")]
        [TypeConverter(typeof(ExpandableObjectConverterEx))]
        public ToolChainOptionsWrapper BuildOptions
        {
            get
            {
                if (this.InnerObject.BuildOptions != null)
                    return BaseWrapper.Wrap < ToolChainOptionsWrapper >(this.InnerObject.BuildOptions);
                else
                    return null;
            }
            set
            {
                if (value != null)
                    this.InnerObject.BuildOptions = value.InnerObject;
                else
                    this.InnerObject.BuildOptions = null;

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
        [TypeConverter(typeof(ExpandableObjectConverterEx))]
        public BuildToolDefineWrapper CCompiler
        {
            get
            {
                if (this.InnerObject.CCompiler != null)
                    return BaseWrapper.Wrap < BuildToolDefineWrapper >(this.InnerObject.CCompiler);
                else
                    return null;
            }
            set
            {
                if (value != null)
                    this.InnerObject.CCompiler = value.InnerObject;
                else
                    this.InnerObject.CCompiler = null;
            }
        }

        [Category("General")]
        [TypeConverter(typeof(ExpandableObjectConverterEx))]
        public BuildToolDefineWrapper CppCompiler
        {
            get
            {
                if (this.InnerObject.CppCompiler != null)
                    return BaseWrapper.Wrap < BuildToolDefineWrapper >(this.InnerObject.CppCompiler);
                else
                    return null;
            }
            set
            {
                if (value != null)
                    this.InnerObject.CppCompiler = value.InnerObject;
                else
                    this.InnerObject.CppCompiler = null;
            }
        }

        [Category("General")]
        public string DbgExt
        {
            get
            {
                return this.InnerObject.DbgExt;
            }
            set
            {
                this.InnerObject.DbgExt = value;
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
        public BuildToolDefineWrapper FromELF
        {
            get
            {
                if (this.InnerObject.FromELF != null)
                    return BaseWrapper.Wrap < BuildToolDefineWrapper >(this.InnerObject.FromELF);
                else
                    return null;
            }
            set
            {
                if (value != null)
                    this.InnerObject.FromELF = value.InnerObject;
                else
                    this.InnerObject.FromELF = null;
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
        [TypeConverter(typeof(ExpandableCollectionConverter<PropertyWrapper, MFProperty>))]
        public CollectionWrapper<PropertyWrapper, MFProperty> Items
        {
            get
            {
                return WrapList<PropertyWrapper, MFProperty>(this.InnerObject.Items);
            }
            set
            {
                this.InnerObject.Items = UnWrapList<PropertyWrapper, MFProperty>(value);
            }
        }

        [Category("General")]
        public string LibExt
        {
            get
            {
                return this.InnerObject.LibExt;
            }
            set
            {
                this.InnerObject.LibExt = value;
            }
        }

        [Category("General")]
        [TypeConverter(typeof(ExpandableObjectConverterEx))]
        public BuildToolDefineWrapper Linker
        {
            get
            {
                if (this.InnerObject.Linker != null)
                    return BaseWrapper.Wrap < BuildToolDefineWrapper >(this.InnerObject.Linker);
                else
                    return null;
            }
            set
            {
                if (value != null)
                    this.InnerObject.Linker = value.InnerObject;
                else
                    this.InnerObject.Linker = null;
            }
        }

        [Category("General")]
        [TypeConverter(typeof(ExpandableCollectionConverter<MiscBuildToolWrapper, MiscBuildTool>))]
        public CollectionWrapper<MiscBuildToolWrapper, MiscBuildTool> MiscTools
        {
            get
            {
                return WrapList<MiscBuildToolWrapper, MiscBuildTool>(this.InnerObject.MiscTools);
            }
            set
            {
                this.InnerObject.MiscTools = UnWrapList<MiscBuildToolWrapper, MiscBuildTool>(value);
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
        public string ObjExt
        {
            get
            {
                return this.InnerObject.ObjExt;
            }
            set
            {
                this.InnerObject.ObjExt = value;
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
        [TypeConverter(typeof(ExpandableCollectionConverter<string>))]
        public Collection<string> SupportedCpuNames
        {
            get
            {
                return new Collection<string>(this.InnerObject.SupportedCpuNames);
            }
            set
            {
                this.InnerObject.SupportedCpuNames = new List<string>(value);
            }
        }

        [Category("General")]
        [TypeConverter(typeof(ExpandableCollectionConverter<ISAWrapper, ISA>))]
        public CollectionWrapper<ISAWrapper, ISA> SupportedISAs
        {
            get
            {
                return WrapList<ISAWrapper, ISA>(this.InnerObject.SupportedISAs);
            }
            set
            {
                this.InnerObject.SupportedISAs = UnWrapList<ISAWrapper, ISA>(value);
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
