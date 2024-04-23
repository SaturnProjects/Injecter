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
using System.CodeDom;

namespace SaturnLoader
{
    public partial class loader : Form
    {
        public loader()
        {
            InitializeComponent();
        }

        private void loader_Load(object sender, EventArgs e)
        {
            satusText.Hide();
        }

        private void guna2Button1_Click(object sender, EventArgs e)
        {
            try 
            {
                satusText.Show();
                satusText.Text = "Injecting...";
                Process.Start("SaturnInjecter.exe"); // loads the injecter
                Console.Beep(500, 500);
                InjectBtn.Hide();
            } catch 
            
            {
                MessageBox.Show("Could Not Find Injecter File\nMake sure you drag the exe in this directory");
                Console.Beep(200, 500);
            }
        }

        private void guna2Button2_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Saturn was created by naz! please give credits\n\nhttps://github.com/naziscool/SaturnInjecter.\nSTAR IT OR ELSE YOUR NOT GONNA GET A COOKIE.", "saturn"); ;
        }
    }
}
