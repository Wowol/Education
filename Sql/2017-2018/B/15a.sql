--ZAD15a
SELECT array_agg(numer_telefonu) as "lista telefonów" from klienci 
WHERE numer_telefonu IS NOT NULL
----