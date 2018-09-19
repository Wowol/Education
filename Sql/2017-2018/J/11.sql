--ZAD11
create or replace function remove_all()
    returns VOID as
$$
declare
   r RECORD;
begin
    FOR r IN (SELECT tablename FROM pg_tables WHERE schemaname = 'public') LOOP
        EXECUTE 'DROP TABLE IF EXISTS ' || quote_ident(r.tablename) || ' CASCADE';
    END LOOP;
end;
$$
language plpgsql;

SELECT remove_all();



