--ZAD5
CREATE OR REPLACE VIEW wplaty_wyplaty AS
(
     SELECT nr_konta as "Konto", 
        COALESCE((SELECT COUNT(*) as c FROM transakcje WHERE z_konta=nr_konta GROUP BY z_konta), 0) as "Ilosc wyplat",
        COALESCE((SELECT COUNT(*) as d FROM transakcje WHERE na_konto=nr_konta GROUP BY na_konto), 0) as "Ilosc wplat"
         FROM konta AS "Ilosc wyplat"
);
SELECT * FROM wplaty_wyplaty;
INSERT INTO transakcje(id, na_konto, kwota) VALUES (200, 1004, 500);
SELECT * FROM wplaty_wyplaty;
DROP VIEW wplaty_wyplaty;