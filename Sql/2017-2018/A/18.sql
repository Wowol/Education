--ZAD18
SELECT nazwisko, regexp_replace(nazwisko, '[KkLlMm]', 'X', 'g') AS zmienione_nazwisko FROM pracownicy ORDER BY 1, 2;
----
