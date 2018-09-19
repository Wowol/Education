--ZAD11
DROP TABLE IF EXISTS projekty;
CREATE TABLE projekty (
    id_projektu NUMERIC(4, 0) PRIMARY KEY,
    opis_projektu CHAR(20) NOT NULL,
    data_rozpoczecia DATE DEFAULT CURRENT_DATE,
    data_zakonczenia DATE CHECK (data_zakonczenia>data_rozpoczecia),
    fundusz NUMERIC(7, 2),
    CONSTRAINT un UNIQUE(opis_projektu)
)