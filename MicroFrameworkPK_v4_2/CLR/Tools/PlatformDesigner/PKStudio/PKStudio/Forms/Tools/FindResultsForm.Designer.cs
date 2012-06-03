namespace PKStudio.Forms.Tools
{
    partial class FindResultsForm
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
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FindResultsForm));
            this.contextMenuStrip1 = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.copyToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator3 = new System.Windows.Forms.ToolStripSeparator();
            this.clearAllToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator4 = new System.Windows.Forms.ToolStripSeparator();
            this.goToLocationToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.goToNextLocationToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.goToPreviousLocationToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.openContainingFolderToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.imageList1 = new System.Windows.Forms.ImageList(this.components);
            this.ComponentsLV = new System.Windows.Forms.ListView();
            this.columnHeader2 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader1 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.toolStrip1 = new System.Windows.Forms.ToolStrip();
            this.GoToBtn = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.FindPrevBtn = new System.Windows.Forms.ToolStripButton();
            this.FindNextBtn = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.ClearAllBtn = new System.Windows.Forms.ToolStripButton();
            this.contextMenuStrip1.SuspendLayout();
            this.toolStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // contextMenuStrip1
            // 
            this.contextMenuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.copyToolStripMenuItem,
            this.toolStripSeparator3,
            this.clearAllToolStripMenuItem,
            this.toolStripSeparator4,
            this.goToLocationToolStripMenuItem,
            this.goToNextLocationToolStripMenuItem,
            this.goToPreviousLocationToolStripMenuItem,
            this.openContainingFolderToolStripMenuItem});
            this.contextMenuStrip1.Name = "contextMenuStrip1";
            this.contextMenuStrip1.Size = new System.Drawing.Size(204, 148);
            this.contextMenuStrip1.Opening += new System.ComponentModel.CancelEventHandler(this.contextMenuStrip1_Opening);
            // 
            // copyToolStripMenuItem
            // 
            this.copyToolStripMenuItem.Image = global::PKStudio.Properties.Resources.copy;
            this.copyToolStripMenuItem.Name = "copyToolStripMenuItem";
            this.copyToolStripMenuItem.Size = new System.Drawing.Size(203, 22);
            this.copyToolStripMenuItem.Text = "Copy";
            this.copyToolStripMenuItem.Click += new System.EventHandler(this.copyToolStripMenuItem_Click);
            // 
            // toolStripSeparator3
            // 
            this.toolStripSeparator3.Name = "toolStripSeparator3";
            this.toolStripSeparator3.Size = new System.Drawing.Size(200, 6);
            // 
            // clearAllToolStripMenuItem
            // 
            this.clearAllToolStripMenuItem.Image = global::PKStudio.Properties.Resources.document_delete;
            this.clearAllToolStripMenuItem.Name = "clearAllToolStripMenuItem";
            this.clearAllToolStripMenuItem.Size = new System.Drawing.Size(203, 22);
            this.clearAllToolStripMenuItem.Text = "Clear All";
            this.clearAllToolStripMenuItem.Click += new System.EventHandler(this.clearAllToolStripMenuItem_Click);
            // 
            // toolStripSeparator4
            // 
            this.toolStripSeparator4.Name = "toolStripSeparator4";
            this.toolStripSeparator4.Size = new System.Drawing.Size(200, 6);
            // 
            // goToLocationToolStripMenuItem
            // 
            this.goToLocationToolStripMenuItem.Image = global::PKStudio.Properties.Resources.arrow_up_green;
            this.goToLocationToolStripMenuItem.Name = "goToLocationToolStripMenuItem";
            this.goToLocationToolStripMenuItem.Size = new System.Drawing.Size(203, 22);
            this.goToLocationToolStripMenuItem.Text = "Go To Location";
            this.goToLocationToolStripMenuItem.Click += new System.EventHandler(this.goToLocationToolStripMenuItem_Click);
            // 
            // goToNextLocationToolStripMenuItem
            // 
            this.goToNextLocationToolStripMenuItem.Image = global::PKStudio.Properties.Resources.find_next;
            this.goToNextLocationToolStripMenuItem.Name = "goToNextLocationToolStripMenuItem";
            this.goToNextLocationToolStripMenuItem.Size = new System.Drawing.Size(203, 22);
            this.goToNextLocationToolStripMenuItem.Text = "Go To Next Location";
            this.goToNextLocationToolStripMenuItem.Click += new System.EventHandler(this.goToNextLocationToolStripMenuItem_Click);
            // 
            // goToPreviousLocationToolStripMenuItem
            // 
            this.goToPreviousLocationToolStripMenuItem.Image = global::PKStudio.Properties.Resources.find_previous;
            this.goToPreviousLocationToolStripMenuItem.Name = "goToPreviousLocationToolStripMenuItem";
            this.goToPreviousLocationToolStripMenuItem.Size = new System.Drawing.Size(203, 22);
            this.goToPreviousLocationToolStripMenuItem.Text = "Go To Previous Location";
            this.goToPreviousLocationToolStripMenuItem.Click += new System.EventHandler(this.goToPreviousLocationToolStripMenuItem_Click);
            // 
            // openContainingFolderToolStripMenuItem
            // 
            this.openContainingFolderToolStripMenuItem.Image = global::PKStudio.Properties.Resources.folder1;
            this.openContainingFolderToolStripMenuItem.Name = "openContainingFolderToolStripMenuItem";
            this.openContainingFolderToolStripMenuItem.Size = new System.Drawing.Size(203, 22);
            this.openContainingFolderToolStripMenuItem.Text = "Open Containing Folder";
            this.openContainingFolderToolStripMenuItem.Click += new System.EventHandler(this.openContainingFolderToolStripMenuItem_Click);
            // 
            // imageList1
            // 
            this.imageList1.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("imageList1.ImageStream")));
            this.imageList1.TransparentColor = System.Drawing.Color.Transparent;
            this.imageList1.Images.SetKeyName(0, "folder.png");
            this.imageList1.Images.SetKeyName(1, "folder_closed.png");
            this.imageList1.Images.SetKeyName(2, "folders.png");
            this.imageList1.Images.SetKeyName(3, "component.png");
            this.imageList1.Images.SetKeyName(4, "application.ico");
            this.imageList1.Images.SetKeyName(5, "box.ico");
            this.imageList1.Images.SetKeyName(6, "cpu.ico");
            this.imageList1.Images.SetKeyName(7, "component_green.ico");
            this.imageList1.Images.SetKeyName(8, "component_yellow.ico");
            this.imageList1.Images.SetKeyName(9, "components.ico");
            this.imageList1.Images.SetKeyName(10, "gears.ico");
            this.imageList1.Images.SetKeyName(11, "text_code_h.png");
            this.imageList1.Images.SetKeyName(12, "text_code_c.png");
            this.imageList1.Images.SetKeyName(13, "text_code_cplusplus.png");
            this.imageList1.Images.SetKeyName(14, "text_code_csharp.png");
            this.imageList1.Images.SetKeyName(15, "document_plain.png");
            this.imageList1.Images.SetKeyName(16, "document_error.png");
            this.imageList1.Images.SetKeyName(17, "text_code_a.png");
            // 
            // ComponentsLV
            // 
            this.ComponentsLV.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeader2,
            this.columnHeader1});
            this.ComponentsLV.ContextMenuStrip = this.contextMenuStrip1;
            this.ComponentsLV.Dock = System.Windows.Forms.DockStyle.Fill;
            this.ComponentsLV.FullRowSelect = true;
            this.ComponentsLV.HeaderStyle = System.Windows.Forms.ColumnHeaderStyle.None;
            this.ComponentsLV.HideSelection = false;
            this.ComponentsLV.Location = new System.Drawing.Point(0, 25);
            this.ComponentsLV.MultiSelect = false;
            this.ComponentsLV.Name = "ComponentsLV";
            this.ComponentsLV.ShowGroups = false;
            this.ComponentsLV.Size = new System.Drawing.Size(655, 401);
            this.ComponentsLV.SmallImageList = this.imageList1;
            this.ComponentsLV.TabIndex = 17;
            this.ComponentsLV.UseCompatibleStateImageBehavior = false;
            this.ComponentsLV.View = System.Windows.Forms.View.Details;
            this.ComponentsLV.SelectedIndexChanged += new System.EventHandler(this.ComponentsLV_SelectedIndexChanged);
            this.ComponentsLV.SizeChanged += new System.EventHandler(this.ComponentsLV_SizeChanged);
            this.ComponentsLV.MouseDoubleClick += new System.Windows.Forms.MouseEventHandler(this.ComponentsLV_MouseDoubleClick);
            // 
            // columnHeader2
            // 
            this.columnHeader2.Width = 200;
            // 
            // columnHeader1
            // 
            this.columnHeader1.Width = 200;
            // 
            // toolStrip1
            // 
            this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.GoToBtn,
            this.toolStripSeparator1,
            this.FindPrevBtn,
            this.FindNextBtn,
            this.toolStripSeparator2,
            this.ClearAllBtn});
            this.toolStrip1.Location = new System.Drawing.Point(0, 0);
            this.toolStrip1.Name = "toolStrip1";
            this.toolStrip1.Size = new System.Drawing.Size(655, 25);
            this.toolStrip1.TabIndex = 0;
            this.toolStrip1.Text = "toolStrip1";
            // 
            // GoToBtn
            // 
            this.GoToBtn.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.GoToBtn.Image = global::PKStudio.Properties.Resources.arrow_up_green;
            this.GoToBtn.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.GoToBtn.Name = "GoToBtn";
            this.GoToBtn.Size = new System.Drawing.Size(23, 22);
            this.GoToBtn.ToolTipText = "Go to the location on the current line";
            this.GoToBtn.Click += new System.EventHandler(this.GoToBtn_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(6, 25);
            // 
            // FindPrevBtn
            // 
            this.FindPrevBtn.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.FindPrevBtn.Image = global::PKStudio.Properties.Resources.find_previous;
            this.FindPrevBtn.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.FindPrevBtn.Name = "FindPrevBtn";
            this.FindPrevBtn.Size = new System.Drawing.Size(23, 22);
            this.FindPrevBtn.Text = "FindPrev";
            this.FindPrevBtn.ToolTipText = "Go to the previous location in the list";
            this.FindPrevBtn.Click += new System.EventHandler(this.FindPrevBtn_Click);
            // 
            // FindNextBtn
            // 
            this.FindNextBtn.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.FindNextBtn.Image = global::PKStudio.Properties.Resources.find_next;
            this.FindNextBtn.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.FindNextBtn.Name = "FindNextBtn";
            this.FindNextBtn.Size = new System.Drawing.Size(23, 22);
            this.FindNextBtn.Text = "FindNext";
            this.FindNextBtn.ToolTipText = "Go to the next location in the list";
            this.FindNextBtn.Click += new System.EventHandler(this.FindNextBtn_Click);
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(6, 25);
            // 
            // ClearAllBtn
            // 
            this.ClearAllBtn.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.ClearAllBtn.Image = global::PKStudio.Properties.Resources.document_delete;
            this.ClearAllBtn.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.ClearAllBtn.Name = "ClearAllBtn";
            this.ClearAllBtn.Size = new System.Drawing.Size(23, 22);
            this.ClearAllBtn.Text = "Clear all";
            this.ClearAllBtn.Click += new System.EventHandler(this.ClearAllBtn_Click);
            // 
            // FindResultsForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(655, 426);
            this.Controls.Add(this.ComponentsLV);
            this.Controls.Add(this.toolStrip1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "FindResultsForm";
            this.Text = "Find Results";
            this.contextMenuStrip1.ResumeLayout(false);
            this.toolStrip1.ResumeLayout(false);
            this.toolStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ToolStrip toolStrip1;
        private System.Windows.Forms.ToolStripButton GoToBtn;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripButton FindPrevBtn;
        private System.Windows.Forms.ToolStripButton FindNextBtn;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
        private System.Windows.Forms.ToolStripButton ClearAllBtn;
        private System.Windows.Forms.ListView ComponentsLV;
        private System.Windows.Forms.ColumnHeader columnHeader2;
        private System.Windows.Forms.ContextMenuStrip contextMenuStrip1;
        private System.Windows.Forms.ToolStripMenuItem copyToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator3;
        private System.Windows.Forms.ToolStripMenuItem clearAllToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator4;
        private System.Windows.Forms.ToolStripMenuItem goToLocationToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem goToNextLocationToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem goToPreviousLocationToolStripMenuItem;
        private System.Windows.Forms.ImageList imageList1;
        private System.Windows.Forms.ToolStripMenuItem openContainingFolderToolStripMenuItem;
        private System.Windows.Forms.ColumnHeader columnHeader1;
    }
}