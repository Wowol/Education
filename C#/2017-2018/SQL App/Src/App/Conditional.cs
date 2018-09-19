using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace App
{
    class Conditional
    {
        public readonly string columnName;
        public readonly string value;
        public readonly string op;

        public Conditional(string columnName, string op, string value)
        {
            this.columnName = columnName;
            this.value = value;
            this.op = op;
        }

        public override string ToString()
        {
            return String.Format("{0} {1} {2}", columnName, op, value);
        }
    }
}
