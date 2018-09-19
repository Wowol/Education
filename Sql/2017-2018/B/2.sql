--ZAD2
SELECT id_zamowienia, sum(ilosc)
FROM produkty_zamowienia
GROUP BY id_zamowienia
ORDER BY 1,2;
----