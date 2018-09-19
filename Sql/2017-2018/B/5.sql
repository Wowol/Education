--ZAD5
SELECT kategoria, MIN(cena_netto), MAX(cena_netto), MAX(cena_netto)-MIN(cena_netto)
FROM produkty
GROUP BY kategoria
ORDER BY 1, 2, 3, 4
----