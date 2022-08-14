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
	
	spinButton = gtk_spin_button_new(NULL, 0.0, 0);
	gtk_container_add(GTK_CONTAINER(window), spinButton);
	// Ajuste
	adjustment = gtk_adjustment_new(20.0, 0.0, 100.0, 1.0, 10.0, 0.0);
	// Propiedades
	g_object_set(
		spinButton,
		"margin-top", 			100,
		"margin-bottom", 		100,
		"adjustment", 			adjustment,
		"climb-rate", 			2.0,
		"digits", 				3, 
		"numeric", 				FALSE,
		"snap-to-ticks",	 	FALSE,
		"update-policy", 		GTK_UPDATE_IF_VALID,
		"value", 				10.0,
		"wrap", 				TRUE,
		"editable", 			TRUE,
		"max-length", 			10,
		"primary-icon-name", 	"media-playback-start",
		"secondary-icon-name", 	"insert-image",
		"show-emoji-icon", 		TRUE,
		"visibility", 			FALSE,
		"invisible-char",		'@',
		"opacity", 				1.0,
		NULL
	);

	if(gtk_spin_button_get_update_policy(GTK_SPIN_BUTTON(spinButton)) != GTK_UPDATE_ALWAYS)
	{
		g_object_set(spinButton, "update-policy", GTK_UPDATE_ALWAYS, NULL);
		g_print("The update policy was set to GTK_UPDATE_ALWAYS\n");
	}

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



