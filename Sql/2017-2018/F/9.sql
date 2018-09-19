--ZAD9
DROP TABLE IF EXISTS plyty_cd;
CREATE TABLE plyty_cd (
    kompozytor char(100) NOT NULL,
    tytul_albumu char(100) NOT NULL,
    data_nagrania DATE,
    data_wydania DATE CHECK (data_nagrania<data_wydania),
    czas_trwania INTERVAL CHECK (czas_trwania < '82 minutes')
    --CONSTRAINT un_ko_ty PRIMARY KEY (kompozytor, tytul_albumu)
);
INSERT INTO plyty_cd VALUES ('abc', 'tytul_albumu', 
    '2014-01-01', '2014-01-04', '20 minutes');
INSERT INTO plyty_cd VALUES ('abc', 'tytul_albumu', 
    '2014-01-01', '2014-01-04', '20 minutes');
