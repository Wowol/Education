--ZAD1
SELECT produkty.nazwa, klienci.nazwa FROM produkty CROSS JOIN klienci WHERE kategoria LIKE 'Artykuły%' AND email IS NOT NULL
ORDER BY 1,2
----