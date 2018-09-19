--ZAD8
SELECT k.* from klienci k LEFT OUTER JOIN rabaty_klientow r USING (id_klienta) WHERE id_rabatu IS NULL 
ORDER BY 1,2,3,4,5