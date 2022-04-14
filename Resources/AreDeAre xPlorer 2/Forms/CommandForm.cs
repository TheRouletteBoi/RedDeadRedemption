using ComponentOwl.BetterListView;
using Pik.IO;
using System;
using System.ComponentModel;
using System.Drawing;
using System.IO;
using System.Media;
using System.Windows.Forms;

namespace AreDeAre_xPlorer_2.Forms
{
  public class CommandForm : Form
  {
    private IContainer components = (IContainer) null;
    private Label titleLabel;
    private Panel panel1;
    private ComboBox commandFileList;
    private Label label2;
    private Label label1;
    private Panel panel3;
    private Panel dataPanelOpenRPF;
    private Panel commandsPanel;
    private ComponentOwl.BetterListView.BetterListView commandsViewer;
    private BetterListViewColumnHeader commandHeader;
    private ContextMenuStrip commandMenu;
    private ToolStripMenuItem addOpenRPFCommandButton;
    private Label label3;
    private Button saveButton;
    private Button openRPFSelectFileNameButton;
    private TextBox openRPFFileNameTextBox;
    private Label label4;
    private ToolStripMenuItem addExtractFileCommandButton;
    private Button applyOpenRPFCommandData;
    private ToolStripMenuItem addCloseRPFCommandButton;
    private Panel dataPanelExtractFile;
    private Label label5;
    private TextBox extractFileFilePathInRPFTextBox;
    private Button extractFileApply;
    private Button extractFileOutputPathButton;
    private TextBox extractFileOutputPathTextBox;
    private Label label6;
    private Panel dataPanelImportReplace;
    private Button importReplaceAppyButton;
    private Button importReplaceChooseInputFileButton;
    private TextBox importReplaceInputFileNameTextBox;
    private Label label7;
    private TextBox importReplaceRPFFileNameTextBox;
    private Label label8;
    private ToolStripMenuItem addImportReplaceCommandButton;
    private Label label9;
    private Label label11;
    private Label label10;
    private CheckBox importReplaceCompress;
    private CheckBox importReplaceKeepOffset;
    private Button moveCommandUpButton;
    private Button moveCommandDownButton;
    private ToolStripSeparator toolStripSeparator1;
    private ToolStripMenuItem removeCommandButton;
    private Panel dataPanelSaveRPF;
    private Label label12;
    private Button saveRPFApplyButton;
    private Button saveRPFChooseFileButton;
    private TextBox saveRPFFileNameTextBox;
    private Label label13;
    private ToolStripMenuItem addSaveRPFCommandButton;
    private CheckBox importReplaceKeepName;
    private Panel dataPanelCreateDir;
    private Label label14;
    private Button createDirApply;
    private TextBox createDirDirNameTextBox;
    private Label label15;
    private TextBox createDirParentNameTextBox;
    private Label label16;
    private ToolStripMenuItem addCreateDirCommandButton;
    private CheckBox saveRPFWriteInorderCheck;

    public CommandForm()
    {
      this.InitializeComponent();
      this.HidePanels();
      this.dataPanelOpenRPF.Dock = DockStyle.Fill;
      this.dataPanelExtractFile.Dock = DockStyle.Fill;
      this.dataPanelImportReplace.Dock = DockStyle.Fill;
      this.dataPanelSaveRPF.Dock = DockStyle.Fill;
      this.dataPanelCreateDir.Dock = DockStyle.Fill;
      this.LoadCommandsDir();
    }

    private RPFCommandFile.Command CurrentCommand { get; set; }

    private void HidePanels()
    {
      this.dataPanelOpenRPF.Visible = false;
      this.dataPanelExtractFile.Visible = false;
      this.dataPanelImportReplace.Visible = false;
      this.dataPanelSaveRPF.Visible = false;
      this.dataPanelCreateDir.Visible = false;
    }

    private void LoadCommandData(RPFCommandFile.Command cmd)
    {
      this.HidePanels();
      this.CurrentCommand = cmd;
      if (cmd.ID == RPFCommandFile.CommandID.OpenRPF)
      {
        this.dataPanelOpenRPF.Visible = true;
        this.openRPFFileNameTextBox.Text = ((RPFCommandFile.OpenRPFCommand) cmd).RPFFileName;
      }
      else if (cmd.ID == RPFCommandFile.CommandID.ExtractFile)
      {
        this.dataPanelExtractFile.Visible = true;
        RPFCommandFile.ExtractFileCommand extractFileCommand = (RPFCommandFile.ExtractFileCommand) cmd;
        this.extractFileFilePathInRPFTextBox.Text = extractFileCommand.RPFFileName;
        this.extractFileOutputPathTextBox.Text = extractFileCommand.OutFileName;
      }
      else if (cmd.ID == RPFCommandFile.CommandID.ImportReplace)
      {
        this.dataPanelImportReplace.Visible = true;
        RPFCommandFile.ImportReplaceCommand importReplaceCommand = (RPFCommandFile.ImportReplaceCommand) cmd;
        this.importReplaceRPFFileNameTextBox.Text = importReplaceCommand.RPFFileName;
        this.importReplaceInputFileNameTextBox.Text = importReplaceCommand.InFileName;
        this.importReplaceKeepOffset.Checked = importReplaceCommand.KeepOffset;
        this.importReplaceCompress.Checked = importReplaceCommand.Compress;
        this.importReplaceKeepName.Checked = importReplaceCommand.KeepName;
      }
      else if (cmd.ID == RPFCommandFile.CommandID.SaveRPF)
      {
        this.dataPanelSaveRPF.Visible = true;
        this.saveRPFFileNameTextBox.Text = ((RPFCommandFile.SaveRPFCommand) cmd).OutRPFFile;
      }
      else
      {
        if (cmd.ID != RPFCommandFile.CommandID.CreateDir)
          return;
        this.dataPanelCreateDir.Visible = true;
        RPFCommandFile.CreateDirectoryCommand directoryCommand = (RPFCommandFile.CreateDirectoryCommand) cmd;
        this.createDirParentNameTextBox.Text = directoryCommand.ParentDir;
        this.createDirDirNameTextBox.Text = directoryCommand.DirName;
      }
    }

    private void LoadSelectedCommandFileToView()
    {
      this.commandsViewer.BeginUpdate();
      this.commandsViewer.Items.Clear();
      foreach (RPFCommandFile.Command command in ((CommandForm.CommandFileObject) this.commandFileList.SelectedItem).CmdFile.Commands)
      {
        BetterListViewItem betterListViewItem = new BetterListViewItem();
        betterListViewItem.Text = command.ToString();
        betterListViewItem.Tag = (object) command;
        this.commandsViewer.Items.Add(betterListViewItem);
      }
      this.commandsViewer.Enabled = true;
      this.commandsViewer.EndUpdate();
    }

    private void LoadCommandsDir()
    {
      if (!AppUtils.DirectoryExists("editor_commands"))
        AppUtils.CreateDirectory("editor_commands");
      this.ClearFileList();
      this.LoadFileList();
    }

    private void LoadFileList()
    {
      foreach (FileInfo file in AppUtils.GetDirInfo("editor_commands").GetFiles())
      {
        if (file.Extension == ".xtpc")
        {
          CommandForm.CommandFileObject commandFileObject = new CommandForm.CommandFileObject();
          commandFileObject.FileName = file.FullName;
          Stream io = (Stream) File.Open(file.FullName, System.IO.FileMode.Open, FileAccess.ReadWrite, FileShare.Read);
          RPFCommandFile rpfCommandFile = new RPFCommandFile(io);
          io.Close();
          io.Dispose();
          commandFileObject.CmdFile = rpfCommandFile;
          this.commandFileList.Items.Add((object) commandFileObject);
        }
      }
      this.AddDefaultOptions();
    }

    private void ClearFileList() => this.commandFileList.Items.Clear();

    private void AddDefaultOptions()
    {
      this.commandFileList.Items.Add((object) new CommandForm.CommandFileObject()
      {
        IsCreateNew = true
      });
      this.commandFileList.SelectedIndexChanged -= new EventHandler(this.commandFileList_SelectedIndexChanged);
      this.commandFileList.SelectedIndex = 0;
      this.commandFileList.SelectedIndexChanged += new EventHandler(this.commandFileList_SelectedIndexChanged);
      if (this.commandFileList.Items.Count <= 1)
        return;
      this.LoadSelectedCommandFileToView();
      this.commandsViewer.Enabled = true;
    }

    private void openRPFSelectFileNameButton_Click(object sender, EventArgs e)
    {
      OpenFileDialog openFileDialog = new OpenFileDialog();
      openFileDialog.Filter = "|*.rpf";
      openFileDialog.Title = "Choose RPF For Command..";
      if (openFileDialog.ShowDialog() != DialogResult.OK)
        return;
      this.openRPFFileNameTextBox.Text = openFileDialog.FileName;
    }

    private void addOpenRPFCommandButton_Click(object sender, EventArgs e)
    {
      ((CommandForm.CommandFileObject) this.commandFileList.SelectedItem).CmdFile.Commands.Add((RPFCommandFile.Command) new RPFCommandFile.OpenRPFCommand());
      this.LoadSelectedCommandFileToView();
    }

    private void addCloseRPFCommandButton_Click(object sender, EventArgs e)
    {
      ((CommandForm.CommandFileObject) this.commandFileList.SelectedItem).CmdFile.Commands.Add((RPFCommandFile.Command) new RPFCommandFile.CloseRPFCommand());
      this.LoadSelectedCommandFileToView();
    }

    private void addExtractFileCommandButton_Click(object sender, EventArgs e)
    {
      ((CommandForm.CommandFileObject) this.commandFileList.SelectedItem).CmdFile.Commands.Add((RPFCommandFile.Command) new RPFCommandFile.ExtractFileCommand());
      this.LoadSelectedCommandFileToView();
    }

    private void addImportReplaceCommandButton_Click(object sender, EventArgs e)
    {
      ((CommandForm.CommandFileObject) this.commandFileList.SelectedItem).CmdFile.Commands.Add((RPFCommandFile.Command) new RPFCommandFile.ImportReplaceCommand());
      this.LoadSelectedCommandFileToView();
    }

    private void addSaveRPFCommandButton_Click(object sender, EventArgs e)
    {
      ((CommandForm.CommandFileObject) this.commandFileList.SelectedItem).CmdFile.Commands.Add((RPFCommandFile.Command) new RPFCommandFile.SaveRPFCommand());
      this.LoadSelectedCommandFileToView();
    }

    private void addCreateDirCommandButton_Click(object sender, EventArgs e)
    {
      ((CommandForm.CommandFileObject) this.commandFileList.SelectedItem).CmdFile.Commands.Add((RPFCommandFile.Command) new RPFCommandFile.CreateDirectoryCommand());
      this.LoadSelectedCommandFileToView();
    }

    private void saveButton_Click(object sender, EventArgs e)
    {
      CommandForm.CommandFileObject selectedItem = (CommandForm.CommandFileObject) this.commandFileList.SelectedItem;
      selectedItem.CmdFile.Commands.Clear();
      foreach (BetterListViewElementBase listViewElementBase in (BetterListViewElementCollection<BetterListViewItem>) this.commandsViewer.Items)
      {
        RPFCommandFile.Command tag = listViewElementBase.Tag as RPFCommandFile.Command;
        selectedItem.CmdFile.Commands.Add(tag);
      }
      PikIO io = new PikIO((Stream) File.Open(selectedItem.FileName, System.IO.FileMode.OpenOrCreate, FileAccess.ReadWrite), PikIO.Endianess.Little);
      selectedItem.CmdFile.Write(io);
      io.Flush();
      io.Close();
      SystemSounds.Asterisk.Play();
    }

    private void extractFileOutputPathButton_Click(object sender, EventArgs e)
    {
      FolderBrowserDialog folderBrowserDialog = new FolderBrowserDialog();
      folderBrowserDialog.ShowNewFolderButton = true;
      if (folderBrowserDialog.ShowDialog() != DialogResult.OK)
        return;
      this.extractFileOutputPathTextBox.Text = folderBrowserDialog.SelectedPath;
    }

    private void applyOpenRPFCommandData_Click(object sender, EventArgs e)
    {
      ((RPFCommandFile.OpenRPFCommand) this.CurrentCommand).RPFFileName = this.openRPFFileNameTextBox.Text;
      SystemSounds.Asterisk.Play();
    }

    private void extractFileApply_Click(object sender, EventArgs e)
    {
      ((RPFCommandFile.ExtractFileCommand) this.CurrentCommand).RPFFileName = this.extractFileFilePathInRPFTextBox.Text;
      ((RPFCommandFile.ExtractFileCommand) this.CurrentCommand).OutFileName = this.extractFileOutputPathTextBox.Text;
      SystemSounds.Asterisk.Play();
    }

    private void importReplaceAppyButton_Click(object sender, EventArgs e)
    {
      ((RPFCommandFile.ImportReplaceCommand) this.CurrentCommand).RPFFileName = this.importReplaceRPFFileNameTextBox.Text;
      ((RPFCommandFile.ImportReplaceCommand) this.CurrentCommand).InFileName = this.importReplaceInputFileNameTextBox.Text;
      ((RPFCommandFile.ImportReplaceCommand) this.CurrentCommand).KeepOffset = this.importReplaceKeepOffset.Checked;
      ((RPFCommandFile.ImportReplaceCommand) this.CurrentCommand).Compress = this.importReplaceCompress.Checked;
      ((RPFCommandFile.ImportReplaceCommand) this.CurrentCommand).KeepName = this.importReplaceKeepName.Checked;
      SystemSounds.Asterisk.Play();
    }

    private void saveRPFApplyButton_Click(object sender, EventArgs e)
    {
      ((RPFCommandFile.SaveRPFCommand) this.CurrentCommand).OutRPFFile = this.saveRPFFileNameTextBox.Text;
      ((RPFCommandFile.SaveRPFCommand) this.CurrentCommand).SaveInOffsetOrder = this.saveRPFWriteInorderCheck.Checked;
      SystemSounds.Asterisk.Play();
    }

    private void createDirApply_Click(object sender, EventArgs e)
    {
      ((RPFCommandFile.CreateDirectoryCommand) this.CurrentCommand).ParentDir = this.createDirParentNameTextBox.Text;
      ((RPFCommandFile.CreateDirectoryCommand) this.CurrentCommand).DirName = this.createDirDirNameTextBox.Text;
      SystemSounds.Asterisk.Play();
    }

    private void saveRPFChooseFileButton_Click(object sender, EventArgs e)
    {
      SaveFileDialog saveFileDialog = new SaveFileDialog();
      saveFileDialog.Title = "Choose output RPF...";
      saveFileDialog.Filter = "|*.rpf";
      if (saveFileDialog.ShowDialog() != DialogResult.OK)
        return;
      this.saveRPFFileNameTextBox.Text = saveFileDialog.FileName;
    }

    private void importReplaceChooseInputFileButton_Click(object sender, EventArgs e)
    {
      OpenFileDialog openFileDialog = new OpenFileDialog();
      openFileDialog.Title = "Choose Input File...";
      openFileDialog.Filter = "|*.*";
      openFileDialog.Multiselect = false;
      if (openFileDialog.ShowDialog() != DialogResult.OK)
        return;
      this.importReplaceInputFileNameTextBox.Text = openFileDialog.FileName;
    }

    private void removeCommandButton_Click(object sender, EventArgs e)
    {
      ((CommandForm.CommandFileObject) this.commandFileList.SelectedItem).CmdFile.Commands.Remove(this.commandsViewer.SelectedItems[0].Tag as RPFCommandFile.Command);
      this.commandsViewer.SelectedItems[0].Remove();
    }

    private void moveCommandUpButton_Click(object sender, EventArgs e)
    {
      if (this.commandsViewer.SelectedItems.Count < 1)
        return;
      int index = this.commandsViewer.SelectedItems[0].Index;
      if (index == 0)
        return;
      BetterListViewItem selectedItem = this.commandsViewer.SelectedItems[0];
      BetterListViewItem betterListViewItem = this.commandsViewer.Items[index - 1];
      this.commandsViewer.Items.Remove(selectedItem);
      this.commandsViewer.Items.Insert(betterListViewItem.Index, selectedItem);
    }

    private void moveCommandDownButton_Click(object sender, EventArgs e)
    {
      if (this.commandsViewer.SelectedItems.Count < 1)
        return;
      int index = this.commandsViewer.SelectedItems[0].Index;
      if (index == this.commandsViewer.Items.Count - 1)
        return;
      BetterListViewItem selectedItem = this.commandsViewer.SelectedItems[0];
      BetterListViewItem betterListViewItem = this.commandsViewer.Items[index + 1];
      this.commandsViewer.Items.Remove(selectedItem);
      this.commandsViewer.Items.Insert(betterListViewItem.Index + 1, selectedItem);
    }

    private void commandsViewer_SelectedIndexChanged(object sender, EventArgs e)
    {
      if (this.commandsViewer.SelectedItems.Count <= 0)
        return;
      this.LoadCommandData((RPFCommandFile.Command) this.commandsViewer.SelectedItems[0].Tag);
    }

    private void commandFileList_SelectedIndexChanged(object sender, EventArgs e)
    {
      CommandForm.CommandFileObject selectedItem = (CommandForm.CommandFileObject) this.commandFileList.SelectedItem;
      if (selectedItem.IsCreateNew)
      {
        this.commandsViewer.Enabled = false;
        SaveFileDialog saveFileDialog = new SaveFileDialog();
        saveFileDialog.Title = "Make New Command File..";
        saveFileDialog.Filter = "|*.xtpc";
        saveFileDialog.InitialDirectory = AppUtils.GetPath("editor_commands");
        if (saveFileDialog.ShowDialog() != DialogResult.OK)
          return;
        Stream xIn = (Stream) File.Create(saveFileDialog.FileName);
        RPFCommandFile rpfCommandFile = new RPFCommandFile();
        PikIO io = new PikIO(xIn, PikIO.Endianess.Little);
        rpfCommandFile.Write(io);
        io.Flush();
        io.Close();
        this.LoadCommandsDir();
      }
      else if (selectedItem.IsLoad)
      {
        this.commandsViewer.Enabled = false;
        OpenFileDialog openFileDialog = new OpenFileDialog();
        openFileDialog.Title = "Open Commands File...";
        openFileDialog.Filter = "|*.xtpc";
        if (openFileDialog.ShowDialog() != DialogResult.OK)
          ;
      }
      else
        this.LoadSelectedCommandFileToView();
    }

    private void commandMenu_Opening(object sender, CancelEventArgs e) => this.removeCommandButton.Enabled = this.commandsViewer.SelectedItems.Count > 0;

    protected override void Dispose(bool disposing)
    {
      if (disposing && this.components != null)
        this.components.Dispose();
      base.Dispose(disposing);
    }

    private void InitializeComponent()
    {
      this.components = (IContainer) new Container();
      ComponentResourceManager componentResourceManager = new ComponentResourceManager(typeof (CommandForm));
      this.titleLabel = new Label();
      this.panel1 = new Panel();
      this.label3 = new Label();
      this.commandFileList = new ComboBox();
      this.label2 = new Label();
      this.label1 = new Label();
      this.panel3 = new Panel();
      this.dataPanelExtractFile = new Panel();
      this.extractFileApply = new Button();
      this.extractFileOutputPathButton = new Button();
      this.extractFileOutputPathTextBox = new TextBox();
      this.label6 = new Label();
      this.extractFileFilePathInRPFTextBox = new TextBox();
      this.label5 = new Label();
      this.dataPanelOpenRPF = new Panel();
      this.applyOpenRPFCommandData = new Button();
      this.openRPFSelectFileNameButton = new Button();
      this.openRPFFileNameTextBox = new TextBox();
      this.label4 = new Label();
      this.commandsPanel = new Panel();
      this.saveButton = new Button();
      this.commandsViewer = new ComponentOwl.BetterListView.BetterListView();
      this.commandHeader = new BetterListViewColumnHeader();
      this.commandMenu = new ContextMenuStrip(this.components);
      this.addOpenRPFCommandButton = new ToolStripMenuItem();
      this.addExtractFileCommandButton = new ToolStripMenuItem();
      this.addCloseRPFCommandButton = new ToolStripMenuItem();
      this.dataPanelImportReplace = new Panel();
      this.importReplaceAppyButton = new Button();
      this.importReplaceChooseInputFileButton = new Button();
      this.importReplaceInputFileNameTextBox = new TextBox();
      this.label7 = new Label();
      this.importReplaceRPFFileNameTextBox = new TextBox();
      this.label8 = new Label();
      this.addImportReplaceCommandButton = new ToolStripMenuItem();
      this.label9 = new Label();
      this.label10 = new Label();
      this.label11 = new Label();
      this.importReplaceKeepOffset = new CheckBox();
      this.importReplaceCompress = new CheckBox();
      this.moveCommandUpButton = new Button();
      this.moveCommandDownButton = new Button();
      this.toolStripSeparator1 = new ToolStripSeparator();
      this.removeCommandButton = new ToolStripMenuItem();
      this.dataPanelSaveRPF = new Panel();
      this.label12 = new Label();
      this.saveRPFApplyButton = new Button();
      this.saveRPFChooseFileButton = new Button();
      this.saveRPFFileNameTextBox = new TextBox();
      this.label13 = new Label();
      this.addSaveRPFCommandButton = new ToolStripMenuItem();
      this.importReplaceKeepName = new CheckBox();
      this.dataPanelCreateDir = new Panel();
      this.label14 = new Label();
      this.createDirApply = new Button();
      this.createDirDirNameTextBox = new TextBox();
      this.label15 = new Label();
      this.createDirParentNameTextBox = new TextBox();
      this.label16 = new Label();
      this.addCreateDirCommandButton = new ToolStripMenuItem();
      this.saveRPFWriteInorderCheck = new CheckBox();
      this.panel1.SuspendLayout();
      this.panel3.SuspendLayout();
      this.dataPanelExtractFile.SuspendLayout();
      this.dataPanelOpenRPF.SuspendLayout();
      this.commandsPanel.SuspendLayout();
      ((ISupportInitialize) this.commandsViewer).BeginInit();
      this.commandMenu.SuspendLayout();
      this.dataPanelImportReplace.SuspendLayout();
      this.dataPanelSaveRPF.SuspendLayout();
      this.dataPanelCreateDir.SuspendLayout();
      this.SuspendLayout();
      this.titleLabel.AutoSize = true;
      this.titleLabel.Location = new Point(4, 2);
      this.titleLabel.Margin = new Padding(15, 0, 15, 0);
      this.titleLabel.Name = "titleLabel";
      this.titleLabel.Size = new Size(136, 32);
      this.titleLabel.TabIndex = 1;
      this.titleLabel.Text = "Commands";
      this.panel1.Controls.Add((Control) this.label3);
      this.panel1.Controls.Add((Control) this.commandFileList);
      this.panel1.Controls.Add((Control) this.label2);
      this.panel1.Controls.Add((Control) this.label1);
      this.panel1.Controls.Add((Control) this.titleLabel);
      this.panel1.Dock = DockStyle.Top;
      this.panel1.Location = new Point(0, 0);
      this.panel1.Name = "panel1";
      this.panel1.Size = new Size(703, 41);
      this.panel1.TabIndex = 2;
      this.label3.AutoSize = true;
      this.label3.Cursor = Cursors.Hand;
      this.label3.Font = new Font("Segoe UI", 10f, FontStyle.Underline, GraphicsUnit.Point, (byte) 0);
      this.label3.Location = new Point(340, 13);
      this.label3.Margin = new Padding(15, 0, 15, 0);
      this.label3.Name = "label3";
      this.label3.Size = new Size(54, 19);
      this.label3.TabIndex = 5;
      this.label3.Text = "Refresh";
      this.commandFileList.DropDownStyle = ComboBoxStyle.DropDownList;
      this.commandFileList.Font = new Font("Segoe UI", 9f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.commandFileList.FormattingEnabled = true;
      this.commandFileList.Location = new Point(187, 11);
      this.commandFileList.Name = "commandFileList";
      this.commandFileList.Size = new Size(151, 23);
      this.commandFileList.TabIndex = 4;
      this.commandFileList.SelectedIndexChanged += new EventHandler(this.commandFileList_SelectedIndexChanged);
      this.label2.AutoSize = true;
      this.label2.Font = new Font("Segoe UI", 10f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.label2.Location = new Point(155, 13);
      this.label2.Margin = new Padding(15, 0, 15, 0);
      this.label2.Name = "label2";
      this.label2.Size = new Size(29, 19);
      this.label2.TabIndex = 3;
      this.label2.Text = "File";
      this.label1.AutoSize = true;
      this.label1.Location = new Point(435, 4);
      this.label1.Margin = new Padding(15, 0, 15, 0);
      this.label1.Name = "label1";
      this.label1.Size = new Size(240, 32);
      this.label1.TabIndex = 2;
      this.label1.Text = "Command Properties";
      this.panel3.Controls.Add((Control) this.dataPanelCreateDir);
      this.panel3.Controls.Add((Control) this.dataPanelSaveRPF);
      this.panel3.Controls.Add((Control) this.dataPanelImportReplace);
      this.panel3.Controls.Add((Control) this.dataPanelExtractFile);
      this.panel3.Controls.Add((Control) this.dataPanelOpenRPF);
      this.panel3.Controls.Add((Control) this.commandsPanel);
      this.panel3.Dock = DockStyle.Fill;
      this.panel3.Location = new Point(0, 41);
      this.panel3.Name = "panel3";
      this.panel3.Size = new Size(703, 539);
      this.panel3.TabIndex = 0;
      this.dataPanelExtractFile.BorderStyle = BorderStyle.FixedSingle;
      this.dataPanelExtractFile.Controls.Add((Control) this.label11);
      this.dataPanelExtractFile.Controls.Add((Control) this.extractFileApply);
      this.dataPanelExtractFile.Controls.Add((Control) this.extractFileOutputPathButton);
      this.dataPanelExtractFile.Controls.Add((Control) this.extractFileOutputPathTextBox);
      this.dataPanelExtractFile.Controls.Add((Control) this.label6);
      this.dataPanelExtractFile.Controls.Add((Control) this.extractFileFilePathInRPFTextBox);
      this.dataPanelExtractFile.Controls.Add((Control) this.label5);
      this.dataPanelExtractFile.Location = new Point(681, 449);
      this.dataPanelExtractFile.Name = "dataPanelExtractFile";
      this.dataPanelExtractFile.Size = new Size(295, 914);
      this.dataPanelExtractFile.TabIndex = 2;
      this.dataPanelExtractFile.Visible = false;
      this.extractFileApply.FlatStyle = FlatStyle.Popup;
      this.extractFileApply.Font = new Font("Segoe UI", 9f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.extractFileApply.Location = new Point(11, 162);
      this.extractFileApply.Name = "extractFileApply";
      this.extractFileApply.Size = new Size(275, 23);
      this.extractFileApply.TabIndex = 6;
      this.extractFileApply.Text = "Apply";
      this.extractFileApply.UseVisualStyleBackColor = true;
      this.extractFileApply.Click += new EventHandler(this.extractFileApply_Click);
      this.extractFileOutputPathButton.FlatStyle = FlatStyle.Popup;
      this.extractFileOutputPathButton.Font = new Font("Segoe UI", 9f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.extractFileOutputPathButton.Location = new Point(257, 132);
      this.extractFileOutputPathButton.Name = "extractFileOutputPathButton";
      this.extractFileOutputPathButton.Size = new Size(29, 23);
      this.extractFileOutputPathButton.TabIndex = 5;
      this.extractFileOutputPathButton.Text = "...";
      this.extractFileOutputPathButton.UseVisualStyleBackColor = true;
      this.extractFileOutputPathButton.Click += new EventHandler(this.extractFileOutputPathButton_Click);
      this.extractFileOutputPathTextBox.Font = new Font("Segoe UI", 10f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.extractFileOutputPathTextBox.Location = new Point(11, 131);
      this.extractFileOutputPathTextBox.Name = "extractFileOutputPathTextBox";
      this.extractFileOutputPathTextBox.Size = new Size(237, 25);
      this.extractFileOutputPathTextBox.TabIndex = 4;
      this.label6.AutoSize = true;
      this.label6.Location = new Point(5, 96);
      this.label6.Name = "label6";
      this.label6.Size = new Size(144, 32);
      this.label6.TabIndex = 3;
      this.label6.Text = "Output Path";
      this.extractFileFilePathInRPFTextBox.Font = new Font("Segoe UI", 10f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.extractFileFilePathInRPFTextBox.Location = new Point(11, 68);
      this.extractFileFilePathInRPFTextBox.Name = "extractFileFilePathInRPFTextBox";
      this.extractFileFilePathInRPFTextBox.Size = new Size(275, 25);
      this.extractFileFilePathInRPFTextBox.TabIndex = 2;
      this.label5.AutoSize = true;
      this.label5.Location = new Point(5, 33);
      this.label5.Name = "label5";
      this.label5.Size = new Size(178, 32);
      this.label5.TabIndex = 1;
      this.label5.Text = "File Path In RPF";
      this.dataPanelOpenRPF.BorderStyle = BorderStyle.FixedSingle;
      this.dataPanelOpenRPF.Controls.Add((Control) this.label10);
      this.dataPanelOpenRPF.Controls.Add((Control) this.applyOpenRPFCommandData);
      this.dataPanelOpenRPF.Controls.Add((Control) this.openRPFSelectFileNameButton);
      this.dataPanelOpenRPF.Controls.Add((Control) this.openRPFFileNameTextBox);
      this.dataPanelOpenRPF.Controls.Add((Control) this.label4);
      this.dataPanelOpenRPF.Location = new Point(1296, 449);
      this.dataPanelOpenRPF.Name = "dataPanelOpenRPF";
      this.dataPanelOpenRPF.Size = new Size(303, 585);
      this.dataPanelOpenRPF.TabIndex = 1;
      this.dataPanelOpenRPF.Visible = false;
      this.applyOpenRPFCommandData.FlatStyle = FlatStyle.Popup;
      this.applyOpenRPFCommandData.Font = new Font("Segoe UI", 9f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.applyOpenRPFCommandData.Location = new Point(11, 99);
      this.applyOpenRPFCommandData.Name = "applyOpenRPFCommandData";
      this.applyOpenRPFCommandData.Size = new Size(281, 23);
      this.applyOpenRPFCommandData.TabIndex = 3;
      this.applyOpenRPFCommandData.Text = "Apply";
      this.applyOpenRPFCommandData.UseVisualStyleBackColor = true;
      this.applyOpenRPFCommandData.Click += new EventHandler(this.applyOpenRPFCommandData_Click);
      this.openRPFSelectFileNameButton.FlatStyle = FlatStyle.Popup;
      this.openRPFSelectFileNameButton.Font = new Font("Segoe UI", 9f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.openRPFSelectFileNameButton.Location = new Point(263, 69);
      this.openRPFSelectFileNameButton.Name = "openRPFSelectFileNameButton";
      this.openRPFSelectFileNameButton.Size = new Size(29, 23);
      this.openRPFSelectFileNameButton.TabIndex = 2;
      this.openRPFSelectFileNameButton.Text = "...";
      this.openRPFSelectFileNameButton.UseVisualStyleBackColor = true;
      this.openRPFSelectFileNameButton.Click += new EventHandler(this.openRPFSelectFileNameButton_Click);
      this.openRPFFileNameTextBox.Font = new Font("Segoe UI", 10f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.openRPFFileNameTextBox.Location = new Point(11, 68);
      this.openRPFFileNameTextBox.Name = "openRPFFileNameTextBox";
      this.openRPFFileNameTextBox.Size = new Size(246, 25);
      this.openRPFFileNameTextBox.TabIndex = 1;
      this.label4.AutoSize = true;
      this.label4.Location = new Point(5, 33);
      this.label4.Name = "label4";
      this.label4.Size = new Size(169, 32);
      this.label4.TabIndex = 0;
      this.label4.Text = "RPF File Name";
      this.commandsPanel.BorderStyle = BorderStyle.FixedSingle;
      this.commandsPanel.Controls.Add((Control) this.moveCommandDownButton);
      this.commandsPanel.Controls.Add((Control) this.moveCommandUpButton);
      this.commandsPanel.Controls.Add((Control) this.saveButton);
      this.commandsPanel.Controls.Add((Control) this.commandsViewer);
      this.commandsPanel.Dock = DockStyle.Left;
      this.commandsPanel.Location = new Point(0, 0);
      this.commandsPanel.Name = "commandsPanel";
      this.commandsPanel.Size = new Size(397, 539);
      this.commandsPanel.TabIndex = 0;
      this.saveButton.FlatStyle = FlatStyle.Popup;
      this.saveButton.Font = new Font("Segoe UI", 9f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.saveButton.Location = new Point(6, 5);
      this.saveButton.Name = "saveButton";
      this.saveButton.Size = new Size(75, 23);
      this.saveButton.TabIndex = 1;
      this.saveButton.Text = "Save";
      this.saveButton.UseVisualStyleBackColor = true;
      this.saveButton.Click += new EventHandler(this.saveButton_Click);
      this.commandsViewer.Columns.Add(this.commandHeader);
      this.commandsViewer.ContextMenuStrip = this.commandMenu;
      this.commandsViewer.Dock = DockStyle.Bottom;
      this.commandsViewer.Enabled = false;
      this.commandsViewer.GridLines = BetterListViewGridLines.Grid;
      this.commandsViewer.Location = new Point(0, 33);
      this.commandsViewer.MultiSelect = false;
      this.commandsViewer.Name = "commandsViewer";
      this.commandsViewer.Size = new Size(395, 504);
      this.commandsViewer.TabIndex = 0;
      this.commandsViewer.SelectedIndexChanged += new EventHandler(this.commandsViewer_SelectedIndexChanged);
      this.commandHeader.Font = new Font("Segoe UI", 12f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.commandHeader.Name = "commandHeader";
      this.commandHeader.Text = "Command";
      this.commandHeader.Width = 394;
      this.commandMenu.Items.AddRange(new ToolStripItem[8]
      {
        (ToolStripItem) this.addOpenRPFCommandButton,
        (ToolStripItem) this.addCreateDirCommandButton,
        (ToolStripItem) this.addImportReplaceCommandButton,
        (ToolStripItem) this.addExtractFileCommandButton,
        (ToolStripItem) this.addSaveRPFCommandButton,
        (ToolStripItem) this.addCloseRPFCommandButton,
        (ToolStripItem) this.toolStripSeparator1,
        (ToolStripItem) this.removeCommandButton
      });
      this.commandMenu.Name = "commandMenu";
      this.commandMenu.Size = new Size(242, 164);
      this.commandMenu.Opening += new CancelEventHandler(this.commandMenu_Opening);
      this.addOpenRPFCommandButton.Name = "addOpenRPFCommandButton";
      this.addOpenRPFCommandButton.Size = new Size(241, 22);
      this.addOpenRPFCommandButton.Text = "Add OpenRPF Command";
      this.addOpenRPFCommandButton.Click += new EventHandler(this.addOpenRPFCommandButton_Click);
      this.addExtractFileCommandButton.Name = "addExtractFileCommandButton";
      this.addExtractFileCommandButton.Size = new Size(241, 22);
      this.addExtractFileCommandButton.Text = "Add Extract File Command";
      this.addExtractFileCommandButton.Click += new EventHandler(this.addExtractFileCommandButton_Click);
      this.addCloseRPFCommandButton.Name = "addCloseRPFCommandButton";
      this.addCloseRPFCommandButton.Size = new Size(241, 22);
      this.addCloseRPFCommandButton.Text = "Add Close RPF Command";
      this.addCloseRPFCommandButton.Click += new EventHandler(this.addCloseRPFCommandButton_Click);
      this.dataPanelImportReplace.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
      this.dataPanelImportReplace.BorderStyle = BorderStyle.FixedSingle;
      this.dataPanelImportReplace.Controls.Add((Control) this.importReplaceKeepName);
      this.dataPanelImportReplace.Controls.Add((Control) this.importReplaceCompress);
      this.dataPanelImportReplace.Controls.Add((Control) this.importReplaceKeepOffset);
      this.dataPanelImportReplace.Controls.Add((Control) this.label9);
      this.dataPanelImportReplace.Controls.Add((Control) this.importReplaceAppyButton);
      this.dataPanelImportReplace.Controls.Add((Control) this.importReplaceChooseInputFileButton);
      this.dataPanelImportReplace.Controls.Add((Control) this.importReplaceInputFileNameTextBox);
      this.dataPanelImportReplace.Controls.Add((Control) this.label7);
      this.dataPanelImportReplace.Controls.Add((Control) this.importReplaceRPFFileNameTextBox);
      this.dataPanelImportReplace.Controls.Add((Control) this.label8);
      this.dataPanelImportReplace.Location = new Point(1605, 449);
      this.dataPanelImportReplace.Name = "dataPanelImportReplace";
      this.dataPanelImportReplace.Size = new Size(0, 449);
      this.dataPanelImportReplace.TabIndex = 3;
      this.dataPanelImportReplace.Visible = false;
      this.importReplaceAppyButton.FlatStyle = FlatStyle.Popup;
      this.importReplaceAppyButton.Font = new Font("Segoe UI", 9f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.importReplaceAppyButton.Location = new Point(11, 215);
      this.importReplaceAppyButton.Name = "importReplaceAppyButton";
      this.importReplaceAppyButton.Size = new Size(275, 23);
      this.importReplaceAppyButton.TabIndex = 6;
      this.importReplaceAppyButton.Text = "Apply";
      this.importReplaceAppyButton.UseVisualStyleBackColor = true;
      this.importReplaceAppyButton.Click += new EventHandler(this.importReplaceAppyButton_Click);
      this.importReplaceChooseInputFileButton.FlatStyle = FlatStyle.Popup;
      this.importReplaceChooseInputFileButton.Font = new Font("Segoe UI", 9f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.importReplaceChooseInputFileButton.Location = new Point(257, 132);
      this.importReplaceChooseInputFileButton.Name = "importReplaceChooseInputFileButton";
      this.importReplaceChooseInputFileButton.Size = new Size(29, 23);
      this.importReplaceChooseInputFileButton.TabIndex = 5;
      this.importReplaceChooseInputFileButton.Text = "...";
      this.importReplaceChooseInputFileButton.UseVisualStyleBackColor = true;
      this.importReplaceChooseInputFileButton.Click += new EventHandler(this.importReplaceChooseInputFileButton_Click);
      this.importReplaceInputFileNameTextBox.Font = new Font("Segoe UI", 10f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.importReplaceInputFileNameTextBox.Location = new Point(11, 131);
      this.importReplaceInputFileNameTextBox.Name = "importReplaceInputFileNameTextBox";
      this.importReplaceInputFileNameTextBox.Size = new Size(237, 25);
      this.importReplaceInputFileNameTextBox.TabIndex = 4;
      this.label7.AutoSize = true;
      this.label7.Location = new Point(5, 96);
      this.label7.Name = "label7";
      this.label7.Size = new Size(115, 32);
      this.label7.TabIndex = 3;
      this.label7.Text = "Input File";
      this.importReplaceRPFFileNameTextBox.Font = new Font("Segoe UI", 10f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.importReplaceRPFFileNameTextBox.Location = new Point(11, 68);
      this.importReplaceRPFFileNameTextBox.Name = "importReplaceRPFFileNameTextBox";
      this.importReplaceRPFFileNameTextBox.Size = new Size(275, 25);
      this.importReplaceRPFFileNameTextBox.TabIndex = 2;
      this.label8.AutoSize = true;
      this.label8.Location = new Point(5, 33);
      this.label8.Name = "label8";
      this.label8.Size = new Size(178, 32);
      this.label8.TabIndex = 1;
      this.label8.Text = "File Path In RPF";
      this.addImportReplaceCommandButton.Name = "addImportReplaceCommandButton";
      this.addImportReplaceCommandButton.Size = new Size(241, 22);
      this.addImportReplaceCommandButton.Text = "Add Import/Replace Command";
      this.addImportReplaceCommandButton.Click += new EventHandler(this.addImportReplaceCommandButton_Click);
      this.label9.AutoSize = true;
      this.label9.Font = new Font("Segoe UI", 12f, FontStyle.Underline, GraphicsUnit.Point, (byte) 0);
      this.label9.Location = new Point(6, 10);
      this.label9.Name = "label9";
      this.label9.Size = new Size(194, 21);
      this.label9.TabIndex = 7;
      this.label9.Text = "Import/Replace Command";
      this.label10.AutoSize = true;
      this.label10.Font = new Font("Segoe UI", 12f, FontStyle.Underline, GraphicsUnit.Point, (byte) 0);
      this.label10.Location = new Point(6, 10);
      this.label10.Name = "label10";
      this.label10.Size = new Size(156, 21);
      this.label10.TabIndex = 8;
      this.label10.Text = "Open RPF Command";
      this.label11.AutoSize = true;
      this.label11.Font = new Font("Segoe UI", 12f, FontStyle.Underline, GraphicsUnit.Point, (byte) 0);
      this.label11.Location = new Point(6, 10);
      this.label11.Name = "label11";
      this.label11.Size = new Size(161, 21);
      this.label11.TabIndex = 8;
      this.label11.Text = "Extract File Command";
      this.importReplaceKeepOffset.AutoSize = true;
      this.importReplaceKeepOffset.Font = new Font("Segoe UI", 12f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.importReplaceKeepOffset.Location = new Point(11, 162);
      this.importReplaceKeepOffset.Name = "importReplaceKeepOffset";
      this.importReplaceKeepOffset.Size = new Size(109, 25);
      this.importReplaceKeepOffset.TabIndex = 8;
      this.importReplaceKeepOffset.Text = "Keep Offset";
      this.importReplaceKeepOffset.UseVisualStyleBackColor = true;
      this.importReplaceCompress.AutoSize = true;
      this.importReplaceCompress.Font = new Font("Segoe UI", 12f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.importReplaceCompress.Location = new Point(11, 184);
      this.importReplaceCompress.Name = "importReplaceCompress";
      this.importReplaceCompress.Size = new Size(99, 25);
      this.importReplaceCompress.TabIndex = 9;
      this.importReplaceCompress.Text = "Compress";
      this.importReplaceCompress.UseVisualStyleBackColor = true;
      this.moveCommandUpButton.FlatStyle = FlatStyle.Popup;
      this.moveCommandUpButton.Font = new Font("Segoe UI", 9f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.moveCommandUpButton.Image = (Image) componentResourceManager.GetObject("moveCommandUpButton.Image");
      this.moveCommandUpButton.Location = new Point(335, 5);
      this.moveCommandUpButton.Name = "moveCommandUpButton";
      this.moveCommandUpButton.Size = new Size(27, 23);
      this.moveCommandUpButton.TabIndex = 2;
      this.moveCommandUpButton.UseVisualStyleBackColor = true;
      this.moveCommandUpButton.Click += new EventHandler(this.moveCommandUpButton_Click);
      this.moveCommandDownButton.FlatStyle = FlatStyle.Popup;
      this.moveCommandDownButton.Font = new Font("Segoe UI", 9f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.moveCommandDownButton.Image = (Image) componentResourceManager.GetObject("moveCommandDownButton.Image");
      this.moveCommandDownButton.Location = new Point(365, 5);
      this.moveCommandDownButton.Name = "moveCommandDownButton";
      this.moveCommandDownButton.Size = new Size(27, 23);
      this.moveCommandDownButton.TabIndex = 3;
      this.moveCommandDownButton.UseVisualStyleBackColor = true;
      this.moveCommandDownButton.Click += new EventHandler(this.moveCommandDownButton_Click);
      this.toolStripSeparator1.Name = "toolStripSeparator1";
      this.toolStripSeparator1.Size = new Size(238, 6);
      this.removeCommandButton.Name = "removeCommandButton";
      this.removeCommandButton.Size = new Size(241, 22);
      this.removeCommandButton.Text = "Remove Command";
      this.removeCommandButton.Click += new EventHandler(this.removeCommandButton_Click);
      this.dataPanelSaveRPF.BorderStyle = BorderStyle.FixedSingle;
      this.dataPanelSaveRPF.Controls.Add((Control) this.saveRPFWriteInorderCheck);
      this.dataPanelSaveRPF.Controls.Add((Control) this.label12);
      this.dataPanelSaveRPF.Controls.Add((Control) this.saveRPFApplyButton);
      this.dataPanelSaveRPF.Controls.Add((Control) this.saveRPFChooseFileButton);
      this.dataPanelSaveRPF.Controls.Add((Control) this.saveRPFFileNameTextBox);
      this.dataPanelSaveRPF.Controls.Add((Control) this.label13);
      this.dataPanelSaveRPF.Location = new Point(986, 449);
      this.dataPanelSaveRPF.Name = "dataPanelSaveRPF";
      this.dataPanelSaveRPF.Size = new Size(304, 585);
      this.dataPanelSaveRPF.TabIndex = 4;
      this.dataPanelSaveRPF.Visible = false;
      this.label12.AutoSize = true;
      this.label12.Font = new Font("Segoe UI", 12f, FontStyle.Underline, GraphicsUnit.Point, (byte) 0);
      this.label12.Location = new Point(6, 10);
      this.label12.Name = "label12";
      this.label12.Size = new Size(151, 21);
      this.label12.TabIndex = 8;
      this.label12.Text = "Save RPF Command";
      this.saveRPFApplyButton.FlatStyle = FlatStyle.Popup;
      this.saveRPFApplyButton.Font = new Font("Segoe UI", 9f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.saveRPFApplyButton.Location = new Point(11, 123);
      this.saveRPFApplyButton.Name = "saveRPFApplyButton";
      this.saveRPFApplyButton.Size = new Size(281, 23);
      this.saveRPFApplyButton.TabIndex = 3;
      this.saveRPFApplyButton.Text = "Apply";
      this.saveRPFApplyButton.UseVisualStyleBackColor = true;
      this.saveRPFApplyButton.Click += new EventHandler(this.saveRPFApplyButton_Click);
      this.saveRPFChooseFileButton.FlatStyle = FlatStyle.Popup;
      this.saveRPFChooseFileButton.Font = new Font("Segoe UI", 9f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.saveRPFChooseFileButton.Location = new Point(263, 69);
      this.saveRPFChooseFileButton.Name = "saveRPFChooseFileButton";
      this.saveRPFChooseFileButton.Size = new Size(29, 23);
      this.saveRPFChooseFileButton.TabIndex = 2;
      this.saveRPFChooseFileButton.Text = "...";
      this.saveRPFChooseFileButton.UseVisualStyleBackColor = true;
      this.saveRPFChooseFileButton.Click += new EventHandler(this.saveRPFChooseFileButton_Click);
      this.saveRPFFileNameTextBox.Font = new Font("Segoe UI", 10f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.saveRPFFileNameTextBox.Location = new Point(11, 68);
      this.saveRPFFileNameTextBox.Name = "saveRPFFileNameTextBox";
      this.saveRPFFileNameTextBox.Size = new Size(246, 25);
      this.saveRPFFileNameTextBox.TabIndex = 1;
      this.label13.AutoSize = true;
      this.label13.Location = new Point(5, 33);
      this.label13.Name = "label13";
      this.label13.Size = new Size(237, 32);
      this.label13.TabIndex = 0;
      this.label13.Text = "RPF File Name (save)";
      this.addSaveRPFCommandButton.Name = "addSaveRPFCommandButton";
      this.addSaveRPFCommandButton.Size = new Size(241, 22);
      this.addSaveRPFCommandButton.Text = "Add Save RPF Command";
      this.addSaveRPFCommandButton.Click += new EventHandler(this.addSaveRPFCommandButton_Click);
      this.importReplaceKeepName.AutoSize = true;
      this.importReplaceKeepName.Font = new Font("Segoe UI", 12f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.importReplaceKeepName.Location = new Point(118, 162);
      this.importReplaceKeepName.Name = "importReplaceKeepName";
      this.importReplaceKeepName.Size = new Size(109, 25);
      this.importReplaceKeepName.TabIndex = 10;
      this.importReplaceKeepName.Text = "Keep Name";
      this.importReplaceKeepName.UseVisualStyleBackColor = true;
      this.dataPanelCreateDir.BorderStyle = BorderStyle.FixedSingle;
      this.dataPanelCreateDir.Controls.Add((Control) this.label14);
      this.dataPanelCreateDir.Controls.Add((Control) this.createDirApply);
      this.dataPanelCreateDir.Controls.Add((Control) this.createDirDirNameTextBox);
      this.dataPanelCreateDir.Controls.Add((Control) this.label15);
      this.dataPanelCreateDir.Controls.Add((Control) this.createDirParentNameTextBox);
      this.dataPanelCreateDir.Controls.Add((Control) this.label16);
      this.dataPanelCreateDir.Location = new Point(382, 449);
      this.dataPanelCreateDir.Name = "dataPanelCreateDir";
      this.dataPanelCreateDir.Size = new Size(293, 914);
      this.dataPanelCreateDir.TabIndex = 5;
      this.dataPanelCreateDir.Visible = false;
      this.label14.AutoSize = true;
      this.label14.Font = new Font("Segoe UI", 12f, FontStyle.Underline, GraphicsUnit.Point, (byte) 0);
      this.label14.Location = new Point(6, 10);
      this.label14.Name = "label14";
      this.label14.Size = new Size(157, 21);
      this.label14.TabIndex = 7;
      this.label14.Text = "Create Dir Command";
      this.createDirApply.FlatStyle = FlatStyle.Popup;
      this.createDirApply.Font = new Font("Segoe UI", 9f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.createDirApply.Location = new Point(11, 162);
      this.createDirApply.Name = "createDirApply";
      this.createDirApply.Size = new Size(275, 23);
      this.createDirApply.TabIndex = 6;
      this.createDirApply.Text = "Apply";
      this.createDirApply.UseVisualStyleBackColor = true;
      this.createDirApply.Click += new EventHandler(this.createDirApply_Click);
      this.createDirDirNameTextBox.Font = new Font("Segoe UI", 10f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.createDirDirNameTextBox.Location = new Point(11, 131);
      this.createDirDirNameTextBox.Name = "createDirDirNameTextBox";
      this.createDirDirNameTextBox.Size = new Size(275, 25);
      this.createDirDirNameTextBox.TabIndex = 4;
      this.label15.AutoSize = true;
      this.label15.Location = new Point(5, 96);
      this.label15.Name = "label15";
      this.label15.Size = new Size(172, 32);
      this.label15.TabIndex = 3;
      this.label15.Text = "New Dir Name";
      this.createDirParentNameTextBox.Font = new Font("Segoe UI", 10f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.createDirParentNameTextBox.Location = new Point(11, 68);
      this.createDirParentNameTextBox.Name = "createDirParentNameTextBox";
      this.createDirParentNameTextBox.Size = new Size(275, 25);
      this.createDirParentNameTextBox.TabIndex = 2;
      this.label16.AutoSize = true;
      this.label16.Location = new Point(5, 33);
      this.label16.Name = "label16";
      this.label16.Size = new Size(284, 32);
      this.label16.TabIndex = 1;
      this.label16.Text = "RPF Parent (no end slash)";
      this.addCreateDirCommandButton.Name = "addCreateDirCommandButton";
      this.addCreateDirCommandButton.Size = new Size(241, 22);
      this.addCreateDirCommandButton.Text = "Add Create Dir Command";
      this.addCreateDirCommandButton.Click += new EventHandler(this.addCreateDirCommandButton_Click);
      this.saveRPFWriteInorderCheck.AutoSize = true;
      this.saveRPFWriteInorderCheck.Font = new Font("Segoe UI", 12f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.saveRPFWriteInorderCheck.Location = new Point(10, 95);
      this.saveRPFWriteInorderCheck.Name = "saveRPFWriteInorderCheck";
      this.saveRPFWriteInorderCheck.Size = new Size(175, 25);
      this.saveRPFWriteInorderCheck.TabIndex = 9;
      this.saveRPFWriteInorderCheck.Text = "Write in Offset Order";
      this.saveRPFWriteInorderCheck.UseVisualStyleBackColor = true;
      this.AutoScaleDimensions = new SizeF(13f, 32f);
      this.AutoScaleMode = AutoScaleMode.Font;
      this.ClientSize = new Size(703, 580);
      this.Controls.Add((Control) this.panel3);
      this.Controls.Add((Control) this.panel1);
      this.Font = new Font("Segoe UI", 18f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.FormBorderStyle = FormBorderStyle.FixedSingle;
      this.Margin = new Padding(6, 8, 6, 8);
      this.MaximizeBox = false;
      this.Name = nameof (CommandForm);
      this.ShowIcon = false;
      this.ShowInTaskbar = false;
      this.Text = "Commands Maker";
      this.panel1.ResumeLayout(false);
      this.panel1.PerformLayout();
      this.panel3.ResumeLayout(false);
      this.dataPanelExtractFile.ResumeLayout(false);
      this.dataPanelExtractFile.PerformLayout();
      this.dataPanelOpenRPF.ResumeLayout(false);
      this.dataPanelOpenRPF.PerformLayout();
      this.commandsPanel.ResumeLayout(false);
      ((ISupportInitialize) this.commandsViewer).EndInit();
      this.commandMenu.ResumeLayout(false);
      this.dataPanelImportReplace.ResumeLayout(false);
      this.dataPanelImportReplace.PerformLayout();
      this.dataPanelSaveRPF.ResumeLayout(false);
      this.dataPanelSaveRPF.PerformLayout();
      this.dataPanelCreateDir.ResumeLayout(false);
      this.dataPanelCreateDir.PerformLayout();
      this.ResumeLayout(false);
    }

    public class CommandFileObject
    {
      public bool IsCreateNew = false;
      public bool IsLoad = false;

      public RPFCommandFile CmdFile { get; set; }

      public string FileName { get; set; }

      public override string ToString() => this.IsCreateNew ? "<Create New>" : Path.GetFileName(this.FileName);
    }
  }
}
