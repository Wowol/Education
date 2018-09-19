--ZAD4

-- Napisz wyzwalacz, który będzie gwarantował podstawową poprawność nowo wstawianych wizyt.
-- Poprawna wizyta nie może trwać dłużej niż jedną godzinę. Co więcej, jeden lekarz może badać
-- tylko jednego pacjenta na raz. Wyzwalacz nie powinien rzucać wyjątku.
CREATE OR REPLACE FUNCTION wizyty_all_check()
  RETURNS trigger AS $wizyty_all_check$
BEGIN
  IF (NEW.data_zakonczenia - NEW.data_rozpoczecia) > ('1 hour') :: INTERVAL
  THEN
    RETURN NULL;
  END IF;

  IF (
    (SELECT COUNT(*)
     FROM wizyty
     WHERE
       lekarz = NEW.lekarz AND
       ((data_rozpoczecia >= NEW.data_rozpoczecia and NEW.data_zakonczenia > data_rozpoczecia) OR
        (data_rozpoczecia <= NEW.data_rozpoczecia and NEW.data_rozpoczecia < data_zakonczenia))
    ) != 0)
  THEN
    RETURN NULL;
  END IF;
  RETURN NEW;
END;
$wizyty_all_check$
LANGUAGE plpgsql;

CREATE TRIGGER wizyty_all_check
  BEFORE INSERT
  ON wizyty
  FOR EACH ROW EXECUTE PROCEDURE wizyty_all_check();
