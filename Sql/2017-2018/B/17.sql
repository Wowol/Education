--ZAD17
SELECT (CASE WHEN nip is null THEN 'Brak' ELSE 'Podany' END) AS "NIP", count(nazwa) as "ilosc klientow" FROM klienci 
GROUP BY nip IS NULL
ORDER BY 1,2
----