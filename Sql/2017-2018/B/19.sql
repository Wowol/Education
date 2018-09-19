--ZAD19
SELECT to_char(data_zlozenia, 'Month') as "Miesiac", count(id_zamowienia) as "Ilosc zamowien" FROM zamowienia
GROUP BY to_char(data_zlozenia, 'Month')
ORDER BY 1,2
----