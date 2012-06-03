using System;
using Microsoft.CSharp;
using System.CodeDom.Compiler;
using System.IO;
using System.Reflection;
using System.Text;
//using ScriptMain;
using System.Threading;
using System.Windows.Forms;

//namespace ScriptMain
//{
//    public abstract class ScriptBase
//    {
//        public bool Run()
//        {
//            return OnRun();
//        }
//        protected abstract bool OnRun();

//        public ScriptBase()
//        {
//        }

//        public bool Exists(string str)
//        {
//            return File.Exists(str);
//        }

//        public bool HasTrailingSlash(string str)
//        {
//            if ((str[str.Length - 1] == '\\') || (str[str.Length - 1] == '/'))
//                return true;
//            else
//                return false;
//        }
//    }
//}


//namespace Scripts
//{
//    public class ScriptEngine
//    {
//        public const string ScriptBaseFirst = "using System.Windows.Forms; namespace ScriptMain" +
//            "{" +
//                "public class ScriptMain : ScriptBase" +
//                "{" +
//                    "protected override bool OnRun()" +
//                    "{";

//        public const string ScriptBaseSecond = "}" +
//                "}" +
//            "};";

//        /// <summary>
//        /// Компилирует и выполняет скрипт
//        /// </summary>
//        /// <param name="src">Исходный код скрипта</param>
//        /// <param name="AppPath">Путь к сборке текущей программы</param>
//        /// <param name="CreateLog">Вести ли лог файл</param>
//        public static void CompileAndRun(string src, string AppPath, bool CreateLog, ref bool res)
//        {
//            res = false;


//            CSharpCodeProvider provider = null;
//            StreamWriter sw = null;
//            StreamWriter swn = null;

//            try
//            {
//                provider = new CSharpCodeProvider();

//                if (CreateLog)
//                {
//                    sw = new StreamWriter(Path.GetDirectoryName(AppPath) + "\\ScriptLog.txt", false);
//                    sw.Write("\r\n******************** " + DateTime.Now.ToString() + " ********************\r\n\r\n");
//                }
//                if (CreateLog) sw.Write("Create CSharpPrivider  " + provider.ToString() + "\r\n");
//                string filename = Path.GetTempFileName();
//                if (CreateLog) sw.Write("Create tempfile name:  " + filename.ToString() + "\r\n");
//                CompilerParameters parameters = new CompilerParameters();

//                parameters.GenerateInMemory = true;
//                parameters.GenerateExecutable = false;
//                parameters.OutputAssembly = filename;

//                if (CreateLog)
//                {
//                    sw.Write("Compile parameters: \r\n");
//                    sw.Write("GenerateInMemory  " + parameters.GenerateInMemory.ToString() + "\r\n");
//                    sw.Write("GenerateExecutable  " + parameters.GenerateExecutable.ToString() + "\r\n");
//                    sw.Write("OutputAssembly  " + parameters.OutputAssembly.ToString() + "\r\n");

//                    sw.Write("Add Assembly: \r\n");
//                }
//                //Добавляем ссылки на сборки. Они аналогичны сборкам использующимся в текущей программе
//                foreach (Assembly asm in AppDomain.CurrentDomain.GetAssemblies())
//                    if (parameters.ReferencedAssemblies.IndexOf(asm.ManifestModule.Name) < 0)
//                    {
//                        parameters.ReferencedAssemblies.Add(asm.Location);
//                        if (CreateLog) sw.Write(asm.Location.ToString() + "\r\n");
//                    }

//                //Ссылка на сборку текущей программы
//                //parameters.ReferencedAssemblies.Add("ScriptTests.exe");
//                parameters.ReferencedAssemblies.Add(AppPath);
//                if (CreateLog) sw.Write(AppPath.ToString() + "\r\n");

//                //Компилируем
//                if (CreateLog) sw.Write("Compile... \r\n");
//                CompilerResults result = provider.CompileAssemblyFromSource(parameters, src);

//                //Собираем ошибки
//                StringBuilder errorInfo = new StringBuilder();
//                //if (result.Errors.Count > 0)
//                //errorInfo.Append("При сборке возникли ошибки:\n");
//                foreach (CompilerError error in result.Errors)
//                {
//                    //(1789,63): error CS1002: ; expected            
//                    if (error.IsWarning)
//                        continue;
//                    errorInfo.Append("(" + "Line" + ": " + error.Line + "): error " + error.ErrorNumber + ": " + error.ErrorText);
//                    errorInfo.Append("\n");
//                }
//                if (!string.IsNullOrEmpty(errorInfo.ToString()))
//                {
//                    //Если были ошибки при компиляции - exeption
//                    if (CreateLog) sw.Write(errorInfo.ToString() + "\r\n");
//                    throw new Exception(errorInfo.ToString());
//                }
//                else
//                {
//                    bool scriptResult = false;
//                    //Выполняем скрипт
//                    if (CreateLog) sw.Write("Deleting tempfile filename" + " \r\n");
//                    if (File.Exists(filename)) File.Delete(filename);
//                    Type t = result.CompiledAssembly.GetType("ScriptMain.ScriptMain");
//                    if (CreateLog) sw.Write("Get type: " + t.ToString() + " \r\n");
//                    if (CreateLog) sw.Close();
//                    if (t != null)
//                    {
//                        try
//                        {
//                            if (CreateLog) swn = new StreamWriter(Path.GetDirectoryName(AppPath) + "\\ScriptLog.txt", true);
//                            ScriptBase s = (ScriptBase)Activator.CreateInstance(t);
//                            if (CreateLog) swn.Write("Create Instance :" + s.ToString() + "\r\n");
//                            if (CreateLog) swn.Write("Run... \r\n");
//                            scriptResult = s.Run();
//                            if (CreateLog) swn.Write("End \r\n");
//                            if (CreateLog) swn.Close();
//                        }
//                        catch (Exception ex)
//                        {
//                            MessageBox.Show(ex.ToString(), "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
//                        }
//                        finally
//                        {
//                            if (swn != null) swn.Close();
//                        }
//                        res = scriptResult;
//                    }
//                    else
//                        //throw new Exception("Не объявлен класс ScriptMain.ScriptMain!");
//                        throw new Exception();
//                }
//            }
//            finally
//            {
//                if (provider != null) provider.Dispose();
//                if (sw != null) sw.Close();                
//            }


//        }
//    }
//}
