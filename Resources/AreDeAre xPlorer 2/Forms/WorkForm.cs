using ComponentOwl.BetterListView;
using Pik.IO;
using RAGE;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace AreDeAre_xPlorer_2.Forms
{
  public class WorkForm : Form
  {
    private Stream openRPFStream;
    private Stream saveRPFStream;
    private Stream saveRPFStreamCopyTo;
    private RPF6 rpfToSave;
    private RPF6 rpfToExportFilesFrom;
    private RPF6 rpfToLoadDirFrom;
    private bool ExportResources;
    private bool UnpackResources;
    private string ExportFilesLocation;
    private string locationToExportTo;
    private RPF6.RPF6TOC.TOCSuperEntry directoryToExport;
    private RPF6.RPF6TOC.TOCSuperEntry directoryToLoad;
    public RPF6 OpenRPFReturn;
    public Exception OpenRPFException;
    public Exception SaveRPFException;
    public Exception ExportFilesException;
    public Exception LoadDirectoryException;
    public List<BetterListViewItem> ItemsToAddToListView;
    public bool Done;
    private IContainer components = (IContainer) null;
    private ProgressBar loadingProgressBar;
    private Label workingTextLabel;

    private void WorkForm_Load(object sender, EventArgs e)
    {
    }

    public WorkForm() => this.InitializeComponent();

    public WorkForm(Stream openRPFStream, string text = "Loading...")
    {
      this.InitializeComponent();
      this.workingTextLabel.Text = text;
      this.openRPFStream = openRPFStream;
      this.DoOpenRPFWork();
    }

    public WorkForm(Stream saveRPFStream, RPF6 rpfToSave, string text = "Saving...", Stream copyTo = null)
    {
      this.InitializeComponent();
      this.workingTextLabel.Text = text;
      this.saveRPFStream = saveRPFStream;
      this.rpfToSave = rpfToSave;
      this.saveRPFStreamCopyTo = copyTo;
      this.DoSaveRPFWork();
    }

    public WorkForm(RPF6 currentRPF, RPF6.RPF6TOC.TOCSuperEntry dir, string outLoc, string text = "Exporting...")
    {
      this.InitializeComponent();
      this.rpfToExportFilesFrom = currentRPF;
      this.directoryToExport = dir;
      this.locationToExportTo = outLoc;
      this.DoExportDirectoryWork();
    }

    public WorkForm(
      RPF6 currentRPF,
      string location,
      bool resources,
      bool unpackResources,
      string text = "Exporting...")
    {
      this.InitializeComponent();
      this.ExportFilesLocation = location;
      this.ExportResources = resources;
      this.UnpackResources = unpackResources;
      this.rpfToExportFilesFrom = currentRPF;
      this.workingTextLabel.Text = text;
      this.DoExportFilesWork();
    }

    public WorkForm(RPF6 currentRPF, RPF6.RPF6TOC.TOCSuperEntry dirToLoad)
    {
      this.InitializeComponent();
      this.rpfToLoadDirFrom = currentRPF;
      this.directoryToLoad = dirToLoad;
      this.DoLoadDirectoryWork();
    }

    private async void DoSaveRPFWork()
    {
      try
      {
        await Task.Factory.StartNew((Action) (() =>
        {
          this.rpfToSave.Write(this.saveRPFStream, AppGlobals.Settings.WriteFilesInOffsetOrder);
          if (this.saveRPFStreamCopyTo == null)
            return;
          this.saveRPFStreamCopyTo.Position = 0L;
          this.saveRPFStreamCopyTo.SetLength(0L);
          this.saveRPFStream.Position = 0L;
          this.saveRPFStream.CopyTo(this.saveRPFStreamCopyTo);
        }));
        this.Done = true;
        this.Hide();
      }
      catch (Exception ex)
      {
        this.SaveRPFException = ex;
        this.Hide();
      }
    }

    private async void DoOpenRPFWork()
    {
      try
      {
        await Task.Factory.StartNew((Action) (() =>
        {
          this.OpenRPFReturn = RPF6.RPF6Header.HasIdentifier(new PikIO(this.openRPFStream, PikIO.Endianess.Big)) ? new RPF6(this.openRPFStream) : throw new Exception("RPF File does not have valid header magic");
          this.OpenRPFException = (Exception) null;
        }));
        this.Done = true;
        this.Hide();
      }
      catch (Exception ex)
      {
        this.OpenRPFReturn = (RPF6) null;
        this.OpenRPFException = ex;
        this.Hide();
      }
    }

    private async void DoExportFilesWork()
    {
      try
      {
        await Task.Factory.StartNew((Action) (() =>
        {
          RPF6.RPF6TOC.TOCSuperEntry superEntry1 = this.rpfToExportFilesFrom.TOC.SuperEntries[0];
          foreach (RPF6.RPF6TOC.TOCSuperEntry superEntry2 in this.rpfToExportFilesFrom.TOC.SuperEntries)
          {
            if (!superEntry2.IsDir && superEntry2.Entry.AsFile.FlagInfo.IsResource == this.ExportResources)
            {
              if (superEntry2.Entry.AsFile.FlagInfo.IsResource && this.UnpackResources)
              {
                MemoryStream memoryStream = new MemoryStream();
                this.rpfToExportFilesFrom.TOC.ExtractFile(superEntry2, (Stream) memoryStream);
                Console.WriteLine(string.Format("Exporting Resource: {0}", (object) superEntry2.Entry.GetPath()));
                if (ResourceUtils.ResourceInfo.IsResourceStream((Stream) memoryStream))
                {
                  byte[] dataFromStream = ResourceUtils.ResourceInfo.GetDataFromStream((Stream) memoryStream);
                  string path = string.Format("{0}{1}{2}", (object) this.ExportFilesLocation, (object) Path.DirectorySeparatorChar, (object) superEntry2.Entry.GetPathTill(superEntry1.Entry.AsDirectory, new string(new char[1]
                  {
                    Path.DirectorySeparatorChar
                  })));
                  if (!Directory.Exists(Path.GetDirectoryName(path)))
                    Directory.CreateDirectory(Path.GetDirectoryName(path));
                  Stream stream = (Stream) File.Create(path);
                  stream.Write(dataFromStream, 0, dataFromStream.Length);
                  stream.Flush();
                  stream.Close();
                }
                else
                {
                  int num = (int) MessageBox.Show(string.Format("File \"{0}\" was not a valid resource\r\n\r\nContinuing extraction..", (object) superEntry2.Entry.Name), "Invalid Resource", MessageBoxButtons.OK, MessageBoxIcon.Hand);
                }
              }
              else
              {
                string path = string.Format("{0}{1}{2}", (object) this.ExportFilesLocation, (object) Path.DirectorySeparatorChar, (object) superEntry2.Entry.GetPathTill(superEntry1.Entry.AsDirectory, new string(new char[1]
                {
                  Path.DirectorySeparatorChar
                })));
                if (!Directory.Exists(Path.GetDirectoryName(path)))
                  Directory.CreateDirectory(Path.GetDirectoryName(path));
                Stream xOut = (Stream) File.Create(path);
                this.rpfToExportFilesFrom.TOC.ExtractFile(superEntry2, xOut);
                xOut.Flush();
                xOut.Close();
              }
            }
          }
        }));
        this.Done = true;
        this.Hide();
      }
      catch (Exception ex)
      {
        this.ExportFilesException = ex;
        this.Hide();
      }
    }

    private async void DoExportDirectoryWork()
    {
      try
      {
        await Task.Factory.StartNew((Action) (() =>
        {
          Action<RPF6.RPF6TOC.TOCSuperEntry, string> extractItem = (Action<RPF6.RPF6TOC.TOCSuperEntry, string>) null;
          extractItem = (Action<RPF6.RPF6TOC.TOCSuperEntry, string>) ((item, origPath) =>
          {
            string path = string.Format("{0}{1}{2}", (object) origPath, (object) Path.DirectorySeparatorChar, (object) item.Entry.GetPathTill(this.directoryToExport.Entry.Parent, Path.DirectorySeparatorChar.ToString()));
            if (item.IsDir)
            {
              if (!Directory.Exists(path))
                Directory.CreateDirectory(path);
              foreach (RPF6.RPF6TOC.TOCSuperEntry child in item.Children)
                extractItem(child, origPath);
            }
            else
            {
              Stream xOut = (Stream) File.Create(path);
              this.rpfToExportFilesFrom.TOC.ExtractFile(item, xOut);
              xOut.Flush();
              xOut.Close();
            }
          });
          extractItem(this.directoryToExport, this.locationToExportTo);
        }));
        this.Done = true;
        this.Hide();
      }
      catch (Exception ex)
      {
        this.ExportFilesException = ex;
        this.Hide();
      }
    }

    private async void DoLoadDirectoryWork()
    {
      try
      {
        await Task.Factory.StartNew((Action) (() =>
        {
          this.ItemsToAddToListView = new List<BetterListViewItem>();
          if (this.directoryToLoad.SuperParent != null)
            this.ItemsToAddToListView.Add(new BetterListViewItem()
            {
              Text = "...",
              Tag = (object) new object[2]
              {
                (object) this.directoryToLoad.SuperParent,
                (object) true
              }
            });
          foreach (RPF6.RPF6TOC.TOCSuperEntry tocSuperEntry in this.directoryToLoad.AllChildren.OrderBy<RPF6.RPF6TOC.TOCSuperEntry, bool>((Func<RPF6.RPF6TOC.TOCSuperEntry, bool>) (x => !x.IsDir)).ToList<RPF6.RPF6TOC.TOCSuperEntry>())
          {
            BetterListViewItem betterListViewItem = new BetterListViewItem();
            betterListViewItem.Text = tocSuperEntry.Entry.Name;
            betterListViewItem.Tag = (object) tocSuperEntry;
            if (!tocSuperEntry.Write || tocSuperEntry.DoesHaveParentMarkedNotToBeWritten)
              betterListViewItem.BackColor = Color.FromArgb(150, (int) byte.MaxValue, 50, 50);
            else if (tocSuperEntry.CustomDataStream != null)
              betterListViewItem.BackColor = Color.FromArgb((int) byte.MaxValue, 50, (int) byte.MaxValue, 50);
            if (tocSuperEntry.IsDir)
            {
              betterListViewItem.SubItems.Add("Directory");
              betterListViewItem.SubItems.Add(string.Format("{0} Items", (object) tocSuperEntry.Children.Count));
              betterListViewItem.ImageIndex = 0;
            }
            else
            {
              RPF6.RPF6TOC.FileEntry asFile = tocSuperEntry.Entry.AsFile;
              string str = "[";
              if (asFile.FlagInfo.IsCompressed | asFile.FlagInfo.IsResource)
              {
                if (asFile.FlagInfo.IsResource)
                  str += string.Format("Resource {0}", (object) asFile.ResourceType);
                if (!asFile.FlagInfo.IsResource && asFile.FlagInfo.IsCompressed)
                  str += string.Format("{0}Compressed", asFile.FlagInfo.IsResource ? (object) ", " : (object) "");
              }
              else
                str += "None";
              string text = str + "]";
              betterListViewItem.SubItems.Add(text);
              betterListViewItem.SubItems.Add((object) tocSuperEntry.Entry.AsFile.SizeInArchive);
              betterListViewItem.ImageIndex = 1;
            }
            this.ItemsToAddToListView.Add(betterListViewItem);
          }
        }));
        this.Done = true;
        this.Hide();
      }
      catch (Exception ex)
      {
        int num = (int) MessageBox.Show(ex.Message + "\r\n" + ex.StackTrace);
        this.LoadDirectoryException = ex;
        this.Hide();
      }
    }

    protected override void Dispose(bool disposing)
    {
      if (disposing && this.components != null)
        this.components.Dispose();
      base.Dispose(disposing);
    }

    private void InitializeComponent()
    {
      this.loadingProgressBar = new ProgressBar();
      this.workingTextLabel = new Label();
      this.SuspendLayout();
      this.loadingProgressBar.Location = new Point(12, 42);
      this.loadingProgressBar.MarqueeAnimationSpeed = 20;
      this.loadingProgressBar.Name = "loadingProgressBar";
      this.loadingProgressBar.Size = new Size(139, 23);
      this.loadingProgressBar.Style = ProgressBarStyle.Marquee;
      this.loadingProgressBar.TabIndex = 3;
      this.workingTextLabel.AutoSize = true;
      this.workingTextLabel.ForeColor = SystemColors.AppWorkspace;
      this.workingTextLabel.Location = new Point(33, 11);
      this.workingTextLabel.Name = "workingTextLabel";
      this.workingTextLabel.Size = new Size(92, 25);
      this.workingTextLabel.TabIndex = 2;
      this.workingTextLabel.Text = "Loading..";
      this.AutoScaleDimensions = new SizeF(12f, 25f);
      this.AutoScaleMode = AutoScaleMode.Font;
      this.ClientSize = new Size(162, 77);
      this.Controls.Add((Control) this.loadingProgressBar);
      this.Controls.Add((Control) this.workingTextLabel);
      this.Font = new Font("Microsoft Sans Serif", 15f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.FormBorderStyle = FormBorderStyle.None;
      this.Margin = new Padding(6);
      this.Name = nameof (WorkForm);
      this.ShowIcon = false;
      this.ShowInTaskbar = false;
      this.StartPosition = FormStartPosition.CenterParent;
      this.Text = nameof (WorkForm);
      this.Load += new EventHandler(this.WorkForm_Load);
      this.ResumeLayout(false);
      this.PerformLayout();
    }
  }
}
