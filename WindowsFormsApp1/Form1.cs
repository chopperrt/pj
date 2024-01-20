using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Microsoft.Win32;
namespace л4
{
    public partial class Form1 : Form
    {
      
        public Form1()
        {
            InitializeComponent();

            RegistryKey key = Registry.CurrentUser.CreateSubKey(@"Lisa");
        }
        private void button1_Click(object sender, EventArgs e) // размер окна
        {
            string hght = textBox2.Text;
            string wdth = textBox3.Text;

            this.Height = Convert.ToInt32(hght);
            this.Width = Convert.ToInt32(wdth);
        }
        private void button2_Click(object sender, EventArgs e)
        {
            RegistryKey key = Registry.CurrentUser.CreateSubKey(@"Lisa");
            key.SetValue("Color", "Фиолетовый"); key.Close();
            BackColor = System.Drawing.Color.DarkViolet;
        }
        private void button3_Click(object sender, EventArgs e)
        {
            RegistryKey key = Registry.CurrentUser.CreateSubKey(@"Lisa");
            key.SetValue("Color", "Черный"); key.Close();
            BackColor = System.Drawing.Color.Black;
        }
        private void button4_Click(object sender, EventArgs e)
        {
            RegistryKey key = Registry.CurrentUser.CreateSubKey(@"Lisa");
            key.SetValue("Color", "Розовый"); key.Close();
            BackColor = System.Drawing.Color.HotPink;
        }
      
        private void button5_Click(object sender, EventArgs e)
        {
            RegistryKey key = Registry.CurrentUser.CreateSubKey(@"Lisa");
            if (key != null)
            {
                string color = (string)key.GetValue("Color");
                if (color == "Фиолетовый")
                    BackColor = System.Drawing.Color.DarkViolet;
                else if (color == "Черный")
                    BackColor = System.Drawing.Color.Black;
                else if (color == "Розовый")
                    BackColor = System.Drawing.Color.HotPink;
            }
        }

        private void button1_Click_1(object sender, EventArgs e) // сохранение в реестре
        {
            RegistryKey key = Registry.CurrentUser.CreateSubKey(@"Lisa");

            key.SetValue("Height", this.Height);
            key.SetValue("Width", this.Width);
            key.Close();
        }

       
    }
}
