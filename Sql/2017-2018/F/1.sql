--ZAD1
DROP TABLE IF EXISTS zwierzeta;
CREATE TABLE zwierzeta (
    gatunek varchar(100) NOT NULL,
    jajorodny char CHECK (jajorodny='T' OR jajorodny='N') NOT NULL,
    liczba_konczyn INT CHECK (liczba_konczyn < 100) NOT NULL,
    data_odkrycia DATE NOT NULL
)
