#include <gtk/gtk.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    GtkWidget *dialog;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
    gint res;

    gtk_init(&argc, &argv);

    dialog = gtk_file_chooser_dialog_new("Open File", NULL, action,
               "_Cancel", GTK_RESPONSE_CANCEL,
               "_Open", GTK_RESPONSE_ACCEPT,
               NULL);

    res = gtk_dialog_run(GTK_DIALOG(dialog));
    if (res == GTK_RESPONSE_ACCEPT) {
        char *filename;
        GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
        filename = gtk_file_chooser_get_filename(chooser);
        // tutaj możesz użyć pliku jako czegoś
        g_free(filename);
    }

    gtk_widget_destroy(dialog);
    return 0;
}
