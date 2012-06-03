using System;
using Microsoft.SPOT.Hardware;
using System.Runtime.CompilerServices;


namespace Microsoft.SPOT.Hardware
{
    /// <summary>
    /// type for PWM port
    /// </summary>
    public class PWM : IDisposable
    {
        static private readonly int c_ToMicroSeconds = 1000000;

        //--//
        
        /// <summary>
        /// The pin used for this PWM port, can be set only when the port is constructed
        /// </summary>
        private readonly Cpu.Pin m_pin;
        /// <summary>
        /// The pin used for this PWM port, can be set only when the port is constructed
        /// </summary>
        private readonly Cpu.PWMChannel m_channel;
        /// <summary>
        /// The frequency of the PWM wave in Hz
        /// </summary>
        private uint m_period;
        /// <summary>
        /// The Duty Cycle of the PWM wave a a percentage [0-100]
        /// </summary>
        private uint m_duration;
        /// <summary>
        /// Polarity of the wave, it determines the idle state of the port
        /// </summary>
        private bool m_invert;

        //--//

        /// <summary>
        /// Build an instance of the PWM type
        /// </summary>
        /// <param name="channel">The channel to use</param>
        /// <param name="frequency_Hz">The frequency of the pulse in Hz</param>
        /// <param name="dutyCycle">The duty cycle of the pulse as a fraction of unity.  Value should be between 0.0 and 1.0</param>
        /// <param name="invert">Whether the output should be inverted or not</param>
        public PWM(Cpu.PWMChannel channel, double frequency_Hz, double dutyCycle, bool invert)
        {
            HardwareProvider hwProvider = HardwareProvider.HwProvider;

            if(hwProvider == null) throw new InvalidOperationException();

            m_pin = hwProvider.GetPwmPinForChannel(channel);
            m_channel = channel;
            //--//
            m_period = PeriodFromFrequency(frequency_Hz);
            m_duration = DurationFromDutyCycleAndPeriod(dutyCycle, m_period);
            m_invert = invert;
            //--//
            try
            {
                Init();
                
                Commit();
                
                Port.ReservePin(m_pin, true);
            }
            catch
            {
                Dispose(false);
            }
        }

        /// <summary>
        /// Build an instance of the PWM type
        /// </summary>
        /// <param name="channel">The channel</param>
        /// <param name="period_us">The period of the pulse in micro seconds</param>
        /// <param name="duration_us">The duration of the pulse in micro seconds.  The value should be a fraction of the period</param>
        /// <param name="invert">Whether the output should be inverted or not</param>
        public PWM(Cpu.PWMChannel channel, uint period_us, uint duration_us, bool invert)
        {
            HardwareProvider hwProvider = HardwareProvider.HwProvider;

            if (hwProvider == null) throw new InvalidOperationException();

            m_pin = hwProvider.GetPwmPinForChannel(channel);
            m_channel = channel;
            //--//
            m_period = period_us;
            m_duration = duration_us;
            m_invert = invert;
            //--//
            try
            {
                Init();
                
                Commit();
                
                Port.ReservePin(m_pin, true);
            }
            catch
            {
                Dispose(false);
            }
        }

        /// <summary>
        /// Finalizer for the PWM type, will stop the port if still running and un-reserve the underlying pin
        /// </summary>
        ~PWM()
        {
            Dispose(false);
        }

        /// <summary>
        /// Diposes the PWM type, will stop the port if still running and un-reserve the PIN
        /// </summary>
        public void Dispose()
        {
            Dispose(true);
        }

        /// <summary>
        /// Starts the PWM port for an indefinite amount of time
        /// </summary>
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern public void Start();

        /// <summary>
        /// Stop the PWM port
        /// </summary>
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern public void Stop();

        //--//

        /// <summary>
        /// The GPIO pin chosen for the selected channel
        /// </summary>
        public Cpu.Pin Pin
        {
            get
            {
                return m_pin;
            }
        }

        /// <summary>
        /// Gets and sets the frequency of the pulse
        /// </summary>
        public double Frequency
        {
            get
            {
                return FrequencyFromPeriod(m_period);
            }
            set
            {
                m_period = PeriodFromFrequency(value);
                Commit();
                //--//
            }
        }


        /// <summary>
        /// Gets and sets the duty cycle of the pulse as a fraction of unity. Value should be included between 0.0 and 1.0
        /// </summary>
        public double DutyCycle
        {
            get
            {
                return DutyCycleFromDurationAndPeriod(m_period, m_duration);
            }
            set
            {
                m_duration = DurationFromDutyCycleAndPeriod(value, m_period);
                Commit();
                //--//
            }
        }


        /// <summary>
        /// Gets and sets the Frequency of the pulse
        /// </summary>
        public uint Period
        {
            get
            {
                return m_period;
            }
            set
            {
                m_period = value;
                Commit();
                //--//
            }
        }


        /// <summary>
        /// Gets and sets the duration of the pulse.  Value should be a frction of the period
        /// </summary>
        public uint Duration
        {
            get
            {
                return m_duration;
            }
            set
            {
                m_duration = value;
                Commit();
                //--//
            }
        }

        //--//

        /// <summary>
        /// Starts a number of PWM ports at the same time
        /// </summary>
        /// <param name="ports"></param>
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern public static void Start(PWM[] ports);

        /// <summary>
        /// Stops a number of PWM ports at the same time
        /// </summary>
        /// <param name="ports"></param>
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern public static void Stop(PWM[] ports);

        //--//

        protected void Dispose(bool disposing)
        {
            try
            {
                Stop();
            }
            catch
            {
                // hide all exceptions...
            }
            finally
            {
                Uninit();

                Port.ReservePin(m_pin, false);
            }
        }

        /// <summary>
        /// Moves values to the HAL
        /// </summary>
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern protected void Commit();

        /// <summary>
        /// Initializes the controller
        /// </summary>
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern protected void Init();

        /// <summary>
        /// Uninitializes the controller
        /// </summary>
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern protected void Uninit();

        //--//

        private static uint PeriodFromFrequency(double f)
        {
            return (uint)((1 / f) * c_ToMicroSeconds);
        }

        private static uint DurationFromDutyCycleAndPeriod(double dutyCycle, double period)
        {
            if (period <= 0)
                throw new ArgumentException();

            if (dutyCycle < 0)
                return 0;

            if (dutyCycle > 1)
                return 1;

            return (uint)(dutyCycle * period);            
        }

        private static double FrequencyFromPeriod(double period)
        {
            return (1 / period) * c_ToMicroSeconds;
        }

        private static double DutyCycleFromDurationAndPeriod(double period_us, double duration_us)
        {
            if (period_us <= 0)
                throw new ArgumentException();

            if (duration_us < 0)
                return 0;

            if (duration_us > period_us)
                return 1;

            return (duration_us / period_us);
        }
    }
}

