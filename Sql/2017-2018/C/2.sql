--ZAD2
SELECT zamowienia.data_zlozenia, klienci.nazwa FROM
 zamowienia JOIN klienci USING (id_klienta) WHERE 
 klienci.nip IS NOT NULL ORDER BY 1,2
----