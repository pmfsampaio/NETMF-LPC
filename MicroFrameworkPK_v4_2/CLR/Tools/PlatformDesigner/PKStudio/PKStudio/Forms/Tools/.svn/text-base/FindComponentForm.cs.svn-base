using WeifenLuo.WinFormsUI.Docking;
using PKStudio.Forms.BaseForms;

namespace PKStudio.Forms.Tools
{
    public partial class FindComponentForm : BasePKInventoryForm
    {
        public FindComponentForm()
        {
            InitializeComponent();

            ComponentTypeCB.Items.Clear();
            ComponentTypeCB.Items.Add(PortingKitWrapper.SearchType.AllComponents);
            ComponentTypeCB.Items.Add(PortingKitWrapper.SearchType.Features);
            ComponentTypeCB.Items.Add(PortingKitWrapper.SearchType.Libraries);
            ComponentTypeCB.Items.Add(PortingKitWrapper.SearchType.LibraryCategories);
            ComponentTypeCB.Items.Add(PortingKitWrapper.SearchType.Files);
            ComponentTypeCB.Items.Add(PortingKitWrapper.SearchType.TextInFiles);
            ComponentTypeCB.SelectedIndex = 0;

            WhereCB.Items.Clear();
            WhereCB.Items.Add(PortingKitWrapper.SearchWhere.All);
            WhereCB.Items.Add(PortingKitWrapper.SearchWhere.PKDatabase);
            WhereCB.Items.Add(PortingKitWrapper.SearchWhere.Solution);
            WhereCB.SelectedIndex = 0;
        }

        private void FindAllBtn_Click(object sender, System.EventArgs e)
        {
            FindWhatCB.Items.Insert(0, FindWhatCB.Text);
            PK.Wrapper.Search((PortingKitWrapper.SearchType)ComponentTypeCB.SelectedItem, (PortingKitWrapper.SearchWhere)WhereCB.SelectedItem, FindWhatCB.Text, MatchCaseCB.Checked, MatchWholeWordCB.Checked);
        }

        private void FindWhatCB_KeyUp(object sender, System.Windows.Forms.KeyEventArgs e)
        {
            if (e.KeyCode == System.Windows.Forms.Keys.Enter)
            {
                FindWhatCB.Items.Insert(0, FindWhatCB.Text);
                PK.Wrapper.Search((PortingKitWrapper.SearchType)ComponentTypeCB.SelectedItem, (PortingKitWrapper.SearchWhere)WhereCB.SelectedItem, FindWhatCB.Text, MatchCaseCB.Checked, MatchWholeWordCB.Checked);
            }
        }
    }
}
