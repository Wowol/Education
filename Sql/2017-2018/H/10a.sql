--ZAD10a
create or replace function silnia(a NUMERIC)
    returns NUMERIC as
$$
declare
	counter NUMERIC := 1;
	result NUMERIC := 1;
begin
    LOOP 
	 EXIT WHEN counter = a+1 ; 
	 result := result*counter;
	 counter := counter + 1; 
	 END LOOP ; 
	return result;

end;
$$
language plpgsql;
