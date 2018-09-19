--ZAD8
SELECT SUM(cena_netto) FROM PRODUKTY
HAVING MAX(cena_netto)>=300
----