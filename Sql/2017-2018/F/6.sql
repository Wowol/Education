--ZAD6
DROP TABLE IF EXISTS plyty_cd;
CREATE TABLE plyty_cd (
    kompozytor char(100) NOT NULL,
    tytul_albumu char(100) NOT NULL,
    data_nagrania DATE,
    data_wydania DATE CHECK (data_nagrania<data_wydania),
    czas_trwania INTERVAL CHECK (czas_trwania < '82 minutes'),
    CONSTRAINT un_ko_ty UNIQUE (kompozytor, tytul_albumu)
)
