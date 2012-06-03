using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Globalization;

namespace PKStudio.Dialogs.ManageProjectWizard.Pages
{
    public partial class ProcessorPropertiesPage : BasePage
    {
        public ProcessorPropertiesPage(WizardParams Params)
            : base(Params)
        {
            InitializeComponent();

            this.MemotyProfileCB.Items.AddRange(new object[] { "Minimal", "Small", "Medium", "Large" });
            this.MemotyProfileCB.SelectedIndex = 0;
        }

        public override string PageName
        {
            get
            {
                return ManageProjectAndSolutionWizardsStrings.IDS_PAGE_NAME_PROCESSOR_CFG;
            }
        }

        public override string PageDescription
        {
            get
            {
                return ManageProjectAndSolutionWizardsStrings.IDS_PAGE_DESCRIPTION_PROCESSOR_CFG;
            }
        }


        public override void BeforeShow()
        {
            if (Params.Solution.MemoryProfile != null)
            {
                string str = Params.Solution.MemoryProfile.ToLower();

                if (!(str == "extrasmall"))
                {
                    if (str == "small")
                    {
                        this.MemotyProfileCB.SelectedIndex = 1;
                    }
                    else if (str == "medium")
                    {
                        this.MemotyProfileCB.SelectedIndex = 2;
                    }
                    else if (str == "large")
                    {
                        this.MemotyProfileCB.SelectedIndex = 3;
                    }
                }
                else
                {
                    this.MemotyProfileCB.SelectedIndex = 0;
                }
            }

            this.SystemClockTB.Text = "0";
            this.SlowClockTB.Text = "0";
            this.RAMBaseTB.Text = "0x00000000";
            this.RAMSizeTB.Text = "0x00000000";
            this.FlashBaseTB.Text = "0x00000000";
            this.FlashSizeTB.Text = "0x00000000";

            if ((Params.Solution.SystemClockSpeed != 0) &&
                (Params.Solution.SlowClockSpeed != 0) &&
                (Params.Solution.RamBase != 0) &&
                (Params.Solution.RamLength != 0) &&
                (Params.Solution.FlashBase != 0) &&
                (Params.Solution.FlashLength != 0)
                )
            {
                this.SystemClockTB.Text = Params.Solution.SystemClockSpeed.ToString();
                this.SlowClockTB.Text = Params.Solution.SlowClockSpeed.ToString();
                this.RAMBaseTB.Text = "0x" + Params.Solution.RamBase.ToString("X08");
                this.RAMSizeTB.Text = "0x" + Params.Solution.RamLength.ToString("X08");
                this.FlashBaseTB.Text = "0x" + Params.Solution.FlashBase.ToString("X08");
                this.FlashSizeTB.Text = "0x" + Params.Solution.FlashLength.ToString("X08");
            }
            else
            {
                DefaultConfig DF = ProcCfgDefaults.GetDefaults(Params.Solution.Processor.Name);

                this.SystemClockTB.Text = DF.SystemClockSpeed.ToString();
                this.SlowClockTB.Text = DF.SlowClockSpeed.ToString();
                this.RAMBaseTB.Text = "0x" + DF.RamBase.ToString("X08");
                this.RAMSizeTB.Text = "0x" + DF.RamLength.ToString("X08");
                this.FlashBaseTB.Text = "0x" + DF.FlashBase.ToString("X08");
                this.FlashSizeTB.Text = "0x" + DF.FlashLength.ToString("X08");
            }

            this.OnShowNextBtn(validate());
        }

        public override void BeforeCloseOnNext()
        {
            int ramBase = 0;
            int ramSize = 0;
            int flashBase = 0;
            int flashSize = 0;
            int clockSpeed = 0;
            int slowClock = 0;

            string Str = "";
            string SelStr = ((string)this.MemotyProfileCB.SelectedItem).ToUpper();
            if (SelStr != null)
            {
                if (!(SelStr == "MINIMAL"))
                {
                    if (SelStr == "SMALL")
                    {
                        Str = "small";
                    }
                    else if (SelStr == "MEDIUM")
                    {
                        Str = "medium";
                    }
                    else if (SelStr == "LARGE")
                    {
                        Str = "large";
                    }
                }
                else
                {
                    Str = "extrasmall";
                }
            }
            Params.Solution.MemoryProfile = Str;



            bool res = validate(out ramBase, out ramSize, out flashBase, out flashSize, out clockSpeed, out slowClock);

            Params.Solution.RamBase = ramBase;
            Params.Solution.RamLength = ramSize;
            Params.Solution.FlashBase = flashBase;
            Params.Solution.FlashLength = flashSize;
            Params.Solution.SystemClockSpeed = clockSpeed;
            Params.Solution.SlowClockSpeed = slowClock;
        }

        private void RAMBaseTB_TextChanged(object sender, EventArgs e)
        {
            this.OnShowNextBtn(validate());
        }

        private void RAMSizeTB_TextChanged(object sender, EventArgs e)
        {
            this.OnShowNextBtn(validate());
        }

        private void FlashBaseTB_TextChanged(object sender, EventArgs e)
        {
            this.OnShowNextBtn(validate());
        }

        private void FlashSizeTB_TextChanged(object sender, EventArgs e)
        {
            this.OnShowNextBtn(validate());
        }

        private void SystemClockTB_TextChanged(object sender, EventArgs e)
        {
            this.OnShowNextBtn(validate());
        }

        private void SlowClockTB_TextChanged(object sender, EventArgs e)
        {
            this.OnShowNextBtn(validate());
        }

        private bool validate()
        {
            int ramBase = 0;
            int ramSize = 0;
            int flashBase = 0;
            int flashSize = 0;
            int clockSpeed = 0;
            int slowClock = 0;

            return validate(out ramBase, out ramSize, out flashBase, out flashSize, out clockSpeed, out slowClock);
        }

        private bool validate(out int ramBase, out int ramSize, out int flashBase, out int flashSize, out int clockSpeed, out int slowClock)
        {
            ramBase = 0;
            ramSize = 0;
            flashBase = 0;
            flashSize = 0;
            clockSpeed = 0;
            slowClock = 0;
            return ((((((this.RAMBaseTB.Text.Length > 0)) && ((this.RAMSizeTB.Text.Length > 0) && (this.FlashBaseTB.Text.Length > 0))) && (((this.FlashSizeTB.Text.Length > 0) && (this.SystemClockTB.Text.Length > 0)) && (this.ParseHexInt(this.FlashBaseTB.Text, out flashBase) && this.ParseHexInt(this.FlashSizeTB.Text, out flashSize)))) && ((this.ParseHexInt(this.RAMBaseTB.Text, out ramBase) && this.ParseHexInt(this.RAMSizeTB.Text, out ramSize)) && this.ParseHexInt(this.SystemClockTB.Text, out clockSpeed))) && this.ParseHexInt(this.SlowClockTB.Text, out slowClock));
        }

        private bool ParseHexInt(string text, out int val)
        {
            bool flag = true;
            val = 0;
            text = text.Trim().ToLower();
            try
            {
                if (text.StartsWith("0x"))
                {
                    text = text.Remove(0, 2);
                    val = int.Parse(text, NumberStyles.HexNumber);
                    return flag;
                }
                val = int.Parse(text);
            }
            catch
            {
                flag = false;
            }
            return flag;
        }
    }

    class DefaultConfig
    {
        public uint SystemClockSpeed { get; set; }
        public uint SlowClockSpeed { get; set; }
        public uint RamBase { get; set; }
        public uint RamLength { get; set; }
        public uint FlashBase { get; set; }
        public uint FlashLength { get; set; }
    }

    class ProcCfgDefaults
    {
        public static DefaultConfig GetDefaults(string Name)
        {
            DefaultConfig DF = new DefaultConfig();
            switch (Name.ToUpper())
            {
                case "AT91SAM7X":
                    DF.SystemClockSpeed = 1500000;
                    DF.SlowClockSpeed = 1500000;
                    DF.RamBase = 0x0;
                    DF.RamLength = 0x00020000;
                    DF.FlashBase = 0x00100000;
                    DF.FlashLength = 0x00080000;
                    break;
                case "AT91SAM9261":
                    DF.SystemClockSpeed = 6208000;
                    DF.SlowClockSpeed = 32768;
                    DF.RamBase = 0x20000000;
                    DF.RamLength = 0x04000000;
                    DF.FlashBase = 0x20000000;
                    DF.FlashLength = 0x04000000;
                    break;
                case "BF537":
                    DF.SystemClockSpeed = 600000000;
                    DF.SlowClockSpeed = 600000000;
                    DF.RamBase = 0x00000000;
                    DF.RamLength = 0x04000000;
                    DF.FlashBase = 0x10000000;
                    DF.FlashLength = 0x00400000;
                    break;
                case "CORTEXM3":
                    DF.SystemClockSpeed = 16000000;
                    DF.SlowClockSpeed = 16000000;
                    DF.RamBase = 0x10000000;
                    DF.RamLength = 0x02000000;
                    DF.FlashBase = 0x00000000;
                    DF.FlashLength = 0x40000000;
                    break;
                case "LPC22XX":
                    DF.SystemClockSpeed = 15000000;
                    DF.SlowClockSpeed = 15000000;
                    DF.RamBase = 0x81000000;
                    DF.RamLength = 0x01000000;
                    DF.FlashBase = 0x80000000;
                    DF.FlashLength = 0x02000000;
                    break;
                case "MC9328":
                    DF.SystemClockSpeed = 16000000;
                    DF.SlowClockSpeed = 16000000;
                    DF.RamBase = 0x08000000;
                    DF.RamLength = 0x02000000;
                    DF.FlashBase = 0x10000000;
                    DF.FlashLength = 0x01000000;
                    break;
                case "PXA271":
                    DF.SystemClockSpeed = 3250000;
                    DF.SlowClockSpeed = 3250000;
                    DF.RamBase = 0xA0000000;
                    DF.RamLength = 0x02000000;
                    DF.FlashBase = 0x00000000;
                    DF.FlashLength = 0x02000000;
                    break;
                case "TEMPLATE":
                    DF.SystemClockSpeed = 16000000;
                    DF.SlowClockSpeed = 16000000;
                    DF.RamBase = 0x08000000;
                    DF.RamLength = 0x02000000;
                    DF.FlashBase = 0x10000000;
                    DF.FlashLength = 0x01000000;
                    break;
                default:
                    DF.SystemClockSpeed = 0;
                    DF.SlowClockSpeed = 0;
                    DF.RamBase = 0x0;
                    DF.RamLength = 0x0;
                    DF.FlashBase = 0x0;
                    DF.FlashLength = 0x0;
                    break;
            }
            return DF;
        }
    }
}
