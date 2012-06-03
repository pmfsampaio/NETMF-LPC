using System;
using System.Collections.Generic;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;
using System.Xml.Serialization;
using System.Text;

namespace OptionsHelper.Options
{
    [Serializable]
    public class OptionsSerializer
    {
        public OptionsSerializer()
        {
            
        }
        private List<OptionsBase> mSOptions = null;

        public void SaveState(string path)
        {
            BinaryFormatter bf = new BinaryFormatter();
            using (FileStream fs = new FileStream(path, FileMode.Create, FileAccess.Write))
            {
                bf.Serialize(fs, this);
            }
        }

        static public OptionsSerializer BackState(string path)
        {
            BinaryFormatter bf = new BinaryFormatter();
            OptionsSerializer os = null;
            using (FileStream fs = new FileStream(path, FileMode.Open, FileAccess.Read))
            {
                os = bf.Deserialize(fs) as OptionsSerializer; 
            }
            return os;
        }

        public List<OptionsBase> SOptions
        {
            get
            {
                if (this.mSOptions == null)
                    this.mSOptions = new List<OptionsBase>();
                return this.mSOptions;
            }
        }
    }
}
