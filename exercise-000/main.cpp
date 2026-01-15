#include <fmt/chrono.h>
#include <fmt/format.h>
#include <iostream>
#include "config.h"

// Definieren Sie zwei Funktionen
void changeValueByParameter(int value)
{
    value = 80;
    fmt::print("value by (paramter): {}\n", value);
    return;
}
void changeValueByPointer(int* ptr)
{
    *ptr = 90;
    fmt::print("value (by pointer): {}\n", *ptr);
    return;
}

int main() 
{
// Teil 1: Zeiger-Grundlagen
// Legen Sie eine int-Variable x mit dem Wert 10 an.
    int x = 10;
// Deklarieren Sie einen Zeiger p, der auf x zeigt.
    int * p = &x;
// Geben Sie mit fmt::print den Wert von x und die Adresse von x aus.
    fmt::print("Wert von x: {}\n", x);
    fmt::print("Adresse von x: {}\n\n", fmt::ptr(&x)); 
// Geben Sie den Wert aus, auf den der Zeiger p zeigt, sowie die Adresse, die in p gespeichert ist.
    fmt::print("Wert auf den p zeigt: {}\n", *p);
    fmt::print("Adresse von die in p gespeichert ist: {}\n\n", fmt::ptr(p));
// Ändern Sie den Wert von x über den Zeiger p auf 42.
    *p = 42;
// Geben Sie erneut den Wert von x und den Wert aus, auf den p zeigt.
    fmt::print("Wert von x: {}\n", x);
    fmt::print("Wert auf den p zeigt: {}\n\n", *p);
    
// Teil 2: Dynamische Speicherverwaltung
// Deklarieren Sie einen Zeiger auf double.
// Reservieren Sie mit new Speicher für genau einen double-Wert und initialisieren Sie ihn mit 3.1415.
    double* d = new double(3.1415);
// Geben Sie Wert und Adresse mit fmt::print aus.
    fmt::print("Adresse von d: {}\n", fmt::ptr(d));
    fmt::print("Wert auf den d zeigt: {}\n\n", *d);
// Geben Sie den Speicher anschließend wieder mit delete frei.
    delete d;

// Teil 3: Funktionen mit Zeigern
    changeValueByParameter(x);
    fmt::print("Change x by Parameter: x = {}\n", x);
    changeValueByPointer(p);
    fmt::print("Change x by Pointer: x = {}\n\n", x);
    
// Aufgabe
// Deklarieren Sie eine int-Variable y = 5;.
    int y = 5;
// Rufen Sie changeValueByParameter(y); auf und geben Sie vor und nach dem Funktionsaufruf den Wert von y aus.
    fmt::print("Wert von y (vor Aufruf): {}\n", y);
    changeValueByParameter(y);
    fmt::print("Wert von y (nach Aufruf): {}\n", y);
//Rufen Sie changeValueByPointer(&y); auf und geben Sie vor und nach dem Funktionsaufruf den Wert von y aus.
    fmt::print("Wert von y (vor Aufruf): {}\n", y);
    changeValueByPointer(&y);
    fmt::print("Wert von y (nach Aufruf): {}\n", y);
    
    return 0; /* exit gracefully*/
}
