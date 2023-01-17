# Gtk_c

*Program "Przeglądarka plików" pozwala na wybór interesującego nas folderu, a następnie wyświetlanie wszystkich plików i katalogów w nim zawartych, wraz ze szczegółowymi informacjami o nich.*

**(Poniższy poradnik jest przeznaczony na systemy Windows)**

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

## Opis kodu
> Inicjalizacja GTK+
```c
gtk_init(&argc, &argv);
```
> Utworzenie okna
```c
window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
```
> Ustawienie tytułu okna
```c
gtk_window_set_title(GTK_WINDOW(window), "Przegladarka plikow");
```
> Ustawienie domyślnych rozmiarów okna
```c
gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
```
> Ustawienie obramowania okna
```c
gtk_container_set_border_width(GTK_CONTAINER(window), 10);
```
> Utworzenie wyboru plików/folderów
```c
chooser = gtk_file_chooser_widget_new(GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER);
```
> Ustawienie domyślnego folderu
```c
gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(chooser), g_get_home_dir());
```
> Utworzenie kontenera typu Box
```c
vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
```
> Dodanie wyboru plików/folderów do kontenera
```c
gtk_box_pack_start(GTK_BOX(vbox), chooser, TRUE, TRUE, 5);
gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 5);
```
> Dodanie kontenera do okna
```c
gtk_container_add(GTK_CONTAINER(window), vbox);
```
> Związanie sygnału zamknięcia okna z funkcją gtk_main_quit
```c
g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
```
> Pokazanie wszystkich elementów
```c
gtk_widget_show_all(window);
```
> Pętla główna GTK+
```c
gtk_main();
```
## [gtk.exe](https://github.com/GabrielaOchoaDaderska/Gtk_c/blob/main/gtk.exe)

![obraz](https://user-images.githubusercontent.com/108947060/212930944-f5cba3bc-be7a-471d-bdd7-fec82d279f4f.png)

---
## License

MIT
