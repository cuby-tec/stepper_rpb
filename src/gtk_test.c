/*
 ============================================================================
 Name        : gtk_test.c
 Author      : CUBY
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 https://www.gtk.org/tutorial1.2/gtk_tut-10.html#ss10.11
 */


// from https://de.wikibooks.org/wiki/GTK_mit_Builder:_Hauptfensterwidgets
#define example_builder

#ifdef example_builder
#include <gtk/gtk.h>

static void
print_hello (GtkWidget *widget,
             gpointer   data)
{
  g_print ("Hello World\n");
}

int
main (int   argc,
      char *argv[])
{
  GtkBuilder *builder;
  GObject *window;
  GObject *button;
  GError *builder_error = NULL;
//  GError *error_b = NULL;
  guint builder_code;

  gtk_init (&argc, &argv);

  /* Construct a GtkBuilder instance and load our UI description */
  builder = gtk_builder_new ();
  builder_code =  gtk_builder_add_from_file (builder, "builder.ui", &builder_error);
  if(!builder_code){
	  g_print("error:builder fault. %s",builder_error->message);
	  return 0;
  }

  /* Connect signal handlers to the constructed widgets. */
  window = gtk_builder_get_object (builder, "window");
  if(!window){
	  g_print("error: no window");
	  return 1;
  }
  g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

  button = gtk_builder_get_object (builder, "button1");
  g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);

  button = gtk_builder_get_object (builder, "button2");
  g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);

  button = gtk_builder_get_object (builder, "quit");
  g_signal_connect (button, "clicked", G_CALLBACK (gtk_main_quit), NULL);

  gtk_main ();

  return 0;
}

#endif



#ifdef example_2
//(gtk_test:9354): Gtk-CRITICAL **: gtk_widget_show_all: assertion 'GTK_IS_WIDGET (widget)' failed
#include <gtk/gtk.h>
#include <glib/gprintf.h>
#include <string.h>


void kleine_callback (GtkWidget *w, gpointer d)
{
    GtkWidget *dialog;
    dialog = gtk_message_dialog_new (NULL,
        GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO,
        GTK_BUTTONS_CLOSE, "Hallo, Welt!");
    gtk_dialog_run (GTK_DIALOG (dialog));
    gtk_widget_destroy (dialog);
}

static const gchar * interface =
"<interface>"
"    <object class=\"GtkUIManager\" id=\"uimanager\">"
"    <child>"
"        <object class=\"GtkActionGroup\" id=\"aktionen\">"
"        <child>"
"            <object class=\"GtkAction\" id=\"datei\">"
"            <property name=\"label\">_Datei</property>"
"            </object>"
"        </child>"
"        <child>"
"            <object class=\"GtkAction\" id=\"neu\">"
"            <property name=\"label\">_Neue Datei</property>"
"            <signal name=\"activate\" handler=\"kleine_callback\"/>"
"            </object>"
"        </child>"
"        <child>"
"            <object class=\"GtkAction\" id=\"exit\">"
"            <property name=\"label\">_Beenden</property>"
"            <property name=\"stock-id\">gtk-quit</property>"
"            <signal name=\"activate\" handler=\"gtk_main_quit\"/>"
"            </object>"
"        </child>"
"        <child>"
"            <object class=\"GtkAction\" id=\"bearbeiten\">"
"            <property name=\"label\">_Bearbeiten</property>"
"            </object>"
"        </child>"
"        </object>"
"    </child>"
"    <ui>"
"    <menubar name=\"menubar\">"
"        <menu action=\"datei\" >"
"            <menuitem action=\"neu\" />"
"            <separator />"
"            <menuitem action=\"exit\" />"
"        </menu>"
"        <menu action=\"bearbeiten\" />"
"    </menubar>"
"    </ui>"
"    </object>"
"   "
"    <object class=\"GtkWindow\" id=\"hauptfenster\" >"
"    <signal name=\"destroy\" handler=\"gtk_main_quit\"/>"
"    <child>"
"        <object class=\"GtkVBox\" id=\"vbox-layout\">"
"        <property name=\"homogeneous\">FALSE</property>"
"        <child>"
"       <object class=\"GtkMenuBar\" id=\"menubar\" constructor=\"uimanager\"/>"
"        </child>"
"        </object>"
"    </child>"
"    </object>"
"</interface>";


int main (int argc, char *argv[])
{
    GtkBuilder *builder;
    GError *errors = NULL;
    GtkWidget *window;

    gtk_init (&argc, &argv);
    builder = gtk_builder_new ();
    gtk_builder_add_from_string (builder, interface,
	strlen(interface), &errors);
    gtk_builder_connect_signals (builder, NULL);
    window = GTK_WIDGET(gtk_builder_get_object (builder, "main window"));
    gtk_widget_show_all (window);
    gtk_main ();
    return 0;
}

#endif

///////////////////////
#ifdef example_1
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>

#include "gtk.xpm"

// Adding for test git  /
#include <glib.h>


//static _menumodel(){
//	GMenuModel menuModel;
//
//}


/* This function is connected to the Close button or
 * closing the window from the WM */
gint delete_event (GtkWidget *widget, GdkEvent *event, gpointer data)
{
  gtk_main_quit ();
  return(FALSE);
}

GtkWidget* close_button; /* This button will emit signal to close
                          * application */
GtkWidget* tooltips_button; /* to enable/disable tooltips */
GtkWidget* text_button,
         * icon_button,
         * both_button; /* radio buttons for toolbar style */
GtkWidget* entry; /* a text entry to show packing any widget into toolbar */

/* that's easy... when one of the buttons is toggled, we just
 * check which one is active and set the style of the toolbar
 * accordingly
 * ATTENTION: our toolbar is passed as data to callback ! */
void radio_event (GtkWidget *widget, gpointer data)
{
  /*if (GTK_TOGGLE_BUTTON (text_button)->active)
    gtk_toolbar_set_style(GTK_TOOLBAR ( data ), GTK_TOOLBAR_TEXT);
  else if (GTK_TOGGLE_BUTTON (icon_button)->active)
    gtk_toolbar_set_style(GTK_TOOLBAR ( data ), GTK_TOOLBAR_ICONS);
  else if (GTK_TOGGLE_BUTTON (both_button)->active)
    gtk_toolbar_set_style(GTK_TOOLBAR ( data ), GTK_TOOLBAR_BOTH);
*/

	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(text_button)))
		gtk_toolbar_set_style(GTK_TOOLBAR(data),GTK_TOOLBAR_TEXT);
	else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(icon_button))) {
		gtk_toolbar_set_style(GTK_TOOLBAR(data),GTK_TOOLBAR_ICONS);
	}
	else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(both_button))) {
		gtk_toolbar_set_style(GTK_TOOLBAR(data),GTK_TOOLBAR_BOTH);
	}

}

/* even easier, just check given toggle button and enable/disable
 * tooltips */
void toggle_event (GtkWidget *widget, gpointer data)
{
//  gtk_toolbar_set_tooltips (GTK_TOOLBAR ( data ),
//                            GTK_TOGGLE_BUTTON (widget)->active );
/*
 * 	gtk_toolbar_set_tooltips (GTK_TOOLBAR ( data ),gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget)));
 *
 */
	gtk_toolbar_set_style(GTK_TOOLBAR(data),GTK_TOOLBAR_BOTH);
}


int main (int argc, char *argv[]){
	int status = 0;
	/* Here is our main window (a dialog) and a handle for the handlebox */
	  GtkWidget* dialog;
	  GtkWidget* handlebox;

	  cairo_surface_t *surface;

	  /* Ok, we need a toolbar, an icon with a mask (one for all of
	      the buttons) and an icon widget to put this icon in (but
	      we'll create a separate widget for each button) */
	   GtkWidget * toolbar;
/*
  *	comment	   -GdkPixmap * icon;
 *	comment	   -GdkBitmap * mask;
*/
	   GtkWidget * iconw;
	   GdkPixbuf *pixbuf;


	   /* this is called in all GTK application. */
	   gtk_init (&argc, &argv);

	   /* create a new window with a given title, and nice size */
	   dialog = gtk_dialog_new ();
	   gtk_window_set_title ( GTK_WINDOW ( dialog ) , "GTKToolbar Tutorial");
	   gtk_widget_set_usize( GTK_WIDGET ( dialog ) , 600 , 300 );
//	   GTK_WINDOW ( dialog )->allow_shrink = TRUE;


/* *
 *  sdfgds  gdk_cairo_set_source_pixbuf();
 *
 */
	   return status;
}
#endif
////////////////////////////


#ifdef EXAMPLE_O

static void
activate (GtkApplication* app,
          gpointer        user_data)
{
  GtkWidget *window;

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Window");
  gtk_window_set_default_size (GTK_WINDOW (window), 600, 500);
  gtk_widget_show_all (window);
}

int main (int    argc,
      char **argv)
{
  GtkApplication *app;
  int status;
  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}

#endif


