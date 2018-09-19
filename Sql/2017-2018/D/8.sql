--ZAD8
WITH RECURSIVE rodzice(bezposredni, topParent, oryginalnaKategoria ) AS (
    SELECT 
      nadkategoria, id_kategoria AS topParent, id_kategoria AS oryginalnaKategoria
    FROM kategorie
  UNION ALL
    SELECT
      c.nadkategoria, c.id_kategoria, r.oryginalnaKategoria
    FROM 
       rodzice r, kategorie c
    WHERE c.id_kategoria = r.bezposredni
  )
-- SELECT
--   oryginalnaKategoria AS category_id, topParent AS topParent 
-- FROM rodzice
SELECT q.nazwa as "nazwa kategorii", k.nazwa as "nazwa najwyższej nadkategorii" 
FROM rodzice r 
LEFT JOIN kategorie k ON r.topParent = k.id_kategoria
LEFT JOIN kategorie q ON r.oryginalnaKategoria = q.id_kategoria
WHERE
bezposredni IS NULL
GROUP BY topParent, oryginalnaKategoria, q.nazwa, k.nazwa