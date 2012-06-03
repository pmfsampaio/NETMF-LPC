using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections;

namespace PKParser.Arg
{
    public class TypedDictionary<K, T> : DictionaryBase
    {
        public string Name { get; private set; }

        public TypedDictionary(string Name)
        {
            this.Name = Name;
        }

               public T this[K key]
        {
            get { return (T)this.Dictionary[key]; }

            set { this.Dictionary[key] = value; }
        }
        public T Add(K key, T value)
        {
            if (!this.Contains(key))
            {
                this.Dictionary.Add(key, value);
            }
            return (T)this.Dictionary[key];
        }

        public bool TryGetValue(K key, out T value)
        {
            value = (T)this.Dictionary[key];
            return value != null;

        }

        public bool Contains(K key)
        {
            return this.Dictionary.Contains(key);
        }

        public ICollection Keys
        {
            get { return this.Dictionary.Keys; }
        }

        public ICollection Values
        {
            get { return this.Dictionary.Values; }
        }
    }
}
