using WeifenLuo.WinFormsUI.Docking;
using System.Collections.Generic;
using System.Windows.Forms;
using System;

namespace PKStudio.Forms.BaseForms.ComponentEditor
{
    public partial class ComponentEditorBaseForm : EditorBaseForm
    {
        public ComponentEditorBaseForm()
        {
            InitializeComponent();
        }


        #region Fields
        /// <summary>
        /// Edit controls list
        /// </summary>
        private List<EditorPageBase> mPages;

        /// <summary>
        /// Opened control
        /// </summary>
        EditorPageBase mCurrent = null;
        #endregion

        #region Properties
        /// <summary>
        /// Edit controls list
        /// </summary>
        public List<EditorPageBase> Pages
        {
            get
            {
                if (this.mPages == null)
                    this.mPages = new List<EditorPageBase>();
                return this.mPages;
            }
        }

        //public Button SaveButton { get { return this.SaveBtn; } }

        #endregion


        #region Metods
        /// <summary>
        /// Ru: Инициализирует форму. Просматривает все добавленные контролы опций, добавляет их в дерево и производит их инициализацию.
        /// En: Initializes the form. Viewing the complete list of options controls, adds them to a tree and produces their initialization.
        /// </summary>
        public void Initialize()
        {
            if (PageTree.Nodes.Count > 0)
                PageTree.Nodes.Clear();
        
            foreach (EditorPageBase page in this.Pages)
            {
                page.ModifiedEvent += new EventHandler(ControlModifiedEvent);
                TreeNode node = new TreeNode(page.NodeName);
                node.Tag = page;
                page.Initialize();
                PageTree.Nodes.Add(node);
                IEventComponent icomp = page as IEventComponent;
                if (icomp != null)
                {
                    icomp.SelectionChangedEvent += new EventHandler<ObjectEventArgs>(icomp_SelectionChangedEvent);
                    icomp.EditEvent += new EventHandler<ObjectEventArgs>(icomp_EditEvent);
                }
            }
            PageTree.SelectedNode = PageTree.Nodes[0];
            SaveBtn.Enabled = false;
        }


        void icomp_EditEvent(object sender, ObjectEventArgs e)
        {
            OnEditEvent(e.Object);
        }

        void icomp_SelectionChangedEvent(object sender, ObjectEventArgs e)
        {
            OnSelectionChangeEvent(e.Object);
        }

        /// <summary>
        /// Ru: Сохранить изменения в открытом контроле
        /// En: Save changes in active(focused) control
        /// </summary>
        /// <returns> if all changes are saved - ture,else - false</returns>
        public bool ApplyChanges()
        {
            bool result = false;
            foreach (EditorPageBase ec in Pages)
            {
                result |= ec.ApplyChanges();
                if (!result) break;
            }
            return result;
        }

        #endregion

        #region EventHandlers
        private void ControlModifiedEvent(object sender, EventArgs e)
        {
            SetModified(true);
        }

        private void SaveBtn_Click(object sender, System.EventArgs e)
        {
            if (SaveBtn.Enabled)
                if (ApplyChanges() == true)
                {
                    Save();
                }
        }

        private void PageTree_AfterSelect(object sender, TreeViewEventArgs e)
        {
            EditorPageBase page = e.Node.Tag as EditorPageBase;
            if (mCurrent != null)
            {
                if (page != null)
                {
                    if (mCurrent != page)
                    {
                        //if (mCurrent.Modified)
                        //{
                        //    if (MessageBox.Show(this, Strings.IDS_OPTIONS_PAGE_CHANGED, Strings.IDS_CONFIRM, MessageBoxButtons.OKCancel, MessageBoxIcon.Question, MessageBoxDefaultButton.Button2) == DialogResult.OK)
                        //        ApplyChanges();
                        //    else
                        //        mCurrent.Initialize();
                        //    ApplyBtn.Enabled = false;
                        //}
                    }
                }
            }
            if (page != null)
            {
                //page.Initialize();
                panel1.Controls.Clear();
                panel1.Controls.Add(page);
                page.Dock = DockStyle.Fill;
                mCurrent = page;
            }
        }

        #endregion

        
    }
}
