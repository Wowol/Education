--ZAD1
CREATE OR REPLACE FUNCTION pesel_check() RETURNS trigger AS $pesel_check$
BEGIN
  IF char_length(NEW.pesel) != 11 OR (SUBSTRING(NEW.pesel, 1, 1)::numeric*1+SUBSTRING(NEW.pesel, 2, 1)::numeric*3+SUBSTRING(NEW.pesel, 3, 1)::numeric*7+SUBSTRING(NEW.pesel, 4, 1)::numeric*9+SUBSTRING(NEW.pesel, 5, 1)::numeric*1+SUBSTRING(NEW.pesel, 6, 1)::numeric*3+SUBSTRING(NEW.pesel, 7, 1)::numeric*7+SUBSTRING(NEW.pesel, 8, 1)::numeric*9+SUBSTRING(NEW.pesel, 9, 1)::numeric*1+SUBSTRING(NEW.pesel, 10, 1)::numeric*3+SUBSTRING(NEW.pesel, 11, 1)::numeric*1)%10!=0 then
    RAISE EXCEPTION 'Niepoprawny PESEL';
  END IF;
  RETURN NEW;
END;
$pesel_check$ LANGUAGE plpgsql;

CREATE TRIGGER pesel_check BEFORE INSERT OR UPDATE ON pacjenci
FOR EACH ROW EXECUTE PROCEDURE pesel_check();

-- DELETE FROM pacjenci WHERE nazwisko='Buczek';

-- INSERT INTO pacjenci VALUES ('98101706951', 'Wojciech', 'Buczek')