-- We had a shortest code competition for this task, that's why it looks so terrible :)

--ZAD1
SELECT name"language",SUM(1)submits FROM submits JOIN jezyk j ON language=j.id GROUP by 1 ORDER BY 2 DESC
----
--ZAD2
SELECT shortname o,s.id q,p.id w,p.name n INTO t FROM submits q JOIN statusy s ON STATUS=s.id JOIN problems p ON problemsid=p.id;CREATE FUNCTION c(BIGINT,BIGINT)RETURNS BIGINT AS'SELECT NULLIF(SUM(1),0)FROM t WHERE q=$1AND w=$2;'LANGUAGE SQL;SELECT o"name",c(8,w)ok,c(7,w)ans,c(5,w)tle,c(4,w)rte,c(14,w)rte,c(3,w)rte,c(2,w)cmp,c(10,w)rul,c(11,w)hea,c(6,w)"int",SUM(1)"all"from t GROUP BY 1,n,w ORDER BY n
----
--ZAD3
SELECT usersid u,problemsid i,MAX(ocena::NUMERIC*10) o INTO t from submits GROUP BY u,i;CREATE FUNCTION f(BIGINT,BIGINT)RETURNS BIGINT AS'SELECT NULLIF(SUM(1),0)FROM t WHERE o<$1+1AND o>=$1AND i=$2'LANGUAGE SQL;SELECT shortname"name",f(10,i)"100",f(9,i)"100-90",f(8,i)"90-80",f(7,i)"80-70",f(6,i)"70-60",f(5,i)"60-50",f(4,i)"50-40",f(3,i)"40-30",f(2,i)"30-20",f(1,i)"20-10",f(0,i)"10-0",SUM(1)"all"from t JOIN problems p ON(i=id)GROUP BY 1,i,name ORDER BY p.name