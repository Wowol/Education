--ZAD5
SELECT * FROM kategorie k WHERE vat < ANY 
(SELECT vat FROM kategorie q WHERE q.nadkategoria=k.id_kategoria)