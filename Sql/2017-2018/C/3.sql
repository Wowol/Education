--ZAD3
SELECT DISTINCT (produkty.nazwa) FROM produkty_zamowienia JOIN zamowienia 
USING (id_zamowienia) JOIN produkty ON (produkty_zamowienia.produkt=produkty.kod_produktu)
 WHERE zamowienia.adres_dostawy LIKE 'ul. Kubusia Puchatka%' ORDER BY 1
----