--ZAD6
SELECT id_zamowienia FROM produkty_zamowienia
GROUP BY id_zamowienia
 HAVING SUM(ILOSC) >= ALL
(SELECT SUM(ilosc) as xddd FROM produkty_zamowienia 
GROUP BY id_zamowienia)