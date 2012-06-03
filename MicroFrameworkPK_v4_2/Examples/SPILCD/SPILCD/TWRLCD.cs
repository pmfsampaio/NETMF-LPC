using System;
using Microsoft.SPOT;
using Microsoft.SPOT.Hardware;
using Microsoft.SPOT.Hardware.K60;
using System.Threading;

namespace SPILCD
{
    /// <summary>
    /// Simple interface to draw on the TWR-LCD module
    /// </summary>
    public class TWRLCD : IDisposable
    {
        // pixel size of the long side of the lcd 
        private const ushort LargeSideSize = 320;

        // pixel size of the short side of the lcd
        private const ushort ShortSideSize = 240;

        // spi interface to LCD
        private SPI _spi = new SPI(new SPI.Configuration((Cpu.Pin)Pins.GPIO_PIN_D11, false, 0, 0, false, false, 24000, SPI.SPI_module.SPI3));
        
        // toggle used to indicate the spi word is a command
        private  OutputPort _dc = new OutputPort((Cpu.Pin)Pins.GPIO_PIN_B17, true);

        public TWRLCD()
        {
            Initialise();
        }

        ~TWRLCD()
        {
            Dispose(false);
        }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        /// <summary>
        /// Dispose of managed and unmanged objects
        /// </summary>
        /// <param name="disposing">true if managed objects should be disposed</param>
        private void Dispose(bool disposing)
        {
            if (disposing)
            {
                _spi.Dispose();
            }
        }

        /// <summary>
        /// Initialise the LCD controller
        /// </summary>
        private void Initialise()
        {
            SetRegister(0x0010, 0x0001);
            SetRegister(0x0000, 0x0001);
            Thread.Sleep(20);

            SetRegister(0x0003, 0xAEAC);
            SetRegister(0x000C, 0x0007);
            SetRegister(0x000D, 0x000F);
            SetRegister(0x000E, 0x2900);
            SetRegister(0x001E, 0x00B3);
            Thread.Sleep(20);

            SetRegister(0x0001, 0x2B3F);
            SetRegister(0x0002, 0x0600);
            SetRegister(0x0010, 0x0000);
            SetRegister(0x0011, 0x60B0);
            Thread.Sleep(200);

            SetRegister(0x0005, 0x0000);
            SetRegister(0x0006, 0x0000);
            SetRegister(0x0016, 0xEF1C);
            SetRegister(0x0017, 0x0003);
            SetRegister(0x0007, 0x0233);
            SetRegister(0x000B, 0x5312);
            SetRegister(0x000F, 0x0000);
            Thread.Sleep(20);

            SetRegister(0x0041, 0x0000);
            SetRegister(0x0042, 0x0000);
            SetRegister(0x0048, 0x0000);
            SetRegister(0x0049, 0x013F);
            SetRegister(0x0044, 0xEF00);
            SetRegister(0x0045, 0x0000);
            SetRegister(0x0046, 0x013F);
            SetRegister(0x004A, 0x0000);
            SetRegister(0x004B, 0x0000);
            Thread.Sleep(20);

            SetRegister(0x0030, 0x0707);
            SetRegister(0x0031, 0x0704);
            SetRegister(0x0032, 0x0204);
            SetRegister(0x0033, 0x0201);
            SetRegister(0x0034, 0x0203);
            SetRegister(0x0035, 0x0204);
            SetRegister(0x0036, 0x0204);
            SetRegister(0x0037, 0x0502);
            SetRegister(0x003A, 0x0302);
            SetRegister(0x003B, 0x0500);
            SetRegister(0x0023, 0x0000);
            SetRegister(0x0024, 0x0000);
            Thread.Sleep(50);

            SetRegister(0x0011, 0x60a8);
        }

        /// <summary>
        /// Set a register on the LCD controller
        /// </summary>
        /// <param name="register">register to set</param>
        /// <param name="data">data to write</param>
        private void SetRegister(ushort register, ushort data)
        {
            _dc.Write(true);
            _spi.Write(new ushort[] { register });
            _dc.Write(false);
            _spi.Write(new ushort[] { data });
        }

        /// <summary>
        /// Clear the current window with the specified colour
        /// </summary>
        /// <param name="color">color to set</param>
        public void Clear(ushort x1, ushort y1, ushort x2, ushort y2, ushort color)
        {
            ushort Addr1 = (ushort)(ShortSideSize - 1 - y1);
            ushort Addr2 = x1;
            ushort x1_x2 = (ushort)((Addr1 << 8) + (ShortSideSize - 1 - y2));

            SetRegister(0x0044, x1_x2);
            SetRegister(0x0045, x1);
            SetRegister(0x0046, x2);
            SetRegister(0x004e, Addr1);
            SetRegister(0x004f, Addr2);

            _dc.Write(true);            
            _spi.Write(new ushort[] { 0x0022 });
            _dc.Write(false);

            // optimize erase - erase entire line at once
            ushort[] line = new ushort[(int) System.Math.Abs(x2 - x1) + 1];

            for (int x = 0; x < line.Length; x++)
            {
                line[x] = color;
            }

            for (ushort y = y1; y <= y2; y++)
            {
                _spi.Write(line);
            }
        }
    }
}
