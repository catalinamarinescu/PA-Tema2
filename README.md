Marinescu Maria-Catalina 324CA
TEMA 2

-------------------------------------------------------------------------------

SUPERCOMPUTER
Pentru aceasta problema am folosit algoritmul lui Kahn cu BFS pentru sortare
topologica. Atat scheletul problemei, cat si algoritmul au fost preluate din
rezolvarea laboratorului 7 de pe OCW.
Pentru inceput am creat doua cozi pe care le-am populat conform algoritmului
lui Kahn cu nodurile care nu au parinte, fiecare coada fiind corespondenta cu 
cu cele doua seturi de date existente in problema.
In continuare, am aplicat de doua ori algoritmul deorece a trebuit sa fie luate
in considerare doua cazuri, si anume atunci cand la inceput nici una din cozi nu 
este goala trebuie vazuta care sortare topologica produce mai putine context
switch-uri, cea care incepe cu nodul cu setul de date 1 sau cu nodul cu setul de
date 2. In fiecare din cele doua cazuri am scos primul nod din coada si i-am 
luat vecinii apoi am scazut numarul de parinti pentru acesta si am vazut daca
mai are vreun parinte. Daca nu, atunci verificam daca are acelasi set de date cu
nodul curent si il adaugam in coada corespunzatoare. Daca mai are parinti atunci
nu se intampla nimic.
La final, dupa ce am format cele doua sortari topologice am numarat cate context
switch-uri exista in fiecare din ele si am returnat numarul mai mic.
Complexitatea acestui algoritm este O(n + m), n fiind numarul de noduri, iar m 
numarul de muchii. 

--------------------------------------------------------------------------------
MAGAZIN
Pentru a rezolva aceasta problema am folosit algoritmul DFS. Atat scheletul 
problemei, cat si algoritmul au fost preluate din rezolvarea laboratorului 7 de 
pe OCW. Am creat o lista de adiacenta pentru arbore, iar pentru intrebari am pus
datele in doi vectori, unul pentru depozitele de unde trebuie sa se 
plece(deposits), iar celalalt pentru numarul de expedieri consecutive(steps).
In cadrul algoritmului DFS am folosit doi vectori extra: sub_tree - vector in 
care pentru fiecare nod se numara cate noduri se afla in subgraful sau; 
position - vector in care pentru fiecare nod se retine pozitia sa in vectorul 
sortat dupa algoritm (sort). Pentru a popula vectorul result cu raspunsul la 
"intrebari" am parcurs cei doi vectori (deposits si steps), iar pentru a vedea 
care este nodul aflat la steps[i] distanta de deposits[i] trebuie ca steps[i] sa
fie mai mic sau egal cu numarul de noduri aflate in subgraf-ul depozitului
curent. Daca este mai mic atunci nodul se va afla la pozitia steps[i] distanta 
de pozitia depozitului in vectorul sort returnat de DFS. Daca este mai mare 
atunci se va afisa -1 deoarece nu se poate parcurge mai mult decat numarul de 
noduri din subgraf-ul depozitului respectiv.
Complexitatea algoritmului este O(n + q), n fiind numarul de noduri si q numarul
de "intrebari".   
