--ZAD9
SELECT DISTINCT(nazwa) FROM rabaty_produktow JOIN produkty ON (produkt=kod_produktu) WHERE min_ilosc=1 OR min_waga<waga ORDER BY 1