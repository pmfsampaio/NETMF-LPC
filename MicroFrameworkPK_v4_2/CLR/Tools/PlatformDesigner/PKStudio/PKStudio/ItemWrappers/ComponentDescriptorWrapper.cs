using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ComponentObjectModel;
using System.ComponentModel;
using XsdInventoryFormatObject;
using PKStudio.ItemWrappers.Converters;
using PKStudio.Tree.Nodes;
using System.Drawing;

namespace PKStudio.ItemWrappers
{
    [DefaultProperty("Description"), Serializable]
    public class ComponentDescriptorWrapper : BaseTypedWrapper<MFComponentDescriptor>, IName, IProjectPath
    {
        private ComponentDescriptorWrapper(MFComponentDescriptor descriptor)
            : base(descriptor)
        {
        }

        protected override BaseNode OnGetTreeNode(BaseNode parent)
        {
            return new ComponentDescriptorNode(this, parent);
        }
        
        [Category("General")]
        [TypeConverter(typeof(ExpandableObjectConverterEx))]
        public ComponentWrapper Component
        {
            get
            {
                if (this.InnerObject.Component != null)
                    return BaseWrapper.Wrap < ComponentWrapper >(this.InnerObject.Component);
                else
                    return null;
            }
        }
        [Category("General")]
        public string Description
        {
            get
            {
                return this.InnerObject.Description;
            }
        }
        [Category("General")]
        public string Documentation
        {
            get
            {
                return this.InnerObject.Documentation;
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
            }
        }
        [Category("General")]
        [TypeConverter(typeof(ExpandableObjectConverterEx))]
        public ProcessorWrapper SolutionProcessor
        {
            get
            {
                if (this.InnerObject.SolutionProcessor != null)
                    return BaseWrapper.Wrap < ProcessorWrapper >( this.InnerObject.SolutionProcessor);
                else
                    return null;
            }
        }


        #region IName Members
        [Browsable(false)]
        public string Name
        {
            get
            {
                return this.InnerObject.Component.Name;
            }
            set
            {
                this.InnerObject.Component.Name = value;
            }
        }

        #endregion
    }
}
