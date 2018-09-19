--ZAD5
SELECT a.nazwa, b.nazwa FROM produkty a CROSS JOIN produkty b WHERE a.cena_netto*(1+a.vat/100)>b.cena_netto*(1+b.vat/100) ORDER BY 1,2----