--ZAD7
DROP TABLE IF EXISTS szef_podwladny;
CREATE TABLE szef_podwladny AS
SELECT s.nazwisko as szef, p.nazwisko as podwladny
FROM pracownicy p
JOIN pracownicy s ON (p.id_szefa=s.id_prac)
WHERE p.nazwisko IS NOT NULL AND s.nazwisko IS NOT NULL
