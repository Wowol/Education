--ZAD5

DROP TABLE IF EXISTS lekarze_prowadzacy;
CREATE TABLE lekarze_prowadzacy (
  pesel  char(11) REFERENCES pacjenci (pesel) NOT NULL,
  lekarz integer REFERENCES lekarze (id)       NOT NULL
);
ALTER TABLE lekarze_prowadzacy
  ADD PRIMARY KEY (pesel, lekarz);

CREATE OR REPLACE FUNCTION dodaj_lekarza()
  RETURNS trigger AS $dodaj_lekarza$
declare
  b numeric;

BEGIN
  b =
  (SELECT
    id
  FROM lekarze
    LEFT JOIN specjalizacje ON (id = id_lekarza)
    LEFT JOIN lekarze_prowadzacy ON (id = lekarz)
  WHERE specjalizacja = 'Medycyna rodzinna'
  GROUP BY id
  ORDER BY COUNT(pesel), id
  LIMIT 1);
   INSERT INTO lekarze_prowadzacy VALUES(NEW.pesel, b);
  RETURN NEW;
END;
$dodaj_lekarza$
LANGUAGE plpgsql;

CREATE TRIGGER dodaj_lekarza
  AFTER INSERT
  ON pacjenci
  FOR EACH ROW EXECUTE PROCEDURE dodaj_lekarza();