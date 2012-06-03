using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections;

namespace PKParser.Arg
{
    public class TypedCollection<T> : CollectionBase
    {

        protected TypedCollection(string Name)
        {
            this.Name = Name;
        }

        public string Name { get; private set; }


        public T this[int index]
        {
            get
            {
                return (T)this.List[index];
            }
            set
            {
                this.List[index] = (T)value;
            }
        }
        public int Add(T item)
        {
            return this.List.Add(item);
        }

        public bool Contains(T value)
        {
            return this.List.Contains(value);
        }
    }
}
