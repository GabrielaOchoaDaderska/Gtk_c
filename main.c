#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>

//deklaracja funkcji
static void open_file(GtkWidget *widget, gpointer data);

int main(int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *openButton;
    GtkWidget *vbox;
    GtkWidget *hbox;
    GtkWidget *label;
    GtkWidget *image;

    gtk_init(&argc, &argv);

    //Tworzenie okna
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Przeglądarka plików");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    //Tworzenie boxu
    vbox = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    //Tworzenie przycisku
    openButton = gtk_button_new_with_label("Otwórz plik");
    gtk_box_pack_start(GTK_BOX(vbox), openButton, FALSE, FALSE, 10);

    //Tworzenie etykiet
    label = gtk_label_new("Ścieżka do pliku:");
    gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 10);

    //Tworzenie obrazu
    image = gtk_image_new();
    gtk_box_pack_start(GTK_BOX(vbox), image, FALSE, FALSE, 10);

    //Tworzenie boxu
    hbox = gtk_hbox_new(FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 10);

    //Podłączanie sygnału do przycisku
    g_signal_connect(G_OBJECT(openButton), "clicked", G_CALLBACK(open_file), (gpointer)image);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}

//Funkcja otwierania pliku
static void open_file(GtkWidget *widget, gpointer data)
{
    GtkWidget *dialog;
    GtkWidget *image = (GtkWidget *)data;
    gint res;
    gchar *filename;
    GError *error = NULL;
    GdkPixbuf *pixbuf;

    dialog = gtk_file_chooser_dialog_new("Otwórz plik",
                                        GTK_WINDOW(gtk_widget_get_toplevel(widget)),
                                        GTK_FILE_CHOOSER_ACTION_OPEN,
                                        GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                                        GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
                                        NULL);
    res = gtk_dialog_run(GTK_DIALOG(dialog));

    if(res == GTK_RESPONSE_ACCEPT)
    {
        filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        gtk_widget_destroy(dialog);

        //Wczytywanie obrazu
        pixbuf = gdk_pixbuf_new_from_file(filename, &error);
        if(!pixbuf)
        {
            GtkWidget *dialog;
            dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(widget)),
                                            GTK_DIALOG_DESTROY_WITH_PARENT,
                                            GTK_MESSAGE_ERROR,
                                            GTK_BUTTONS_CLOSE,
                                            "Nie można otworzyć pliku: %s",
                                            error->message);
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
            g_error_free(error);
        }
        else
        {
            gtk_image_set_from_pixbuf(GTK_IMAGE(image), pixbuf);
            g_object_unref(pixbuf);
        }
    }
    else
        gtk_widget_destroy(dialog);
}