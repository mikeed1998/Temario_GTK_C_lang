#include <gtk/gtk.h>

void main(void)
{
	GtkWidget *ventana;
	const gchar *const titulo = "My App";
	gint ancho, alto;
	
	gtk_init(NULL, NULL);
	
	ventana = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(ventana), titulo);
	gtk_window_set_default_size(GTK_WINDOW(ventana), 800, 600);
	gtk_window_get_size(GTK_WINDOW(ventana), &ancho, &alto);
	g_print("Ancho = %d - Alto = %d\n", ancho, alto);
	
	gtk_window_set_position(GTK_WINDOW(ventana), GTK_WIN_POS_CENTER);
	gtk_window_get_size(GTK_WINDOW(ventana), &ancho, &alto);
	g_print("Ancho = %d - Alto = %d\n", ancho, alto);
	
	gtk_window_set_position(GTK_WINDOW(ventana), GTK_WIN_POS_MOUSE);
	gtk_window_get_size(GTK_WINDOW(ventana), &ancho, &alto);
	g_print("Ancho = %d - Alto = %d\n", ancho, alto);
	
	gtk_window_move(GTK_WINDOW(ventana), 500, 155);
	gtk_window_get_size(GTK_WINDOW(ventana), &ancho, &alto);
	g_print("Ancho = %d - Alto = %d\n", ancho, alto);
	
	gtk_container_set_border_width(GTK_CONTAINER(ventana), 20);
	
	g_signal_connect(ventana, "delete-event", gtk_main_quit, NULL);
	
	gtk_widget_show_all(ventana);
	gtk_main();
}
