using Pik;
using Pik.IO;
using RAGE;
using RAGE.ExtraClasses;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace AreDeAre_xPlorer_2
{
  public class RPFCommandFile
  {
    public static EventHandler<RPF6Report> OnOperation;
    public static EventHandler<RPF6ErrorReport> OnError;
    public const int Magic = 1481920579;

    public int Version { get; set; }

    public int CommandCount { get; set; }

    public List<RPFCommandFile.Command> Commands { get; set; }

    public static bool IsValidCommandFile(Stream xIn)
    {
      PikIO pikIo = new PikIO(xIn, PikIO.Endianess.Little);
      int num = pikIo.ReadInt32();
      pikIo.Position -= 4L;
      return num == 1481920579;
    }

    public RPFCommandFile(Stream io)
    {
      this.Commands = new List<RPFCommandFile.Command>();
      io.Position += 8L;
      this.ReadCommands(new PikIO(io, PikIO.Endianess.Little));
    }

    public RPFCommandFile() => this.Commands = new List<RPFCommandFile.Command>();

    public bool CanExecuteCommands() => this.Commands.Count<RPFCommandFile.Command>((Func<RPFCommandFile.Command, bool>) (x => x.ID == RPFCommandFile.CommandID.OpenRPF)) == 1;

    public void ExecuteCommands()
    {
      RPF6 rpF6 = (RPF6) null;
      foreach (RPFCommandFile.Command command in this.Commands)
      {
        if (command.ID == RPFCommandFile.CommandID.OpenRPF)
        {
          if (RPFCommandFile.OnOperation != null)
            RPFCommandFile.OnOperation((object) this, new RPF6Report()
            {
              CurrentOperation = 0,
              TotalOperations = 1,
              TitleText = "Opening",
              StatusOperationText = "Opening",
              StatusText = "RPF"
            });
          rpF6 = new RPF6((Stream) File.Open((command as RPFCommandFile.OpenRPFCommand).RPFFileName, FileMode.Open));
          if (RPFCommandFile.OnOperation != null)
            RPFCommandFile.OnOperation((object) this, new RPF6Report()
            {
              CurrentOperation = 1,
              TotalOperations = 1,
              TitleText = "Finished",
              StatusOperationText = "Opening",
              StatusText = "RPF"
            });
        }
        else if (command.ID == RPFCommandFile.CommandID.ExtractFile)
        {
          RPFCommandFile.ExtractFileCommand extractFileCommand = command as RPFCommandFile.ExtractFileCommand;
          RPF6.RPF6TOC.TOCSuperEntry entryByPath = rpF6.TOC.GetEntryByPath(extractFileCommand.RPFFileName);
          if (entryByPath != null)
          {
            if (RPFCommandFile.OnOperation != null)
              RPFCommandFile.OnOperation((object) this, new RPF6Report()
              {
                CurrentOperation = 0,
                TotalOperations = 1,
                TitleText = "Extracting",
                StatusOperationText = "Extracting",
                StatusText = entryByPath.Entry.Name
              });
            Stream xOut = (Stream) File.Create(string.Format("{0}\\{1}", (object) extractFileCommand.OutFileName, (object) entryByPath.Entry.Name));
            rpF6.TOC.ExtractFile(entryByPath, xOut);
            xOut.Flush();
            xOut.Close();
            if (RPFCommandFile.OnOperation != null)
              RPFCommandFile.OnOperation((object) this, new RPF6Report()
              {
                CurrentOperation = 1,
                TotalOperations = 1,
                TitleText = "Finished",
                StatusOperationText = "Extracting",
                StatusText = entryByPath.Entry.Name
              });
          }
          else if (RPFCommandFile.OnError != null)
            RPFCommandFile.OnError((object) this, new RPF6ErrorReport()
            {
              Message = string.Format("Could not find \"{0}\"", (object) extractFileCommand.RPFFileName)
            });
        }
        else if (command.ID == RPFCommandFile.CommandID.CloseRPF)
        {
          if (RPFCommandFile.OnOperation != null)
            RPFCommandFile.OnOperation((object) this, new RPF6Report()
            {
              CurrentOperation = 0,
              TotalOperations = 1,
              TitleText = "Closing",
              StatusOperationText = "Closing",
              StatusText = "RPF"
            });
          rpF6.CloseAllStreams();
          rpF6.RPFIO.Close();
          rpF6 = (RPF6) null;
          if (RPFCommandFile.OnOperation != null)
            RPFCommandFile.OnOperation((object) this, new RPF6Report()
            {
              CurrentOperation = 1,
              TotalOperations = 1,
              TitleText = "Finished",
              StatusOperationText = "Closing",
              StatusText = "RPF"
            });
        }
        else if (command.ID == RPFCommandFile.CommandID.ImportReplace)
        {
          RPFCommandFile.ImportReplaceCommand importReplaceCommand = command as RPFCommandFile.ImportReplaceCommand;
          RPF6.RPF6TOC.TOCSuperEntry entryByPath1 = rpF6.TOC.GetEntryByPath(importReplaceCommand.RPFFileName.Replace('\\', '/'));
          string fileName = Path.GetFileName(importReplaceCommand.InFileName);
          RPF6FileNameHandler.AddName(fileName);
          RPF6FileNameHandler.SaveNames();
          if (entryByPath1 == null)
          {
            string fullPath = Path.GetDirectoryName(importReplaceCommand.RPFFileName).Replace('\\', '/');
            RPF6.RPF6TOC.TOCSuperEntry entryByPath2 = rpF6.TOC.GetEntryByPath(fullPath);
            if (RPFCommandFile.OnOperation != null)
              RPFCommandFile.OnOperation((object) this, new RPF6Report()
              {
                CurrentOperation = 0,
                TotalOperations = 1,
                TitleText = "Importing",
                StatusOperationText = "Importing",
                StatusText = fileName
              });
            RPF6.RPF6TOC.TOCSuperEntry tocSuperEntry = new RPF6.RPF6TOC.TOCSuperEntry();
            RPF6.RPF6TOC.FileEntry fileEntry = new RPF6.RPF6TOC.FileEntry();
            Stream fileStream = (Stream) File.Open(importReplaceCommand.InFileName, FileMode.Open);
            (bool, string, int, int, int) resourceInformation = ResourceUtils.ResourceInfo.GetResourceInformation(fileStream);
            if (resourceInformation.Item1)
            {
              fileEntry.ResourceType = (byte) resourceInformation.Item3;
              fileEntry.FlagInfo.Flag1 = resourceInformation.Item4;
              fileEntry.FlagInfo.Flag2 = resourceInformation.Item5;
            }
            fileEntry.NameOffset = DataUtils.GetHash(fileName);
            fileEntry.SizeInArchive = (int) fileStream.Length;
            if (importReplaceCommand.Compress)
              fileEntry.FlagInfo.IsCompressed = importReplaceCommand.Compress;
            tocSuperEntry.CustomDataStream = fileStream;
            tocSuperEntry.Entry = (RPF6.RPF6TOC.TOCEntry) fileEntry;
            entryByPath2.Children.Add(tocSuperEntry);
            if (RPFCommandFile.OnOperation != null)
              RPFCommandFile.OnOperation((object) this, new RPF6Report()
              {
                CurrentOperation = 1,
                TotalOperations = 1,
                TitleText = "Importing",
                StatusOperationText = "Importing",
                StatusText = fileName
              });
          }
          else
          {
            RPF6.RPF6TOC.FileEntry fileEntry = new RPF6.RPF6TOC.FileEntry();
            Stream fileStream = (Stream) File.Open(importReplaceCommand.InFileName, FileMode.Open);
            (bool, string, int, int, int) resourceInformation = ResourceUtils.ResourceInfo.GetResourceInformation(fileStream);
            if (resourceInformation.Item1)
            {
              fileEntry.FlagInfo.IsResource = true;
              fileEntry.ResourceType = (byte) resourceInformation.Item3;
              fileEntry.FlagInfo.Flag1 = resourceInformation.Item4;
              fileEntry.FlagInfo.Flag2 = resourceInformation.Item5;
            }
            fileEntry.NameOffset = importReplaceCommand.KeepName ? entryByPath1.Entry.NameOffset : DataUtils.GetHash(fileName);
            fileEntry.SizeInArchive = (int) fileStream.Length;
            fileEntry.KeepOffset = !importReplaceCommand.KeepOffset ? new long?() : new long?(entryByPath1.Entry.AsFile.GetOffset());
            entryByPath1.ReadBackFromRPF = false;
            entryByPath1.OldEntry = entryByPath1.Entry;
            entryByPath1.Entry = (RPF6.RPF6TOC.TOCEntry) fileEntry;
            fileStream.Position = 0L;
            entryByPath1.CustomDataStream = fileStream;
            if (RPFCommandFile.OnOperation != null)
              RPFCommandFile.OnOperation((object) this, new RPF6Report()
              {
                CurrentOperation = 1,
                TotalOperations = 1,
                TitleText = "Replacing",
                StatusOperationText = "Replacing",
                StatusText = entryByPath1.OldEntry.Name
              });
          }
        }
        else if (command.ID == RPFCommandFile.CommandID.SaveRPF)
        {
          if (RPFCommandFile.OnOperation != null)
            RPFCommandFile.OnOperation((object) this, new RPF6Report()
            {
              CurrentOperation = 1,
              TotalOperations = 1,
              TitleText = "Saving",
              StatusOperationText = "Saving",
              StatusText = "RPF"
            });
          RPFCommandFile.SaveRPFCommand saveRpfCommand = command as RPFCommandFile.SaveRPFCommand;
          Stream xOut = (Stream) File.Create(saveRpfCommand.OutRPFFile);
          rpF6.Write(xOut, saveRpfCommand.SaveInOffsetOrder);
        }
        else if (command.ID == RPFCommandFile.CommandID.CreateDir)
        {
          RPFCommandFile.CreateDirectoryCommand directoryCommand = (RPFCommandFile.CreateDirectoryCommand) command;
          string fullPath = directoryCommand.ParentDir.Replace('\\', '/');
          RPF6.RPF6TOC.TOCSuperEntry entryByPath = rpF6.TOC.GetEntryByPath(fullPath);
          if (entryByPath != null && entryByPath.IsDir)
          {
            RPF6FileNameHandler.AddName(directoryCommand.DirName);
            RPF6FileNameHandler.SaveNames();
            uint newDirHash = DataUtils.GetHash(directoryCommand.DirName);
            if (entryByPath.AllChildren.Count<RPF6.RPF6TOC.TOCSuperEntry>((Func<RPF6.RPF6TOC.TOCSuperEntry, bool>) (x => (int) x.Entry.NameOffset == (int) newDirHash)) == 0)
            {
              RPF6.RPF6TOC.TOCSuperEntry child = new RPF6.RPF6TOC.TOCSuperEntry();
              child.SuperParent = entryByPath;
              RPF6.RPF6TOC.TOCSuperEntry tocSuperEntry = child;
              RPF6.RPF6TOC.DirectoryEntry directoryEntry = new RPF6.RPF6TOC.DirectoryEntry();
              directoryEntry.Name = directoryCommand.DirName;
              directoryEntry.Parent = entryByPath.Entry.AsDirectory;
              tocSuperEntry.Entry = (RPF6.RPF6TOC.TOCEntry) directoryEntry;
              entryByPath.AddChild(child);
            }
            else if (RPFCommandFile.OnError != null)
              RPFCommandFile.OnError((object) this, new RPF6ErrorReport()
              {
                Ex = (Exception) null,
                Message = string.Format("Could not create directory \"{0}\" in \"{1}\"\r\nA directory with that name already exists here!", (object) directoryCommand.DirName, (object) fullPath)
              });
          }
          else if (RPFCommandFile.OnError != null)
            RPFCommandFile.OnError((object) this, new RPF6ErrorReport()
            {
              Ex = (Exception) null,
              Message = string.Format("Could not create directory \"{0}\" in \"{1}\"\r\nParent path does not exist!", (object) directoryCommand.DirName, (object) fullPath)
            });
        }
      }
    }

    private void ReadCommands(PikIO io)
    {
      int num = io.ReadInt32();
      for (int index = 0; index < num; ++index)
      {
        switch (io.ReadByte())
        {
          case 0:
            this.Commands.Add((RPFCommandFile.Command) RPFCommandFile.OpenRPFCommand.ReadNew(io));
            break;
          case 1:
            this.Commands.Add((RPFCommandFile.Command) RPFCommandFile.ExtractFileCommand.ReadNew(io));
            break;
          case 2:
            this.Commands.Add((RPFCommandFile.Command) RPFCommandFile.CloseRPFCommand.ReadNew(io));
            break;
          case 3:
            this.Commands.Add((RPFCommandFile.Command) RPFCommandFile.ImportReplaceCommand.ReadNew(io));
            break;
          case 4:
            this.Commands.Add((RPFCommandFile.Command) RPFCommandFile.SaveRPFCommand.ReadNew(io));
            break;
          case 5:
            this.Commands.Add((RPFCommandFile.Command) RPFCommandFile.CreateDirectoryCommand.ReadNew(io));
            break;
        }
      }
    }

    public void Write(PikIO io)
    {
      io.Write(1481920579);
      io.Write(0);
      io.Write(this.Commands.Count);
      foreach (RPFCommandFile.Command command in this.Commands)
        command.Write(io);
    }

    public enum CommandID : byte
    {
      OpenRPF,
      ExtractFile,
      CloseRPF,
      ImportReplace,
      SaveRPF,
      CreateDir,
    }

    public abstract class Command
    {
      public RPFCommandFile.CommandID ID { get; set; }

      public abstract void Write(PikIO io);
    }

    public class OpenRPFCommand : RPFCommandFile.Command
    {
      public OpenRPFCommand() => this.ID = RPFCommandFile.CommandID.OpenRPF;

      public short StreamID { get; set; }

      public string RPFFileName { get; set; }

      public static RPFCommandFile.OpenRPFCommand ReadNew(PikIO io)
      {
        RPFCommandFile.OpenRPFCommand openRpfCommand = new RPFCommandFile.OpenRPFCommand();
        openRpfCommand.StreamID = io.ReadInt16();
        BinaryReader binaryReader = new BinaryReader(io.BaseStream);
        openRpfCommand.RPFFileName = binaryReader.ReadString();
        return openRpfCommand;
      }

      public override void Write(PikIO io)
      {
        io.WriteByte((byte) this.ID);
        io.Write(this.StreamID);
        if (this.RPFFileName == null || this.RPFFileName.Length == 0)
          io.WriteByte((byte) 0);
        else
          new BinaryWriter(io.BaseStream).Write(this.RPFFileName);
      }

      public override string ToString() => "Open RPF";
    }

    public class CloseRPFCommand : RPFCommandFile.Command
    {
      public CloseRPFCommand() => this.ID = RPFCommandFile.CommandID.CloseRPF;

      public short StreamID { get; set; }

      public override void Write(PikIO io)
      {
        io.Write((byte) this.ID);
        io.Write(this.StreamID);
      }

      public static RPFCommandFile.CloseRPFCommand ReadNew(PikIO io) => new RPFCommandFile.CloseRPFCommand()
      {
        StreamID = io.ReadInt16()
      };

      public override string ToString() => "Close RPF";
    }

    public class SaveRPFCommand : RPFCommandFile.Command
    {
      public SaveRPFCommand() => this.ID = RPFCommandFile.CommandID.SaveRPF;

      public string OutRPFFile { get; set; }

      public bool SaveInOffsetOrder { get; set; }

      public static RPFCommandFile.SaveRPFCommand ReadNew(PikIO io)
      {
        RPFCommandFile.SaveRPFCommand saveRpfCommand = new RPFCommandFile.SaveRPFCommand();
        BinaryReader binaryReader = new BinaryReader(io.BaseStream);
        saveRpfCommand.OutRPFFile = binaryReader.ReadString();
        saveRpfCommand.SaveInOffsetOrder = io.ReadBool();
        return saveRpfCommand;
      }

      public override void Write(PikIO io)
      {
        io.Write((byte) this.ID);
        BinaryWriter binaryWriter = new BinaryWriter(io.BaseStream);
        if (this.OutRPFFile == null)
          io.WriteByte((byte) 0);
        else
          binaryWriter.Write(this.OutRPFFile);
        io.Write(this.SaveInOffsetOrder);
      }

      public override string ToString() => "Save RPF";
    }

    public class ImportReplaceCommand : RPFCommandFile.Command
    {
      public ImportReplaceCommand() => this.ID = RPFCommandFile.CommandID.ImportReplace;

      public short StreamID { get; set; }

      public string RPFFileName { get; set; }

      public string InFileName { get; set; }

      public bool KeepName { get; set; }

      public bool KeepOffset { get; set; }

      public bool Compress { get; set; }

      public bool Resource { get; set; }

      public int Flag1 { get; set; }

      public int Flag2 { get; set; }

      public static RPFCommandFile.ImportReplaceCommand ReadNew(PikIO io)
      {
        RPFCommandFile.ImportReplaceCommand importReplaceCommand = new RPFCommandFile.ImportReplaceCommand();
        BinaryReader binaryReader = new BinaryReader(io.BaseStream);
        importReplaceCommand.StreamID = io.ReadInt16();
        importReplaceCommand.RPFFileName = binaryReader.ReadString();
        importReplaceCommand.InFileName = binaryReader.ReadString();
        importReplaceCommand.KeepName = io.ReadBool();
        importReplaceCommand.KeepOffset = io.ReadBool();
        importReplaceCommand.Compress = io.ReadBool();
        importReplaceCommand.Resource = io.ReadBool();
        importReplaceCommand.Flag1 = io.ReadInt32();
        importReplaceCommand.Flag2 = io.ReadInt32();
        return importReplaceCommand;
      }

      public override void Write(PikIO io)
      {
        BinaryWriter binaryWriter = new BinaryWriter(io.BaseStream);
        io.Write((byte) this.ID);
        io.Write(this.StreamID);
        if (this.RPFFileName == null)
          io.WriteByte((byte) 0);
        else
          binaryWriter.Write(this.RPFFileName);
        if (this.InFileName == null)
          io.WriteByte((byte) 0);
        else
          binaryWriter.Write(this.InFileName);
        io.Write(this.KeepName);
        io.Write(this.KeepOffset);
        io.Write(this.Compress);
        io.Write(this.Resource);
        io.Write(this.Flag1);
        io.Write(this.Flag2);
      }

      public override string ToString() => "Import/Replace";
    }

    public class ExtractFileCommand : RPFCommandFile.Command
    {
      public ExtractFileCommand() => this.ID = RPFCommandFile.CommandID.ExtractFile;

      public short StreamID { get; set; }

      public bool UnpackResourceIfNeeded { get; set; }

      public bool DecompressIfNeeded { get; set; }

      public string RPFFileName { get; set; }

      public string OutFileName { get; set; }

      public static RPFCommandFile.ExtractFileCommand ReadNew(PikIO io)
      {
        RPFCommandFile.ExtractFileCommand extractFileCommand = new RPFCommandFile.ExtractFileCommand();
        extractFileCommand.StreamID = io.ReadInt16();
        extractFileCommand.UnpackResourceIfNeeded = io.ReadBool();
        extractFileCommand.DecompressIfNeeded = io.ReadBool();
        BinaryReader binaryReader = new BinaryReader(io.BaseStream);
        extractFileCommand.RPFFileName = binaryReader.ReadString();
        extractFileCommand.OutFileName = binaryReader.ReadString();
        return extractFileCommand;
      }

      public override void Write(PikIO io)
      {
        io.Write((byte) this.ID);
        io.Write(this.StreamID);
        io.Write(this.UnpackResourceIfNeeded);
        io.Write(this.DecompressIfNeeded);
        BinaryWriter binaryWriter = new BinaryWriter(io.BaseStream);
        if (this.RPFFileName == null)
          binaryWriter.Write((byte) 0);
        else
          binaryWriter.Write(this.RPFFileName);
        if (this.OutFileName == null)
          binaryWriter.Write((byte) 0);
        else
          binaryWriter.Write(this.OutFileName);
      }

      public override string ToString() => "Extract File";
    }

    public class CreateDirectoryCommand : RPFCommandFile.Command
    {
      public CreateDirectoryCommand() => this.ID = RPFCommandFile.CommandID.CreateDir;

      public short StreamID { get; set; }

      public string ParentDir { get; set; }

      public string DirName { get; set; }

      public static RPFCommandFile.CreateDirectoryCommand ReadNew(PikIO io)
      {
        RPFCommandFile.CreateDirectoryCommand directoryCommand = new RPFCommandFile.CreateDirectoryCommand();
        directoryCommand.StreamID = io.ReadInt16();
        BinaryReader binaryReader = new BinaryReader(io.BaseStream);
        directoryCommand.ParentDir = binaryReader.ReadString();
        directoryCommand.DirName = binaryReader.ReadString();
        return directoryCommand;
      }

      public override void Write(PikIO io)
      {
        io.Write((byte) this.ID);
        io.Write(this.StreamID);
        BinaryWriter binaryWriter = new BinaryWriter(io.BaseStream);
        if (this.ParentDir == null)
          io.WriteByte((byte) 0);
        else
          binaryWriter.Write(this.ParentDir);
        if (this.DirName == null)
          io.WriteByte((byte) 0);
        else
          binaryWriter.Write(this.DirName);
      }

      public override string ToString() => "Create Directory";
    }
  }
}
