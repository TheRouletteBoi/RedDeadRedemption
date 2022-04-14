using DevExpress.XtraEditors;
using RAGE;
using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;

namespace AreDeAre_xPlorer_2.Forms
{
  public class PlatformSelectionForm : XtraForm
  {
    private IContainer components = (IContainer) null;
    private SimpleButton xboxPlatformButton;
    private SimpleButton playstation3Platform;

    public AppGlobals.PlatformEnum SelectedPlatform { get; set; }

    public PlatformSelectionForm()
    {
      this.InitializeComponent();
      this.SelectedPlatform = AppGlobals.PlatformEnum.None;
    }

    private void xboxPlatformButton_Click(object sender, EventArgs e)
    {
      this.SelectedPlatform = AppGlobals.PlatformEnum.Xbox;
      RPF6.CurrentEncryptionKey = AppGlobals.EncryptionKey;
      this.Close();
    }

    private void playstation3Platform_Click(object sender, EventArgs e)
    {
      this.SelectedPlatform = AppGlobals.PlatformEnum.PS3;
      RPF6.CurrentEncryptionKey = AppGlobals.EncryptionKey;
      this.Close();
    }

    protected override void Dispose(bool disposing)
    {
      if (disposing && this.components != null)
        this.components.Dispose();
      base.Dispose(disposing);
    }

    private void InitializeComponent()
    {
      ComponentResourceManager componentResourceManager = new ComponentResourceManager(typeof (PlatformSelectionForm));
      this.xboxPlatformButton = new SimpleButton();
      this.playstation3Platform = new SimpleButton();
      this.SuspendLayout();
      this.xboxPlatformButton.AllowFocus = false;
      this.xboxPlatformButton.Appearance.Font = new Font("Tahoma", 12f);
      this.xboxPlatformButton.Appearance.Options.UseFont = true;
      this.xboxPlatformButton.Location = new Point(15, 22);
      this.xboxPlatformButton.Name = "xboxPlatformButton";
      this.xboxPlatformButton.Size = new Size(215, 41);
      this.xboxPlatformButton.TabIndex = 2;
      this.xboxPlatformButton.Text = "Xbox 360";
      this.xboxPlatformButton.Click += new EventHandler(this.xboxPlatformButton_Click);
      this.playstation3Platform.AllowFocus = false;
      this.playstation3Platform.Appearance.Font = new Font("Tahoma", 12f);
      this.playstation3Platform.Appearance.Options.UseFont = true;
      this.playstation3Platform.Location = new Point(15, 69);
      this.playstation3Platform.Name = "playstation3Platform";
      this.playstation3Platform.Size = new Size(215, 41);
      this.playstation3Platform.TabIndex = 3;
      this.playstation3Platform.Text = "Playstation 3";
      this.playstation3Platform.Click += new EventHandler(this.playstation3Platform_Click);
      this.Appearance.Options.UseFont = true;
      this.AutoScaleDimensions = new SizeF(11f, 23f);
      this.AutoScaleMode = AutoScaleMode.Font;
      this.ClientSize = new Size(245, 126);
      this.Controls.Add((Control) this.playstation3Platform);
      this.Controls.Add((Control) this.xboxPlatformButton);
      this.Font = new Font("Arial", 15f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.FormBorderStyle = FormBorderStyle.FixedSingle;
      this.Icon = (Icon) componentResourceManager.GetObject("$this.Icon");
      this.LookAndFeel.SkinName = "Sharp";
      this.LookAndFeel.UseDefaultLookAndFeel = false;
      this.Margin = new Padding(6, 5, 6, 5);
      this.MaximizeBox = false;
      this.Name = nameof (PlatformSelectionForm);
      this.ShowIcon = false;
      this.StartPosition = FormStartPosition.CenterScreen;
      this.Text = "Choose Platform";
      this.ResumeLayout(false);
    }
  }
}
