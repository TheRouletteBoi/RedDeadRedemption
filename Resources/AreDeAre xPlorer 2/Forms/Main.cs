using AreDeAre_xPlorer_2.Forms.Viewers;
using ComponentOwl.BetterListView;
using DevExpress.Utils;
using DevExpress.Utils.Menu;
using DevExpress.XtraBars;
using DevExpress.XtraEditors;
using DevExpress.XtraEditors.Controls;
using Pik;
using Pik.IO;
using RAGE;
using RAGE.RDR2;
using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Media;
using System.Windows.Forms;

namespace AreDeAre_xPlorer_2.Forms
{
  public class Main : XtraForm
  {
    private RPF6 CurrentRPF;
    private RPF6.RPF6TOC.TOCSuperEntry CurrentDirectory;
    private Stream CurrentRPFStream;
    private string CurrentRPFFileName;
    private Dictionary<int, Tuple<bool, bool, string, string>> SupportedRSCTypes = new Dictionary<int, Tuple<bool, bool, string, string>>();
    private List<string> SupportedNonResourceExtensions = new List<string>();
    private IContainer components = (IContainer) null;
    private Panel mainPanel;
    private ComponentOwl.BetterListView.BetterListView rpfViewer;
    private BetterListViewColumnHeader InfoHeader;
    private BetterListViewColumnHeader SizeHeader;
    private ContextMenuStrip fileOptions;
    private ToolStripMenuItem importButton;
    private ToolStripMenuItem removeFileButton;
    private ToolStripMenuItem extractFileButton;
    private ToolStripSeparator toolStripSeparator2;
    private ToolStripMenuItem createDirectoryButton;
    private ToolStripMenuItem replaceFileButton;
    private ToolStripSeparator toolStripSeparator3;
    private ToolStripMenuItem viewFilePropertiesButton;
    private ImageList iconList;
    private BetterListViewColumnHeader nameColumn;
    private ToolStripMenuItem extractTheseFilesButton;
    private ToolStripSeparator toolStripSeparator5;
    private ToolStripMenuItem extractResourceButton;
    private ToolStripSeparator toolStripSeparator4;
    private ToolStripMenuItem copyPathButton;
    private BarManager mainBarManager;
    private Bar bar2;
    private BarButtonItem barButtonItem1;
    private Bar statusStrip;
    private BarDockControl barDockControlTop;
    private BarDockControl barDockControlBottom;
    private BarDockControl barDockControlLeft;
    private BarDockControl barDockControlRight;
    private BarAndDockingController barAndDockingController;
    private BarSubItem fileButton;
    private BarButtonItem createNewButton;
    private BarButtonItem openButton;
    private BarSubItem saveButton;
    private BarButtonItem saveCurrentButton;
    private BarButtonItem saveAsNewButton;
    private BarButtonItem closeButton;
    private BarSubItem toolsButton;
    private BarSubItem toolsExtractButton;
    private BarButtonItem extractResourceFilesButton;
    private BarButtonItem extractNonResourceFilesButton;
    private BarButtonItem extractRootDirectoryButton;
    private BarButtonItem unpackResourceButton;
    private BarSubItem barSubItem5;
    private BarStaticItem barStaticItem1;
    private BarButtonItem barButtonItem11;
    private BarSubItem barSubItem6;
    private BarButtonItem changePlatformButton;
    private BarButtonItem barButtonItem12;
    private BarButtonItem aboutButton;
    private BarButtonItem barButtonItem2;
    private Bar bar1;
    private BarSubItem barSubItem1;
    private BreadCrumbEdit directoryCrumb;
    private BarStaticItem fileCountStatusLabel;
    private BarStaticItem barStaticItem2;
    private BarStaticItem fileNameStatusLabe;
    private BarStaticItem fileSavedStatus;
    private BarStaticItem entryCountLabel;
    private SkinBarSubItem skinBarSubItem1;
    private ToolStripMenuItem viewFileTypeButton;
    private BarSubItem barSubItem2;
    private BarButtonItem stringTableViewerButton;

    public Main()
    {
      this.InitializeComponent();
      this.SupportedRSCTypes.Add(1, new Tuple<bool, bool, string, string>(true, false, "String Table", "Frag"));
      if (AppUtils.FileExists("settings.dat"))
        AppGlobals.Settings.Load(AppUtils.OpenFile("settings.dat", System.IO.FileMode.Open, FileAccess.ReadWrite, FileShare.ReadWrite));
      this.Text = string.Format("AreDeAre xPlorer 2 - by XBLToothPik [{0}]", AppGlobals.Platform == AppGlobals.PlatformEnum.Xbox ? (object) "Xbox 360" : (object) "Playstation 3");
    }

    private void createNewButton_Click(object sender, ItemClickEventArgs e)
    {
      if (this.CurrentRPF != null && MessageBox.Show("Are you sure you want to close the current file?", "Close File - Confirm", MessageBoxButtons.YesNo) == DialogResult.No)
        return;
      this.CurrentRPF = new RPF6();
      RPF6.RPF6TOC.TOCSuperEntry super = new RPF6.RPF6TOC.TOCSuperEntry();
      RPF6.RPF6TOC.DirectoryEntry directoryEntry = new RPF6.RPF6TOC.DirectoryEntry();
      super.Entry = (RPF6.RPF6TOC.TOCEntry) directoryEntry;
      directoryEntry.Name = "root";
      this.CurrentRPF.TOC.SuperEntries.Add(super);
      this.fileCountStatusLabel.Caption = string.Format("File Count: {0} | Directory Count: {1}", (object) this.CurrentRPF.Header.FileCount, (object) this.CurrentRPF.Header.DirectoryCount);
      this.LoadDirectory(super);
      this.mainPanel.Enabled = true;
    }

    private void openButton_Click(object sender, ItemClickEventArgs e)
    {
      OpenFileDialog openFileDialog = new OpenFileDialog();
      openFileDialog.Title = "Open Red Dead RPF...";
      openFileDialog.Filter = "|*.rpf";
      if (openFileDialog.ShowDialog() != DialogResult.OK)
        return;
      this.LoadRPF(openFileDialog.FileName);
    }

    private void saveCurrentButton_Click(object sender, ItemClickEventArgs e)
    {
      AppGlobals.Settings.WriteFilesInOffsetOrder = MessageBox.Show("Would you like to sort File Entries by offset?", "Write Order", MessageBoxButtons.YesNo) == DialogResult.Yes;
      if (MessageBox.Show("Are you sure you want to overwrite the current RPF?", "Overwrite RPF - Confirm", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
        return;
      string fullPath = string.Empty;
      if (this.CurrentDirectory != null)
        fullPath = this.CurrentDirectory.Entry.GetPath();
      string tempFileName = Path.GetTempFileName();
      Stream xOut = (Stream) File.Open(tempFileName, System.IO.FileMode.Open, FileAccess.ReadWrite);
      this.SaveRPF(xOut);
      this.CurrentRPFStream.Close();
      xOut.Close();
      File.Delete(this.CurrentRPFFileName);
      File.Move(tempFileName, string.Format("{0}{1}{2}", (object) Path.GetDirectoryName(this.CurrentRPFFileName), (object) Path.DirectorySeparatorChar, (object) Path.GetFileName(this.CurrentRPFFileName)));
      this.CurrentRPFStream = (Stream) File.Open(this.CurrentRPFFileName, System.IO.FileMode.Open);
      this.CurrentRPF.RPFIO = new PikIO(this.CurrentRPFStream, PikIO.Endianess.Big);
      RPF6.RPF6TOC.TOCSuperEntry super = fullPath == string.Empty ? (RPF6.RPF6TOC.TOCSuperEntry) null : this.CurrentRPF.TOC.GetEntryByPath(fullPath);
      if (super != null)
        this.LoadDirectory(super);
      else
        this.LoadDirectory(this.CurrentRPF.TOC.SuperEntries[0]);
      this.fileCountStatusLabel.Caption = string.Format("File Count: {0} | Directory Count: {1}", (object) this.CurrentRPF.Header.FileCount, (object) this.CurrentRPF.Header.DirectoryCount);
    }

    private void saveAsNewButton_Click(object sender, ItemClickEventArgs e)
    {
      AppGlobals.Settings.WriteFilesInOffsetOrder = MessageBox.Show("Would you like to sort File Entries by offset?", "Write Order", MessageBoxButtons.YesNo) == DialogResult.Yes;
      SaveFileDialog saveFileDialog = new SaveFileDialog();
      saveFileDialog.Title = "Save RPF...";
      saveFileDialog.Filter = "RPF|*.rpf|All Files|*.*";
      if (saveFileDialog.ShowDialog() != DialogResult.OK)
        return;
      string fullPath = string.Empty;
      if (this.CurrentDirectory != null)
        fullPath = this.CurrentDirectory.Entry.GetPath();
      Stream xOut = (Stream) File.Create(saveFileDialog.FileName, 262144);
      this.SaveRPF(xOut);
      xOut.Close();
      RPF6.RPF6TOC.TOCSuperEntry super = fullPath == string.Empty ? (RPF6.RPF6TOC.TOCSuperEntry) null : this.CurrentRPF.TOC.GetEntryByPath(fullPath);
      if (super != null)
        this.LoadDirectory(super);
      else
        this.LoadDirectory(this.CurrentRPF.TOC.SuperEntries[0]);
      this.fileCountStatusLabel.Caption = string.Format("File Count: {0} | Directory Count: {1}", (object) this.CurrentRPF.Header.FileCount, (object) this.CurrentRPF.Header.DirectoryCount);
    }

    private void closeButton_Click(object sender, ItemClickEventArgs e)
    {
      if (MessageBox.Show("Are you sure you want to close the current file?", "Close File - Confirm", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
        return;
      this.mainPanel.Enabled = false;
      this.rpfViewer.Items.Clear();
      this.SetPathNoOverflow("");
      this.CurrentRPF.CloseAllStreams();
      this.CurrentRPF = (RPF6) null;
      this.CurrentDirectory = (RPF6.RPF6TOC.TOCSuperEntry) null;
      this.fileCountStatusLabel.Caption = "";
      this.fileNameStatusLabe.Caption = "";
      this.fileSavedStatus.Caption = "";
      this.entryCountLabel.Caption = "";
      if (this.CurrentRPFStream != null)
      {
        this.CurrentRPFStream.Close();
        this.CurrentRPFStream = (Stream) null;
      }
    }

    private void extractResourceFilesButton_ItemClick(object sender, ItemClickEventArgs e)
    {
      FolderBrowserDialog folderBrowserDialog = new FolderBrowserDialog();
      if (folderBrowserDialog.ShowDialog() != DialogResult.OK)
        return;
      bool unpackResources = MessageBox.Show("Would you like to unpack resources?", "Export Resources - Unpack All", MessageBoxButtons.YesNo) == DialogResult.Yes;
      this.ExportFiles(folderBrowserDialog.SelectedPath, true, unpackResources);
      SystemSounds.Asterisk.Play();
    }

    private void extractNonResourceFilesButton_ItemClick(object sender, ItemClickEventArgs e)
    {
      FolderBrowserDialog folderBrowserDialog = new FolderBrowserDialog();
      if (folderBrowserDialog.ShowDialog() != DialogResult.OK)
        return;
      this.ExportFiles(folderBrowserDialog.SelectedPath, false, false);
      SystemSounds.Asterisk.Play();
    }

    private void extractRootDirectoryButton_ItemClick(object sender, ItemClickEventArgs e)
    {
      FolderBrowserDialog folderBrowserDialog = new FolderBrowserDialog();
      if (folderBrowserDialog.ShowDialog() != DialogResult.OK)
        return;
      WorkForm workForm = new WorkForm(this.CurrentRPF, this.CurrentRPF.TOC.SuperEntries[0], folderBrowserDialog.SelectedPath);
      if (!workForm.Done)
      {
        int num1 = (int) workForm.ShowDialog();
      }
      if (workForm.ExportFilesException != null)
      {
        int num2 = (int) MessageBox.Show(string.Format("An Error Occurred Exporting Root Directory:\r\n{0}\r\n\r\n{1}", (object) workForm.ExportFilesException.Message, (object) workForm.ExportFilesException.StackTrace), "Export Root - Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }
      workForm.Dispose();
    }

    private void unpackResourceButton_ItemClick(object sender, ItemClickEventArgs e)
    {
      OpenFileDialog openFileDialog = new OpenFileDialog();
      openFileDialog.Title = "Open Resource...";
      openFileDialog.Filter = "|*.*";
      if (openFileDialog.ShowDialog() != DialogResult.OK)
        return;
      Stream stream1 = (Stream) File.Open(openFileDialog.FileName, System.IO.FileMode.Open, FileAccess.Read, FileShare.ReadWrite);
      if (ResourceUtils.ResourceInfo.IsResourceStream(stream1))
      {
        byte[] dataFromStream = ResourceUtils.ResourceInfo.GetDataFromStream(stream1);
        SaveFileDialog saveFileDialog = new SaveFileDialog();
        saveFileDialog.Title = "Export Resource Data";
        saveFileDialog.Filter = "|*.*";
        if (saveFileDialog.ShowDialog() == DialogResult.OK)
        {
          Stream stream2 = (Stream) File.Create(saveFileDialog.FileName);
          stream2.Write(dataFromStream, 0, dataFromStream.Length);
          stream2.Flush();
          stream2.Close();
          stream1.Close();
          SystemSounds.Asterisk.Play();
        }
      }
      else
      {
        int num = (int) MessageBox.Show("Not a valid resource file", "Invalid Resource File", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }
    }

    private void stringTableViewerButton_ItemClick(object sender, ItemClickEventArgs e)
    {
      int num = (int) new Viewer_ST(this.CurrentRPF).ShowDialog();
    }

    private void aboutButton_ItemClick(object sender, ItemClickEventArgs e)
    {
      int num = (int) new AboutForm().ShowDialog();
    }

    private void changePlatformButton_ItemClick(object sender, ItemClickEventArgs e) => Application.Restart();

    private void rpfViewer_DoubleClick(object sender, EventArgs e)
    {
      if (this.rpfViewer.SelectedItems.Count <= 0)
        return;
      BetterListViewItem selectedItem = this.rpfViewer.SelectedItems[0];
      if (selectedItem.Tag is RPF6.RPF6TOC.TOCSuperEntry)
      {
        RPF6.RPF6TOC.TOCSuperEntry tag = selectedItem.Tag as RPF6.RPF6TOC.TOCSuperEntry;
        if (tag.IsDir)
        {
          this.LoadDirectory(tag);
          RPF6.RPF6TOC.DirectoryEntry asDirectory = tag.Entry.AsDirectory;
        }
        else
        {
          PropertiesForm propertiesForm = new PropertiesForm(tag);
          int num = (int) propertiesForm.ShowDialog();
          if (propertiesForm.ModifiedProperties)
            this.LoadDirectory(this.CurrentDirectory);
        }
      }
      else if (selectedItem.Tag is object[])
      {
        object[] tag = (object[]) selectedItem.Tag;
        RPF6.RPF6TOC.TOCSuperEntry super = (RPF6.RPF6TOC.TOCSuperEntry) tag[0];
        if (!(bool) tag[1])
          return;
        this.LoadDirectory(super);
      }
      else
      {
        int num = (int) MessageBox.Show("BLVI Tag was unknown.  This shouldn't have happened..\r\nApplication Will Exit", "Program Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
        Application.Exit();
      }
    }

    private void importButton_Click(object sender, EventArgs e) => this.DoFileImportReplace();

    private void removeFileButton_Click(object sender, EventArgs e)
    {
      if (this.rpfViewer.SelectedItems.Count <= 0)
        return;
      this.rpfViewer.BeginUpdate();
      BetterListViewItem selectedItem = this.rpfViewer.SelectedItems[0];
      if (selectedItem.Tag is RPF6.RPF6TOC.TOCSuperEntry)
      {
        RPF6.RPF6TOC.TOCSuperEntry tag = (RPF6.RPF6TOC.TOCSuperEntry) selectedItem.Tag;
        bool markedNotToBeWritten = tag.DoesHaveParentMarkedNotToBeWritten;
        if (!markedNotToBeWritten && tag.Write)
          tag.MarkAsNotToBeWritten(false, this.CurrentRPF.TOC.SuperEntries);
        else if (tag.Write && !tag.DoesHaveParentMarkedNotToBeWritten)
          tag.MarkAsNotToBeWritten(false, this.CurrentRPF.TOC.SuperEntries);
        else if (!tag.Write && !markedNotToBeWritten)
          tag.MarkAsNotToBeWritten(true, this.CurrentRPF.TOC.SuperEntries);
        selectedItem.BackColor = tag.Write ? (tag.CustomDataStream == null ? Color.Empty : Color.FromArgb(150, 50, (int) byte.MaxValue, 50)) : Color.FromArgb(150, (int) byte.MaxValue, 50, 50);
      }
      this.rpfViewer.EndUpdate();
    }

    private void extractFileButton_Click(object sender, EventArgs e)
    {
      if (this.rpfViewer.SelectedItems.Count <= 0)
        return;
      this.rpfViewer.BeginUpdate();
      BetterListViewItem selectedItem = this.rpfViewer.SelectedItems[0];
      if (selectedItem.Tag is RPF6.RPF6TOC.TOCSuperEntry)
      {
        RPF6.RPF6TOC.TOCSuperEntry tag = (RPF6.RPF6TOC.TOCSuperEntry) selectedItem.Tag;
        if (!tag.IsDir)
        {
          SaveFileDialog saveFileDialog = new SaveFileDialog();
          saveFileDialog.Title = string.Format("Export {0}..", (object) tag.Entry.Name);
          saveFileDialog.Filter = "|*.*";
          saveFileDialog.FileName = tag.Entry.Name;
          if (saveFileDialog.ShowDialog() == DialogResult.OK)
          {
            try
            {
              Stream xOut = (Stream) File.Create(saveFileDialog.FileName);
              this.CurrentRPF.TOC.ExtractFile(tag, xOut);
              xOut.Close();
              SystemSounds.Asterisk.Play();
            }
            catch (Exception ex)
            {
              int num = (int) MessageBox.Show(string.Format("Could not export file.\r\nError:\r\n\r\n{0}\r\n\r\nStack Trace: {1}", (object) ex.Message, (object) ex.StackTrace), "Export Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
            }
          }
        }
        else
        {
          FolderBrowserDialog folderBrowserDialog = new FolderBrowserDialog();
          if (folderBrowserDialog.ShowDialog() == DialogResult.OK)
          {
            WorkForm workForm = new WorkForm(this.CurrentRPF, tag, folderBrowserDialog.SelectedPath);
            if (!workForm.Done)
            {
              int num1 = (int) workForm.ShowDialog();
            }
            if (workForm.ExportFilesException != null)
            {
              int num2 = (int) MessageBox.Show(string.Format("An Error Occurred Exporting Directory:\r\n{0}\r\n\r\n{1}", (object) workForm.ExportFilesException.Message, (object) workForm.ExportFilesException.StackTrace), "Export Directory - Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
            }
            workForm.Dispose();
          }
        }
      }
      this.rpfViewer.EndUpdate();
    }

    private void viewFilePropertiesButton_Click(object sender, EventArgs e)
    {
      foreach (BetterListViewItem selectedItem in (BetterListViewCachedCollection<BetterListViewItem>) this.rpfViewer.SelectedItems)
      {
        if (selectedItem.Tag is RPF6.RPF6TOC.TOCSuperEntry)
        {
          PropertiesForm propertiesForm = new PropertiesForm((RPF6.RPF6TOC.TOCSuperEntry) selectedItem.Tag);
          int num = (int) propertiesForm.ShowDialog();
          if (propertiesForm.ModifiedProperties)
            this.LoadDirectory(this.CurrentDirectory);
        }
      }
    }

    private void createDirectoryToolStripMenuItem_Click(object sender, EventArgs e)
    {
      List<RPF6.RPF6TOC.TOCSuperEntry> allChildren = this.CurrentDirectory.AllChildren;
      NameDirectoryForm nameDirectoryForm = new NameDirectoryForm();
      int num1 = (int) nameDirectoryForm.ShowDialog();
      if (string.IsNullOrEmpty(nameDirectoryForm.NewDirectoryName))
        return;
      uint newDirHash = DataUtils.GetHash(nameDirectoryForm.NewDirectoryName);
      if (allChildren.Count<RPF6.RPF6TOC.TOCSuperEntry>((Func<RPF6.RPF6TOC.TOCSuperEntry, bool>) (x => (int) x.Entry.NameOffset == (int) newDirHash)) == 0)
      {
        RPF6FileNameHandler.AddName(nameDirectoryForm.NewDirectoryName);
        RPF6FileNameHandler.SaveNames();
        RPF6.RPF6TOC.TOCSuperEntry child = new RPF6.RPF6TOC.TOCSuperEntry();
        child.SuperParent = this.CurrentDirectory;
        RPF6.RPF6TOC.TOCSuperEntry tocSuperEntry = child;
        RPF6.RPF6TOC.DirectoryEntry directoryEntry = new RPF6.RPF6TOC.DirectoryEntry();
        directoryEntry.Name = nameDirectoryForm.NewDirectoryName;
        directoryEntry.Parent = this.CurrentDirectory.SuperParent == null ? (RPF6.RPF6TOC.DirectoryEntry) null : this.CurrentDirectory.SuperParent.Entry.AsDirectory;
        tocSuperEntry.Entry = (RPF6.RPF6TOC.TOCEntry) directoryEntry;
        this.CurrentDirectory.AddChild(child);
        this.LoadDirectory(this.CurrentDirectory);
      }
      else
      {
        int num2 = (int) MessageBox.Show(string.Format("A Directory With The Name Of \"{0}\" Already Exists Here!", (object) nameDirectoryForm.NewDirectoryName), "Directory Already Exists", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }
    }

    private void replaceFileButton_Click(object sender, EventArgs e)
    {
      foreach (BetterListViewItem selectedItem in (BetterListViewCachedCollection<BetterListViewItem>) this.rpfViewer.SelectedItems)
      {
        if (selectedItem.Tag is RPF6.RPF6TOC.TOCSuperEntry)
        {
          RPF6.RPF6TOC.TOCSuperEntry tag = (RPF6.RPF6TOC.TOCSuperEntry) selectedItem.Tag;
          if (!tag.IsDir && tag.CustomDataStream != null && tag.IsFileFromRPF)
          {
            tag.CustomDataStream = (Stream) null;
            tag.ReadBackFromRPF = true;
            tag.Entry = tag.OldEntry;
          }
          else
            this.DoFileImportReplace(replaceTab: true);
        }
      }
      this.LoadDirectory(this.CurrentDirectory);
    }

    private void extractResourceButton_Click(object sender, EventArgs e)
    {
      if (this.rpfViewer.SelectedItems.Count <= 0)
        return;
      BetterListViewItem selectedItem = this.rpfViewer.SelectedItems[0];
      if (selectedItem.Tag is RPF6.RPF6TOC.TOCSuperEntry)
      {
        RPF6.RPF6TOC.TOCSuperEntry tag = (RPF6.RPF6TOC.TOCSuperEntry) selectedItem.Tag;
        MemoryStream memoryStream = new MemoryStream();
        this.CurrentRPF.TOC.ExtractFile(tag, (Stream) memoryStream);
        if (ResourceUtils.ResourceInfo.IsResourceStream((Stream) memoryStream))
        {
          byte[] dataFromStream = ResourceUtils.ResourceInfo.GetDataFromStream((Stream) memoryStream);
          SaveFileDialog saveFileDialog = new SaveFileDialog();
          saveFileDialog.Title = "Export Resource...";
          saveFileDialog.Filter = "|*.*";
          saveFileDialog.FileName = string.Format("{0}.unpacked", (object) tag.Entry.Name);
          if (saveFileDialog.ShowDialog() == DialogResult.OK)
          {
            Stream stream = (Stream) File.Create(saveFileDialog.FileName);
            stream.Write(dataFromStream, 0, dataFromStream.Length);
            stream.Flush();
            stream.Close();
            SystemSounds.Asterisk.Play();
          }
        }
        else
        {
          int num = (int) MessageBox.Show(string.Format("{0} was not a valid resource file", (object) tag.Entry.Name), "Invalid Resource File", MessageBoxButtons.OK, MessageBoxIcon.Hand);
        }
      }
    }

    private void copyPathButton_Click(object sender, EventArgs e)
    {
      foreach (BetterListViewItem selectedItem in (BetterListViewCachedCollection<BetterListViewItem>) this.rpfViewer.SelectedItems)
      {
        if (selectedItem.Tag is RPF6.RPF6TOC.TOCSuperEntry)
        {
          RPF6.RPF6TOC.TOCSuperEntry tag = (RPF6.RPF6TOC.TOCSuperEntry) selectedItem.Tag;
          try
          {
            Clipboard.SetText(tag.GetPath());
          }
          catch (Exception ex)
          {
            int num = (int) MessageBox.Show(string.Format("Could not copy path:\r\n{0}", (object) ex.Message), "Copy Path Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
          }
        }
      }
    }

    private void viewFileTypeButton_Click(object sender, EventArgs e)
    {
      if (this.rpfViewer.SelectedItems.Count <= 0)
        return;
      BetterListViewItem selectedItem = this.rpfViewer.SelectedItems[0];
      if (selectedItem.Tag is RPF6.RPF6TOC.TOCSuperEntry)
      {
        RPF6.RPF6TOC.TOCSuperEntry tag = (RPF6.RPF6TOC.TOCSuperEntry) selectedItem.Tag;
        if (!tag.IsDir)
          this.ShowFileViewer(tag);
      }
    }

    private void createEditCommandButton_Click(object sender, EventArgs e)
    {
      int num = (int) new CommandForm().ShowDialog();
    }

    private void runCommandButton_Click(object sender, EventArgs e)
    {
      OpenFileDialog openFileDialog = new OpenFileDialog();
      openFileDialog.Title = "Open Command File...";
      openFileDialog.Filter = "|*.xtpc";
      openFileDialog.InitialDirectory = AppUtils.GetPath("editor_commands");
      if (openFileDialog.ShowDialog() != DialogResult.OK)
        return;
      Stream xIn = (Stream) File.Open(openFileDialog.FileName, System.IO.FileMode.Open);
      if (!RPFCommandFile.IsValidCommandFile(xIn))
      {
        int num = (int) MessageBox.Show("This is not a valid XTPC command file!", "Invalid Command File", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }
      else
        this.RunCommandFile(xIn);
    }

    private void toolsButton_Popup(object sender, EventArgs e) => this.toolsExtractButton.Enabled = this.CurrentRPF != null;

    private void fileButton_Popup(object sender, EventArgs e)
    {
      this.saveButton.Enabled = this.CurrentRPF != null;
      this.closeButton.Enabled = this.CurrentRPF != null;
      this.saveCurrentButton.Enabled = this.CurrentRPF != null && this.CurrentRPFStream != null && this.CurrentRPFFileName != null;
    }

    private void fileOptions_Opening(object sender, CancelEventArgs e)
    {
      this.importButton.Image = this.iconList.Images[3];
      this.createDirectoryButton.Image = this.iconList.Images[2];
      this.viewFilePropertiesButton.Image = this.iconList.Images[7];
      this.extractResourceButton.Image = this.iconList.Images[10];
      this.importButton.Enabled = this.createDirectoryButton.Enabled = this.CurrentDirectory.Write && !this.CurrentDirectory.DoesHaveParentMarkedNotToBeWritten;
      this.extractTheseFilesButton.Enabled = this.CurrentDirectory.Children.Count<RPF6.RPF6TOC.TOCSuperEntry>((Func<RPF6.RPF6TOC.TOCSuperEntry, bool>) (x => !x.IsDir)) > 0 && this.CurrentDirectory.Write && !this.CurrentDirectory.DoesHaveParentMarkedNotToBeWritten;
      if (this.rpfViewer.SelectedItems.Count > 0)
      {
        BetterListViewItem selectedItem = this.rpfViewer.SelectedItems[0];
        if (selectedItem.Tag is RPF6.RPF6TOC.TOCSuperEntry)
        {
          RPF6.RPF6TOC.TOCSuperEntry tag = (RPF6.RPF6TOC.TOCSuperEntry) selectedItem.Tag;
          this.viewFileTypeButton.Enabled = this.CanViewFileType(tag);
          this.viewFileTypeButton.Text = string.Format("View {0}", (object) this.GetViewFileTypeString(tag));
          this.copyPathButton.Enabled = true;
          this.extractFileButton.Enabled = tag.Write && !tag.DoesHaveParentMarkedNotToBeWritten;
          this.viewFilePropertiesButton.Enabled = !tag.IsDir && tag.Write && !tag.DoesHaveParentMarkedNotToBeWritten;
          this.extractResourceButton.Enabled = !tag.IsDir && !tag.DoesHaveParentMarkedNotToBeWritten && tag.Entry.AsFile.FlagInfo.IsResource;
          if (!tag.Write || tag.DoesHaveParentMarkedNotToBeWritten)
          {
            this.replaceFileButton.Enabled = false;
            this.replaceFileButton.Text = tag.IsDir ? "Replace Directory" : "Replace File";
            this.replaceFileButton.Image = tag.IsDir ? (Image) null : this.iconList.Images[6];
            this.viewFileTypeButton.Enabled = false;
          }
          if (!tag.IsDir && tag.CustomDataStream != null && tag.IsFileFromRPF)
          {
            this.replaceFileButton.Text = "Un-Replace";
            this.replaceFileButton.Enabled = true;
          }
          else if (!tag.IsDir && tag.CustomDataStream != null && !tag.IsFileFromRPF)
          {
            this.replaceFileButton.Text = "Replace File";
            this.replaceFileButton.Enabled = false;
          }
          else
          {
            this.replaceFileButton.Text = tag.IsDir ? "Replace Directory" : "Replace File";
            this.replaceFileButton.Enabled = !tag.IsDir && (tag.Write && !tag.DoesHaveParentMarkedNotToBeWritten);
            this.replaceFileButton.Image = tag.IsDir ? (Image) null : this.iconList.Images[6];
          }
          if (tag.IsDir)
          {
            this.extractFileButton.Image = this.iconList.Images[9];
            this.removeFileButton.Image = this.iconList.Images[tag.Write ? 4 : 2];
            this.removeFileButton.Text = tag.Write ? "Remove Directory" : "Un-Remove Directory";
            this.extractFileButton.Text = "Extract Directory";
          }
          else
          {
            this.extractFileButton.Image = this.iconList.Images[8];
            this.removeFileButton.Image = this.iconList.Images[tag.Write ? 5 : 3];
            this.removeFileButton.Text = tag.Write ? "Remove File" : "Un-Remove File";
            this.extractFileButton.Text = "Extract File";
          }
          if (!tag.DoesHaveParentMarkedNotToBeWritten)
            this.removeFileButton.Enabled = true;
          else
            this.removeFileButton.Enabled = false;
        }
        else
        {
          this.copyPathButton.Enabled = false;
          this.removeFileButton.Enabled = false;
          this.extractFileButton.Enabled = false;
          this.viewFilePropertiesButton.Enabled = false;
          this.replaceFileButton.Enabled = false;
          this.extractResourceButton.Enabled = false;
        }
      }
      else
      {
        this.replaceFileButton.Text = "Replace File";
        this.removeFileButton.Text = "Remove File";
        this.extractFileButton.Text = "Extract File";
        this.replaceFileButton.Enabled = false;
        this.removeFileButton.Enabled = false;
        this.extractFileButton.Enabled = false;
        this.viewFilePropertiesButton.Enabled = false;
        this.extractResourceButton.Enabled = false;
      }
    }

    private void rpfViewer_Resize(object sender, EventArgs e)
    {
      if (this.rpfViewer.Items.Count <= 0)
        return;
      this.rpfViewer.BeginUpdate();
      this.rpfViewer.HScrollBarDisplayMode = BetterListViewScrollBarDisplayMode.Hide;
      int width = this.rpfViewer.Width;
      int num = width / 2;
      this.nameColumn.Width = num;
      this.InfoHeader.Width = this.SizeHeader.Width = (width - num) / 2;
      try
      {
        this.SizeHeader.Width -= !this.rpfViewer.VScrollBarVisible ? 2 : this.rpfViewer.VScrollBarWidth + 2;
      }
      catch
      {
      }
      this.rpfViewer.EndUpdate();
      this.rpfViewer.HScrollBarDisplayMode = BetterListViewScrollBarDisplayMode.ShowIfNeeded;
    }

    private void Main_DragDrop(object sender, DragEventArgs e)
    {
      if (!e.Data.GetDataPresent(DataFormats.FileDrop))
        return;
      string[] data = (string[]) e.Data.GetData(DataFormats.FileDrop);
      int num1 = ((IEnumerable<string>) data).Count<string>((Func<string, bool>) (x => Path.GetExtension(x) == ".rpf"));
      if (num1 > 1)
      {
        int num2 = (int) MessageBox.Show("You cannot open multiple RPFs at the same time!", "Multiple RPFs", MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
      }
      else if (num1 == 1)
      {
        if (data.Length > 1)
        {
          int num3 = (int) MessageBox.Show("You cannot open an RPF and other files!", "Multiple Files", MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
        }
        else
          this.LoadRPF(data[0]);
      }
      else if (this.CurrentRPF != null)
      {
        BetterListViewItem blvi = (BetterListViewItem) null;
        this.GetSelectedItemSuper(true, out blvi);
        for (int index = 0; index < data.Length; ++index)
          this.DoFileImportReplace(data.Length <= 1, data[index], data[index]);
      }
    }

    private void Main_DragEnter(object sender, DragEventArgs e)
    {
      if (!e.Data.GetDataPresent(DataFormats.FileDrop))
        return;
      string[] data = (string[]) e.Data.GetData(DataFormats.FileDrop);
      int num = ((IEnumerable<string>) data).Count<string>((Func<string, bool>) (x => Path.GetExtension(x) == ".rpf"));
      if (num > 1)
        e.Effect = DragDropEffects.None;
      else if (num == 1)
        e.Effect = data.Length <= 1 ? DragDropEffects.Link : DragDropEffects.None;
      else if (this.CurrentRPF != null)
        e.Effect = DragDropEffects.Copy;
    }

    private void directoryCrumb_PathChanged(object sender, BreadCrumbPathChangedEventArgs e) => this.LoadDirectory(this.CurrentRPF.TOC.GetEntryByPath(e.Path));

    private void ShowFileViewer(RPF6.RPF6TOC.TOCSuperEntry super)
    {
      RPF6.RPF6TOC.FileEntry asFile = super.Entry.AsFile;
      if (!asFile.FlagInfo.IsResource || asFile.ResourceType != (byte) 1 || asFile.FlagInfo.IsExtendedFlags)
        return;
      int num = (int) new Viewer_ST(super, this.CurrentRPF).ShowDialog();
    }

    private string GetViewFileTypeString(RPF6.RPF6TOC.TOCSuperEntry super)
    {
      RPF6.RPF6TOC.FileEntry asFile = super.Entry.AsFile;
      if (!this.CanViewFileType(super) || !asFile.FlagInfo.IsResource)
        return "File";
      int resourceType = (int) asFile.ResourceType;
      if (this.SupportedRSCTypes.ContainsKey(resourceType))
      {
        if (this.SupportedRSCTypes[resourceType].Item1 == !asFile.FlagInfo.IsExtendedFlags)
          return this.SupportedRSCTypes[resourceType].Item3;
        if (this.SupportedRSCTypes[resourceType].Item2 == asFile.FlagInfo.IsExtendedFlags)
          return this.SupportedRSCTypes[resourceType].Item4;
      }
      return "File";
    }

    private bool CanViewFileType(RPF6.RPF6TOC.TOCSuperEntry super)
    {
      if (super.IsDir)
        return false;
      RPF6.RPF6TOC.FileEntry asFile = super.Entry.AsFile;
      if (!asFile.FlagInfo.IsResource)
        return false;
      int resourceType = (int) asFile.ResourceType;
      return this.SupportedRSCTypes.ContainsKey(resourceType) && (this.SupportedRSCTypes[resourceType].Item1 && !asFile.FlagInfo.IsExtendedFlags || this.SupportedRSCTypes[resourceType].Item2 && asFile.FlagInfo.IsExtendedFlags);
    }

    private void SetPathNoOverflow(string newPath)
    {
      this.directoryCrumb.PathChanged -= new BreadCrumbPathChangedEventHandler(this.directoryCrumb_PathChanged);
      this.directoryCrumb.Properties.Nodes.Clear();
      this.directoryCrumb.Path = newPath;
      this.directoryCrumb.PathChanged += new BreadCrumbPathChangedEventHandler(this.directoryCrumb_PathChanged);
    }

    private void DoFileImportReplace(
      bool cursor = false,
      string importFileLoc = null,
      string replaceFileLoc = null,
      bool replaceTab = false)
    {
      BetterListViewItem blvi = (BetterListViewItem) null;
      RPF6.RPF6TOC.TOCSuperEntry selectedItemSuper = this.GetSelectedItemSuper(cursor, out blvi);
      RPF6.RPF6TOC.TOCSuperEntry selectedReplaceFile = (RPF6.RPF6TOC.TOCSuperEntry) null;
      RPF6.RPF6TOC.TOCSuperEntry selectedFile;
      if (replaceFileLoc != null && this.CurrentDirectory.DoesHaveEntry(Path.GetFileName(replaceFileLoc)))
      {
        selectedReplaceFile = this.CurrentDirectory.GetChild(Path.GetFileName(replaceFileLoc));
        selectedFile = selectedReplaceFile;
        replaceTab = true;
      }
      else
        selectedFile = selectedItemSuper;
      NewImportReplaceForm importReplaceForm = new NewImportReplaceForm(replaceTab, this.CurrentDirectory, selectedFile, selectedReplaceFile, importFileLoc, replaceFileLoc);
      int num = (int) importReplaceForm.ShowDialog();
      if (importReplaceForm.TOCResult == null)
        return;
      if (importReplaceForm.Mode == NewImportReplaceForm.FileMode.Import)
        this.CurrentDirectory.AddChild(importReplaceForm.TOCResult);
      else if (importReplaceForm.TOCResult != null)
      {
        if (selectedFile.CustomDataStream != null)
          selectedFile.CustomDataStream.Close();
        selectedFile.CustomDataStream = importReplaceForm.TOCResult.CustomDataStream;
        selectedFile.Entry = importReplaceForm.TOCResult.Entry;
        selectedFile.OldEntry = importReplaceForm.TOCResult.OldEntry;
        selectedFile.ReadBackFromRPF = false;
        if (blvi != null)
          blvi.Tag = (object) selectedFile;
      }
      this.LoadDirectory(this.CurrentDirectory);
    }

    private RPF6.RPF6TOC.TOCSuperEntry GetSelectedItemSuper(
      bool mouseCoords,
      out BetterListViewItem blvi)
    {
      RPF6.RPF6TOC.TOCSuperEntry tocSuperEntry = (RPF6.RPF6TOC.TOCSuperEntry) null;
      BetterListViewItem betterListViewItem = (BetterListViewItem) null;
      if (!mouseCoords)
      {
        if ((uint) this.rpfViewer.SelectedItems.Count > 0U)
          betterListViewItem = this.rpfViewer.SelectedItems[0];
      }
      else
        betterListViewItem = this.rpfViewer.GetItemAt(this.rpfViewer.PointToClient(Cursor.Position));
      blvi = betterListViewItem;
      if (betterListViewItem != null)
      {
        object tag = betterListViewItem.Tag;
        if (tag is object[])
        {
          tocSuperEntry = (RPF6.RPF6TOC.TOCSuperEntry) ((object[]) tag)[0];
          if (tocSuperEntry.IsDir)
            tocSuperEntry = (RPF6.RPF6TOC.TOCSuperEntry) null;
        }
        else if (tag is RPF6.RPF6TOC.TOCSuperEntry)
          tocSuperEntry = (RPF6.RPF6TOC.TOCSuperEntry) tag;
      }
      return tocSuperEntry;
    }

    private void ExportFiles(string dir, bool resourceFiles, bool unpackResources)
    {
      WorkForm workForm = new WorkForm(this.CurrentRPF, dir, resourceFiles, unpackResources);
      if (!workForm.Done)
      {
        int num1 = (int) workForm.ShowDialog();
      }
      if (workForm.ExportFilesException != null)
      {
        int num2 = (int) MessageBox.Show(string.Format("An Error Occurred Trying To Export {0}\r\n{1}\r\n\r\n{2}", resourceFiles ? (object) "Resources" : (object) "Non-Resources", (object) workForm.ExportFilesException.Message, (object) workForm.ExportFilesException.StackTrace), "Error Exporting Files", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }
      workForm.Dispose();
    }

    private void LoadDirectory(RPF6.RPF6TOC.TOCSuperEntry super)
    {
      this.CurrentDirectory = super;
      this.rpfViewer.BeginUpdate();
      this.rpfViewer.Items.Clear();
      if (!super.IsDir)
        throw new Exception("Super was not a directory");
      super.GetPathArray();
      this.SetPathNoOverflow(super.GetPath());
      this.entryCountLabel.Caption = string.Format("{0} Items", (object) this.CurrentDirectory.Children.Count);
      WorkForm workForm = new WorkForm(this.CurrentRPF, super);
      if (!workForm.Done)
      {
        int num1 = (int) workForm.ShowDialog();
      }
      if (workForm.LoadDirectoryException != null)
      {
        int num2 = (int) MessageBox.Show(string.Format("An Error Occurred Loading Directory:\r\n{0}\r\n{1}", (object) workForm.LoadDirectoryException.Message, (object) workForm.LoadDirectoryException.StackTrace), "Load Directory - Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }
      else
        this.rpfViewer.Items.AddRange((IEnumerable) workForm.ItemsToAddToListView);
      workForm.Dispose();
      this.rpfViewer.EndUpdate();
      this.rpfViewer_Resize((object) this, (EventArgs) null);
    }

    public void LoadRPF(string fileLoc)
    {
      if (this.CurrentRPF != null && MessageBox.Show("Are you sure you want to close the current RPF?\r\n\r\nAll unsaved progress will be lost.", "Close RPF Confirm", MessageBoxButtons.YesNo, MessageBoxIcon.Question) == DialogResult.No)
        return;
      this.CurrentDirectory = (RPF6.RPF6TOC.TOCSuperEntry) null;
      this.CurrentRPFFileName = fileLoc;
      this.CurrentRPFStream = (Stream) File.Open(fileLoc, System.IO.FileMode.Open, FileAccess.ReadWrite, FileShare.ReadWrite);
      this.fileNameStatusLabe.Caption = string.Format("{0}", (object) Path.GetFileName(fileLoc));
      this.LoadRPF(this.CurrentRPFStream);
    }

    public void LoadRPF(Stream xIn)
    {
      NewWorkForm newWorkForm = new NewWorkForm(this.CurrentRPFStream);
      if (!newWorkForm.Done)
      {
        int num1 = (int) newWorkForm.ShowDialog();
      }
      if (newWorkForm.OpenRPFException != null)
      {
        int num2 = (int) MessageBox.Show(string.Format("An Error Has Occurred:\r\n{0}\r\n\r\n{1}", (object) newWorkForm.OpenRPFException.Message, (object) newWorkForm.OpenRPFException.StackTrace), "Error Opening RPF", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }
      else
      {
        if (this.CurrentRPF != null)
          this.CurrentRPF.CloseAllStreams();
        this.CurrentRPF = newWorkForm.OpenRPF6Return;
        this.fileCountStatusLabel.Caption = string.Format("File Count: {0} Directory Count: {1}", (object) this.CurrentRPF.Header.FileCount, (object) this.CurrentRPF.Header.DirectoryCount);
        this.LoadDirectory(this.CurrentRPF.TOC.SuperEntries[0]);
        this.mainPanel.Enabled = true;
      }
      newWorkForm.Dispose();
    }

    private void SaveRPF(Stream xOut)
    {
      NewWorkForm newWorkForm = new NewWorkForm(xOut, this.CurrentRPF);
      if (!newWorkForm.Done)
      {
        int num1 = (int) newWorkForm.ShowDialog();
      }
      if (newWorkForm.SaveRPFException != null)
      {
        int num2 = (int) MessageBox.Show(string.Format("An Error Occurred Trying To Save RPF:\r\n{0}\r\n\r\n{1}", (object) newWorkForm.SaveRPFException.Message, (object) newWorkForm.SaveRPFException.StackTrace), "Save RPF - Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }
      else
      {
        this.fileSavedStatus.Visibility = BarItemVisibility.Always;
        this.fileSavedStatus.Caption = "File Saved!";
        Timer timer1 = new Timer();
        timer1.Interval = 3000;
        timer1.Tick += (EventHandler) ((sender, e) =>
        {
          this.fileSavedStatus.Caption = "";
          this.fileSavedStatus.Visibility = BarItemVisibility.Never;
          Timer timer = sender as Timer;
          timer.Stop();
          timer.Dispose();
        });
        timer1.Start();
      }
      newWorkForm.Dispose();
    }

    private void RunCommandFile(Stream xIn)
    {
      NewWorkForm newWorkForm = new NewWorkForm(new RPFCommandFile(xIn), xIn);
      if (newWorkForm.Done)
        return;
      int num = (int) newWorkForm.ShowDialog();
    }

    private void xSTToolStripMenuItem_Click(object sender, EventArgs e)
    {
      OpenFileDialog openFileDialog = new OpenFileDialog();
      openFileDialog.Title = "OPEN XST";
      openFileDialog.Filter = "|*.xst";
      if (openFileDialog.ShowDialog() != DialogResult.OK)
        return;
      Stream xIn = (Stream) File.Open(openFileDialog.FileName, System.IO.FileMode.Open);
      _ST st = new _ST(xIn);
      Stream xOut = (Stream) File.Create("test_stringtable");
      st.Write(xOut);
      xOut.Flush();
      xOut.Close();
      xIn.Close();
    }

    protected override void Dispose(bool disposing)
    {
      if (disposing && this.components != null)
        this.components.Dispose();
      base.Dispose(disposing);
    }

    private void InitializeComponent()
    {
      this.components = (IContainer) new Container();
      ComponentResourceManager componentResourceManager = new ComponentResourceManager(typeof (Main));
      this.mainPanel = new Panel();
      this.rpfViewer = new ComponentOwl.BetterListView.BetterListView();
      this.nameColumn = new BetterListViewColumnHeader();
      this.InfoHeader = new BetterListViewColumnHeader();
      this.SizeHeader = new BetterListViewColumnHeader();
      this.fileOptions = new ContextMenuStrip(this.components);
      this.importButton = new ToolStripMenuItem();
      this.createDirectoryButton = new ToolStripMenuItem();
      this.toolStripSeparator2 = new ToolStripSeparator();
      this.replaceFileButton = new ToolStripMenuItem();
      this.extractFileButton = new ToolStripMenuItem();
      this.removeFileButton = new ToolStripMenuItem();
      this.toolStripSeparator3 = new ToolStripSeparator();
      this.extractTheseFilesButton = new ToolStripMenuItem();
      this.toolStripSeparator5 = new ToolStripSeparator();
      this.viewFilePropertiesButton = new ToolStripMenuItem();
      this.extractResourceButton = new ToolStripMenuItem();
      this.toolStripSeparator4 = new ToolStripSeparator();
      this.copyPathButton = new ToolStripMenuItem();
      this.iconList = new ImageList(this.components);
      this.mainBarManager = new BarManager(this.components);
      this.bar2 = new Bar();
      this.fileButton = new BarSubItem();
      this.createNewButton = new BarButtonItem();
      this.openButton = new BarButtonItem();
      this.saveButton = new BarSubItem();
      this.saveCurrentButton = new BarButtonItem();
      this.saveAsNewButton = new BarButtonItem();
      this.closeButton = new BarButtonItem();
      this.toolsButton = new BarSubItem();
      this.toolsExtractButton = new BarSubItem();
      this.extractResourceFilesButton = new BarButtonItem();
      this.extractNonResourceFilesButton = new BarButtonItem();
      this.extractRootDirectoryButton = new BarButtonItem();
      this.unpackResourceButton = new BarButtonItem();
      this.barSubItem5 = new BarSubItem();
      this.barSubItem6 = new BarSubItem();
      this.aboutButton = new BarButtonItem();
      this.changePlatformButton = new BarButtonItem();
      this.statusStrip = new Bar();
      this.fileCountStatusLabel = new BarStaticItem();
      this.fileNameStatusLabe = new BarStaticItem();
      this.fileSavedStatus = new BarStaticItem();
      this.entryCountLabel = new BarStaticItem();
      this.barAndDockingController = new BarAndDockingController(this.components);
      this.barDockControlTop = new BarDockControl();
      this.barDockControlBottom = new BarDockControl();
      this.barDockControlLeft = new BarDockControl();
      this.barDockControlRight = new BarDockControl();
      this.barButtonItem1 = new BarButtonItem();
      this.barStaticItem1 = new BarStaticItem();
      this.barButtonItem11 = new BarButtonItem();
      this.barButtonItem12 = new BarButtonItem();
      this.barButtonItem2 = new BarButtonItem();
      this.barSubItem1 = new BarSubItem();
      this.barStaticItem2 = new BarStaticItem();
      this.skinBarSubItem1 = new SkinBarSubItem();
      this.bar1 = new Bar();
      this.directoryCrumb = new BreadCrumbEdit();
      this.viewFileTypeButton = new ToolStripMenuItem();
      this.barSubItem2 = new BarSubItem();
      this.stringTableViewerButton = new BarButtonItem();
      this.mainPanel.SuspendLayout();
      ((ISupportInitialize) this.rpfViewer).BeginInit();
      this.fileOptions.SuspendLayout();
      this.mainBarManager.BeginInit();
      this.barAndDockingController.BeginInit();
      this.directoryCrumb.Properties.BeginInit();
      this.SuspendLayout();
      this.mainPanel.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
      this.mainPanel.Controls.Add((Control) this.rpfViewer);
      this.mainPanel.Enabled = false;
      this.mainPanel.Location = new Point(0, 57);
      this.mainPanel.Margin = new Padding(4, 2, 4, 2);
      this.mainPanel.Name = "mainPanel";
      this.mainPanel.Size = new Size(704, 457);
      this.mainPanel.TabIndex = 2;
      this.rpfViewer.ColorSortedColumn = Color.DimGray;
      this.rpfViewer.Columns.Add(this.nameColumn);
      this.rpfViewer.Columns.Add(this.InfoHeader);
      this.rpfViewer.Columns.Add(this.SizeHeader);
      this.rpfViewer.ContextMenuStrip = this.fileOptions;
      this.rpfViewer.Dock = DockStyle.Fill;
      this.rpfViewer.Font = new Font("Arial", 9f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.rpfViewer.ImageList = this.iconList;
      this.rpfViewer.Location = new Point(0, 0);
      this.rpfViewer.Margin = new Padding(4, 2, 4, 2);
      this.rpfViewer.MaximumAutoSizeWidth = 50;
      this.rpfViewer.MultiSelect = false;
      this.rpfViewer.Name = "rpfViewer";
      this.rpfViewer.SearchSettings = new BetterListViewSearchSettings(BetterListViewSearchMode.PrefixOrSubstring, BetterListViewSearchOptions.FirstWordOnly | BetterListViewSearchOptions.PlaySound | BetterListViewSearchOptions.PrefixPreference | BetterListViewSearchOptions.WordSearch, (IEnumerable<int>) new int[1]);
      this.rpfViewer.Size = new Size(704, 457);
      this.rpfViewer.SortOnCollectionChange = false;
      this.rpfViewer.TabIndex = 0;
      this.rpfViewer.DoubleClick += new EventHandler(this.rpfViewer_DoubleClick);
      this.rpfViewer.Resize += new EventHandler(this.rpfViewer_Resize);
      this.nameColumn.Name = "nameColumn";
      this.nameColumn.Text = "Name";
      this.nameColumn.Width = 276;
      this.InfoHeader.Name = "InfoHeader";
      this.InfoHeader.Text = "Info";
      this.InfoHeader.Width = 199;
      this.SizeHeader.Name = "SizeHeader";
      this.SizeHeader.Text = "Size";
      this.SizeHeader.Width = 174;
      this.fileOptions.Font = new Font("Arial", 11f);
      this.fileOptions.Items.AddRange(new ToolStripItem[14]
      {
        (ToolStripItem) this.importButton,
        (ToolStripItem) this.createDirectoryButton,
        (ToolStripItem) this.toolStripSeparator2,
        (ToolStripItem) this.replaceFileButton,
        (ToolStripItem) this.extractFileButton,
        (ToolStripItem) this.removeFileButton,
        (ToolStripItem) this.toolStripSeparator3,
        (ToolStripItem) this.extractTheseFilesButton,
        (ToolStripItem) this.toolStripSeparator5,
        (ToolStripItem) this.viewFilePropertiesButton,
        (ToolStripItem) this.extractResourceButton,
        (ToolStripItem) this.toolStripSeparator4,
        (ToolStripItem) this.copyPathButton,
        (ToolStripItem) this.viewFileTypeButton
      });
      this.fileOptions.Name = "fileOptions";
      this.fileOptions.Size = new Size(209, 248);
      this.fileOptions.Opening += new CancelEventHandler(this.fileOptions_Opening);
      this.importButton.Name = "importButton";
      this.importButton.Size = new Size(208, 22);
      this.importButton.Text = "Import File";
      this.importButton.Click += new EventHandler(this.importButton_Click);
      this.createDirectoryButton.Name = "createDirectoryButton";
      this.createDirectoryButton.Size = new Size(208, 22);
      this.createDirectoryButton.Text = "Create Directory";
      this.createDirectoryButton.Click += new EventHandler(this.createDirectoryToolStripMenuItem_Click);
      this.toolStripSeparator2.Name = "toolStripSeparator2";
      this.toolStripSeparator2.Size = new Size(205, 6);
      this.replaceFileButton.Name = "replaceFileButton";
      this.replaceFileButton.ShortcutKeys = Keys.R | Keys.Control;
      this.replaceFileButton.Size = new Size(208, 22);
      this.replaceFileButton.Text = "Replace File";
      this.replaceFileButton.Click += new EventHandler(this.replaceFileButton_Click);
      this.extractFileButton.Name = "extractFileButton";
      this.extractFileButton.Size = new Size(208, 22);
      this.extractFileButton.Text = "Extract File";
      this.extractFileButton.Click += new EventHandler(this.extractFileButton_Click);
      this.removeFileButton.Name = "removeFileButton";
      this.removeFileButton.Size = new Size(208, 22);
      this.removeFileButton.Text = "Remove File";
      this.removeFileButton.Click += new EventHandler(this.removeFileButton_Click);
      this.toolStripSeparator3.Name = "toolStripSeparator3";
      this.toolStripSeparator3.Size = new Size(205, 6);
      this.extractTheseFilesButton.Name = "extractTheseFilesButton";
      this.extractTheseFilesButton.Size = new Size(208, 22);
      this.extractTheseFilesButton.Text = "Extract These Files";
      this.extractTheseFilesButton.Visible = false;
      this.toolStripSeparator5.Name = "toolStripSeparator5";
      this.toolStripSeparator5.Size = new Size(205, 6);
      this.toolStripSeparator5.Visible = false;
      this.viewFilePropertiesButton.Name = "viewFilePropertiesButton";
      this.viewFilePropertiesButton.Size = new Size(208, 22);
      this.viewFilePropertiesButton.Text = "View Properties";
      this.viewFilePropertiesButton.Click += new EventHandler(this.viewFilePropertiesButton_Click);
      this.extractResourceButton.Name = "extractResourceButton";
      this.extractResourceButton.Size = new Size(208, 22);
      this.extractResourceButton.Text = "Extract Resource";
      this.extractResourceButton.Click += new EventHandler(this.extractResourceButton_Click);
      this.toolStripSeparator4.Name = "toolStripSeparator4";
      this.toolStripSeparator4.Size = new Size(205, 6);
      this.copyPathButton.Enabled = false;
      this.copyPathButton.Name = "copyPathButton";
      this.copyPathButton.Size = new Size(208, 22);
      this.copyPathButton.Text = "Copy Path";
      this.copyPathButton.Click += new EventHandler(this.copyPathButton_Click);
      this.iconList.ImageStream = (ImageListStreamer) componentResourceManager.GetObject("iconList.ImageStream");
      this.iconList.TransparentColor = Color.Transparent;
      this.iconList.Images.SetKeyName(0, "folder.png");
      this.iconList.Images.SetKeyName(1, "page.png");
      this.iconList.Images.SetKeyName(2, "folder_add.png");
      this.iconList.Images.SetKeyName(3, "page_add.png");
      this.iconList.Images.SetKeyName(4, "folder_delete.png");
      this.iconList.Images.SetKeyName(5, "page_delete.png");
      this.iconList.Images.SetKeyName(6, "page_copy.png");
      this.iconList.Images.SetKeyName(7, "page_edit.png");
      this.iconList.Images.SetKeyName(8, "page_save.png");
      this.iconList.Images.SetKeyName(9, "folder_go.png");
      this.iconList.Images.SetKeyName(10, "package_go.png");
      this.mainBarManager.AllowQuickCustomization = false;
      this.mainBarManager.Bars.AddRange(new Bar[2]
      {
        this.bar2,
        this.statusStrip
      });
      this.mainBarManager.Controller = this.barAndDockingController;
      this.mainBarManager.DockControls.Add(this.barDockControlTop);
      this.mainBarManager.DockControls.Add(this.barDockControlBottom);
      this.mainBarManager.DockControls.Add(this.barDockControlLeft);
      this.mainBarManager.DockControls.Add(this.barDockControlRight);
      this.mainBarManager.Form = (Control) this;
      this.mainBarManager.Items.AddRange(new BarItem[31]
      {
        (BarItem) this.barButtonItem1,
        (BarItem) this.fileButton,
        (BarItem) this.createNewButton,
        (BarItem) this.openButton,
        (BarItem) this.saveButton,
        (BarItem) this.saveCurrentButton,
        (BarItem) this.saveAsNewButton,
        (BarItem) this.barStaticItem1,
        (BarItem) this.closeButton,
        (BarItem) this.toolsButton,
        (BarItem) this.toolsExtractButton,
        (BarItem) this.extractResourceFilesButton,
        (BarItem) this.extractNonResourceFilesButton,
        (BarItem) this.extractRootDirectoryButton,
        (BarItem) this.unpackResourceButton,
        (BarItem) this.barButtonItem11,
        (BarItem) this.barSubItem5,
        (BarItem) this.barButtonItem12,
        (BarItem) this.barSubItem6,
        (BarItem) this.changePlatformButton,
        (BarItem) this.aboutButton,
        (BarItem) this.barButtonItem2,
        (BarItem) this.barSubItem1,
        (BarItem) this.barStaticItem2,
        (BarItem) this.fileCountStatusLabel,
        (BarItem) this.fileNameStatusLabe,
        (BarItem) this.fileSavedStatus,
        (BarItem) this.entryCountLabel,
        (BarItem) this.skinBarSubItem1,
        (BarItem) this.barSubItem2,
        (BarItem) this.stringTableViewerButton
      });
      this.mainBarManager.MainMenu = this.bar2;
      this.mainBarManager.MaxItemId = 31;
      this.mainBarManager.StatusBar = this.statusStrip;
      this.bar2.BarName = "Main menu";
      this.bar2.DockCol = 0;
      this.bar2.DockRow = 0;
      this.bar2.DockStyle = BarDockStyle.Top;
      this.bar2.LinksPersistInfo.AddRange(new LinkPersistInfo[4]
      {
        new LinkPersistInfo((BarItem) this.fileButton),
        new LinkPersistInfo((BarItem) this.toolsButton),
        new LinkPersistInfo((BarItem) this.barSubItem6),
        new LinkPersistInfo((BarItem) this.changePlatformButton)
      });
      this.bar2.OptionsBar.AllowQuickCustomization = false;
      this.bar2.OptionsBar.UseWholeRow = true;
      this.bar2.Text = "Main menu";
      this.fileButton.Caption = "File";
      this.fileButton.Id = 1;
      this.fileButton.LinksPersistInfo.AddRange(new LinkPersistInfo[4]
      {
        new LinkPersistInfo((BarItem) this.createNewButton),
        new LinkPersistInfo((BarItem) this.openButton),
        new LinkPersistInfo((BarItem) this.saveButton),
        new LinkPersistInfo((BarItem) this.closeButton)
      });
      this.fileButton.Name = "fileButton";
      this.fileButton.Popup += new EventHandler(this.fileButton_Popup);
      this.createNewButton.Caption = "Create New";
      this.createNewButton.Id = 2;
      this.createNewButton.Name = "createNewButton";
      this.createNewButton.ItemClick += new ItemClickEventHandler(this.createNewButton_Click);
      this.openButton.Caption = "Open";
      this.openButton.Id = 3;
      this.openButton.Name = "openButton";
      this.openButton.ItemClick += new ItemClickEventHandler(this.openButton_Click);
      this.saveButton.Caption = "Save";
      this.saveButton.Id = 4;
      this.saveButton.LinksPersistInfo.AddRange(new LinkPersistInfo[2]
      {
        new LinkPersistInfo((BarItem) this.saveCurrentButton),
        new LinkPersistInfo((BarItem) this.saveAsNewButton)
      });
      this.saveButton.Name = "saveButton";
      this.saveCurrentButton.Caption = "Current";
      this.saveCurrentButton.Id = 5;
      this.saveCurrentButton.Name = "saveCurrentButton";
      this.saveCurrentButton.ItemClick += new ItemClickEventHandler(this.saveCurrentButton_Click);
      this.saveAsNewButton.Caption = "As New..";
      this.saveAsNewButton.Id = 6;
      this.saveAsNewButton.Name = "saveAsNewButton";
      this.saveAsNewButton.ItemClick += new ItemClickEventHandler(this.saveAsNewButton_Click);
      this.closeButton.Caption = "Close";
      this.closeButton.Id = 8;
      this.closeButton.Name = "closeButton";
      this.closeButton.ItemClick += new ItemClickEventHandler(this.closeButton_Click);
      this.toolsButton.Caption = "Tools";
      this.toolsButton.Id = 9;
      this.toolsButton.LinksPersistInfo.AddRange(new LinkPersistInfo[4]
      {
        new LinkPersistInfo((BarItem) this.toolsExtractButton),
        new LinkPersistInfo((BarItem) this.unpackResourceButton),
        new LinkPersistInfo((BarItem) this.barSubItem5),
        new LinkPersistInfo((BarItem) this.barSubItem2)
      });
      this.toolsButton.Name = "toolsButton";
      this.toolsButton.Popup += new EventHandler(this.toolsButton_Popup);
      this.toolsExtractButton.Caption = "Extract";
      this.toolsExtractButton.Id = 10;
      this.toolsExtractButton.LinksPersistInfo.AddRange(new LinkPersistInfo[3]
      {
        new LinkPersistInfo((BarItem) this.extractResourceFilesButton),
        new LinkPersistInfo((BarItem) this.extractNonResourceFilesButton),
        new LinkPersistInfo((BarItem) this.extractRootDirectoryButton)
      });
      this.toolsExtractButton.Name = "toolsExtractButton";
      this.extractResourceFilesButton.Caption = "Resource Files";
      this.extractResourceFilesButton.Id = 11;
      this.extractResourceFilesButton.Name = "extractResourceFilesButton";
      this.extractResourceFilesButton.ItemClick += new ItemClickEventHandler(this.extractResourceFilesButton_ItemClick);
      this.extractNonResourceFilesButton.Caption = "Non-Resource Files";
      this.extractNonResourceFilesButton.Id = 12;
      this.extractNonResourceFilesButton.Name = "extractNonResourceFilesButton";
      this.extractNonResourceFilesButton.ItemClick += new ItemClickEventHandler(this.extractNonResourceFilesButton_ItemClick);
      this.extractRootDirectoryButton.Caption = "Root Directory";
      this.extractRootDirectoryButton.Id = 13;
      this.extractRootDirectoryButton.Name = "extractRootDirectoryButton";
      this.extractRootDirectoryButton.ItemClick += new ItemClickEventHandler(this.extractRootDirectoryButton_ItemClick);
      this.unpackResourceButton.Caption = "Unpack Resource";
      this.unpackResourceButton.Id = 14;
      this.unpackResourceButton.Name = "unpackResourceButton";
      this.unpackResourceButton.ItemClick += new ItemClickEventHandler(this.unpackResourceButton_ItemClick);
      this.barSubItem5.Caption = "Commands";
      this.barSubItem5.Id = 16;
      this.barSubItem5.Name = "barSubItem5";
      this.barSubItem6.Caption = "Help";
      this.barSubItem6.Id = 18;
      this.barSubItem6.LinksPersistInfo.AddRange(new LinkPersistInfo[1]
      {
        new LinkPersistInfo((BarItem) this.aboutButton)
      });
      this.barSubItem6.Name = "barSubItem6";
      this.aboutButton.Caption = "About";
      this.aboutButton.Id = 20;
      this.aboutButton.Name = "aboutButton";
      this.aboutButton.ItemClick += new ItemClickEventHandler(this.aboutButton_ItemClick);
      this.changePlatformButton.Caption = "Change Platform";
      this.changePlatformButton.Id = 19;
      this.changePlatformButton.Name = "changePlatformButton";
      this.changePlatformButton.ItemClick += new ItemClickEventHandler(this.changePlatformButton_ItemClick);
      this.statusStrip.BarName = "Status bar";
      this.statusStrip.CanDockStyle = BarCanDockStyle.Bottom;
      this.statusStrip.DockCol = 0;
      this.statusStrip.DockRow = 0;
      this.statusStrip.DockStyle = BarDockStyle.Bottom;
      this.statusStrip.LinksPersistInfo.AddRange(new LinkPersistInfo[4]
      {
        new LinkPersistInfo((BarItem) this.fileCountStatusLabel),
        new LinkPersistInfo((BarItem) this.fileNameStatusLabe),
        new LinkPersistInfo((BarItem) this.fileSavedStatus),
        new LinkPersistInfo((BarItem) this.entryCountLabel)
      });
      this.statusStrip.OptionsBar.AllowQuickCustomization = false;
      this.statusStrip.OptionsBar.DrawDragBorder = false;
      this.statusStrip.OptionsBar.UseWholeRow = true;
      this.statusStrip.Text = "Status bar";
      this.fileCountStatusLabel.Id = 24;
      this.fileCountStatusLabel.Name = "fileCountStatusLabel";
      this.fileCountStatusLabel.TextAlignment = StringAlignment.Near;
      this.fileNameStatusLabe.Alignment = BarItemLinkAlignment.Right;
      this.fileNameStatusLabe.Id = 25;
      this.fileNameStatusLabe.Name = "fileNameStatusLabe";
      this.fileNameStatusLabe.TextAlignment = StringAlignment.Near;
      this.fileSavedStatus.Id = 26;
      this.fileSavedStatus.Name = "fileSavedStatus";
      this.fileSavedStatus.TextAlignment = StringAlignment.Near;
      this.fileSavedStatus.Visibility = BarItemVisibility.Never;
      this.entryCountLabel.Id = 27;
      this.entryCountLabel.Name = "entryCountLabel";
      this.entryCountLabel.TextAlignment = StringAlignment.Near;
      this.barAndDockingController.LookAndFeel.SkinName = "Sharp";
      this.barAndDockingController.LookAndFeel.UseDefaultLookAndFeel = false;
      this.barAndDockingController.PropertiesBar.AllowLinkLighting = false;
      this.barAndDockingController.PropertiesBar.DefaultGlyphSize = new Size(16, 16);
      this.barAndDockingController.PropertiesBar.DefaultLargeGlyphSize = new Size(32, 32);
      this.barDockControlTop.CausesValidation = false;
      this.barDockControlTop.Dock = DockStyle.Top;
      this.barDockControlTop.Location = new Point(0, 0);
      this.barDockControlTop.Manager = this.mainBarManager;
      this.barDockControlTop.Size = new Size(704, 24);
      this.barDockControlBottom.CausesValidation = false;
      this.barDockControlBottom.Dock = DockStyle.Bottom;
      this.barDockControlBottom.Location = new Point(0, 510);
      this.barDockControlBottom.Manager = this.mainBarManager;
      this.barDockControlBottom.Size = new Size(704, 28);
      this.barDockControlLeft.CausesValidation = false;
      this.barDockControlLeft.Dock = DockStyle.Left;
      this.barDockControlLeft.Location = new Point(0, 24);
      this.barDockControlLeft.Manager = this.mainBarManager;
      this.barDockControlLeft.Size = new Size(0, 486);
      this.barDockControlRight.CausesValidation = false;
      this.barDockControlRight.Dock = DockStyle.Right;
      this.barDockControlRight.Location = new Point(704, 24);
      this.barDockControlRight.Manager = this.mainBarManager;
      this.barDockControlRight.Size = new Size(0, 486);
      this.barButtonItem1.Caption = "File";
      this.barButtonItem1.Id = 0;
      this.barButtonItem1.Name = "barButtonItem1";
      this.barStaticItem1.ContentHorizontalAlignment = BarItemContentAlignment.Near;
      this.barStaticItem1.Id = 7;
      this.barStaticItem1.Name = "barStaticItem1";
      this.barStaticItem1.TextAlignment = StringAlignment.Near;
      this.barButtonItem11.Caption = "barButtonItem11";
      this.barButtonItem11.Id = 15;
      this.barButtonItem11.Name = "barButtonItem11";
      this.barButtonItem12.Caption = "barButtonItem12";
      this.barButtonItem12.Id = 17;
      this.barButtonItem12.Name = "barButtonItem12";
      this.barButtonItem2.Caption = "barButtonItem2";
      this.barButtonItem2.Id = 21;
      this.barButtonItem2.Name = "barButtonItem2";
      this.barSubItem1.Caption = "barSubItem1";
      this.barSubItem1.Id = 22;
      this.barSubItem1.Name = "barSubItem1";
      this.barStaticItem2.Id = 23;
      this.barStaticItem2.Name = "barStaticItem2";
      this.barStaticItem2.TextAlignment = StringAlignment.Near;
      this.skinBarSubItem1.Caption = "skinBarSubItem1";
      this.skinBarSubItem1.Id = 28;
      this.skinBarSubItem1.Name = "skinBarSubItem1";
      this.bar1.BarName = "Custom 4";
      this.bar1.DockCol = 0;
      this.bar1.DockRow = 1;
      this.bar1.DockStyle = BarDockStyle.Top;
      this.bar1.Text = "Custom 4";
      this.directoryCrumb.Location = new Point(0, 30);
      this.directoryCrumb.MenuManager = (IDXMenuManager) this.mainBarManager;
      this.directoryCrumb.Name = "directoryCrumb";
      this.directoryCrumb.Properties.AllowDropDownWhenReadOnly = DefaultBoolean.False;
      this.directoryCrumb.Properties.AllowFocused = false;
      this.directoryCrumb.Properties.Appearance.BackColor = Color.Gainsboro;
      this.directoryCrumb.Properties.Appearance.Options.UseBackColor = true;
      this.directoryCrumb.Properties.Buttons.AddRange(new EditorButton[1]
      {
        new EditorButton(ButtonPredefines.Combo)
      });
      this.directoryCrumb.Properties.PathSeparator = "/";
      this.directoryCrumb.Properties.ReadOnly = true;
      this.directoryCrumb.Size = new Size(704, 22);
      this.directoryCrumb.TabIndex = 7;
      this.directoryCrumb.PathChanged += new BreadCrumbPathChangedEventHandler(this.directoryCrumb_PathChanged);
      this.viewFileTypeButton.Name = "viewFileTypeButton";
      this.viewFileTypeButton.Size = new Size(208, 22);
      this.viewFileTypeButton.Text = "View [FILETYPE]";
      this.viewFileTypeButton.Click += new EventHandler(this.viewFileTypeButton_Click);
      this.barSubItem2.Caption = "Viewers";
      this.barSubItem2.Id = 29;
      this.barSubItem2.LinksPersistInfo.AddRange(new LinkPersistInfo[1]
      {
        new LinkPersistInfo((BarItem) this.stringTableViewerButton)
      });
      this.barSubItem2.Name = "barSubItem2";
      this.stringTableViewerButton.Caption = "StringTable Viewer";
      this.stringTableViewerButton.Id = 30;
      this.stringTableViewerButton.Name = "stringTableViewerButton";
      this.stringTableViewerButton.ItemClick += new ItemClickEventHandler(this.stringTableViewerButton_ItemClick);
      this.AllowDrop = true;
      this.Appearance.Options.UseFont = true;
      this.AutoScaleDimensions = new SizeF(11f, 23f);
      this.AutoScaleMode = AutoScaleMode.Font;
      this.ClientSize = new Size(704, 538);
      this.Controls.Add((Control) this.directoryCrumb);
      this.Controls.Add((Control) this.mainPanel);
      this.Controls.Add((Control) this.barDockControlLeft);
      this.Controls.Add((Control) this.barDockControlRight);
      this.Controls.Add((Control) this.barDockControlBottom);
      this.Controls.Add((Control) this.barDockControlTop);
      this.Font = new Font("Arial", 15f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.FormBorderEffect = FormBorderEffect.Shadow;
      this.Icon = (Icon) componentResourceManager.GetObject("$this.Icon");
      this.KeyPreview = true;
      this.LookAndFeel.SkinName = "Sharp";
      this.LookAndFeel.UseDefaultLookAndFeel = false;
      this.Margin = new Padding(6);
      this.MinimumSize = new Size(600, 409);
      this.Name = nameof (Main);
      this.StartPosition = FormStartPosition.CenterScreen;
      this.Text = "AreDeAre xPlorer 2 ";
      this.DragDrop += new DragEventHandler(this.Main_DragDrop);
      this.DragEnter += new DragEventHandler(this.Main_DragEnter);
      this.mainPanel.ResumeLayout(false);
      ((ISupportInitialize) this.rpfViewer).EndInit();
      this.fileOptions.ResumeLayout(false);
      this.mainBarManager.EndInit();
      this.barAndDockingController.EndInit();
      this.directoryCrumb.Properties.EndInit();
      this.ResumeLayout(false);
      this.PerformLayout();
    }
  }
}
