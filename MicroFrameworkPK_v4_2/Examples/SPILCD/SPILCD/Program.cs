using System;
using Microsoft.SPOT;

namespace SPILCD
{
    /// <summary>
    /// Application to demonstate the SPI interface of the Kinetis Microframework port
    ///
    /// *NOTE* this requires the TWR-LCD module to be setup for 4 wire SPI mode, set SW1 to:
    /// 
    ///  PIN | OFF/ON |
    ///   1    OFF
    ///   2    ON
    ///   3    ON
    ///   4    OFF
    ///   5    ON
    ///   6    ON
    ///   7    ON
    ///   8    OFF
    /// </summary>
    public class Program
    {
        public static void Main()
        {
            using (TWRLCD lcd = new TWRLCD())
            {
                // blank background
                lcd.Clear(0, 0, 319, 239, 0x0000);

                Random r = new Random();

                ushort x1, y1, x2, y2, color;

                while (true)
                {
                    x1 = (ushort) r.Next(319);
                    y1 = (ushort) r.Next(239);
                    x2 = (ushort) System.Math.Min(319, x1 + r.Next(319) + 1);
                    y2 = (ushort) System.Math.Min(239, y1 + r.Next(239) + 1);
                    color = (ushort) r.Next(0xFFFF);

                    // draw random rectangle
                    lcd.Clear(x1, y1, x2, y2, color);
                }
            }
        }

    }
}
