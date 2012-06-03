using System.Windows.Forms;
using System;
using PKStudio.ItemWrappers;

namespace PKStudio.Dialogs
{
    public partial class NewLibraryCategoryDialog : Form
    {
        public NewLibraryCategoryDialog()
        {
            InitializeComponent();
            this.LibraryCategory = null;
        }

        public LibraryCategoryWrapper LibraryCategory { get; set; }


        private void FillFields()
        {
            GroupsCb.Items.Clear();
            GroupsCb.Items.Add("");

            foreach (LibraryCategoryWrapper libCat in PK.Wrapper.GetLibraryCategories())
            {
                if (!GroupsCb.Items.Contains(libCat.Groups))
                {
                    GroupsCb.Items.Add(libCat.Groups);
                }
            }

            LevelCb.Items.Clear();
            LevelCb.Items.Add(LibraryLevelWrapper.CLR);
            LevelCb.Items.Add(LibraryLevelWrapper.HAL);
            LevelCb.Items.Add(LibraryLevelWrapper.PAL);
            LevelCb.Items.Add(LibraryLevelWrapper.Support);
            LevelCb.SelectedItem = LibraryLevelWrapper.CLR;            
        }


        public DialogResult ShowDialog(IWin32Window owner,LibraryCategoryWrapper LibCat)
        {
            this.Text = Strings.CloneLibraryCategory;
            this.LibraryCategory = LibCat;
            FillFields();

            if (GroupsCb.Items.Contains(LibCat.Groups)) GroupsCb.SelectedItem = LibCat.Groups;
            else
            {
                if (GroupsCb.Items.Count > 0) GroupsCb.SelectedIndex = 0;
            }

            NameTb.Text = PK.Wrapper.GenerateNewLibraryCategoryName(LibCat.Name);

            LevelCb.SelectedItem = LibCat.Level;

            return this.ShowDialog(owner);
        }

        public DialogResult ShowDialog(IWin32Window owner, string groups)
        {
            this.Text = Strings.NewLibraryCategory;
            this.LibraryCategory = null;
            FillFields();

            if (GroupsCb.Items.Contains(groups)) GroupsCb.SelectedItem = groups;
            else 
            {
                if (GroupsCb.Items.Count > 0) GroupsCb.SelectedIndex = 0;
            }

            NameTb.Text = PK.Wrapper.GenerateNewLibraryCategoryName("NewLibraryCategory" + LevelLbl.Text);

            return this.ShowDialog(owner);
        }


        
        #region Button events
        private void CancelBtn_Click(object sender, System.EventArgs e)
        {
            this.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.Close();
        }

        private void OtBtn_Click(object sender, System.EventArgs e)
        {
            try
            {
                if (!PK.Wrapper.CheckLibraryCategoryName(NameTb.Text + LevelLbl.Text))
                {
                    if (this.LibraryCategory != null)
                    {
                        this.LibraryCategory = PK.Wrapper.CloneLibraryCategory(this.LibraryCategory, NameTb.Text + LevelLbl.Text, GroupsCb.Text, (LibraryLevelWrapper)LevelCb.SelectedItem);
                    }
                    else
                    {
                        this.LibraryCategory = PK.Wrapper.CreateLibraryCategory(NameTb.Text + LevelLbl.Text, GroupsCb.Text, (LibraryLevelWrapper)LevelCb.SelectedItem);
                    }
                    this.DialogResult = System.Windows.Forms.DialogResult.OK;
                    this.Close();
                }
                else throw new ArgumentException(Strings.LibraryCategory + " \"" + NameTb.Text + LevelLbl.Text+"\"" + Strings.AlreadyExist+".");
            }
            catch (Exception ex)
            {
                MessageBox.Show(this, ex.Message, Strings.Error, MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
        #endregion



        private void LevelCb_SelectedIndexChanged(object sender, System.EventArgs e)
        {
            LevelLbl.Text = "_" + LevelCb.Text;
        }
    }
}
