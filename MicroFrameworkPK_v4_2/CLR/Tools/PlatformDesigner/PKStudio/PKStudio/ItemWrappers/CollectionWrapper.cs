using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections;
using System.Collections.ObjectModel;
using System.Reflection;
using System.Diagnostics;

namespace PKStudio.ItemWrappers
{
    public class CollectionWrapper<W, L> : ICollection<W> , IList<W> where W: BaseTypedWrapper<L>
    {
        private IList<L> InnerList;


        private CollectionWrapper(L[] list)
            : this(new List<L>(list))
        {
        }

        private CollectionWrapper(IList<L> list)
        {
            this.InnerList = list;
            foreach (L item in InnerList)
            {
                BaseWrapper.Wrap<W>(item);
            }
        }

        public CollectionWrapper(IList<W> list)
        {
            this.InnerList = new List<L>();
            foreach (W item in list)
            {
                this.InnerList.Add(item.InnerObject);
            }
        }

        private CollectionWrapper(Collection<W> list)
            : this(new List<W>(list))
        {
        }

        public static implicit operator CollectionWrapper<W, L>(Collection<W> list)
        {
            return new CollectionWrapper<W, L>(list);
        }

        public static implicit operator Collection<W> (CollectionWrapper<W, L> list)
        {
            return new Collection<W>(list);
        }

        public void Add(W item)
        {
            this.InnerList.Add(item.InnerObject);
        }

        public void Clear()
        {
            this.InnerList.Clear();
        }

        public void CopyTo(W[] array, int arrayIndex)
        {
            List<W> copyList = new List<W>();
            foreach (L item in this.InnerList)
            {
                copyList.Add(BaseWrapper.Wrap<W>(item));
            }
            copyList.CopyTo(array, arrayIndex);
        }

        public int Count
        {
            get
            {
                return this.InnerList.Count;
            }
        }

        public bool IsReadOnly
        {
            get
            {
                return this.InnerList.IsReadOnly;
            }
        }

        public bool Remove(W item)
        {
            return this.InnerList.Remove(item.InnerObject);
        }


        public IEnumerator<W> GetEnumerator()
        {
            foreach (L item in this.InnerList)
            {
                yield return BaseWrapper.Wrap<W>(item);
            }
        }


        IEnumerator IEnumerable.GetEnumerator()
        {
            return this.GetEnumerator();
        }


        public bool Contains(W item)
        {
            return this.InnerList.Contains(item.InnerObject);
        }


        public int IndexOf(W item)
        {
            return this.InnerList.IndexOf(item.InnerObject);
        }

        public void Insert(int index, W item)
        {
            this.InnerList.Insert(index, item.InnerObject);
        }

        public void RemoveAt(int index)
        {
            this.InnerList.RemoveAt(index);
        }

        public W this[int index]
        {
            get
            {
                return BaseWrapper.Wrap<W>( this.InnerList[index]);
            }
            set
            {
                if (value != null)
                    this.InnerList[index] = value.InnerObject;
                else
                    this.InnerList[index] = default(L);
            }
        }

    }
}
