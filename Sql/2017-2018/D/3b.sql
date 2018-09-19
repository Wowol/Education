--ZAD3b
SELECT (SELECT nazwa FROM kategorie k WHERE k.id_kategoria=p.id_kategoria)
    FROM produkty p
    GROUP BY id_kategoria
    HAVING count(*)>=3