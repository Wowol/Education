--ZAD3
ALTER TABLE zamowienia DROP CONSTRAINT "fk_zam_kli";
ALTER TABLE rabaty_klientow DROP CONSTRAINT "fk_zam_kli";
ALTER TABLE rabaty_klientow DROP CONSTRAINT "fk_zam_pol";

ALTER TABLE zamowienia ADD CONSTRAINT "fk_zam_kli" FOREIGN KEY (id_klienta) REFERENCES klienci(id_klienta) ON DELETE SET NULL;
ALTER TABLE rabaty_klientow ADD CONSTRAINT "fk_zam_kli" FOREIGN KEY(id_klienta) REFERENCES klienci(id_klienta) ON DELETE CASCADE;
ALTER TABLE rabaty_klientow ADD CONSTRAINT "fk_zam_pol" FOREIGN KEY(id_polecajacego) REFERENCES klienci(id_klienta) ON DELETE CASCADE;

ALTER TABLE zamowienia ALTER COLUMN id_klienta DROP NOT NULL;

DELETE FROM klienci;
DROP TABLE klienci CASCADE;