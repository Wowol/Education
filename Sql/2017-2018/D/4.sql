--ZAD4
SELECT * FROM rabaty WHERE data_do-data_od =
(SELECT max(data_do-data_od) FROM rabaty)