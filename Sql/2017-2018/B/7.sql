--ZAD7
SELECT COUNT(CASE WHEN waga<1000 THEN 1 ELSE NULL END)
FROM produkty
ORDER BY 1
----