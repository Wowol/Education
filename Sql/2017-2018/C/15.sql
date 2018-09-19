--ZAD15
SELECT id_rabatu, znizka, (CASE WHEN id_klienta IS NULL THEN 'RABAT PRODUKTU' ELSE 'RABAT KLIENCKI' END) AS "typ rabatu" FROM rabaty
LEFT OUTER JOIN rabaty_klientow USING (id_rabatu)
ORDER BY 1,2,3