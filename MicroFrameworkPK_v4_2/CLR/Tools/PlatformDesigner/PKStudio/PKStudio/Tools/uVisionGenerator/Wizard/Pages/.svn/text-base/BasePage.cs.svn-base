using System;
using System.Windows.Forms;
using PKStudio.ItemWrappers;
using PKStudio.Tools.uVisionGenerator.Classes.HelpClasses;

namespace PKStudio.Tools.uVisionGenerator.Wizard.Pages
{
    public partial class BasePage : UserControl
    {
        protected SolutionWrapper sol = null;
        protected ConvertConfig config = null;

        public BasePage()
        {
            InitializeComponent();
        }

        public BasePage(SolutionWrapper sol, ConvertConfig config)
        {
            InitializeComponent();
            this.sol = sol;
            this.config = config;
            this.Dock = DockStyle.Fill;
        }

        public virtual string PageName { get { return string.Empty;} }
        public virtual string PageDescription { get { return string.Empty; } }

        public virtual void BeforeCloseOnNext() { }
        public virtual void BeforeCloseOnBack() { }
        public virtual void BeforeShow() { }
        public virtual void AfterShow() { }



        #region events
        public event EventHandler<ErrorEventArgs> ErrorEvent;
        protected void OnError(Exception ex)
        {
            if (ErrorEvent != null)
            {
                ErrorEvent(this,new ErrorEventArgs(ex));
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
}
