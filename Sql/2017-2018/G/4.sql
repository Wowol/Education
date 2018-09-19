--ZAD4
ALTER TABLE etaty ADD COLUMN pensja_od NUMERIC(8, 2),  
    ADD COLUMN pensja_do NUMERIC(8, 2);
UPDATE etaty SET pensja_do=(CASE WHEN widelki[2]>widelki[1] THEN widelki[2] ELSE widelki[1] END);
UPDATE etaty SET pensja_od=(CASE WHEN widelki[2]>widelki[1] THEN widelki[1] ELSE widelki[2] END);
ALTER TABLE etaty DROP COLUMN widelki;

ALTER TABLE etaty 
    ALTER COLUMN pensja_od SET NOT NULL,
    ALTER COLUMN pensja_do SET NOT NULL,
    ADD CONSTRAINT larger CHECK (pensja_od<pensja_do);    