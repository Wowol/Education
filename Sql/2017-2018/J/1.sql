--ZAD1
create or replace function cast_int(a varchar)
    returns INT AS $$
declare
tempp INT;
BEGIN
    tempp=a;
    return tempp;
    EXCEPTION WHEN others THEN
        return NULL;
end;
$$
language plpgsql;
