--ZAD7
SELECT B.nazwa
    ,A.IloscZmian
FROM (
        SELECT kod_produktu
            ,COUNT(DISTINCT data_wprowadzenia) AS IloscZmian
        FROM historia_cen
        WHERE DATE_PART('month',data_wprowadzenia) = 4
        GROUP BY kod_produktu
        ) A
    INNER JOIN produkty B ON A.kod_produktu = B.kod_produktu
WHERE A.IloscZmian >= 2

