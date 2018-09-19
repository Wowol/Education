--ZAD4
SELECT nazwisko, COALESCE(placa_pod,0) + COALESCE(placa_dod,0) as placa FROM pracownicy ORDER BY 1, 2
----