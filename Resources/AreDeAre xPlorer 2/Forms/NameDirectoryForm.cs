using DevExpress.XtraEditors;
using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;

namespace AreDeAre_xPlorer_2.Forms
{
  public class NameDirectoryForm : XtraForm
  {
    private IContainer components = (IContainer) null;
    private Label label1;
    private Panel panel1;
    private Label label2;
    private SimpleButton createDirectoryButton;
    private TextEdit directoryNameBox;

    public string NewDirectoryName { get; set; }

    public NameDirectoryForm()
    {
      this.InitializeComponent();
      this.NewDirectoryName = string.Empty;
    }

    private void createDirectoryButton_Click(object sender, EventArgs e)
    {
      if (string.IsNullOrEmpty(this.directoryNameBox.Text))
        return;
      this.NewDirectoryName = this.directoryNameBox.Text;
      this.Close();
    }

    private void directoryNameBox_KeyUp(object sender, KeyEventArgs e)
    {
      if (e.KeyCode != Keys.Return && e.KeyCode != Keys.Return)
        return;
      this.createDirectoryButton_Click((object) this, (EventArgs) null);
    }

    protected override void Dispose(bool disposing)
    {
      if (disposing && this.components != null)
        this.components.Dispose();
      base.Dispose(disposing);
    }

    private void InitializeComponent()
    {
      this.label1 = new Label();
      this.panel1 = new Panel();
      this.label2 = new Label();
      this.createDirectoryButton = new SimpleButton();
      this.directoryNameBox = new TextEdit();
      this.panel1.SuspendLayout();
      this.directoryNameBox.Properties.BeginInit();
      this.SuspendLayout();
      this.label1.AutoSize = true;
      this.label1.Font = new Font("Arial", 18f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.label1.Location = new Point(12, 9);
      this.label1.Name = "label1";
      this.label1.Size = new Size(185, 27);
      this.label1.TabIndex = 0;
      this.label1.Text = "Create Directory";
      this.panel1.BorderStyle = BorderStyle.FixedSingle;
      this.panel1.Controls.Add((Control) this.directoryNameBox);
      this.panel1.Controls.Add((Control) this.label2);
      this.panel1.Location = new Point(17, 39);
      this.panel1.Name = "panel1";
      this.panel1.Size = new Size(302, 72);
      this.panel1.TabIndex = 1;
      this.label2.AutoSize = true;
      this.label2.Font = new Font("Arial", 13f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.label2.Location = new Point(9, 6);
      this.label2.Name = "label2";
      this.label2.Size = new Size(134, 21);
      this.label2.TabIndex = 3;
      this.label2.Text = "Directory Name";
      this.createDirectoryButton.AllowFocus = false;
      this.createDirectoryButton.Appearance.Font = new Font("Tahoma", 12f);
      this.createDirectoryButton.Appearance.Options.UseFont = true;
      this.createDirectoryButton.Location = new Point(17, 117);
      this.createDirectoryButton.Name = "createDirectoryButton";
      this.createDirectoryButton.Size = new Size(302, 33);
      this.createDirectoryButton.TabIndex = 2;
      this.createDirectoryButton.Text = "Create";
      this.createDirectoryButton.Click += new EventHandler(this.createDirectoryButton_Click);
      this.directoryNameBox.EditValue = (object) "";
      this.directoryNameBox.Location = new Point(13, 30);
      this.directoryNameBox.Name = "directoryNameBox";
      this.directoryNameBox.Properties.Appearance.Font = new Font("Tahoma", 13f);
      this.directoryNameBox.Properties.Appearance.Options.UseFont = true;
      this.directoryNameBox.Size = new Size(273, 28);
      this.directoryNameBox.TabIndex = 4;
      this.Appearance.Options.UseFont = true;
      this.AutoScaleMode = AutoScaleMode.None;
      this.ClientSize = new Size(331, 162);
      this.Controls.Add((Control) this.createDirectoryButton);
      this.Controls.Add((Control) this.panel1);
      this.Controls.Add((Control) this.label1);
      this.Font = new Font("Arial", 10f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.FormBorderStyle = FormBorderStyle.FixedToolWindow;
      this.LookAndFeel.SkinName = "Sharp";
      this.LookAndFeel.UseDefaultLookAndFeel = false;
      this.Name = nameof (NameDirectoryForm);
      this.ShowIcon = false;
      this.ShowInTaskbar = false;
      this.StartPosition = FormStartPosition.CenterParent;
      this.Text = "Create Directory";
      this.panel1.ResumeLayout(false);
      this.panel1.PerformLayout();
      this.directoryNameBox.Properties.EndInit();
      this.ResumeLayout(false);
      this.PerformLayout();
    }
  }
}
