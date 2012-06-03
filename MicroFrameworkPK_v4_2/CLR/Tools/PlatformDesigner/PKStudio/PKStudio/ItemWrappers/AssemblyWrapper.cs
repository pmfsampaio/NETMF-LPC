using System;
using System.Collections.Generic;
using System.ComponentModel;
using XsdInventoryFormatObject;
using System.Collections.ObjectModel;
using PKStudio.Tree.Nodes;
using PKStudio.ItemWrappers.Converters;

namespace PKStudio.ItemWrappers
{
    [DefaultProperty("Name"), Serializable]
    public class AssemblyWrapper : BaseTypedWrapper<MFAssembly>, IName, IGroups, IGuid, IProjectPath
    {
        private AssemblyWrapper(MFAssembly assembly)
            : base(assembly)
        {
        }

        protected override BaseNode OnGetTreeNode(Tree.Nodes.BaseNode parent)
        {
            return new AssemblyNode(this, parent);
        }


        [Category("General")]
        public string AssemblyFile
        {
            get
            {
                return this.InnerObject.AssemblyFile;
            }
            set
            {
                this.InnerObject.AssemblyFile = value;
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
        [TypeConverter(typeof(ExpandableCollectionConverter<ComponentWrapper, MFComponent>))]
        public CollectionWrapper<ComponentWrapper, MFComponent> References
        {
            get
            {
                return WrapList<ComponentWrapper, MFComponent>(this.InnerObject.References);
            }
            set
            {
                this.InnerObject.References = UnWrapList<ComponentWrapper, MFComponent>(value);
            }
        }

    }
}
