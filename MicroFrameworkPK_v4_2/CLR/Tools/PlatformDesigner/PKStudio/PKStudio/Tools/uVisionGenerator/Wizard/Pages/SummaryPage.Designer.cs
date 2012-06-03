namespace PKStudio.Tools.uVisionGenerator.Wizard.Pages
{
    partial class SummaryPage
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
            this.SummaryRTB = new System.Windows.Forms.RichTextBox();
            this.SuspendLayout();
            // 
            // SummaryRTB
            // 
            this.SummaryRTB.BackColor = System.Drawing.SystemColors.Window;
            this.SummaryRTB.Dock = System.Windows.Forms.DockStyle.Fill;
            this.SummaryRTB.Font = new System.Drawing.Font("Courier New", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.SummaryRTB.Location = new System.Drawing.Point(0, 0);
            this.SummaryRTB.Name = "SummaryRTB";
            this.SummaryRTB.ReadOnly = true;
            this.SummaryRTB.Size = new System.Drawing.Size(520, 338);
            this.SummaryRTB.TabIndex = 0;
            this.SummaryRTB.Text = "";
            // 
            // SummaryPage
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.SummaryRTB);
            this.Name = "SummaryPage";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.RichTextBox SummaryRTB;
    }
}
