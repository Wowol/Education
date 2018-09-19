--ZAD11
SELECT DISTINCT(id_zamowienia) FROM zamowienia
JOIN klienci USING (id_klienta)
JOIN rabaty_klientow USING (id_klienta)
ORDER BY 1