using System;
using System.Windows.Forms;
using PKStudio;

namespace OptionsHelper.Options
{   
    /// <summary>
    /// Ru: Базовый класс для отображения опций с помощью формы OptionsForm
    /// En: Base class to display options using the form OptionsForm
    /// </summary>
    public class OptionsControlBase : UserControl
    {

        #region Fields
        /// <summary>
        /// Modified field
        /// </summary>
        private bool _modified = false;

        /// <summary>
        /// Ru: Настройка, которой управляет этот контрол
        /// En: Option, which is managed by this control
        /// </summary>
        protected OptionsBase controlledOption;
        #endregion

        #region Properties

        /// <summary>
        /// Control name in tree
        /// </summary>
        public virtual string NodeName
        {
            get
            {
                return string.Empty;
            }
        }

        /// <summary>
        /// Modified property
        /// </summary>
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

        public OptionsBase ControlledOption { get { return this.controlledOption; } set { this.controlledOption = value; } }
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
                ModifiedEvent(this,EventArgs.Empty);
            }
        }

        /// <summary>
        /// Initialize method. Calls from OptionsControl.
        /// </summary>
        public void Initialize()
        {
            _modified = false;
            OnInitialized();
        }

        /// <summary>
        /// Apply changes. Calls from OptionsControl when user click Ok or Apply buttons
        /// </summary>
        public bool ApplyChanges()
        {
            if (this.Modified)
            {
                try
                {
                    this.Modified = !OnApplyChanges();
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
        public virtual void SetOption(OptionsBase ModifiedOption)
        {
            this.controlledOption = ModifiedOption;
        }

        #endregion

        #region events
        public event EventHandler ModifiedEvent;
        #endregion

        private void InitializeComponent()
        {
            this.SuspendLayout();
            // 
            // OptionsControlBase
            // 
            this.Name = "OptionsControlBase";
            this.Size = new System.Drawing.Size(430, 342);
            this.ResumeLayout(false);

        }
    }
}
