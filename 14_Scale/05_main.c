#include <gtk/gtk.h>

GtkWidget *createWindow(const gint, const gint, const gchar*);
void load_css(void);

void main(void)
{
	GtkWidget *window;
	GtkAdjustment *adjustment;
	GtkWidget *scale;

	gtk_init(NULL, NULL);
	load_css();

	window = createWindow(400, 300, "Titulo");

	adjustment = gtk_adjustment_new(5.0, 0.0, 10.0, 1.0, 2.0, 0.0);

	scale = gtk_scale_new(GTK_ORIENTATION_HORIZONTAL, adjustment);
	gtk_container_add(GTK_CONTAINER(window), scale);

	g_object_set(
		scale,
		"digits", 3,
		"draw-value", FALSE,
		"has-origin", FALSE, 
		"value-pos", GTK_POS_RIGHT,
		// Ragen properties
		"inverted", FALSE,
		"round-digits", 2,
		"margin", 50,
		"name", "my-scale", // gtk_widget_set_name(); #my-scale
		"tooltip-text", "",
		NULL
	);

	gtk_widget_show_all(window);
	gtk_main();
}

void load_css(void)
{
	GtkCssProvider 	*provider;
	GdkDisplay 		*display;
	GdkScreen 		*screen;
	
	const gchar *css_style_file = "";
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


