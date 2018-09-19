--ZAD13
SELECT klienci.nazwa as "klient", SUM(ilosc) as "ilosc produktow" FROM klienci 
JOIN zamowienia USING (id_klienta)
JOIN produkty_zamowienia USING (id_zamowienia)
JOIN produkty ON (produkt=kod_produktu)
WHERE waga > 1000
GROUP BY klienci.id_klienta
ORDER BY 1,2