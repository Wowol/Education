--ZAD14

CREATE OR REPLACE FUNCTION stan_konta(konto numeric(11), d TIMESTAMP)
  RETURNS NUMERIC(11, 2)
AS $$
declare
  b   numeric = 0;
  k   numeric(11, 2);
  arr numeric [] = '{}';
BEGIN
  arr = (SELECT array_agg(CASE WHEN na_konto = konto
    THEN kwota
                          ELSE kwota * -1 END
  ORDER BY data_zlecenia)
         from transakcje
         WHERE data_zlecenia <= d AND (z_konta = konto OR na_konto = konto));
  if arr IS NULL OR array_length(arr, 1) = 0
  THEN
    RETURN 0;
  end IF;
  FOREACH k IN ARRAY arr
  LOOP
    b = b + k;
  END LOOP;
  return b;
END; $$
LANGUAGE 'plpgsql';

CREATE OR REPLACE FUNCTION historia_konta(konto numeric(11))
  RETURNS TABLE(
    data TIMESTAMP,
    stan numeric(11, 2)
  )
AS $$
declare
  b   numeric = 0;
  k   numeric(11, 2);
  arr numeric [] = '{}';
BEGIN
  RETURN QUERY
  SELECT
    data_zlecenia,
    stan_konta(konto, data_zlecenia)
  from transakcje
  WHERE z_konta = konto OR na_konto = konto
  ORDER BY data_zlecenia;
END; $$
LANGUAGE 'plpgsql';

CREATE OR REPLACE FUNCTION moment_rozspojniajacy()
  RETURNS TIMESTAMP
AS $$
declare
  b   numeric = 0;
  k   numeric(11, 2);
  arr numeric [] = '{}';
BEGIN
  RETURN (
    SELECT (SELECT data
            FROM historia_konta(z_konta)
            WHERE stan < 0
            ORDER BY data
            LIMIT 1) chuj
    from transakcje
    ORDER BY chuj
    LIMIT 1
  );
END; $$
LANGUAGE 'plpgsql';

-- SELECT * FROM moment_rozspojniajacy()
--  SELECT CASE WHEN na_konto=1001 THEN kwota ELSE kwota*-1 END, data_zlecenia from transakcje
--      WHERE data_zlecenia<=to_date('2014-12-02', 'YYYY-MM-DD') AND (z_konta=1001 OR na_konto=1001) ORDER BY data_zlecenia
-- SELECT * FROM stan_konta(1001::NUMERIC, to_date('2014-11-02', 'YYYY-MM-DD'));


-- CREATE OR REPLACE FUNCTION stan_konta(konto NUMERIC(11), czas TIMESTAMP)
--     returns integer as
-- $$
-- declare
--     b       integer;
-- begin
--     b = a + 1;
--     return b;
-- end;
-- $$
-- language plpgsql;
-- SELECT * FROM transakcje;
-- SELECT * FROM konta;
-- UPDATE transakcje SET kwota=2000 WHERE id=105