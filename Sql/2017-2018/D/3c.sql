--ZAD3c
SELECT kategorie.nazwa FROM kategorie JOIN produkty USING (id_kategoria)
GROUP BY id_kategoria
HAVING count(*)>=3