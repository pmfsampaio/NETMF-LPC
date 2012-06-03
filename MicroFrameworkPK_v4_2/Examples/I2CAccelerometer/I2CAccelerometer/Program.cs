using System;
using System.Threading;
using Microsoft.SPOT;
using Microsoft.SPOT.Hardware;

namespace I2CAccelerometer
{
    /// <summary>
    /// Application to demonstate the I2C interface of the Kinetis Microframework port
    /// </summary>
    public class Program
    {
        // i2c address of MMA7660 accelerometer on K60 devboard
        private const int MMA7660Address = 0x4C;

        public static void Main()
        {
            using (MMA7660 accelerometer = new MMA7660(MMA7660Address))
            {
                while (true)
                {
                    MMA7660.XYZ result = accelerometer.GetXYZ();

                    // show result visual studio output window
                    Debug.Print("X = " + result.X.ToString() + ", Y = " + result.Y.ToString() + ", Z = " + result.Z.ToString());

                    // wait a bit before next reading
                    Thread.Sleep(250);
                }
            }
        }
    }
}
