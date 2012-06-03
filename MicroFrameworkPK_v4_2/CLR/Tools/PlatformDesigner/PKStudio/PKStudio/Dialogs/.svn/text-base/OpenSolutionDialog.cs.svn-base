using System;
using System.Collections.Generic;
using System.Windows.Forms;
using ComponentObjectModel;
using PKStudio.ItemWrappers;
using System.Collections.ObjectModel;
using PKStudio.Forms.Explorers;
using PKStudio.Tree;
using PKStudio.Forms.BaseForms;
using PKStudio.Tree.Nodes;
using Aga.Controls.Tree;

namespace PKStudio.Dialogs
{
    public partial class OpenSolutionDialog : Form
    {
        public ComponentDescriptorWrapper SelectedSolution {get;set;}

        public OpenSolutionDialog()
        {
            InitializeComponent();
            _treeView.AddIconControl("Icon");
            _treeView.AddTextBoxControl("Name");
            _treeView.ShowLines = false;
            _treeView.ShowPlusMinus = false;
            _treeView.SetModel(InventoryBrowserModel.SolutionsNamesModel, false);

        }

        private void rb_SelectFromList_CheckedChanged(object sender, EventArgs e)
        {
            if (rb_SelectFromList.Checked) rb_BrowsePlatformFile.Checked = false;
        }

        private void rb_BrowsePlatformFile_CheckedChanged(object sender, EventArgs e)
        {
            if (rb_BrowsePlatformFile.Checked) rb_SelectFromList.Checked = false;
        }


        /// <summary>
        /// Show description in RichTextBox
        /// </summary>
        /// <param name="obj"></param>
        /// <param name="rtbDesc"></param>
        private void DisplayDescription(ComponentDescriptorWrapper descriptor)
        {
            this.SuspendLayout();
            rtb_PlatformFeatures.Clear();
            rtb_PlatformFeatures.AppendText("------------------------------------------------\n");
            rtb_PlatformFeatures.AppendText("Solution options:      \n");
            rtb_PlatformFeatures.AppendText("------------------------------------------------\n");
            rtb_PlatformFeatures.AppendText("Component.Name:                                        " + descriptor.Component.Name + "\n");
            rtb_PlatformFeatures.AppendText("Component.ComponentType:                               " + descriptor.Component.ComponentType.ToString() + "\n");
            rtb_PlatformFeatures.AppendText("Component.ProjectPath:                                 " + descriptor.Component.ProjectPath + "\n");
            rtb_PlatformFeatures.AppendText("Component.GUID:                                        " + descriptor.Component.Guid + "\n");
            rtb_PlatformFeatures.AppendText("Component.Conditional:                                 " + descriptor.Component.Conditional + "\n");
            rtb_PlatformFeatures.AppendText("Component.RefCount:                                    " + descriptor.Component.RefCount.ToString() + "\n");
            rtb_PlatformFeatures.AppendText("Component.RefCountSpecified:                           " + descriptor.Component.RefCountSpecified.ToString() + "\n\n");
            if (descriptor.Component.VersionDependency != null)
            {
                rtb_PlatformFeatures.AppendText("Component.RefCountSpecified.VersionDependency.Author:  " + descriptor.Component.VersionDependency.Author + "\n");
                rtb_PlatformFeatures.AppendText("Component.RefCountSpecified.VersionDependency.Date:    " + descriptor.Component.VersionDependency.Date + "\n");
                rtb_PlatformFeatures.AppendText("Component.RefCountSpecified.VersionDependency.Major:   " + descriptor.Component.VersionDependency.Major + "\n");
                rtb_PlatformFeatures.AppendText("Component.RefCountSpecified.VersionDependency.Minor:   " + descriptor.Component.VersionDependency.Minor + "\n");
                rtb_PlatformFeatures.AppendText("Component.RefCountSpecified.VersionDependency.Build:   " + descriptor.Component.VersionDependency.Build + "\n");
                rtb_PlatformFeatures.AppendText("Component.RefCountSpecified.VersionDependency.Revision:" + descriptor.Component.VersionDependency.Revision + "\n");
                rtb_PlatformFeatures.AppendText("Component.RefCountSpecified.VersionDependency.Extra:   " + descriptor.Component.VersionDependency.Extra + "\n\n");
            }

            rtb_PlatformFeatures.AppendText("Description:                                           " + descriptor.Description + "\n");
            rtb_PlatformFeatures.AppendText("Documentation:                                         " + descriptor.Documentation + "\n");
            rtb_PlatformFeatures.AppendText("ProjectPath:                                           " + descriptor.ProjectPath + "\n\n");

            rtb_PlatformFeatures.AppendText("------------------------------------------------\n");
            rtb_PlatformFeatures.AppendText("Processor:      \n");
            rtb_PlatformFeatures.AppendText("------------------------------------------------\n");
            rtb_PlatformFeatures.AppendText("SolutionProcessor.CPU Name:                            " + descriptor.SolutionProcessor.CpuName + "\n");
            rtb_PlatformFeatures.AppendText("SolutionProcessor.Custom filter                        " + descriptor.SolutionProcessor.CustomFilter + "\n");
            rtb_PlatformFeatures.AppendText("SolutionProcessor.Default ISA:                         " + descriptor.SolutionProcessor.DefaultISA + "\n");
            rtb_PlatformFeatures.AppendText("SolutionProcessor.Description:                         " + descriptor.SolutionProcessor.Description + "\n");
            rtb_PlatformFeatures.AppendText("SolutionProcessor.Documentation:                       " + descriptor.SolutionProcessor.Documentation + "\n");
            rtb_PlatformFeatures.AppendText("SolutionProcessor.Guid:                                " + descriptor.SolutionProcessor.Guid + "\n");
            rtb_PlatformFeatures.AppendText("SolutionProcessor.Name:                                " + descriptor.SolutionProcessor.Name + "\n");
            rtb_PlatformFeatures.AppendText("SolutionProcessor.PlatformFamily:                      " + descriptor.SolutionProcessor.PlatformFamily + "\n");
            rtb_PlatformFeatures.AppendText("SolutionProcessor.ProjectPath:                         " + descriptor.SolutionProcessor.ProjectPath + "\n");
            rtb_PlatformFeatures.AppendText("SolutionProcessor.IsSolutionWizardVisible:             " + descriptor.SolutionProcessor.IsSolutionWizardVisible.ToString() + "\n\n");

            rtb_PlatformFeatures.AppendText("------------------------------------------------\n");
            rtb_PlatformFeatures.AppendText("Processor version:      \n");
            rtb_PlatformFeatures.AppendText("------------------------------------------------\n");
            rtb_PlatformFeatures.AppendText("SolutionProcessor.Version.Author:                      " + descriptor.SolutionProcessor.Version.Author + "\n");
            rtb_PlatformFeatures.AppendText("SolutionProcessor.Version.Date:                        " + descriptor.SolutionProcessor.Version.Date + "\n");
            rtb_PlatformFeatures.AppendText("SolutionProcessor.Version.Major:                       " + descriptor.SolutionProcessor.Version.Major + "\n");
            rtb_PlatformFeatures.AppendText("SolutionProcessor.Version.Minor:                       " + descriptor.SolutionProcessor.Version.Minor + "\n");
            rtb_PlatformFeatures.AppendText("SolutionProcessor.Version.Build:                       " + descriptor.SolutionProcessor.Version.Build + "\n");
            rtb_PlatformFeatures.AppendText("SolutionProcessor.Version.Revision:                    " + descriptor.SolutionProcessor.Version.Revision + "\n");
            rtb_PlatformFeatures.AppendText("SolutionProcessor.Version.Extra:                       " + descriptor.SolutionProcessor.Version.Extra + "\n\n");

            rtb_PlatformFeatures.AppendText("------------------------------------------------\n");
            rtb_PlatformFeatures.AppendText("Processor Build tool options: (Count: " + descriptor.SolutionProcessor.BuildToolOptions.Count.ToString() + ")\n");
            rtb_PlatformFeatures.AppendText("------------------------------------------------\n");
            foreach (BuildToolRefWrapper opt in descriptor.SolutionProcessor.BuildToolOptions)
            {
                rtb_PlatformFeatures.AppendText("Option:      \n");
                rtb_PlatformFeatures.AppendText("SolutionProcessor.BuildToolOptions.Name:                       " + opt.Name + "\n");
                rtb_PlatformFeatures.AppendText("SolutionProcessor.BuildToolOptions.Guid:                       " + opt.Guid + "\n");
                rtb_PlatformFeatures.AppendText("SolutionProcessor.BuildToolOptions.BuildOptions.ToolName:      " + opt.BuildOptions.ToolName + "\n");
                rtb_PlatformFeatures.AppendText("SolutionProcessor.BuildToolOptions.BuildOptions.DeviceType:    " + opt.BuildOptions.DeviceType + "\n");
                rtb_PlatformFeatures.AppendText("SolutionProcessor.BuildToolOptions.BuildOptions.Condition:     " + opt.BuildOptions.Condition + "\n");

                rtb_PlatformFeatures.AppendText("EnvironmentVariables (Count: " + opt.BuildOptions.EnvironmentVariables.Count.ToString() + "):      \n");
                foreach (EnvVarWrapper var in opt.BuildOptions.EnvironmentVariables)
                {
                    rtb_PlatformFeatures.AppendText("   Condition:              " + var.Conditional + "\n");
                    rtb_PlatformFeatures.AppendText("   " + var.Name + " = " + var.Value + "\n");
                }
                rtb_PlatformFeatures.AppendText("\n");

                //rtb_PlatformFeatures.AppendText("ArchiverFlags.BuildToolParameters:              " + opt.BuildOptions.ArchiverFlags.BuildToolParameters. + "\n");
            }

            if (descriptor.SolutionProcessor.Properties != null)
            {
                rtb_PlatformFeatures.AppendText("------------------------------------------------\n");
                rtb_PlatformFeatures.AppendText("Processor Properties: (Count: " + descriptor.SolutionProcessor.Properties.Count.ToString() + ")\n");
                rtb_PlatformFeatures.AppendText("------------------------------------------------\n");
            }

            if (descriptor.SolutionProcessor.SupportedISAs != null)
            {
                rtb_PlatformFeatures.AppendText("------------------------------------------------\n");
                rtb_PlatformFeatures.AppendText("Processor Supported ISAs: (Count: " + descriptor.SolutionProcessor.SupportedISAs.Count.ToString() + ")\n");
                rtb_PlatformFeatures.AppendText("------------------------------------------------\n");
                foreach (ComponentWrapper component in descriptor.SolutionProcessor.SupportedISAs)
                {
                    rtb_PlatformFeatures.AppendText("SolutionProcessor.SupportedISAs.name:     " + component.Name + "\n");
                }
            }
            this.ResumeLayout();
        }

        private void CancelBtn_Click(object sender, EventArgs e)
        {
            this.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.Close();
        }

        private void OkBtn_Click(object sender, EventArgs e)
        {
            this.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.Close();
        }

        private void _treeView_SelectionChangedEvent(object sender, ObjectEventArgs e)
        {
            ComponentDescriptorWrapper wrapper = e.Object as ComponentDescriptorWrapper;
            if (wrapper != null)
            {
                this.DisplayDescription(wrapper);
                this.SelectedSolution = wrapper;
            }
            else
            {
                this.rtb_PlatformFeatures.Clear();
            }

        }

        private void _treeView_NodeMouseDoubleClick(object sender, TreeNodeAdvMouseEventArgs e)
        {
            if (this.SelectedSolution != null)
            {
                this.DialogResult = System.Windows.Forms.DialogResult.OK;
                this.Close();
            }
        }
    }
}
