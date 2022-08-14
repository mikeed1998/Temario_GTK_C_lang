#include <gtk/gtk.h>

int main(int argc, char *argv[])
{
	GtkWidget *ventana;
	
	gtk_init(&argc, &argv);
	
	ventana = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	
	g_signal_connect(ventana, "delete_event", gtk_main_quit, NULL);
	
	gtk_widget_show_all(ventana);
	gtk_main();
	return 0;
}

// $ gcc `pkg-config --cflags gtk+-3.0` hello.c -o hello `pkg-config --libs gtk+-3.0`
