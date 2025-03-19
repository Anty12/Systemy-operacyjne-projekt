# Systemy operacyjne projekt
## Etap 1 - Problem jedzących filozofów
### Opis problemu
Pięciu filozofów siedzi przy stole i każdy wykonuje jedną z dwóch czynności – albo je, albo rozmyśla. Stół jest okrągły, przed każdym z nich znajduje się miska ze spaghetti, a pomiędzy każdą sąsiadującą parą filozofów leży widelec, a więc każda osoba ma przy sobie dwie sztuki – po swojej lewej i prawej stronie. Ponieważ jedzenie potrawy jest trudne przy użyciu jednego widelca, zakłada się, że każdy filozof korzysta z dwóch. Dodatkowo nie ma możliwości skorzystania z widelca, który nie znajduje się bezpośrednio przed daną osobą. Filozofowie nigdy nie rozmawiają ze sobą, co stwarza zagrożenie zakleszczenia w sytuacji, gdy każdy z nich zabierze lewy widelec i będzie czekał na prawy (lub na odwrót) [[Wikipedia](https://pl.wikipedia.org/wiki/Problem_ucztuj%C4%85cych_filozof%C3%B3w)].
### Wątki
- **philosopher** - wątek filozofa, który je (korzysta z zasobu) oraz (myśli)
### Sekcje krytyczne
- Dostęp do widelców - aby rozwiązać problem zakleszczenia, użyłem metody hierachi zasobów, czyli zasoby(widelce) są uporządkowane (mają ID) i podczas brania zasobów wątek(filozof) musi uzyskiwać dostęp od zasobu od najmniejszego ID do największego. Aby zapewnić prawidłowy dostęp, do odczyty zasobów użyłem własnych semaforów i operacji atomowych.
### Instrukcja uruchomienia
Aby uruchomić program należy jako argument podać ilość uruchamianych filozofów, przykład: project1 8 .
### Dodatek - program test
Pozwala sprawidzić, czy w program działa poprawnie, czyli sprawdza czy w danym momencie nie je przypadkiem dwóch sąsiadujących ze sobą filozofów. Program jako argument przyjmuje nazwę pliku testowego zawierającego logi programu, przykład: test log.txt .
