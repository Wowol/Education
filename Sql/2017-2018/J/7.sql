--ZAD7

-- create table tab(id int, imie varchar(20), nazwisko varchar(30));
-- insert into tab values (5, 'Anna', 'Kowalska'), (10, 'Jan', 'Nowak'), (15, 'Andrzej', 'Chmielnicki'), (20, 'Wojciech', 'Szczepański'), (25, 'Józef', 'Gąbka'), (30, 'Grzegorz', 'Brzęczyszczykiewicz'), (35, 'Piotr', 'Ptak');
--

SELECT *, (ctid::text::point)[1] as numer  FROM tab WHERE (ctid::text::point)[1]::bigint%3=1