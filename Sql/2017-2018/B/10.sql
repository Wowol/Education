--ZAD10
SELECT id_klienta FROM zamowienia
GROUP BY id_klienta
HAVING COUNT(id_klienta)>=2
ORDER BY 1
----