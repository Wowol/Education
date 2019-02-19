# Wstęp

W ramach projektu należało napisać algorytm link state + bfs oraz następujące scenariusze sieci:

- Hiperkostka
- Cykl z awaryjną krawędzią
- Losowe grafy geograficzne

# 1 Link state + bfs

Pakiety dzielimy na 2 typy: zwykłe wysyłające informacje, oraz metapakiety, wysyłające następujące dane:

- Źródło (z którego routera został wysłany pakiet)
- Aktualny tickrate dla źródła
- Lista routerów, z którymi połączony jest router wysyłający metapakiet.

W każdym ticku routera patrzymy na przybyłe pakiety. Jeżeli któryś pakiet jest metapakietem, to rozpatrza-
my go osobno. W takim przypadku patrzymy się najpierw, czy nie otrzymaliśmy wcześniej nowszej informacji od
routera, który ten metapakiet rozsyła. Jeżeli tak, to ignorujemy nową wiadomość. Jeżeli nie, to musimy zaktualizo-
wać graf routera. Dodajemy odpowiednie krawędzie, które otrzymaliśmy w wiadomości. Następnie puszczany jest
algorytm bfs na tym grafie, aby było wiadomo, do którego linka trzeba wysłać pakiet, aby szedł jak najkrótszą
trasą do routera docelowego. Następnie metapakiet, który dostaliśmy, rozsyłamy dalej do wszystkich sąsiadów, a
dokładniej dajemy go do kolejki wysyłanych pakietów.

Raz na 50 ticków każdy router wysyła taki metapackiet zawierający informację o nim samym do wszystkich
jego sąsiadów. W pozostałym przypadku router wysyła skolejkowane pakiety tak, aby nie wysłać dwóch pakietów
tym samym linkiem.

# 2 Scenariusze

## 2.1 Hiperkostka

Hiperkostka to graf, w którym każdy router jest połączony z innym, jeżeli różnią się na dokładnie jednym bicie. W
napisanym scenariuszu hiperkostka jest 4-wymiarowa (czyli 16 routerów). W każdym ticku symulacji z prawdopo-
dobienstwem 5% jest wysyłany pakiet przez losowo wybrane 2 routery.

## 2.2 Cykl z awaryjną krawędzią

Graf jest cyklem 100 elementowym, w którym jeden link między routerami 0, 99 wyłącza się co 5 ticków, oraz
włącza co 10. Takie ustawienie przy naszym algorytmie spowoduje, że jest pakiet wysłany z routera 90 do routera
10 ma dużą szansę nie dojść do celu, gdyż algorytm będzie ciągle wybierał najkrótszą ścieżkę.

### 1


## 2.3 Losowe grafy geograficzne

Mamy losowo rozmieszczone routery na mapie 100 _x_ 100. Każdy router ma losowy wektor, według którego będzie
się poruszał co 20 ticków. 2 routery są ze sobą połączone bezpośrednim linkiem, jeżeli są w odpowiednio niedużej
od siebie odległości. W każdym ticku z prawdopodobienstwem 50% losowo wybrany router będzie chciał wysłać
pakiet do innego losowo wybranego.

# 3 Testy

Do skryptu _simulate.py_ została dodana możliwość dodania parametru _-s_ (silent), która powoduje wypisanie tylko
wyników (bez słów). Zwracany jest więc wtedy output: _delievery rate_ , _avg time_.
Do przeprowadzenia testów zostały napisany pythonowy skrypt _test.py_. Testowane są tylko scenariusze hiperkostki
oraz grafów geograficznych, gdyż scenariusz z awaryjną krawędzią w większości przypadków daje skuteczność 0%.
Każdy z testów został uruchomiony 50 razy, została wzięta średnia z wyników.

# 4 Wyniki

| Scenariusz   	| Delievery rate 	| Average time 	|   	|   	|
|--------------	|----------------	|--------------	|---	|---	|
| Hiperkostka  	| 99.81%         	| 4            	|   	|   	|
| Geograficzny 	| 72.64%         	| 50           	|   	|   	|
| Awaryjny     	| 0%             	| -            	|   	|   	|

