using Pik;
using System.Collections.Generic;
using System.IO;

namespace RAGE
{
  public static class RPF6FileNameHandler
  {
    public static Dictionary<uint, string> FileNames { get; set; }

    public static void LoadNames(Stream textFile = null)
    {
      if (RPF6FileNameHandler.FileNames == null)
        RPF6FileNameHandler.FileNames = new Dictionary<uint, string>();
      if (textFile == null)
        return;
      StreamReader streamReader = new StreamReader(textFile);
      int num = 1;
      while (!streamReader.EndOfStream)
      {
        string str = streamReader.ReadLine();
        uint hash = DataUtils.GetHash(str);
        if (!RPF6FileNameHandler.FileNames.ContainsKey(hash))
          RPF6FileNameHandler.FileNames.Add(hash, str);
        ++num;
      }
    }

    public static bool AddName(string name)
    {
      uint hash = DataUtils.GetHash(name);
      if (RPF6FileNameHandler.FileNames.ContainsKey(hash))
        return false;
      RPF6FileNameHandler.FileNames.Add(hash, name);
      return true;
    }

    public static void SaveNames()
    {
      StreamWriter streamWriter = new StreamWriter(AppUtils.OpenFile("ImportedFileNames.txt", FileMode.OpenOrCreate, FileAccess.ReadWrite, FileShare.Read));
      streamWriter.BaseStream.SetLength(0L);
      foreach (KeyValuePair<uint, string> fileName in RPF6FileNameHandler.FileNames)
        streamWriter.WriteLine(fileName.Value);
      streamWriter.Flush();
      streamWriter.Close();
    }
  }
}
