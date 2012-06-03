using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using PKStudio.Tree;

namespace PKStudio.Forms.Explorers
{
    public partial class ProcessorExplorer : InventoryExplorer
    {
        public ProcessorExplorer()
        {
            InitializeComponent();
            PK.Wrapper.LoadFeaturesAsyncCompleteEvent += new EventHandler(OnLoadInventoryComplete);

        }

        protected override void OnLoadInventoryComplete(object sender, EventArgs e)
        {
            SetModel(InventoryBrowserModel.ProcessorsModel);
        }
    }
}
