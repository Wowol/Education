using System.Collections.Generic;

namespace Generic
{
    public class Tree
    {
        public static IEnumerable<T> Traverse<T>(Node<T> root)
        {
            Stack<Node<T>> stack = new Stack<Node<T>>();
            Dictionary<Node<T>, IEnumerator<Node<T>>> dict = new Dictionary<Node<T>, IEnumerator<Node<T>>>();
            stack.Push(root);

            while (stack.Count > 0)
            {
                Node<T> node = stack.Peek();
                if (!dict.ContainsKey(node)) // jestesmy pierwszy raz
                {
                    dict[node] = node.Children?.GetEnumerator();
                    yield return node.Data;
                    if (dict[node] != null && dict[node].MoveNext())
                    {
                        stack.Push(dict[node].Current);
                    }
                    else
                    {
                        stack.Pop();
                    }
                }
                else
                {
                    if (dict[node].MoveNext())
                    {
                        stack.Push(dict[node].Current);
                    }
                    else
                    {
                        stack.Pop();
                    }
                }
            }

        }
    }
}