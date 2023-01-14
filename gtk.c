#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

//Funkcja wyœwietlaj¹ca informacje o pliku lub folderze.
void show_details(GtkWidget *widget, gpointer window)
{
    gchar *file = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(window));
    GtkWidget *dialog;
    struct stat buf;

    stat(file, &buf);

    dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                        GTK_DIALOG_DESTROY_WITH_PARENT,
                        GTK_MESSAGE_INFO,
                        GTK_BUTTONS_OK,
                        "Nazwa pliku: %s\n", file);

    if(S_ISREG(buf.st_mode)) {
        gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG(dialog),
        "Typ pliku: Plik zwyk³y\nRozmiar: %ld bajtów\nUstawienia dostêpu: %3lo",
        buf.st_size, buf.st_mode & 0777);
    } else if(S_ISDIR(buf.st_mode)) {
        gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG(dialog),
        "Typ pliku: Katalog\nUstawienia dostêpu: %3lo",
        buf.st_mode & 0777);
    }

    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

int main(int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *chooser;
    GtkWidget *button;
    GtkWidget *vbox;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Przegl¹darka plików");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    chooser = gtk_file_chooser_widget_new(GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER);
    gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(chooser), g_get_home_dir());

    button = gtk_button_new_with_label("Poka¿ informacje");
    g_signal_connect(button, "clicked", G_CALLBACK(show_details), chooser);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_pack_start(GTK_BOX(vbox), chooser, TRUE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
