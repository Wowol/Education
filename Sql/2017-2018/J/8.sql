--ZAD8

SELECT *
FROM zwierzeta
ORDER BY CASE WHEN rodzaj = 'pies'
  THEN 1
         ELSE (CASE WHEN rodzaj = 'kot'
           THEN 2
               ELSE 3 END) END, nazwa