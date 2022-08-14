#include <gtk/gtk.h>

void load_css(void);

void main(void)
{
	GtkWidget *ventana;
	GtkWidget *boton;
	GtkWidget *boton2;
	GtkWidget *box;
	
	gtk_init(NULL, NULL);
	load_css();
	
	ventana = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(ventana), "My App");
	gtk_window_set_default_size(GTK_WINDOW(ventana), 200, 400);
	gtk_container_set_border_width(GTK_CONTAINER(ventana), 10);
	g_signal_connect(ventana, "delete-event", gtk_main_quit, NULL);
	
	box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	
	boton = gtk_button_new_with_label("Clic ID");
	gtk_widget_set_name(boton, "mi-boton");
	gtk_box_pack_start(GTK_BOX(box), boton, TRUE, TRUE, 0);
	g_signal_connect(boton, "clicked", gtk_main_quit, NULL);
	
	boton2 = gtk_button_new_with_label("Clic Class");
	gtk_style_context_add_class(gtk_widget_get_style_context(boton2), "circular");
	gtk_box_pack_start(GTK_BOX(box), boton2, TRUE, TRUE, 0);
	g_signal_connect(boton2, "clicked", gtk_main_quit, NULL);
	
	gtk_container_add(GTK_CONTAINER(ventana), box);
	
	gtk_widget_show_all(ventana);
	gtk_main();
}

void load_css(void)
{
	GtkCssProvider 	*provider;
	GdkDisplay 		*display;
	GdkScreen 		*screen;
	
	const gchar *css_style_file = "04_main.css";
	GFile *css_fp				= g_file_new_for_path(css_style_file);
	GError *error 				= 0;
	
	provider = gtk_css_provider_new();
	display  = gdk_display_get_default();
	screen   = gdk_display_get_default_screen(display);
	
	gtk_style_context_add_provider_for_screen(
		screen, 
		GTK_STYLE_PROVIDER(provider), 
		GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
	gtk_css_provider_load_from_file(provider, css_fp, &error);
	
	g_object_unref(provider);
}



