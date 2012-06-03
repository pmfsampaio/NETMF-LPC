using System.Windows.Forms;
using PKStudio.TreeNodes;
using PKStudio.ItemWrappers;
using System.IO;

namespace PKStudio.Forms.Tools
{
    public partial class FindResultsForm : PKStudio.Forms.BaseForms.BasePKInventoryForm
    {
        public FindResultsForm()
        {
            InitializeComponent();
            PK.Wrapper.SearchComplitedEvent += new System.EventHandler<PortingKitWrapper.SearchComplitedEventArgs>(PKWrapper_SearchComplitedEvent);
            PK.Wrapper.ElementFindedEvent += new System.EventHandler<PortingKitWrapper.ElementFindedEventArgs>(Wrapper_ElementFindedEvent);
            PK.Wrapper.SearchStartedEvent += new System.EventHandler<PortingKitWrapper.SearchStartedEventArgs>(Wrapper_SearchStartedEvent);
        }

        void Wrapper_SearchStartedEvent(object sender, PortingKitWrapper.SearchStartedEventArgs e)
        {
            ClearItemList();
            string type = "";
            switch (e.SearchParams.Type)
            {
                case PortingKitWrapper.SearchType.AllComponents:
                    type = Strings.ALL + " types";
                    break;
                case PortingKitWrapper.SearchType.Libraries:
                    type = "Libraries";
                    break;
                case PortingKitWrapper.SearchType.LibraryCategories:
                    type = "Library Categories";
                    break;
                case PortingKitWrapper.SearchType.Features:
                    type = "Features";
                    break;
                case PortingKitWrapper.SearchType.Files:
                    type = "Files";
                    break;
                case PortingKitWrapper.SearchType.TextInFiles:
                    type = "Text in files";
                    break;
                default:
                    break;
            }

            string where = "";
            switch (e.SearchParams.Where)
            {
                case PortingKitWrapper.SearchWhere.All:
                    where = "Porting Kit Database and opened Solution";
                    break;
                case PortingKitWrapper.SearchWhere.PKDatabase:
                    where = "Porting Kit Database";
                    break;
                case PortingKitWrapper.SearchWhere.Solution:
                    where = "Opened Solution";
                    break;
                default:
                    break;
            }

            AddTextInList(Strings.FindAll + " \"" + e.SearchParams.What + "\" " + Strings.IN + " " + type + " " + Strings.IN + " " + where);
        }

        private string GetComponentName(PKStudio.PortingKitWrapper.SearchResultsHolder.ComponentDescriptor ComponentDescriptor)
        {
            string result = string.Empty;
            if (ComponentDescriptor.Parent != null)
            {
                result += GetComponentName(ComponentDescriptor.Parent) + "\\";
            }

            if (ComponentDescriptor.Component != null)
                result += ComponentDescriptor.Component.Name;
            else if (ComponentDescriptor.File != null)
                result +=Path.GetFileName(ComponentDescriptor.File.File);

            return result;
        }

        void Wrapper_ElementFindedEvent(object sender, PortingKitWrapper.ElementFindedEventArgs e)
        {
            if (e.ComponentDescriptor.Component != null)
            {
                ListViewItem it = new ListViewItem(GetComponentName(e.ComponentDescriptor));
                it.Tag = e.ComponentDescriptor;
                switch (e.ComponentDescriptor.Component.ComponentType)
                {
                    case ComponentTypeWrapper.Library:
                        it.ImageIndex = (int)MFTreeNodeBase.ImageKeysEnum.Library;
                        break;
                    case ComponentTypeWrapper.Feature:
                        it.ImageIndex = (int)MFTreeNodeBase.ImageKeysEnum.Feature;
                        break;
                    case ComponentTypeWrapper.MFAssembly:
                        break;
                    case ComponentTypeWrapper.MFSolution:
                        it.ImageIndex = (int)MFTreeNodeBase.ImageKeysEnum.Solution;
                        break;
                    case ComponentTypeWrapper.Processor:
                        it.ImageIndex = (int)MFTreeNodeBase.ImageKeysEnum.Processor;
                        break;
                    case ComponentTypeWrapper.OperatingSystem:
                        break;
                    case ComponentTypeWrapper.BuildTool:
                        break;
                    case ComponentTypeWrapper.ISA:
                        it.ImageIndex = (int)MFTreeNodeBase.ImageKeysEnum.ISA;
                        break;
                    case ComponentTypeWrapper.BuildParameter:
                        break;
                    case ComponentTypeWrapper.LibraryCategory:
                        it.ImageIndex = (int)MFTreeNodeBase.ImageKeysEnum.LibraryCategory;
                        break;
                    case ComponentTypeWrapper.Unknown:
                        break;
                    default:
                        break;
                }
                AddItemInList(it);
            }
            else if (e.ComponentDescriptor.File != null)
            {
            
                ListViewItem it = null;

                if (e.ComponentDescriptor.Line == null)
                    it = new ListViewItem(GetComponentName(e.ComponentDescriptor));
                else
                {
                    //it = new ListViewItem(GetComponentName(e.ComponentDescriptor) + ":      " + e.ComponentDescriptor.Line.Text.Trim());
                    it = new ListViewItem(GetComponentName(e.ComponentDescriptor) + ":      ");
                    it.SubItems.Add(e.ComponentDescriptor.Line.Text.Trim());
                }

                it.Tag = e.ComponentDescriptor;
                it.ImageIndex = (int)MFSourceFileTreeNode.FileName2ImageKey(e.ComponentDescriptor.File.File);
                AddItemInList(it);
            }
        }

        void PKWrapper_SearchComplitedEvent(object sender, PKStudio.PortingKitWrapper.SearchComplitedEventArgs e)
        {
            //SortList();
            AddTextInList(Strings.MatchingComponents + " : " + e.SearchResults.FindedComponents.Count + "    " + Strings.TotalComponentsSearched + " : " + e.SearchResults.TotalComponentsSearched);
            AutoResizeList();
        }

        private void ComponentsLV_SizeChanged(object sender, System.EventArgs e)
        {
            //ComponentsLV.Columns[0].Width = ComponentsLV.Width - 10;
            //ComponentsLV.AutoResizeColumns(ColumnHeaderAutoResizeStyle.ColumnContent);
        }

        private void ComponentsLV_SelectedIndexChanged(object sender, System.EventArgs e)
        {

        }

        private void ClearAllBtn_Click(object sender, System.EventArgs e)
        {
            Clear();
        }

        private void ComponentsLV_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            if (e.Button == System.Windows.Forms.MouseButtons.Left)
                GoTo();
        }

        private void GoToBtn_Click(object sender, System.EventArgs e)
        {
            GoTo();
        }

        private void FindNextBtn_Click(object sender, System.EventArgs e)
        {
            GoToNext();
        }

        private void FindPrevBtn_Click(object sender, System.EventArgs e)
        {
            GoToPrev();
        }

        private void clearAllToolStripMenuItem_Click(object sender, System.EventArgs e)
        {
            Clear();
        }

        private void goToLocationToolStripMenuItem_Click(object sender, System.EventArgs e)
        {
            GoTo();
        }

        private void goToNextLocationToolStripMenuItem_Click(object sender, System.EventArgs e)
        {
            GoToNext();
        }

        private void goToPreviousLocationToolStripMenuItem_Click(object sender, System.EventArgs e)
        {
            GoToPrev();
        }

        private void GoToNext()
        {
            int selected;
            if (ComponentsLV.SelectedIndices.Count != 0)
                selected = ComponentsLV.SelectedIndices[0];
            else
                selected = 0;

            if (selected + 1 < ComponentsLV.Items.Count)
            {
                selected++;
                ComponentsLV.Items[selected].Selected = true;
                ComponentsLV.Items[selected].EnsureVisible();
            }

            GoTo();
        }

        private void GoToPrev()
        {
            int selected;
            if (ComponentsLV.SelectedIndices.Count != 0)
                selected = ComponentsLV.SelectedIndices[0];
            else
                selected = 0;

            if (selected - 1 >= 0)
            {
                selected--;
                ComponentsLV.Items[selected].Selected = true;
                ComponentsLV.Items[selected].EnsureVisible();
            }

            GoTo();
        }

        private void GoTo()
        {
            if (ComponentsLV.SelectedItems.Count > 0)
            {
                if (ComponentsLV.SelectedItems[0].Tag != null)
                    OnEditEvent(ComponentsLV.SelectedItems[0].Tag);
            }
        }

        private void Clear()
        {
            ClearItemList();
        }

        private void copyToolStripMenuItem_Click(object sender, System.EventArgs e)
        {
            if (ComponentsLV.SelectedItems.Count > 0)
            {
                Clipboard.SetText(ComponentsLV.SelectedItems[0].Text);
            }
        }

        private delegate void AutoResizeListCallback();
        private void AutoResizeList()
        {
            if (ComponentsLV.InvokeRequired)
            {
                AutoResizeListCallback d = new AutoResizeListCallback(AutoResizeList);
                ComponentsLV.BeginInvoke(d, new object[] {  });
            }
            else
            {
                ComponentsLV.AutoResizeColumns(ColumnHeaderAutoResizeStyle.ColumnContent);
            }
        }

        private delegate void AddTextInListCallback(string text);
        private void AddTextInList(string text)
        {
            if (ComponentsLV.InvokeRequired)
            {
                AddTextInListCallback d = new AddTextInListCallback(AddTextInList);
                ComponentsLV.BeginInvoke(d, new object[] { text });
            }
            else
            {
                ComponentsLV.Items.Add(text).EnsureVisible();
                //ComponentsLV.AutoResizeColumns(ColumnHeaderAutoResizeStyle.ColumnContent);
            }
        }

        private delegate void AddItemInListCallback(ListViewItem item);
        private void AddItemInList(ListViewItem item)
        {
            if (ComponentsLV.InvokeRequired)
            {
                AddItemInListCallback d = new AddItemInListCallback(AddItemInList);
                ComponentsLV.BeginInvoke(d, new object[] { item });
            }
            else
            {
                ComponentsLV.Items.Add(item).EnsureVisible();
                //ComponentsLV.AutoResizeColumns(ColumnHeaderAutoResizeStyle.ColumnContent);                
            }
        }

        private delegate void SortListCallback();
        private void SortList()
        {
            if (ComponentsLV.InvokeRequired)
            {
                SortListCallback d = new SortListCallback(SortList);
                ComponentsLV.BeginInvoke(d, new object[] { });
            }
            else
            {
                ComponentsLV.Sort();
            }
        }

        private delegate void ClearItemListCallback();
        private void ClearItemList()
        {
            if (ComponentsLV.InvokeRequired)
            {
                ClearItemListCallback d = new ClearItemListCallback(ClearItemList);
                ComponentsLV.BeginInvoke(d, new object[] { });
            }
            else
            {
                ComponentsLV.Items.Clear();
            }
        }

        private void contextMenuStrip1_Opening(object sender, System.ComponentModel.CancelEventArgs e)
        {
            if (ComponentsLV.SelectedItems.Count > 0)
            {
                if (ComponentsLV.SelectedItems[0].Tag != null)
                {

                    if (ComponentsLV.SelectedItems[0].Tag is PKStudio.PortingKitWrapper.SearchResultsHolder.ComponentDescriptor)
                    {
                        PKStudio.PortingKitWrapper.SearchResultsHolder.ComponentDescriptor compDesc = ComponentsLV.SelectedItems[0].Tag as PKStudio.PortingKitWrapper.SearchResultsHolder.ComponentDescriptor;

                        if (compDesc.Component != null)
                        {
                            string path = PK.Wrapper.ExpandEnvVars(compDesc.Component.ProjectPath, "");
                            if ((!string.IsNullOrEmpty(path)) && (File.Exists(Path.GetFullPath(path))))
                            {
                                openContainingFolderToolStripMenuItem.Visible = true;
                            }
                            else
                                openContainingFolderToolStripMenuItem.Visible = false;
                        }
                        else if (compDesc.File != null)
                        {
                            string path = PK.Wrapper.ExpandEnvVars(compDesc.File.FullPath, "");
                            if ((!string.IsNullOrEmpty(path)) && (File.Exists(Path.GetFullPath(path))))
                            {
                                openContainingFolderToolStripMenuItem.Visible = true;
                            }
                            else
                                openContainingFolderToolStripMenuItem.Visible = false;
                        }
                        else
                            openContainingFolderToolStripMenuItem.Visible = false;

                    }
                }
            }
        }

        private void openContainingFolderToolStripMenuItem_Click(object sender, System.EventArgs e)
        {
            if (ComponentsLV.SelectedItems.Count > 0)
            {
                if (ComponentsLV.SelectedItems[0].Tag != null)
                {
                    if (ComponentsLV.SelectedItems[0].Tag is PKStudio.PortingKitWrapper.SearchResultsHolder.ComponentDescriptor)
                    {
                        PKStudio.PortingKitWrapper.SearchResultsHolder.ComponentDescriptor compDesc = ComponentsLV.SelectedItems[0].Tag as PKStudio.PortingKitWrapper.SearchResultsHolder.ComponentDescriptor;

                        if (compDesc.File != null)
                            this.OnOpenContainingFolderEvent(compDesc.File.FullPath);
                        if (compDesc.Component != null)
                            this.OnOpenContainingFolderEvent(compDesc.Component.ProjectPath);
                    }
                }
            }
        }
    }
}
