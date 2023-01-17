# Gtk_c

*Program "Przeglądarka plików" pozwala na wybór interesującego nas folderu, a następnie wyświetlanie wszystkich plików i katalogów w nim zawartych, wraz ze szczegółowymi informacjami o nich.*

**(Poniższy poradnik jest przeznaczony na systemy Windows)

## Instalacja [GTK+](https://www.gtk.org/)
- Program do odpalania programu 
![obraz](https://user-images.githubusercontent.com/108947060/212928544-43abd596-a9ca-4035-9800-0746200db9dc.png)
- Ustawianie [programu i pobranie](https://www.gtk.org/docs/installations/windows/)
```
gcc $(pkg-config --cflags gtk+-3.0) -o nazwadowolna gtk.c $(pkg-config --libs gtk+-3.0)
```
---
!!! komendą cd wybrać lokaliację programu w c/c++!!!

## KOD [gtk.c](https://github.com/GabrielaOchoaDaderska/Gtk_c/blob/main/gtk.c)
