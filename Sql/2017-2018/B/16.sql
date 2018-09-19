--ZAD16
SELECT produkt, COUNT(*) from produkty_zamowienia 
GROUP BY produkt
ORDER BY 2 DESC, 1
----