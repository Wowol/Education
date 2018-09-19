--ZAD1
SELECT ROUND(MIN(cena_netto*(1+vat/100)), 2) as min, ROUND(MAX(cena_netto*(1+vat/100)),2) as max FROM produkty ORDER BY 1,2;
----