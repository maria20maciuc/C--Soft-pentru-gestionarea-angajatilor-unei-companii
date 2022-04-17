# C-Soft-pentru-gestionarea-angajatilor-unei-companii

Functionalitati program:

* funcțiile angajaților sunt organizate într-un sistem ierarhic, acestea putând fi muncitor sau
manager;
* un manager poate fi CEO, Șef departament sau Team leader. Un muncitor nu are niciun
subordonat. Un șef de departament poate avea subordonați mai mulți team leaderi.
* fiecare angajat va avea: Nume, Salariu, Functie, Departament și lista cu angajații
subordonati;
* s-a definit o clasă template Meniu care sa gestioneze angajații (dupa tip). Clasa contine indexul unui angajat (incrementat automat la angajarea unei personae noi prin
supraîncărcarea operatorului +=) și un vector de pointeri la obiecte de tip Angajat, alocat
dinamic;
* informațiile sunt păstrate în fișiere.

Aplicatia permite urmatoarele actiuni:

* afișarea informațiilor despre toți angajații
* total cheltuieli cu salariile
* introducerea unui nou angajat (angajarea unei persoane în firmă)
* modificarea salariului unui angajat
