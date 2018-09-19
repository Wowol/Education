--ZAD2
CREATE OR REPLACE FUNCTION wizyty_check() RETURNS trigger AS $wizyty_check$
BEGIN
  IF NEW.data_zakonczenia IS NULL THEN
    NEW.data_zakonczenia=NEW.data_rozpoczecia+(30 ||' minutes')::interval;
  END IF;
  RETURN NEW;
END;
$wizyty_check$ LANGUAGE plpgsql;

CREATE TRIGGER pesel_check BEFORE INSERT ON wizyty
FOR EACH ROW EXECUTE PROCEDURE wizyty_check();