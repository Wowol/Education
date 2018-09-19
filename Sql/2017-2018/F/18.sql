--ZAD18
DROP TABLE IF EXISTS pracownicy_zespoly;
CREATE TABLE pracownicy_zespoly AS
SELECT nazwisko, etat, placa_pod*12 as roczna_placa, z.nazwa as zespol, z.adres as adres_pracy
FROM pracownicy JOIN zespoly z USING (id_zesp)