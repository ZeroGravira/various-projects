#include <gtk/gtk.h>

/*This will be a simulation of the television the game
  will be played on.*/
int main( int argc, char* argv[] ) {

	GtkWidget* window;
	GtkWidget* frame;

	gtk_init( &argc, &argv );

	/*initialize emulator window*/
	window = gtk_window_new( GTK_WINDOW_TOPLEVEL );
	gtk_window_set_title( GTK_WINDOW( window ), "NES emulator" );
	gtk_window_set_default_size( GTK_WINDOW( window ), 230, 200 );
	gtk_window_set_position( GTK_WINDOW( window ), GTK_WIN_POS_CENTER );
	/*gtk_window_set_resizable( GTK_WINDOW( window ), TRUE );*/

	/*initialize frame*/
	frame = gtk_fixed_new();
	gtk_container_add( GTK_CONTAINER( window ), frame );

	/*display everything*/
	gtk_widget_show_all( window );

	/*set program to terminate when window closes*/
	g_signal_connect( window, "destroy", G_CALLBACK( gtk_main_quit ), NULL );
	gtk_main();

	return 0;
}
