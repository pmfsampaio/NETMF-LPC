using System;
using System.Diagnostics;
using System.Reflection;
using Microsoft.Win32;
using PKStudio.ItemWrappers;


namespace PKStudio
{
    public class Helper
    {
        /// <summary>
        /// Get Porting Kit registry record
        /// </summary>
        /// <param name="keySubPath">Путь ключа</param>
        /// <param name="key">Ключ</param>
        /// <returns></returns>
        public static string GetPortingKitRegistryValue(string keySubPath, string key)
        {
            try
            {
                System.Version version = Assembly.GetEntryAssembly().GetName().Version;
                using (RegistryKey key2 = Registry.LocalMachine.OpenSubKey(@"Software\Microsoft\.NETMicroFrameworkPortingKit"))
                {
                    if (key2 == null)
                    {
                        return "xxxxx-xxx-xxxxxxx-xxxxx";
                    }
                    System.Version version2 = new System.Version(0, 0, 0, 0);
                    System.Version version3 = new System.Version(0, 0, 0, 0);
                    foreach (string str in key2.GetSubKeyNames())
                    {
                        if (str.Length >= 2)
                        {
                            System.Version version4 = new System.Version(str.Substring(1));
                            if ((version4.Major == version.Major) && (version4 > version3))
                            {
                                version3 = version4;
                            }
                            if (version4 > version2)
                            {
                                version2 = version4;
                            }
                        }
                    }
                    string str3 = null;
                    if (version3.Major != 0)
                    {
                        str3 = "v" + version3.ToString();
                    }
                    else if (version2.Major != 0)
                    {
                        str3 = "v" + version2.ToString();
                    }
                    if (!string.IsNullOrEmpty(str3))
                    {
                        string name = str3 + @"\" + keySubPath;
                        using (RegistryKey key3 = key2.OpenSubKey(name))
                        {
                            if (key3 == null)
                            {
                                return "xxxxx-xxx-xxxxxxx-xxxxx";
                            }
                            return (string)key3.GetValue(key);
                        }
                    }
                }
            }
            catch (FormatException)
            {
            }
            catch (ArgumentException)
            {
            }
            return null;
        }

        /// <summary>
        /// Get Micro Framework ProductID
        /// </summary>
        /// <returns></returns>
        public static string GetProductId()
        {
            string portingKitRegistryValue = Helper.GetPortingKitRegistryValue(@"Registration\DigitalProductID", "ProductID");
            if (string.IsNullOrEmpty(portingKitRegistryValue))
            {
                portingKitRegistryValue = "xxxxx-xxx-xxxxxxx-xxxxx";
            }
            return portingKitRegistryValue;
        }

        public static bool IsWindowsSolution(SolutionWrapper solution)
        {
            return (0 == string.Compare(solution.Processor.Name, "windows", true));
        }

        public class AssemblyInfoHelper
        {
            private static Assembly m_Assembly;

            public AssemblyInfoHelper(Assembly assembly)
            {
                m_Assembly = assembly;
            }

            private T CustomAttributes<T>()
                where T : Attribute
            {
                object[] customAttributes = m_Assembly.GetCustomAttributes(typeof(T), false);

                if ((customAttributes != null) && (customAttributes.Length > 0))
                {
                    return ((T)customAttributes[0]);
                }

                throw new InvalidOperationException();
            }

            public string Title
            {
                get
                {
                    return CustomAttributes<AssemblyTitleAttribute>().Title;
                }
            }

            public string Description
            {
                get
                {
                    return CustomAttributes<AssemblyDescriptionAttribute>().Description;
                }
            }

            public string Company
            {
                get
                {
                    return CustomAttributes<AssemblyCompanyAttribute>().Company;
                }
            }

            public string Product
            {
                get
                {
                    return CustomAttributes<AssemblyProductAttribute>().Product;
                }
            }

            public string Copyright
            {
                get
                {
                    return CustomAttributes<AssemblyCopyrightAttribute>().Copyright;
                }
            }

            public string Trademark
            {
                get
                {
                    return CustomAttributes<AssemblyTrademarkAttribute>().Trademark;
                }
            }

            public string AssemblyVersion
            {
                get
                {
                    return m_Assembly.GetName().Version.ToString();
                }
            }

            public string FileVersion
            {
                get
                {
                    FileVersionInfo fvi = FileVersionInfo.GetVersionInfo(m_Assembly.Location);
                    return fvi.FileVersion;
                }
            }

            public string Guid
            {
                get
                {
                    return CustomAttributes<System.Runtime.InteropServices.GuidAttribute>().Value;
                }
            }

            public string FileName
            {
                get
                {
                    FileVersionInfo fvi = FileVersionInfo.GetVersionInfo(m_Assembly.Location);
                    return fvi.OriginalFilename;
                }
            }

            public string FilePath
            {
                get
                {
                    FileVersionInfo fvi = FileVersionInfo.GetVersionInfo(m_Assembly.Location);
                    return fvi.FileName;
                }
            }
        }

    }
}
