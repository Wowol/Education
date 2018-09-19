--ZAD5
CREATE FUNCTION array_intersect(a anyarray, b anyarray)
  RETURNS anyarray
  language sql
as $FUNCTION$
    SELECT ARRAY(
        SELECT UNNEST(a)
        INTERSECT
        SELECT UNNEST(b)
    );
$FUNCTION$;