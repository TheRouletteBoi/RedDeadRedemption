using DevExpress.XtraBars;
using DevExpress.XtraEditors;
using Pik;
using RAGE;
using RAGE.RDR2;
using System;
using System.ComponentModel;
using System.Drawing;
using System.Globalization;
using System.IO;
using System.Media;
using System.Text;
using System.Windows.Forms;

namespace AreDeAre_xPlorer_2.Forms.Viewers
{
  public class Viewer_ST : XtraForm
  {
    private RPF6.RPF6TOC.TOCSuperEntry _selectedFile;
    private _ST Table;
    private RPF6 _rpf;
    private string _currentFileName;
    private IContainer components = (IContainer) null;
    private RichTextBox textView;
    private PanelControl panelControl1;
    private Bar bar2;
    private BarManager barManager1;
    private Bar bar4;
    private Bar bar3;
    private BarSubItem fileButton;
    private BarButtonItem createNewButton;
    private BarButtonItem openButton;
    private BarSubItem saveButton;
    private BarButtonItem saveCurrentEntryButton;
    private BarButtonItem saveNewEntryButton;
    private BarButtonItem saveNewFileButton;
    private BarButtonItem closeButton;
    private BarAndDockingController barAndDockingController1;
    private BarDockControl barDockControlTop;
    private BarDockControl barDockControlBottom;
    private BarDockControl barDockControlLeft;
    private BarDockControl barDockControlRight;
    private BarButtonItem barButtonItem1;

    public Viewer_ST(RPF6.RPF6TOC.TOCSuperEntry file, RPF6 rpf)
    {
      this.InitializeComponent();
      this._selectedFile = file;
      this._rpf = rpf;
      this.InitData();
    }

    public Viewer_ST(RPF6 rpf)
    {
      this._rpf = rpf;
      this.InitData();
    }

    public Viewer_ST() => this.InitData();

    private void InitData()
    {
      if (this._selectedFile == null)
        this.Text = string.Format("New - StringTable Viewer [{0}]", (object) AppGlobals.PlatformString);
      else
        this.Text = string.Format("{0} - StringTableViewer [{1}]", (object) this._selectedFile.Entry.Name, (object) AppGlobals.PlatformString);
      if (this._selectedFile == null)
        return;
      MemoryStream memoryStream = new MemoryStream();
      this._rpf.TOC.ExtractFile(this._selectedFile, (Stream) memoryStream);
      this.Table = new _ST((Stream) memoryStream);
      this.LoadData();
    }

    private void LoadData()
    {
      StringBuilder stringBuilder = new StringBuilder();
      for (int index = 0; index < this.Table.Entries.Count; ++index)
        stringBuilder.AppendLine(string.Format("0x{0} = {1}", (object) this.Table.Entries[index].Key.ToString("X8"), (object) this.Table.Entries[index].StrValue));
      this.textView.Text = stringBuilder.ToString();
    }

    private _ST MakeStringTable()
    {
      _ST st = new _ST();
      st.TableModValue = 101U;
      int num1;
      Action<int, string> action = (Action<int, string>) ((ind, msg) => num1 = (int) MessageBox.Show(string.Format("Error at line {0}\r\n{1}", (object) ind, (object) msg), "Error Parsing", MessageBoxButtons.OK, MessageBoxIcon.Hand));
      int num2 = 1;
      foreach (string line in this.textView.Lines)
      {
        if (!string.IsNullOrEmpty(line) && !string.IsNullOrWhiteSpace(line))
        {
          int length = line.IndexOf('=');
          if (length == -1)
          {
            action(num2, "Expetected '='");
            return (_ST) null;
          }
          string str = line.Substring(0, length);
          string val = line.Substring(length + 1);
          uint result = 0;
          if (str.StartsWith("0x"))
          {
            if (!uint.TryParse(str.Substring(2), NumberStyles.HexNumber, (IFormatProvider) null, out result))
            {
              action(num2, "Invalid Hex Key Identifier.  Could not parse Hex.  A key that begins with '0x' is reserved as raw hex key.");
              return (_ST) null;
            }
          }
          else
            result = DataUtils.GetHash(str);
          st.AddEntry(result, val);
          ++num2;
        }
      }
      return st;
    }

    private void fileButton_Popup(object sender, EventArgs e)
    {
      if (this._rpf == null)
        this.saveNewEntryButton.Enabled = false;
      if (this._selectedFile == null && string.IsNullOrEmpty(this._currentFileName))
      {
        this.saveCurrentEntryButton.Visibility = BarItemVisibility.Never;
        this.saveCurrentEntryButton.Enabled = false;
      }
      else
      {
        this.saveCurrentEntryButton.Visibility = BarItemVisibility.Always;
        this.saveCurrentEntryButton.Enabled = true;
        if (this._selectedFile != null)
          this.saveCurrentEntryButton.Caption = "Current Entry";
        else if (!string.IsNullOrEmpty(this._currentFileName))
          this.saveCurrentEntryButton.Caption = "Current File";
        else
          this.saveCurrentEntryButton.Caption = "UNK_STATUS";
      }
      if (this._rpf == null)
      {
        this.saveNewEntryButton.Visibility = BarItemVisibility.Never;
        this.saveNewEntryButton.Enabled = false;
      }
      this.saveNewEntryButton.Visibility = BarItemVisibility.Always;
      this.saveNewEntryButton.Enabled = true;
      if (!File.Exists(this._currentFileName) && this._selectedFile == null)
      {
        this.closeButton.Visibility = BarItemVisibility.Never;
        this.closeButton.Enabled = false;
      }
      else
      {
        this.closeButton.Visibility = BarItemVisibility.Always;
        this.closeButton.Enabled = true;
      }
    }

    private void saveCurrentEntryButton_ItemClick(object sender, ItemClickEventArgs e)
    {
      _ST st = this.MakeStringTable();
      if (st != null)
      {
        if (this._selectedFile != null || string.IsNullOrEmpty(this._currentFileName))
          return;
        if (File.Exists(this._currentFileName))
        {
          Stream xOut = (Stream) File.Open(this._currentFileName, System.IO.FileMode.Open);
          xOut.SetLength(0L);
          st.Write(xOut);
          xOut.Flush();
          xOut.Close();
          SystemSounds.Asterisk.Play();
        }
        else
        {
          int num = (int) MessageBox.Show(string.Format("Could not save:\r\nThe file \"{0}\" no longer exists.", (object) this._currentFileName), "File No Longer Exists", MessageBoxButtons.OK, MessageBoxIcon.Hand);
        }
      }
      else
      {
        int num1 = (int) MessageBox.Show("There was an error generating the string table for the given information.  Please contact the developer about this.", "Error Generating String Table", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }
    }

    private void saveNewFileButton_ItemClick(object sender, ItemClickEventArgs e)
    {
      _ST st = this.MakeStringTable();
      if (st != null)
      {
        SaveFileDialog saveFileDialog = new SaveFileDialog();
        saveFileDialog.Title = "Save New StringTable..";
        saveFileDialog.Filter = string.Format("StringTable|*.{0}st|All Files|*.*", (object) AppGlobals.PlatformChar);
        if (saveFileDialog.ShowDialog() != DialogResult.OK)
          return;
        Stream xOut = (Stream) File.Create(saveFileDialog.FileName);
        st.Write(xOut);
        xOut.Flush();
        xOut.Close();
        SystemSounds.Asterisk.Play();
      }
      else
      {
        int num = (int) MessageBox.Show("There was an error generating the string table for the given information.  Please contact the developer about this.", "Error Generating String Table", MessageBoxButtons.OK, MessageBoxIcon.Hand);
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
      this.components = (IContainer) new Container();
      this.textView = new RichTextBox();
      this.panelControl1 = new PanelControl();
      this.bar2 = new Bar();
      this.barManager1 = new BarManager(this.components);
      this.barDockControlTop = new BarDockControl();
      this.barDockControlBottom = new BarDockControl();
      this.barDockControlLeft = new BarDockControl();
      this.barDockControlRight = new BarDockControl();
      this.bar4 = new Bar();
      this.barAndDockingController1 = new BarAndDockingController(this.components);
      this.bar3 = new Bar();
      this.barButtonItem1 = new BarButtonItem();
      this.fileButton = new BarSubItem();
      this.openButton = new BarButtonItem();
      this.saveButton = new BarSubItem();
      this.createNewButton = new BarButtonItem();
      this.closeButton = new BarButtonItem();
      this.saveCurrentEntryButton = new BarButtonItem();
      this.saveNewEntryButton = new BarButtonItem();
      this.saveNewFileButton = new BarButtonItem();
      this.panelControl1.BeginInit();
      this.panelControl1.SuspendLayout();
      this.barManager1.BeginInit();
      this.barAndDockingController1.BeginInit();
      this.SuspendLayout();
      this.textView.Dock = DockStyle.Fill;
      this.textView.Font = new Font("Tahoma", 9f);
      this.textView.Location = new Point(2, 2);
      this.textView.Name = "textView";
      this.textView.Size = new Size(551, 397);
      this.textView.TabIndex = 0;
      this.textView.Text = "";
      this.panelControl1.Controls.Add((Control) this.textView);
      this.panelControl1.Dock = DockStyle.Fill;
      this.panelControl1.Location = new Point(0, 24);
      this.panelControl1.Name = "panelControl1";
      this.panelControl1.Size = new Size(555, 401);
      this.panelControl1.TabIndex = 1;
      this.bar2.BarName = "Main menu";
      this.bar2.CanDockStyle = BarCanDockStyle.Top;
      this.bar2.DockCol = 0;
      this.bar2.DockRow = 0;
      this.bar2.DockStyle = BarDockStyle.Top;
      this.bar2.OptionsBar.AllowQuickCustomization = false;
      this.bar2.OptionsBar.UseWholeRow = true;
      this.bar2.Text = "Main menu";
      this.barManager1.Bars.AddRange(new Bar[2]
      {
        this.bar4,
        this.bar3
      });
      this.barManager1.Controller = this.barAndDockingController1;
      this.barManager1.DockControls.Add(this.barDockControlTop);
      this.barManager1.DockControls.Add(this.barDockControlBottom);
      this.barManager1.DockControls.Add(this.barDockControlLeft);
      this.barManager1.DockControls.Add(this.barDockControlRight);
      this.barManager1.Form = (Control) this;
      this.barManager1.Items.AddRange(new BarItem[9]
      {
        (BarItem) this.barButtonItem1,
        (BarItem) this.fileButton,
        (BarItem) this.openButton,
        (BarItem) this.saveButton,
        (BarItem) this.createNewButton,
        (BarItem) this.closeButton,
        (BarItem) this.saveCurrentEntryButton,
        (BarItem) this.saveNewEntryButton,
        (BarItem) this.saveNewFileButton
      });
      this.barManager1.MainMenu = this.bar3;
      this.barManager1.MaxItemId = 9;
      this.barManager1.StatusBar = this.bar4;
      this.barDockControlTop.CausesValidation = false;
      this.barDockControlTop.Dock = DockStyle.Top;
      this.barDockControlTop.Location = new Point(0, 0);
      this.barDockControlTop.Manager = this.barManager1;
      this.barDockControlTop.Size = new Size(555, 24);
      this.barDockControlBottom.CausesValidation = false;
      this.barDockControlBottom.Dock = DockStyle.Bottom;
      this.barDockControlBottom.Location = new Point(0, 425);
      this.barDockControlBottom.Manager = this.barManager1;
      this.barDockControlBottom.Size = new Size(555, 19);
      this.barDockControlLeft.CausesValidation = false;
      this.barDockControlLeft.Dock = DockStyle.Left;
      this.barDockControlLeft.Location = new Point(0, 24);
      this.barDockControlLeft.Manager = this.barManager1;
      this.barDockControlLeft.Size = new Size(0, 401);
      this.barDockControlRight.CausesValidation = false;
      this.barDockControlRight.Dock = DockStyle.Right;
      this.barDockControlRight.Location = new Point(555, 24);
      this.barDockControlRight.Manager = this.barManager1;
      this.barDockControlRight.Size = new Size(0, 401);
      this.bar4.BarName = "Status bar";
      this.bar4.CanDockStyle = BarCanDockStyle.Bottom;
      this.bar4.DockCol = 0;
      this.bar4.DockRow = 0;
      this.bar4.DockStyle = BarDockStyle.Bottom;
      this.bar4.OptionsBar.AllowQuickCustomization = false;
      this.bar4.OptionsBar.DrawDragBorder = false;
      this.bar4.OptionsBar.UseWholeRow = true;
      this.bar4.Text = "Status bar";
      this.barAndDockingController1.LookAndFeel.SkinName = "Sharp";
      this.barAndDockingController1.LookAndFeel.UseDefaultLookAndFeel = false;
      this.barAndDockingController1.PropertiesBar.AllowLinkLighting = false;
      this.barAndDockingController1.PropertiesBar.DefaultGlyphSize = new Size(16, 16);
      this.barAndDockingController1.PropertiesBar.DefaultLargeGlyphSize = new Size(32, 32);
      this.bar3.BarName = "Custom 4";
      this.bar3.DockCol = 0;
      this.bar3.DockRow = 0;
      this.bar3.DockStyle = BarDockStyle.Top;
      this.bar3.LinksPersistInfo.AddRange(new LinkPersistInfo[1]
      {
        new LinkPersistInfo((BarItem) this.fileButton)
      });
      this.bar3.OptionsBar.MultiLine = true;
      this.bar3.OptionsBar.UseWholeRow = true;
      this.bar3.Text = "Custom 4";
      this.barButtonItem1.Caption = "File";
      this.barButtonItem1.Id = 0;
      this.barButtonItem1.Name = "barButtonItem1";
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
      this.openButton.Caption = "Open";
      this.openButton.Id = 2;
      this.openButton.Name = "openButton";
      this.saveButton.Caption = "Save";
      this.saveButton.Id = 3;
      this.saveButton.LinksPersistInfo.AddRange(new LinkPersistInfo[3]
      {
        new LinkPersistInfo((BarItem) this.saveCurrentEntryButton),
        new LinkPersistInfo((BarItem) this.saveNewEntryButton),
        new LinkPersistInfo((BarItem) this.saveNewFileButton)
      });
      this.saveButton.Name = "saveButton";
      this.createNewButton.Caption = "Create New";
      this.createNewButton.Id = 4;
      this.createNewButton.Name = "createNewButton";
      this.closeButton.Caption = "Close";
      this.closeButton.Id = 5;
      this.closeButton.Name = "closeButton";
      this.saveCurrentEntryButton.Caption = "Current Entry";
      this.saveCurrentEntryButton.Id = 6;
      this.saveCurrentEntryButton.Name = "saveCurrentEntryButton";
      this.saveCurrentEntryButton.ItemClick += new ItemClickEventHandler(this.saveCurrentEntryButton_ItemClick);
      this.saveNewEntryButton.Caption = "New Entry";
      this.saveNewEntryButton.Id = 7;
      this.saveNewEntryButton.Name = "saveNewEntryButton";
      this.saveNewFileButton.Caption = "New File";
      this.saveNewFileButton.Id = 8;
      this.saveNewFileButton.Name = "saveNewFileButton";
      this.AutoScaleDimensions = new SizeF(6f, 13f);
      this.AutoScaleMode = AutoScaleMode.Font;
      this.ClientSize = new Size(555, 444);
      this.Controls.Add((Control) this.panelControl1);
      this.Controls.Add((Control) this.barDockControlLeft);
      this.Controls.Add((Control) this.barDockControlRight);
      this.Controls.Add((Control) this.barDockControlBottom);
      this.Controls.Add((Control) this.barDockControlTop);
      this.LookAndFeel.SkinName = "Sharp";
      this.LookAndFeel.UseDefaultLookAndFeel = false;
      this.Name = nameof (Viewer_ST);
      this.ShowIcon = false;
      this.ShowInTaskbar = false;
      this.Text = nameof (Viewer_ST);
      this.panelControl1.EndInit();
      this.panelControl1.ResumeLayout(false);
      this.barManager1.EndInit();
      this.barAndDockingController1.EndInit();
      this.ResumeLayout(false);
      this.PerformLayout();
    }
  }
}
