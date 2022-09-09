#include <gtk/gtk.h>

void load_css(void);
GtkWidget *createWindow(const gint, const gint, const gchar*);

void main(void)
{
	GtkWidget *window;
	GtkWidget *scaleButton;

	gtk_init(NULL, NULL);
	load_css();

	window = createWindow(300, 300, "Titulo");

	scaleButton = gtk_scale_button_new(GTK_ICON_SIZE_DIALOG, 0, 5, 1, NULL);
	gtk_widget_set_name(scaleButton, "my-scale-button");
	gtk_widget_set_size_request(scaleButton, 50, 50);
	g_object_set(scaleButton, "margin", 50, NULL);
	gtk_container_add(GTK_CONTAINER(window), scaleButton);

	gtk_widget_show_all(window);
	gtk_main();
}

void load_css(void)
{
	GtkCssProvider 	*provider;
	GdkDisplay 		*display;
	GdkScreen 		*screen;
	
	const gchar *css_style_file = "07_style.css";
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

GtkWidget *createWindow(const gint width, const gint height, const gchar *titulo)
{
	GtkWidget *window;

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(window, "destroy", gtk_main_quit, window);
	gtk_window_set_title(GTK_WINDOW(window), titulo);
	gtk_window_set_default_size(GTK_WINDOW(window), width, height);
	gtk_container_set_border_width(GTK_CONTAINER(window), 25);
	
	return window;
}



