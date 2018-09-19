--ZAD10
SELECT klienci.*, id_zamowienia, SUM(ilosc*cena_netto) FROM klienci  
JOIN zamowienia USING (id_klienta) 
JOIN produkty_zamowienia USING (id_zamowienia)
JOIN produkty ON (kod_produktu=produkt)
WHERE klienci.nazwa = 'Urząd Skarbowy w Radomiu'
GROUP BY id_zamowienia, klienci.id_klienta
----