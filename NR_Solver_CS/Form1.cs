using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using NRmethod; //C++ Managed DLL class
using TruncateInVB; //VB class meant for truncating the number to give more accurate readings (as after a certain decimal point it is inaccurate)
using System.Text.RegularExpressions;
 
namespace WindowsFormsApplication1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            label1.Text = "Real Root 1: Not found"; //reset outputs so no previous root is displayed
            label2.Text = "Real Root 2: Not found";
            label3.Text = "Real Root 3: Not found";

            double a=0,b=0,c=0,k=0; //set all coefficients to 0 by default (resetting any previous value entered)
            if (Regex.IsMatch(textBox1.Text, @"^-*[0-9.]+$")) a = System.Convert.ToDouble(textBox1.Text);
            if (Regex.IsMatch(textBox2.Text, @"^-*[0-9.]+$")) b = System.Convert.ToDouble(textBox2.Text);
            if (Regex.IsMatch(textBox3.Text, @"^-*[0-9.]+$")) c = System.Convert.ToDouble(textBox3.Text);
            if (Regex.IsMatch(textBox4.Text, @"^-*[0-9.]+$")) k = System.Convert.ToDouble(textBox4.Text);
           
            NR NRobject = new NR(a,b,c,k); //creates NR object whose class implements methods of solving 3rd order eq'n 

            Truncate_num truncans0 = new Truncate_num(NRobject.roots[0]);
            Truncate_num truncans1 = new Truncate_num(NRobject.roots[1]);
            Truncate_num truncans2 = new Truncate_num(NRobject.roots[2]);

            /* Below is a case where taking both sides of NR converge to the same number. This means that there is only 1 root. 
             * This adjusts the output so that only 1 is displayed. If the number is 100000000 (a chosen number to signifiy that 
             * there is no root) then do not display such a number*/
            if (NRobject.dcompare(truncans0.output, truncans1.output) && (NRobject.roots[0] != 100000000)) label1.Text = "Real Root: x = " + System.Convert.ToString(truncans0.output);
            
            /* As long as a root exists, (i.e the root is not equal to 100000000) The root will be displayed else, the output won't be changed */
            else
            {
                if (truncans0.output != 100000000) label1.Text = "Real Root 1: x = " + System.Convert.ToString(truncans0.output);
                if (truncans2.output != 100000000 && truncans2.output!=truncans0.output) label2.Text = "Real Root 2: x = " + System.Convert.ToString(truncans2.output);
                if (truncans1.output != 100000000 && truncans1.output!=truncans2.output) label3.Text = "Real Root 3: x = " + System.Convert.ToString(truncans1.output);
            }
        }
    }
}
