using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Text.RegularExpressions;

namespace SatoriA
{
    class Program
    {
        static Dictionary<char, int> priority = new Dictionary<char, int>();

        static string ConvertToONP(string p)
        {
            string outString = "";

            Stack<string> s = new Stack<string>();

            int i = -1;
            foreach (char c in p)
            {
                i++;

                if (!Char.IsDigit(c) && !priority.ContainsKey(c))
                {
                    throw new Exception();
                }

                if (Char.IsDigit(c))
                {
                    outString += c;
                    if (i+1 >= p.Length || !Char.IsDigit(p[i+1]))
                    {
                        outString += " ";
                    }
                    continue;
                }
                

                if (c == '(')
                {
                    s.Push(c.ToString());
                    continue;
                }

                if (c == ')')
                {
                    while (s.Peek() != "(")
                    {
                        outString += " " + s.Pop() + " ";
                    }
                    s.Pop();
                    continue;
                }

                if (priority.ContainsKey(c))
                {
                    if (s.Count == 0 || priority[c] > priority[s.Peek()[0]])
                    {
                        s.Push(c.ToString());
                    }
                    else
                    {
                        while (s.Count > 0 && priority[c] <= priority[s.Peek()[0]])
                        {
                            outString += " " + s.Pop() + " ";
                        }

                        s.Push(c.ToString());
                    }
                }
            }

            while (s.Count != 0)
            {
                outString += " " + s.Pop() + " ";
            }

            return outString;
        }

        static int Compute(int a, int b, char op)
        {
            checked
            {
                switch (op)
                {
                    case '*':
                        return a * b;
                    case '+':
                        return a + b;
                    case '-':
                        return a - b;
                    case '/':
                        return a / b;
                    default:
                        throw new Exception();
                }
            }
          
        }

        static int CalculateONP(string[] p)
        {
            Stack<int> s = new Stack<int>();
            foreach(string c in p)
            {
                if (Char.IsDigit(c[0]))
                {
                    s.Push(Convert.ToInt32(c));
                    continue;
                }
                else
                {
                    int first = s.Pop();
                    int second = s.Pop();
                    int result = Compute(second, first, c[0]);
                    s.Push(result);
                }
            }

            return s.Pop();
        }

        static void Main(string[] args)
        {
            priority['('] = 0;
            priority['+'] = 1;
            priority['-'] = 1;
            priority[')'] = 1;
            priority['*'] = 2;
            priority['/'] = 2;

            while (true)
            {
                string line = Console.ReadLine();

                if (line == null)
                    return;

                try
                {
                    string onp = ConvertToONP(line);
                    Console.WriteLine(CalculateONP(onp.Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries)));
                }
                catch
                {
                    Console.WriteLine("Error");
                }
              
            }
        }
    }
}
