--ZAD17
SELECT CONCAT(SUBSTRING(etat, 1, 2),id_prac) AS wygenerowany_kod, id_prac, nazwisko, etat FROM pracownicy ORDER BY 1, 2, 3, 4;
----
