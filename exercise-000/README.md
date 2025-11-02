## Übungsaufgabe Zeiger in C++ (exercise-000)

### Vorwort
Ich habe die Aufgabe nach bestem Wissen und gewissen ausgeführt. Da ich lieber auf meinem eigenen Computer arbeite, als im Codespace (aufgrund des Editors), habe ich statt `fmt::println()` `fmt::print()` benutzt. Das liegt daran, dass es anders Problemenicht richtig läuft und es ja im Endeffekt keinen großen Unterschied macht. 

### Aufgabe
#### Teil 1: Zeiger Grundlagen
Die Beschreibung nimmt hier den Programmablauf quasi schon vorweg.

#### Teil 2: Dynamische Speicherverwaltung
Die Pointer-Variable `d` wird als double pointer initialisiert. Dabei wird sie ebenfalls definiert, indem ihr durch `new` inklusive der double-"Funktion" der Pointer auf einen double im heap vom Wert `3.1415` zugewiesen wird.

#### Teil 3: Funktionen mit Zeigern
Der Unterschied der beiden Funktionen liegt darin, dass bei `void changeValueByParameter(int value)` die Variable als Parameter und bei `void changeValueByPointer(int* ptr)` die Variable als Pointer, bzw. ihre Adresse übergeben wird. Neben syntaktischer Unterschiede innerhalb der Funktion, ist es wichtig zu beachten, dass bei der Parameterübergabe eine Kopie der Variable erstellt wird. Das führt dazu, dass eine Änderung der Übergabevariable innerhalb der Funktion, keinen Einfluss auf die orginale Funktion hat. Bei der Übergabe als Pointer (oder Adresse) wird die Adresse oder der Pointer zwar ebenfalls kopiert, allerdings verändert sich bei der Änderung des Inhalts der Adresse natürlich auch der Inhalt der ursprünglichen Variable, der ja hinter dieser Adresse steht (Im übertragende Sinne). 
