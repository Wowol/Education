--ZAD19
SELECT nazwisko, to_char(zatrudniony, 'Month, DD YYYY') as data_zatrudnienia FROM pracownicy WHERE id_zesp=20 ORDER BY id_prac
----