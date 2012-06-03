using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Diagnostics;
using System.Threading;
using OptionsHelper.Options;
using PKStudio;
using PKStudio.Forms.Options.Options;
using System.IO;

namespace PKStudioLauncher
{
    class Program
    {
        static string PKStudioLauncherName = "PKStudioLauncher";
        static string OptionsPath = System.IO.Path.GetDirectoryName(System.Reflection.Assembly.GetExecutingAssembly().Location) + "\\options.dat";
        static string PKStudioPath = System.IO.Path.GetDirectoryName(System.Reflection.Assembly.GetExecutingAssembly().Location) + "\\PKStudio.exe";

        static void Main(string[] args)
        {
            foreach (Process proc in Process.GetProcessesByName(PKStudioLauncherName))
            {
                if (proc.Id != Process.GetCurrentProcess().Id)
                    return;
            }

            string tool = string.Empty;
            string toolPath = string.Empty;
            string PKPath = string.Empty;

            if (File.Exists(OptionsPath))
            {
                OptionsSerializer serializer = OptionsSerializer.BackState(OptionsPath);

                foreach (OptionsBase option in serializer.SOptions)
                {
                    EnvironmentOption envOption = option as EnvironmentOption;
                    if (envOption != null)
                    {
                        tool = EnvironmentOption.GetToolString(envOption.Tool);
                        toolPath = envOption.Path;
                    }

                    PKVersionOption verOption = option as PKVersionOption;
                    if (verOption != null)
                    {
                        PKPath = verOption.PKVersion.Path;
                    }
                }
            }

            string path = "";
            string portingKitRegistryValue = Environment.GetEnvironmentVariable("SPOCLIENT");
            string SpoClientPath = "";
            if (string.IsNullOrEmpty(portingKitRegistryValue) || !Directory.Exists(portingKitRegistryValue))
            {
                portingKitRegistryValue = PKPath;
            }
            if (string.IsNullOrEmpty(portingKitRegistryValue) || !Directory.Exists(portingKitRegistryValue))
            {
                portingKitRegistryValue = Helper.GetPortingKitRegistryValue("", "InstallRoot");
            }
            if (!string.IsNullOrEmpty(portingKitRegistryValue) && Directory.Exists(portingKitRegistryValue))
            {
                path = portingKitRegistryValue;
            }

            if (!Directory.Exists(path) || !Directory.Exists(path + @"\DeviceCode\Targets\"))
            {
                using (SetSPOForm of = new SetSPOForm())
                {
                    if (of.ShowDialog() != System.Windows.Forms.DialogResult.OK)
                    {
                        Console.WriteLine(".NET Micro Framework Porting Kit directory was not found. Waiting for exit...");
                        Process.GetCurrentProcess().WaitForExit();
                    }
                    else
                    {
                        if (Directory.Exists(path + @"\DeviceCode\Targets\"))
                            SpoClientPath = of.Path;
                        else
                        {
                            Console.WriteLine(".NET Micro Framework Porting Kit directory was not found. Waiting for exit...");
                            Process.GetCurrentProcess().WaitForExit();
                        }
                    }
                }
            }
            else
            {
                Environment.SetEnvironmentVariable("SPOCLIENT", path);
                SpoClientPath = path;
            }


            if (SpoClientPath.Substring(SpoClientPath.Length - 1, 1) != @"\") SpoClientPath += @"\";
            path = string.Format("{0}setenv_base.cmd {1} PORT {2}", SpoClientPath, tool, toolPath);

            foreach (Process proc in Process.GetProcessesByName("PKStudio"))
            {
                Console.WriteLine("Another running copy of PKStudio has been detected. Waiting for exit...");
                proc.WaitForExit();
            }
            if (File.Exists(PKStudioPath))
            {
                Process process = new Process();
                ProcessStartInfo info = process.StartInfo;
                info.FileName = Environment.ExpandEnvironmentVariables("%comspec%");
                info.RedirectStandardInput = true;
                info.UseShellExecute = false;
                info.WindowStyle = ProcessWindowStyle.Hidden;
                if (process.Start())
                {
                    process.StandardInput.WriteLine(path);                    
                    process.StandardInput.WriteLine(PKStudioPath);
                }
            }
            else
            {
                Console.WriteLine("PKStudio executable not found.");
            }
        }
    }
}
