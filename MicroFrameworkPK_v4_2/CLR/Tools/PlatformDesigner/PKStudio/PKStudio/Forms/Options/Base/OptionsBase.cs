using System;
using System.Collections.Generic;
using System.Text;

namespace OptionsHelper.Options
{
    /// <summary>
    /// Abstract Obtions base class
    /// </summary>
    [Serializable]
    public abstract class OptionsBase
    {
        public abstract bool OnApplyChanges();
        public abstract void OnInitialized();
    }
}
