#include <gtk/gtk.h>

int main( int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button;
    GtkWidget *file_chooser;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Przegladarka plikow");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    grid = gtk_grid_new();
    button = gtk_button_new_with_label("Otworz plik");
    file_chooser = gtk_file_chooser_widget_new(GTK_FILE_CHOOSER_ACTION_OPEN);

    gtk_container_add(GTK_CONTAINER(window), grid);
    gtk_grid_attach(GTK_GRID(grid), button, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), file_chooser, 0, 1, 1, 1);

    g_signal_connect(button, "clicked", G_CALLBACK(gtk_widget_show), file_chooser);
    g_signal_connect(file_chooser, "selection-changed", G_CALLBACK(gtk_file_chooser_get_filename), NULL);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}