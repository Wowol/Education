--ZAD12
SELECT kategoria from produkty WHERE vat=8
GROUP BY kategoria
HAVING count(distinct rabat)=count(nazwa)
----