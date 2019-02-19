#if !SATORI
using System;
using System.Collections.Generic;
using System.Linq;

class Program
{
    static void Main()
    {
        System.Linq.Expressions.Expression<Action> expression = () =>
#endif
            (
            from currentTest in Enumerable.Range(0, Convert.ToInt32(Console.ReadLine()))
            let numberOfVertexAndEdges = Console.ReadLine().Split()
            let numberOfVertex = Convert.ToInt32(numberOfVertexAndEdges[0])
            let numberOfEdges = Convert.ToInt32(numberOfVertexAndEdges[1])
            select
            (
                from e in Enumerable.Range(0, numberOfEdges)
                let edge = Console.ReadLine().Split()
                let firstVertex = Convert.ToInt32(edge[0]) - 1
                let secondVertex = Convert.ToInt32(edge[1]) - 1
                select new { firstVertex, secondVertex }
            ).Aggregate(Enumerable.Range(0, numberOfVertex).ToArray(), (comp, newEdge) => (
                    from v in comp
                    select v == comp[newEdge.firstVertex] ?
                        Math.Min(v, comp[newEdge.secondVertex]) :
                            v == comp[newEdge.secondVertex] ? Math.Min(v, comp[newEdge.firstVertex]) : v
                    ).ToArray()
                ).ToList().Distinct().Count()
            ).ToList().ForEach(result => Console.WriteLine(result))
#if !SATORI
        ;
        expression.Compile().Invoke();
    }
}
#endif