using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace PKStudio.Forms.Options.Options
{
    [Serializable]
    public class PKVer : Object
    {
        public PKVer(string name, string path)
        {
            this.Name = name;
            this.Path = path;
        }
        public string Name { get; set; }
        public string Path { get; set; }

        public override string ToString()
        {
            return Name;
        }
        public override bool Equals(object obj)
        {
            if (obj is PKVer)
            {
                PKVer ver = obj as PKVer;
                if(ver == null) return false;

                if (this.Name != ver.Name) return false;
                if (this.Path != ver.Path) return false;
                return true;
            }
            else return base.Equals(obj);
        }
        public override int GetHashCode()
        {
            return base.GetHashCode();
        }
    }

    [Serializable]
    public class PKVersionOption : OptionsHelper.Options.OptionsBase
    {
        PKVer _PKVersion;

        public PKVer PKVersion { get { return this._PKVersion; } set { this._PKVersion = value; } }

        public override void OnInitialized()
        {
            
        }

        public override bool OnApplyChanges()
        {
            return true;
        }
    }
}
