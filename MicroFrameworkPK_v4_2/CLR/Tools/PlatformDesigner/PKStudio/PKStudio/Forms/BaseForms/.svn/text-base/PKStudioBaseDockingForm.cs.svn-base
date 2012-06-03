using System.Windows.Forms;
using WeifenLuo.WinFormsUI.Docking;
using System.Collections.Generic;

namespace PKStudio.Forms.BaseForms
{
    /// <summary>
    /// Ru: Базовый класс всех плавающих окон в PK Studio. Все окна должны наследоваться от него
    /// En: Base class for all docking PK Studio windows.
    /// </summary>
    public partial class PKStudioBaseDockingForm : DockContent
    {
        DockState _dockDockstate;       

        public PKStudioBaseDockingForm()
        {
            InitializeComponent();

            floatToolStripMenuItem.Text = Strings.Float;
            dockToolStripMenuItem.Text = Strings.Dock;
            dockAsTabbetDocumentToolStripMenuItem.Text = Strings.DockAsTabbed;
            autoHideToolStripMenuItem.Text = Strings.AutoHide;
            hideToolStripMenuItem.Text = Strings.Hide;
            closeToolStripMenuItem.Text = Strings.Close;
            closeAllButThisToolStripMenuItem.Text = Strings.CloseAllButThis;

            saveToolStripMenuItem.Visible = false;
            saveToolStripMenuItem.Enabled = false;
            SavetoolStripSeparator.Visible = false;
        }

        private void contextMenuStrip1_Opening(object sender, System.ComponentModel.CancelEventArgs e)
        {
            switch (this.DockState)
            {
                case DockState.DockBottom:
                case DockState.DockLeft:
                case DockState.DockRight:
                case DockState.DockTop:
                    floatToolStripMenuItem.Enabled = true;
                    dockToolStripMenuItem.Enabled = false;
                    if ((this.DockAreas & WeifenLuo.WinFormsUI.Docking.DockAreas.Document) != 0) 
                        dockAsTabbetDocumentToolStripMenuItem.Enabled = true;
                    else
                        dockAsTabbetDocumentToolStripMenuItem.Enabled = false;
                    autoHideToolStripMenuItem.Enabled = true;
                    hideToolStripMenuItem.Enabled = true;
                    closeToolStripMenuItem.Visible = false;
                    closeAllButThisToolStripMenuItem.Visible = false;
                    ClosetoolStripSeparator.Visible = false;
                    break;
                case DockState.DockBottomAutoHide:
                case DockState.DockLeftAutoHide:
                case DockState.DockRightAutoHide:
                case DockState.DockTopAutoHide:
                    floatToolStripMenuItem.Enabled = true;
                    dockToolStripMenuItem.Enabled = true;
                    if ((this.DockAreas & WeifenLuo.WinFormsUI.Docking.DockAreas.Document) != 0) 
                        dockAsTabbetDocumentToolStripMenuItem.Enabled = true;
                    else
                        dockAsTabbetDocumentToolStripMenuItem.Enabled = false;
                    autoHideToolStripMenuItem.Enabled = false;
                    hideToolStripMenuItem.Enabled = true;
                    closeToolStripMenuItem.Visible = false;
                    closeAllButThisToolStripMenuItem.Visible = false;
                    ClosetoolStripSeparator.Visible = false;
                    break;
                case DockState.Document:
                    floatToolStripMenuItem.Enabled = true;
                    dockToolStripMenuItem.Enabled = true;
                    dockAsTabbetDocumentToolStripMenuItem.Enabled = false;
                    autoHideToolStripMenuItem.Enabled = false;
                    hideToolStripMenuItem.Enabled = true;
                    closeToolStripMenuItem.Visible = true;
                    closeAllButThisToolStripMenuItem.Visible = true;
                    ClosetoolStripSeparator.Visible = true;
                    break;
                case DockState.Float:
                    floatToolStripMenuItem.Enabled = false;
                    dockToolStripMenuItem.Enabled = true;
                    if ((this.DockAreas & WeifenLuo.WinFormsUI.Docking.DockAreas.Document) != 0) 
                        dockAsTabbetDocumentToolStripMenuItem.Enabled = true;
                    else
                        dockAsTabbetDocumentToolStripMenuItem.Enabled = false;
                    autoHideToolStripMenuItem.Enabled = false;
                    hideToolStripMenuItem.Enabled = true;
                    closeToolStripMenuItem.Visible = false;
                    closeAllButThisToolStripMenuItem.Visible = false;
                    ClosetoolStripSeparator.Visible = false;
                    break;
                case DockState.Hidden:
                    break;
                case DockState.Unknown:
                    break;
                default:
                    break;
            }
        }

        #region ContextMenu

        private void floatToolStripMenuItem_Click(object sender, System.EventArgs e)
        {
            this.DockState = WeifenLuo.WinFormsUI.Docking.DockState.Float;
        }

        private void dockToolStripMenuItem_Click(object sender, System.EventArgs e)
        {
            if (_dockDockstate != WeifenLuo.WinFormsUI.Docking.DockState.Unknown)
                this.DockState = _dockDockstate;
            else
            {
                if ((this.DockAreas & WeifenLuo.WinFormsUI.Docking.DockAreas.DockRight) != 0)
                    this.DockState = WeifenLuo.WinFormsUI.Docking.DockState.DockRight;
            }
        }

        private void dockAsTabbetDocumentToolStripMenuItem_Click(object sender, System.EventArgs e)
        {
            if ((this.DockAreas & WeifenLuo.WinFormsUI.Docking.DockAreas.Document) != 0)
                this.DockState = WeifenLuo.WinFormsUI.Docking.DockState.Document;
        }

        private void autoHideToolStripMenuItem_Click(object sender, System.EventArgs e)
        {
            switch (this.DockState)
            {
                case DockState.DockBottom:
                    this.DockState = WeifenLuo.WinFormsUI.Docking.DockState.DockBottomAutoHide;
                    break;
                case DockState.DockLeft:
                    this.DockState = WeifenLuo.WinFormsUI.Docking.DockState.DockLeftAutoHide;
                    break;
                case DockState.DockRight:
                    this.DockState = WeifenLuo.WinFormsUI.Docking.DockState.DockRightAutoHide;
                    break;
                case DockState.DockTop:
                    this.DockState = WeifenLuo.WinFormsUI.Docking.DockState.DockTopAutoHide;
                    break;
                default:
                    break;
            }
        }

        private void hideToolStripMenuItem_Click(object sender, System.EventArgs e)
        {
            if (this.HideOnClose)
            {
                this.Hide();
            }
        }

        private void closeToolStripMenuItem_Click(object sender, System.EventArgs e)
        {
            if (this.HideOnClose)
            {
                this.Hide();
            }
            else
                this.Close();
        }

        private void closeAllButThisToolStripMenuItem_Click(object sender, System.EventArgs e)
        {
            List<DockContent> contlist = new List<DockContent>();
            foreach (DockContent item in this.DockPanel.Contents)
            {
                if (item.DockState == WeifenLuo.WinFormsUI.Docking.DockState.Document)
                {
                    if (item != this)
                        contlist.Add(item);
                }
            }

            if (contlist.Count > 0)
            {
                foreach (DockContent item in contlist)
                {
                    if (item.HideOnClose)
                    {
                        item.Hide();
                    }
                    else
                        item.Close();
                }
            }
        }

        #endregion

        public ContextMenuStrip TabContextMenu { get { return this.contextMenuStrip1;} }

        private void PKStudioBaseDockingForm_DockStateChanged(object sender, System.EventArgs e)
        {
            switch (this.DockState)
            {
                case DockState.DockBottom:
                case DockState.DockLeft:
                case DockState.DockRight:
                case DockState.DockTop:
                    _dockDockstate = DockState;
                    break;
                default:
                    break;
            }
        }
    }
}
