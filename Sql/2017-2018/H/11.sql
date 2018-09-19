--ZAD11

CREATE SEQUENCE seq maxvalue 5000 START 1000 INCREMENT BY 10;

CREATE OR REPLACE FUNCTION bilans_kont()
 RETURNS TABLE (
 konto numeric(11),
 suma_wplat numeric(11,2),
 suma_wyplat numeric(11,2)
)
AS $$
BEGIN
 RETURN QUERY
  SELECT nr_konta as "Konto",
        COALESCE((SELECT SUM(kwota) as d FROM transakcje WHERE na_konto=nr_konta GROUP BY na_konto), 0),
        COALESCE((SELECT SUM(kwota) as c FROM transakcje WHERE z_konta=nr_konta GROUP BY z_konta), 0)
         FROM konta;
END; $$
LANGUAGE 'plpgsql';

CREATE OR REPLACE FUNCTION bonus_swiateczny(p NUMERIC DEFAULT 0.01) RETURNS void
AS $$
BEGIN
      INSERT INTO transakcje(id, na_konto, kwota)
              select nextval('seq'),konto,suma_wyplat*p from bilans_kont();
END; $$
LANGUAGE 'plpgsql';