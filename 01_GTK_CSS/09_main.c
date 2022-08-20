#include <gtk/gtk.h>

void load_css(void);
GtkWidget *createWindow(const gint, const gint);

void main(void)
{
	GtkWidget *window;
	GtkWidget *toggle_button;

	gtk_init(NULL, NULL);
	load_css();
	
	window = createWindow(400, 300);
	
	toggle_button = gtk_toggle_button_new_with_label("Click Me");
	g_object_set(toggle_button, "margin", 75, NULL);
	gtk_container_add(GTK_CONTAINER(window), toggle_button);
	
	gtk_widget_show_all(window);
	gtk_main();
}

void load_css(void)
{
	GtkCssProvider 	*provider;
	GdkDisplay 		*display;
	GdkScreen 		*screen;
	
	const gchar *css_style_file = "09_main.css";
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

GtkWidget *createWindow(const gint width, const gint height)
{
	GtkWidget *ventana;
	
	ventana = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(ventana), "My App");
	gtk_window_set_default_size(GTK_WINDOW(ventana), width, height);
	gtk_container_set_border_width(GTK_CONTAINER(ventana), 10);
	g_signal_connect(ventana, "delete-event", gtk_main_quit, NULL);
	
	return ventana;
}



