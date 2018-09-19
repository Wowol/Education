--ZAD10b
create or replace function silnia(a NUMERIC)
    returns NUMERIC as
$$
declare
begin
    IF (a = 0) THEN
        RETURN 1;
    ELSE
    return a*(silnia(a-1));
    END IF;
    
end;
$$
language plpgsql;