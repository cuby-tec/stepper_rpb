/*
 * cu_debug_lib.c
 *
 *  Created on: 18 марта 2017 г.
 *      Author: walery
 */



#include "cu_debug_lib.h"


void
callback(GtkWidget *w, gpointer p){
//	char* s = "String:";
//	GtkWidget child = gtk_bin_get_child (w);
//	g_print("type_callback\n");
/*
*   (gtk_test:16783): WARNING **: www GtkMenuBar
*   (gtk_test:16783): WARNING **: www GtkBox
*/
	g_print("cu_debug_lib:cu_print_widget_children: %s",G_OBJECT_TYPE_NAME(w));

}

static void
(*GtkCallbak)(GtkWidget *w,gpointer p);
/**
 * Удаление наследников из главного окна.
 */
void
cu_print_widget_children(GtkWidget *widget)
{

	gpointer * pointer = NULL;

	GtkCallbak = callback;

	gtk_container_foreach((GtkContainer*)widget, GtkCallbak, pointer );


/*
	GList *list;

	list = gtk_container_get_children (GTK_CONTAINER (window));
	if(g_list_length(list)){
//		gtk_container_remove(GTK_CONTAINER (window),GTK_WIDGET(list->data));
//		gtk_widget_destroy(GTK_WIDGET(list->data));
		g_object_unref(list->data);
	}
*/

}
