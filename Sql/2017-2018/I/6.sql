--ZAD6

DROP VIEW IF EXISTS pediatrzy;
CREATE VIEW pediatrzy AS
  SELECT id, imie, nazwisko
  FROM lekarze
    LEFT JOIN specjalizacje ON (id_lekarza = id)
  WHERE specjalizacja = 'Pediatria';

CREATE RULE ped AS ON INSERT TO pediatrzy DO INSTEAD (INSERT INTO lekarze VALUES (NEW.id, NEW.imie, NEW.nazwisko);
  INSERT INTO specjalizacje VALUES (NEW.id, 'Pediatria'));

