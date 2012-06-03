using System.Windows.Forms;
using System;
using PKStudio.ItemWrappers;

namespace PKStudio.Forms.Editors
{
    public partial class LibraryEditor : BaseForms.ComponentEditor.ComponentEditorBaseForm
    {
        public LibraryEditor()
            : base()
        {
            InitializeComponent();

            PK.Wrapper.LoadLibrariesAsyncCompleteEvent += new EventHandler(PKWrapper_LoadLibrariesAsyncCompleteEvent);
        }

        private LibraryWrapper Lib;

        /// <summary>
        /// Sets Libraray for edition
        /// </summary>
        /// <param name="LibCat"></param>
        public void SetLib(LibraryWrapper Lib)
        {
            UpdateForm(Lib);
        }

        private void UpdateForm(LibraryWrapper Lib)
        {
            FormText = Strings.Library+" : " + Lib.Name;
            ModifiedFormText = FormText + "*";

            this.Lib = Lib;

            this.Pages.Clear();

            this.Pages.Add(new Editors.Pages.Library.MainPage(Lib));
            this.Pages.Add(new Editors.Pages.DescriptionPage(Lib));
            this.Pages.Add(new Editors.Pages.DocumentationPage(Lib));
            this.Pages.Add(new Editors.Pages.Library.LibraryDependenciesPage(Lib));
            this.Pages.Add(new Editors.Pages.Library.LibraryCategoryPage(Lib));
            this.Pages.Add(new Editors.Pages.Library.ISASpecificPage(Lib));
            this.Pages.Add(new Editors.Pages.Library.ProcessorSpecificPage(Lib));
            
            //this.Pages.Add(new Editors.Pages.LibraryCategory.FlagsPage(LibCat));
            
            //this.Pages.Add(new Editors.Pages.LibraryCategory.FeatureAssociationsPage(LibCat));
            //this.Pages.Add(new Editors.Pages.LibraryCategory.TemplatesPage(LibCat));
            //this.Pages.Add(new Editors.Pages.LibraryCategory.LibraryProjCachePage(LibCat));

            this.Initialize();

            SetModified(false);
        }

        public LibraryWrapper Library { get { return this.Lib;} }

        public override BaseWrapper EditComponent
        {
            get
            {
                return this.Library;
            }
        }

        public override void Save()
        {
            //try
            //{
            //    ApplyChanges();
            //    PK.Wrapper.SaveLibraryProj(this.Lib);
            //    SetModified(false);
            //}
            //catch (Exception ex)
            //{
            //    MessageBox.Show(this, ex.Message, Strings.Error, MessageBoxButtons.OK, MessageBoxIcon.Error);
            //}
        }

        void PKWrapper_LoadLibrariesAsyncCompleteEvent(object sender, EventArgs e)
        {
            if (this.Lib != null)
                this.SetLib(PK.Wrapper.FindLibrary(this.Lib.Guid));
        }
    }
}
