/*
 * cu_debug_lib.h
 *
 *  Created on: 18 марта 2017 г.
 *      Author: walery
 */

#ifndef CU_DEBUG_LIB_H_
#define CU_DEBUG_LIB_H_
/*
 * GtkWidget child = gtk_bin_get_child (w);
 */
#include <stdlib.h>
#include <gtk/gtk.h>

void
cu_print_widget_children(GtkWidget *widget);

#endif /* CU_DEBUG_LIB_H_ */
