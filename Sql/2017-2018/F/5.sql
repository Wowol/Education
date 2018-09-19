--ZAD5
DROP TABLE IF EXISTS pokoje;
CREATE TABLE pokoje (
    numer_pokoju NUMERIC(3, 0) PRIMARY KEY,
    id_zesp NUMERIC(2, 0) REFERENCES zespoly(id_zesp),
    liczba_okien NUMERIC (1, 0)
)
