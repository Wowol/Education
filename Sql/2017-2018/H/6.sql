--ZAD6
create or replace function oblicz_koszt(NUMERIC(11, 2))
    returns NUMERIC(11, 2) as
$$
begin
    return ROUND($1*0.02, 2);
end;
$$
language plpgsql;