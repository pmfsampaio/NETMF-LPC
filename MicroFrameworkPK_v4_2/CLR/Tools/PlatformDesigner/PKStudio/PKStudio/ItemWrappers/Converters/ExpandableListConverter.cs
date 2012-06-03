using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;
using System.Globalization;
using System.Collections.ObjectModel;

namespace PKStudio.ItemWrappers.Converters
{
    public class ExpandableCollectionConverter<W> : CollectionConverter
    {
        public override object ConvertTo(ITypeDescriptorContext context, CultureInfo culture, object value, Type destinationType)
        {
            if (destinationType == null)
            {
                throw new ArgumentNullException("destinationType");
            }
            if ((destinationType == typeof(string)) && (value is Collection<W>))
            {
                return string.Empty;
            }
            return base.ConvertTo(context, culture, value, destinationType);
        }

        public override PropertyDescriptorCollection GetProperties(ITypeDescriptorContext context, object value, Attribute[] attributes)
        {
            PropertyDescriptor[] properties = null;
            //Type type = value.GetType();
            Collection<W> collection = value as Collection<W>;
            if (value != null)
            {
                List<Attribute> alist = new List<Attribute>(attributes);
                alist.Add(new ReadOnlyAttribute(true));
                alist.Add(new TypeConverterAttribute(typeof(ExpandableObjectConverterEx)));
                int length = collection.Count;
                properties = new PropertyDescriptor[length];
                Type arrayType = collection.GetType();
                Type elementType = typeof(W);
                for (int i = 0; i < length; i++)
                {
                    properties[i] = new ArrayPropertyDescriptor(arrayType, elementType, i, alist.ToArray());
                }
            }
            return new PropertyDescriptorCollection(properties);
        }

        public override bool GetPropertiesSupported(ITypeDescriptorContext context)
        {
            return true;
        }

        private class ArrayPropertyDescriptor : TypeConverter.SimplePropertyDescriptor
        {
            private int index;

            public ArrayPropertyDescriptor(Type arrayType, Type elementType, int index, Attribute[] attributes)
                : base(arrayType, "" + (index + 1) + "", elementType, attributes)
            {
                this.index = index;
            }

            public override object GetValue(object instance)
            {
                Collection<W> collection = instance as Collection<W>;
                if (collection != null)
                {
                    if (collection.Count > this.index)
                    {
                        return collection[this.index];
                    }
                }
                return null;
            }

            public override void SetValue(object instance, object value)
            {
                Collection<W> collection = instance as Collection<W>;
                if (collection != null)
                {
                    if (collection.Count > this.index)
                    {
                        collection[index] = (W)value;
                    }
                    this.OnValueChanged(instance, EventArgs.Empty);
                }
            }
        }
    }
    
    public class ExpandableCollectionConverter<W, L> : CollectionConverter where W : BaseTypedWrapper<L>
    {
        public override object ConvertTo(ITypeDescriptorContext context, CultureInfo culture, object value, Type destinationType)
        {
            if (destinationType == null)
            {
                throw new ArgumentNullException("destinationType");
            }
            if ((destinationType == typeof(string)) && (value is CollectionWrapper<W, L>))
            {
                return string.Empty;
            }
            return base.ConvertTo(context, culture, value, destinationType);
        }

        public override PropertyDescriptorCollection GetProperties(ITypeDescriptorContext context, object value, Attribute[] attributes)
        {
            PropertyDescriptor[] properties = null;
            //Type type = value.GetType();
            CollectionWrapper<W, L> collection = value as CollectionWrapper<W, L>;
            if (value != null)
            {
                List<Attribute> alist = new List<Attribute>(attributes);
                alist.Add(new ReadOnlyAttribute(true));
                alist.Add(new TypeConverterAttribute(typeof(ExpandableObjectConverterEx)));
                int length = collection.Count;
                properties = new PropertyDescriptor[length];
                Type arrayType = collection.GetType();
                Type elementType = typeof(W);
                for (int i = 0; i < length; i++)
                {
                    properties[i] = new ArrayPropertyDescriptor(arrayType, elementType, i, alist.ToArray());
                }
            }
            return new PropertyDescriptorCollection(properties);
        }

        public override bool GetPropertiesSupported(ITypeDescriptorContext context)
        {
            return true;
        }

        private class ArrayPropertyDescriptor : TypeConverter.SimplePropertyDescriptor
        {
            private int index;

            public ArrayPropertyDescriptor(Type arrayType, Type elementType, int index, Attribute[] attributes)
                : base(arrayType, "" + (index + 1) + "", elementType, attributes)
            {
                this.index = index;
            }

            public override object GetValue(object instance)
            {
                CollectionWrapper<W, L> collection = instance as CollectionWrapper<W, L>;
                if (collection != null)
                {
                    if (collection.Count > this.index)
                    {
                        return collection[this.index];
                    }
                }
                return null;
            }

            public override void SetValue(object instance, object value)
            {
                CollectionWrapper<W, L> collection = instance as CollectionWrapper<W, L>;
                if (collection != null)
                {
                    if (collection.Count > this.index)
                    {
                        collection[index] = (W)value;
                    }
                    this.OnValueChanged(instance, EventArgs.Empty);
                }
            }
        }
    }
}
