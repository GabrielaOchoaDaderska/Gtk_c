
#include <gtk/gtk.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

GtkWidget *file_list;

//Funkcja do wyświetlania informacji o plikach
void show_files_info(const char *dirname) {
	DIR *dir;
	struct dirent *entry;
	if ((dir = opendir(dirname)) == NULL) {
		perror("opendir() error");
		return;
	}
	while ((entry = readdir(dir)) != NULL) {
		printf("Name: %s\n", entry->d_name);
		printf("Inode: %ld\n", entry->d_ino);
		printf("Reclen: %d\n", entry->d_reclen);
		printf("Type: %d\n", entry->d_type);
		printf("\n");
	}
	closedir(dir);
}

//Funkcja do wyświetlania zawartości katalogu
void show_files(const char *dirname) {
	DIR *dir;
	struct dirent *entry;
	if ((dir = opendir(dirname)) == NULL) {
		perror("opendir() error");
		return;
	}
	while ((entry = readdir(dir)) != NULL) {
		GtkTreeIter iter;
		gtk_list_store_append(GTK_LIST_STORE(file_list), &iter);
		gtk_list_store_set(
			GTK_LIST_STORE(file_list), &iter,
			0, entry->d_name,
			-1
		);
	}
	closedir(dir);
}

//Funkcja do wyboru folderu
static void select_folder_cb(GtkWidget *widget, gpointer data) {
	GtkWidget *dialog;
	dialog = gtk_file_chooser_dialog_new("Select folder", NULL, 
		GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER,
		"_Cancel", GTK_RESPONSE_CANCEL,
		"_Open", GTK_RESPONSE_ACCEPT,
		NULL);
	if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
		char *filename;
		filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
		gtk_list_store_clear(GTK_LIST_STORE(file_list));
		show_files(filename);
		show_files_info(filename);
		g_free(filename);
	}
	gtk_widget_destroy(dialog);
}

static void activate(GtkApplication *app, gpointer user_data) {
	GtkWidget *window;
	GtkWidget *grid;
	GtkWidget *scrolled_window;
	GtkWidget *select_folder;
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;

	//Tworzenie okna i siatki
	window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(window), "Przeglądarka plików");
	gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);

	grid = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(window), grid);

	//Tworzenie paska bocznego
	GtkWidget *side_bar;
	side_bar = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_grid_attach(GTK_GRID(grid), side_bar, 0, 1, 1, 3);

	GtkWidget *home_button;
	home_button = gtk_button_new_with_label("Home");
	gtk_box_pack_start(GTK_BOX(side_bar), home_button, FALSE, FALSE, 0);

	GtkWidget *documents_button;
	documents_button = gtk_button_new_with_label("Documents");
	gtk_box_pack_start(GTK_BOX(side_bar), documents_button, FALSE, FALSE, 0);

	GtkWidget *downloads_button;
	downloads_button = gtk_button_new_with_label("Downloads");
	gtk_box_pack_start(GTK_BOX(side_bar), downloads_button, FALSE, FALSE, 0);

	//Tworzenie listy plików
	scrolled_window = gtk_scrolled_window_new(NULL, NULL);
	gtk_grid_attach(GTK_GRID(grid), scrolled_window, 1, 1, 1, 3);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

	file_list = gtk_list_store_new(1, G_TYPE_STRING);
	GtkWidget *file_view = gtk_tree_view_new_with_model(GTK_TREE_MODEL(file_list));
	gtk_container_add(GTK_CONTAINER(scrolled_window), file_view);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Nazwa pliku", renderer, "text", 0, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(file_view), column);

	select_folder = gtk_button_new_with_label("Wybierz folder");
	gtk_grid_attach(GTK_GRID(grid), select_folder, 0, 0, 1, 1);
	g_signal_connect(G_OBJECT(select_folder), "clicked", G_CALLBACK(select_folder_cb), NULL);
	gtk_widget_show_all(window);
}

int main(int argc, char **argv) {
	GtkApplication *app;
	int status;

	app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
	g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
	status = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);

	return status;
}
