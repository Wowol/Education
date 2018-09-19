--ZAD4
SELECT klienci.nazwa as "nazwa klienta", (case WHEN COUNT(DISTINCT adres_dostawy)>=2 THEN 'TAK' ELSE 'NIE' END) as "rozne adresy" FROM klienci 
JOIN zamowienia USING (id_klienta) GROUP BY id_klienta ORDER BY 1,2
----