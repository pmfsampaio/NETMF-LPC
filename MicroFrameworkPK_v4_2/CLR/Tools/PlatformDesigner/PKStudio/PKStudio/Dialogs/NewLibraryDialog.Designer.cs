namespace PKStudio.Dialogs
{
    partial class NewLibraryDialog
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

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(NewLibraryDialog));
            this.label1 = new System.Windows.Forms.Label();
            this.NameTb = new System.Windows.Forms.TextBox();
            this.IsStubCb = new System.Windows.Forms.CheckBox();
            this.TestCb = new System.Windows.Forms.CheckBox();
            this.CancelBtn = new System.Windows.Forms.Button();
            this.OtBtn = new System.Windows.Forms.Button();
            this.folderBrowserDialog1 = new System.Windows.Forms.FolderBrowserDialog();
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.tableLayoutPanel3 = new System.Windows.Forms.TableLayoutPanel();
            this.GroupsCb = new System.Windows.Forms.ComboBox();
            this.label6 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.LevelCb = new System.Windows.Forms.ComboBox();
            this.nameSuffixLbl = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.DirectoryTb = new System.Windows.Forms.TextBox();
            this.BrowseBtn = new System.Windows.Forms.Button();
            this.label10 = new System.Windows.Forms.Label();
            this.ProjNameTb = new System.Windows.Forms.TextBox();
            this.projSuffixLbl = new System.Windows.Forms.Label();
            this.tableLayoutPanel2 = new System.Windows.Forms.TableLayoutPanel();
            this.tableLayoutPanel1.SuspendLayout();
            this.tableLayoutPanel3.SuspendLayout();
            this.tableLayoutPanel2.SuspendLayout();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(3, 6);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(35, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Name";
            // 
            // NameTb
            // 
            this.NameTb.Dock = System.Windows.Forms.DockStyle.Fill;
            this.NameTb.Location = new System.Drawing.Point(72, 3);
            this.NameTb.Name = "NameTb";
            this.NameTb.Size = new System.Drawing.Size(484, 20);
            this.NameTb.TabIndex = 1;
            // 
            // IsStubCb
            // 
            this.IsStubCb.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.IsStubCb.AutoSize = true;
            this.IsStubCb.Location = new System.Drawing.Point(72, 134);
            this.IsStubCb.Name = "IsStubCb";
            this.IsStubCb.Size = new System.Drawing.Size(89, 17);
            this.IsStubCb.TabIndex = 5;
            this.IsStubCb.Text = "Is Stub library";
            this.IsStubCb.UseVisualStyleBackColor = true;
            this.IsStubCb.CheckedChanged += new System.EventHandler(this.IsStubCb_CheckedChanged);
            // 
            // TestCb
            // 
            this.TestCb.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.TestCb.AutoSize = true;
            this.TestCb.Location = new System.Drawing.Point(72, 160);
            this.TestCb.Name = "TestCb";
            this.TestCb.Size = new System.Drawing.Size(88, 17);
            this.TestCb.TabIndex = 6;
            this.TestCb.Text = "Is Test library";
            this.TestCb.UseVisualStyleBackColor = true;
            this.TestCb.CheckedChanged += new System.EventHandler(this.TestCb_CheckedChanged);
            // 
            // CancelBtn
            // 
            this.CancelBtn.Anchor = System.Windows.Forms.AnchorStyles.Right;
            this.CancelBtn.Location = new System.Drawing.Point(560, 3);
            this.CancelBtn.Name = "CancelBtn";
            this.CancelBtn.Size = new System.Drawing.Size(75, 23);
            this.CancelBtn.TabIndex = 7;
            this.CancelBtn.Text = "Cancel";
            this.CancelBtn.UseVisualStyleBackColor = true;
            this.CancelBtn.Click += new System.EventHandler(this.CancelBtn_Click);
            // 
            // OtBtn
            // 
            this.OtBtn.Anchor = System.Windows.Forms.AnchorStyles.Right;
            this.OtBtn.Location = new System.Drawing.Point(475, 3);
            this.OtBtn.Name = "OtBtn";
            this.OtBtn.Size = new System.Drawing.Size(75, 23);
            this.OtBtn.TabIndex = 8;
            this.OtBtn.Text = "Ok";
            this.OtBtn.UseVisualStyleBackColor = true;
            this.OtBtn.Click += new System.EventHandler(this.OtBtn_Click);
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.ColumnCount = 1;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.Controls.Add(this.tableLayoutPanel3, 0, 0);
            this.tableLayoutPanel1.Controls.Add(this.tableLayoutPanel2, 0, 1);
            this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel1.Location = new System.Drawing.Point(0, 0);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 2;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 36F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(644, 422);
            this.tableLayoutPanel1.TabIndex = 31;
            // 
            // tableLayoutPanel3
            // 
            this.tableLayoutPanel3.ColumnCount = 3;
            this.tableLayoutPanel3.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 69F));
            this.tableLayoutPanel3.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel3.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 79F));
            this.tableLayoutPanel3.Controls.Add(this.GroupsCb, 1, 1);
            this.tableLayoutPanel3.Controls.Add(this.label6, 0, 2);
            this.tableLayoutPanel3.Controls.Add(this.label9, 0, 1);
            this.tableLayoutPanel3.Controls.Add(this.LevelCb, 1, 2);
            this.tableLayoutPanel3.Controls.Add(this.nameSuffixLbl, 2, 0);
            this.tableLayoutPanel3.Controls.Add(this.NameTb, 1, 0);
            this.tableLayoutPanel3.Controls.Add(this.label1, 0, 0);
            this.tableLayoutPanel3.Controls.Add(this.TestCb, 1, 6);
            this.tableLayoutPanel3.Controls.Add(this.label8, 0, 3);
            this.tableLayoutPanel3.Controls.Add(this.IsStubCb, 1, 5);
            this.tableLayoutPanel3.Controls.Add(this.DirectoryTb, 1, 3);
            this.tableLayoutPanel3.Controls.Add(this.BrowseBtn, 2, 3);
            this.tableLayoutPanel3.Controls.Add(this.label10, 0, 4);
            this.tableLayoutPanel3.Controls.Add(this.ProjNameTb, 1, 4);
            this.tableLayoutPanel3.Controls.Add(this.projSuffixLbl, 2, 4);
            this.tableLayoutPanel3.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel3.Location = new System.Drawing.Point(3, 3);
            this.tableLayoutPanel3.Name = "tableLayoutPanel3";
            this.tableLayoutPanel3.RowCount = 8;
            this.tableLayoutPanel3.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 26F));
            this.tableLayoutPanel3.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 26F));
            this.tableLayoutPanel3.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 26F));
            this.tableLayoutPanel3.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 26F));
            this.tableLayoutPanel3.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 26F));
            this.tableLayoutPanel3.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 26F));
            this.tableLayoutPanel3.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 26F));
            this.tableLayoutPanel3.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel3.Size = new System.Drawing.Size(638, 380);
            this.tableLayoutPanel3.TabIndex = 3;
            // 
            // GroupsCb
            // 
            this.GroupsCb.Dock = System.Windows.Forms.DockStyle.Fill;
            this.GroupsCb.FormattingEnabled = true;
            this.GroupsCb.Location = new System.Drawing.Point(72, 29);
            this.GroupsCb.Name = "GroupsCb";
            this.GroupsCb.Size = new System.Drawing.Size(484, 21);
            this.GroupsCb.Sorted = true;
            this.GroupsCb.TabIndex = 31;
            // 
            // label6
            // 
            this.label6.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(3, 58);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(33, 13);
            this.label6.TabIndex = 26;
            this.label6.Text = "Level";
            // 
            // label9
            // 
            this.label9.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(3, 32);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(41, 13);
            this.label9.TabIndex = 24;
            this.label9.Text = "Groups";
            // 
            // LevelCb
            // 
            this.LevelCb.Dock = System.Windows.Forms.DockStyle.Fill;
            this.LevelCb.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.LevelCb.FormattingEnabled = true;
            this.LevelCb.Location = new System.Drawing.Point(72, 55);
            this.LevelCb.Name = "LevelCb";
            this.LevelCb.Size = new System.Drawing.Size(484, 21);
            this.LevelCb.TabIndex = 29;
            // 
            // nameSuffixLbl
            // 
            this.nameSuffixLbl.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.nameSuffixLbl.AutoSize = true;
            this.nameSuffixLbl.Location = new System.Drawing.Point(559, 6);
            this.nameSuffixLbl.Margin = new System.Windows.Forms.Padding(0, 3, 3, 3);
            this.nameSuffixLbl.Name = "nameSuffixLbl";
            this.nameSuffixLbl.Size = new System.Drawing.Size(34, 13);
            this.nameSuffixLbl.TabIndex = 30;
            this.nameSuffixLbl.Text = "_HAL";
            // 
            // label8
            // 
            this.label8.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(3, 84);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(49, 13);
            this.label8.TabIndex = 32;
            this.label8.Text = "Directory";
            // 
            // DirectoryTb
            // 
            this.DirectoryTb.Dock = System.Windows.Forms.DockStyle.Fill;
            this.DirectoryTb.Location = new System.Drawing.Point(72, 81);
            this.DirectoryTb.Name = "DirectoryTb";
            this.DirectoryTb.Size = new System.Drawing.Size(484, 20);
            this.DirectoryTb.TabIndex = 33;
            // 
            // BrowseBtn
            // 
            this.BrowseBtn.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.BrowseBtn.Location = new System.Drawing.Point(562, 81);
            this.BrowseBtn.Name = "BrowseBtn";
            this.BrowseBtn.Size = new System.Drawing.Size(73, 20);
            this.BrowseBtn.TabIndex = 34;
            this.BrowseBtn.Text = "Browse...";
            this.BrowseBtn.UseVisualStyleBackColor = true;
            this.BrowseBtn.Click += new System.EventHandler(this.BrowseBtn_Click);
            // 
            // label10
            // 
            this.label10.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(3, 110);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(56, 13);
            this.label10.TabIndex = 35;
            this.label10.Text = ".proj name";
            // 
            // ProjNameTb
            // 
            this.ProjNameTb.Dock = System.Windows.Forms.DockStyle.Fill;
            this.ProjNameTb.Location = new System.Drawing.Point(72, 107);
            this.ProjNameTb.Name = "ProjNameTb";
            this.ProjNameTb.Size = new System.Drawing.Size(484, 20);
            this.ProjNameTb.TabIndex = 36;
            this.ProjNameTb.Text = "dotNetMF";
            // 
            // projSuffixLbl
            // 
            this.projSuffixLbl.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.projSuffixLbl.AutoSize = true;
            this.projSuffixLbl.Location = new System.Drawing.Point(559, 110);
            this.projSuffixLbl.Margin = new System.Windows.Forms.Padding(0, 0, 3, 0);
            this.projSuffixLbl.Name = "projSuffixLbl";
            this.projSuffixLbl.Size = new System.Drawing.Size(30, 13);
            this.projSuffixLbl.TabIndex = 37;
            this.projSuffixLbl.Text = "_test";
            // 
            // tableLayoutPanel2
            // 
            this.tableLayoutPanel2.ColumnCount = 3;
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 85F));
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 85F));
            this.tableLayoutPanel2.Controls.Add(this.OtBtn, 1, 0);
            this.tableLayoutPanel2.Controls.Add(this.CancelBtn, 2, 0);
            this.tableLayoutPanel2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel2.Location = new System.Drawing.Point(3, 389);
            this.tableLayoutPanel2.Name = "tableLayoutPanel2";
            this.tableLayoutPanel2.RowCount = 1;
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel2.Size = new System.Drawing.Size(638, 30);
            this.tableLayoutPanel2.TabIndex = 0;
            // 
            // NewLibraryDialog
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(644, 422);
            this.Controls.Add(this.tableLayoutPanel1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "NewLibraryDialog";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "New Library Dialog";
            this.tableLayoutPanel1.ResumeLayout(false);
            this.tableLayoutPanel3.ResumeLayout(false);
            this.tableLayoutPanel3.PerformLayout();
            this.tableLayoutPanel2.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox NameTb;
        private System.Windows.Forms.CheckBox IsStubCb;
        private System.Windows.Forms.CheckBox TestCb;
        private System.Windows.Forms.Button CancelBtn;
        private System.Windows.Forms.Button OtBtn;
        private System.Windows.Forms.FolderBrowserDialog folderBrowserDialog1;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel3;
        private System.Windows.Forms.ComboBox GroupsCb;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.ComboBox LevelCb;
        private System.Windows.Forms.Label nameSuffixLbl;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.TextBox DirectoryTb;
        private System.Windows.Forms.Button BrowseBtn;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.TextBox ProjNameTb;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel2;
        private System.Windows.Forms.Label projSuffixLbl;
    }
}