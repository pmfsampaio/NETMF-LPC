using System;
using System.Windows.Forms;
using PKStudio.ItemWrappers;

namespace PKStudio.Dialogs.ManageProjectWizard.Pages
{
    public partial class BasePage : UserControl
    {
        //protected ProjectWrapper OldProject = null;
        //protected ProjectWrapper NewProject = null;

        protected WizardParams Params = null;

        public BasePage()
        {
            InitializeComponent();
            this.ToShow = true;
        }

        //public BasePage(ProjectWrapper OldProject, ProjectWrapper NewProject)
        public BasePage(WizardParams Params)
        {
            InitializeComponent();
            this.Params = Params;
            this.Dock = DockStyle.Fill;
            this.ToShow = true;
        }

        public virtual string PageName { get { return string.Empty; } set { } }
        public virtual string PageDescription { get { return string.Empty; } set { } }

        public virtual void BeforeCloseOnNext() { }
        public virtual void BeforeCloseOnBack() { }
        public virtual void BeforeShow() { }
        public virtual void AfterShow() { }

        public bool ToShow { get; set; }



        #region events
        public event EventHandler<ErrorEventArgs> ErrorEvent;
        protected void OnError(Exception ex)
        {
            if (ErrorEvent != null)
            {
                ErrorEvent(this, new ErrorEventArgs(ex));
            }
        }
        
        public event EventHandler<ShowBtnEventArgs> ShowNextBtnEvent;
        protected void OnShowNextBtn(bool show)
        {
            if (ShowNextBtnEvent != null)
            {
                ShowNextBtnEvent(this, new ShowBtnEventArgs(show));
            }
        }

        public event EventHandler<ShowBtnEventArgs> ShowBackBtnEvent;
        protected void OnShowBackBtn(bool show)
        {
            if (ShowBackBtnEvent != null)
            {
                ShowBackBtnEvent(this, new ShowBtnEventArgs(show));
            }
        }
        #endregion
    }

    public class ErrorEventArgs : EventArgs
    {
        public ErrorEventArgs(Exception Exception)
        {
            this.Exception = Exception;
        }
        public Exception Exception { get; set; }
    }

    public class ShowBtnEventArgs : EventArgs
    {
        public ShowBtnEventArgs(bool show)
        {
            this.Show = show;
        }
        public bool Show { get; set; }
    }
}
