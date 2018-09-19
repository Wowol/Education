using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace App
{
    static class SqlQueryConsts
    {
        public const string ALL_TABLES_QUERY = "SELECT table_name FROM information_schema.tables WHERE table_schema='ksiegarnia_internetowa' AND table_type = 'BASE TABLE'";
        public const string SELECT_ALL_QUERY = "SELECT * FROM ";

        public const string BOOKS_QUERY = @"CREATE OR REPLACE VIEW books_query as SELECT
                      tytul,
                      rocznik,
                      string_agg(distinct (imie || ' ' || nazwisko), ', ') as autorzy,
                      string_agg(distinct (cena || ' zł') :: varchar, ', ')         as ceny,
                      string_agg(distinct (w2.nazwa), ', ')                as wydawnictwa
                    FROM ksiazki k
                      LEFT JOIN gatunki_ksiazek ON(isbn = id_ksiazki)
                      LEFT JOIN gatunki g on gatunki_ksiazek.id_gatunku = g.id
                      LEFT JOIN autorzy_ksiazek a on k.isbn = a.id_ksiazki
                      LEFT JOIN autorzy a2 on a.id_autora = a2.id
                      LEFT JOIN wydawnictwa w2 on k.wydawnictwo = w2.id
                      LEFT JOIN formaty_ksiazek fk ON isbn = fk.id_ksiazki
                      LEFT JOIN formaty f ON id_formatu = f.id
                    GROUP BY isbn, tytul;";

        public const string BOOKS_STATS = @" CREATE OR REPLACE VIEW books_stats as
            SELECT isbn, tytul, coalesce((SELECT count(*) FROM zamowienia
            WHERE id_ksiazki=isbn group by isbn), 0) as ilosc 
            FROM ksiazki;";

        public const string CITY_STATS = @" CREATE OR REPLACE VIEW city_stats as
            SELECT m.miasto, 
            coalesce((SELECT count(*) from zamowienia join adresy a on adres_dostawy=id
            where a.miasto=m.miasto group by a.miasto), 0) as liczba
            FROM miasta m;";

        public const string WYD_STATS = @" CREATE OR REPLACE VIEW wyd_stats as
            SELECT w.id, w.nazwa,
            coalesce((SELECT count(*) from zamowienia join ksiazki k on id_ksiazki=k.isbn
            where k.wydawnictwo=w.id group by nazwa), 0) as liczba_zamowien
            FROM wydawnictwa w;";

        public const string ZAM_STATS = @" CREATE OR REPLACE VIEW zamowienia_koszty AS
  SELECT id_zamowienia, cena*ilosc as suma FROM zamowienia z JOIN formaty_ksiazek fk ON (z.id_formatu = fk.id_formatu AND z.id_ksiazki = fk.id_ksiazki)";

    }
}
