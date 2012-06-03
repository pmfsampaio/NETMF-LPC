using System;
using System.ComponentModel;
using XsdInventoryFormatObject;
using PKStudio.ItemWrappers.Converters;
using PKStudio.Tree.Nodes;

namespace PKStudio.ItemWrappers
{
    [DefaultProperty("Name"), Serializable]
    public class BuildToolRefWrapper : BaseTypedWrapper<BuildToolRef>, IGuid , IName
    {
        private BuildToolRefWrapper(BuildToolRef tool_ref)
            : base(tool_ref)
        {
        }

        protected override BaseNode OnGetTreeNode(Tree.Nodes.BaseNode parent)
        {
            return new BuildToolRefNode(this, parent);
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

    }
}
