using System.Windows.Forms;
using PKStudio.TreeNodes;
using PKStudio.ItemWrappers;
using PKStudio.Tree;

namespace PKStudio.Forms.Editors.Pages
{
    //TO compile form uncomment this line, comment next line
    public partial class DependenciesPage<T> : PageBase<T> where T : BaseWrapper
    //TO edit form UI uncomment this line, comment previous line
    //public partial class DependenciesPage<T> : GenericPageBase
    {
        public DependenciesPage()
        {
            InitializeComponent();
        }

        public DependenciesPage(T Wrapper, string Name)
            : base(Wrapper)
        {
            InitializeComponent();
            _treeView.AddIconControl("Icon");
            _treeView.AddTextBoxControl("Name");
            this.NodeName = Name;
            HeaderLbl.Text = this.NodeName;
        }

        #region Dependencies

        protected void SetModel(InventoryBrowserModel model)
        {
            _treeView.SetModel(model, false);
        }

        private void ShowDescription(ComponentWrapper component)
        {
            DepsInfoRTB.Clear();
            DepsInfoRTB.Text = component.BriefDescription;
        }

        private void DepDeleteBtn_Click(object sender, System.EventArgs e)
        {
            //if (DepsListView.SelectedItems.Count != 0)
            //{
            //    if (DepsListView.SelectedItems[0] != null)
            //    {
            //        if (MessageBox.Show(this, Strings.DeleteDependency + " \"" + DepsListView.SelectedItems[0].SubItems[1].Text + "\" ?", Strings.Warning, MessageBoxButtons.YesNo, MessageBoxIcon.Warning) == System.Windows.Forms.DialogResult.Yes)
            //        {
            //            DepsListView.Items.Remove(DepsListView.SelectedItems[0]);
            //            ModifiedChange();
            //        }

            //        if (DepsListView.Items.Count > 0)
            //            DepsListView.Items[0].Selected = true;
            //    }
            //}
        }

        private void DepAddBtn_Click(object sender, System.EventArgs e)
        {
            //using (Dialogs.SelectComponentDialog sf = new Dialogs.SelectComponentDialog(true, false, false, false, false, false, false, false, false, true))
            //{
            //    if (sf.ShowDialog(this) == System.Windows.Forms.DialogResult.OK)
            //    {
            //        //ComponentWrapper c = sf.SelectedComponent;

            //        ListViewItem it = DepsListView.Items.Add(sf.SelectedComponent.ComponentType.ToString());
            //        it.SubItems.Add(sf.SelectedComponent.Name);
            //        switch (sf.SelectedComponent.ComponentType)
            //        {
            //            case ComponentTypeWrapper.Library:
            //                it.ImageIndex = (int)MFTreeNodeBase.ImageKeysEnum.Library;
            //                break;
            //            case ComponentTypeWrapper.LibraryCategory:
            //                it.ImageIndex = (int)MFTreeNodeBase.ImageKeysEnum.LibraryCategory;
            //                break;
            //            case ComponentTypeWrapper.Feature:
            //            case ComponentTypeWrapper.MFAssembly:
            //            case ComponentTypeWrapper.MFSolution:
            //            case ComponentTypeWrapper.Processor:
            //            case ComponentTypeWrapper.OperatingSystem:
            //            case ComponentTypeWrapper.BuildTool:
            //            case ComponentTypeWrapper.ISA:
            //            case ComponentTypeWrapper.BuildParameter:
            //            case ComponentTypeWrapper.Unknown:
            //            default:
            //                break;
            //        }
            //        it.Selected = true;

            //        ModifiedChange();
            //    }
            //}
        }

        #endregion

        private void _treeView_SelectionChangedEvent(object sender, BaseForms.ObjectEventArgs e)
        {
            ComponentWrapper wrapper = e.Object as ComponentWrapper;
            if (wrapper != null)
            {
                this.ShowDescription(wrapper);
                this.OnSelectionChangeEvent(wrapper);
            }
        }

        private void _treeView_EditEvent(object sender, BaseForms.ObjectEventArgs e)
        {
            ComponentWrapper wrapper = e.Object as ComponentWrapper;
            if (wrapper != null)
            {
                this.OnEditEvent(wrapper);
            }

        }
    }

    public class LibraryDependenciesPageBase : DependenciesPage<LibraryWrapper>
    {
        public LibraryDependenciesPageBase()
            : base(null, Strings.Dependencies)
        {
        }
        public LibraryDependenciesPageBase(LibraryWrapper Wrapper, string Name)
            : base(Wrapper, Name)
        {
        }
    }

    public class FeatureDependenciesPageBase : DependenciesPage<FeatureWrapper>
    {
        public FeatureDependenciesPageBase()
            : base(null, Strings.Dependencies)
        {
        }
        public FeatureDependenciesPageBase(FeatureWrapper Wrapper, string Name)
            : base(Wrapper, Name)
        {
        }
    }

    public class LibraryCategoryDependenciesPageBase : DependenciesPage<LibraryCategoryWrapper>
    {
        public LibraryCategoryDependenciesPageBase()
            : base(null, Strings.Dependencies)
        {
        }
        public LibraryCategoryDependenciesPageBase(LibraryCategoryWrapper Wrapper, string Name)
            : base(Wrapper, Name)
        {
        }
    }

}
