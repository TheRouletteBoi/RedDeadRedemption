using System;
using System.Collections.Generic;
using System.IO;
using System.Reflection;
using System.Security.Cryptography;

public class EmbeddedAssembly
{
  private static Dictionary<string, Assembly> dic = (Dictionary<string, Assembly>) null;

  public static void Load(string embeddedResource, string fileName)
  {
    if (EmbeddedAssembly.dic == null)
      EmbeddedAssembly.dic = new Dictionary<string, Assembly>();
    byte[] numArray = (byte[]) null;
    using (Stream manifestResourceStream = Assembly.GetExecutingAssembly().GetManifestResourceStream(embeddedResource))
    {
      numArray = manifestResourceStream != null ? new byte[(int) manifestResourceStream.Length] : throw new Exception(embeddedResource + " is not found in Embedded Resources.");
      manifestResourceStream.Read(numArray, 0, (int) manifestResourceStream.Length);
      try
      {
        Assembly assembly = Assembly.Load(numArray);
        EmbeddedAssembly.dic.Add(assembly.FullName, assembly);
        return;
      }
      catch
      {
      }
    }
    bool flag = false;
    string path = "";
    using (SHA1CryptoServiceProvider cryptoServiceProvider = new SHA1CryptoServiceProvider())
    {
      string str1 = BitConverter.ToString(cryptoServiceProvider.ComputeHash(numArray)).Replace("-", string.Empty);
      path = Path.GetTempPath() + fileName;
      if (File.Exists(path))
      {
        byte[] buffer = File.ReadAllBytes(path);
        string str2 = BitConverter.ToString(cryptoServiceProvider.ComputeHash(buffer)).Replace("-", string.Empty);
        flag = str1 == str2;
      }
      else
        flag = false;
    }
    if (!flag)
      File.WriteAllBytes(path, numArray);
    Assembly assembly1 = Assembly.LoadFile(path);
    EmbeddedAssembly.dic.Add(assembly1.FullName, assembly1);
  }

  public static Assembly Get(string assemblyFullName) => EmbeddedAssembly.dic == null || EmbeddedAssembly.dic.Count == 0 || !EmbeddedAssembly.dic.ContainsKey(assemblyFullName) ? (Assembly) null : EmbeddedAssembly.dic[assemblyFullName];
}
