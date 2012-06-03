namespace PKStudio.Dialogs
{
    partial class AboutDialog
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
            this.OkBtn = new System.Windows.Forms.Button();
            this.richTextBox1 = new System.Windows.Forms.RichTextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.VersionLbl = new System.Windows.Forms.Label();
            this.TitleLbl = new System.Windows.Forms.Label();
            this.CopyrightLbl = new System.Windows.Forms.Label();
            this.mailtoLabel = new System.Windows.Forms.LinkLabel();
            this.ContactsLabel = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // OkBtn
            // 
            this.OkBtn.Location = new System.Drawing.Point(307, 249);
            this.OkBtn.Name = "OkBtn";
            this.OkBtn.Size = new System.Drawing.Size(75, 23);
            this.OkBtn.TabIndex = 0;
            this.OkBtn.Text = "Ok";
            this.OkBtn.UseVisualStyleBackColor = true;
            this.OkBtn.Click += new System.EventHandler(this.OkBtn_Click);
            // 
            // richTextBox1
            // 
            this.richTextBox1.BackColor = System.Drawing.SystemColors.Window;
            this.richTextBox1.Location = new System.Drawing.Point(12, 143);
            this.richTextBox1.Name = "richTextBox1";
            this.richTextBox1.ReadOnly = true;
            this.richTextBox1.Size = new System.Drawing.Size(370, 100);
            this.richTextBox1.TabIndex = 1;
            this.richTextBox1.Text = "";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(14, 127);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(270, 13);
            this.label1.TabIndex = 2;
            this.label1.Text = "Microsoft .NET Micro Framework Porting Kit information:";
            // 
            // VersionLbl
            // 
            this.VersionLbl.AutoSize = true;
            this.VersionLbl.Location = new System.Drawing.Point(14, 43);
            this.VersionLbl.Name = "VersionLbl";
            this.VersionLbl.Size = new System.Drawing.Size(42, 13);
            this.VersionLbl.TabIndex = 10;
            this.VersionLbl.Text = "Version";
            // 
            // TitleLbl
            // 
            this.TitleLbl.AutoSize = true;
            this.TitleLbl.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.TitleLbl.Location = new System.Drawing.Point(12, 9);
            this.TitleLbl.Name = "TitleLbl";
            this.TitleLbl.Size = new System.Drawing.Size(58, 25);
            this.TitleLbl.TabIndex = 9;
            this.TitleLbl.Text = "Title";
            // 
            // CopyrightLbl
            // 
            this.CopyrightLbl.AutoSize = true;
            this.CopyrightLbl.Location = new System.Drawing.Point(14, 73);
            this.CopyrightLbl.Name = "CopyrightLbl";
            this.CopyrightLbl.Size = new System.Drawing.Size(51, 13);
            this.CopyrightLbl.TabIndex = 11;
            this.CopyrightLbl.Text = "Copyright";
            // 
            // mailtoLabel
            // 
            this.mailtoLabel.AutoSize = true;
            this.mailtoLabel.Location = new System.Drawing.Point(72, 104);
            this.mailtoLabel.Name = "mailtoLabel";
            this.mailtoLabel.Size = new System.Drawing.Size(124, 13);
            this.mailtoLabel.TabIndex = 13;
            this.mailtoLabel.TabStop = true;
            this.mailtoLabel.Text = "info@pkstudionetmf.com";
            this.mailtoLabel.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.mailtoLabel_LinkClicked);
            // 
            // ContactsLabel
            // 
            this.ContactsLabel.AutoSize = true;
            this.ContactsLabel.Location = new System.Drawing.Point(14, 104);
            this.ContactsLabel.Name = "ContactsLabel";
            this.ContactsLabel.Size = new System.Drawing.Size(52, 13);
            this.ContactsLabel.TabIndex = 14;
            this.ContactsLabel.Text = "Contacts:";
            // 
            // AboutDialog
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(394, 284);
            this.Controls.Add(this.ContactsLabel);
            this.Controls.Add(this.mailtoLabel);
            this.Controls.Add(this.CopyrightLbl);
            this.Controls.Add(this.VersionLbl);
            this.Controls.Add(this.TitleLbl);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.richTextBox1);
            this.Controls.Add(this.OkBtn);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "AboutDialog";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "AboutDialog";
            this.Load += new System.EventHandler(this.AboutDialog_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button OkBtn;
        private System.Windows.Forms.RichTextBox richTextBox1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label VersionLbl;
        private System.Windows.Forms.Label TitleLbl;
        private System.Windows.Forms.Label CopyrightLbl;
        private System.Windows.Forms.LinkLabel mailtoLabel;
        private System.Windows.Forms.Label ContactsLabel;
    }
}