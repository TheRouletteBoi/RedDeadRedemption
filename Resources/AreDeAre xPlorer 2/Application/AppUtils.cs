﻿using System.Drawing;
using System.IO;
using System.Reflection;
using System.Windows.Forms;

public static class AppUtils
{
  public static Stream GetResourceAsStream(string resName) => Assembly.GetExecutingAssembly().GetManifestResourceStream(string.Format("AreDeAre_xPlorer_2.Resources.{0}", (object) resName));

  public static string GetAppPath() => Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location);

  public static Stream OpenFile(
    string name,
    FileMode mode,
    FileAccess access,
    FileShare share)
  {
    return (Stream) File.Open(string.Format("{0}\\{1}", (object) AppUtils.GetAppPath(), (object) name), mode, access, share);
  }

  public static Stream CreateFile(string name) => (Stream) File.Create(string.Format("{0}\\{1}", (object) AppUtils.GetAppPath(), (object) name));

  public static void CreateDirectory(string name) => Directory.CreateDirectory(string.Format("{0}\\{1}", (object) AppUtils.GetAppPath(), (object) name));

  public static bool FileExists(string name) => File.Exists(string.Format("{0}\\{1}", (object) AppUtils.GetAppPath(), (object) name));

  public static bool DirectoryExists(string dir) => Directory.Exists(string.Format("{0}\\{1}", (object) AppUtils.GetAppPath(), (object) dir));

  public static DirectoryInfo GetDirInfo(string dir) => new DirectoryInfo(string.Format("{0}\\{1}", (object) AppUtils.GetAppPath(), (object) dir));

  public static string GetPath(string p) => string.Format("{0}\\{1}", (object) AppUtils.GetAppPath(), (object) p);

  public static string GetCompactedString(string stringToCompact, Font font, int maxWidth)
  {
    string text = string.Copy(stringToCompact);
    Size proposedSize = new Size(maxWidth, 0);
    TextFormatFlags flags = TextFormatFlags.ModifyString | TextFormatFlags.PathEllipsis;
    TextRenderer.MeasureText(text, font, proposedSize, flags);
    return text;
  }

  public static string TruncString(string myStr, int THRESHOLD) => myStr.Length > THRESHOLD ? myStr.Substring(0, THRESHOLD) + "..." : myStr;
}
