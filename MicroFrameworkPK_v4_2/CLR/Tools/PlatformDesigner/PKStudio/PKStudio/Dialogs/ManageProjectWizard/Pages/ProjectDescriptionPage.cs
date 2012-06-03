using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using PKStudio.ItemWrappers;
using System.IO;

namespace PKStudio.Dialogs.ManageProjectWizard.Pages
{
    public partial class ProjectDescriptionPage : BasePage
    {
        public ProjectDescriptionPage(WizardParams Params)
            : base(Params)
        {
            InitializeComponent();
        }


        public override string PageName
        {
            get
            {
                return ManageProjectAndSolutionWizardsStrings.IDS_PAGE_NAME_PROJECT_INFO;
            }
        }

        public override string PageDescription
        {
            get
            {
                return ManageProjectAndSolutionWizardsStrings.IDS_PAGE_DESCRIPTION_PROJECT_INFO;
            }
        }

        public override void BeforeShow()
        {
            this.DescriptionTb.Focus();

            this.NameTB.Text = Params.NewProject.Name;
            this.DescriptionTb.Text = Params.NewProject.Description;
            this.IsCLRLbl.Text = Params.NewProject.IsClrProject.ToString();
            this.IsSolutionWizardVisibleLbl.Text = Params.NewProject.IsSolutionWizardVisible.ToString();
            this.OnIsCLR(Params.NewProject.IsClrProject);

            if (this.NameTB.Text.Length <= 0) this.OnShowNextBtn(false);
            else this.OnShowNextBtn(true);

        }

        public override void BeforeCloseOnNext()
        {
            Params.NewProject.Description = this.DescriptionTb.Text;
            Params.NewProject.Name = this.NameTB.Text;
        }

        private void NameTB_TextChanged(object sender, EventArgs e)
        {
            if (this.NameTB.Text.Length <= 0) this.OnShowNextBtn(false);
            else this.OnShowNextBtn(true);
        }



        public event EventHandler<IsCLREventArgs> IsCLREvent;
        protected void OnIsCLR(bool IsCLR)
        {
            if (IsCLREvent != null)
            {
                IsCLREvent(this, new IsCLREventArgs(IsCLR));
            }
        }
    }

    public class IsCLREventArgs : EventArgs
    {
        public IsCLREventArgs(bool IsCLR)
        {
            this.IsCLR = IsCLR;
        }
        public bool IsCLR { get; set; }
    }
}
