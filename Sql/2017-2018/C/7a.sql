--ZAD7a
SELECT b.nazwa, c.nazwa FROM rabaty_klientow a 
NATURAL JOIN klienci b JOIN klienci c ON (id_polecajacego=c.id_klienta)
ORDER BY 1,2