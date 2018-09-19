using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace App
{
    public static class ExtensionMethods
    {
        public static TextBox GetColumnTextBox(this Panel p)
        {
            return (TextBox) p.Controls[0];
        }

        public static ComboBox GetOperatorComboBox(this Panel p)
        {
            return (ComboBox)p.Controls[1];
        }

        public static TextBox GetValueTextBox(this Panel p)
        {
            return (TextBox)p.Controls[2];
        }
    }
}
