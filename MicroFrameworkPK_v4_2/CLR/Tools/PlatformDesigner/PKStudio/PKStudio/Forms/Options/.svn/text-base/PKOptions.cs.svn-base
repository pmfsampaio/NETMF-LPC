using PKStudio.Forms.Options.Options;
using PKStudio.Forms.Options.Pages;

namespace PKStudio.Forms.Options
{
    public partial class PKOptions : OptionsHelper.Options.OptionsForm
    {
        public PKOptions()
        {
            InitializeComponent();

            Pages.Add(new EnvironmentOptionsPage(new EnvironmentOption()));
            Pages.Add(new PKVesrionOptionPage(new PKVersionOption()));

            Initialize();
            this.AboutButton.Visible = false;
            //this.LoadButton.Visible = false;
            //this.SaveButton.Visible = false;
            this.AfterApplyChangesEvent += new System.EventHandler(PKOptions_AfterApplyChangesEvent);

            OptionsLoaded = false;

            try
            {
                this.LoadOptions(System.Windows.Forms.Application.StartupPath+@"\options.dat");
                this.OptionsLoaded = true;
                this.ApplyButton.Enabled = false;
            }
            catch 
            {
                this.OptionsLoaded = false;
            }
            
        }

        public bool OptionsLoaded { get; set; }

        void PKOptions_AfterApplyChangesEvent(object sender, System.EventArgs e)
        {
            this.SaveOptions(System.Windows.Forms.Application.StartupPath+@"\options.dat");
        }
    }
}
