--ZAD1
DROP TABLE IF EXISTS kategorie;
CREATE TABLE kategorie(
	id_kategoria serial PRIMARY KEY,
	nazwa varchar(250) NOT NULL UNIQUE,
	vat NUMERIC(3, 1) NOT NULL
);

INSERT INTO kategorie (nazwa, vat) SELECT DISTINCT(kategoria), vat from produkty;
ALTER TABLE produkty 
	DROP COLUMN IF EXISTS id_kategoria,

	ADD COLUMN id_kategoria integer REFERENCES kategorie(id_kategoria);
   
 
UPDATE produkty SET id_kategoria = (SELECT id_kategoria FROM kategorie WHERE kategoria=nazwa);

ALTER TABLE produkty ALTER COLUMN id_kategoria SET NOT NULL;

ALTER TABLE produkty DROP COLUMN kategoria, DROP COLUMN vat
