using System;
using System.Collections.Generic;
using System.Windows.Forms;
using PKStudio.ItemWrappers;
using PKStudio.Tools.uVisionGenerator.Classes.HelpClasses;
using System.Collections.ObjectModel;
using XsdInventoryFormatObject;

namespace PKStudio.Tools.uVisionGenerator.Wizard.Pages
{
    public partial class ProjectsAndConfigurationsPage : BasePage
    {
        public ProjectsAndConfigurationsPage(SolutionWrapper sol, ConvertConfig config)
            : base(sol, config)
        {
            InitializeComponent();

            UpdateCells(sol.Projects);
        }

        private void UpdateCells(CollectionWrapper<ProjectWrapper, MFProject> projects)
        {
            ProjectDataGridView.Rows.Clear();
            ProjectDataGridView.Rows.Add(projects.Count);

            for (int i = 0; i < projects.Count; i++)
            {
                ProjectWrapper proj = sol.Projects[i];
                DataGridViewRow row = ProjectDataGridView.Rows[i];

                DataGridViewCheckBoxCell CheckBoxCell = (DataGridViewCheckBoxCell)row.Cells[0];
                DataGridViewTextBoxCell NameCell = (DataGridViewTextBoxCell)row.Cells[1];
                DataGridViewComboBoxCell BuildTypeCell = (DataGridViewComboBoxCell)row.Cells[2];
                DataGridViewComboBoxCell MediaTypeCell = (DataGridViewComboBoxCell)row.Cells[3];

                CheckBoxCell.Value = true;

                NameCell.Value = proj.Name.Trim();

                BuildTypeCell.Items.Clear();
                BuildTypeCell.Items.Add("Debug");
                BuildTypeCell.Items.Add("Release");
                BuildTypeCell.Items.Add("RTM");
                BuildTypeCell.Value = "Debug";
                BuildTypeCell.Sorted = false;

                MediaTypeCell.Items.Clear();
                MediaTypeCell.Items.Add("FLASH");
                MediaTypeCell.Items.Add("RAM");
                MediaTypeCell.Value = "FLASH";
                MediaTypeCell.Sorted = false;

                //BuildTypeCell.Value = "Debug";
                //MediaTypeCell.Value = "FLASH";
                row.Tag = proj;
            }
        }


        public override void BeforeCloseOnNext()
        {
            config.ProjectList.Clear();

            foreach (DataGridViewRow row in ProjectDataGridView.Rows)
            {
                DataGridViewCheckBoxCell CheckBoxCell = (DataGridViewCheckBoxCell)row.Cells[0];
                //DataGridViewTextBoxCell NameCell = (DataGridViewTextBoxCell)row.Cells[1];
                DataGridViewComboBoxCell BuildTypeCell = (DataGridViewComboBoxCell)row.Cells[2];
                DataGridViewComboBoxCell MediaTypeCell = (DataGridViewComboBoxCell)row.Cells[3];

                if ((bool)CheckBoxCell.Value == true)
                {
                    config.ProjectList.Add(new ConvertableMFProject((ProjectWrapper)row.Tag, BuildTypeCell.Value.ToString(), MediaTypeCell.Value.ToString()));
                }
                else
                {
                    if (config.ContainsProject((ProjectWrapper)row.Tag))
                        config.RemoveProject((ProjectWrapper)row.Tag);
                }
            }

            if (config.ProjectList.Count == 0) throw new ArgumentException(KeilWizardStrings.IDS_ERROR_SELECT_PROJECT);

            config.Name = sol.Name.Trim();
            base.BeforeCloseOnNext();
        }

        public override void BeforeShow()
        {

            foreach (DataGridViewRow row in ProjectDataGridView.Rows)
            {
                DataGridViewCheckBoxCell CheckBoxCell = (DataGridViewCheckBoxCell)row.Cells[0];
                //DataGridViewTextBoxCell NameCell = (DataGridViewTextBoxCell)row.Cells[1];
                DataGridViewComboBoxCell BuildTypeCell = (DataGridViewComboBoxCell)row.Cells[2];
                DataGridViewComboBoxCell MediaTypeCell = (DataGridViewComboBoxCell)row.Cells[3];

                CheckBoxCell.Value = false;
                BuildTypeCell.Value = "Debug";
                MediaTypeCell.Value = "FLASH";
            }

            foreach (ConvertableMFProject cc in config.ProjectList)
            {
                foreach (DataGridViewRow row in ProjectDataGridView.Rows)
                {
                    DataGridViewCheckBoxCell CheckBoxCell = (DataGridViewCheckBoxCell)row.Cells[0];
                    //DataGridViewTextBoxCell NameCell = (DataGridViewTextBoxCell)row.Cells[1];
                    DataGridViewComboBoxCell BuildTypeCell = (DataGridViewComboBoxCell)row.Cells[2];
                    DataGridViewComboBoxCell MediaTypeCell = (DataGridViewComboBoxCell)row.Cells[3];

                    if (((ProjectWrapper)row.Tag) == cc.Project)
                    {
                        CheckBoxCell.Value = true;
                        BuildTypeCell.Value = cc.BuildType;
                        MediaTypeCell.Value = cc.MediaType;
                    }
                }
            }

            base.BeforeShow();
        }

        public override string PageName
        {
            get
            {
                return KeilWizardStrings.IDS_PAGE_NAME_SELECT_PROJECT;
            }
        }

        public override string PageDescription
        {
            get
            {
                return KeilWizardStrings.IDS_PAGE_DESCRIPTION_SELECT_PROJECT;
            }
        }

        private void ProjectDataGridView_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            if (e.RowIndex != -1)
            {
                if (e.ColumnIndex == 1)
                {
                    DataGridViewRow row = ProjectDataGridView.Rows[e.RowIndex];
                    DataGridViewCheckBoxCell CheckBoxCell = (DataGridViewCheckBoxCell)row.Cells[0];
                    CheckBoxCell.Value = !(bool)CheckBoxCell.Value;
                }
            }
        }
    }
}
