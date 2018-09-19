--ZAD3a
SELECT kategorie.nazwa FROM kategorie WHERE id_kategoria IN 
(SELECT id_kategoria FROM produkty 
    GROUP BY id_kategoria
    HAVING COUNT(*)>=3)