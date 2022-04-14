using System;
using System.ComponentModel;
using System.Diagnostics;
using System.Drawing;
using System.Windows.Forms;

namespace AreDeAre_xPlorer_2.Forms
{
  public class AboutForm : Form
  {
    private IContainer components = (IContainer) null;
    private Label label2;
    private Label label3;
    private Label label4;
    private Label label5;
    private Label label6;
    private Label label7;
    private Label label9;
    private Label silkIconsLabel;
    private Panel panel1;
    private PictureBox pictureBox1;
    private PictureBox pictureBox2;
    private Label versionLabel;

    public AboutForm()
    {
      this.InitializeComponent();
      this.versionLabel.Text = string.Format("Version: {0}", (object) AppGlobals.Version);
    }

    private void silkIconsLabel_Click(object sender, EventArgs e) => Process.Start("http://www.famfamfam.com/lab/icons/silk/");

    protected override void Dispose(bool disposing)
    {
      if (disposing && this.components != null)
        this.components.Dispose();
      base.Dispose(disposing);
    }

    private void InitializeComponent()
    {
      ComponentResourceManager componentResourceManager = new ComponentResourceManager(typeof (AboutForm));
      this.label2 = new Label();
      this.label3 = new Label();
      this.label4 = new Label();
      this.label5 = new Label();
      this.label6 = new Label();
      this.label7 = new Label();
      this.label9 = new Label();
      this.silkIconsLabel = new Label();
      this.panel1 = new Panel();
      this.pictureBox2 = new PictureBox();
      this.pictureBox1 = new PictureBox();
      this.versionLabel = new Label();
      this.panel1.SuspendLayout();
      ((ISupportInitialize) this.pictureBox2).BeginInit();
      ((ISupportInitialize) this.pictureBox1).BeginInit();
      this.SuspendLayout();
      this.label2.AutoSize = true;
      this.label2.Font = new Font("Arial", 17f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.label2.Location = new Point(211, 60);
      this.label2.Margin = new Padding(4, 0, 4, 0);
      this.label2.Name = "label2";
      this.label2.Size = new Size(168, 26);
      this.label2.TabIndex = 1;
      this.label2.Text = "by XBLToothPik";
      this.label3.AutoSize = true;
      this.label3.Font = new Font("Consolas", 20.25f, FontStyle.Italic, GraphicsUnit.Point, (byte) 0);
      this.label3.Location = new Point(4, 91);
      this.label3.Margin = new Padding(4, 0, 4, 0);
      this.label3.Name = "label3";
      this.label3.Size = new Size(300, 32);
      this.label3.TabIndex = 2;
      this.label3.Text = "Very Special Thanks";
      this.label4.AutoSize = true;
      this.label4.Font = new Font("Arial", 20f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.label4.Location = new Point(40, 189);
      this.label4.Margin = new Padding(4, 0, 4, 0);
      this.label4.Name = "label4";
      this.label4.Size = new Size(161, 32);
      this.label4.TabIndex = 3;
      this.label4.Text = "ap ii intense";
      this.label5.AutoSize = true;
      this.label5.Font = new Font("Arial", 20f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.label5.Location = new Point(40, 221);
      this.label5.Margin = new Padding(4, 0, 4, 0);
      this.label5.Name = "label5";
      this.label5.Size = new Size(103, 32);
      this.label5.TabIndex = 4;
      this.label5.Text = "kcozart";
      this.label6.AutoSize = true;
      this.label6.Font = new Font("Arial", 20f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.label6.Location = new Point(40, 157);
      this.label6.Margin = new Padding(4, 0, 4, 0);
      this.label6.Name = "label6";
      this.label6.Size = new Size(119, 32);
      this.label6.TabIndex = 5;
      this.label6.Text = "Dageron";
      this.label7.AutoSize = true;
      this.label7.Font = new Font("Arial", 20f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.label7.Location = new Point(40, 125);
      this.label7.Margin = new Padding(4, 0, 4, 0);
      this.label7.Name = "label7";
      this.label7.Size = new Size(130, 32);
      this.label7.TabIndex = 6;
      this.label7.Text = "twisted89";
      this.label9.AutoSize = true;
      this.label9.Font = new Font("Consolas", 20.25f, FontStyle.Italic, GraphicsUnit.Point, (byte) 0);
      this.label9.Location = new Point(4, 253);
      this.label9.Margin = new Padding(4, 0, 4, 0);
      this.label9.Name = "label9";
      this.label9.Size = new Size(60, 32);
      this.label9.TabIndex = 8;
      this.label9.Text = "Art";
      this.silkIconsLabel.AutoSize = true;
      this.silkIconsLabel.Cursor = Cursors.Hand;
      this.silkIconsLabel.Font = new Font("Arial", 20f, FontStyle.Italic | FontStyle.Underline, GraphicsUnit.Point, (byte) 0);
      this.silkIconsLabel.ForeColor = Color.Blue;
      this.silkIconsLabel.Location = new Point(18, 284);
      this.silkIconsLabel.Margin = new Padding(4, 0, 4, 0);
      this.silkIconsLabel.Name = "silkIconsLabel";
      this.silkIconsLabel.Size = new Size(131, 31);
      this.silkIconsLabel.TabIndex = 9;
      this.silkIconsLabel.Text = "Silk Icons";
      this.silkIconsLabel.Click += new EventHandler(this.silkIconsLabel_Click);
      this.panel1.BorderStyle = BorderStyle.FixedSingle;
      this.panel1.Controls.Add((Control) this.versionLabel);
      this.panel1.Controls.Add((Control) this.pictureBox2);
      this.panel1.Controls.Add((Control) this.pictureBox1);
      this.panel1.Controls.Add((Control) this.silkIconsLabel);
      this.panel1.Controls.Add((Control) this.label2);
      this.panel1.Controls.Add((Control) this.label9);
      this.panel1.Controls.Add((Control) this.label3);
      this.panel1.Controls.Add((Control) this.label4);
      this.panel1.Controls.Add((Control) this.label7);
      this.panel1.Controls.Add((Control) this.label5);
      this.panel1.Controls.Add((Control) this.label6);
      this.panel1.Location = new Point(12, 12);
      this.panel1.Name = "panel1";
      this.panel1.Size = new Size(394, 328);
      this.panel1.TabIndex = 10;
      this.pictureBox2.BorderStyle = BorderStyle.Fixed3D;
      this.pictureBox2.Image = (Image) componentResourceManager.GetObject("pictureBox2.Image");
      this.pictureBox2.Location = new Point(205, 142);
      this.pictureBox2.Name = "pictureBox2";
      this.pictureBox2.Size = new Size(175, 173);
      this.pictureBox2.SizeMode = PictureBoxSizeMode.StretchImage;
      this.pictureBox2.TabIndex = 11;
      this.pictureBox2.TabStop = false;
      this.pictureBox1.Image = (Image) componentResourceManager.GetObject("pictureBox1.Image");
      this.pictureBox1.Location = new Point(10, 7);
      this.pictureBox1.Name = "pictureBox1";
      this.pictureBox1.Size = new Size(369, 50);
      this.pictureBox1.SizeMode = PictureBoxSizeMode.StretchImage;
      this.pictureBox1.TabIndex = 10;
      this.pictureBox1.TabStop = false;
      this.versionLabel.AutoSize = true;
      this.versionLabel.Font = new Font("Arial", 12f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.versionLabel.Location = new Point(7, 60);
      this.versionLabel.Margin = new Padding(4, 0, 4, 0);
      this.versionLabel.Name = "versionLabel";
      this.versionLabel.Size = new Size(95, 18);
      this.versionLabel.TabIndex = 12;
      this.versionLabel.Text = "Version: N/A";
      this.AutoScaleDimensions = new SizeF(9f, 18f);
      this.AutoScaleMode = AutoScaleMode.Font;
      this.ClientSize = new Size(418, 347);
      this.Controls.Add((Control) this.panel1);
      this.Font = new Font("Arial", 12f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.FormBorderStyle = FormBorderStyle.FixedToolWindow;
      this.Margin = new Padding(4);
      this.Name = nameof (AboutForm);
      this.ShowIcon = false;
      this.ShowInTaskbar = false;
      this.StartPosition = FormStartPosition.CenterParent;
      this.Text = "About AreDeAre xPlorer 2";
      this.panel1.ResumeLayout(false);
      this.panel1.PerformLayout();
      ((ISupportInitialize) this.pictureBox2).EndInit();
      ((ISupportInitialize) this.pictureBox1).EndInit();
      this.ResumeLayout(false);
    }
  }
}
