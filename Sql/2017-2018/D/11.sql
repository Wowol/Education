--ZAD11
SELECT id_zamowienia, ROUND(SUM(cena_netto*(1+vat/100)*ilosc), 2) FROM produkty_zamowienia
JOIN zamowienia z using (id_zamowienia)
JOIN historia_cen on produkt=kod_produktu
JOIN produkty USING (kod_produktu)
JOIN kategorie USING (id_kategoria)
WHERE (id_zamowienia, ilosc, kod_produktu, data_wprowadzenia) IN
(
SELECT id_zamowienia, ilosc, kod_produktu, MAX(data_wprowadzenia) FROM produkty_zamowienia
JOIN zamowienia z using (id_zamowienia)
JOIN historia_cen on produkt=kod_produktu
WHERE data_wprowadzenia<data_zlozenia
GROUP BY kod_produktu, ilosc, id_zamowienia
)
GROUP BY id_zamowienia