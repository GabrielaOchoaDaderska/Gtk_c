
#include<gtk/gtk.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<dirent.h>
//
GtkWidget* window;
GtkWidget* list;
GtkWidget* directory;
GtkWidget* files;
GtkWidget* scrolled_window;
GtkWidget* scrolled_window2;
GtkWidget* scrolled_window3;

void openfile(GtkWidget* widget, gpointer* data)
{
	gchar* string;
	GtkTreeIter iter;
	GtkTreeModel* model;
	if(gtk_tree_selection_get_selected(GTK_TREE_SELECTION(data), &model, &iter) == TRUE)
	{
		gtk_tree_model_get(model, &iter, 0, &string, -1);
		if(strcmp(string, "..")!=0){
			gtk_list_store_clear(GTK_LIST_STORE(files));
			DIR* dir;
			struct dirent* ent;
			if((dir=opendir(string))!=NULL){
				while((ent=readdir(dir))!=NULL){
					GtkTreeIter iter;
					gtk_list_store_append(GTK_LIST_STORE(files), &iter);
					gtk_list_store_set(GTK_LIST_STORE(files), &iter, 0, ent->d_name, -1);
				}
				closedir(dir);
			}
			else{
				g_print("Nie można otworzyć folderu %s\n", string);
			}
			gtk_entry_set_text(GTK_ENTRY(directory), string);
		}
		else{
			gchar* old_dir;
			old_dir=strdup(string);
			gtk_list_store_clear(GTK_LIST_STORE(files));
			DIR* dir;
			struct dirent* ent;
			if((dir=opendir(old_dir))!=NULL){
				while((ent=readdir(dir))!=NULL){
					GtkTreeIter iter;
					gtk_list_store_append(GTK_LIST_STORE(files), &iter);
					gtk_list_store_set(GTK_LIST_STORE(files), &iter, 0, ent->d_name, -1);
				}
				closedir(dir);
			}
			else{
				g_print("Nie można otworzyć folderu %s\n", old_dir);
			}
			gtk_entry_set_text(GTK_ENTRY(directory), old_dir);
			free(old_dir);
		}
		g_free(string);
	}
}

int main (int argc, char* argv[])
{
	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Przeglądarka Plików");
	gtk_window_set_default_size(GTK_WINDOW(window), 700, 500);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

	GtkWidget* vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	gtk_container_add(GTK_CONTAINER(window), vbox);

	GtkWidget* hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
	gtk_container_add(GTK_CONTAINER(vbox), hbox);

	scrolled_window = gtk_scrolled_window_new(NULL, NULL);
	gtk_container_set_border_width(GTK_CONTAINER(scrolled_window), 10);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_widget_set_size_request(scrolled_window, 200, 400);
	gtk_box_pack_start(GTK_BOX(hbox), scrolled_window, FALSE, FALSE, 0);

	list = gtk_list_store_new(1, G_TYPE_STRING);
	GtkTreeIter iter;

	gtk_list_store_append(GTK_LIST_STORE(list), &iter);
	gtk_list_store_set(GTK_LIST_STORE(list), &iter, 0, "/", -1);

	GtkTreeModel* model = GTK_TREE_MODEL(list);
	GtkWidget* tree_view = gtk_tree_view_new_with_model(model);
	gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(tree_view), FALSE);

	GtkCellRenderer* renderer = gtk_cell_renderer_text_new();
	GtkTreeViewColumn* column = gtk_tree_view_column_new_with_attributes("Folder", renderer, "text", 0, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);

	GtkTreeSelection* selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(tree_view));
	gtk_container_add(GTK_CONTAINER(scrolled_window), tree_view);

	scrolled_window2 = gtk_scrolled_window_new(NULL, NULL);
	gtk_container_set_border_width(GTK_CONTAINER(scrolled_window2), 10);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window2), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_widget_set_size_request(scrolled_window2, 200, 400);
	gtk_box_pack_start(GTK_BOX(hbox), scrolled_window2, FALSE, FALSE, 0);

	files = gtk_list_store_new(1, G_TYPE_STRING);

	GtkTreeModel* model2 = GTK_TREE_MODEL(files);
	GtkWidget* tree_view2 = gtk_tree_view_new_with_model(model2);
	gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(tree_view2), FALSE);

	GtkCellRenderer* renderer2 = gtk_cell_renderer_text_new();
	GtkTreeViewColumn* column2 = gtk_tree_view_column_new_with_attributes("Plik", renderer2, "text", 0, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view2), column2);

	GtkTreeSelection* selection2 = gtk_tree_view_get_selection(GTK_TREE_VIEW(tree_view2));
	gtk_container_add(GTK_CONTAINER(scrolled_window2), tree_view2);

	scrolled_window3 = gtk_scrolled_window_new(NULL, NULL);
	gtk_container_set_border_width(GTK_CONTAINER(scrolled_window3), 10);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window3), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_widget_set_size_request(scrolled_window3, 200, 400);
	gtk_box_pack_start(GTK_BOX(hbox), scrolled_window3, TRUE, TRUE, 0);

	directory = gtk_entry_new();
	gtk_container_add(GTK_CONTAINER(scrolled_window3), directory);

	gtk_widget_show_all(window);

	g_signal_connect(selection, "changed", G_CALLBACK(openfile), selection);

	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

	gtk_main();

	return 0;
}
