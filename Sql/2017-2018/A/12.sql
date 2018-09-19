--ZAD12
SELECT nazwisko, zatrudniony, etat FROM pracownicy WHERE EXTRACT(YEAR FROM zatrudniony)=1992 OR EXTRACT(YEAR FROM zatrudniony)=1993 ORDER BY 1, 2, 3
----





