--ZAD2
DROP TABLE IF EXISTS historia_cen;
CREATE TABLE historia_cen AS(
	SELECT kod_produktu, cena_netto FROM produkty
);

ALTER TABLE historia_cen
	ADD COLUMN data_wprowadzenia DATE;
	
UPDATE historia_cen set data_wprowadzenia ='2000-01-01'; 

ALTER TABLE historia_cen ALTER COLUMN data_wprowadzenia SET NOT NULL,
	ALTER COLUMN cena_netto SET NOT NULL;


ALTER TABLE historia_cen ADD PRIMARY KEY (kod_produktu, data_wprowadzenia);
	
	


ALTER TABLE historia_cen ADD FOREIGN KEY (kod_produktu)  REFERENCES produkty(kod_produktu);
ALTER TABLE produkty DROP COLUMN cena_netto
