using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace PKStudio.Forms.BaseForms.ComponentEditor
{
    public partial class EditorPageBase : UserControl
    {
        public EditorPageBase()
        {
            InitializeComponent();
        }

        #region Fields

        private bool _modified = false;

        #endregion

        #region Properties

        /// <summary>
        /// Control name in tree
        /// </summary>
        public string NodeName {get; protected set;}

        public bool Modified
        {
            get
            {
                return this._modified;
            }
            set
            {
                this._modified = value;
            }
        }

        #endregion

        #region Metods
        /// <summary>
        /// Ru: Устанавливает свойство _modified в true и вызывет соответствующее событие
        /// Необходимо вызывать в наследнике при изменении опции
        /// 
        /// En: Sets _modified to true and fires event
        /// Must be called from inherit classes when changing options
        /// </summary>
        protected void ModifiedChange()
        {
            _modified = true;
            if (ModifiedEvent != null)
            {
                ModifiedEvent(this, EventArgs.Empty);
            }
        }

        public void Initialize()
        {
            _modified = false;
            OnInitialized();
        }

        public bool ApplyChanges()
        {
            if (this.Modified)
            {
                try
                {
                    this.Modified = OnApplyChanges();
                }
                catch (Exception e)
                {
                    MessageBox.Show(this, e.Message, Strings.Error, MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
            return this.Modified;
        }

        /// <summary>
        /// Apply changes
        /// </summary>
        /// <returns>Returns true, if the changes are saved successfully, false otherwise</returns>
        public virtual bool OnApplyChanges()
        {
            return false;
        }

        /// <summary>
        /// Initialize control
        /// </summary>
        protected virtual void OnInitialized()
        {
        }

        /// <summary>        
        /// Set Option, which will be managed by this control
        /// </summary>
        /// <param name="option"></param>
        //public virtual void SetOption(OptionsBase option)
        //{
        //    this.option = option;
        //}

        #endregion

        #region events
        public event EventHandler ModifiedEvent;
        #endregion
    }
}
