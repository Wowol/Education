--ZAD1
SELECT nazwa FROM produkty WHERE id_kategoria=
(SELECT id_kategoria FROM produkty WHERE nazwa='Piórnik duży')