--ZAD9
SELECT p.nazwa, ROUND(cena_netto+(cena_netto*vat/100), 2) FROM historia_cen 
JOIN produkty p USING (kod_produktu)
JOIN kategorie USING (id_kategoria)
WHERE (kod_produktu, data_wprowadzenia) IN
(SELECT kod_produktu, MAX(data_wprowadzenia) FROM historia_cen
    GROUP BY kod_produktu) 