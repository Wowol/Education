--ZAD9

-- DROP TABLE IF EXISTS tab;
-- CREATE TABLE tab(
-- 	a int,
-- 	b char(3) NOT NULL CHECK (b IN ('tak', 'nie'))
-- );
-- INSERT INTO tab VALUES (1,'tak'), (2,'nie'), (3,'nie'), (4,'tak'), (5,'tak');

ALTER TABLE tab DROP CONSTRAINT tab_b_check;
ALTER TABLE tab ALTER COLUMN b DROP DEFAULT;
ALTER TABLE tab ALTER b TYPE bool USING CASE WHEN b='nie' THEN FALSE ELSE TRUE END;
ALTER TABLE tab ALTER COLUMN b SET DEFAULT FALSE;

-- SELECT * FROM tab;
