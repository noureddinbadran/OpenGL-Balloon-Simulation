using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Diagnostics;
using System.IO;

namespace WindowsFormsApplication1
{
    public partial class Form1 : Form
    {
        Process proc;
        ProcessStartInfo procInfo;
        String text4 = "4.002602";
        public Form1()
        {
            InitializeComponent();

            radiohellium.Checked = true;
            rb_earth.Checked = true;


            Text1.Text = "0";
            Text2.Text = "4";
           // Text3.Text = "9.81";
           // Text4.Text = "4.002602";
            //Text5.Text = "50";
            Text6.Text = "50";
           // Text7.Text = "101325";
           // Text8.Text = "288.15";
          //  Text9.Text = "8.31447";
            Text10.Text = "1400";
        //    Text11.Text = "0.0289644";

            ssl.Text = " Today is " + DateTime.Now;

            procInfo = new ProcessStartInfo();
            proc = new Process();
        }

        private void btnclick_Click(object sender, EventArgs e)
        {
            if(rb_earth.Checked==true)
                RunCMD("Template.exe", Text1.Text + " " + Text2.Text + " " + "9.81" + " " + text4 + " " + "50" + " " + Text6.Text + " " + "101325" + " " + "288.15" + " " + "8.31447" + " " + Text10.Text + " " + "0.0289644" + " " + "Earth");    
            else
                RunCMD("Template.exe", Text1.Text + " " + Text2.Text + " " + "9.81" + " " + text4 + " " + "50" + " " + Text6.Text + " " + "101325" + " " + "288.15" + " " + "8.31447" + " " + Text10.Text + " " + "0.0289644" + " " + "Moon");    
        }

        private void RunCMD(string FileName, string Commands)
        {
                procInfo.FileName = FileName;
                procInfo.Arguments = Commands;
                procInfo.CreateNoWindow = true;
     
                proc.StartInfo = procInfo;
                proc.Start();
                 
        }

        private void button1_Click(object sender, EventArgs e)
        {
            MessageBox.Show("This project aims to emulate GOOGLE LOON BALLONS ...\nDone by :\nGhaith Hahi\nNoor Alden Badran\nWalaa Alfares\nYaser Alawa", "About LOON", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void radiohellium_CheckedChanged(object sender, EventArgs e)
        {
            text4 = "4.002602";
        }

        private void radioHedroigin_CheckedChanged(object sender, EventArgs e)
        {
            text4 = "2.01588";
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

    }
}