# Wstęp

W ramach projektu należało napisać klienta oraz serwer zgodnie z protokołem [RFC-7440](https://tools.ietf.org/html/rfc7440).

# Klient

Klienta uruchamiamy poleceniem python3 client.py. Na ekranie zostaną wypisane argumenty wymagane oraz opcjo-
nalne. Można również użyć argumentu -h, aby pokazać sposób użycia.

# Serwer

Serwer uruchamiamy poleceniem python3 server.py. Na ekranie zostaną wypisane argumenty wymagane oraz opcjo-
nalne. Można również użyć argumentu -h, aby pokazać sposób użycia.

# RFC-7440

Zarówno klient, jak i serwer, działają zgodnie ze standardem [RFC-7440](https://tools.ietf.org/html/rfc7440). Klient defaultowo ma wielkość window
równą 1 - działa wtedy tak, jak zostało opisane w standardzie [RFC-1350](https://tools.ietf.org/html/rfc1350). Wielkość tą możemy modifikować flagą
-w.

# Testy

Klient oraz serwer był testowany poprzez nadanie prawdopodobienstwa wysłania pakietu. Oba dobrze radziły sobie
z tymi problemami.


