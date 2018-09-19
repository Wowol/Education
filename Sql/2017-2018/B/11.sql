--ZAD11
SELECT kategoria from produkty
GROUP BY kategoria
HAVING count(distinct rabat)=count(nazwa)
----