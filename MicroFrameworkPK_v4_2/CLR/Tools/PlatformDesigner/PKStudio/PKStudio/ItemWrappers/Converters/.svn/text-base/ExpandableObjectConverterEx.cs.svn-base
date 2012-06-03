using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;
using System.Reflection;

namespace PKStudio.ItemWrappers.Converters
{
    class ExpandableObjectConverterEx : ExpandableObjectConverter
    {
        public override bool CanConvertTo(ITypeDescriptorContext context, Type destinationType)
        {
            if (destinationType == typeof(string))
            {
                return true;
            }
            else
                return base.CanConvertTo(context, destinationType);
        }

        public override object ConvertTo(ITypeDescriptorContext context, System.Globalization.CultureInfo culture, object value, Type destinationType)
        {
            if (value != null)
                if (destinationType == typeof(string))
                {
                    DefaultPropertyAttribute dpa = null;
                    foreach (var attr in value.GetType().GetCustomAttributes(true))
                    {
                        if (attr.GetType() == typeof(DefaultPropertyAttribute))
                        {
                            dpa = (DefaultPropertyAttribute)attr;
                            break;
                        }
                    }
                    if(dpa != null)
                        if (dpa.Name != null)
                        {
                            object ret = value.GetType().InvokeMember(dpa.Name, BindingFlags.GetProperty, null, value, null);
                            if (ret != null)
                                return ret.ToString();
                            else
                                return string.Empty;
                        }
                }
            return base.ConvertTo(context, culture, value, destinationType);
        }
    }
}
