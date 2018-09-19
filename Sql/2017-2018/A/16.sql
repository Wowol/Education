--ZAD16
SELECT concat(nazwisko, repeat('.', 40-char_length(nazwisko)-char_length(etat) ), etat) as "nazwisko i etat" FROM pracownicy ORDER BY id_prac
----
