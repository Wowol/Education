--ZAD8

CREATE OR REPLACE RULE protec AS ON DELETE TO lekarze
  WHERE OLD.id IN (select id
                   from lekarze
                     left join specjalizacje s2 on lekarze.id = s2.id_lekarza
                   WHERE specjalizacja = 'Chirurgia') DO INSTEAD NOTHING;

