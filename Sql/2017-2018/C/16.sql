--ZAD16
SELECT (CASE WHEN COUNT (*) > 0 THEN 'TAK' else 'NIE' END) FROM rabaty_klientow a
CROSS JOIN rabaty_klientow b
WHERE a.id_klienta=b.id_polecajacego AND b.id_klienta=a.id_polecajacego