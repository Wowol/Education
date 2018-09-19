--ZAD10
SELECT p.nazwa,
  ROUND(cena_netto*(1+vat/100), 2)-SUM(CASE WHEN data_od<=data_wprowadzenia AND data_do>=data_wprowadzenia THEN znizka ELSE 0 END)
  FROM produkty p
JOIN historia_cen h USING (kod_produktu)
LEFT JOIN rabaty_produkty rp ON (kod_produktu=id_produktu)
LEFT JOIN rabaty r USING (id_rabatu)
LEFT JOIN kategorie USING (id_kategoria)
WHERE (kod_produktu, data_wprowadzenia) IN
(
SELECT kod_produktu, MAX(data_wprowadzenia) FROM historia_cen
GROUP BY kod_produktu
)
GROUP BY kod_produktu, p.nazwa, vat, cena_netto