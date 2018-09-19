--ZAD2
DROP TABLE IF EXISTS klienci;
CREATE TABLE klienci (
    pesel char(11) PRIMARY KEY,
    adres varchar(100),
    wiek NUMERIC(2, 0) NOT NULL,
    wspolpraca_od DATE NOT NULL
)
