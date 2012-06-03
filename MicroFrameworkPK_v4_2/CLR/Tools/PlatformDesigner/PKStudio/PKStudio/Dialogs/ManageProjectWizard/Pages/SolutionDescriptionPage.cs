using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using XsdInventoryFormatObject;
using PKStudio.ItemWrappers;

namespace PKStudio.Dialogs.ManageProjectWizard.Pages
{
    public partial class SolutionDescriptionPage : BasePage
    {
        public SolutionDescriptionPage(WizardParams Params)
            : base(Params)
        {
            InitializeComponent();
        }


        public override string PageName
        {
            get
            {
                return ManageProjectAndSolutionWizardsStrings.IDS_PAGE_NAME_SOLUTION_INFO;
            }
        }

        public override string PageDescription
        {
            get
            {
                return ManageProjectAndSolutionWizardsStrings.IDS_PAGE_DESCRIPTION_SOLUTION_INFO;
            }
        }

        public override void BeforeShow()
        {
            this.NameTB.Focus();
            if (this.NameTB.Text.Length <= 0) this.OnShowNextBtn(false);
            else this.OnShowNextBtn(true);
            this.IsSolutionWizardVisibleLbl.Text = true.ToString();
        }

        public override void BeforeCloseOnNext()
        {
            Params.Solution = PK.Wrapper.CreateSolution(this.NameTB.Text, this.DescriptionTb.Text, this.AuthorTB.Text, true);
        }

        private void NameTB_TextChanged(object sender, EventArgs e)
        {
            if (this.NameTB.Text.Length <= 0) this.OnShowNextBtn(false);
            else this.OnShowNextBtn(true);
        }
    }
}
