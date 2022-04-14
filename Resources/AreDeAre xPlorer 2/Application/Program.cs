using AreDeAre_xPlorer_2.Forms;
using DevExpress.Skins;
using DevExpress.UserSkins;
using RAGE;
using System;
using System.IO;
using System.Media;
using System.Reflection;
using System.Windows.Forms;

namespace AreDeAre_xPlorer_2
{
  internal static class Program
  {
    [STAThread]
    private static void Main(string[] args)
    {
      Application.EnableVisualStyles();
      Application.SetCompatibleTextRenderingDefault(false);
      BonusSkins.Register();
      SkinManager.EnableFormSkins();
      AppDomain.CurrentDomain.AssemblyResolve += new ResolveEventHandler(Program.AreDeArexPlorer2_AssemblyResolve);
      AppDomain.CurrentDomain.UnhandledException += new UnhandledExceptionEventHandler(Program.AreDeArexPlorer2_UnhandledException);
      if (!AppUtils.FileExists("xcompress32.dll"))
        throw new Exception("Could not find \"xcompress32.dll\"");
      string embeddedResource1 = "AreDeAre_xPlorer_2.Resources.betterlistviewexpress-net45.dll";
      string embeddedResource2 = "AreDeAre_xPlorer_2.Resources.ICSharpCode.SharpZipLib.dll";
      string embeddedResource3 = "AreDeAre_xPlorer_2.Resources.PikIO.dll";
      EmbeddedAssembly.Load(embeddedResource1, "betterlistviewexpress-net45.dll");
      EmbeddedAssembly.Load(embeddedResource2, "ICSharpCode.SharpZipLib.dll");
      EmbeddedAssembly.Load(embeddedResource3, "PikIO.dll");
      PlatformSelectionForm platformSelectionForm = new PlatformSelectionForm();
      int num1 = (int) platformSelectionForm.ShowDialog();
      if ((uint) platformSelectionForm.SelectedPlatform <= 0U)
        return;
      AppGlobals.Platform = platformSelectionForm.SelectedPlatform;
      string name1 = AppGlobals.Platform == AppGlobals.PlatformEnum.Xbox ? "knownXbox360FileNames.txt" : "knownPS3FileNames.txt";
      string name2 = "ImportedFileNames.txt";
      if (AppUtils.FileExists(name1))
      {
        Stream textFile1 = AppUtils.OpenFile(name1, System.IO.FileMode.Open, FileAccess.ReadWrite, FileShare.Read);
        RPF6FileNameHandler.LoadNames(textFile1);
        textFile1.Close();
        if (AppUtils.FileExists(name2))
        {
          Stream textFile2 = AppUtils.OpenFile(name2, System.IO.FileMode.Open, FileAccess.Read, FileShare.ReadWrite);
          RPF6FileNameHandler.LoadNames(textFile2);
          textFile2.Close();
        }
        if (args.Length != 0 && Path.GetExtension(args[0]) == ".xtpc")
        {
          Stream stream = (Stream) File.Open(args[0], System.IO.FileMode.Open);
          if (RPFCommandFile.IsValidCommandFile(stream))
          {
            NewWorkForm newWorkForm = new NewWorkForm(new RPFCommandFile(stream), stream);
            if (!newWorkForm.Done)
            {
              int num2 = (int) newWorkForm.ShowDialog();
            }
            SystemSounds.Asterisk.Play();
          }
          else
          {
            int num3 = (int) MessageBox.Show(string.Format("\"{0}\" was not a valid command file.", (object) args[0]), "Invalid Command File", MessageBoxButtons.OK, MessageBoxIcon.Hand);
          }
        }
        else
        {
          AppGlobals.Platform = platformSelectionForm.SelectedPlatform;
          AreDeAre_xPlorer_2.Forms.Main main = new AreDeAre_xPlorer_2.Forms.Main();
          if ((uint) args.Length > 0U)
            main.LoadRPF(args[0]);
          Application.Run((Form) main);
        }
      }
      else
      {
        int num4 = (int) MessageBox.Show(string.Format("Could not find {0}\r\nApplication will now exit.", (object) name1), "Error - File Not Found", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }
    }

    private static void AreDeArexPlorer2_UnhandledException(
      object sender,
      UnhandledExceptionEventArgs e)
    {
      int num = (int) MessageBox.Show(string.Format("An Error Has Occurred:\r\n{0}\r\n\r\n{1}\r\n\r\nThe application will now exit.", (object) ((Exception) e.ExceptionObject).Message, (object) ((Exception) e.ExceptionObject).StackTrace), "Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      Application.Exit();
    }

    private static Assembly AreDeArexPlorer2_AssemblyResolve(
      object sender,
      ResolveEventArgs args)
    {
      Console.WriteLine(string.Format("Resolving Assembly: {0}", (object) args.Name));
      return EmbeddedAssembly.Get(args.Name);
    }
  }
}
