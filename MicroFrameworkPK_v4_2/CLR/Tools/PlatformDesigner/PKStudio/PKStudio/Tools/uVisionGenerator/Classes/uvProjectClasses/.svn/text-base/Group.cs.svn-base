using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace PKStudio.Tools.uVisionGenerator.Classes.uvProjectClasses
{
    /// <summary>
    /// uVision project group
    /// </summary>
    public class Group : IComparable<Group>
    {
        public Group()
        {
            this.Name = "";
            this.Num = 0;
        }

        public Group(string name, int num)
        {
            this.Name = name;
            this.Num = num;
        }
        public string Name { get; set; }
        public int Num { get; set; }

        #region IComparable<Group> Members

        public int CompareTo(Group other)
        {
            return string.Compare(this.Name, other.Name, StringComparison.InvariantCultureIgnoreCase);
        }

        #endregion
    }
}
