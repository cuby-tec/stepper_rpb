/*
 * settingsWindowgroup.c
 *
 *  Created on: 12.03.2017
 *      Author: walery
 */

#include "settingsWindowgroup.h"


static GtkWindowGroup *settingGroup;

static GtkWidget	*setting1;


void makeSettings(void){
	g_print("win.settings");
	settingGroup = gtk_window_group_new();

//	setting1 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
/*
	setting1 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_group_add_window(settingGroup, (GtkWindow*)setting1);
	gtk_window_set_title((GtkWindow*)setting1,"Settings");
	gtk_window_set_destroy_with_parent((GtkWindow*)setting1,TRUE);
	gtk_window_set_gravity (setting1,GDK_GRAVITY_NORTH_WEST);


	gtk_window_set_modal(setting1,TRUE);
*/

//	setting1 = gtk_dialog_new();

//	setting1 = gtk_notebook_new();
//	 gtk_widget_show_all(setting1);

//http://stackoverflow.com/questions/37405202/gtknotebook-does-not-show-tab-label-content
    GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkWidget* notebook = gtk_notebook_new();
    GtkWidget* page_content = gtk_label_new("Content");
    GtkWidget* tab_label = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    GtkWidget* label_content_1 = gtk_label_new("Title");
    GtkWidget* label_content_2 = gtk_button_new_with_label("Close");

    gtk_widget_show(GTK_WIDGET(label_content_1));
    gtk_widget_show(GTK_WIDGET(label_content_2));
    gtk_widget_show(GTK_WIDGET(tab_label));
    gtk_box_pack_start(GTK_BOX(tab_label), label_content_1, TRUE, TRUE, 0);
    gtk_box_pack_end(GTK_BOX(tab_label), label_content_2, FALSE, FALSE, 0);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page_content, tab_label);
    gtk_notebook_set_show_tabs(GTK_NOTEBOOK(notebook), TRUE);
    gtk_container_add(GTK_CONTAINER(window), notebook);

    gtk_widget_show_all(GTK_WIDGET(window));

	//g_free (settingGroup);
}


/**
 * Заполнить окно "Редактором установок".
 */
void
includeSettings( GtkWidget *window)
{
	GtkBuilder *builder;
	GError *err = NULL;
	GtkWidget *grid1;

	builder = gtk_builder_new ();

	gtk_builder_add_from_file(builder,"settings_stack.ui",&err);
	if (err)
	{
		g_error ("ERROR: %s\n", err->message);
		return ;
	}

	gtk_builder_connect_signals (builder, NULL);

	grid1 = GTK_WIDGET (gtk_builder_get_object (builder, "grid1"));

//	gtk_container_add (GTK_CONTAINER (window), grid1);
	gtk_grid_attach(GTK_GRID(window),grid1,0,1,2,1);

//	g_free(builder);

}


