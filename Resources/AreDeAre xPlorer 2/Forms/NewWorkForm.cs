using Pik.IO;
using RAGE;
using RAGE.ExtraClasses;
using System;
using System.ComponentModel;
using System.Drawing;
using System.IO;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace AreDeAre_xPlorer_2.Forms
{
  public class NewWorkForm : Form
  {
    public string CommandFile;
    public Exception OpenRPFException;
    public Exception SaveRPFException;
    public RPF6 OpenRPF6Return;
    public RPF6 RPFToSave;
    public RPF6 RPFToExportFilesFrom;
    public RPF6 RPFToLoadDirFrom;
    public Stream OpenRPFStream;
    public Stream SaveRPFStream;
    public Progress<RPF6Report> Prog;
    private IContainer components = (IContainer) null;
    private Label titleLabel;
    private Panel panel1;
    private Label statusLabel;
    private ProgressBar progBar;

    public bool Done { get; set; }

    public IProgress<RPF6Report> IProg => (IProgress<RPF6Report>) this.Prog;

    public NewWorkForm(Stream openRPFStream)
    {
      this.InitializeComponent();
      this.Prog = new Progress<RPF6Report>(new Action<RPF6Report>(this.ProgReport));
      this.OpenRPFStream = openRPFStream;
      this.DoOpenRPF();
    }

    public NewWorkForm(Stream saveRPFStream, RPF6 rpfToSave)
    {
      this.InitializeComponent();
      this.Prog = new Progress<RPF6Report>(new Action<RPF6Report>(this.ProgReport));
      this.SaveRPFStream = saveRPFStream;
      this.RPFToSave = rpfToSave;
      this.DoSaveRPF();
    }

    public NewWorkForm(RPFCommandFile cmdFile, Stream cmdStream)
    {
      this.InitializeComponent();
      this.Prog = new Progress<RPF6Report>(new Action<RPF6Report>(this.ProgReport));
      this.DoRunCommandFile(cmdFile, cmdStream);
    }

    private async void DoRunCommandFile(RPFCommandFile file, Stream cmdStream)
    {
      RPFCommandFile.OnOperation += new EventHandler<RPF6Report>(this.OnOperation);
      RPF6.OnOperation += new EventHandler<RPF6Report>(this.OnOperation);
      await Task.Factory.StartNew((Action) (() => file.ExecuteCommands()));
      RPFCommandFile.OnOperation -= new EventHandler<RPF6Report>(this.OnOperation);
      RPF6.OnOperation -= new EventHandler<RPF6Report>(this.OnOperation);
      cmdStream.Close();
      this.Done = true;
      this.Close();
    }

    private async void DoSaveRPF()
    {
      try
      {
        this.LoadEvents();
        await Task.Factory.StartNew((Action) (() => this.RPFToSave.Write(this.SaveRPFStream, AppGlobals.Settings.WriteFilesInOffsetOrder)));
        this.ClearEvents();
        this.Done = true;
        this.Close();
      }
      catch (Exception ex)
      {
        this.SaveRPFException = ex;
        this.ClearEvents();
      }
    }

    private async void DoOpenRPF()
    {
      try
      {
        this.LoadEvents();
        await Task.Factory.StartNew((Action) (() =>
        {
          this.OpenRPF6Return = RPF6.RPF6Header.HasIdentifier(new PikIO(this.OpenRPFStream, PikIO.Endianess.Big)) ? new RPF6(this.OpenRPFStream) : throw new Exception("RPF File does not have valid header magic");
        }));
        this.ClearEvents();
        this.Done = true;
        this.Close();
      }
      catch (Exception ex)
      {
        this.OpenRPFException = ex;
        this.ClearEvents();
      }
    }

    public void ProgReport(RPF6Report progreport)
    {
      this.titleLabel.Text = progreport.TitleText;
      this.statusLabel.Text = string.Format("{0} {1}", (object) progreport.StatusOperationText, (object) AppUtils.TruncString(progreport.StatusText, 28));
      this.progBar.Value = progreport.Percent;
      this.titleLabel.Invalidate();
      this.statusLabel.Invalidate();
      this.progBar.Invalidate();
      this.titleLabel.Update();
      this.progBar.Update();
      this.statusLabel.Update();
    }

    public void OnError(object sender, RPF6ErrorReport e)
    {
      int num = (int) MessageBox.Show(e.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
    }

    public void OnOperation(object sender, RPF6Report e) => this.IProg.Report(e);

    private void LoadEvents() => RPF6.OnOperation += new EventHandler<RPF6Report>(this.OnOperation);

    private void ClearEvents() => RPF6.OnOperation -= new EventHandler<RPF6Report>(this.OnOperation);

    protected override void Dispose(bool disposing)
    {
      if (disposing && this.components != null)
        this.components.Dispose();
      base.Dispose(disposing);
    }

    private void InitializeComponent()
    {
      this.titleLabel = new Label();
      this.panel1 = new Panel();
      this.progBar = new ProgressBar();
      this.statusLabel = new Label();
      this.panel1.SuspendLayout();
      this.SuspendLayout();
      this.titleLabel.AutoSize = true;
      this.titleLabel.Location = new Point(26, 22);
      this.titleLabel.Margin = new Padding(7, 0, 7, 0);
      this.titleLabel.Name = "titleLabel";
      this.titleLabel.Size = new Size(123, 32);
      this.titleLabel.TabIndex = 0;
      this.titleLabel.Text = "WORKING";
      this.panel1.BorderStyle = BorderStyle.FixedSingle;
      this.panel1.Controls.Add((Control) this.progBar);
      this.panel1.Controls.Add((Control) this.statusLabel);
      this.panel1.Location = new Point(32, 57);
      this.panel1.Name = "panel1";
      this.panel1.Size = new Size(399, 81);
      this.panel1.TabIndex = 1;
      this.progBar.Location = new Point(20, 42);
      this.progBar.Name = "progBar";
      this.progBar.Size = new Size(360, 23);
      this.progBar.TabIndex = 3;
      this.statusLabel.AutoSize = true;
      this.statusLabel.Font = new Font("Segoe UI", 15f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.statusLabel.Location = new Point(15, 11);
      this.statusLabel.Margin = new Padding(7, 0, 7, 0);
      this.statusLabel.Name = "statusLabel";
      this.statusLabel.Size = new Size(112, 28);
      this.statusLabel.TabIndex = 2;
      this.statusLabel.Text = "Status STAT";
      this.AutoScaleDimensions = new SizeF(13f, 32f);
      this.AutoScaleMode = AutoScaleMode.Font;
      this.ClientSize = new Size(468, 161);
      this.Controls.Add((Control) this.panel1);
      this.Controls.Add((Control) this.titleLabel);
      this.DoubleBuffered = true;
      this.Font = new Font("Segoe UI", 18f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.FormBorderStyle = FormBorderStyle.None;
      this.Margin = new Padding(7);
      this.Name = nameof (NewWorkForm);
      this.ShowInTaskbar = false;
      this.StartPosition = FormStartPosition.CenterParent;
      this.Text = nameof (NewWorkForm);
      this.panel1.ResumeLayout(false);
      this.panel1.PerformLayout();
      this.ResumeLayout(false);
      this.PerformLayout();
    }
  }
}
