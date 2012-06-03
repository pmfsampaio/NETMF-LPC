using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using PKStudio.ItemWrappers;
using PKStudio.Tree.Nodes;
using System.Collections.ObjectModel;
using PKStudio.Tree;

namespace PKStudio.Dialogs.ManageProjectWizard.Pages
{
    public partial class ProcessorPage : BasePage
    {
        ComponentWrapper selectedProcessor = null;

        public ProcessorPage(WizardParams Params)
            : base(Params)
        {
            InitializeComponent();
            _treeView.NodeControls.Clear();
            _treeView.AddIconControl("Icon");
            _treeView.AddTextBoxControl("Name");
            List<ProcessorWrapper> PWL = new List<ProcessorWrapper>();
            foreach (ProcessorWrapper PW in PK.Wrapper.GetProcessors())
            {
                if (PW.IsSolutionWizardVisible) PWL.Add(PW);
            }

            _treeView.SetModel(InventoryBrowserModel.GetComponentNodeModel<ProcessorWrapper>(PWL.ToArray()), false);
        }

        public override string PageName
        {
            get
            {
                return ManageProjectAndSolutionWizardsStrings.IDS_PAGE_NAME_PROCESSOR;
            }
        }

        public override string PageDescription
        {
            get
            {
                return ManageProjectAndSolutionWizardsStrings.IDS_PAGE_DESCRIPTION_PROCESSOR;
            }
        }

        public override void BeforeCloseOnNext()
        {
            if (selectedProcessor != null)
            {
                Params.Solution.Processor = selectedProcessor;
            }
        }

        public override void BeforeShow()
        {
            base.BeforeShow();
            if (selectedProcessor == null)
            {
                this.OnShowNextBtn(false);
            }
            else
            {
                _treeView.SetSelectedComponent(selectedProcessor);
            }
        }

        private void ShowDescription(ComponentWrapper processor)
        {
            ProcessorWrapper PW = PK.Wrapper.FindProcessor(processor.Guid);
            DescriptionTB.Clear();
            if (PW != null)
            {
                DescriptionTB.AppendText("Name: " + PW.Name + "\r\n\r\n");
                DescriptionTB.AppendText("Project Path:\r\n");
                DescriptionTB.AppendText(PW.ProjectPath + "\r\n\r\n");
                DescriptionTB.AppendText("Description:\r\n");
                DescriptionTB.AppendText(PW.Description + "\r\n\r\n");
            }
        }

        private void _treeView_SelectionChangedEvent(object sender, Forms.BaseForms.ObjectEventArgs e)
        {
            ComponentWrapper CW = e.Object as ComponentWrapper;
            if (CW != null)
            {
                ShowDescription(CW);
                selectedProcessor = CW;
                this.OnShowNextBtn(true);
            }
        }
    }
}
