--ZAD3
create or replace function nulls(VARIADIC arr anyarray)
  returns INT AS $$
declare
  tempp INT;
BEGIN
  tempp = 0;
  FOR i IN 1..array_length(arr, 1) LOOP
    if arr[i] IS NULL
    THEN
      tempp = tempp + 1;
    end if;
  END LOOP;
  return tempp;
end;
$$
language plpgsql;