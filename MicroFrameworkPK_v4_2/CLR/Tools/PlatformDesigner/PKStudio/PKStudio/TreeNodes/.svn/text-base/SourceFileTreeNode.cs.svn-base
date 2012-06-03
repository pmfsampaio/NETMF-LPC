using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Diagnostics;
using PKStudio.ItemWrappers;

namespace PKStudio.TreeNodes
{
    class MFSourceFileTreeNode : MFTreeNodeBase
    {
        public MFSourceFileTreeNode()
        {
        }
        static Dictionary<int, ImageKeysEnum> extentions = new Dictionary<int, ImageKeysEnum> { 
                { ".cpp".ToUpperInvariant().GetHashCode(), ImageKeysEnum.CPP } 
              , { ".c".ToUpperInvariant().GetHashCode(), ImageKeysEnum.C } 
              , { ".h".ToUpperInvariant().GetHashCode(), ImageKeysEnum.Header } 
              , { ".cs".ToUpperInvariant().GetHashCode(), ImageKeysEnum.CS } 
              , { ".s".ToUpperInvariant().GetHashCode(), ImageKeysEnum.Asm } 
        };

        public static ImageKeysEnum FileName2ImageKey(BuildFileWrapper BuildFile)
        {
            ImageKeysEnum key = FileName2ImageKey(BuildFile.File);

            if (!File.Exists(BuildFile.FullPath))
            {
                Debug.WriteLine(string.Format ("MFSourceFileTreeNode: \"File {0} not exists\"", BuildFile.FullPath));
                key = ImageKeysEnum.Missing;
            }

            return key;
        }
        
        public static ImageKeysEnum FileName2ImageKey(string file)
        {
            ImageKeysEnum key;

            try
            {
                if (!extentions.TryGetValue(Path.GetExtension(file).ToUpperInvariant().GetHashCode(), out key))
                    key = ImageKeysEnum.Unknown;
            }
            catch (Exception)
            {
                key = ImageKeysEnum.Unknown;
            }

            return key;
        }

        public BuildFileWrapper BuildFile { get; private set; }

        public MFSourceFileTreeNode(BuildFileWrapper BuildFile)
            : base(Path.GetFileName(BuildFile.File), FileName2ImageKey(BuildFile))
        {
            this.BuildFile = BuildFile;
            this.Tag = BuildFile;
        }
    }
}
