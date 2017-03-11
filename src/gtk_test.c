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
#define GTkapplication

#ifdef GTkapplication
#include <stdlib.h>
#include <gtk/gtk.h>
#include <stdio.h>

static void
activate_toggle (GSimpleAction *action,
                 GVariant      *parameter,
                 gpointer       user_data)
{
  GVariant *state;

  state = g_action_get_state (G_ACTION (action));
  g_action_change_state (G_ACTION (action), g_variant_new_boolean (!g_variant_get_boolean (state)));
  g_variant_unref (state);
}

static void
activate_radio (GSimpleAction *action,
                GVariant      *parameter,
                gpointer       user_data)
{
  g_action_change_state (G_ACTION (action), parameter);
}

static void
change_fullscreen_state (GSimpleAction *action,
                         GVariant      *state,
                         gpointer       user_data)
{
  if (g_variant_get_boolean (state))
    gtk_window_fullscreen (user_data);
  else
    gtk_window_unfullscreen (user_data);

  g_simple_action_set_state (action, state);
}

static void
change_justify_state (GSimpleAction *action,
                      GVariant      *state,
                      gpointer       user_data)
{
  GtkTextView *text = g_object_get_data (user_data, "bloatpad-text");
  const gchar *str;

  str = g_variant_get_string (state, NULL);

  if (g_str_equal (str, "left"))
    gtk_text_view_set_justification (text, GTK_JUSTIFY_LEFT);
  else if (g_str_equal (str, "center"))
    gtk_text_view_set_justification (text, GTK_JUSTIFY_CENTER);
  else if (g_str_equal (str, "right"))
    gtk_text_view_set_justification (text, GTK_JUSTIFY_RIGHT);
  else
    /* ignore this attempted change */
    return;

  g_simple_action_set_state (action, state);
}

static GtkClipboard *
get_clipboard (GtkWidget *widget)
{
  return gtk_widget_get_clipboard (widget, gdk_atom_intern_static_string ("CLIPBOARD"));
}

static void
window_copy (GSimpleAction *action,
             GVariant      *parameter,
             gpointer       user_data)
{
  GtkWindow *window = GTK_WINDOW (user_data);
  GtkTextView *text = g_object_get_data ((GObject*)window, "bloatpad-text");

  gtk_text_buffer_copy_clipboard (gtk_text_view_get_buffer (text),
                                  get_clipboard ((GtkWidget*) text));
}

static void
window_paste (GSimpleAction *action,
              GVariant      *parameter,
              gpointer       user_data)
{
  GtkWindow *window = GTK_WINDOW (user_data);
  GtkTextView *text = g_object_get_data ((GObject*)window, "bloatpad-text");

  gtk_text_buffer_paste_clipboard (gtk_text_view_get_buffer (text),
                                   get_clipboard ((GtkWidget*) text),
                                   NULL,
                                   TRUE);

}


/*
 * Отрыть файл управления.
 */
static void window_open(GSimpleAction *action,
		 GVariant      *parameter,
		 gpointer       user_data)
{
//	g_print("win.OPEN.");
	char *filename;
	FILE *pfile;
	GtkWidget *dialog;
//parent_window
	dialog = gtk_file_chooser_dialog_new ("Open File",
	                                      NULL ,
	                                      GTK_FILE_CHOOSER_ACTION_OPEN,
	                                      GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
	                                      GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
	                                      NULL);

	if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT)
	  {

	    filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
//	    open_file (filename);
	    pfile = fopen(filename,"r");
	    if(pfile!=NULL){
	    	g_print("File opened:%s \n",filename);
	    	fclose(pfile);
	    }

	    g_print("File closed:%s \n",filename);
	    g_free (filename);
	  }

	gtk_widget_destroy (dialog);
}

/**
 * Запустить файл на выполнение.
 */
static void window_run(GSimpleAction *action,
		 GVariant      *parameter,
		 gpointer       user_data)
{
	g_print("win.RUN");
}


static GActionEntry win_entries[] = {
  { "copy", window_copy, NULL, NULL, NULL },
  { "paste", window_paste, NULL, NULL, NULL },
  { "fullscreen", activate_toggle, NULL, "false", change_fullscreen_state },
  { "justify", activate_radio, "s", "'left'", change_justify_state },
  { "open", window_open, NULL, NULL, NULL },
  { "run", window_run, NULL, NULL, NULL }
};

static void
new_window (GApplication *app,
            GFile        *file)
{
  GtkWidget *window, *grid, *scrolled, *view;
  GtkWidget *toolbar;
  GtkToolItem *button;
  GtkWidget *sw, *box, *label;

  window = gtk_application_window_new (GTK_APPLICATION (app));
  gtk_window_set_default_size ((GtkWindow*)window, 640, 480);
  g_action_map_add_action_entries (G_ACTION_MAP (window), win_entries, G_N_ELEMENTS (win_entries), window);
  gtk_window_set_title (GTK_WINDOW (window), "Bloatpad");

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

  gtk_widget_show_all (GTK_WIDGET (window));
}

static void
bloat_pad_activate (GApplication *application)
{
  new_window (application, NULL);
}

static void
bloat_pad_open (GApplication  *application,
                GFile        **files,
                gint           n_files,
                const gchar   *hint)
{
  gint i;

  for (i = 0; i < n_files; i++)
    new_window (application, files[i]);
}

typedef GtkApplication BloatPad;
typedef GtkApplicationClass BloatPadClass;

G_DEFINE_TYPE (BloatPad, bloat_pad, GTK_TYPE_APPLICATION)

static void
bloat_pad_finalize (GObject *object)
{
  G_OBJECT_CLASS (bloat_pad_parent_class)->finalize (object);
}

static void
new_activated (GSimpleAction *action,
               GVariant      *parameter,
               gpointer       user_data)
{
  GApplication *app = user_data;

  g_application_activate (app);
}

static void
about_activated (GSimpleAction *action,
                 GVariant      *parameter,
                 gpointer       user_data)
{
  gtk_show_about_dialog (NULL,
                         "program-name", "Bloatpad",
                         "title", "About Bloatpad",
                         "comments", "Not much to say, really.",
                         NULL);
}

static void
quit_activated (GSimpleAction *action,
                GVariant      *parameter,
                gpointer       user_data)
{
  GApplication *app = user_data;

  g_application_quit (app);
}

static GActionEntry app_entries[] = {
  { "new", new_activated, NULL, NULL, NULL },
  { "about", about_activated, NULL, NULL, NULL },
  { "quit", quit_activated, NULL, NULL, NULL },
};

static void
bloat_pad_startup (GApplication *application)
{
  GtkBuilder *builder;
  GError *builder_error = NULL;
  guint builder_code;

  G_APPLICATION_CLASS (bloat_pad_parent_class)
    ->startup (application);

  g_action_map_add_action_entries (G_ACTION_MAP (application), app_entries, G_N_ELEMENTS (app_entries), application);

  builder = gtk_builder_new ();
  builder_code =  gtk_builder_add_from_file (builder, "m_menu.ui", &builder_error);
  if(!builder_code){
//	  g_print("error:builder fault. %s",builder_error->message);
	  g_error ("String#44 %s", builder_error->message);
	  g_error_free (builder_error);
	  return;
  }


  gtk_application_set_app_menu (GTK_APPLICATION (application), G_MENU_MODEL (gtk_builder_get_object (builder, "app-menu")));
  gtk_application_set_menubar (GTK_APPLICATION (application), G_MENU_MODEL (gtk_builder_get_object (builder, "menubar")));
  g_object_unref (builder);
}

static void
bloat_pad_init (BloatPad *app)
{
}

static void
bloat_pad_class_init (BloatPadClass *class)
{
  GApplicationClass *application_class = G_APPLICATION_CLASS (class);
  GObjectClass *object_class = G_OBJECT_CLASS (class);

  application_class->startup = bloat_pad_startup;
  application_class->activate = bloat_pad_activate;
  application_class->open = bloat_pad_open;

  object_class->finalize = bloat_pad_finalize;

}

BloatPad *
bloat_pad_new (void)
{
  GtkApplication *bloat_pad;

//  g_type_init ();

  g_set_application_name ("Bloatpad");

  bloat_pad = g_object_new (bloat_pad_get_type (),
                            "application-id", "org.gtk.Test.bloatpad",
                            "flags", G_APPLICATION_HANDLES_OPEN,
                            "inactivity-timeout", 30000,
                            "register-session", TRUE,
                            NULL);

  return bloat_pad;
}

int
main (int argc, char **argv)
{
  BloatPad *bloat_pad;
  int status;

  bloat_pad = bloat_pad_new ();

  gtk_application_add_accelerator (GTK_APPLICATION (bloat_pad),
                                   "F11", "win.fullscreen", NULL);

  status = g_application_run (G_APPLICATION (bloat_pad), argc, argv);

  g_object_unref (bloat_pad);

  return status;
}



#endif

///////////////////////

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
  builder_code =  gtk_builder_add_from_file (builder, "menu.ui", &builder_error);
  if(!builder_code){
//	  g_print("error:builder fault. %s",builder_error->message);
	  g_error ("String#44 %s", builder_error->message);
	  g_error_free (builder_error);
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


//  GtkWidget * box = gtk_box_new(0,0);
//  gtk_container_add(GTK_CONTAINER(window),box);
//  gtk_container_add(GTK_CONTAINER(box), (GtkWidget*)button);


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


