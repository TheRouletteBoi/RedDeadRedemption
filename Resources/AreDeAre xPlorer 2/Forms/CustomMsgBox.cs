using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;

namespace AreDeAre_xPlorer_2.Forms
{
  public class CustomMsgBox : Form
  {
    private IContainer components = (IContainer) null;

    public CustomMsgBox() => this.InitializeComponent();

    protected override void Dispose(bool disposing)
    {
      if (disposing && this.components != null)
        this.components.Dispose();
      base.Dispose(disposing);
    }

    private void InitializeComponent()
    {
      this.SuspendLayout();
      this.AutoScaleDimensions = new SizeF(6f, 13f);
      this.AutoScaleMode = AutoScaleMode.Font;
      this.ClientSize = new Size(296, 152);
      this.FormBorderStyle = FormBorderStyle.FixedSingle;
      this.MaximizeBox = false;
      this.MinimizeBox = false;
      this.Name = nameof (CustomMsgBox);
      this.ShowIcon = false;
      this.ShowInTaskbar = false;
      this.StartPosition = FormStartPosition.CenterParent;
      this.Text = "MSGBOX";
      this.ResumeLayout(false);
    }
  }
}
