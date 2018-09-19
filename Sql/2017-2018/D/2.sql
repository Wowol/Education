--ZAD2
SELECT nazwa FROM produkty where id_kategoria in 
(SELECT id_kategoria FROM kategorie WHERE nadkategoria IS NOT NULL)