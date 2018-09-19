--ZAD14
SELECT count(nazwa) FROM produkty WHERE kategoria='Artykuły papiernicze'
GROUP BY kategoria
----