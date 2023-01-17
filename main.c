/* Główna funkcja programu.
   Inicjuje GTK+, tworzy główne okno, wstawia widget FileChooser i ustawia
   odpowiednie słuchacze zdarzeń. */
int main (int argc, char **argv)
{
    GtkWidget *window;  // Wskaźnik na główne okno
    GtkWidget *file_chooser;  // Wskaźnik na widget FileChooser
    GtkFileFilter *filter;  // Wskaźnik na filtr plików

    // Inicjalizacja GTK+
    gtk_init(&argc, &argv);

    // Tworzenie głównego okna
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Przeglądarka plików");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    // Tworzenie widgetu FileChooser
    file_chooser = gtk_file_chooser_widget_new(GTK_FILE_CHOOSER_ACTION_OPEN);
    gtk_file_chooser_set_show_hidden(GTK_FILE_CHOOSER(file_chooser), TRUE);
    gtk_file_chooser_set_local_only(GTK_FILE_CHOOSER(file_chooser), FALSE);
    gtk_file_chooser_set_select_multiple(GTK_FILE_CHOOSER(file_chooser), FALSE);

    // Tworzenie filtra dla plików
    filter = gtk_file_filter_new();
    gtk_file_filter_set_name(filter, "Wszystkie pliki");
    gtk_file_filter_add_pattern(filter, "*.*");
    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(file_chooser), filter);

    // Dodawanie widgetu do głównego okna
    gtk_container_add(GTK_CONTAINER(window), file_chooser);

    // Ustawienie słuchacza zdarzeń
    g_signal_connect(G_OBJECT(window), "destroy",
        G_CALLBACK(gtk_main_quit), NULL);

    // Wyświetlenie wszystkich widgetów
    gtk_widget_show_all(window);

    // Pętla główna
    gtk_main();

    return 0;
}
