--ZAD4
SELECT kategoria, ROUND(AVG(waga), 2)
FROM produkty
GROUP BY kategoria
HAVING COUNT(nazwa)>=2
ORDER BY 2 DESC, 1 ASC
----