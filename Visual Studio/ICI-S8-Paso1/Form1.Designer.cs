namespace ICI_S8_Paso1
{
    partial class Form1
    {
        /// <summary>
        /// Variable del diseñador necesaria.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Limpiar los recursos que se estén usando.
        /// </summary>
        /// <param name="disposing">true si los recursos administrados se deben desechar; false en caso contrario.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Código generado por el Diseñador de Windows Forms

        /// <summary>
        /// Método necesario para admitir el Diseñador. No se puede modificar
        /// el contenido de este método con el editor de código.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.button1 = new System.Windows.Forms.Button();
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.button2 = new System.Windows.Forms.Button();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.textBox2 = new System.Windows.Forms.TextBox();
            this.button3 = new System.Windows.Forms.Button();
            this.lbDigitalMeter1 = new LBSoft.IndustrialCtrls.Meters.LBDigitalMeter();
            this.lbKnob1 = new LBSoft.IndustrialCtrls.Knobs.LBKnob();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.lbAnalogMeter1 = new LBSoft.IndustrialCtrls.Meters.LBAnalogMeter();
            this.lbKnob2 = new LBSoft.IndustrialCtrls.Knobs.LBKnob();
            this.button4 = new System.Windows.Forms.Button();
            this.button5 = new System.Windows.Forms.Button();
            this.button6 = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.textBox3 = new System.Windows.Forms.TextBox();
            this.textBox4 = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.button7 = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(41, 147);
            this.button1.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(175, 44);
            this.button1.TabIndex = 0;
            this.button1.Text = "Tiempo de lectura";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // serialPort1
            // 
            this.serialPort1.PortName = "COM3";
            this.serialPort1.ReceivedBytesThreshold = 4;
            this.serialPort1.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.serialPort1_DataReceived);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(423, 257);
            this.button2.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(297, 70);
            this.button2.TabIndex = 1;
            this.button2.Text = "Cancelar todos los comandos";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // timer1
            // 
            this.timer1.Enabled = true;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // textBox2
            // 
            this.textBox2.Location = new System.Drawing.Point(41, 199);
            this.textBox2.Name = "textBox2";
            this.textBox2.Size = new System.Drawing.Size(175, 22);
            this.textBox2.TabIndex = 3;
            this.textBox2.TextChanged += new System.EventHandler(this.textBox2_TextChanged);
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(41, 270);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(203, 57);
            this.button3.TabIndex = 4;
            this.button3.Text = "Activar control por potenciómetro";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.button3_Click);
            // 
            // lbDigitalMeter1
            // 
            this.lbDigitalMeter1.BackColor = System.Drawing.Color.CornflowerBlue;
            this.lbDigitalMeter1.Format = "00.00";
            this.lbDigitalMeter1.Location = new System.Drawing.Point(24, 38);
            this.lbDigitalMeter1.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.lbDigitalMeter1.Name = "lbDigitalMeter1";
            this.lbDigitalMeter1.Renderer = null;
            this.lbDigitalMeter1.Signed = false;
            this.lbDigitalMeter1.Size = new System.Drawing.Size(209, 103);
            this.lbDigitalMeter1.TabIndex = 6;
            this.lbDigitalMeter1.Value = 0D;
            // 
            // lbKnob1
            // 
            this.lbKnob1.BackColor = System.Drawing.Color.Transparent;
            this.lbKnob1.DrawRatio = 0.75F;
            this.lbKnob1.ForeColor = System.Drawing.SystemColors.ControlText;
            this.lbKnob1.IndicatorColor = System.Drawing.Color.Red;
            this.lbKnob1.IndicatorOffset = 10F;
            this.lbKnob1.KnobCenter = ((System.Drawing.PointF)(resources.GetObject("lbKnob1.KnobCenter")));
            this.lbKnob1.KnobColor = System.Drawing.Color.CadetBlue;
            this.lbKnob1.KnobRect = ((System.Drawing.RectangleF)(resources.GetObject("lbKnob1.KnobRect")));
            this.lbKnob1.Location = new System.Drawing.Point(250, 215);
            this.lbKnob1.MaxValue = 90F;
            this.lbKnob1.MinValue = 0F;
            this.lbKnob1.Name = "lbKnob1";
            this.lbKnob1.Renderer = null;
            this.lbKnob1.ScaleColor = System.Drawing.SystemColors.HighlightText;
            this.lbKnob1.Size = new System.Drawing.Size(150, 150);
            this.lbKnob1.StepValue = 1F;
            this.lbKnob1.Style = LBSoft.IndustrialCtrls.Knobs.LBKnob.KnobStyle.Circular;
            this.lbKnob1.TabIndex = 7;
            this.lbKnob1.Value = 0F;
            this.lbKnob1.KnobChangeValue += new LBSoft.IndustrialCtrls.Knobs.KnobChangeValue(this.lbKnob1_KnobChangeValue);
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(144, 333);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(100, 22);
            this.textBox1.TabIndex = 8;
            // 
            // lbAnalogMeter1
            // 
            this.lbAnalogMeter1.BackColor = System.Drawing.Color.Transparent;
            this.lbAnalogMeter1.BodyColor = System.Drawing.Color.RoyalBlue;
            this.lbAnalogMeter1.Location = new System.Drawing.Point(423, 38);
            this.lbAnalogMeter1.MaxValue = 11D;
            this.lbAnalogMeter1.MeterStyle = LBSoft.IndustrialCtrls.Meters.LBAnalogMeter.AnalogMeterStyle.Circular;
            this.lbAnalogMeter1.MinValue = 1D;
            this.lbAnalogMeter1.Name = "lbAnalogMeter1";
            this.lbAnalogMeter1.NeedleColor = System.Drawing.Color.Yellow;
            this.lbAnalogMeter1.Renderer = null;
            this.lbAnalogMeter1.ScaleColor = System.Drawing.Color.White;
            this.lbAnalogMeter1.ScaleDivisions = 10;
            this.lbAnalogMeter1.ScaleSubDivisions = 10;
            this.lbAnalogMeter1.Size = new System.Drawing.Size(150, 150);
            this.lbAnalogMeter1.TabIndex = 9;
            this.lbAnalogMeter1.Value = 7D;
            this.lbAnalogMeter1.ViewGlass = false;
            this.lbAnalogMeter1.Load += new System.EventHandler(this.lbAnalogMeter1_Load);
            // 
            // lbKnob2
            // 
            this.lbKnob2.BackColor = System.Drawing.Color.Transparent;
            this.lbKnob2.DrawRatio = 0.75F;
            this.lbKnob2.IndicatorColor = System.Drawing.Color.Red;
            this.lbKnob2.IndicatorOffset = 10F;
            this.lbKnob2.KnobCenter = ((System.Drawing.PointF)(resources.GetObject("lbKnob2.KnobCenter")));
            this.lbKnob2.KnobColor = System.Drawing.Color.SkyBlue;
            this.lbKnob2.KnobRect = ((System.Drawing.RectangleF)(resources.GetObject("lbKnob2.KnobRect")));
            this.lbKnob2.Location = new System.Drawing.Point(579, 38);
            this.lbKnob2.MaxValue = 11F;
            this.lbKnob2.MinValue = 1F;
            this.lbKnob2.Name = "lbKnob2";
            this.lbKnob2.Renderer = null;
            this.lbKnob2.ScaleColor = System.Drawing.Color.Lavender;
            this.lbKnob2.Size = new System.Drawing.Size(150, 150);
            this.lbKnob2.StepValue = 1F;
            this.lbKnob2.Style = LBSoft.IndustrialCtrls.Knobs.LBKnob.KnobStyle.Circular;
            this.lbKnob2.TabIndex = 10;
            this.lbKnob2.Value = 0F;
            this.lbKnob2.KnobChangeValue += new LBSoft.IndustrialCtrls.Knobs.KnobChangeValue(this.lbKnob2_KnobChangeValue);
            // 
            // button4
            // 
            this.button4.Location = new System.Drawing.Point(423, 199);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(80, 38);
            this.button4.TabIndex = 11;
            this.button4.Text = "Izquierda";
            this.button4.UseVisualStyleBackColor = true;
            this.button4.Click += new System.EventHandler(this.button4_Click);
            // 
            // button5
            // 
            this.button5.Location = new System.Drawing.Point(509, 199);
            this.button5.Name = "button5";
            this.button5.Size = new System.Drawing.Size(80, 38);
            this.button5.TabIndex = 12;
            this.button5.Text = "Derecha";
            this.button5.UseVisualStyleBackColor = true;
            this.button5.Click += new System.EventHandler(this.button5_Click);
            // 
            // button6
            // 
            this.button6.Location = new System.Drawing.Point(811, 38);
            this.button6.Name = "button6";
            this.button6.Size = new System.Drawing.Size(152, 55);
            this.button6.TabIndex = 13;
            this.button6.Text = "Apertura y cierre";
            this.button6.UseVisualStyleBackColor = true;
            this.button6.Click += new System.EventHandler(this.button6_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(768, 124);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(123, 17);
            this.label1.TabIndex = 14;
            this.label1.Text = "Tiempo de espera";
            this.label1.Click += new System.EventHandler(this.label1_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(923, 124);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(70, 17);
            this.label2.TabIndex = 15;
            this.label2.Text = "Velocidad";
            // 
            // textBox3
            // 
            this.textBox3.Location = new System.Drawing.Point(782, 147);
            this.textBox3.Name = "textBox3";
            this.textBox3.Size = new System.Drawing.Size(100, 22);
            this.textBox3.TabIndex = 16;
            // 
            // textBox4
            // 
            this.textBox4.Location = new System.Drawing.Point(910, 147);
            this.textBox4.Name = "textBox4";
            this.textBox4.Size = new System.Drawing.Size(100, 22);
            this.textBox4.TabIndex = 17;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(59, 17);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(123, 17);
            this.label3.TabIndex = 18;
            this.label3.Text = "Temperatura local";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(451, 17);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(103, 17);
            this.label4.TabIndex = 19;
            this.label4.Text = "Velocidad local";
            // 
            // button7
            // 
            this.button7.Location = new System.Drawing.Point(792, 199);
            this.button7.Name = "button7";
            this.button7.Size = new System.Drawing.Size(192, 69);
            this.button7.TabIndex = 20;
            this.button7.Text = "Mostrar en el display";
            this.button7.UseVisualStyleBackColor = true;
            this.button7.Click += new System.EventHandler(this.button7_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.Control;
            this.ClientSize = new System.Drawing.Size(1022, 377);
            this.Controls.Add(this.button7);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.textBox4);
            this.Controls.Add(this.textBox3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.button6);
            this.Controls.Add(this.button5);
            this.Controls.Add(this.button4);
            this.Controls.Add(this.lbKnob2);
            this.Controls.Add(this.lbAnalogMeter1);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.lbKnob1);
            this.Controls.Add(this.lbDigitalMeter1);
            this.Controls.Add(this.button3);
            this.Controls.Add(this.textBox2);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.button1);
            this.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.Name = "Form1";
            this.Text = "ICI-S8-Paso1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button button1;
        private System.IO.Ports.SerialPort serialPort1;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.TextBox textBox2;
        private System.Windows.Forms.Button button3;
        private LBSoft.IndustrialCtrls.Meters.LBDigitalMeter lbDigitalMeter1;
        private LBSoft.IndustrialCtrls.Knobs.LBKnob lbKnob1;
        private System.Windows.Forms.TextBox textBox1;
        private LBSoft.IndustrialCtrls.Meters.LBAnalogMeter lbAnalogMeter1;
        private LBSoft.IndustrialCtrls.Knobs.LBKnob lbKnob2;
        private System.Windows.Forms.Button button4;
        private System.Windows.Forms.Button button5;
        private System.Windows.Forms.Button button6;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox textBox3;
        private System.Windows.Forms.TextBox textBox4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Button button7;
    }
}

