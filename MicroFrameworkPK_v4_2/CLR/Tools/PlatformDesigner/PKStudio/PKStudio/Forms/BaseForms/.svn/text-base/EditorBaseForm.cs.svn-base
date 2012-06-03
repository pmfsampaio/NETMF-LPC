using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using PKStudio.ItemWrappers;

namespace PKStudio.Forms.BaseForms
{
    public partial class EditorBaseForm : BasePKInventoryForm
    {

        protected string FormText = "";
        protected string ModifiedFormText = "";

        protected bool modified = false;

        public EditorBaseForm()
        {
            InitializeComponent();
            this.TabContextMenu.Items["saveToolStripMenuItem"].Visible = true;
            this.TabContextMenu.Items["saveToolStripMenuItem"].Enabled = true;
            this.TabContextMenu.Items["saveToolStripMenuItem"].Click += new EventHandler(EditorBaseForm_Click);

            this.TabContextMenu.Items["SavetoolStripSeparator"].Visible = true;

            this.TabContextMenu.Items["dockToolStripMenuItem"].Visible = false;
            this.TabContextMenu.Items["autoHideToolStripMenuItem"].Visible = false;
            this.TabContextMenu.Items["hideToolStripMenuItem"].Visible = false;

        }

        void EditorBaseForm_Click(object sender, EventArgs e)
        {
            this.Save();
        }

        public bool Modified { get { return this.modified; } }

        public virtual BaseWrapper EditComponent
        {
            get
            {
                return null;
            }
        }

        protected void SetModified(bool modified)
        {
            this.modified = modified;
            if (this.modified)
                this.TabText = ModifiedFormText;
            else
                this.TabText = FormText;
        }

        public virtual void Save()
        {

        }

        private void EditorBaseForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (e.CloseReason == CloseReason.UserClosing)
            {
                if (this.modified)
                {
                    using (PKStudio.Dialogs.SaveChangesDialog SCDlg = new Dialogs.SaveChangesDialog())
                    {
                        DialogResult res = SCDlg.ShowDialog(this, this.EditComponent);

                        switch (res)
                        {
                            case DialogResult.Cancel:
                                e.Cancel = true;
                                break;
                            case DialogResult.No:
                                break;
                            case DialogResult.Yes:
                                Save();
                                break;
                            default:
                                break;
                        }
                    }
                }
            }
        }

    }
}
