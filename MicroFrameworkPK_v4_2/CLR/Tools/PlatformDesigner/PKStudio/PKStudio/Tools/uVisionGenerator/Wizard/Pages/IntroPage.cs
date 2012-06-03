using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace PKStudio.Tools.uVisionGenerator.Wizard.Pages
{
    public partial class IntroPage : BasePage
    {
        public IntroPage()
        {
            InitializeComponent();
        }

        public override string PageName
        {
            get
            {
                return KeilWizardStrings.IDS_PAGE_NAME_INTRO;
            }
        }

        public override string PageDescription
        {
            get
            {
                return KeilWizardStrings.IDS_PAGE_DESCRIPTION_INTRO;
            }
        }
    }
}
