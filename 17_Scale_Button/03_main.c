#include <gtk/gtk.h>

void load_css(void);
GtkWidget *createWindow(const gint, const gint, const gchar*);

void main(void)
{
	GtkWidget *window;
	GtkWidget *scaleButton;
	GtkAdjustment *adjustment;
	const gchar *icons[] = {
		"media-playback-start",
		"media-playback-pause",
		"media-playback-stop",
		"media-record",
		"media-seek-backward",
		"media-seek-forward",
		"media-skip-backward",
		"media-skip-forward",
		"object-flip-horizontal",
		"object-flip-vertical",
		NULL
	};

	gtk_init(NULL, NULL);
	load_css();

	window = createWindow(400, 300, "Titulo");

	
	scaleButton = gtk_scale_button_new(GTK_ICON_SIZE_DIALOG, 0, 10, 1, NULL);
	g_object_set(scaleButton, "margin-left", 30, NULL);
	gtk_container_add(GTK_CONTAINER(window), scaleButton);

	adjustment = gtk_adjustment_new(5, 0, 10, 1, 2, 0);
	gtk_scale_button_set_adjustment(GTK_SCALE_BUTTON(scaleButton), adjustment);

	gtk_scale_button_set_icons(GTK_SCALE_BUTTON(scaleButton), icons);

	gtk_scale_button_set_value(GTK_SCALE_BUTTON(scaleButton), 10);

	g_print("The value is %f\n", gtk_scale_button_get_value(GTK_SCALE_BUTTON(scaleButton)));

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


