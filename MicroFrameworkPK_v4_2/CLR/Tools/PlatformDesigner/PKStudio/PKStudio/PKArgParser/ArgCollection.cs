using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections;

namespace PKParser.Arg
{
    public class ArgCollection : TypedCollection<string>
    {
        public ArgCollection(string Name, string Tag)
            : base(Name)
        {
            this.Tag = Tag;
        }
        public string Tag { get; private set; }
    }
}
