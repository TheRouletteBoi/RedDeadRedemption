using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;

namespace AreDeAre_xPlorer_2.Forms
{
  public class SettingsForm : Form
  {
    private IContainer components = (IContainer) null;
    private Label label11;
    private Panel panel1;
    private CheckBox checkBox1;
    private Label label1;

    public SettingsForm() => this.InitializeComponent();

    protected override void Dispose(bool disposing)
    {
      if (disposing && this.components != null)
        this.components.Dispose();
      base.Dispose(disposing);
    }

    private void InitializeComponent()
    {
      this.label11 = new Label();
      this.panel1 = new Panel();
      this.label1 = new Label();
      this.checkBox1 = new CheckBox();
      this.panel1.SuspendLayout();
      this.SuspendLayout();
      this.label11.AutoSize = true;
      this.label11.Font = new Font("Segoe UI", 18f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.label11.Location = new Point(12, 9);
      this.label11.Name = "label11";
      this.label11.Size = new Size(101, 32);
      this.label11.TabIndex = 1;
      this.label11.Text = "Settings";
      this.panel1.BorderStyle = BorderStyle.FixedSingle;
      this.panel1.Controls.Add((Control) this.checkBox1);
      this.panel1.Controls.Add((Control) this.label1);
      this.panel1.Location = new Point(18, 44);
      this.panel1.Name = "panel1";
      this.panel1.Size = new Size(453, 357);
      this.panel1.TabIndex = 2;
      this.label1.AutoSize = true;
      this.label1.Font = new Font("Segoe UI", 18f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.label1.Location = new Point(15, 193);
      this.label1.Name = "label1";
      this.label1.Size = new Size(180, 32);
      this.label1.TabIndex = 3;
      this.label1.Text = "Debug Settings";
      this.checkBox1.AutoSize = true;
      this.checkBox1.Location = new Point(34, 228);
      this.checkBox1.Name = "checkBox1";
      this.checkBox1.Size = new Size(102, 25);
      this.checkBox1.TabIndex = 4;
      this.checkBox1.Text = "checkBox1";
      this.checkBox1.UseVisualStyleBackColor = true;
      this.AutoScaleDimensions = new SizeF(9f, 21f);
      this.AutoScaleMode = AutoScaleMode.Font;
      this.ClientSize = new Size(491, 413);
      this.Controls.Add((Control) this.panel1);
      this.Controls.Add((Control) this.label11);
      this.Font = new Font("Segoe UI", 12f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.FormBorderStyle = FormBorderStyle.FixedToolWindow;
      this.Margin = new Padding(4, 5, 4, 5);
      this.MaximizeBox = false;
      this.MinimizeBox = false;
      this.Name = nameof (SettingsForm);
      this.Text = "Settings";
      this.panel1.ResumeLayout(false);
      this.panel1.PerformLayout();
      this.ResumeLayout(false);
      this.PerformLayout();
    }
  }
}
