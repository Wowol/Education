--ZAD3
DROP TABLE IF EXISTS uczelnie;
CREATE TABLE uczelnie (
    id_uczelni NUMERIC(4, 0) PRIMARY KEY,
    nazwa varchar(100),
    adres varchar(100),
    budzet NUMERIC(10, 2) NOT NULL,
    zalozona DATE NOT NULL,
    CONSTRAINT og UNIQUE (nazwa)
)
