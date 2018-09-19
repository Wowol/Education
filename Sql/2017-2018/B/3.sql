--ZAD3
SELECT produkt
FROM produkty_zamowienia
GROUP BY produkt
HAVING SUM(ilosc)>=50
ORDER BY 1
----