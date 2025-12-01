# point — einfache 2D-Point-Bibliothek

Kurz: Kleine C++-Bibliothek, die eine Point-Klasse (x,y) mit Basisoperationen bereitstellt.

## Voraussetzungen

- CMake >= 3.10.2
- fmt (wird per find_package in der CMakeLists erwartet)

Einbinden in ein größeres CMake-Projekt

1. Stelle sicher, dass das `point`-Subprojekt vor den Konsumenten-Subprojekten hinzugefügt wird:

```cmake
add_subdirectory(libs/point)
# danach z.B.
add_subdirectory(exercise-005)
```

2. In der CMakeLists des Konsumenten:

```cmake
add_executable(myapp src/main.cpp)
target_link_libraries(myapp PRIVATE point)
```

Das Library-Target heißt `point` und exportiert die Include-Pfade (Header liegen in `libs/point/include`, z.B. `point/point.hpp`).

## Beispiel: Benutzung in C++

```cpp
#include "point/point.hpp"
#include <iostream>

int main() {
    Point a(1.0, 2.0);
    Point b(4.0, 6.0);
    std::cout << "Distance: " << a.distance_to(b) << "\n";
    a.move(1.0, -1.0);
    a.print();
    return 0;
}
```

## Build (aus dem Workspace-Root)

```bash
cmake -S . -B build
cmake --build build
# optional: nur ein bestimmtes Target bauen
cmake --build build --target exercise-005
```

## Hinweise

- Header-Pfad: `#include "point/point.hpp"`.
- Die Bibliothek verwendet `fmt` für Log-Ausgaben; die Abhängigkeit wird in der CMakeLists von `point` erwartet.
- Falls die Bibliothek außerhalb des Build-Trees genutzt werden soll, ergänze `install()` und `export()` in der CMake-Konfiguration.

## Troubleshooting

- Bei "file not found" für `point.hpp` prüfen: wurde `add_subdirectory(libs/point)` im Top-Level-CMake vor dem Consumer aufgerufen und verbindet der Consumer das Target (`target_link_libraries(... PRIVATE point)`)?
