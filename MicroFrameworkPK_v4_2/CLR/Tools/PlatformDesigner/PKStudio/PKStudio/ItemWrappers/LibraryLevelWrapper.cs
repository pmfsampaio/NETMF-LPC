using System;
using XsdInventoryFormatObject;

namespace PKStudio.ItemWrappers
{
    [Serializable]
    public enum LibraryLevelWrapper
    {
        CLR = LibraryLevel.CLR,
        PAL = LibraryLevel.PAL,
        HAL = LibraryLevel.HAL,
        Support = LibraryLevel.Support
    }
}
