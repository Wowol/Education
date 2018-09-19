--ZAD12

CREATE OR REPLACE FUNCTION stan_konta (konto numeric(11), d TIMESTAMP)
 RETURNS NUMERIC(11, 2)
AS $$
declare 
b numeric = 0;
k numeric(11, 2);
arr numeric[] = '{}';
BEGIN
  arr = (SELECT array_agg(CASE WHEN na_konto=konto THEN kwota ELSE kwota*-1 END ORDER BY data_zlecenia) from transakcje
        WHERE data_zlecenia<=d AND (z_konta=konto OR na_konto=konto));
    if arr IS NULL OR array_length(arr, 1)=0 THEN
        RETURN 0;
    end IF;
 FOREACH k IN ARRAY arr
    LOOP
        b = b+k;
        IF b<0 THEN
            RAISE EXCEPTION 'Wykryto ujemny bilans konta';
        END IF;
    END LOOP;
    return b;
END; $$
LANGUAGE 'plpgsql';


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