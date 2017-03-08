/*
 ============================================================================
 Name        : gtk_test.c
 Author      : CUBY
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#define GTK_30



#ifdef GTK_30

#include <gtk/gtk.h>

// Adding for test git  /
#include <glib.h>


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
  g_print ("Hello World\n");
  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}


//#endif

#elif GTK_
#include <stdio.h>
#include <stdlib.h>
//
//int main(void) {
//	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
//	return EXIT_SUCCESS;
//}
//gtk-2.0
#include <gtk/gtk.h>   // Подключаем библиотеку GTK+

int main( int argc, char *argv[] ) {
                               //Объявляем виджеты:
   GtkWidget *label;                                          // Метка
   GtkWidget *window;                                         // Главное окно
   gtk_init( &argc, &argv );                           // Инициализируем GTK+
   window = gtk_window_new( GTK_WINDOW_TOPLEVEL );            // Создаем главное окно
   gtk_window_set_title( GTK_WINDOW( window ),                // Устанавливаем заголовок окна
                        "Здравствуй, мир!");
   label = gtk_label_new( "Здравствуй, мир!" );      // Создаем метку с текстом

   gtk_container_add( GTK_CONTAINER( window ), label );       // Вставляем метку в главное окно

   gtk_widget_show_all( window );                             // Показываем окно вместе с виджетами
   g_signal_connect( G_OBJECT( window ), "destroy", // Соединяем сигнал завершения с выходом
                     G_CALLBACK( gtk_main_quit ), NULL );
   gtk_main();                                                // Приложение переходит в цикл ожидания
   return 0;
}

// elif X11
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <X11/Xlib.h>

extern int errno;

int main( void ) {
   Display *d;
   Window w;
   XEvent e;
   char *msg = "Hello, World!";
   int s;

   if( ( d = XOpenDisplay( getenv("DISPLAY" ) ) ) == NULL ) {  // Соединиться с X сервером,
      printf( "Can't connect X server: %s\n", strerror( errno ) );
      exit( 1 );
   }
   s = DefaultScreen( d );
   w = XCreateSimpleWindow( d, RootWindow( d, s ),     // Создать окно
                            10, 10, 200, 200, 1,
                            BlackPixel( d, s ), WhitePixel( d, s ) );
   XSelectInput( d, w, ExposureMask | KeyPressMask );  // На какие события будем реагировать?
   XMapWindow( d, w );                                 // Вывести окно на экран
   while( 1 ) {                                        // Бесконечный цикл обработки событий
      XNextEvent( d, &e );
      if( e.type == Expose ) {                         // Перерисовать окно
         XFillRectangle( d, w, DefaultGC( d, s ), 20, 20, 10, 10 );
         XDrawString( d, w, DefaultGC( d, s ), 50, 50, msg, strlen( msg ) );
      }
      if( e.type == KeyPress )                         // При нажатии кнопки - выход
         break;
   }
   XCloseDisplay( d );                                 // Закрыть соединение с X сервером
   return 0;
}
#endif
