using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using PKStudio.Tree;
using Aga.Controls.Tree.NodeControls;
using Aga.Controls.Tree;
using PKStudio.Tree.Nodes;
using PKStudio.ItemWrappers;
using PKStudio.Forms.BaseForms;

namespace PKStudio.Dialogs.ManageProjectWizard.Pages
{
    public partial class BaseTreePage : BasePage
    {
        private BackgroundWorker bw {get; set;}
        public BaseTreePage()
            : base()
        {
            InitializeComponent();
        }


        public BaseTreePage(WizardParams Params)
            : base(Params)
        {
            InitializeComponent();

            SetupTreeEvents(_treeView);
            SetupTreeEvents(_dependTreeView);
            SetupTreeEvents(_referencedByTreeView);
            this.bw = new BackgroundWorker();
            this.bw.DoWork += new DoWorkEventHandler(bw_DoWork);
            this.bw.RunWorkerCompleted += new RunWorkerCompletedEventHandler(bw_RunWorkerCompleted);
        }

        void bw_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            if (e.Error != null)
            {
                throw e.Error;
            }
            UpdateTree();
        }

        private void UpdateReferences()
        {
            if (this.References == null)
            {
                this.References = GetReferenceInfo();
            }
            this.References.CalcReferences();
        }

        protected virtual bool OnUpdateTree()
        {
            return true;
        }

        protected void UpdateTree()
        {
            if (this.OnUpdateTree())
            {
                SetupTree(_treeView, InventoryBrowserModel.GetModel(this.References.GetNodes()), false);
            }
        }
        
        void bw_DoWork(object sender, DoWorkEventArgs e)
        {
            UpdateReferences();
        }

        protected ReferenceInfo References { get; set; }

        protected void SetupTreeEvents(InventoryTree tree)
        {
            tree.NodeMouseDoubleClick += new EventHandler<TreeNodeAdvMouseEventArgs>(this._treeView_NodeMouseDoubleClick);
            tree.SelectionChangedEvent += new EventHandler<ObjectEventArgs>(this._treeView_SelectionChangedEvent);
        }

        protected virtual ReferenceInfo GetReferenceInfo()
        {
            return null;
        }

        public override void BeforeShow()
        {
            while (bw.IsBusy)
            {
                Application.DoEvents();
            }
            //bw.RunWorkerAsync();
            UpdateReferences();
            UpdateTree();
            base.BeforeShow();
        }

        protected void SetupTree(InventoryTree tree, ITreeModel model, bool expandRoot)
        {
            tree.NodeControls.Clear();
            NodeCheckBox checkBox = tree.AddCheckBoxControl("Checked");
            checkBox.IsVisibleValueNeeded += new EventHandler<NodeControlValueEventArgs>(IsCheckBoxVisible);
            checkBox.IsEditEnabledValueNeeded += new EventHandler<NodeControlValueEventArgs>(IsCheckBoxEnabled);
            checkBox.CheckStateChanged += new EventHandler<TreePathEventArgs>(CheckBoxStateChanged);
            tree.AddIconControl("Icon");
            tree.AddTextBoxControl("Name");
            tree.SetModel(model, expandRoot);
        }

        void IsCheckBoxEnabled(object sender, NodeControlValueEventArgs e)
        {
            bool result = true;
            ComponentNode node = e.Node.Tag as ComponentNode;
            if (node != null)
            {
                ComponentWrapper component = node.TypedContent;
                if (this.References.IsFeatureReadOnly(component) == false)
                {
                    if (component.Checked == true)
                    {
                        List<ComponentWrapper> refList;
                        this.References.GetRefList(component, out refList);
                        if (refList.Count != 0)
                        {
                            StringBuilder builder = new StringBuilder();
                            builder.AppendFormat("Component \"{0}\" has checked dependencies:\r\n", component.Name);
                            foreach (ComponentWrapper dependency in refList)
                            {
                                builder.AppendFormat("\"{0}\"\r\n", dependency.Name);
                            }
                            builder.AppendFormat("Try to uncheck them?");
                            if (MessageBox.Show(this, builder.ToString(), "Unresolved dependencies", MessageBoxButtons.OKCancel, MessageBoxIcon.Question, MessageBoxDefaultButton.Button2) == DialogResult.OK)
                            {
                                RecursiveCheckComponent(component);
                            }
                            else
                                result = false;
                        }
                    }
                }
                else
                {
                    result = false;
                }
                
            }
            e.Value = result;
        }

        protected virtual bool OnCheckBoxVisible(ComponentNode node)
        {
            return true;
        }

        void IsCheckBoxVisible(object sender, NodeControlValueEventArgs e)
        {
            e.Value = false;
            ComponentNode node = e.Node.Tag as ComponentNode;
            if (node != null)
            {
                e.Value = OnCheckBoxVisible(node);
            }
        }

        void CheckBoxStateChanged(object sender, TreePathEventArgs e)
        {
            ComponentNode node = e.Path.LastNode as ComponentNode;
            if (node != null)
            {
                RecursiveCheckComponent(node.TypedContent);
            }
        }

        protected virtual bool OnCheckComponent(ComponentWrapper component)
        {
            return true;
        }


        private void RecursiveCheckComponent(ComponentWrapper component)
        {
            if (this.References.RecursiveCheckComponent(component))
            {
                _treeView.SetModel(InventoryBrowserModel.GetModel(this.References.GetNodes()), false);
            }
        }

        private void ShowDescription(LibraryWrapper library)
        {
            DescriptionTB.AppendText("Name: " + library.Name + "\r\n\r\n");
            DescriptionTB.AppendText("Project Path:\r\n");
            DescriptionTB.AppendText(library.ProjectPath + "\r\n\r\n");
            DescriptionTB.AppendText("Required: " + library.Required + "\r\n\r\n");
            if (!string.IsNullOrEmpty(library.CustomFilter))
                DescriptionTB.AppendText("Custom Filter: " + library.CustomFilter + "\r\n\r\n");
            if (library.ProcessorSpecific != null)
            {
                if (!string.IsNullOrEmpty(library.ProcessorSpecific.Name))
                    DescriptionTB.AppendText("Processor Specific: " + library.ProcessorSpecific.Name + "\r\n\r\n");
            }
            //DescriptionTB.AppendText("Sulution Visible: " + LCW.IsSolutionWizardVisible + "\r\n\r\n");
            DescriptionTB.AppendText("Description:\r\n");
            DescriptionTB.AppendText(library.Description + "\r\n\r\n");
        }

        private void ShowDescription(LibraryCategoryWrapper libcat)
        {
            DescriptionTB.AppendText("Name: " + libcat.Name + "\r\n\r\n");
            DescriptionTB.AppendText("Project Path:\r\n");
            DescriptionTB.AppendText(libcat.ProjectPath + "\r\n\r\n");
            DescriptionTB.AppendText("Required: " + libcat.Required + "\r\n\r\n");
            //DescriptionTB.AppendText("Sulution Visible: " + LCW.IsSolutionWizardVisible + "\r\n\r\n");
            DescriptionTB.AppendText("Description:\r\n");
            DescriptionTB.AppendText(libcat.Description + "\r\n\r\n");
        }

        private void ShowDescription(FeatureWrapper feature)
        {
            DescriptionTB.Clear();
            DescriptionTB.AppendText("Name: " + feature.Name + "\r\n\r\n");
            DescriptionTB.AppendText("Project Path:\r\n");
            DescriptionTB.AppendText(feature.ProjectPath + "\r\n\r\n");
            DescriptionTB.AppendText("Required: " + feature.Required + "\r\n\r\n");
            DescriptionTB.AppendText("Solution Wizard Visible: " + feature.IsSolutionWizardVisible + "\r\n\r\n");
            if (!string.IsNullOrEmpty(feature.Filter))
                DescriptionTB.AppendText("Filter: " + feature.Filter + "\r\n\r\n");
            DescriptionTB.AppendText("Description:\r\n");
            DescriptionTB.AppendText(feature.Description + "\r\n\r\n");
        }


        private void ShowDescription(object sender, ComponentWrapper component)
        {
            if (sender == _treeView)
            {
                ReferenceData refData = this.References[component];

                DescriptionTB.Clear();

                if (refData.Wrapper is FeatureWrapper)
                {
                    ShowDescription(refData.Wrapper as FeatureWrapper);
                }

                if (refData.Wrapper is LibraryWrapper)
                {
                    ShowDescription(refData.Wrapper as LibraryWrapper);
                }

                if (refData.Wrapper is LibraryCategoryWrapper)
                {
                    ShowDescription(refData.Wrapper as LibraryCategoryWrapper);
                }

                SetupTree(_dependTreeView, InventoryBrowserModel.GetModel(this.References.GetDependsFrom(component)), true);
                SetupTree(_referencedByTreeView, InventoryBrowserModel.GetModel(this.References.GetRequiredBy(component)), true);
            }
            else
            {
                //_treeView.SetSelectedComponent(component);
            }
        }

        protected void _treeView_SelectionChangedEvent(object sender, ObjectEventArgs e)
        {
            ComponentWrapper component = e.Object as ComponentWrapper;
            if (component != null)
            {
                ShowDescription(sender, component);
            }
        }

        protected void _treeView_NodeMouseDoubleClick(object sender, TreeNodeAdvMouseEventArgs e)
        {
            if (e.Button == System.Windows.Forms.MouseButtons.Left)
            {
                ComponentNode node = e.Node.Tag as ComponentNode;
                if (node != null)
                {
                    _treeView.SetSelectedComponent(node.TypedContent);

                    //ShowDescription(e.Node.Tree, node.TypedContent);
                }
            }
        }

        protected virtual void btnShowComponents_CheckedChanged(object sender, EventArgs e)
        {
        }

    }
}
