--ZAD12
SELECT nazwa as "klient", COALESCE(SUM(ilosc), 0) as "ilosc produktow" FROM klienci 
LEFT OUTER JOIN zamowienia USING (id_klienta)
LEFT OUTER JOIN produkty_zamowienia USING (id_zamowienia)
GROUP BY nazwa
ORDER BY 1,2