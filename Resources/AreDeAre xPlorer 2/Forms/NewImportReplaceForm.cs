using Pik;
using RAGE;
using System;
using System.ComponentModel;
using System.Drawing;
using System.Globalization;
using System.IO;
using System.Windows.Forms;

namespace AreDeAre_xPlorer_2.Forms
{
  public class NewImportReplaceForm : Form
  {
    public RPF6.RPF6TOC.TOCSuperEntry TOCResult;
    private Stream ImportFileStream;
    private Stream ReplaceFileStream;
    public NewImportReplaceForm.FileMode Mode;
    private RPF6.RPF6TOC.TOCSuperEntry SelectedFile;
    private RPF6.RPF6TOC.TOCSuperEntry SelectedReplaceFile;
    private string NewImportFileName;
    private string NewReplaceFileName;
    private IContainer components = (IContainer) null;
    private TabControl mainTabControl;
    private TabPage importTab;
    private TabPage replaceTab;
    private Panel panel1;
    private Label label1;
    private Panel fileImportPanel;
    private RadioButton import_Append;
    private RadioButton import_Before;
    private RadioButton import_After;
    private Button importOpenFile;
    private TextBox importFileName;
    private Label label2;
    private Button importFileButton;
    private Panel importFileResourcePanel;
    private TextBox importResourceFlag2;
    private TextBox importResourceFlag1;
    private Label label4;
    private Label label3;
    private LinkLabel importFileResourceInfoLabel;
    private Label importResourceVersionLabel;
    private Label label5;
    private NumericUpDown importResourceType;
    private CheckBox importCompressCheck;
    private CheckBox importResourceCheck;
    private Panel panel2;
    private CheckBox replaceKeepOffsetCheck;
    private CheckBox replaceCompressCheck;
    private CheckBox replaceResourceCheck;
    private Panel replaceFileResourcePanel;
    private TextBox replaceResourceFlag2;
    private TextBox replaceResourceFlag1;
    private Label label6;
    private Label label7;
    private LinkLabel linkLabel1;
    private Label replaceResourceVersionLabel;
    private Label label9;
    private NumericUpDown replaceResourceType;
    private Button replaceButton;
    private Panel panel4;
    private Button replaceFileOpen;
    private TextBox replacingWithFileName;
    private Label label10;
    private Label label11;
    private Label label12;
    private TextBox replacingFileName;
    private CheckBox replaceReplaceNameCheck;

    public NewImportReplaceForm(
      bool replaceTab,
      RPF6.RPF6TOC.TOCSuperEntry fileParentDir,
      RPF6.RPF6TOC.TOCSuperEntry selectedFile = null,
      RPF6.RPF6TOC.TOCSuperEntry selectedReplaceFile = null,
      string importLoc = null,
      string replaceLoc = null)
    {
      this.InitializeComponent();
      this.SelectedFile = selectedFile;
      this.NewImportFileName = importLoc;
      this.NewReplaceFileName = replaceLoc;
      this.SelectedReplaceFile = selectedReplaceFile;
      if (selectedFile == null || !replaceTab)
        this.Mode = NewImportReplaceForm.FileMode.Import;
      if (this.SelectedFile != null && !this.SelectedFile.IsDir)
        this.Mode |= NewImportReplaceForm.FileMode.Replace;
      this.ConfigureTabs(replaceTab);
    }

    private void LoadImportTabData()
    {
      this.ImportFileStream = (Stream) File.Open(this.NewImportFileName, System.IO.FileMode.Open, FileAccess.Read, FileShare.Read);
      (bool, string, int, int, int) resourceInformation = ResourceUtils.ResourceInfo.GetResourceInformation(this.ImportFileStream);
      this.importResourceCheck.Enabled = true;
      this.importCompressCheck.Enabled = true;
      if (resourceInformation.Item1)
      {
        this.importResourceVersionLabel.Text = string.Format("Resource Version: {0}", (object) resourceInformation.Item2);
        this.importResourceType.Value = (Decimal) resourceInformation.Item3;
        this.importResourceFlag1.Text = resourceInformation.Item4.ToString("X8");
        this.importResourceFlag2.Text = resourceInformation.Item5.ToString("X8");
        this.importResourceCheck.Checked = true;
        this.importCompressCheck.Checked = false;
        this.importFileResourcePanel.Enabled = true;
      }
      else
      {
        this.importFileResourcePanel.Enabled = false;
        this.importResourceCheck.Checked = false;
        this.importCompressCheck.Checked = false;
      }
    }

    private void LoadReplaceTabData()
    {
      this.ReplaceFileStream = (Stream) File.Open(this.NewReplaceFileName, System.IO.FileMode.Open, FileAccess.Read, FileShare.Read);
      (bool, string, int, int, int) resourceInformation = ResourceUtils.ResourceInfo.GetResourceInformation(this.ReplaceFileStream);
      this.replaceResourceCheck.Enabled = true;
      this.replaceCompressCheck.Enabled = true;
      if (resourceInformation.Item1)
      {
        this.replaceResourceVersionLabel.Text = string.Format("Resource Version: {0}", (object) resourceInformation.Item2);
        this.replaceResourceType.Value = (Decimal) resourceInformation.Item3;
        this.replaceResourceFlag1.Text = resourceInformation.Item4.ToString("X8");
        this.replaceResourceFlag2.Text = resourceInformation.Item5.ToString("X8");
        this.replaceResourceCheck.Checked = true;
        this.replaceCompressCheck.Checked = false;
        this.replaceFileResourcePanel.Enabled = true;
      }
      else
      {
        this.replaceFileResourcePanel.Enabled = false;
        this.replaceResourceCheck.Checked = false;
        this.replaceCompressCheck.Checked = false;
      }
    }

    private void LoadImportTab()
    {
      this.import_Append.Enabled = true;
      if (this.SelectedFile != null && !this.SelectedFile.IsDir)
      {
        this.import_Before.Enabled = true;
        this.import_After.Enabled = true;
        this.import_After.Text = string.Format("After {0}", (object) this.SelectedFile.Entry.Name);
        this.import_Before.Text = string.Format("Before {0}", (object) this.SelectedFile.Entry.Name);
      }
      bool flag = false;
      if (this.NewImportFileName != null)
      {
        flag = true;
        this.importFileName.Text = this.NewImportFileName;
      }
      if (!flag)
        return;
      this.LoadImportTabData();
    }

    private void LoadReplaceTab()
    {
      bool flag = false;
      this.replacingFileName.Text = this.SelectedReplaceFile == null ? this.SelectedFile.Entry.Name : this.SelectedReplaceFile.Entry.Name;
      if (this.NewReplaceFileName != null)
      {
        flag = true;
        this.replacingWithFileName.Text = this.NewReplaceFileName;
      }
      if (!flag)
        return;
      this.LoadReplaceTabData();
    }

    private void ConfigureTabs(bool repTab)
    {
      if (repTab)
        this.mainTabControl.SelectedTab = this.replaceTab;
      if (this.Mode == NewImportReplaceForm.FileMode.Import)
        this.mainTabControl.TabPages.Remove(this.replaceTab);
      this.LoadImportTab();
      if ((this.Mode & NewImportReplaceForm.FileMode.Replace) != NewImportReplaceForm.FileMode.Replace)
        return;
      this.LoadReplaceTab();
    }

    private void importFileButton_Click(object sender, EventArgs e)
    {
      RPF6.RPF6TOC.TOCSuperEntry tocSuperEntry = new RPF6.RPF6TOC.TOCSuperEntry();
      tocSuperEntry.CustomDataStream = this.ImportFileStream;
      RPF6.RPF6TOC.FileEntry fileEntry = new RPF6.RPF6TOC.FileEntry()
      {
        FlagInfo = new ResourceUtils.FlagInfo()
      };
      fileEntry.FlagInfo.Flag1 = DataUtils.IntFromUInt(string.IsNullOrEmpty(this.importResourceFlag1.Text) ? 0U : uint.Parse(this.importResourceFlag1.Text, NumberStyles.HexNumber));
      fileEntry.FlagInfo.Flag2 = DataUtils.IntFromUInt(string.IsNullOrEmpty(this.importResourceFlag2.Text) ? 0U : uint.Parse(this.importResourceFlag2.Text, NumberStyles.HexNumber));
      if (this.importResourceCheck.Checked)
      {
        fileEntry.FlagInfo.IsResource = true;
        fileEntry.ResourceType = (byte) this.importResourceType.Value;
      }
      else if (this.importCompressCheck.Checked)
      {
        fileEntry.FlagInfo.IsCompressed = true;
        fileEntry.FlagInfo.SetTotalSize((int) this.ImportFileStream.Length, 0);
      }
      else
        fileEntry.FlagInfo.SetTotalSize((int) this.ImportFileStream.Length, 0);
      fileEntry.SizeInArchive = (int) this.ImportFileStream.Length;
      RPF6FileNameHandler.AddName(Path.GetFileName(this.importFileName.Text));
      RPF6FileNameHandler.SaveNames();
      tocSuperEntry.Entry = (RPF6.RPF6TOC.TOCEntry) fileEntry;
      fileEntry.NameOffset = DataUtils.GetHash(Path.GetFileName(this.importFileName.Text));
      if (this.SelectedFile != null)
      {
        switch (this.import_Before.Checked ? NewImportReplaceForm.ImportOrder.Before : (this.import_After.Checked ? NewImportReplaceForm.ImportOrder.After : NewImportReplaceForm.ImportOrder.Append))
        {
          case NewImportReplaceForm.ImportOrder.Before:
            this.SelectedFile.WriteBefore_Children.Add(tocSuperEntry);
            break;
          case NewImportReplaceForm.ImportOrder.After:
            this.SelectedFile.WriteAfterChildren.Add(tocSuperEntry);
            break;
        }
      }
      this.TOCResult = tocSuperEntry;
      this.Mode = NewImportReplaceForm.FileMode.Import;
      this.Close();
    }

    private void replaceButton_Click(object sender, EventArgs e)
    {
      RPF6.RPF6TOC.TOCSuperEntry tocSuperEntry1 = new RPF6.RPF6TOC.TOCSuperEntry();
      RPF6.RPF6TOC.TOCSuperEntry tocSuperEntry2 = this.SelectedReplaceFile == null ? this.SelectedFile : this.SelectedReplaceFile;
      tocSuperEntry1.CustomDataStream = this.ReplaceFileStream;
      tocSuperEntry1.OldEntry = tocSuperEntry2.Entry;
      tocSuperEntry1.ReadBackFromRPF = false;
      RPF6.RPF6TOC.FileEntry fileEntry = new RPF6.RPF6TOC.FileEntry()
      {
        FlagInfo = new ResourceUtils.FlagInfo()
      };
      fileEntry.FlagInfo.Flag1 = DataUtils.IntFromUInt(string.IsNullOrEmpty(this.replaceResourceFlag1.Text) ? 0U : uint.Parse(this.replaceResourceFlag1.Text, NumberStyles.HexNumber));
      fileEntry.FlagInfo.Flag2 = DataUtils.IntFromUInt(string.IsNullOrEmpty(this.replaceResourceFlag2.Text) ? 0U : uint.Parse(this.replaceResourceFlag2.Text, NumberStyles.HexNumber));
      if (this.replaceResourceCheck.Checked)
      {
        fileEntry.FlagInfo.IsResource = true;
        fileEntry.ResourceType = (byte) this.replaceResourceType.Value;
      }
      else if (this.replaceCompressCheck.Checked)
      {
        fileEntry.FlagInfo.IsCompressed = true;
        fileEntry.FlagInfo.SetTotalSize((int) this.ReplaceFileStream.Length, 0);
      }
      else
      {
        fileEntry.FlagInfo.IsCompressed = false;
        fileEntry.FlagInfo.SetTotalSize((int) this.ReplaceFileStream.Length, 0);
      }
      fileEntry.SizeInArchive = (int) this.ReplaceFileStream.Length;
      if (this.replaceReplaceNameCheck.Checked)
        fileEntry.NameOffset = DataUtils.GetHash(this.replacingWithFileName.Text);
      else
        fileEntry.NameOffset = tocSuperEntry2.Entry.NameOffset;
      RPF6FileNameHandler.AddName(Path.GetFileName(this.replacingWithFileName.Text));
      tocSuperEntry1.Entry = (RPF6.RPF6TOC.TOCEntry) fileEntry;
      tocSuperEntry1.Entry.AsFile.KeepOffset = this.replaceKeepOffsetCheck.Checked ? new long?(tocSuperEntry1.OldEntry.AsFile.GetOffset()) : new long?();
      RPF6FileNameHandler.SaveNames();
      this.TOCResult = tocSuperEntry1;
      this.Mode = NewImportReplaceForm.FileMode.Replace;
      this.Close();
    }

    private void importOpenFile_Click(object sender, EventArgs e)
    {
      OpenFileDialog openFileDialog = new OpenFileDialog();
      openFileDialog.Title = "Import File...";
      openFileDialog.Filter = "|*.*";
      openFileDialog.Multiselect = false;
      if (openFileDialog.ShowDialog() != DialogResult.OK)
        return;
      if (this.ImportFileStream != null)
        this.ImportFileStream.Close();
      this.ImportFileStream = (Stream) null;
      this.NewImportFileName = openFileDialog.FileName;
      this.LoadImportTab();
    }

    private void replaceFileOpen_Click(object sender, EventArgs e)
    {
      OpenFileDialog openFileDialog = new OpenFileDialog();
      openFileDialog.Title = string.Format("Replace {0} with...", (object) this.SelectedFile.Entry.Name);
      openFileDialog.Filter = "|*.*";
      openFileDialog.Multiselect = false;
      if (openFileDialog.ShowDialog() != DialogResult.OK)
        return;
      if (this.ReplaceFileStream != null)
        this.ReplaceFileStream.Close();
      this.ReplaceFileStream = (Stream) null;
      this.NewReplaceFileName = openFileDialog.FileName;
      this.LoadReplaceTab();
    }

    private void FlagBoxes_TextChanged(object sender, EventArgs e)
    {
      TextBox textBox = sender as TextBox;
      string text = textBox.Text;
      int result = 0;
      if (int.TryParse(text, NumberStyles.HexNumber, (IFormatProvider) NumberFormatInfo.CurrentInfo, out result) || !(text != string.Empty))
        return;
      textBox.Text = text.Remove(text.Length - 1, 1);
      textBox.SelectionStart = textBox.Text.Length;
    }

    private void fileResourceCheck_CheckedChanged(object sender, EventArgs e) => this.importFileResourcePanel.Enabled = this.importResourceCheck.Checked;

    private void replaceResourceCheck_CheckedChanged(object sender, EventArgs e) => this.replaceFileResourcePanel.Enabled = this.replaceResourceCheck.Checked;

    protected override void Dispose(bool disposing)
    {
      if (disposing && this.components != null)
        this.components.Dispose();
      base.Dispose(disposing);
    }

    private void InitializeComponent()
    {
      this.mainTabControl = new TabControl();
      this.importTab = new TabPage();
      this.panel1 = new Panel();
      this.importCompressCheck = new CheckBox();
      this.importResourceCheck = new CheckBox();
      this.importFileResourcePanel = new Panel();
      this.importResourceFlag2 = new TextBox();
      this.importResourceFlag1 = new TextBox();
      this.label4 = new Label();
      this.label3 = new Label();
      this.importFileResourceInfoLabel = new LinkLabel();
      this.importResourceVersionLabel = new Label();
      this.label5 = new Label();
      this.importResourceType = new NumericUpDown();
      this.importFileButton = new Button();
      this.fileImportPanel = new Panel();
      this.import_Append = new RadioButton();
      this.import_Before = new RadioButton();
      this.import_After = new RadioButton();
      this.importOpenFile = new Button();
      this.importFileName = new TextBox();
      this.label2 = new Label();
      this.label1 = new Label();
      this.replaceTab = new TabPage();
      this.panel2 = new Panel();
      this.replaceKeepOffsetCheck = new CheckBox();
      this.replaceCompressCheck = new CheckBox();
      this.replaceResourceCheck = new CheckBox();
      this.replaceFileResourcePanel = new Panel();
      this.replaceResourceFlag2 = new TextBox();
      this.replaceResourceFlag1 = new TextBox();
      this.label6 = new Label();
      this.label7 = new Label();
      this.linkLabel1 = new LinkLabel();
      this.replaceResourceVersionLabel = new Label();
      this.label9 = new Label();
      this.replaceResourceType = new NumericUpDown();
      this.replaceButton = new Button();
      this.panel4 = new Panel();
      this.replaceReplaceNameCheck = new CheckBox();
      this.label12 = new Label();
      this.replacingFileName = new TextBox();
      this.replaceFileOpen = new Button();
      this.replacingWithFileName = new TextBox();
      this.label10 = new Label();
      this.label11 = new Label();
      this.mainTabControl.SuspendLayout();
      this.importTab.SuspendLayout();
      this.panel1.SuspendLayout();
      this.importFileResourcePanel.SuspendLayout();
      this.importResourceType.BeginInit();
      this.fileImportPanel.SuspendLayout();
      this.replaceTab.SuspendLayout();
      this.panel2.SuspendLayout();
      this.replaceFileResourcePanel.SuspendLayout();
      this.replaceResourceType.BeginInit();
      this.panel4.SuspendLayout();
      this.SuspendLayout();
      this.mainTabControl.Controls.Add((Control) this.importTab);
      this.mainTabControl.Controls.Add((Control) this.replaceTab);
      this.mainTabControl.Dock = DockStyle.Fill;
      this.mainTabControl.Font = new Font("Segoe UI", 12f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.mainTabControl.Location = new Point(0, 0);
      this.mainTabControl.Name = "mainTabControl";
      this.mainTabControl.SelectedIndex = 0;
      this.mainTabControl.Size = new Size(430, 454);
      this.mainTabControl.TabIndex = 0;
      this.importTab.Controls.Add((Control) this.panel1);
      this.importTab.Location = new Point(4, 30);
      this.importTab.Name = "importTab";
      this.importTab.Padding = new Padding(3);
      this.importTab.Size = new Size(422, 420);
      this.importTab.TabIndex = 0;
      this.importTab.Text = "Import";
      this.importTab.UseVisualStyleBackColor = true;
      this.panel1.BorderStyle = BorderStyle.FixedSingle;
      this.panel1.Controls.Add((Control) this.importCompressCheck);
      this.panel1.Controls.Add((Control) this.importResourceCheck);
      this.panel1.Controls.Add((Control) this.importFileResourcePanel);
      this.panel1.Controls.Add((Control) this.importFileButton);
      this.panel1.Controls.Add((Control) this.fileImportPanel);
      this.panel1.Controls.Add((Control) this.label1);
      this.panel1.Location = new Point(8, 6);
      this.panel1.Name = "panel1";
      this.panel1.Size = new Size(404, 410);
      this.panel1.TabIndex = 1;
      this.importCompressCheck.AutoSize = true;
      this.importCompressCheck.Enabled = false;
      this.importCompressCheck.Location = new Point(118, 185);
      this.importCompressCheck.Name = "importCompressCheck";
      this.importCompressCheck.Size = new Size(99, 25);
      this.importCompressCheck.TabIndex = 10;
      this.importCompressCheck.Text = "Compress";
      this.importCompressCheck.UseVisualStyleBackColor = true;
      this.importResourceCheck.AutoSize = true;
      this.importResourceCheck.Enabled = false;
      this.importResourceCheck.Location = new Point(18, 185);
      this.importResourceCheck.Name = "importResourceCheck";
      this.importResourceCheck.Size = new Size(93, 25);
      this.importResourceCheck.TabIndex = 9;
      this.importResourceCheck.Text = "Resource";
      this.importResourceCheck.UseVisualStyleBackColor = true;
      this.importResourceCheck.CheckedChanged += new EventHandler(this.fileResourceCheck_CheckedChanged);
      this.importFileResourcePanel.BorderStyle = BorderStyle.FixedSingle;
      this.importFileResourcePanel.Controls.Add((Control) this.importResourceFlag2);
      this.importFileResourcePanel.Controls.Add((Control) this.importResourceFlag1);
      this.importFileResourcePanel.Controls.Add((Control) this.label4);
      this.importFileResourcePanel.Controls.Add((Control) this.label3);
      this.importFileResourcePanel.Controls.Add((Control) this.importFileResourceInfoLabel);
      this.importFileResourcePanel.Controls.Add((Control) this.importResourceVersionLabel);
      this.importFileResourcePanel.Controls.Add((Control) this.label5);
      this.importFileResourcePanel.Controls.Add((Control) this.importResourceType);
      this.importFileResourcePanel.Enabled = false;
      this.importFileResourcePanel.Location = new Point(14, 216);
      this.importFileResourcePanel.Name = "importFileResourcePanel";
      this.importFileResourcePanel.Size = new Size(373, 145);
      this.importFileResourcePanel.TabIndex = 5;
      this.importResourceFlag2.Location = new Point(132, 93);
      this.importResourceFlag2.MaxLength = 8;
      this.importResourceFlag2.Name = "importResourceFlag2";
      this.importResourceFlag2.Size = new Size(236, 29);
      this.importResourceFlag2.TabIndex = 13;
      this.importResourceFlag2.TextChanged += new EventHandler(this.FlagBoxes_TextChanged);
      this.importResourceFlag1.Location = new Point(132, 63);
      this.importResourceFlag1.MaxLength = 8;
      this.importResourceFlag1.Name = "importResourceFlag1";
      this.importResourceFlag1.Size = new Size(236, 29);
      this.importResourceFlag1.TabIndex = 12;
      this.importResourceFlag1.TextChanged += new EventHandler(this.FlagBoxes_TextChanged);
      this.label4.AutoSize = true;
      this.label4.Location = new Point(7, 94);
      this.label4.Name = "label4";
      this.label4.Size = new Size(119, 21);
      this.label4.TabIndex = 11;
      this.label4.Text = "Resource Flag2:";
      this.label3.AutoSize = true;
      this.label3.Location = new Point(7, 64);
      this.label3.Name = "label3";
      this.label3.Size = new Size(119, 21);
      this.label3.TabIndex = 9;
      this.label3.Text = "Resource Flag1:";
      this.importFileResourceInfoLabel.AutoSize = true;
      this.importFileResourceInfoLabel.Cursor = Cursors.Hand;
      this.importFileResourceInfoLabel.Location = new Point(291, 122);
      this.importFileResourceInfoLabel.Name = "importFileResourceInfoLabel";
      this.importFileResourceInfoLabel.Size = new Size(84, 21);
      this.importFileResourceInfoLabel.TabIndex = 7;
      this.importFileResourceInfoLabel.TabStop = true;
      this.importFileResourceInfoLabel.Text = "Important!";
      this.importResourceVersionLabel.AutoSize = true;
      this.importResourceVersionLabel.Font = new Font("Segoe UI", 14f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.importResourceVersionLabel.Location = new Point(9, 5);
      this.importResourceVersionLabel.Name = "importResourceVersionLabel";
      this.importResourceVersionLabel.Size = new Size(198, 25);
      this.importResourceVersionLabel.TabIndex = 6;
      this.importResourceVersionLabel.Text = "Resource Version: N/A";
      this.label5.AutoSize = true;
      this.label5.Location = new Point(7, 34);
      this.label5.Name = "label5";
      this.label5.Size = new Size(113, 21);
      this.label5.TabIndex = 5;
      this.label5.Text = "Resource Type:";
      this.importResourceType.Location = new Point(132, 33);
      this.importResourceType.Maximum = new Decimal(new int[4]
      {
        (int) byte.MaxValue,
        0,
        0,
        0
      });
      this.importResourceType.Name = "importResourceType";
      this.importResourceType.Size = new Size(236, 29);
      this.importResourceType.TabIndex = 4;
      this.importFileButton.Location = new Point(14, 366);
      this.importFileButton.Name = "importFileButton";
      this.importFileButton.Size = new Size(373, 35);
      this.importFileButton.TabIndex = 4;
      this.importFileButton.Text = "Import";
      this.importFileButton.UseVisualStyleBackColor = true;
      this.importFileButton.Click += new EventHandler(this.importFileButton_Click);
      this.fileImportPanel.BorderStyle = BorderStyle.FixedSingle;
      this.fileImportPanel.Controls.Add((Control) this.import_Append);
      this.fileImportPanel.Controls.Add((Control) this.import_Before);
      this.fileImportPanel.Controls.Add((Control) this.import_After);
      this.fileImportPanel.Controls.Add((Control) this.importOpenFile);
      this.fileImportPanel.Controls.Add((Control) this.importFileName);
      this.fileImportPanel.Controls.Add((Control) this.label2);
      this.fileImportPanel.Location = new Point(14, 40);
      this.fileImportPanel.Name = "fileImportPanel";
      this.fileImportPanel.Size = new Size(373, 140);
      this.fileImportPanel.TabIndex = 2;
      this.import_Append.AutoSize = true;
      this.import_Append.Checked = true;
      this.import_Append.Location = new Point(14, 110);
      this.import_Append.Name = "import_Append";
      this.import_Append.Size = new Size(131, 25);
      this.import_Append.TabIndex = 5;
      this.import_Append.TabStop = true;
      this.import_Append.Text = "Append To End";
      this.import_Append.UseVisualStyleBackColor = true;
      this.import_Before.AutoSize = true;
      this.import_Before.Enabled = false;
      this.import_Before.Location = new Point(14, 87);
      this.import_Before.Name = "import_Before";
      this.import_Before.Size = new Size(115, 25);
      this.import_Before.TabIndex = 4;
      this.import_Before.TabStop = true;
      this.import_Before.Text = "Before [FILE]";
      this.import_Before.UseVisualStyleBackColor = true;
      this.import_After.AutoSize = true;
      this.import_After.Enabled = false;
      this.import_After.Location = new Point(14, 64);
      this.import_After.Name = "import_After";
      this.import_After.Size = new Size(104, 25);
      this.import_After.TabIndex = 3;
      this.import_After.TabStop = true;
      this.import_After.Text = "After [FILE]";
      this.import_After.UseVisualStyleBackColor = true;
      this.importOpenFile.Font = new Font("Segoe UI", 10f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.importOpenFile.Location = new Point(326, 33);
      this.importOpenFile.Name = "importOpenFile";
      this.importOpenFile.Size = new Size(42, 23);
      this.importOpenFile.TabIndex = 2;
      this.importOpenFile.Text = "...";
      this.importOpenFile.UseVisualStyleBackColor = true;
      this.importOpenFile.Click += new EventHandler(this.importOpenFile_Click);
      this.importFileName.Font = new Font("Segoe UI", 10f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.importFileName.Location = new Point(3, 33);
      this.importFileName.Name = "importFileName";
      this.importFileName.ReadOnly = true;
      this.importFileName.Size = new Size(315, 25);
      this.importFileName.TabIndex = 1;
      this.label2.AutoSize = true;
      this.label2.Font = new Font("Segoe UI", 13f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.label2.Location = new Point(9, 5);
      this.label2.Name = "label2";
      this.label2.Size = new Size(98, 25);
      this.label2.TabIndex = 0;
      this.label2.Text = "File Import";
      this.label1.AutoSize = true;
      this.label1.Font = new Font("Segoe UI", 18f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.label1.Location = new Point(8, 5);
      this.label1.Name = "label1";
      this.label1.Size = new Size(86, 32);
      this.label1.TabIndex = 0;
      this.label1.Text = "Import";
      this.replaceTab.Controls.Add((Control) this.panel2);
      this.replaceTab.Location = new Point(4, 30);
      this.replaceTab.Name = "replaceTab";
      this.replaceTab.Padding = new Padding(3);
      this.replaceTab.Size = new Size(422, 420);
      this.replaceTab.TabIndex = 1;
      this.replaceTab.Text = "Replace";
      this.replaceTab.UseVisualStyleBackColor = true;
      this.panel2.BorderStyle = BorderStyle.FixedSingle;
      this.panel2.Controls.Add((Control) this.replaceKeepOffsetCheck);
      this.panel2.Controls.Add((Control) this.replaceCompressCheck);
      this.panel2.Controls.Add((Control) this.replaceResourceCheck);
      this.panel2.Controls.Add((Control) this.replaceFileResourcePanel);
      this.panel2.Controls.Add((Control) this.replaceButton);
      this.panel2.Controls.Add((Control) this.panel4);
      this.panel2.Controls.Add((Control) this.label11);
      this.panel2.Location = new Point(8, 8);
      this.panel2.Name = "panel2";
      this.panel2.Size = new Size(404, 401);
      this.panel2.TabIndex = 2;
      this.replaceKeepOffsetCheck.AutoSize = true;
      this.replaceKeepOffsetCheck.Location = new Point(224, 174);
      this.replaceKeepOffsetCheck.Name = "replaceKeepOffsetCheck";
      this.replaceKeepOffsetCheck.Size = new Size(109, 25);
      this.replaceKeepOffsetCheck.TabIndex = 11;
      this.replaceKeepOffsetCheck.Text = "Keep Offset";
      this.replaceKeepOffsetCheck.UseVisualStyleBackColor = true;
      this.replaceCompressCheck.AutoSize = true;
      this.replaceCompressCheck.Enabled = false;
      this.replaceCompressCheck.Location = new Point(118, 174);
      this.replaceCompressCheck.Name = "replaceCompressCheck";
      this.replaceCompressCheck.Size = new Size(99, 25);
      this.replaceCompressCheck.TabIndex = 10;
      this.replaceCompressCheck.Text = "Compress";
      this.replaceCompressCheck.UseVisualStyleBackColor = true;
      this.replaceResourceCheck.AutoSize = true;
      this.replaceResourceCheck.Enabled = false;
      this.replaceResourceCheck.Location = new Point(18, 174);
      this.replaceResourceCheck.Name = "replaceResourceCheck";
      this.replaceResourceCheck.Size = new Size(93, 25);
      this.replaceResourceCheck.TabIndex = 9;
      this.replaceResourceCheck.Text = "Resource";
      this.replaceResourceCheck.UseVisualStyleBackColor = true;
      this.replaceResourceCheck.CheckedChanged += new EventHandler(this.replaceResourceCheck_CheckedChanged);
      this.replaceFileResourcePanel.BorderStyle = BorderStyle.FixedSingle;
      this.replaceFileResourcePanel.Controls.Add((Control) this.replaceResourceFlag2);
      this.replaceFileResourcePanel.Controls.Add((Control) this.replaceResourceFlag1);
      this.replaceFileResourcePanel.Controls.Add((Control) this.label6);
      this.replaceFileResourcePanel.Controls.Add((Control) this.label7);
      this.replaceFileResourcePanel.Controls.Add((Control) this.linkLabel1);
      this.replaceFileResourcePanel.Controls.Add((Control) this.replaceResourceVersionLabel);
      this.replaceFileResourcePanel.Controls.Add((Control) this.label9);
      this.replaceFileResourcePanel.Controls.Add((Control) this.replaceResourceType);
      this.replaceFileResourcePanel.Enabled = false;
      this.replaceFileResourcePanel.Location = new Point(14, 205);
      this.replaceFileResourcePanel.Name = "replaceFileResourcePanel";
      this.replaceFileResourcePanel.Size = new Size(373, 145);
      this.replaceFileResourcePanel.TabIndex = 5;
      this.replaceResourceFlag2.Location = new Point(132, 93);
      this.replaceResourceFlag2.MaxLength = 8;
      this.replaceResourceFlag2.Name = "replaceResourceFlag2";
      this.replaceResourceFlag2.Size = new Size(236, 29);
      this.replaceResourceFlag2.TabIndex = 13;
      this.replaceResourceFlag2.TextChanged += new EventHandler(this.FlagBoxes_TextChanged);
      this.replaceResourceFlag1.Location = new Point(132, 63);
      this.replaceResourceFlag1.MaxLength = 8;
      this.replaceResourceFlag1.Name = "replaceResourceFlag1";
      this.replaceResourceFlag1.Size = new Size(236, 29);
      this.replaceResourceFlag1.TabIndex = 12;
      this.replaceResourceFlag1.TextChanged += new EventHandler(this.FlagBoxes_TextChanged);
      this.label6.AutoSize = true;
      this.label6.Location = new Point(7, 94);
      this.label6.Name = "label6";
      this.label6.Size = new Size(119, 21);
      this.label6.TabIndex = 11;
      this.label6.Text = "Resource Flag2:";
      this.label7.AutoSize = true;
      this.label7.Location = new Point(7, 64);
      this.label7.Name = "label7";
      this.label7.Size = new Size(119, 21);
      this.label7.TabIndex = 9;
      this.label7.Text = "Resource Flag1:";
      this.linkLabel1.AutoSize = true;
      this.linkLabel1.Cursor = Cursors.Hand;
      this.linkLabel1.Location = new Point(291, 122);
      this.linkLabel1.Name = "linkLabel1";
      this.linkLabel1.Size = new Size(84, 21);
      this.linkLabel1.TabIndex = 7;
      this.linkLabel1.TabStop = true;
      this.linkLabel1.Text = "Important!";
      this.replaceResourceVersionLabel.AutoSize = true;
      this.replaceResourceVersionLabel.Font = new Font("Segoe UI", 14f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.replaceResourceVersionLabel.Location = new Point(9, 5);
      this.replaceResourceVersionLabel.Name = "replaceResourceVersionLabel";
      this.replaceResourceVersionLabel.Size = new Size(198, 25);
      this.replaceResourceVersionLabel.TabIndex = 6;
      this.replaceResourceVersionLabel.Text = "Resource Version: N/A";
      this.label9.AutoSize = true;
      this.label9.Location = new Point(7, 34);
      this.label9.Name = "label9";
      this.label9.Size = new Size(113, 21);
      this.label9.TabIndex = 5;
      this.label9.Text = "Resource Type:";
      this.replaceResourceType.Location = new Point(132, 33);
      this.replaceResourceType.Maximum = new Decimal(new int[4]
      {
        (int) byte.MaxValue,
        0,
        0,
        0
      });
      this.replaceResourceType.Name = "replaceResourceType";
      this.replaceResourceType.Size = new Size(236, 29);
      this.replaceResourceType.TabIndex = 4;
      this.replaceButton.Location = new Point(14, 356);
      this.replaceButton.Name = "replaceButton";
      this.replaceButton.Size = new Size(373, 35);
      this.replaceButton.TabIndex = 4;
      this.replaceButton.Text = "Replace";
      this.replaceButton.UseVisualStyleBackColor = true;
      this.replaceButton.Click += new EventHandler(this.replaceButton_Click);
      this.panel4.BorderStyle = BorderStyle.FixedSingle;
      this.panel4.Controls.Add((Control) this.replaceReplaceNameCheck);
      this.panel4.Controls.Add((Control) this.label12);
      this.panel4.Controls.Add((Control) this.replacingFileName);
      this.panel4.Controls.Add((Control) this.replaceFileOpen);
      this.panel4.Controls.Add((Control) this.replacingWithFileName);
      this.panel4.Controls.Add((Control) this.label10);
      this.panel4.Location = new Point(14, 40);
      this.panel4.Name = "panel4";
      this.panel4.Size = new Size(373, 129);
      this.panel4.TabIndex = 2;
      this.replaceReplaceNameCheck.AutoSize = true;
      this.replaceReplaceNameCheck.Enabled = false;
      this.replaceReplaceNameCheck.Location = new Point(191, 64);
      this.replaceReplaceNameCheck.Name = "replaceReplaceNameCheck";
      this.replaceReplaceNameCheck.Size = new Size(129, 25);
      this.replaceReplaceNameCheck.TabIndex = 11;
      this.replaceReplaceNameCheck.Text = "Replace Name";
      this.replaceReplaceNameCheck.UseVisualStyleBackColor = true;
      this.label12.AutoSize = true;
      this.label12.Font = new Font("Segoe UI", 13f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.label12.Location = new Point(9, 64);
      this.label12.Name = "label12";
      this.label12.Size = new Size(49, 25);
      this.label12.TabIndex = 4;
      this.label12.Text = "With";
      this.replacingFileName.Font = new Font("Segoe UI", 10f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.replacingFileName.Location = new Point(6, 33);
      this.replacingFileName.Name = "replacingFileName";
      this.replacingFileName.ReadOnly = true;
      this.replacingFileName.Size = new Size(314, 25);
      this.replacingFileName.TabIndex = 3;
      this.replaceFileOpen.Font = new Font("Segoe UI", 10f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.replaceFileOpen.Location = new Point(326, 92);
      this.replaceFileOpen.Name = "replaceFileOpen";
      this.replaceFileOpen.Size = new Size(42, 23);
      this.replaceFileOpen.TabIndex = 2;
      this.replaceFileOpen.Text = "...";
      this.replaceFileOpen.UseVisualStyleBackColor = true;
      this.replaceFileOpen.Click += new EventHandler(this.replaceFileOpen_Click);
      this.replacingWithFileName.Font = new Font("Segoe UI", 10f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.replacingWithFileName.Location = new Point(6, 92);
      this.replacingWithFileName.Name = "replacingWithFileName";
      this.replacingWithFileName.ReadOnly = true;
      this.replacingWithFileName.Size = new Size(314, 25);
      this.replacingWithFileName.TabIndex = 1;
      this.label10.AutoSize = true;
      this.label10.Font = new Font("Segoe UI", 13f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.label10.Location = new Point(9, 4);
      this.label10.Name = "label10";
      this.label10.Size = new Size(88, 25);
      this.label10.TabIndex = 0;
      this.label10.Text = "Replacing";
      this.label11.AutoSize = true;
      this.label11.Font = new Font("Segoe UI", 18f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.label11.Location = new Point(6, 3);
      this.label11.Name = "label11";
      this.label11.Size = new Size(97, 32);
      this.label11.TabIndex = 0;
      this.label11.Text = "Replace";
      this.AutoScaleDimensions = new SizeF(6f, 13f);
      this.AutoScaleMode = AutoScaleMode.Font;
      this.ClientSize = new Size(430, 454);
      this.Controls.Add((Control) this.mainTabControl);
      this.FormBorderStyle = FormBorderStyle.FixedSingle;
      this.MaximizeBox = false;
      this.MinimizeBox = false;
      this.Name = nameof (NewImportReplaceForm);
      this.ShowIcon = false;
      this.ShowInTaskbar = false;
      this.StartPosition = FormStartPosition.CenterScreen;
      this.Text = "Import/Replace";
      this.mainTabControl.ResumeLayout(false);
      this.importTab.ResumeLayout(false);
      this.panel1.ResumeLayout(false);
      this.panel1.PerformLayout();
      this.importFileResourcePanel.ResumeLayout(false);
      this.importFileResourcePanel.PerformLayout();
      this.importResourceType.EndInit();
      this.fileImportPanel.ResumeLayout(false);
      this.fileImportPanel.PerformLayout();
      this.replaceTab.ResumeLayout(false);
      this.panel2.ResumeLayout(false);
      this.panel2.PerformLayout();
      this.replaceFileResourcePanel.ResumeLayout(false);
      this.replaceFileResourcePanel.PerformLayout();
      this.replaceResourceType.EndInit();
      this.panel4.ResumeLayout(false);
      this.panel4.PerformLayout();
      this.ResumeLayout(false);
    }

    public enum FileMode
    {
      Import,
      Replace,
    }

    public enum ImportOrder
    {
      Append,
      Before,
      After,
    }
  }
}
