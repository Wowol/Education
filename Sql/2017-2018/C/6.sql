--ZAD6
SELECT DISTINCT(klienci.nazwa), klienci.email FROM klienci NATURAL JOIN zamowienia WHERE date_part('month', data_zlozenia)=3
ORDER BY 1, 2