--ZAD2
CREATE SEQUENCE seq maxvalue 99 START 10 INCREMENT BY 1;
INSERT INTO klienci VALUES
(nextval('seq'), 'Anna', 'Nowak'),
(nextval('seq'), 'Jan', 'Kowalski')