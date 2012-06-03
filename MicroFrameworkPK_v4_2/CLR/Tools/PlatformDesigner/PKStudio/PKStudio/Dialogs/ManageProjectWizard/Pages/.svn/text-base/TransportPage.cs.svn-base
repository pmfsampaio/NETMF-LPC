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

namespace PKStudio.Dialogs.ManageProjectWizard.Pages
{
    public partial class TransportPage : BasePage
    {
        LibraryCategoryWrapper selectedTransport = null;

        public TransportPage(WizardParams Params)
            : base(Params)
        {
            InitializeComponent();

            _treeView.NodeControls.Clear();
            _treeView.AddIconControl("Icon");
            _treeView.AddTextBoxControl("Name");
            //List<ComponentWrapper> CWL = new List<ComponentWrapper>();
            //foreach (LibraryCategoryWrapper LCWW in PK.Wrapper.GetTransports())
            //{
            //    if (PW.IsSolutionWizardVisible) PWL.Add(PW);
            //}

            _treeView.SetModel(InventoryBrowserModel.GetComponentNodeModel<LibraryCategoryWrapper>(PK.Wrapper.GetTransports().ToArray()), false);

        }

        public override string PageName
        {
            get
            {
                return ManageProjectAndSolutionWizardsStrings.IDS_PAGE_NAME_TRANSPORT;
            }
        }

        public override string PageDescription
        {
            get
            {
                return ManageProjectAndSolutionWizardsStrings.IDS_PAGE_DESCRIPTION_TRANSPORT;
            }
        }

        public override void BeforeCloseOnNext()
        {
            if (selectedTransport != null)
            {
                string str = "COM1";
                string str2 = selectedTransport.Name.ToUpper();
                if (str2.StartsWith("USART"))
                {
                    str = "COM1";
                }
                else if (str2.StartsWith("USB"))
                {
                    str = "USB1";
                }
                else if (str2.StartsWith("SOCKETS"))
                {
                    str = "COM_SOCKET_DBG";
                }

                Params.Solution.TransportType = selectedTransport;
                Params.Solution.DebuggerPort = str;
            }
        }

        public override void BeforeShow()
        {
            base.BeforeShow();
            if (selectedTransport == null)
            {
                this.OnShowNextBtn(false);
            }
        }

        private void ShowDescription(LibraryCategoryWrapper Transport)
        {
            DescriptionTB.Clear();
            DescriptionTB.AppendText("Name: " + Transport.Name + "\r\n\r\n");
            DescriptionTB.AppendText("Project Path:\r\n");
            DescriptionTB.AppendText(Transport.ProjectPath + "\r\n\r\n");
            DescriptionTB.AppendText("Is Transport:\r\n");
            DescriptionTB.AppendText(Transport.IsTransport + "\r\n\r\n");
            DescriptionTB.AppendText("Description:\r\n");
            DescriptionTB.AppendText(Transport.Description + "\r\n\r\n");            
        }

        private void _treeView_SelectionChangedEvent(object sender, Forms.BaseForms.ObjectEventArgs e)
        {
            if (e.Object != null)
            {
                ComponentWrapper CW = e.Object as ComponentWrapper;

                LibraryCategoryWrapper LCW = PK.Wrapper.FindLibraryCategory(CW.Guid);

                if (LCW != null)
                {
                    ShowDescription(LCW);
                    selectedTransport = LCW;
                    this.OnShowNextBtn(true);
                }
            }
        }
    }
}
