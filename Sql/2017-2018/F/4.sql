--ZAD4
DROP TABLE IF EXISTS ksiazki;
CREATE TABLE ksiazki (
    id_ksiazki NUMERIC(10, 0) PRIMARY KEY,
    tytul varchar(100) NOT NULL,
    autorzy varchar(100),
    cena NUMERIC(6, 2),
    data_wydania DATE
)
