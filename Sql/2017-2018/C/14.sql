--ZAD14
SELECT nazwa AS "klient", COUNT(id_zamowienia) as "ilosc zamowien" FROM klienci
LEFT OUTER JOIN zamowienia USING (id_klienta)
GROUP BY id_klienta
ORDER BY "ilosc zamowien" DESC, "klient" ASC