--ZAD10

CREATE OR REPLACE VIEW terminarz (pacjent, specjalista, termin_od, termin_do) AS
  select
    pacjent,
    specjalizacja,
    data_rozpoczecia,
    data_zakonczenia
  FROM wizyty CROSS JOIN specjalizacje
  WHERE false;

CREATE RULE umawianie AS ON INSERT to terminarz DO INSTEAD INSERT INTO wizyty
  SELECT
    id,
    NEW.pacjent :: char(11),
    NEW.termin_od :: TIMESTAMP,
    NEW.termin_do :: TIMESTAMP
  FROM lekarze
    LEFT JOIN specjalizacje ON (id = id_lekarza)
    LEFT JOIN wizyty ON (id = lekarz)
  WHERE specjalizacja = NEW.specjalista
  GROUP BY id, NEW.pacjent, NEW.termin_od, NEW.termin_do
  HAVING SUM(CASE WHEN
    (NEW.termin_od, NEW.termin_do)
    OVERLAPS
    (data_rozpoczecia, data_zakonczenia)
    THEN 1
             ELSE 0 END) = 0
  ORDER BY id
  LIMIT 1;
--
-- INSERT INTO terminarz VALUES ('43080817599', 'Chirurgia', '2008-07-25 07:59:00.000000', '2008-07-25 08:01:00.000000');
--
--
-- SELECT *
-- FROM wizyty;
-- SELECT
--   id,
--   '43080817599' :: char(11),
--   '2008-07-25 08:59:00.000000' :: TIMESTAMP,
--   '2008-07-25 09:04:00.000000' :: TIMESTAMP
-- FROM lekarze
--   LEFT JOIN specjalizacje ON (id = id_lekarza)
--   LEFT JOIN wizyty ON (id = lekarz)
-- WHERE specjalizacja = 'Chirurgia'
-- GROUP BY id
-- HAVING SUM(CASE WHEN
--   ('2008-07-25 08:59:00.000000', '2008-07-25 09:01:00.000000')
--   OVERLAPS
--   (data_rozpoczecia, data_zakonczenia)
--   THEN 1
--            ELSE 0 END) = 0
-- ORDER BY id
-- LIMIT 1;
--
--
-- SELECT *
-- FROM lekarze
--   LEFT JOIN specjalizacje ON (id = id_lekarza)
--   LEFT JOIN wizyty ON (id = lekarz)
--
-- INSERT INTO wizyty SELECT id,
-- SELECT *
-- FROM lekarze
--   LEFT JOIN specjalizacje ON (id = id_lekarza)
--   LEFT JOIN wizyty ON (id = lekarz)
-- WHERE specjalizacja = 'Chirurgia' AND NOT (
--   ('2008-07-25 08:59:00.000000', '2008-07-25 09:01:00.000000') OVERLAPS
--   (data_rozpoczecia, data_zakonczenia))
-- ORDER BY id
-- LIMIT 1;
--
--
-- SELECT *
-- FROM wizyty
--   LEFT JOIN
--
-- --
-- -- SELECT
-- --   id,
-- --   COUNT(pacjent)
-- -- FROM lekarze
-- --   LEFT JOIN specjalizacje ON (id = id_lekarza)
-- --   LEFT JOIN wizyty ON (id = lekarz)
-- -- WHERE specjalizacja = 'Medycyna rodzinna'
-- -- GROUP BY id
-- -- ORDER BY COUNT(pacjent), id
-- -- --   LIMIT 1