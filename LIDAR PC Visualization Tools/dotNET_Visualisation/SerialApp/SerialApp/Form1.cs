using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;

namespace SerialApp
{
    public partial class Form1 : Form
    {
        //public SerialReadWrite Port;
        private string buffer;
        public string Message;
        public string PrevMessage;
        public SerialRead serialread = new SerialRead();
        delegate void UpdatePlotDelegate(double X, double Y);

        public Form1()
        {
            InitializeComponent();
            chart1.Series.Clear();
            chart1.Series.Add("LIDAR Data");
            chart1.Series["LIDAR Data"].ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Point;
            buffer = string.Empty;
            Message = string.Empty;
            PrevMessage = Message;
            serialread.ReadSerial();


        }

        private void groupBox1_Enter(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e)
        {
            textBox1.Text = string.Empty;
            chart1.Series.Clear();
            chart1.Series.Add("LIDAR Data");
            chart1.Series["LIDAR Data"].ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Point;
            serialread.port.DiscardInBuffer();
        }

        public void SerialDataSent(object source, EventArgs args)
        {
            SerialRead tempObj = (SerialRead)source;
            //double[] X = new double[tempObj.Message.Length];
            //double[] Y = new double[tempObj.Message.Length];


            //for (int i = 2; i < (tempObj.Message.Length - 2); i++)
            //{
            //    string[] temp = tempObj.Message[i].ToString().Split(',');
            //    if (temp.Length == 3)
            //    {
            //        bool isNumeric = double.TryParse(temp[0], out double n) && double.TryParse(temp[1], out double n2);
            //        if (isNumeric)
            //        {
            //            double d = Convert.ToDouble(temp[0]);
            //            double a = Convert.ToDouble(temp[1]);
            //            X[i] = d * Math.Cos(a * Math.PI / 180);
            //            Y[i] = d * Math.Sin(a * Math.PI / 180);
            //        }
            //    }
            //}
            //if (chart1.InvokeRequired)
            //{
            //    Delegate del = new UpdatePlotDelegate(UpdatePlot);
            //    this.Invoke(del, X, Y);
            //}
            //else
            //{
            //    chart1.Series["LIDAR Data"].Points.AddXY(X, Y);
            //}
        }

        public void UpdatePlot(double[] X, double[] Y)
        {

            for (int i = 2; i < (X.Length - 2); i++)
            {
                if (X[i] > -10000 && X[i] < 10000 && Y[i] > -10000 && Y[i] < 10000 & X[i] != 0 && Y[i] != 0)
                {
                    chart1.Series["LIDAR Data"].Points.AddXY(X, Y);
                    chart1.ChartAreas[0].RecalculateAxesScale();
                }
            }
        }

        public class SerialRead
        {
            public SerialPort port = new SerialPort("COM5", 115200, Parity.None, 8, StopBits.One);
            public delegate void SendSerialDataEventHandler(object source, EventArgs args);
            public event SendSerialDataEventHandler SerialDataSent;
            public string Message;
            protected virtual void OnSerialDataSent()
            {
                if (SerialDataSent != null)
                {
                    SerialDataSent(this, EventArgs.Empty);
                }
            }
            public void ReadSerial()
            {
                port.DataReceived += new SerialDataReceivedEventHandler(dataRecieved);
                port.Open();
            }

            private void dataRecieved(object sender, SerialDataReceivedEventArgs e)
            {
                SerialPort sp = (SerialPort)sender;
                Message = sp.ReadExisting();
            }
         
        }

    }

}
