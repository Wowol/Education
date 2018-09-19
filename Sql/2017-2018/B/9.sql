--ZAD9
SELECT (CASE WHEN COUNT(DISTINCT adres_dostawy)=COUNT(adres_dostawy) THEN 'TAK' ELSE 'NIE' end) FROM zamowienia
----