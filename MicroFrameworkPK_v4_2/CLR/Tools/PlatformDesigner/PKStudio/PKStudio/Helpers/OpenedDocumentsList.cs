using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using XsdInventoryFormatObject;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;

namespace PKStudio.Helpers
{
    /// <summary>
    /// Класс, солержащий открытие для редоктирования документы.
    /// </summary>
    /// <remarks>Сериализуемый класс, который используется при загрузче, чтобы узнать, какие компоненты были открыты для редактирования</remarks>
    [Serializable]
    class OpenedDocumentsList
    {
        private List<string> _files = new List<string>();
        private List<MFComponent> _components = new List<MFComponent>();

        /// <summary>
        /// Список открытых для редактировани файлов
        /// </summary>
        public List<string> Files { get { return _files;} }
        /// <summary>
        /// Cписок открытых для редактирования компонентов
        /// </summary>
        public List<MFComponent> Components { get { return _components; } }



        public void Serialize(OpenedDocumentsList list, string path)
        {
            BinaryFormatter sf = new BinaryFormatter();
            FileStream fs = new FileStream
               (path, FileMode.Create, FileAccess.Write);
            sf.Serialize(fs, list);
            fs.Close();
        }
        public OpenedDocumentsList Deserialize(string path)
        {
            BinaryFormatter sf = new BinaryFormatter();
            FileStream fs = new FileStream(path, FileMode.Open, FileAccess.Read);
            OpenedDocumentsList e = (OpenedDocumentsList)sf.Deserialize(fs);
            fs.Close();
            return e;
        }
    }
}
