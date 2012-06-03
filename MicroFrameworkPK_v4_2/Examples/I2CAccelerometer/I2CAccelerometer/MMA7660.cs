using System;
using Microsoft.SPOT;
using Microsoft.SPOT.Hardware;
using System.Threading;

namespace I2CAccelerometer
{
    /// <summary>
    /// Interface to the MMA7660 Accelerometer
    /// </summary>
    public class MMA7660 : IDisposable
    {
        // run at 400khz
        private const int ClockRateKhz = 400;

        // I2C interface
        private I2CDevice _i2c;
        private I2CDevice.I2CTransaction[] _xRead;
        private I2CDevice.I2CTransaction[] _yRead;
        private I2CDevice.I2CTransaction[] _zRead;
        
        // cache for i2c response
        private byte[] _xaxis = new byte[1];
        private byte[] _yaxis = new byte[1];
        private byte[] _zaxis = new byte[1];

        /// <summary>
        /// Tilt position details
        /// </summary>
        public struct XYZ 
        {
            public int X;
            public int Y;
            public int Z;

            public XYZ(int x, int y, int z)
            {
                this.X = x;
                this.Y = y;
                this.Z = z;
            }
        }
         
        public MMA7660(ushort address)
        {
            _i2c = new I2CDevice(new I2CDevice.Configuration(address, ClockRateKhz));

            // put into sleep mode while we setup
            SetRegister(0x07, 0x00);
            
            // disable sleep counter
            SetRegister(0x05, 0x00);

            // disable interrupt
            SetRegister(0x06, 0x10);

            // disable tap detection
            SetRegister(0x09, 0xE0);

            // 32 samples per second + average of 4
            SetRegister(0x08, 0x62);

            // tap debounce count to zero
            SetRegister(0x0A, 0x00);
            
            // enable
            SetRegister(0x07, 0x41);

            // give it a bit to get a sample
            Thread.Sleep(125);
            
            // cache the x,y,z i2c transactions
            _xRead = new I2CDevice.I2CTransaction[] {
                I2CDevice.CreateWriteTransaction(new byte[] {0x00}),
                I2CDevice.CreateReadTransaction(_xaxis),
            };

            _yRead = new I2CDevice.I2CTransaction[] {
                I2CDevice.CreateWriteTransaction(new byte[] {0x01}),
                I2CDevice.CreateReadTransaction(_yaxis),
            };

            _zRead = new I2CDevice.I2CTransaction[] {
                I2CDevice.CreateWriteTransaction(new byte[] {0x02}),
                I2CDevice.CreateReadTransaction(_zaxis),
            };
        }

        ~MMA7660()
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
                _i2c.Dispose();
            }            
        }

        /// <summary>
        /// Sets a register with given parameter
        /// </summary>
        /// <param name="register">register to set</param>
        /// <param name="data">value to set to</param>
        private void SetRegister(byte register, byte data)
        {
            // Disable tap detection
            I2CDevice.I2CTransaction[] i2cCommand = new I2CDevice.I2CTransaction[] {
               I2CDevice.CreateWriteTransaction(new byte[] { register, data }),
            };

            if (_i2c.Execute(i2cCommand, 1000) == 0)
            {
                throw new Exception("Set Register Failed [" + register.ToString() + "," + data.ToString() + "]" );
            }
        }

        /// <summary>
        /// Converts the return value from the accelerometer into a signed integer
        /// </summary>
        /// <param name="input">input byte</param>
        /// <returns>converted value</returns>
        private int Convert(byte input)
        {
            int result = input;

            result &= ~0x40;

            if ((result & 0x20) != 0)
            {
                result |= 0xE0;
            }
            
            return ((sbyte)((byte)(0xFF & result)));
        }

        /// <summary>
        /// Get the tilt position
        /// </summary>
        /// <returns>tilt position</returns>
        public XYZ GetXYZ()
        {  
            if (_i2c.Execute(_xRead, 1000) == 0)
            {
                throw new Exception("Failed to read X");
            }

            if (_i2c.Execute(_yRead, 1000) == 0)
            {
                throw new Exception("Failed to read Y");
            }
                        
            if (_i2c.Execute(_zRead, 1000) == 0)
            {
                throw new Exception("Failed to read Z");
            }

            return new XYZ(Convert(_xaxis[0]), Convert(_yaxis[0]), Convert(_zaxis[0]));
        }
    }
}
