using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace PKStudio
{
    static class PK
    {
        private static PortingKitWrapper wrapper = new PortingKitWrapper();

        public static PortingKitWrapper Wrapper
        {
            get
            {
                return wrapper;
            }
        }
    }
}
