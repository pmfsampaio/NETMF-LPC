using System;
using PKStudio.Tree.Nodes;
using PKStudio.Tree;
using PKStudio.ItemWrappers;

namespace PKStudio.Forms.BaseForms
{
    public interface IEventComponent
    {
        event EventHandler<ObjectEventArgs> SelectionChangedEvent;
        void OnSelectionChangeEvent(object obj);

        event EventHandler<ObjectEventArgs> ShowPropertiesEvent;
        void OnShowPropertiesEvent(object obj);

        event EventHandler<ObjectEventArgs> ShowReferencesDiagramEvent;
        void OnShowReferencesDiagramEvent(object obj);

        event EventHandler<ObjectEventArgs> EditEvent;
        void OnEditEvent(object obj);
    }


    public partial class BasePKInventoryForm : PKStudioBaseDockingForm, IEventComponent
    {
        public BasePKInventoryForm()
        {
            InitializeComponent();
        }

        #region events

        #region Show Properties Event
        public event EventHandler<ObjectEventArgs> ShowPropertiesEvent;

        public void OnShowPropertiesEvent(object obj)
        {
            if (ShowPropertiesEvent != null)
            {
                ShowPropertiesEvent(this, new ObjectEventArgs(obj));
            }
        }
        #endregion

        #region Show References Diagram Event

        public event EventHandler<ObjectEventArgs> ShowReferencesDiagramEvent;

        public void OnShowReferencesDiagramEvent(object obj)
        {
            if (ShowReferencesDiagramEvent != null)
            {
                ShowReferencesDiagramEvent(this, new ObjectEventArgs(obj));
            }
        }

        #endregion

        #region Edit Event

        public event EventHandler<ObjectEventArgs> EditEvent;

        public void OnEditEvent(object obj)
        {
            if (EditEvent != null)
            {
                EditEvent(this, new ObjectEventArgs(obj));
            }
        }

        #endregion

        #region Open Containing Folder

        public event EventHandler<PathEventArgs> OpenContainingFolderEvent;

        public void OnOpenContainingFolderEvent(string path)
        {
            if (OpenContainingFolderEvent != null)
            {
                OpenContainingFolderEvent(this, new PathEventArgs(path));
            }
        }

        #endregion

        #region Generate Event
        public event EventHandler<GenerateEventArgs> GenerateEvent;

        protected void OnGenerateEvent(GenerateTypes type, object obj)
        {
            if (GenerateEvent != null)
            {
                GenerateEvent(this, new GenerateEventArgs(obj,type));
            }
        }



        #endregion

        #region Selection change Event
        public event EventHandler<ObjectEventArgs> SelectionChangedEvent;


        public void OnSelectionChangeEvent(object obj)
        {
            if (SelectionChangedEvent != null)
            {
                SelectionChangedEvent(this, new ObjectEventArgs(obj));
            }
        }

        #endregion

        #region Tree Node Action Event

        public event EventHandler<WrapperActionArgs> WrapperActionEvent;

        public void OnWrapperActionEvent(BaseWrapper Wrapper, NodeAction Action)
        {
            if (this.WrapperActionEvent != null)
            {
                this.WrapperActionEvent(this, new WrapperActionArgs(Wrapper, Action));
            }
        }

        #endregion

        #endregion
    }

    public enum GenerateTypes : int
    {
        KeilProject = 0,
    }

    public class ObjectEventArgs : EventArgs
    {
        public ObjectEventArgs(object obj)
        {
            this.Object = obj;
        }
        public object Object { get; set; }
    }

    public class PathEventArgs : EventArgs
    {
        public PathEventArgs(string Path)
        {
            this.Path = Path;
        }
        public string Path { get; set; }
    }

    public class WrapperActionArgs : EventArgs
    {
        public WrapperActionArgs(BaseWrapper Wrapper, NodeAction Action)
        {
            this.Wrapper = Wrapper;
            this.Action = Action;
        }
        public BaseWrapper Wrapper { get; set; }
        public NodeAction Action { get; set; }
    }

    public class GenerateEventArgs : EventArgs
    {
        public GenerateEventArgs(object Object, GenerateTypes Type)
        {
            this.Object = Object;
            this.Type = Type;
        }

        public object Object { get; set; }
        public GenerateTypes Type { get; set; }
    }
}
