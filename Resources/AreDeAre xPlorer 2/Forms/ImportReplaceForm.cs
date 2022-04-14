using Pik;
using Pik.IO;
using RAGE;
using System;
using System.ComponentModel;
using System.Drawing;
using System.Globalization;
using System.IO;
using System.Windows.Forms;

namespace AreDeAre_xPlorer_2.Forms
{
  public class ImportReplaceForm : Form
  {
    private IContainer components = (IContainer) null;
    private Label IRLabel;
    private Panel fileImportPanel;
    private Button openFileButton;
    private TextBox importFileName;
    private Label label1;
    private Panel importFileResourcePanel;
    private Label label2;
    private NumericUpDown fileResourceType;
    private CheckBox fileResourceCheck;
    private Label fileResourceVersion;
    private LinkLabel importFileResourceInfoLabel;
    private CheckBox fileCompressCheck;
    private Label label4;
    private Label label3;
    private Button importFileButton;
    private TextBox fileResourceFlag2;
    private TextBox fileResourceFlag1;
    private Panel fileReplacePanel;
    private Button replaceChooseButton;
    private TextBox replaceWith;
    private Label label5;
    private TextBox replacingFile;
    private Label label6;
    private Button replaceFileButton;
    private CheckBox fileReplaceNameCheck;
    private CheckBox fileKeepOffset;
    private RadioButton import_Append;
    private RadioButton import_Before;
    private RadioButton import_After;

    public RPF6.RPF6TOC.TOCSuperEntry TOCResult { get; set; }

    private RPF6.RPF6TOC.TOCSuperEntry EntryToReplace { get; set; }

    private RPF6.RPF6TOC.TOCSuperEntry ImportParent { get; set; }

    private RPF6.RPF6TOC.TOCSuperEntry SelectedFile { get; set; }

    private Stream ReplaceStream { get; set; }

    private Stream ImportStream { get; set; }

    private bool Import { get; set; }

    public ImportReplaceForm(
      bool import,
      RPF6.RPF6TOC.TOCSuperEntry importParent,
      RPF6.RPF6TOC.TOCSuperEntry selectedFile = null,
      RPF6.RPF6TOC.TOCSuperEntry entryToReplace = null,
      string importFileLoc = null)
    {
      this.InitializeComponent();
      this.EntryToReplace = entryToReplace;
      this.Import = import;
      this.SelectedFile = selectedFile;
      if (!import)
      {
        this.Text = "Replace";
        this.IRLabel.Text = "Replace File";
        this.replacingFile.Text = entryToReplace.Entry.Name;
        this.importFileButton.Visible = false;
        this.fileImportPanel.Visible = false;
        this.fileReplacePanel.Visible = true;
        this.replaceFileButton.Visible = true;
        this.fileResourceCheck.Visible = true;
        this.fileCompressCheck.Visible = true;
        this.fileCompressCheck.Enabled = true;
        this.fileReplaceNameCheck.Visible = true;
        this.fileKeepOffset.Visible = true;
        this.fileReplacePanel.Location = new Point(18, 32);
        this.importFileResourcePanel.Location = new Point(18, 182);
        this.fileResourceCheck.Location = new Point(19, 158);
        this.fileCompressCheck.Location = new Point(119, 158);
        this.Size = new Size(419, 416);
      }
      else
      {
        this.Text = nameof (Import);
        this.IRLabel.Text = "Import File";
        if (this.SelectedFile != null)
        {
          this.import_Before.Text = string.Format("Before {0}", (object) selectedFile.Entry.Name);
          this.import_After.Text = string.Format("After {0}", (object) selectedFile.Entry.Name);
        }
        if (this.SelectedFile == null || this.SelectedFile.IsDir)
        {
          this.import_Before.Enabled = false;
          this.import_After.Enabled = false;
          this.import_Append.Checked = true;
        }
        this.importFileButton.Visible = true;
        this.fileImportPanel.Visible = true;
        this.fileCompressCheck.Visible = true;
        this.fileResourceCheck.Visible = true;
        this.fileKeepOffset.Visible = false;
        this.fileResourceCheck.Location = new Point(19, 180);
        this.fileCompressCheck.Location = new Point(119, 180);
        this.fileKeepOffset.Location = new Point(225, 180);
        this.importFileResourcePanel.Location = new Point(18, 204);
        this.importFileButton.Location = new Point(18, 355);
        this.fileImportPanel.Location = new Point(18, 38);
        this.Size = new Size(419, 439);
      }
    }

    private void openFileButton_Click(object sender, EventArgs e)
    {
      OpenFileDialog openFileDialog = new OpenFileDialog();
      openFileDialog.Title = "Import File...";
      openFileDialog.Filter = "|*.*";
      openFileDialog.Multiselect = false;
      if (openFileDialog.ShowDialog() != DialogResult.OK)
        return;
      this.importFileName.Text = openFileDialog.FileName;
      this.LoadImportData();
    }

    private void importFileButton_Click(object sender, EventArgs e)
    {
      RPF6.RPF6TOC.TOCSuperEntry tocSuperEntry = new RPF6.RPF6TOC.TOCSuperEntry();
      tocSuperEntry.CustomDataStream = this.ImportStream;
      RPF6.RPF6TOC.FileEntry fileEntry = new RPF6.RPF6TOC.FileEntry();
      fileEntry.FlagInfo.Flag1 = DataUtils.IntFromUInt(string.IsNullOrEmpty(this.fileResourceFlag1.Text) ? 0U : uint.Parse(this.fileResourceFlag1.Text, NumberStyles.HexNumber));
      fileEntry.FlagInfo.Flag2 = DataUtils.IntFromUInt(string.IsNullOrEmpty(this.fileResourceFlag2.Text) ? 0U : uint.Parse(this.fileResourceFlag2.Text, NumberStyles.HexNumber));
      if (this.fileResourceCheck.Checked)
      {
        fileEntry.FlagInfo.IsResource = true;
        fileEntry.ResourceType = (byte) this.fileResourceType.Value;
      }
      else if (this.fileCompressCheck.Checked)
      {
        fileEntry.FlagInfo.IsCompressed = true;
        fileEntry.FlagInfo.SetTotalSize((int) this.ImportStream.Length, 0);
      }
      else
      {
        fileEntry.FlagInfo.IsCompressed = false;
        fileEntry.FlagInfo.SetTotalSize((int) this.ImportStream.Length, 0);
      }
      fileEntry.SizeInArchive = (int) this.ImportStream.Length;
      RPF6FileNameHandler.AddName(Path.GetFileName(this.importFileName.Text));
      RPF6FileNameHandler.SaveNames();
      fileEntry.NameOffset = DataUtils.GetHash(Path.GetFileName(this.importFileName.Text));
      RPF6FileNameHandler.FileNames.ContainsKey(fileEntry.NameOffset);
      tocSuperEntry.Entry = (RPF6.RPF6TOC.TOCEntry) fileEntry;
      if (this.SelectedFile != null)
      {
        switch (this.import_Before.Checked ? ImportReplaceForm.ImportOrder.Before : (this.import_After.Checked ? ImportReplaceForm.ImportOrder.After : ImportReplaceForm.ImportOrder.Append))
        {
          case ImportReplaceForm.ImportOrder.Before:
            this.SelectedFile.WriteBefore_Children.Add(tocSuperEntry);
            break;
          case ImportReplaceForm.ImportOrder.After:
            this.SelectedFile.WriteAfterChildren.Add(tocSuperEntry);
            break;
        }
      }
      this.TOCResult = tocSuperEntry;
      this.Close();
    }

    private void replaceChooseButton_Click(object sender, EventArgs e)
    {
      OpenFileDialog openFileDialog = new OpenFileDialog();
      openFileDialog.Title = "Replace with...";
      openFileDialog.Filter = "|*.*";
      openFileDialog.Multiselect = false;
      if (openFileDialog.ShowDialog() != DialogResult.OK)
        return;
      this.replaceWith.Text = openFileDialog.FileName;
      this.LoadReplaceData();
    }

    private void replaceFileButton_Click(object sender, EventArgs e)
    {
      RPF6.RPF6TOC.TOCSuperEntry tocSuperEntry = new RPF6.RPF6TOC.TOCSuperEntry();
      tocSuperEntry.CustomDataStream = this.ReplaceStream;
      tocSuperEntry.OldEntry = this.EntryToReplace.Entry;
      tocSuperEntry.ReadBackFromRPF = false;
      RPF6.RPF6TOC.FileEntry fileEntry = new RPF6.RPF6TOC.FileEntry();
      fileEntry.FlagInfo.Flag1 = DataUtils.IntFromUInt(string.IsNullOrEmpty(this.fileResourceFlag1.Text) ? 0U : uint.Parse(this.fileResourceFlag1.Text, NumberStyles.HexNumber));
      fileEntry.FlagInfo.Flag2 = DataUtils.IntFromUInt(string.IsNullOrEmpty(this.fileResourceFlag2.Text) ? 0U : uint.Parse(this.fileResourceFlag2.Text, NumberStyles.HexNumber));
      if (this.fileResourceCheck.Checked)
      {
        fileEntry.FlagInfo.IsResource = true;
        fileEntry.ResourceType = (byte) this.fileResourceType.Value;
      }
      else if (this.fileCompressCheck.Checked)
      {
        fileEntry.FlagInfo.IsCompressed = true;
        fileEntry.FlagInfo.SetTotalSize((int) this.ReplaceStream.Length, 0);
      }
      else
      {
        fileEntry.FlagInfo.IsCompressed = true;
        fileEntry.FlagInfo.SetTotalSize((int) this.ReplaceStream.Length, 0);
      }
      fileEntry.SizeInArchive = (int) this.ReplaceStream.Length;
      if (this.fileReplaceNameCheck.Checked)
        fileEntry.NameOffset = DataUtils.GetHash(Path.GetFileName(this.replaceWith.Text));
      else
        fileEntry.NameOffset = this.EntryToReplace.Entry.NameOffset;
      RPF6FileNameHandler.AddName(Path.GetFileName(this.importFileName.Text));
      tocSuperEntry.Entry = (RPF6.RPF6TOC.TOCEntry) fileEntry;
      tocSuperEntry.Entry.AsFile.KeepOffset = this.fileKeepOffset.Checked ? new long?(tocSuperEntry.OldEntry.AsFile.GetOffset()) : new long?();
      RPF6FileNameHandler.SaveNames();
      this.TOCResult = tocSuperEntry;
      this.Close();
    }

    private void LoadReplaceData()
    {
      try
      {
        this.ReplaceStream = (Stream) File.Open(this.replaceWith.Text, System.IO.FileMode.Open, FileAccess.Read, FileShare.ReadWrite);
        if (this.ReplaceStream.Length >= 12L)
        {
          PikIO pikIo = new PikIO(this.ReplaceStream, PikIO.Endianess.Big);
          uint ident = pikIo.ReadUInt32();
          int num1;
          switch (ident)
          {
            case 88298322:
            case 2235781970:
            case 2252559186:
              num1 = 1;
              break;
            default:
              num1 = ident == 105075538U ? 1 : 0;
              break;
          }
          if (num1 != 0)
          {
            int num2 = pikIo.ReadInt32();
            this.fileResourceVersion.Text = string.Format("Resource Version: {0}", (object) ResourceUtils.ResourceInfo.GetResourceVersionStringFromIdent(ident));
            int num3;
            int num4;
            if (ident == 2235781970U || ident == 2252559186U)
            {
              num3 = pikIo.ReadInt32();
              num4 = pikIo.ReadInt32();
            }
            else
            {
              num3 = pikIo.ReadInt32();
              num4 = 0;
            }
            this.fileResourceCheck.Enabled = true;
            this.fileCompressCheck.Enabled = true;
            this.fileResourceCheck.Checked = true;
            this.fileResourceType.Value = (Decimal) num2;
            this.fileCompressCheck.Checked = (num3 & 1073741824) > 0;
            this.fileResourceFlag1.Text = num3.ToString("X8");
            this.fileResourceFlag2.Text = num4.ToString("X8");
          }
        }
        this.fileKeepOffset.Enabled = true;
        this.ReplaceStream.Position = 0L;
      }
      catch (Exception ex)
      {
        int num = (int) MessageBox.Show(string.Format("Could not replace file\r\nError:\r\n{0}\r\nStack:\r\n{1}\r\n\r\nApplication will now exit.", (object) ex.Message, (object) ex.StackTrace), "Import Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
        Application.Exit();
      }
    }

    private void LoadImportData()
    {
      this.fileResourceCheck.Enabled = true;
      this.fileCompressCheck.Enabled = true;
      try
      {
        this.ImportStream = (Stream) File.Open(this.importFileName.Text, System.IO.FileMode.Open, FileAccess.Read, FileShare.ReadWrite);
        if (this.ImportStream.Length >= 12L)
        {
          PikIO pikIo = new PikIO(this.ImportStream, PikIO.Endianess.Big);
          uint ident = pikIo.ReadUInt32();
          int num1;
          switch (ident)
          {
            case 88298322:
            case 2235781970:
            case 2252559186:
              num1 = 1;
              break;
            default:
              num1 = ident == 105075538U ? 1 : 0;
              break;
          }
          if (num1 != 0)
          {
            int num2 = pikIo.ReadInt32();
            this.fileResourceVersion.Text = string.Format("Resource Version: {0}", (object) ResourceUtils.ResourceInfo.GetResourceVersionStringFromIdent(ident));
            int num3;
            int num4;
            if (ident == 2235781970U || ident == 2252559186U)
            {
              num3 = pikIo.ReadInt32();
              num4 = pikIo.ReadInt32();
            }
            else
            {
              this.fileResourceVersion.Text = "Resource Version: RSC05";
              num3 = pikIo.ReadInt32();
              num4 = 0;
            }
            this.fileResourceCheck.Checked = true;
            this.fileResourceType.Value = (Decimal) num2;
            this.fileCompressCheck.Checked = (num3 & 1073741824) > 0;
            this.fileResourceFlag1.Text = num3.ToString("X8");
            this.fileResourceFlag2.Text = num4.ToString("X8");
          }
        }
        this.ImportStream.Position = 0L;
      }
      catch (Exception ex)
      {
        int num = (int) MessageBox.Show(string.Format("Could not import file\r\nError:\r\n{0}\r\nStack:\r\n{1}\r\n\r\nApplication will now exit.", (object) ex.Message, (object) ex.StackTrace), "Import Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
        Application.Exit();
      }
    }

    private void fileImportResource_CheckedChanged(object sender, EventArgs e)
    {
      this.importFileResourcePanel.Enabled = this.fileResourceCheck.Checked;
      if (!this.fileResourceCheck.Checked)
      {
        this.fileResourceVersion.Text = "Resource Version: None";
        this.fileResourceType.Value = 0M;
        this.fileResourceFlag1.Text = string.Empty;
        this.fileResourceFlag2.Text = string.Empty;
      }
      else if (this.Import)
        this.LoadImportData();
      else
        this.LoadReplaceData();
      this.fileCompressCheck.Enabled = !this.fileResourceCheck.Checked;
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

    protected override void Dispose(bool disposing)
    {
      if (disposing && this.components != null)
        this.components.Dispose();
      base.Dispose(disposing);
    }

    private void InitializeComponent()
    {
      this.IRLabel = new Label();
      this.fileImportPanel = new Panel();
      this.import_Append = new RadioButton();
      this.import_Before = new RadioButton();
      this.import_After = new RadioButton();
      this.openFileButton = new Button();
      this.importFileName = new TextBox();
      this.label1 = new Label();
      this.fileCompressCheck = new CheckBox();
      this.importFileResourcePanel = new Panel();
      this.fileResourceFlag2 = new TextBox();
      this.fileResourceFlag1 = new TextBox();
      this.label4 = new Label();
      this.label3 = new Label();
      this.importFileResourceInfoLabel = new LinkLabel();
      this.fileResourceVersion = new Label();
      this.label2 = new Label();
      this.fileResourceType = new NumericUpDown();
      this.fileResourceCheck = new CheckBox();
      this.importFileButton = new Button();
      this.fileReplacePanel = new Panel();
      this.fileReplaceNameCheck = new CheckBox();
      this.replacingFile = new TextBox();
      this.label6 = new Label();
      this.replaceChooseButton = new Button();
      this.replaceWith = new TextBox();
      this.label5 = new Label();
      this.replaceFileButton = new Button();
      this.fileKeepOffset = new CheckBox();
      this.fileImportPanel.SuspendLayout();
      this.importFileResourcePanel.SuspendLayout();
      this.fileResourceType.BeginInit();
      this.fileReplacePanel.SuspendLayout();
      this.SuspendLayout();
      this.IRLabel.AutoSize = true;
      this.IRLabel.Font = new Font("Segoe UI", 18f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.IRLabel.Location = new Point(12, 3);
      this.IRLabel.Name = "IRLabel";
      this.IRLabel.Size = new Size(91, 32);
      this.IRLabel.TabIndex = 0;
      this.IRLabel.Text = "IRLabel";
      this.fileImportPanel.BorderStyle = BorderStyle.FixedSingle;
      this.fileImportPanel.Controls.Add((Control) this.import_Append);
      this.fileImportPanel.Controls.Add((Control) this.import_Before);
      this.fileImportPanel.Controls.Add((Control) this.import_After);
      this.fileImportPanel.Controls.Add((Control) this.openFileButton);
      this.fileImportPanel.Controls.Add((Control) this.importFileName);
      this.fileImportPanel.Controls.Add((Control) this.label1);
      this.fileImportPanel.Location = new Point(397, 32);
      this.fileImportPanel.Name = "fileImportPanel";
      this.fileImportPanel.Size = new Size(373, 140);
      this.fileImportPanel.TabIndex = 1;
      this.fileImportPanel.Visible = false;
      this.import_Append.AutoSize = true;
      this.import_Append.Checked = true;
      this.import_Append.Location = new Point(14, 110);
      this.import_Append.Name = "import_Append";
      this.import_Append.Size = new Size(133, 22);
      this.import_Append.TabIndex = 5;
      this.import_Append.TabStop = true;
      this.import_Append.Text = "Append To End";
      this.import_Append.UseVisualStyleBackColor = true;
      this.import_Before.AutoSize = true;
      this.import_Before.Location = new Point(14, 87);
      this.import_Before.Name = "import_Before";
      this.import_Before.Size = new Size(118, 22);
      this.import_Before.TabIndex = 4;
      this.import_Before.TabStop = true;
      this.import_Before.Text = "Before [FILE]";
      this.import_Before.UseVisualStyleBackColor = true;
      this.import_After.AutoSize = true;
      this.import_After.Location = new Point(14, 64);
      this.import_After.Name = "import_After";
      this.import_After.Size = new Size(104, 22);
      this.import_After.TabIndex = 3;
      this.import_After.TabStop = true;
      this.import_After.Text = "After [FILE]";
      this.import_After.UseVisualStyleBackColor = true;
      this.openFileButton.Font = new Font("Segoe UI", 10f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.openFileButton.Location = new Point(326, 33);
      this.openFileButton.Name = "openFileButton";
      this.openFileButton.Size = new Size(42, 23);
      this.openFileButton.TabIndex = 2;
      this.openFileButton.Text = "...";
      this.openFileButton.UseVisualStyleBackColor = true;
      this.openFileButton.Click += new EventHandler(this.openFileButton_Click);
      this.importFileName.Font = new Font("Segoe UI", 10f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.importFileName.Location = new Point(3, 33);
      this.importFileName.Name = "importFileName";
      this.importFileName.ReadOnly = true;
      this.importFileName.Size = new Size(315, 25);
      this.importFileName.TabIndex = 1;
      this.label1.AutoSize = true;
      this.label1.Font = new Font("Segoe UI", 13f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.label1.Location = new Point(9, 5);
      this.label1.Name = "label1";
      this.label1.Size = new Size(98, 25);
      this.label1.TabIndex = 0;
      this.label1.Text = "File Import";
      this.fileCompressCheck.AutoSize = true;
      this.fileCompressCheck.Enabled = false;
      this.fileCompressCheck.Location = new Point(119, 158);
      this.fileCompressCheck.Name = "fileCompressCheck";
      this.fileCompressCheck.Size = new Size(100, 22);
      this.fileCompressCheck.TabIndex = 5;
      this.fileCompressCheck.Text = "Compress";
      this.fileCompressCheck.UseVisualStyleBackColor = true;
      this.fileCompressCheck.Visible = false;
      this.importFileResourcePanel.BorderStyle = BorderStyle.FixedSingle;
      this.importFileResourcePanel.Controls.Add((Control) this.fileResourceFlag2);
      this.importFileResourcePanel.Controls.Add((Control) this.fileResourceFlag1);
      this.importFileResourcePanel.Controls.Add((Control) this.label4);
      this.importFileResourcePanel.Controls.Add((Control) this.label3);
      this.importFileResourcePanel.Controls.Add((Control) this.importFileResourceInfoLabel);
      this.importFileResourcePanel.Controls.Add((Control) this.fileResourceVersion);
      this.importFileResourcePanel.Controls.Add((Control) this.label2);
      this.importFileResourcePanel.Controls.Add((Control) this.fileResourceType);
      this.importFileResourcePanel.Enabled = false;
      this.importFileResourcePanel.Location = new Point(18, 182);
      this.importFileResourcePanel.Name = "importFileResourcePanel";
      this.importFileResourcePanel.Size = new Size(373, 145);
      this.importFileResourcePanel.TabIndex = 4;
      this.fileResourceFlag2.Location = new Point(132, 93);
      this.fileResourceFlag2.MaxLength = 8;
      this.fileResourceFlag2.Name = "fileResourceFlag2";
      this.fileResourceFlag2.Size = new Size(236, 26);
      this.fileResourceFlag2.TabIndex = 13;
      this.fileResourceFlag2.TextChanged += new EventHandler(this.FlagBoxes_TextChanged);
      this.fileResourceFlag1.Location = new Point(132, 62);
      this.fileResourceFlag1.MaxLength = 8;
      this.fileResourceFlag1.Name = "fileResourceFlag1";
      this.fileResourceFlag1.Size = new Size(236, 26);
      this.fileResourceFlag1.TabIndex = 12;
      this.fileResourceFlag1.TextChanged += new EventHandler(this.FlagBoxes_TextChanged);
      this.label4.AutoSize = true;
      this.label4.Location = new Point(7, 94);
      this.label4.Name = "label4";
      this.label4.Size = new Size(123, 18);
      this.label4.TabIndex = 11;
      this.label4.Text = "Resource Flag2:";
      this.label3.AutoSize = true;
      this.label3.Location = new Point(7, 64);
      this.label3.Name = "label3";
      this.label3.Size = new Size(123, 18);
      this.label3.TabIndex = 9;
      this.label3.Text = "Resource Flag1:";
      this.importFileResourceInfoLabel.AutoSize = true;
      this.importFileResourceInfoLabel.Cursor = Cursors.Hand;
      this.importFileResourceInfoLabel.Location = new Point(291, 122);
      this.importFileResourceInfoLabel.Name = "importFileResourceInfoLabel";
      this.importFileResourceInfoLabel.Size = new Size(77, 18);
      this.importFileResourceInfoLabel.TabIndex = 7;
      this.importFileResourceInfoLabel.TabStop = true;
      this.importFileResourceInfoLabel.Text = "Important!";
      this.fileResourceVersion.AutoSize = true;
      this.fileResourceVersion.Font = new Font("Segoe UI", 14f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.fileResourceVersion.Location = new Point(9, 5);
      this.fileResourceVersion.Name = "fileResourceVersion";
      this.fileResourceVersion.Size = new Size(198, 25);
      this.fileResourceVersion.TabIndex = 6;
      this.fileResourceVersion.Text = "Resource Version: N/A";
      this.label2.AutoSize = true;
      this.label2.Location = new Point(7, 34);
      this.label2.Name = "label2";
      this.label2.Size = new Size(116, 18);
      this.label2.TabIndex = 5;
      this.label2.Text = "Resource Type:";
      this.fileResourceType.Location = new Point(132, 33);
      this.fileResourceType.Maximum = new Decimal(new int[4]
      {
        (int) byte.MaxValue,
        0,
        0,
        0
      });
      this.fileResourceType.Name = "fileResourceType";
      this.fileResourceType.Size = new Size(236, 26);
      this.fileResourceType.TabIndex = 4;
      this.fileResourceCheck.AutoSize = true;
      this.fileResourceCheck.Enabled = false;
      this.fileResourceCheck.Location = new Point(19, 158);
      this.fileResourceCheck.Name = "fileResourceCheck";
      this.fileResourceCheck.Size = new Size(94, 22);
      this.fileResourceCheck.TabIndex = 3;
      this.fileResourceCheck.Text = "Resource";
      this.fileResourceCheck.UseVisualStyleBackColor = true;
      this.fileResourceCheck.Visible = false;
      this.fileResourceCheck.CheckedChanged += new EventHandler(this.fileImportResource_CheckedChanged);
      this.importFileButton.Location = new Point(397, 288);
      this.importFileButton.Name = "importFileButton";
      this.importFileButton.Size = new Size(373, 35);
      this.importFileButton.TabIndex = 3;
      this.importFileButton.Text = "Import";
      this.importFileButton.UseVisualStyleBackColor = true;
      this.importFileButton.Visible = false;
      this.importFileButton.Click += new EventHandler(this.importFileButton_Click);
      this.fileReplacePanel.BorderStyle = BorderStyle.FixedSingle;
      this.fileReplacePanel.Controls.Add((Control) this.fileReplaceNameCheck);
      this.fileReplacePanel.Controls.Add((Control) this.replacingFile);
      this.fileReplacePanel.Controls.Add((Control) this.label6);
      this.fileReplacePanel.Controls.Add((Control) this.replaceChooseButton);
      this.fileReplacePanel.Controls.Add((Control) this.replaceWith);
      this.fileReplacePanel.Controls.Add((Control) this.label5);
      this.fileReplacePanel.Location = new Point(18, 32);
      this.fileReplacePanel.Name = "fileReplacePanel";
      this.fileReplacePanel.Size = new Size(373, 120);
      this.fileReplacePanel.TabIndex = 6;
      this.fileReplacePanel.Visible = false;
      this.fileReplaceNameCheck.AutoSize = true;
      this.fileReplaceNameCheck.Location = new Point(187, 59);
      this.fileReplaceNameCheck.Name = "fileReplaceNameCheck";
      this.fileReplaceNameCheck.Size = new Size(131, 22);
      this.fileReplaceNameCheck.TabIndex = 8;
      this.fileReplaceNameCheck.Text = "Replace Name";
      this.fileReplaceNameCheck.UseVisualStyleBackColor = true;
      this.fileReplaceNameCheck.Visible = false;
      this.replacingFile.Font = new Font("Segoe UI", 10f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.replacingFile.Location = new Point(3, 31);
      this.replacingFile.Name = "replacingFile";
      this.replacingFile.ReadOnly = true;
      this.replacingFile.Size = new Size(365, 25);
      this.replacingFile.TabIndex = 4;
      this.label6.AutoSize = true;
      this.label6.Font = new Font("Segoe UI", 13f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.label6.Location = new Point(8, 3);
      this.label6.Name = "label6";
      this.label6.Size = new Size(88, 25);
      this.label6.TabIndex = 3;
      this.label6.Text = "Replacing";
      this.replaceChooseButton.Font = new Font("Segoe UI", 10f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.replaceChooseButton.Location = new Point(326, 85);
      this.replaceChooseButton.Name = "replaceChooseButton";
      this.replaceChooseButton.Size = new Size(42, 23);
      this.replaceChooseButton.TabIndex = 2;
      this.replaceChooseButton.Text = "...";
      this.replaceChooseButton.UseVisualStyleBackColor = true;
      this.replaceChooseButton.Click += new EventHandler(this.replaceChooseButton_Click);
      this.replaceWith.Font = new Font("Segoe UI", 10f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.replaceWith.Location = new Point(3, 84);
      this.replaceWith.Name = "replaceWith";
      this.replaceWith.ReadOnly = true;
      this.replaceWith.Size = new Size(315, 25);
      this.replaceWith.TabIndex = 1;
      this.label5.AutoSize = true;
      this.label5.Font = new Font("Segoe UI", 13f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.label5.Location = new Point(8, 57);
      this.label5.Name = "label5";
      this.label5.Size = new Size(114, 25);
      this.label5.TabIndex = 0;
      this.label5.Text = "Replace With";
      this.replaceFileButton.Location = new Point(18, 333);
      this.replaceFileButton.Name = "replaceFileButton";
      this.replaceFileButton.Size = new Size(373, 35);
      this.replaceFileButton.TabIndex = 7;
      this.replaceFileButton.Text = "Replace";
      this.replaceFileButton.UseVisualStyleBackColor = true;
      this.replaceFileButton.Visible = false;
      this.replaceFileButton.Click += new EventHandler(this.replaceFileButton_Click);
      this.fileKeepOffset.AutoSize = true;
      this.fileKeepOffset.Enabled = false;
      this.fileKeepOffset.Location = new Point(225, 158);
      this.fileKeepOffset.Name = "fileKeepOffset";
      this.fileKeepOffset.Size = new Size(110, 22);
      this.fileKeepOffset.TabIndex = 8;
      this.fileKeepOffset.Text = "Keep Offset";
      this.fileKeepOffset.UseVisualStyleBackColor = true;
      this.fileKeepOffset.Visible = false;
      this.AutoScaleDimensions = new SizeF(9f, 18f);
      this.AutoScaleMode = AutoScaleMode.Font;
      this.AutoSize = true;
      this.ClientSize = new Size(777, 377);
      this.Controls.Add((Control) this.fileKeepOffset);
      this.Controls.Add((Control) this.replaceFileButton);
      this.Controls.Add((Control) this.fileReplacePanel);
      this.Controls.Add((Control) this.fileCompressCheck);
      this.Controls.Add((Control) this.importFileButton);
      this.Controls.Add((Control) this.fileResourceCheck);
      this.Controls.Add((Control) this.importFileResourcePanel);
      this.Controls.Add((Control) this.fileImportPanel);
      this.Controls.Add((Control) this.IRLabel);
      this.Font = new Font("Arial", 12f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.FormBorderStyle = FormBorderStyle.FixedSingle;
      this.Margin = new Padding(4);
      this.MaximizeBox = false;
      this.MinimizeBox = false;
      this.Name = nameof (ImportReplaceForm);
      this.ShowIcon = false;
      this.StartPosition = FormStartPosition.CenterParent;
      this.Text = "REPLACE/IMPORT";
      this.fileImportPanel.ResumeLayout(false);
      this.fileImportPanel.PerformLayout();
      this.importFileResourcePanel.ResumeLayout(false);
      this.importFileResourcePanel.PerformLayout();
      this.fileResourceType.EndInit();
      this.fileReplacePanel.ResumeLayout(false);
      this.fileReplacePanel.PerformLayout();
      this.ResumeLayout(false);
      this.PerformLayout();
    }

    public enum ImportOrder
    {
      Append,
      Before,
      After,
    }
  }
}
