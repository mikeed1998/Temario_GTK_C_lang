#include <gtk/gtk.h>


GtkWidget *createWindow(const gint, const gint, const gchar*);
void load_css(void);

void main(void)
{
	GtkWidget *window; 
	GtkWidget *spinButton;
	GtkAdjustment *adjustment;

	gtk_init(NULL, NULL);
	load_css();

	window = createWindow(400, 300, "Spin button");
	
	adjustment = gtk_adjustment_new(50.0, 0.0, 100.0, 1.0, 10.0, 0.0);

	spinButton = gtk_spin_button_new(adjustment, 1.0, 2);
	gtk_style_context_add_class(gtk_widget_get_style_context(spinButton), "spin-button");
	g_object_set(spinButton, "margin-top", 100, "margin-bottom", 100, NULL);
	gtk_container_add(GTK_CONTAINER(window), spinButton);

	gtk_widget_show_all(window);
	gtk_main();
}

void load_css(void)
{
	GtkCssProvider 	*provider = gtk_css_provider_new();
	GdkDisplay 		*display = gdk_display_get_default();
	GdkScreen 		*screen = gdk_display_get_default_screen(display);
	
	const gchar *css_file = "10_style.css";
	GFile *css_fp				= g_file_new_for_path(css_file);
	GError *error 				= 0;
	
	gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
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


