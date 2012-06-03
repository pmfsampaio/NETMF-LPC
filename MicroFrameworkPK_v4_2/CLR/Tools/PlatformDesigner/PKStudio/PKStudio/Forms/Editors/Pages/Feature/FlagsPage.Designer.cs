namespace PKStudio.Forms.Editors.Pages.Feature
{
    partial class FlagsPage
    {
        /// <summary> 
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.tableLayoutPanel2 = new System.Windows.Forms.TableLayoutPanel();
            this.IsSolutionWizardVisibleCB = new System.Windows.Forms.CheckBox();
            this.HiddenCheckBox = new System.Windows.Forms.CheckBox();
            this.RequiredCheckBox = new System.Windows.Forms.CheckBox();
            this.HeaderLbl = new System.Windows.Forms.Label();
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.tableLayoutPanel2.SuspendLayout();
            this.tableLayoutPanel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // tableLayoutPanel2
            // 
            this.tableLayoutPanel2.ColumnCount = 1;
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel2.Controls.Add(this.IsSolutionWizardVisibleCB, 0, 0);
            this.tableLayoutPanel2.Controls.Add(this.HiddenCheckBox, 0, 1);
            this.tableLayoutPanel2.Controls.Add(this.RequiredCheckBox, 0, 2);
            this.tableLayoutPanel2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel2.Location = new System.Drawing.Point(5, 27);
            this.tableLayoutPanel2.Name = "tableLayoutPanel2";
            this.tableLayoutPanel2.RowCount = 4;
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 25F));
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 25F));
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 25F));
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel2.Size = new System.Drawing.Size(716, 491);
            this.tableLayoutPanel2.TabIndex = 1;
            // 
            // IsSolutionWizardVisibleCB
            // 
            this.IsSolutionWizardVisibleCB.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.IsSolutionWizardVisibleCB.AutoSize = true;
            this.IsSolutionWizardVisibleCB.Enabled = false;
            this.IsSolutionWizardVisibleCB.Location = new System.Drawing.Point(3, 4);
            this.IsSolutionWizardVisibleCB.Name = "IsSolutionWizardVisibleCB";
            this.IsSolutionWizardVisibleCB.Size = new System.Drawing.Size(144, 17);
            this.IsSolutionWizardVisibleCB.TabIndex = 24;
            this.IsSolutionWizardVisibleCB.Text = "Is Solution Wizard Visible";
            this.IsSolutionWizardVisibleCB.UseVisualStyleBackColor = true;
            this.IsSolutionWizardVisibleCB.CheckedChanged += new System.EventHandler(this.IgnoreDefaultLibPathCheckBox_CheckedChanged);
            // 
            // HiddenCheckBox
            // 
            this.HiddenCheckBox.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.HiddenCheckBox.AutoSize = true;
            this.HiddenCheckBox.Enabled = false;
            this.HiddenCheckBox.Location = new System.Drawing.Point(3, 29);
            this.HiddenCheckBox.Name = "HiddenCheckBox";
            this.HiddenCheckBox.Size = new System.Drawing.Size(60, 17);
            this.HiddenCheckBox.TabIndex = 25;
            this.HiddenCheckBox.Text = "Hidden";
            this.HiddenCheckBox.UseVisualStyleBackColor = true;
            this.HiddenCheckBox.CheckedChanged += new System.EventHandler(this.IsTransportCheckBox_CheckedChanged);
            // 
            // RequiredCheckBox
            // 
            this.RequiredCheckBox.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.RequiredCheckBox.AutoSize = true;
            this.RequiredCheckBox.Enabled = false;
            this.RequiredCheckBox.Location = new System.Drawing.Point(3, 54);
            this.RequiredCheckBox.Name = "RequiredCheckBox";
            this.RequiredCheckBox.Size = new System.Drawing.Size(69, 17);
            this.RequiredCheckBox.TabIndex = 26;
            this.RequiredCheckBox.Text = "Required";
            this.RequiredCheckBox.UseVisualStyleBackColor = true;
            this.RequiredCheckBox.CheckedChanged += new System.EventHandler(this.RequiredCheckBox_CheckedChanged);
            // 
            // HeaderLbl
            // 
            this.HeaderLbl.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.HeaderLbl.AutoSize = true;
            this.HeaderLbl.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.HeaderLbl.Location = new System.Drawing.Point(5, 5);
            this.HeaderLbl.Name = "HeaderLbl";
            this.HeaderLbl.Size = new System.Drawing.Size(37, 13);
            this.HeaderLbl.TabIndex = 0;
            this.HeaderLbl.Text = "Flags";
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.CellBorderStyle = System.Windows.Forms.TableLayoutPanelCellBorderStyle.Inset;
            this.tableLayoutPanel1.ColumnCount = 1;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.Controls.Add(this.HeaderLbl, 0, 0);
            this.tableLayoutPanel1.Controls.Add(this.tableLayoutPanel2, 0, 1);
            this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel1.Location = new System.Drawing.Point(0, 0);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 2;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(726, 523);
            this.tableLayoutPanel1.TabIndex = 0;
            // 
            // FlagsPage
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.tableLayoutPanel1);
            this.Name = "FlagsPage";
            this.tableLayoutPanel2.ResumeLayout(false);
            this.tableLayoutPanel2.PerformLayout();
            this.tableLayoutPanel1.ResumeLayout(false);
            this.tableLayoutPanel1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel2;
        private System.Windows.Forms.CheckBox IsSolutionWizardVisibleCB;
        private System.Windows.Forms.CheckBox HiddenCheckBox;
        private System.Windows.Forms.CheckBox RequiredCheckBox;
        private System.Windows.Forms.Label HeaderLbl;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;

    }
}
