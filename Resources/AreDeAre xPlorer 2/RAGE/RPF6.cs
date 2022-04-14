using Pik;
using Pik.IO;
using RAGE.ExtraClasses;
using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;

namespace RAGE
{
  public class RPF6
  {
    public static EventHandler<RPF6Report> OnOperation;

    public static string Gen_PossibleSectorCalc(long size, long pos)
    {
      long num1 = pos >> 23;
      long num2 = size + pos;
      long num3 = num1;
      long num4 = num2 + -1L >> 23;
      return num3 <= num4 ? string.Format("{0}|{1}", (object) num4, (object) num3) : throw new Exception("wat");
    }

    public static byte[] CurrentEncryptionKey { get; set; }

    public RPF6.RPF6Header Header { get; set; }

    public RPF6.RPF6TOC TOC { get; set; }

    public PikIO RPFIO { get; set; }

    public RPF6(Stream xIn)
    {
      PikIO io = new PikIO(xIn, PikIO.Endianess.Big);
      this.RPFIO = io;
      if (RPF6.OnOperation != null)
        RPF6.OnOperation((object) this, new RPF6Report()
        {
          StatusOperationText = "Reading",
          StatusText = nameof (Header),
          TitleText = "Reading..."
        });
      this.Header = RPF6.RPF6Header.ReadHeader(io);
      if (RPF6.OnOperation != null)
        RPF6.OnOperation((object) this, new RPF6Report()
        {
          StatusOperationText = "Reading",
          StatusText = nameof (TOC),
          TitleText = "Reading..."
        });
      this.TOC = RPF6.RPF6TOC.ReadTOC(io, this);
      if (RPF6.OnOperation == null)
        return;
      RPF6.OnOperation((object) this, new RPF6Report()
      {
        StatusOperationText = "Finished",
        StatusText = nameof (TOC),
        TitleText = "Done Reading"
      });
    }

    public RPF6()
    {
      this.Header = new RPF6.RPF6Header();
      this.TOC = new RPF6.RPF6TOC(this);
    }

    public void CloseAllStreams()
    {
      foreach (RPF6.RPF6TOC.TOCSuperEntry superEntry in this.TOC.SuperEntries)
      {
        if (superEntry.CustomDataStream != null)
        {
          superEntry.CustomDataStream.Close();
          superEntry.CustomDataStream = (Stream) null;
        }
      }
    }

    public void Write(Stream xOut, bool writeInOffsetOrder)
    {
      PikIO io = new PikIO(xOut, PikIO.Endianess.Big);
      if (RPF6.OnOperation != null)
        RPF6.OnOperation((object) this, new RPF6Report()
        {
          StatusOperationText = "Rebuilding",
          StatusText = "TOC",
          TitleText = "Rebuilding.."
        });
      this.TOC.Rebuild();
      if (RPF6.OnOperation != null)
        RPF6.OnOperation((object) this, new RPF6Report()
        {
          StatusOperationText = "Writing",
          StatusText = "Header",
          TitleText = "Writing.."
        });
      RPF6.RPF6Header.WriteHeader(io, this.Header);
      long position = io.Position;
      io.WriteBytes(new byte[this.Header.TOCSize]);
      io.WriteBytes(new byte[DataUtils.NumLeftTill((int) io.Length, 2048) == 2048 ? 0 : DataUtils.NumLeftTill((int) io.Length, 2048)]);
      while (io.Position < 671743L)
        io.WriteByte((byte) 0);
      List<RPF6.RPF6TOC.TOCSuperEntry> tocSuperEntryList1 = new List<RPF6.RPF6TOC.TOCSuperEntry>();
      List<RPF6.RPF6TOC.TOCSuperEntry> tocSuperEntryList2 = new List<RPF6.RPF6TOC.TOCSuperEntry>();
      foreach (RPF6.RPF6TOC.TOCSuperEntry superEntry in this.TOC.SuperEntries)
      {
        if (!superEntry.IsDir)
        {
          if (superEntry.Entry.AsFile.FlagInfo.IsResource)
            tocSuperEntryList2.Add(superEntry);
          else
            tocSuperEntryList1.Add(superEntry);
        }
      }
      List<RPF6.RPF6TOC.TOCSuperEntry> tocSuperEntryList3 = new List<RPF6.RPF6TOC.TOCSuperEntry>();
      tocSuperEntryList3.AddRange((IEnumerable<RPF6.RPF6TOC.TOCSuperEntry>) tocSuperEntryList2);
      tocSuperEntryList3.AddRange((IEnumerable<RPF6.RPF6TOC.TOCSuperEntry>) tocSuperEntryList1);
      if (writeInOffsetOrder)
      {
        List<RPF6.RPF6TOC.TOCSuperEntry> source = new List<RPF6.RPF6TOC.TOCSuperEntry>();
        List<RPF6.RPF6TOC.TOCSuperEntry> tocSuperEntryList4 = new List<RPF6.RPF6TOC.TOCSuperEntry>();
        foreach (RPF6.RPF6TOC.TOCSuperEntry tocSuperEntry in tocSuperEntryList3)
        {
          if (!tocSuperEntry.IsDir)
          {
            if (tocSuperEntry.Entry.AsFile.KeepOffset.HasValue || tocSuperEntry.ReadBackFromRPF)
              source.Add(tocSuperEntry);
            else
              tocSuperEntryList4.Add(tocSuperEntry);
          }
        }
        List<RPF6.RPF6TOC.TOCSuperEntry> list = source.OrderBy<RPF6.RPF6TOC.TOCSuperEntry, long>((Func<RPF6.RPF6TOC.TOCSuperEntry, long>) (x => x.Entry.AsFile.GetOffset(true))).ToList<RPF6.RPF6TOC.TOCSuperEntry>();
        list.AddRange((IEnumerable<RPF6.RPF6TOC.TOCSuperEntry>) tocSuperEntryList4);
        Action<RPF6.RPF6TOC.TOCSuperEntry> WriteEntry = (Action<RPF6.RPF6TOC.TOCSuperEntry>) null;
        WriteEntry = (Action<RPF6.RPF6TOC.TOCSuperEntry>) (super =>
        {
          if (super.IsDir || !super.Write || super.DoesHaveParentMarkedNotToBeWritten || super.Written)
            return;
          foreach (RPF6.RPF6TOC.TOCSuperEntry writeBeforeChild in super.WriteBefore_Children)
            WriteEntry(writeBeforeChild);
          RPF6.RPF6TOC.FileEntry asFile = super.Entry.AsFile;
          byte[] b = (byte[]) null;
          if (asFile.FlagInfo.IsCompressed && !asFile.FlagInfo.IsResource && super.CustomDataStream != null)
          {
            byte[] numArray = new byte[super.CustomDataStream.Length];
            super.CustomDataStream.Read(numArray, 0, numArray.Length);
            b = DataUtils.Compress(numArray, 9);
          }
          int num = super.ReadBackFromRPF ? asFile.SizeInArchive : (b != null ? b.Length : (int) super.CustomDataStream.Length);
          asFile.SizeInArchive = num;
          if (!asFile.FlagInfo.IsResource)
          {
            long length;
            if (num >= 131072)
            {
              length = PikIO.Utils.RoundUp(io.Position, 2048L) - io.Position;
              if (length == 0L)
                length = 2048L;
            }
            else
            {
              length = PikIO.Utils.RoundUp(io.Position, 8L) - io.Position;
              if (length == 0L)
                length = 8L;
            }
            io.WriteBytes(new byte[length]);
          }
          else
          {
            long length = PikIO.Utils.RoundUp(io.Position, 2048L) - io.Position;
            if (length == 0L)
              length = 2048L;
            io.WriteBytes(new byte[length]);
          }
          if (super.CustomDataStream != null && !super.ReadBackFromRPF)
          {
            asFile.SetOffset(io.Position);
            if (b == null)
              super.CustomDataStream.CopyTo(io.BaseStream);
            else
              io.WriteBytes(b);
            super.CustomDataStream.Position = 0L;
          }
          else if (super.ReadBackFromRPF)
          {
            this.RPFIO.Position = asFile.GetOffset();
            asFile.SetOffset(io.Position);
            this.RPFIO.BufferCopy(io.BaseStream, (uint) asFile.SizeInArchive, 262144U);
          }
          foreach (RPF6.RPF6TOC.TOCSuperEntry writeAfterChild in super.WriteAfterChildren)
            WriteEntry(writeAfterChild);
          super.Written = true;
        });
        int num1 = 0;
        foreach (RPF6.RPF6TOC.TOCSuperEntry tocSuperEntry in list)
        {
          if (RPF6.OnOperation != null)
            RPF6.OnOperation((object) this, new RPF6Report()
            {
              StatusOperationText = "Writing",
              StatusText = string.Format("{0}", (object) tocSuperEntry.Entry.Name),
              TitleText = string.Format("Writing Files ({0}/{1})", (object) (num1 + 1), (object) list.Count),
              CurrentOperation = num1,
              TotalOperations = list.Count
            });
          WriteEntry(tocSuperEntry);
          ++num1;
        }
        for (int index = 0; index < tocSuperEntryList3.Count; ++index)
          tocSuperEntryList3[index].Written = false;
      }
      else
      {
        Action<RPF6.RPF6TOC.TOCSuperEntry> WriteEntry = (Action<RPF6.RPF6TOC.TOCSuperEntry>) null;
        WriteEntry = (Action<RPF6.RPF6TOC.TOCSuperEntry>) (super =>
        {
          if (super.IsDir || !super.Write || super.DoesHaveParentMarkedNotToBeWritten || super.Written)
            return;
          foreach (RPF6.RPF6TOC.TOCSuperEntry writeBeforeChild in super.WriteBefore_Children)
            WriteEntry(writeBeforeChild);
          RPF6.RPF6TOC.FileEntry asFile = super.Entry.AsFile;
          byte[] b = (byte[]) null;
          if (asFile.FlagInfo.IsCompressed && !asFile.FlagInfo.IsResource && super.CustomDataStream != null)
          {
            byte[] numArray = new byte[super.CustomDataStream.Length];
            super.CustomDataStream.Read(numArray, 0, numArray.Length);
            b = DataUtils.Compress(numArray, 9);
          }
          int num = super.ReadBackFromRPF ? asFile.SizeInArchive : (b != null ? b.Length : (int) super.CustomDataStream.Length);
          asFile.SizeInArchive = num;
          if (!asFile.AsFile.FlagInfo.IsResource)
          {
            long length;
            if (num >= 131072)
            {
              length = PikIO.Utils.RoundUp(io.Position, 2048L) - io.Position;
              if (length == 0L)
                length = 2048L;
            }
            else
            {
              length = PikIO.Utils.RoundUp(io.Position, 8L) - io.Position;
              if (length == 0L)
                length = 8L;
            }
            io.WriteBytes(new byte[length]);
          }
          else
          {
            long length = PikIO.Utils.RoundUp(io.Position, 2048L) - io.Position;
            if (length == 0L)
              length = 2048L;
            io.WriteBytes(new byte[length]);
          }
          if (super.CustomDataStream != null && !super.ReadBackFromRPF)
          {
            asFile.SetOffset(io.Position);
            if (b == null)
              super.CustomDataStream.CopyTo(io.BaseStream);
            else
              io.WriteBytes(b);
            super.CustomDataStream.Position = 0L;
          }
          else if (super.ReadBackFromRPF)
          {
            this.RPFIO.Position = asFile.GetOffset();
            asFile.SetOffset(io.Position);
            this.RPFIO.BufferCopy(io.BaseStream, (uint) asFile.SizeInArchive, 262144U);
          }
          foreach (RPF6.RPF6TOC.TOCSuperEntry writeAfterChild in super.WriteAfterChildren)
            WriteEntry(writeAfterChild);
          super.Written = true;
        });
        int num1 = 0;
        foreach (RPF6.RPF6TOC.TOCSuperEntry tocSuperEntry in tocSuperEntryList3)
        {
          if (RPF6.OnOperation != null)
            RPF6.OnOperation((object) this, new RPF6Report()
            {
              StatusOperationText = "Writing",
              StatusText = string.Format("{0}", (object) tocSuperEntry.Entry.Name),
              TitleText = string.Format("Writing Files ({0}/{1})", (object) (num1 + 1), (object) tocSuperEntryList3.Count),
              CurrentOperation = num1,
              TotalOperations = tocSuperEntryList3.Count
            });
          WriteEntry(tocSuperEntry);
        }
        for (int index = 0; index < tocSuperEntryList3.Count; ++index)
          tocSuperEntryList3[index].Written = false;
      }
      io.WriteBytes(new byte[(int) (PikIO.Utils.RoundUp(io.Position, 2048L) - io.Position)]);
      io.Position = position;
      RPF6.RPF6TOC.WriteTOC(io, this.TOC);
      io.Flush();
    }

    public class RPF6Header
    {
      public const int Ident = 1380992566;

      public int EntryCount { get; set; }

      public int TOCSize => (int) ((long) (((this.EntryCount << 2) + this.EntryCount << 2) + 15) & 4294967280L);

      public int UNK1 { get; set; }

      public int EncFlag { get; set; }

      public bool Encrypted
      {
        get => (uint) this.EncFlag > 0U;
        set
        {
          if (value)
            this.EncFlag = -3;
          else
            this.EncFlag = 0;
        }
      }

      public int FileCount { get; set; }

      public int DirectoryCount { get; set; }

      public static bool HasIdentifier(PikIO io)
      {
        long position = io.Position;
        int num = io.ReadInt32();
        io.Position = position;
        return num == 1380992566;
      }

      public static RPF6.RPF6Header ReadHeader(PikIO io)
      {
        RPF6.RPF6Header rpF6Header = new RPF6.RPF6Header();
        io.ReadInt32();
        rpF6Header.EntryCount = io.ReadInt32();
        rpF6Header.UNK1 = io.ReadInt32();
        rpF6Header.EncFlag = io.ReadInt32();
        return rpF6Header;
      }

      public static void WriteHeader(PikIO io, RPF6.RPF6Header header)
      {
        io.Write(1380992566);
        io.Write(header.EntryCount);
        io.Write(header.UNK1);
        io.Write(header.EncFlag);
      }
    }

    public class RPF6TOC
    {
      public List<RPF6.RPF6TOC.TOCEntry> Entries { get; set; }

      public List<RPF6.RPF6TOC.TOCSuperEntry> SuperEntries { get; set; }

      private RPF6 RPFFile { get; set; }

      private static int GetOffset(int entryCount, int startIndex)
      {
        int num1 = entryCount + startIndex >> 1;
        int num2 = num1 << 2;
        return (num1 + num2) * 4;
      }

      public RPF6TOC(RPF6 rpfFile)
      {
        this.RPFFile = rpfFile;
        this.Entries = new List<RPF6.RPF6TOC.TOCEntry>();
        this.SuperEntries = new List<RPF6.RPF6TOC.TOCSuperEntry>();
      }

      public static RPF6.RPF6TOC ReadTOC(PikIO io, RPF6 rpfFile)
      {
        RPF6.RPF6TOC rpF6Toc = new RPF6.RPF6TOC(rpfFile);
        MemoryStream memoryStream = new MemoryStream();
        byte[] numArray;
        if (rpfFile.Header.Encrypted)
        {
          long tocSize = (long) rpfFile.Header.TOCSize;
          numArray = DataUtils.Decrypt(io.ReadBytes((int) tocSize), RPF6.CurrentEncryptionKey);
          if (AppGlobals.Settings.WriteDecryptedTOC)
            File.WriteAllBytes("toc_decrypted", numArray);
        }
        else
        {
          numArray = io.ReadBytes(rpfFile.Header.TOCSize);
          if (AppGlobals.Settings.WriteDecryptedTOC)
            File.WriteAllBytes("toc_decrypted", numArray);
        }
        PikIO io1 = new PikIO((Stream) new MemoryStream(numArray), PikIO.Endianess.Big);
        int num1 = 0;
        int num2 = 0;
        long num3 = 0;
        SortedList<long, RPF6.RPF6TOC.TOCSuperEntry> source1 = new SortedList<long, RPF6.RPF6TOC.TOCSuperEntry>();
        StreamWriter streamWriter1 = (StreamWriter) null;
        StreamWriter streamWriter2 = (StreamWriter) null;
        if (AppGlobals.Settings.WriteTOCOrder)
          streamWriter1 = new StreamWriter(AppUtils.CreateFile("toc_order.txt"));
        if (AppGlobals.Settings.WriteRSCInfo)
          streamWriter2 = new StreamWriter(AppUtils.CreateFile("rsc_info.txt"));
        for (int index = 0; index < rpfFile.Header.EntryCount; ++index)
        {
          RPF6.RPF6TOC.TOCEntry tocEntry = RPF6.RPF6TOC.TOCEntry.ReadEntry(io1);
          if (AppGlobals.Settings.WriteTOCOrder)
          {
            int num4 = 0;
            if (tocEntry.IsFile && tocEntry.AsFile.FlagInfo.IsResource)
              num4 = (int) tocEntry.AsFile.ResourceType;
            streamWriter1.WriteLine(string.Format("[{0}]\t[{1}] {2} {3} [{4}]", (object) index, tocEntry.IsFile ? (object) "F" : (object) "D", (object) tocEntry.Name, tocEntry.IsDirectory ? (object) string.Format("[-> {0}, {1}]", (object) tocEntry.AsDirectory.ContentEntryIndex, (object) (RPF6.RPF6TOC.GetOffset(tocEntry.AsDirectory.ContentEntryCount, tocEntry.AsDirectory.ContentEntryIndex) / 20)) : (object) "", (object) num4));
          }
          if (AppGlobals.Settings.WriteRSCInfo && tocEntry.IsFile && tocEntry.AsFile.FlagInfo.IsResource)
          {
            ResourceUtils.FlagInfo flagInfo = new ResourceUtils.FlagInfo(tocEntry.AsFile.FlagInfo.Flag1, tocEntry.AsFile.FlagInfo.Flag2);
            streamWriter2.WriteLine(string.Format("---- {0} [RSC {1}]", (object) tocEntry.Name, (object) tocEntry.AsFile.ResourceType));
            streamWriter2.WriteLine(flagInfo.ToString());
            streamWriter2.WriteLine("##################################################################");
          }
          RPF6.RPF6TOC.TOCSuperEntry tocSuperEntry = new RPF6.RPF6TOC.TOCSuperEntry();
          tocEntry.SuperOwner = tocSuperEntry;
          tocSuperEntry.ReadBackFromRPF = true;
          tocSuperEntry.IsFileFromRPF = true;
          tocSuperEntry.Entry = tocEntry;
          rpF6Toc.Entries.Add(tocEntry);
          rpF6Toc.SuperEntries.Add(tocSuperEntry);
          if (tocEntry.IsFile && AppGlobals.Settings.MakeFileInfoData)
            source1.Add(tocEntry.AsFile.GetOffset(), tocSuperEntry);
          if (tocEntry.IsFile)
          {
            ++num1;
            num3 += (long) tocEntry.AsFile.SizeInArchive;
          }
          else
            ++num2;
        }
        if (AppGlobals.Settings.WriteRSCInfo)
        {
          streamWriter2.Flush();
          streamWriter2.Close();
        }
        if (AppGlobals.Settings.WriteTOCOrder)
        {
          streamWriter1.Flush();
          streamWriter1.Close();
        }
        KeyValuePair<long, RPF6.RPF6TOC.TOCSuperEntry> keyValuePair1;
        if (AppGlobals.Settings.MakeFileInfoData)
        {
          StreamWriter streamWriter3 = new StreamWriter(AppUtils.CreateFile("file_data.txt"));
          for (int index = 0; index < source1.Count; ++index)
          {
            keyValuePair1 = source1.ElementAt<KeyValuePair<long, RPF6.RPF6TOC.TOCSuperEntry>>(index);
            long key = keyValuePair1.Key;
            keyValuePair1 = source1.ElementAt<KeyValuePair<long, RPF6.RPF6TOC.TOCSuperEntry>>(index);
            RPF6.RPF6TOC.FileEntry asFile = keyValuePair1.Value.Entry.AsFile;
            string str1 = asFile.FlagInfo.IsResource ? "R" : "F";
            string str2 = RPF6.Gen_PossibleSectorCalc((long) asFile.SizeInArchive, asFile.Offset);
            bool flag1 = asFile.GetOffset() % 8L == 0L;
            bool flag2 = asFile.GetOffset() % 2048L == 0L;
            streamWriter3.WriteLine(string.Format("{0}     {1}\t[{2}, {3}]\t[{4} | {5}] [SIZE: {6}] [C:{7}, {8}] [SEC: {9}]", (object) str1, (object) asFile.GetOffset(), (object) flag1.ToString(), (object) flag2.ToString(), (object) asFile.Name, (object) asFile.NameOffset.ToString("X8"), (object) asFile.SizeInArchive, asFile.FlagInfo.IsCompressed ? (object) "Y" : (object) "N", (object) asFile.FlagInfo.GetTotalSize(), (object) str2));
          }
          streamWriter3.Flush();
          streamWriter3.Close();
        }
        if (AppGlobals.Settings.MakeDiffDataFile)
        {
          StreamWriter streamWriter3 = new StreamWriter(AppUtils.CreateFile("diff_data.txt"));
          SortedList<long, RPF6.RPF6TOC.FileEntry> source2 = new SortedList<long, RPF6.RPF6TOC.FileEntry>();
          for (int index = 0; index < rpF6Toc.Entries.Count; ++index)
          {
            if (rpF6Toc.Entries[index].IsFile)
            {
              RPF6.RPF6TOC.FileEntry asFile = rpF6Toc.Entries[index].AsFile;
              source2.Add(asFile.GetOffset(), asFile);
            }
          }
          long num4 = 671744;
          RPF6.RPF6TOC.FileEntry fileEntry = (RPF6.RPF6TOC.FileEntry) null;
          for (int index = 0; index < source2.Count; ++index)
          {
            KeyValuePair<long, RPF6.RPF6TOC.FileEntry> keyValuePair2 = source2.ElementAt<KeyValuePair<long, RPF6.RPF6TOC.FileEntry>>(index);
            long num5 = keyValuePair2.Key - num4;
            StreamWriter streamWriter4 = streamWriter3;
            keyValuePair2 = source2.ElementAt<KeyValuePair<long, RPF6.RPF6TOC.FileEntry>>(index);
            string str = string.Format("{0} was {1} bytes away from {2}", (object) keyValuePair2.Value.Name, (object) num5, (object) (fileEntry == null ? "FILESTART" : fileEntry.Name));
            streamWriter4.WriteLine(str);
            keyValuePair2 = source2.ElementAt<KeyValuePair<long, RPF6.RPF6TOC.FileEntry>>(index);
            long offset = keyValuePair2.Value.GetOffset();
            keyValuePair2 = source2.ElementAt<KeyValuePair<long, RPF6.RPF6TOC.FileEntry>>(index);
            long sizeInArchive = (long) keyValuePair2.Value.SizeInArchive;
            num4 = offset + sizeInArchive;
            keyValuePair2 = source2.ElementAt<KeyValuePair<long, RPF6.RPF6TOC.FileEntry>>(index);
            fileEntry = keyValuePair2.Value;
          }
          streamWriter3.Flush();
          streamWriter3.Close();
        }
        rpfFile.Header.FileCount = num1;
        rpfFile.Header.DirectoryCount = num2;
        for (int index = 0; index < rpF6Toc.Entries.Count; ++index)
        {
          RPF6.RPF6TOC.TOCEntry entry = rpF6Toc.Entries[index];
          if (entry.IsDirectory)
          {
            RPF6.RPF6TOC.DirectoryEntry asDirectory = entry.AsDirectory;
            for (int contentEntryIndex = asDirectory.ContentEntryIndex; contentEntryIndex < asDirectory.ContentEntryIndex + asDirectory.ContentEntryCount; ++contentEntryIndex)
            {
              rpF6Toc.Entries[contentEntryIndex].Parent = entry.AsDirectory;
              rpF6Toc.SuperEntries[contentEntryIndex].SuperParent = rpF6Toc.SuperEntries[index];
              rpF6Toc.SuperEntries[index].Children.Add(rpF6Toc.SuperEntries[contentEntryIndex]);
            }
          }
        }
        if (AppGlobals.Settings.MakeFileDirectoryListing)
        {
          StreamWriter streamWriter3 = new StreamWriter(AppUtils.CreateFile("directory_listing.txt"));
          for (int index = 0; index < source1.Count; ++index)
          {
            keyValuePair1 = source1.ElementAt<KeyValuePair<long, RPF6.RPF6TOC.TOCSuperEntry>>(index);
            long key = keyValuePair1.Key;
            keyValuePair1 = source1.ElementAt<KeyValuePair<long, RPF6.RPF6TOC.TOCSuperEntry>>(index);
            RPF6.RPF6TOC.TOCSuperEntry tocSuperEntry = keyValuePair1.Value;
            streamWriter3.WriteLine(string.Format("{0}", (object) tocSuperEntry.Entry.GetPath()));
          }
          streamWriter3.Flush();
          streamWriter3.Close();
        }
        return rpF6Toc;
      }

      public static void WriteTOC(PikIO io, RPF6.RPF6TOC toc)
      {
        MemoryStream memoryStream = new MemoryStream();
        PikIO io1 = new PikIO((Stream) memoryStream, PikIO.Endianess.Big);
        for (int index = 0; index < toc.Entries.Count; ++index)
          RPF6.RPF6TOC.TOCEntry.WriteEntry(io1, toc.Entries[index]);
        byte[] b = new byte[PikIO.Utils.RoundUp(memoryStream.Position, 16L) - memoryStream.Position];
        io1.WriteBytes(b);
        byte[] numArray = memoryStream.ToArray();
        if (toc.RPFFile.Header.Encrypted)
          numArray = DataUtils.Encrypt(numArray, RPF6.CurrentEncryptionKey);
        io.WriteBytes(numArray);
      }

      public void Rebuild()
      {
        List<RPF6.RPF6TOC.TOCSuperEntry> newSupers = new List<RPF6.RPF6TOC.TOCSuperEntry>();
        Action<RPF6.RPF6TOC.TOCSuperEntry> sortSupers = (Action<RPF6.RPF6TOC.TOCSuperEntry>) null;
        sortSupers = (Action<RPF6.RPF6TOC.TOCSuperEntry>) (entry =>
        {
          if (!entry.Write || entry.DoesHaveParentMarkedNotToBeWritten)
            return;
          if (!newSupers.Contains(entry))
            newSupers.Add(entry);
          if (entry.IsDir && entry.Children != null && entry.Children.Count > 0)
          {
            entry.StartIndex = newSupers.Count;
            newSupers.AddRange((IEnumerable<RPF6.RPF6TOC.TOCSuperEntry>) entry.Children.OrderBy<RPF6.RPF6TOC.TOCSuperEntry, uint>((Func<RPF6.RPF6TOC.TOCSuperEntry, uint>) (o => o.Entry.NameOffset)));
            foreach (RPF6.RPF6TOC.TOCSuperEntry child in entry.Children)
              sortSupers(child);
          }
        });
        sortSupers(this.SuperEntries[0]);
        this.SuperEntries = newSupers;
        List<RPF6.RPF6TOC.TOCEntry> tocEntryList = new List<RPF6.RPF6TOC.TOCEntry>();
        foreach (RPF6.RPF6TOC.TOCSuperEntry superEntry in this.SuperEntries)
        {
          if (superEntry.Write && !superEntry.DoesHaveParentMarkedNotToBeWritten)
          {
            if (superEntry.Entry.IsDirectory)
            {
              RPF6.RPF6TOC.DirectoryEntry asDirectory = superEntry.Entry.AsDirectory;
              asDirectory.ContentEntryIndex = superEntry.StartIndex;
              asDirectory.ContentEntryCount = superEntry.Children.Count;
            }
            tocEntryList.Add(superEntry.Entry);
          }
        }
        this.Entries = tocEntryList;
        this.RPFFile.Header.FileCount = this.Entries.Count<RPF6.RPF6TOC.TOCEntry>((Func<RPF6.RPF6TOC.TOCEntry, bool>) (x => x.IsFile));
        this.RPFFile.Header.DirectoryCount = this.Entries.Count<RPF6.RPF6TOC.TOCEntry>((Func<RPF6.RPF6TOC.TOCEntry, bool>) (x => x.IsDirectory));
        this.RPFFile.Header.EntryCount = this.Entries.Count;
      }

      public void ExtractFile(RPF6.RPF6TOC.TOCSuperEntry entry, Stream xOut)
      {
        long position = xOut.Position;
        if (entry.CustomDataStream != null && !entry.ReadBackFromRPF)
        {
          entry.CustomDataStream.Position = 0L;
          entry.CustomDataStream.CopyTo(xOut);
        }
        else
        {
          RPF6.RPF6TOC.FileEntry asFile = entry.Entry.AsFile;
          if (asFile.FlagInfo.IsCompressed && !asFile.FlagInfo.IsResource)
          {
            this.RPFFile.RPFIO.Position = asFile.GetOffset();
            byte[] buffer = DataUtils.DecompressDeflate(this.RPFFile.RPFIO.ReadBytes(asFile.SizeInArchive), asFile.FlagInfo.GetTotalSize());
            xOut.Write(buffer, 0, buffer.Length);
          }
          else
          {
            ulong offset = (ulong) asFile.GetOffset();
            this.RPFFile.RPFIO.Position = asFile.GetOffset();
            this.RPFFile.RPFIO.BufferCopy(xOut, (uint) entry.Entry.AsFile.SizeInArchive, 32768U);
          }
        }
        xOut.Position = position;
      }

      public void ReplaceEntry(
        RPF6.RPF6TOC.TOCSuperEntry entryToReplace,
        RPF6.RPF6TOC.TOCSuperEntry replaceWith)
      {
        RPF6.RPF6TOC.TOCSuperEntry superParent = entryToReplace.SuperParent;
        int index = superParent.Children.IndexOf(entryToReplace);
        superParent.Children.Remove(entryToReplace);
        superParent.Children.Insert(index, replaceWith);
      }

      public RPF6.RPF6TOC.TOCSuperEntry GetEntryByPath(string fullPath, char seperator = '/')
      {
        RPF6.RPF6TOC.TOCSuperEntry superEntry = this.SuperEntries[0];
        if (fullPath.EndsWith(string.Format("{0}", (object) seperator)))
          fullPath = fullPath.Remove(fullPath.Length - 1, 1);
        string[] strArray = fullPath.Split(seperator);
        if (strArray[0] != "root")
          return (RPF6.RPF6TOC.TOCSuperEntry) null;
        RPF6.RPF6TOC.TOCSuperEntry tocSuperEntry = superEntry;
        for (int index = 1; index < strArray.Length; ++index)
        {
          uint hash = !strArray[index].StartsWith("0x") ? DataUtils.GetHash(strArray[index]) : uint.Parse(strArray[index].Substring(2), NumberStyles.HexNumber);
          RPF6.RPF6TOC.TOCSuperEntry child = tocSuperEntry.GetChild(hash);
          if (child == null)
            return (RPF6.RPF6TOC.TOCSuperEntry) null;
          tocSuperEntry = child;
        }
        return tocSuperEntry;
      }

      public class TOCSuperEntry
      {
        private bool _Write;

        public TOCSuperEntry()
        {
          this.Children = new List<RPF6.RPF6TOC.TOCSuperEntry>();
          this.RemovedChildren = new List<RPF6.RPF6TOC.TOCSuperEntry>();
          this.WriteBefore_Children = new List<RPF6.RPF6TOC.TOCSuperEntry>();
          this.WriteAfterChildren = new List<RPF6.RPF6TOC.TOCSuperEntry>();
          this._Write = true;
        }

        public bool ReadBackFromRPF { get; set; }

        public bool IsFileFromRPF { get; set; }

        public bool Written { get; set; }

        public bool Write => this._Write;

        public bool DoesHaveParentMarkedNotToBeWritten
        {
          get
          {
            RPF6.RPF6TOC.TOCSuperEntry superParent = this.SuperParent;
            if (superParent == null)
              return false;
            for (; superParent != null; superParent = superParent.SuperParent)
            {
              if (!superParent.Write)
                return true;
            }
            return false;
          }
        }

        public void MarkAsNotToBeWritten(bool write, List<RPF6.RPF6TOC.TOCSuperEntry> allSupers)
        {
          if (!write & this._Write)
          {
            this._Write = write;
            if (this.SuperParent == null)
              return;
            this.SuperParent.Children.Remove(this);
            this.SuperParent.RemovedChildren.Add(this);
            allSupers.Remove(this);
          }
          else
          {
            this._Write = write;
            if (this.SuperParent != null)
            {
              this.SuperParent.Children.Add(this);
              this.SuperParent.RemovedChildren.Remove(this);
              allSupers.Add(this);
            }
          }
        }

        public void AddChild(RPF6.RPF6TOC.TOCSuperEntry child)
        {
          child.SuperParent = this;
          this.Children.Add(child);
        }

        public bool DoesHaveEntry(string name, bool checkALLCHILDREN = false) => this.DoesHaveEntry(DataUtils.GetHash(name), checkALLCHILDREN);

        public bool DoesHaveEntry(uint hash, bool checkALLCHILDREN = false)
        {
          foreach (RPF6.RPF6TOC.TOCSuperEntry tocSuperEntry in checkALLCHILDREN ? this.AllChildren : this.Children)
          {
            if ((int) tocSuperEntry.Entry.NameOffset == (int) hash)
              return true;
          }
          return false;
        }

        public RPF6.RPF6TOC.TOCSuperEntry GetChild(string name) => this.GetChild(DataUtils.GetHash(name));

        public RPF6.RPF6TOC.TOCSuperEntry GetChild(uint hash)
        {
          foreach (RPF6.RPF6TOC.TOCSuperEntry child in this.Children)
          {
            if ((int) child.Entry.NameOffset == (int) hash)
              return child;
          }
          return (RPF6.RPF6TOC.TOCSuperEntry) null;
        }

        public RPF6.RPF6TOC.TOCEntry Entry { get; set; }

        public RPF6.RPF6TOC.TOCEntry OldEntry { get; set; }

        public Stream CustomDataStream { get; set; }

        public void SetCustomStream(Stream custom, int virt, int phys)
        {
          this.CustomDataStream = custom;
          this.Entry.AsFile.FlagInfo.SetTotalSize(virt, phys);
        }

        public bool IsDir => this.Entry.IsDirectory;

        public int StartIndex { get; set; }

        public RPF6.RPF6TOC.TOCSuperEntry SuperParent { get; set; }

        public RPF6.RPF6TOC.TOCSuperEntry WriteOrderParent { get; set; }

        public List<RPF6.RPF6TOC.TOCSuperEntry> Children { get; set; }

        public List<RPF6.RPF6TOC.TOCSuperEntry> RemovedChildren { get; set; }

        public List<RPF6.RPF6TOC.TOCSuperEntry> WriteBefore_Children { get; set; }

        public List<RPF6.RPF6TOC.TOCSuperEntry> WriteAfterChildren { get; set; }

        public List<RPF6.RPF6TOC.TOCSuperEntry> AllChildren
        {
          get
          {
            List<RPF6.RPF6TOC.TOCSuperEntry> tocSuperEntryList = new List<RPF6.RPF6TOC.TOCSuperEntry>();
            tocSuperEntryList.AddRange((IEnumerable<RPF6.RPF6TOC.TOCSuperEntry>) this.Children);
            tocSuperEntryList.AddRange((IEnumerable<RPF6.RPF6TOC.TOCSuperEntry>) this.RemovedChildren);
            return tocSuperEntryList;
          }
        }

        public RPF6.RPF6TOC.TOCSuperEntry[] GetPathArray()
        {
          List<RPF6.RPF6TOC.TOCSuperEntry> source = new List<RPF6.RPF6TOC.TOCSuperEntry>();
          source.Add(this);
          for (RPF6.RPF6TOC.TOCSuperEntry superParent = this.SuperParent; superParent != null; superParent = superParent.SuperParent)
            source.Add(superParent);
          return source.Reverse<RPF6.RPF6TOC.TOCSuperEntry>().ToArray<RPF6.RPF6TOC.TOCSuperEntry>();
        }

        public string GetPath(char seperator = '/')
        {
          string str = string.Empty;
          RPF6.RPF6TOC.TOCSuperEntry[] pathArray = this.GetPathArray();
          for (int index = 0; index < pathArray.Length; ++index)
            str = index != pathArray.Length - 1 ? str + string.Format("{0}{1}", (object) pathArray[index].Entry.Name, (object) seperator) : str + string.Format("{0}", (object) pathArray[index].Entry.Name);
          return str;
        }
      }

      public abstract class TOCEntry
      {
        public RPF6.RPF6TOC.DirectoryEntry Parent { get; set; }

        public RPF6.RPF6TOC.TOCSuperEntry SuperOwner { get; set; }

        public RPF6.RPF6TOC.DirectoryEntry AsDirectory => this as RPF6.RPF6TOC.DirectoryEntry;

        public RPF6.RPF6TOC.FileEntry AsFile => this as RPF6.RPF6TOC.FileEntry;

        public bool IsFile => this is RPF6.RPF6TOC.FileEntry;

        public bool IsDirectory => this is RPF6.RPF6TOC.DirectoryEntry;

        public uint NameOffset { get; set; }

        public static bool ReadAsDir(PikIO io)
        {
          io.Seek(8L, SeekOrigin.Current);
          byte num = io.ReadByte();
          io.Seek(-9L, SeekOrigin.Current);
          return num == (byte) 128;
        }

        public static RPF6.RPF6TOC.TOCEntry ReadEntry(PikIO io)
        {
          if (RPF6.RPF6TOC.TOCEntry.ReadAsDir(io))
          {
            RPF6.RPF6TOC.DirectoryEntry directoryEntry = new RPF6.RPF6TOC.DirectoryEntry();
            directoryEntry.NameOffset = io.ReadUInt32();
            directoryEntry.Flags = io.ReadInt32();
            if ((uint) directoryEntry.Flags > 0U)
              throw new Exception("What?");
            directoryEntry.ContentEntryIndex = io.ReadInt32() & int.MaxValue;
            directoryEntry.ContentEntryCount = io.ReadInt32() & 268435455;
            directoryEntry.UNK = io.ReadInt32();
            return (uint) directoryEntry.UNK <= 0U ? (RPF6.RPF6TOC.TOCEntry) directoryEntry : throw new Exception("What?");
          }
          RPF6.RPF6TOC.FileEntry fileEntry = new RPF6.RPF6TOC.FileEntry();
          fileEntry.NameOffset = io.ReadUInt32();
          fileEntry.SizeInArchive = io.ReadInt32();
          fileEntry.Offset = (long) io.ReadInt32();
          fileEntry.FlagInfo = new ResourceUtils.FlagInfo()
          {
            Flag1 = io.ReadInt32(),
            Flag2 = io.ReadInt32()
          };
          return (RPF6.RPF6TOC.TOCEntry) fileEntry;
        }

        public static void WriteEntry(PikIO io, RPF6.RPF6TOC.TOCEntry entry)
        {
          io.Write(entry.NameOffset);
          if (entry.IsDirectory)
          {
            RPF6.RPF6TOC.DirectoryEntry asDirectory = entry.AsDirectory;
            io.Write(asDirectory.Flags);
            io.Write((int) (2147483648L | (long) (asDirectory.ContentEntryIndex & int.MaxValue)));
            io.Write(asDirectory.ContentEntryCount & 268435455);
            io.Write(asDirectory.UNK);
          }
          else
          {
            RPF6.RPF6TOC.FileEntry asFile = entry.AsFile;
            io.Write(asFile.SizeInArchive);
            io.Write((uint) asFile.Offset);
            io.Write(asFile.FlagInfo.Flag1);
            io.Write(asFile.FlagInfo.Flag2);
          }
        }

        public string Name
        {
          get
          {
            if (this.IsDirectory && this.NameOffset == 0U)
              return "root";
            return RPF6FileNameHandler.FileNames.ContainsKey(this.NameOffset) ? RPF6FileNameHandler.FileNames[this.NameOffset] : string.Format("0x{0}", (object) this.NameOffset.ToString("X8"));
          }
          set => this.NameOffset = value.ToLower() == "root" ? 0U : DataUtils.GetHash(value);
        }

        public string GetPath(string seperator = "/")
        {
          string str = this.Name;
          for (RPF6.RPF6TOC.DirectoryEntry parent = this.Parent; parent != null; parent = parent.Parent)
            str = str.Insert(0, string.Format("{0}{1}", (object) parent.Name, (object) seperator));
          return str;
        }

        public string GetPathTill(RPF6.RPF6TOC.DirectoryEntry tillDirectory, string seperator = "/")
        {
          string str = this.Name;
          for (RPF6.RPF6TOC.DirectoryEntry parent = this.Parent; parent != null && parent != tillDirectory; parent = parent.Parent)
            str = str.Insert(0, string.Format("{0}{1}", (object) parent.Name, (object) seperator));
          return str;
        }

        public int GetLevel()
        {
          int num = 0;
          for (RPF6.RPF6TOC.DirectoryEntry parent = this.Parent; parent != null; parent = parent.Parent)
            ++num;
          return num;
        }
      }

      public class DirectoryEntry : RPF6.RPF6TOC.TOCEntry
      {
        public int ContentEntryIndex { get; set; }

        public int ContentEntryCount { get; set; }

        public int Flags { get; set; }

        public int UNK { get; set; }
      }

      public class FileEntry : RPF6.RPF6TOC.TOCEntry
      {
        public ResourceUtils.FlagInfo FlagInfo;

        public int SizeInArchive { get; set; }

        public long Offset { get; set; }

        public long? KeepOffset { get; set; }

        public byte ResourceType
        {
          get => (byte) ((ulong) this.Offset & (ulong) byte.MaxValue);
          set => this.Offset = this.Offset & -256L | (long) value;
        }

        public void SetOffset(long offset)
        {
          if ((ulong) offset % 8UL > 0UL)
          {
            this.Offset = -1L;
            throw new Exception("INVALID_SET_OFFSET");
          }
          if (this.FlagInfo.IsResource)
            this.Offset = offset / 8L | (long) this.ResourceType;
          else
            this.Offset = offset / 8L;
        }

        public long GetOffset(bool getKeepOffset = false)
        {
          if (getKeepOffset && this.KeepOffset.HasValue)
            return this.KeepOffset.Value;
          return this.FlagInfo.IsResource ? (this.Offset & 2147483392L) * 8L : (this.Offset & (long) int.MaxValue) * 8L;
        }
      }
    }
  }
}
