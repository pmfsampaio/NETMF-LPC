using System;
using System.Collections.Generic;
using System.ComponentModel;
using PKStudio.ItemWrappers.Converters;
using XsdInventoryFormatObject;
using System.Collections.ObjectModel;
using PKStudio.Tree.Nodes;

namespace PKStudio.ItemWrappers
{
    [Serializable]
    [DefaultProperty("Name")]
    public class LibraryCategoryWrapper : BaseTypedWrapper<LibraryCategory>, IName, IGroups, IGuid, IVersion, IProjectPath, IDescription, IDocumentation
    {
        private LibraryCategoryWrapper(LibraryCategory libCat)
            :base(libCat)
        {
        }

        protected override BaseNode OnGetTreeNode(BaseNode parent)
        {
            return new LibraryCategoryNode(this, parent);
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
        [TypeConverter(typeof(ExpandableCollectionConverter<ComponentWrapper, MFComponent>))]
        public CollectionWrapper<ComponentWrapper, MFComponent> FeatureAssociations
        {
            get
            {
                return WrapList<ComponentWrapper, MFComponent>(this.InnerObject.FeatureAssociations);
            }
            set
            {
                this.InnerObject.FeatureAssociations = UnWrapList<ComponentWrapper, MFComponent>(value);
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

        [Category("General")]
        public bool IsTransport
        {
            get
            {
                return this.InnerObject.IsTransport;
            }
            set
            {
                this.InnerObject.IsTransport = value;
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
        [TypeConverter(typeof(ExpandableCollectionConverter<string>))]
        public Collection<string> LibraryProjCache
        {
            get
            {
                return new Collection<string>(this.InnerObject.LibraryProjCache);
            }
            set
            {
                this.InnerObject.LibraryProjCache = new List<string>(value);
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
        [TypeConverter(typeof(ExpandableObjectConverterEx))]
        public ComponentWrapper StubLibrary
        {
            get
            {
                if (this.InnerObject.StubLibrary != null)
                    return BaseWrapper.Wrap < ComponentWrapper >(this.InnerObject.StubLibrary);
                else
                    return null;
            }
            set
            {
                if (value != null)
                    this.InnerObject.StubLibrary = value.InnerObject;
                else
                    this.InnerObject.StubLibrary = null;
            }
        }

        [Category("General")]
        [TypeConverter(typeof(ExpandableCollectionConverter<ApiTemplateWrapper, ApiTemplate>))]
        public CollectionWrapper<ApiTemplateWrapper, ApiTemplate> Templates
        {
            get
            {
                return WrapList<ApiTemplateWrapper, ApiTemplate>( this.InnerObject.Templates);
            }
            set
            {
                this.InnerObject.Templates = UnWrapList<ApiTemplateWrapper, ApiTemplate>( value);
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
