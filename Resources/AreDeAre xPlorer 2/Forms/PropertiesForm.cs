using RAGE;
using System;
using System.ComponentModel;
using System.Drawing;
using System.Globalization;
using System.Windows.Forms;

namespace AreDeAre_xPlorer_2.Forms
{
  public class PropertiesForm : Form
  {
    private RPF6.RPF6TOC.TOCSuperEntry PropertyOfEntry;
    private RPF6.RPF6TOC.TOCEntry TempEntry;
    private IContainer components = (IContainer) null;
    private Label propertiesOflabel;
    private Label propertiesOfNameLabel;
    private Label label1;
    private Panel fileInfoPanel;
    private Label fileInfoSizeNameLabel;
    private TextBox FileResourceFlag2;
    private TextBox FileResourceFlag1;
    private Label resourceFlag2Label;
    private Label resourceFlag1Label;
    private CheckBox isFileResource;
    private Button applyChangesButton;
    private Label label2;
    private NumericUpDown fileResourceType;
    private CheckBox fileCompressed;
    private TextBox fileResourceStart;
    private Label label3;
    private Label fileInfoSize;

    public bool ModifiedProperties { get; set; }

    public PropertiesForm(RPF6.RPF6TOC.TOCSuperEntry entry)
    {
      this.InitializeComponent();
      this.PropertyOfEntry = entry;
      if (this.PropertyOfEntry.IsDir)
      {
        RPF6.RPF6TOC.DirectoryEntry asDirectory = this.PropertyOfEntry.Entry.AsDirectory;
        RPF6.RPF6TOC.DirectoryEntry directoryEntry = new RPF6.RPF6TOC.DirectoryEntry();
        directoryEntry.Flags = asDirectory.Flags;
        directoryEntry.ContentEntryCount = asDirectory.ContentEntryCount;
        directoryEntry.ContentEntryIndex = asDirectory.ContentEntryIndex;
        directoryEntry.NameOffset = asDirectory.NameOffset;
        directoryEntry.Parent = asDirectory.Parent;
        directoryEntry.UNK = asDirectory.UNK;
        this.TempEntry = (RPF6.RPF6TOC.TOCEntry) directoryEntry;
      }
      else
      {
        RPF6.RPF6TOC.FileEntry asFile = this.PropertyOfEntry.Entry.AsFile;
        RPF6.RPF6TOC.FileEntry fileEntry = new RPF6.RPF6TOC.FileEntry();
        fileEntry.NameOffset = asFile.NameOffset;
        fileEntry.Parent = asFile.Parent;
        fileEntry.SizeInArchive = asFile.SizeInArchive;
        fileEntry.Offset = asFile.Offset;
        fileEntry.FlagInfo = new ResourceUtils.FlagInfo()
        {
          Flag1 = asFile.FlagInfo.Flag1,
          Flag2 = asFile.FlagInfo.Flag2
        };
        this.TempEntry = (RPF6.RPF6TOC.TOCEntry) fileEntry;
      }
      if (entry.Entry.AsFile.FlagInfo.IsResource)
      {
        int num = (int) MessageBox.Show(entry.Entry.AsFile.FlagInfo.ToString());
      }
      this.isFileResource.CheckedChanged -= new EventHandler(this.isFileResource_CheckedChanged);
      this.fileCompressed.CheckedChanged -= new EventHandler(this.fileCompressed_CheckedChanged);
      this.isFileResource.Checked = !entry.IsDir && entry.Entry.AsFile.FlagInfo.IsResource;
      this.fileCompressed.Checked = !entry.IsDir && entry.Entry.AsFile.FlagInfo.IsCompressed;
      this.isFileResource.CheckedChanged += new EventHandler(this.isFileResource_CheckedChanged);
      this.fileCompressed.CheckedChanged += new EventHandler(this.fileCompressed_CheckedChanged);
      this.propertiesOflabel.Text = string.Format("Properties Of {0}", this.PropertyOfEntry.IsDir ? (object) "Directory" : (object) "File");
      this.LoadDataFile();
    }

    private void applyChangesButton_Click(object sender, EventArgs e)
    {
      if (!this.PropertyOfEntry.IsDir)
      {
        RPF6.RPF6TOC.FileEntry asFile = this.PropertyOfEntry.Entry.AsFile;
        this.SaveDataFile();
      }
      this.ModifiedProperties = true;
      this.Close();
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

    private void isFileResource_CheckedChanged(object sender, EventArgs e)
    {
      this.fileResourceType.Enabled = this.isFileResource.Checked;
      this.TempEntry.AsFile.FlagInfo.IsResource = this.isFileResource.Checked;
      this.TempEntry.AsFile.ResourceType = this.isFileResource.Checked ? this.PropertyOfEntry.Entry.AsFile.ResourceType : (byte) 0;
      this.LoadDataFile();
    }

    private void fileCompressed_CheckedChanged(object sender, EventArgs e)
    {
      this.isFileResource.CheckedChanged -= new EventHandler(this.isFileResource_CheckedChanged);
      this.isFileResource.Checked = false;
      int virtOrSize = this.PropertyOfEntry.CustomDataStream == null || this.PropertyOfEntry.ReadBackFromRPF ? this.TempEntry.AsFile.FlagInfo.GetTotalSize() : (int) this.PropertyOfEntry.CustomDataStream.Length;
      this.TempEntry.AsFile.FlagInfo.IsCompressed = this.fileCompressed.Checked;
      this.TempEntry.AsFile.FlagInfo.SetTotalSize(virtOrSize, 0);
      this.LoadDataFile();
      this.isFileResource.CheckedChanged += new EventHandler(this.isFileResource_CheckedChanged);
    }

    private void LoadDataFile()
    {
      this.isFileResource.CheckedChanged -= new EventHandler(this.isFileResource_CheckedChanged);
      this.propertiesOfNameLabel.Text = this.TempEntry.Name;
      this.fileInfoPanel.Visible = this.isFileResource.Visible = this.fileCompressed.Visible = !this.PropertyOfEntry.IsDir;
      if (!this.PropertyOfEntry.IsDir)
      {
        RPF6.RPF6TOC.FileEntry asFile = this.TempEntry.AsFile;
        this.fileResourceType.Value = (Decimal) (this.isFileResource.Checked ? (int) asFile.ResourceType : 0);
        this.FileResourceFlag1.Text = asFile.FlagInfo.Flag1.ToString("X8");
        this.FileResourceFlag2.Text = asFile.FlagInfo.Flag2.ToString("X8");
        this.resourceFlag1Label.Text = string.Format("{0}", this.isFileResource.Checked ? (object) "Resource Flag1:" : (object) "Flag1:");
        this.resourceFlag2Label.Text = string.Format("{0}", this.isFileResource.Checked ? (object) "Resource Flag2:" : (object) "Flag2:");
        this.fileResourceStart.Text = asFile.FlagInfo.ResourceStart.ToString();
        this.fileInfoSize.Text = string.Format("{0}", (object) asFile.SizeInArchive);
        this.fileCompressed.Visible = !this.isFileResource.Checked && !asFile.FlagInfo.IsExtendedFlags;
      }
      this.isFileResource.CheckedChanged += new EventHandler(this.isFileResource_CheckedChanged);
    }

    private void SaveDataFile()
    {
      if (this.PropertyOfEntry.IsDir)
        return;
      if (this.isFileResource.Checked)
      {
        this.TempEntry.AsFile.FlagInfo.IsResource = this.isFileResource.Checked;
        this.TempEntry.AsFile.ResourceType = (byte) this.fileResourceType.Value;
      }
      this.TempEntry.AsFile.FlagInfo.Flag1 = int.Parse(this.FileResourceFlag1.Text, NumberStyles.HexNumber);
      this.TempEntry.AsFile.FlagInfo.Flag2 = int.Parse(this.FileResourceFlag2.Text, NumberStyles.HexNumber);
      this.PropertyOfEntry.Entry = this.TempEntry;
    }

    protected override void Dispose(bool disposing)
    {
      if (disposing && this.components != null)
        this.components.Dispose();
      base.Dispose(disposing);
    }

    private void InitializeComponent()
    {
      this.propertiesOflabel = new Label();
      this.propertiesOfNameLabel = new Label();
      this.label1 = new Label();
      this.fileInfoPanel = new Panel();
      this.fileInfoSize = new Label();
      this.fileResourceStart = new TextBox();
      this.label3 = new Label();
      this.label2 = new Label();
      this.fileResourceType = new NumericUpDown();
      this.FileResourceFlag2 = new TextBox();
      this.FileResourceFlag1 = new TextBox();
      this.resourceFlag2Label = new Label();
      this.resourceFlag1Label = new Label();
      this.fileInfoSizeNameLabel = new Label();
      this.isFileResource = new CheckBox();
      this.applyChangesButton = new Button();
      this.fileCompressed = new CheckBox();
      this.fileInfoPanel.SuspendLayout();
      this.fileResourceType.BeginInit();
      this.SuspendLayout();
      this.propertiesOflabel.AutoSize = true;
      this.propertiesOflabel.Font = new Font("Segoe UI", 18f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.propertiesOflabel.Location = new Point(12, 8);
      this.propertiesOflabel.Name = "propertiesOflabel";
      this.propertiesOflabel.Size = new Size(246, 32);
      this.propertiesOflabel.TabIndex = 0;
      this.propertiesOflabel.Text = "Properties Of (file/dir)";
      this.propertiesOfNameLabel.AutoSize = true;
      this.propertiesOfNameLabel.Font = new Font("Segoe UI", 16f, FontStyle.Italic, GraphicsUnit.Point, (byte) 0);
      this.propertiesOfNameLabel.Location = new Point(30, 35);
      this.propertiesOfNameLabel.Name = "propertiesOfNameLabel";
      this.propertiesOfNameLabel.Size = new Size(53, 30);
      this.propertiesOfNameLabel.TabIndex = 1;
      this.propertiesOfNameLabel.Text = "N/A";
      this.label1.AutoSize = true;
      this.label1.Font = new Font("Segoe UI", 18f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.label1.Location = new Point(12, 70);
      this.label1.Name = "label1";
      this.label1.Size = new Size(57, 32);
      this.label1.TabIndex = 2;
      this.label1.Text = "Info";
      this.fileInfoPanel.BorderStyle = BorderStyle.FixedSingle;
      this.fileInfoPanel.Controls.Add((Control) this.fileInfoSize);
      this.fileInfoPanel.Controls.Add((Control) this.fileResourceStart);
      this.fileInfoPanel.Controls.Add((Control) this.label3);
      this.fileInfoPanel.Controls.Add((Control) this.label2);
      this.fileInfoPanel.Controls.Add((Control) this.fileResourceType);
      this.fileInfoPanel.Controls.Add((Control) this.FileResourceFlag2);
      this.fileInfoPanel.Controls.Add((Control) this.FileResourceFlag1);
      this.fileInfoPanel.Controls.Add((Control) this.resourceFlag2Label);
      this.fileInfoPanel.Controls.Add((Control) this.resourceFlag1Label);
      this.fileInfoPanel.Controls.Add((Control) this.fileInfoSizeNameLabel);
      this.fileInfoPanel.Location = new Point(15, 105);
      this.fileInfoPanel.Name = "fileInfoPanel";
      this.fileInfoPanel.Size = new Size(357, 173);
      this.fileInfoPanel.TabIndex = 3;
      this.fileInfoPanel.Visible = false;
      this.fileInfoSize.AutoSize = true;
      this.fileInfoSize.Font = new Font("Arial", 14f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.fileInfoSize.Location = new Point(156, 12);
      this.fileInfoSize.Name = "fileInfoSize";
      this.fileInfoSize.Size = new Size(52, 22);
      this.fileInfoSize.TabIndex = 22;
      this.fileInfoSize.Text = "Size:";
      this.fileResourceStart.Location = new Point(160, 128);
      this.fileResourceStart.MaxLength = 8;
      this.fileResourceStart.Name = "fileResourceStart";
      this.fileResourceStart.ReadOnly = true;
      this.fileResourceStart.Size = new Size(186, 26);
      this.fileResourceStart.TabIndex = 21;
      this.label3.AutoSize = true;
      this.label3.Font = new Font("Arial", 13f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.label3.Location = new Point(12, 131);
      this.label3.Name = "label3";
      this.label3.Size = new Size(135, 21);
      this.label3.TabIndex = 20;
      this.label3.Text = "Resource Start:";
      this.label2.AutoSize = true;
      this.label2.Font = new Font("Arial", 13f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.label2.Location = new Point(12, 42);
      this.label2.Name = "label2";
      this.label2.Size = new Size(137, 21);
      this.label2.TabIndex = 19;
      this.label2.Text = "Resource Type:";
      this.fileResourceType.AutoSize = true;
      this.fileResourceType.Location = new Point(160, 40);
      this.fileResourceType.Maximum = new Decimal(new int[4]
      {
        (int) byte.MaxValue,
        0,
        0,
        0
      });
      this.fileResourceType.Name = "fileResourceType";
      this.fileResourceType.Size = new Size(186, 26);
      this.fileResourceType.TabIndex = 18;
      this.FileResourceFlag2.Location = new Point(160, 98);
      this.FileResourceFlag2.MaxLength = 8;
      this.FileResourceFlag2.Name = "FileResourceFlag2";
      this.FileResourceFlag2.Size = new Size(186, 26);
      this.FileResourceFlag2.TabIndex = 17;
      this.FileResourceFlag2.TextChanged += new EventHandler(this.FlagBoxes_TextChanged);
      this.FileResourceFlag1.Location = new Point(160, 69);
      this.FileResourceFlag1.MaxLength = 8;
      this.FileResourceFlag1.Name = "FileResourceFlag1";
      this.FileResourceFlag1.Size = new Size(186, 26);
      this.FileResourceFlag1.TabIndex = 16;
      this.FileResourceFlag1.TextChanged += new EventHandler(this.FlagBoxes_TextChanged);
      this.resourceFlag2Label.AutoSize = true;
      this.resourceFlag2Label.Font = new Font("Arial", 13f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.resourceFlag2Label.Location = new Point(12, 101);
      this.resourceFlag2Label.Name = "resourceFlag2Label";
      this.resourceFlag2Label.Size = new Size(142, 21);
      this.resourceFlag2Label.TabIndex = 15;
      this.resourceFlag2Label.Text = "Resource Flag2:";
      this.resourceFlag1Label.AutoSize = true;
      this.resourceFlag1Label.Font = new Font("Arial", 13f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.resourceFlag1Label.Location = new Point(12, 72);
      this.resourceFlag1Label.Name = "resourceFlag1Label";
      this.resourceFlag1Label.Size = new Size(142, 21);
      this.resourceFlag1Label.TabIndex = 14;
      this.resourceFlag1Label.Text = "Resource Flag1:";
      this.fileInfoSizeNameLabel.AutoSize = true;
      this.fileInfoSizeNameLabel.Font = new Font("Arial", 14f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.fileInfoSizeNameLabel.Location = new Point(12, 12);
      this.fileInfoSizeNameLabel.Name = "fileInfoSizeNameLabel";
      this.fileInfoSizeNameLabel.Size = new Size(52, 22);
      this.fileInfoSizeNameLabel.TabIndex = 0;
      this.fileInfoSizeNameLabel.Text = "Size:";
      this.isFileResource.AutoSize = true;
      this.isFileResource.Location = new Point(154, 80);
      this.isFileResource.Name = "isFileResource";
      this.isFileResource.Size = new Size(94, 22);
      this.isFileResource.TabIndex = 18;
      this.isFileResource.Text = "Resource";
      this.isFileResource.UseVisualStyleBackColor = true;
      this.isFileResource.Visible = false;
      this.applyChangesButton.FlatStyle = FlatStyle.Popup;
      this.applyChangesButton.Location = new Point(15, 284);
      this.applyChangesButton.Name = "applyChangesButton";
      this.applyChangesButton.Size = new Size(357, 30);
      this.applyChangesButton.TabIndex = 19;
      this.applyChangesButton.Text = "Apply";
      this.applyChangesButton.UseVisualStyleBackColor = true;
      this.applyChangesButton.Click += new EventHandler(this.applyChangesButton_Click);
      this.fileCompressed.AutoSize = true;
      this.fileCompressed.Location = new Point(254, 80);
      this.fileCompressed.Name = "fileCompressed";
      this.fileCompressed.Size = new Size(118, 22);
      this.fileCompressed.TabIndex = 20;
      this.fileCompressed.Text = "Compressed";
      this.fileCompressed.UseVisualStyleBackColor = true;
      this.fileCompressed.Visible = false;
      this.fileCompressed.CheckedChanged += new EventHandler(this.fileCompressed_CheckedChanged);
      this.AutoScaleDimensions = new SizeF(9f, 18f);
      this.AutoScaleMode = AutoScaleMode.Font;
      this.ClientSize = new Size(388, 326);
      this.Controls.Add((Control) this.fileCompressed);
      this.Controls.Add((Control) this.applyChangesButton);
      this.Controls.Add((Control) this.isFileResource);
      this.Controls.Add((Control) this.fileInfoPanel);
      this.Controls.Add((Control) this.label1);
      this.Controls.Add((Control) this.propertiesOfNameLabel);
      this.Controls.Add((Control) this.propertiesOflabel);
      this.Font = new Font("Arial", 12f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.FormBorderStyle = FormBorderStyle.FixedToolWindow;
      this.Margin = new Padding(4);
      this.MaximizeBox = false;
      this.MinimizeBox = false;
      this.Name = nameof (PropertiesForm);
      this.ShowIcon = false;
      this.ShowInTaskbar = false;
      this.StartPosition = FormStartPosition.CenterParent;
      this.Text = "Properties - N/A";
      this.fileInfoPanel.ResumeLayout(false);
      this.fileInfoPanel.PerformLayout();
      this.fileResourceType.EndInit();
      this.ResumeLayout(false);
      this.PerformLayout();
    }
  }
}
