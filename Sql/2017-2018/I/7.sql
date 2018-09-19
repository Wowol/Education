--ZAD7

DROP VIEW IF EXISTS chirurdzy;
CREATE VIEW chirurdzy AS
  SELECT id, imie, nazwisko
  FROM lekarze
    LEFT JOIN specjalizacje ON (id_lekarza = id)
  WHERE specjalizacja = 'Chirurgia';

CREATE RULE protec AS ON DELETE TO chirurdzy
DO INSTEAD NOTHING;

