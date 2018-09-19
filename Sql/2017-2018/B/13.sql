--ZAD13
SELECT kategoria, ROUND(COALESCE(VARIANCE(cena_netto), 0), 2) as wariancja, ROUND(COALESCE(STDDEV(cena_netto), 0), 2) as "standardowe odchylenie" from produkty
GROUP BY kategoria
ORDER BY 1,2,3

----