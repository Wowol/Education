--ZAD21
SELECT id_prac, CAST(
             CASE 
                  WHEN placa_pod > 1850
                     THEN 'wiecej'
		  WHEN placa_pod = 1850
			THEN 'rowna'
		WHEN placa_pod < 1850
			then 'mniej'
             END AS varchar) 
FROM pracownicy ORDER BY 1, 2
----




