using System;
using System.ComponentModel;
using XsdInventoryFormatObject;

namespace PKStudio.ItemWrappers
{
    [Serializable]
    [DefaultProperty("FilePath")]
    public class ApiTemplateWrapper : BaseTypedWrapper<ApiTemplate>
    {
        private ApiTemplateWrapper(ApiTemplate template)
            : base(template)
        {
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
        public string FilePath
        {
            get
            {
                return this.InnerObject.FilePath;
            }
            set
            {
                this.InnerObject.FilePath = value;
            }
        }
    }
}
