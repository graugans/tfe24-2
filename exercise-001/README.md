# Übungsaufgabe: Referenzen in C++ mit `fmt`

### Anmerkungen zum Programm
Wie sie bereits in ihrem Hinweis geschrieben haben, bewirkt die Übergabe einer Referenz in einer Funktion, dass die übergebene Variable direkt verändert werden kann. Generell lässt sich sagen, dass die Referenz eigentlich nur ein Pointer mit konstanter Adresse und variabeln Inhalt. Der Unterschied besteht darin, dass die Referenz immer auf eine Variable zeigt und nicht einfach NULL sein kann. Dadurch soll sie ein deutlich sichereres Programmieren ermöglichen. Daneben wird sie vom Compiler wegoptimiert und ist somit auch effizienter als ein herkömmlicher Pointer.
