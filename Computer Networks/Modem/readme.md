# Wstęp

W ramach projektu należało napisać serwer, który nasłuchuje sygnały z mikrofonu i interpretujący je we własciwy
sposób, oraz klienta, który te sygnały wysyła.
Do wysyłania sygnałów używamy dwóch częstotliwości, zdefiniowanych w pliku config.py. Na chwilę obecną sygnał
interpretujemy jako częstotliwość 7000, a brak sygnału jako 5000 (można te wartości zmodyfikować w tym pliku).
Ramki, z którymi wysyłamy sygnały, są podobne do ramek ethernetu, tzn mamy:

- preambuła, postaci 10101011
- 1 bajt adresu odbiory
- 1 bajt adresu nadawcy
- 1 bajt długości
- 4 bajty sumy kontrolnej CRC

```
Wszystkie bity sa zakodowane 4 B 5 B + N RZ
```
# Serwer

Serwer uruchamiamy poleceniem _python3 server.py_. Serwer oczekuje na ramki, gdy dostanie poprawną, wypisze
tuplę: (odbiorca, nadawca, wiadomość).

Opis synchronizacji odczytu bitów w serwerze:
Czytamy paczkę rozmiaru 2 _∗f ramerate∗seconds_. Paczkę tą dzielę na małe okienka, każde okienko jest o długości
_f ramerate∗seconds_ , a zaczyna się w: _f rameraten∗seconds∗k_ , gdzie _k_ - numer okienka, _n_ - liczba okienek, z góry usta-
lona w pliku _config.py_. W każdym okienku uruchamiamy szybką transformatę fouriera, oraz patrzymy się, która
z wartości dla argumentów: (częstotliwość dla bitu 1), (częstotliwość dla bitu 0) jest w tej transfromacie większa.
Następnie, jako błąd, liczona jest wartość bezwględna dla róznicy tych wartości. Te dwie rzeczy, czyli bit, oraz błąd,
dodajemy do tablicy dla danego okienka.

Następnie patrzymy na tablicę wartości dla okienek. Jeżeli w którymś okienku ostatnie 8 bitów jest równoważ-
ne preambule, to to okienko uznajemy za dobrego kandydata do czytania całej ramki. Jeżeli więcej niż jedno
okienko ma taką własność, to wybieramy to, którego suma błędów jest jak najmniejsza.

Jeżeli nie znaleźliśmy takiego okienka, to usuwamy pierwsze _f ramerate∗seconds_ wartości z bufora, oraz do-
czytujemy do niego kolejne _f ramerate∗seconds_ wartości z mikrofonu i powtarzamy te kroki.

Jeżeli znaleźliśmy najlepsze okienko, to czytamy tylko te bity, które są w wybranym okienku. Jeżeli przeczyta-
ne bity odpowiednio rozkodowane mogą być ramką, dekodujemy ją oraz wypisujemy na standardowe wyjście.

Serwer będzie działał w nieskończoność, chyba, że wartość _endserverafterreceivingtests_ w pliku _config.py_ jest
równa _false_ , wtedy serwer zakończy się po prawidłowym odczytaiu _numberoftests_ wiadomości (flaga ta jest przy-
datna do testów).

# Klient

Klienta uruchamiamy poleceniem _python3 client.py NADAWCA ODBIORCA_. Następnie wpisujemy wiadomo-
ści przeznaczone do wysłania. Program czeka na zakończenie wejścia, czyli po skończeniu wpisywania naciskamy
_CTRL+D_. Następuje wówczas wysyłanie ramek (czyli wysyłanie odpowiednich częstotliwości do głośnika).

# Testy

Do przeprowadzenia testów zostały napisane specjalne skrypty: _testclient.py_ oraz _test.sh_. Pythonowy skrypt
_testclient.py_ losuje _numberoftests_ wiadomości o długości _stringlength_ (obie wartości są zdefiniowane w pliku
config.py). Należy mieć na uwadze, że wiadomości nie mogą być dłuższe niż 255 znaków, ponieważ mamy tylko 1
bajt długości. Skrypt losuje również numer adresata i numer nadawcy. Następnie odbywa się standardowe wysyłanie
ramek, tak jak w zwykłym kliencie. Dodatkowo, skrypt wypisuje na standardowe wyjście tuplę (odbiorca, nadawca,
wiadomość):

Bashowy skrypt _test.sh_ pozwala w łatwy sposób przetestować rozwiązanie. Skrypt ten uruchamia _server.py_ oraz
_testclient.py_ , oraz patrzy, czy:

1. Serwer się zakończył (przed uruchomieniem tego skryptu koniecznie należy ustawić flagę _endserverafterreceivingtests_
    na _True_ )
2. Wyjście dla serwera jest takie samo jak wyście dla testclienta.

Jeżeli oba warunki zostaną spełnione, skrypt zakończy się z kodem 0 oraz nic nie wypisze. Jeżeli któryś warunek
nie zostanie spełniony, zostanie wypisana odpowiednia wiadomość oraz skrypt zakończy się z kodem 1.

# Wnioski z testów

Serwer poprawnie odczytuje bity przy wysyłaniu 100 bitów na sekundę, przy podziale na 10 ramek oraz często-
tliwości 5000, 7000, odpowiednio dla bitu 1 oraz bitu 0. Zmiana częstotliwości nie wpływała na prędkość (jeżeli
częstotliwości były odpowiednio od siebie odległe). Liczba ramek wpływała na wynik - przy wartości mniejszej niż
5 serwer nie radził sobie z dobrą synchronizacją.
