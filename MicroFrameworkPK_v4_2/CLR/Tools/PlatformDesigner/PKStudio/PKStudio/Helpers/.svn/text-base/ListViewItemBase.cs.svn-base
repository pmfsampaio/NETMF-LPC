using System.Windows.Forms;

namespace PKStudio.Helpers
{
    class ListViewItemBase : TreeNode
    {
        public enum ListViewItemType
        {
            LibraryCategory,
            Library,
            Processor,
            Project,
            Feature,            
        }

        public ListViewItemBase(string text) : base(text) { this.Name = text; }

        public ListViewItemBase() : base() { }

        private ListViewItemType _type;        

        public ListViewItemType ItemType { get { return this._type; } set { this._type = value; } }
    }
}
