--ZAD3
CREATE OR REPLACE FUNCTION wizyty_del_check() RETURNS trigger AS $wizyty_del_check$
BEGIN
  IF (CURRENT_TIMESTAMP-OLD.data_rozpoczecia)<('5 years')::INTERVAL THEN
    RETURN NULL;
  END IF;
  RETURN OLD;
END;
$wizyty_del_check$ LANGUAGE plpgsql;

CREATE TRIGGER pesel_check BEFORE DELETE ON wizyty
FOR EACH ROW EXECUTE PROCEDURE wizyty_del_check();

-- DELETE FROM wizyty WHERE pacjent='98101706950';

-- SELECT * FROM wizyty;