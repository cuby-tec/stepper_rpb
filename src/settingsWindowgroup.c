/*
 * settingsWindowgroup.c
 *
 *  Created on: 12.03.2017
 *      Author: walery
 */

#include "settingsWindowgroup.h"


static GtkWindowGroup *settingGroup;

//static GtkWidget	*setting1;


void makeSettings(void){
//	g_print("win.settings");
	settingGroup = gtk_window_group_new();

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

//	GtkWidget *box;

	GtkWidget *child;
	child = gtk_bin_get_child (GTK_BIN( window));

//	box = gtk_box_new(GTK_ORIENTATION_VERTICAL,1);





//	cu_clearWindow(window);

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
//	gtk_grid_attach(GTK_GRID(window),grid1,0,1,2,1);


	gtk_box_pack_start(GTK_BOX( child ),grid1,FALSE,FALSE,1);


	/*
	 *  env MALLOC_CHECK_=2 ./Debug/gtk_test
	 *  Abort
	 */
//	g_free(builder);




}

/**
 * Заглавная страница
 */
#define _START_GRID
void
includeStartPage(GtkWidget *window)
{
	GtkWidget  *grid;
	GtkWidget *toolbar;
	GtkToolItem *button;
	GtkWidget *sw, *box, *label;

/*
	GList *list = gtk_container_get_children (GTK_CONTAINER (window));
	if(g_list_length(list)){
		gtk_container_remove(GTK_CONTAINER (window),GTK_WIDGET(list->data));
	}
*/
//	cu_clearWindow(window);

	  /* Compose start window. */
	#ifdef _START_GRID
	  grid = gtk_grid_new ();
	  gtk_container_add (GTK_CONTAINER (window), grid);

	  toolbar = gtk_toolbar_new ();
	  button = gtk_toggle_tool_button_new_from_stock (GTK_STOCK_JUSTIFY_LEFT);
	  gtk_actionable_set_detailed_action_name (GTK_ACTIONABLE (button), "win.justify::left");
	  gtk_container_add (GTK_CONTAINER (toolbar), GTK_WIDGET (button));

	  button = gtk_toggle_tool_button_new_from_stock (GTK_STOCK_JUSTIFY_CENTER);
	  gtk_actionable_set_detailed_action_name (GTK_ACTIONABLE (button), "win.justify::center");
	  gtk_container_add (GTK_CONTAINER (toolbar), GTK_WIDGET (button));

	  button = gtk_toggle_tool_button_new_from_stock (GTK_STOCK_JUSTIFY_RIGHT);
	  gtk_actionable_set_detailed_action_name (GTK_ACTIONABLE (button), "win.justify::right");
	  gtk_container_add (GTK_CONTAINER (toolbar), GTK_WIDGET (button));

	  button = gtk_separator_tool_item_new ();
	  gtk_separator_tool_item_set_draw (GTK_SEPARATOR_TOOL_ITEM (button), FALSE);
	  gtk_tool_item_set_expand (GTK_TOOL_ITEM (button), TRUE);
	  gtk_container_add (GTK_CONTAINER (toolbar), GTK_WIDGET (button));

	  button = gtk_tool_item_new ();
	  box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 6);
	  gtk_container_add (GTK_CONTAINER (button), box);
	  label = gtk_label_new ("Fullscreen:");
	  gtk_container_add (GTK_CONTAINER (box), label);
	  sw = gtk_switch_new ();
	  gtk_actionable_set_action_name (GTK_ACTIONABLE (sw), "win.fullscreen");
	  gtk_container_add (GTK_CONTAINER (box), sw);
	  gtk_container_add (GTK_CONTAINER (toolbar), GTK_WIDGET (button));

	  gtk_grid_attach (GTK_GRID (grid), toolbar, 0, 0, 1, 1);
	/* //
	  scrolled = gtk_scrolled_window_new (NULL, NULL);
	  gtk_widget_set_hexpand (scrolled, TRUE);
	  gtk_widget_set_vexpand (scrolled, TRUE);
	  view = gtk_text_view_new ();

	  g_object_set_data ((GObject*)window, "bloatpad-text", view);

	  gtk_container_add (GTK_CONTAINER (scrolled), view);

	  gtk_grid_attach (GTK_GRID (grid), scrolled, 0, 1, 1, 1);

	  if (file != NULL)
	    {
	      gchar *contents;
	      gsize length;

	      if (g_file_load_contents (file, NULL, &contents, &length, NULL, NULL))
	        {
	          GtkTextBuffer *buffer;

	          buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (view));
	          gtk_text_buffer_set_text (buffer, contents, length);
	          g_free (contents);
	        }
	    }
	*/
	#endif

}

