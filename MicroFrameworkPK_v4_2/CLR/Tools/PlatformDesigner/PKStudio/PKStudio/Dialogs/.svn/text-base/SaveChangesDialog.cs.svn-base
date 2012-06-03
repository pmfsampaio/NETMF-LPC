using System.Windows.Forms;
using System.Reflection;
using System.Collections.Generic;
using PKStudio.TreeNodes;
using PKStudio.ItemWrappers;
using System.Collections.ObjectModel;

namespace PKStudio.Dialogs
{
    public partial class SaveChangesDialog : Form
    {
        public SaveChangesDialog()
        { 
            InitializeComponent();

            Helper.AssemblyInfoHelper asmhelper = new Helper.AssemblyInfoHelper(Assembly.GetExecutingAssembly());
            this.Text = asmhelper.Title;
            listView1.Items.Clear();
        }

        public DialogResult ShowDialog(IWin32Window owner, Collection<BaseWrapper> components)
        {
            foreach (BaseWrapper component in components)
            {
                this.AddItem(component);
            }
            listView1.AutoResizeColumns(ColumnHeaderAutoResizeStyle.ColumnContent);
            return this.ShowDialog(owner);
        }

        public DialogResult ShowDialog(IWin32Window owner, BaseWrapper component)
        {
            this.AddItem(component);
            listView1.AutoResizeColumns(ColumnHeaderAutoResizeStyle.ColumnContent);
            return this.ShowDialog(owner);
        }

        private void AddItem(BaseWrapper component)
        {
            ListViewItem it = listView1.Items.Add(component.InnerName);
            it.SubItems.Add(component.InnerProjectPath);
        }

        private void listView1_SelectedIndexChanged(object sender, System.EventArgs e)
        {
            if (listView1.SelectedItems.Count>0)
                listView1.SelectedItems[0].Selected = false;
        }
    }
}
