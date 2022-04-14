using System;
using System.IO;
using System.Reflection;

public static class AppGlobals
{
  private static DateTime buildDate = new FileInfo(Assembly.GetExecutingAssembly().Location).LastWriteTime;
  public static string BuildDate = string.Format("{0}{1}{2}", (object) AppGlobals.buildDate.Month, (object) AppGlobals.buildDate.Day, (object) (AppGlobals.buildDate.Year % 100));
  public static string Version = "0.0.0";
  public static AppGlobals.PlatformEnum Platform = AppGlobals.PlatformEnum.Xbox;
  public static byte[] EncryptionKey = new byte[32]
  {
    (byte) 183,
    (byte) 98,
    (byte) 223,
    (byte) 182,
    (byte) 226,
    (byte) 178,
    (byte) 198,
    (byte) 222,
    (byte) 175,
    (byte) 114,
    (byte) 42,
    (byte) 50,
    (byte) 210,
    (byte) 251,
    (byte) 111,
    (byte) 12,
    (byte) 152,
    (byte) 163,
    (byte) 33,
    (byte) 116,
    (byte) 98,
    (byte) 201,
    (byte) 196,
    (byte) 237,
    (byte) 173,
    (byte) 170,
    (byte) 46,
    (byte) 208,
    (byte) 221,
    (byte) 249,
    (byte) 47,
    (byte) 16
  };

  public static char PlatformChar
  {
    get
    {
      int num;
      switch (AppGlobals.Platform)
      {
        case AppGlobals.PlatformEnum.PS3:
          num = 99;
          break;
        case AppGlobals.PlatformEnum.Xbox:
          num = 120;
          break;
        default:
          num = 117;
          break;
      }
      return (char) num;
    }
  }

  public static string PlatformString
  {
    get
    {
      string str;
      switch (AppGlobals.Platform)
      {
        case AppGlobals.PlatformEnum.PS3:
          str = "PS3";
          break;
        case AppGlobals.PlatformEnum.Xbox:
          str = "Xbox 360";
          break;
        default:
          str = "INVALID_PLAT";
          break;
      }
      return str;
    }
  }

  public static class Settings
  {
    public const int SettingsVersion = 2;
    public static bool WriteFilesInOffsetOrder;
    public static bool MakeFileDirectoryListing;
    public static bool MakeDiffDataFile;
    public static bool MakeFileInfoData;
    public static bool WriteDecryptedTOC;
    public static bool WriteTOCOrder;
    public static bool WriteRSCInfo;

    public static void Save(Stream xOut)
    {
      BinaryWriter binaryWriter = new BinaryWriter(xOut);
      binaryWriter.Write(2);
      binaryWriter.Write(AppGlobals.Settings.MakeFileDirectoryListing);
      binaryWriter.Write(AppGlobals.Settings.MakeDiffDataFile);
      binaryWriter.Write(AppGlobals.Settings.MakeFileInfoData);
      binaryWriter.Write(AppGlobals.Settings.WriteDecryptedTOC);
      binaryWriter.Write(AppGlobals.Settings.WriteTOCOrder);
      binaryWriter.Write(AppGlobals.Settings.WriteRSCInfo);
      binaryWriter.Close();
    }

    public static void Load(Stream xIn)
    {
      BinaryReader binaryReader = new BinaryReader(xIn);
      if (binaryReader.ReadInt32() == 2)
      {
        AppGlobals.Settings.MakeFileDirectoryListing = binaryReader.ReadBoolean();
        AppGlobals.Settings.MakeDiffDataFile = binaryReader.ReadBoolean();
        AppGlobals.Settings.MakeFileInfoData = binaryReader.ReadBoolean();
        AppGlobals.Settings.WriteDecryptedTOC = binaryReader.ReadBoolean();
        AppGlobals.Settings.WriteTOCOrder = binaryReader.ReadBoolean();
        AppGlobals.Settings.WriteRSCInfo = binaryReader.ReadBoolean();
      }
      binaryReader.Close();
    }
  }

  public enum PlatformEnum
  {
    None = 0,
    PS3 = 4096, // 0x00001000
    Xbox = 8192, // 0x00002000
  }
}
