using System;
using System.Windows.Forms;
using PKStudio.ItemWrappers;
using PKStudio.Forms.BaseForms;
using PKStudio.Forms.BaseForms.ComponentEditor;

namespace PKStudio.Forms.Editors
{
    public partial class FeatureEditor : BaseForms.ComponentEditor.ComponentEditorBaseForm
    {
        public FeatureEditor()
            :base()
        {
            InitializeComponent();

            PK.Wrapper.LoadFeaturesAsyncCompleteEvent += new EventHandler(PKWrapper_LoadFeaturesAsyncCompleteEvent);
        }

        private FeatureWrapper Feat;

        /// <summary>
        /// Sets Feature for edition
        /// </summary>
        /// <param name="LibCat"></param>
        public void SetFeat(FeatureWrapper Feat)
        {
            UpdateForm(Feat);
        }

        private void UpdateForm(FeatureWrapper Feat)
        {
            FormText = Strings.Feature + " : " + Feat.Name;
            ModifiedFormText = FormText + "*";

            this.Feat = Feat;
            if (Feat.Filter == null) Feat.Filter = "";

            this.Pages.Clear();

            this.Pages.Add(new Editors.Pages.Feature.MainPage(Feat));
            this.Pages.Add(new Editors.Pages.DescriptionPage(Feat));
            this.Pages.Add(new Editors.Pages.DocumentationPage(Feat));
            this.Pages.Add(new Editors.Pages.Feature.FilterPage(Feat));
            this.Pages.Add(new Editors.Pages.Feature.FlagsPage(Feat));
            this.Pages.Add(new Editors.Pages.Feature.ComponentDependenciesPage(Feat));
            this.Pages.Add(new Editors.Pages.Feature.FeatureDependenciesPage(Feat));


           this.Initialize();

            SetModified(false);
        }

       
        public override BaseWrapper  EditComponent
        {
            get
            {
                return this.Feature;
            }
        }

        public FeatureWrapper Feature { get { return this.Feat; } }

        public override void Save()
        {
            //try
            //{
            //    ApplyChanges();
            //    PK.Wrapper.SaveFeatureProj(this.Feat);
            //    SetModified(false);
            //}
            //catch (Exception ex)
            //{
            //    MessageBox.Show(this, ex.Message, Strings.Error, MessageBoxButtons.OK, MessageBoxIcon.Error);
            //}

        }

        void PKWrapper_LoadFeaturesAsyncCompleteEvent(object sender, EventArgs e)
        {
            if (this.Feat != null)
                this.SetFeat(PK.Wrapper.FindFeature(this.Feat.Guid));
        }
    }
}
