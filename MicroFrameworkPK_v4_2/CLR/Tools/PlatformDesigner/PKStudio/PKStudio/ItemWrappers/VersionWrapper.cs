using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;

namespace PKStudio.ItemWrappers
{
    [DefaultProperty("Version"), Serializable]
    public class VersionWrapper : BaseTypedWrapper<XsdInventoryFormatObject.Version>
    {
        private VersionWrapper(XsdInventoryFormatObject.Version version)
            : base(version)
        {
        }

        [Browsable(false)]
        public string Version
        {
            get
            {
                return string.Format("{0}.{1}.{2}.{3} {4}", this.Major, this.Minor, this.Build, this.Revision, this.Date);
            }
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
        public string Build
        {
            get
            {
                return this.InnerObject.Build;
            }
            set
            {
                this.InnerObject.Build = value;
            }
        }

        [Category("General")]
        public DateTime Date
        {
            get
            {
                return this.InnerObject.Date;
            }
            set
            {
                this.InnerObject.Date = value;
            }
        }

        [Category("General")]
        public string Extra
        {
            get
            {
                return this.InnerObject.Extra;
            }
            set
            {
                this.InnerObject.Extra = value;
            }
        }

        [Category("General")]
        public string Major
        {
            get
            {
                return this.InnerObject.Major;
            }
            set
            {
                this.InnerObject.Major = value;
            }
        }

        [Category("General")]
        public string Minor
        {
            get
            {
                return this.InnerObject.Minor;
            }
            set
            {
                this.InnerObject.Minor = value;
            }
        }

        [Category("General")]
        public string Revision
        {
            get
            {
                return this.InnerObject.Revision;
            }
            set
            {
                this.InnerObject.Revision = value;
            }
        }
    }
}
