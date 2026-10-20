[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/3SRI_-8J)
[![Open in Codespaces](https://classroom.github.com/assets/launch-codespace-2972f46106e565e64193e422d61a12cf1da4916b45550586e14ef0a7c637dd04.svg)](https://classroom.github.com/open-in-codespaces?assignment_repo_id=23394099)
# Proiect PA 2025

Repository-ul conține scheletul proiectului și testele publice.

## Structură

`include/`
Headerele pentru modulele cerute.

`src/`
Fișierele pe care trebuie să le completați.

`tests/public/`
Teste publice pentru fiecare pas. Aici găsiți fișierele de intrare și ieșirea așteptată.

`build/`
Conține binarele pentru rularea testelor publice:
- `build/public_pas1`
- `build/public_pas2`
- `build/public_pas3`
- `build/public_pas4`

## Rulare teste publice

Pentru a rula toate testele publice:

```bash
make public-test
```

Pentru a rula testele publice doar pentru un pas:

```bash
./build/public_pas1 tests/public/pas1/entitati.csv tests/public/pas1/relatii.csv tests/public/pas1/interogari.txt
./build/public_pas2 tests/public/pas2/entitati.csv tests/public/pas2/relatii.csv tests/public/pas2/interogari.txt
./build/public_pas3 tests/public/pas3/entitati.csv tests/public/pas3/relatii.csv tests/public/pas3/interogari.txt
./build/public_pas4 tests/public/pas4/entitati.csv tests/public/pas4/relatii.csv tests/public/pas4/interogari.txt
```

Fiecare test public are și un fișier `expected.txt` cu rezultatul așteptat.

## Teste publice și teste private

Există două tipuri de teste:
- teste publice, incluse în acest repository;
- teste private, folosite la evaluare.

Faptul că testele publice trec nu garantează punctaj maxim.


 ## Completare :

 # Structuri :

 Graful - stocheaza faptul ca entitatile sunt pastrate intr-un vector dinamic , iar relatiile sunt de tip liste inlantuite pt fiecare nod. Acesta este folosit in favoarea unui matrice deoarece aceasta ar consuma mai multa memorie in mod inuti fata de graf.

 Arborele de cautare - utiizat pentru a nu exista duplicate in randul datelor adiacente nodurilor . Acesta functioneaza ca un index si functioneaza mai rapid fata de o cautare clasica dupa nume.

 Coada - este bazata pe o lista simplu inlanuita . Utilizata pt procesarea interogarilor in ordinea citirii acestora.

 Min-Heap - ste bazata pe un tablou dinamic alocat de heap indexat de la 0 . Acesta functioneaza precum o coada de prioritati pt algoritmul Djikstra.


# Complexitati :

Edge - O(log n) . Operatia se reduce la o cautare in arborele binar (BTS).

Edge - O(log(n) + grad(x)) . Mai inati se cauta nodurile x si y , iar apoi sunt parcurse muchiile spre iesire a nodului x pentru a evdea daca exista drum spre y.

Neighbors - O(log(n) + grad(x)) . Se gaseste nodul x iar apoi ii sunt printati vecinii.

# Algoritmi :

Path - O(n+m) , unde n - nr de noduri , iar m - nr de muchii.

Dijkstra - O((n+m)*log(n)) , n si m au aceeasi insemnatate ca la Path.

