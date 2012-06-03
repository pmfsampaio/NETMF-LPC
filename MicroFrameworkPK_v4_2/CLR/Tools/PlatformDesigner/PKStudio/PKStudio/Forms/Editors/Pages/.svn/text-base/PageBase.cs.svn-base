using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using PKStudio.ItemWrappers;
using PKStudio.Forms.BaseForms;
using PKStudio.Forms.BaseForms.ComponentEditor;

namespace PKStudio.Forms.Editors.Pages
{
    public partial class PageBase<T> : EditorPageBase, IEventComponent where T : BaseWrapper
    {
        public T Wrapper { get; protected set; }
        public PageBase()
        {
            InitializeComponent();
        }
        public PageBase(T Wrapper)
            : this()
        {
            this.Wrapper = Wrapper;
        }

        protected override void OnInitialized()
        {
            this.RefreshControl();
        }
        protected virtual void RefreshControl()
        {
        }

        public event EventHandler<ObjectEventArgs> SelectionChangedEvent;

        public void OnSelectionChangeEvent(object obj)
        {
            if (this.SelectionChangedEvent != null)
            {
                this.SelectionChangedEvent(this, new ObjectEventArgs(obj));
            }
        }

        public event EventHandler<ObjectEventArgs> ShowPropertiesEvent;

        public void OnShowPropertiesEvent(object obj)
        {
            if (this.ShowPropertiesEvent != null)
            {
                this.ShowPropertiesEvent(this, new ObjectEventArgs(obj));
            }
        }

        public event EventHandler<ObjectEventArgs> ShowReferencesDiagramEvent;

        public void OnShowReferencesDiagramEvent(object obj)
        {
            if (this.ShowReferencesDiagramEvent != null)
            {
                this.ShowReferencesDiagramEvent(this, new ObjectEventArgs(obj));
            }
        }

        public event EventHandler<ObjectEventArgs> EditEvent;

        public void OnEditEvent(object obj)
        {
            if (this.EditEvent != null)
            {
                this.EditEvent(this, new ObjectEventArgs(obj));
            }
        }
    }
    public class GenericPageBase : PageBase<BaseWrapper>
    {
        public GenericPageBase()
            : base(null)
        {
        }
        public GenericPageBase(BaseWrapper Wrapper)
            : base(Wrapper)
        {
        }
    }
    public class LibraryWrapperPageBase : PageBase<LibraryWrapper>
    {
        public LibraryWrapperPageBase()
            : base(null)
        {
        }
        public LibraryWrapperPageBase(LibraryWrapper Wrapper)
            : base(Wrapper)
        {
        }
    }
    public class FeaturePageBase : PageBase<FeatureWrapper>
    {
        public FeaturePageBase()
            : base(null)
        {
        }
        public FeaturePageBase(FeatureWrapper Wrapper)
            : base(Wrapper)
        {
        }
    }
    public class LibraryCategoryPageBase : PageBase<LibraryCategoryWrapper>
    {
        public LibraryCategoryPageBase()
            : base(null)
        {
        }
        public LibraryCategoryPageBase(LibraryCategoryWrapper Wrapper)
            : base(Wrapper)
        {
        }
    }


}
