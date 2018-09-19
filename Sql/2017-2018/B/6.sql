--ZAD6
SELECT kategoria, COUNT(CASE WHEN vat!=18 THEN 1 ELSE NULL END) as "ilosc produktow"
FROM produkty
GROUP BY kategoria
ORDER BY 1, 2
----