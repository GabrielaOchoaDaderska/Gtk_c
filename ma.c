#include <gtk/gtk.h>

int main(int argc, char **argv)
{
    GtkWidget *window;
    GtkWidget *file_chooser;
    GtkFileFilter *filter;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Przeglądarka plików");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    file_chooser = gtk_file_chooser_widget_new(GTK_FILE_CHOOSER_ACTION_OPEN);
    gtk_file_chooser_set_select_multiple(GTK_FILE_CHOOSER(file_chooser), TRUE);
    gtk_file_chooser_set_show_hidden(GTK_FILE_CHOOSER(file_chooser), TRUE);
    gtk_file_chooser_set_show_size_column(GTK_FILE_CHOOSER(file_chooser), TRUE);
    gtk_file_chooser_set_search_mode(GTK_FILE_CHOOSER(file_chooser), TRUE);
    gtk_container_add(GTK_CONTAINER(window), file_chooser);

    filter = gtk_file_filter_new();
    gtk_file_filter_set_name(filter, "Wszystkie pliki");
    gtk_file_filter_add_pattern(filter, "*");
    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(file_chooser), filter);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}