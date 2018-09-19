--ZAD4
create or replace function remove_duplicates(n text)
  returns void as
$$
begin
  EXECUTE '
    DELETE FROM ' || n || ' WHERE ctid NOT IN
(SELECT max(ctid) FROM ' || n || ' GROUP BY ' || n || '.*)';

end;
$$
language plpgsql;