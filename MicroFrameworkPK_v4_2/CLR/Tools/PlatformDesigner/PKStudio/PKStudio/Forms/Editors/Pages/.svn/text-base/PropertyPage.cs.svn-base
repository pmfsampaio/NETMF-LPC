using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using PKStudio.ItemWrappers;
using PKStudio.Tree;

namespace PKStudio.Forms.Editors.Pages
{
    //TO compile form uncomment this line, comment next line
    public partial class PropertyPage<T> : PageBase<T> where T : BaseWrapper
    //TO edit form UI uncomment this line, comment previous line
    //public partial class PropertyPage<T> : GenericPageBase
    {
        public PropertyPage()
        {
            InitializeComponent();
        }
        public PropertyPage(T Wrapper, string Name)
            : base(Wrapper)
        {
            InitializeComponent();
            this.NodeName = Name;
            _treeView.AddIconControl("Icon");
            _treeView.AddTextBoxControl("Name");
            HeaderLbl.Text = Name;
        }

        protected void SetModel(InventoryBrowserModel model)
        {
            _treeView.SetModel(model, false);
        }

        private void _treeView_SelectionChangedEvent(object sender, BaseForms.ObjectEventArgs e)
        {
            ComponentWrapper wrapper = e.Object as ComponentWrapper;
            if (wrapper != null)
            {
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
    public class LibraryPropertyPageBase : PropertyPage<LibraryWrapper>
    {
        public LibraryPropertyPageBase()
            : base(null, String.Empty)
        {
        }
        public LibraryPropertyPageBase(LibraryWrapper Wrapper, string Name)
            : base(Wrapper, Name)
        {
        }
    }

    public class FeaturePropertyPageBase : PropertyPage<FeatureWrapper>
    {
        public FeaturePropertyPageBase()
            : base(null, String.Empty)
        {
        }
        public FeaturePropertyPageBase(FeatureWrapper Wrapper, string Name)
            : base(Wrapper, Name)
        {
        }
    }

    public class LibraryCategoryPropertyPageBase : PropertyPage<LibraryCategoryWrapper>
    {
        public LibraryCategoryPropertyPageBase()
            : base(null, String.Empty)
        {
        }
        public LibraryCategoryPropertyPageBase(LibraryCategoryWrapper Wrapper, string Name)
            : base(Wrapper, Name)
        {
        }
    }

}
