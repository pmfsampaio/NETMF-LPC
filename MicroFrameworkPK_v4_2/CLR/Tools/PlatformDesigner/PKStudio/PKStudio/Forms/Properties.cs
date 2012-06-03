using PKStudio.Forms.BaseForms;
using PKStudio.ItemWrappers;
using PKStudio.Tree.Nodes;
using System.Security.Permissions;

namespace PKStudio.Forms
{
    [SecurityPermission(SecurityAction.Demand)]
    public partial class Properties : BasePKInventoryForm
    {
        public Properties(object obj)
        {
            InitializeComponent();
            propertyGrid1.SelectedObject = obj;
        }

        public Properties()
            : this(null)
        {
        }

        public void SetObject(object obj)
        {
            string text = string.Empty;
            if (obj is BaseNode)
            {
                text = (obj as BaseNode).Name;
            }
            else if (obj is BaseWrapper)
            {
                text = (obj as BaseWrapper).ClassName;
            }
            else if (obj is object)
            {
                text = obj.GetType().ToString();
            }
            propertyGrid1.SelectedObject = obj;
            textBox1.Text = text;
        }
    }
}
