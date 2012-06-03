using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections;
using System.Reflection;
using System.Diagnostics;

namespace PKStudio.ItemWrappers
{
    public class WeakCache : IEnumerable<object>
    {
        private Dictionary<WeakReference, WeakReference> _cache = new Dictionary<WeakReference, WeakReference>();

        private static ConstructorInfo GetConstructor<W>(Type obj_type)
        {
            ConstructorInfo ci = typeof(W).GetConstructor(BindingFlags.NonPublic | BindingFlags.Instance, null, new Type[] { obj_type }, null);
            Debug.Assert(ci != null);
            return ci;
        }

        public W Wrap<W>(object obj)
        {
            if (obj == null)
                return default(W);
            else
                return CreateWrapper<W>(obj);
        }

        private W CreateWrapper<W>(object obj)
        {
            return Add<W>(obj);
        }


        private W Add<W>(object content)
        {
            List<WeakReference> to_remove = new List<WeakReference>();
            W to_return = default(W);
            lock (_cache)
            {
                foreach (WeakReference content_wr in _cache.Keys)
                {
                    if (content_wr.IsAlive == false)
                    {
                        to_remove.Add(content_wr);
                        continue;
                    }
                    WeakReference wrapper_wr = _cache[content_wr];
                    if (wrapper_wr.IsAlive == false)
                    {
                        to_remove.Add(content_wr);
                        continue;
                    }
                    if (object.ReferenceEquals(content_wr.Target, content))
                    {
                        to_return = (W)_cache[content_wr].Target;
                        break;
                    }
                }
                foreach (WeakReference content_wr in to_remove)
                {
                    _cache.Remove(content_wr);
                }
                if (to_return == null)
                {
                    ConstructorInfo ci = GetConstructor<W>(content.GetType());
                    to_return = (W)ci.Invoke(new object[] { content });
                    Debug.Assert(to_return != null);
                    _cache.Add(new WeakReference(content), new WeakReference(to_return));
                }
            }
            return to_return;
        }

        #region IEnumerable<object> Members

        public IEnumerator<object> GetEnumerator()
        {
            List<WeakReference> to_remove = new List<WeakReference>();
            lock (_cache)
            {
                foreach (WeakReference content in _cache.Keys)
                {
                    if (content.IsAlive == false)
                    {
                        to_remove.Add(content);
                        continue;
                    }
                    WeakReference wrapper = _cache[content];
                    if (wrapper.IsAlive == false)
                    {
                        to_remove.Add(content);
                        continue;
                    }
                    yield return _cache[content].Target;
                }
                foreach (WeakReference content in to_remove)
                {
                    _cache.Remove(content);
                }
            }
        }

        #endregion

        #region IEnumerable Members

        IEnumerator IEnumerable.GetEnumerator()
        {
            return this.GetEnumerator();
        }

        #endregion
    }
}
