using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace PKParser.Arg
{
    public class ParamCollection : TypedDictionary<string, ArgCollection>
    {
        public ParamCollection(string Name)
            : base(Name)
        {
            this.Files = new Dictionary<int, string>();
        }
        public Dictionary<int, string> Files { get; private set; }

    }
}
