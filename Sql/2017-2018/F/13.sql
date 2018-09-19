--ZAD13
DROP TABLE IF EXISTS projekty, przydzialy;
CREATE TABLE projekty (
    id_projektu NUMERIC(4, 0) PRIMARY KEY,
    opis_projektu CHAR(20) NOT NULL,
    data_rozpoczecia DATE DEFAULT CURRENT_DATE,
    data_zakonczenia DATE CHECK (data_zakonczenia>data_rozpoczecia),
    fundusz NUMERIC(7, 2),
    CONSTRAINT un UNIQUE(opis_projektu)
);
CREATE TABLE przydzialy (
    id_projektu NUMERIC(4, 0) REFERENCES projekty(id_projektu),
    id_prac NUMERIC(4, 0) REFERENCES pracownicy(id_prac),
    od DATE DEFAULT CURRENT_DATE,
    "do" DATE CHECK ("do">od),
    stawka NUMERIC (7, 2),
    rola char(20) CHECK
        (rola IN ('KIERUJACY', 'ANALITYK', 'PROGRAMISTA')),
    CONSTRAINT pk PRIMARY KEY (id_projektu, id_prac)
);
ALTER TABLE przydzialy ADD COLUMN godziny NUMERIC;