--ZAD9

CREATE RULE delet AS ON DELETE TO pacjenci DO ALSO DELETE FROM wizyty WHERE pacjent=OLD.pesel;