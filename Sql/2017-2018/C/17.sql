--ZAD17
SELECT id_zamowienia, MAX(ilosc) FROM zamowienia
JOIN produkty_zamowienia USING (id_zamowienia)
GROUP BY id_zamowienia
ORDER BY "max" DESC, id_zamowienia ASC