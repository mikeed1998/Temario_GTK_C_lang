#include <gtk/gtk.h>

GtkWidget *createWindow(const gint, const gint, const gchar*);
void load_css(void);

void main(void)
{
	GtkWidget *window; 
	GtkWidget *spinButton;

	gtk_init(NULL, NULL);
	load_css();

	window = createWindow(400, 300, "Spin button");
	// **
	spinButton = gtk_spin_button_new_with_range(0.0, 0.0, 1.0);
	g_object_set(spinButton, "margin", 150, NULL);
	gtk_container_add(GTK_CONTAINER(window), spinButton);
	// **
	gtk_spin_button_set_range(GTK_SPIN_BUTTON(spinButton), 0, 100);
	gtk_spin_button_set_digits(GTK_SPIN_BUTTON(spinButton), 2);
	gtk_spin_button_set_increments(GTK_SPIN_BUTTON(spinButton), 1.0, 10.0);
	gtk_spin_button_set_numeric(GTK_SPIN_BUTTON(spinButton), TRUE);
	gtk_spin_button_set_wrap(GTK_SPIN_BUTTON(spinButton), FALSE);
	// **
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(spinButton), 0.0);
	gint temp = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinButton));
	g_print("Temp = %d\n", temp);
	// **
	// gtk_spin_button_spin(GTK_SPIN_BUTTON(spinButton), GTK_SPIN_STEP_FORWARD, 30.0);
	// gtk_spin_button_spin(GTK_SPIN_BUTTON(spinButton), GTK_SPIN_HOME, 0.0);
	// gtk_spin_button_spin(GTK_SPIN_BUTTON(spinButton), GTK_SPIN_END, 0.0);
	gtk_spin_button_spin(GTK_SPIN_BUTTON(spinButton), GTK_SPIN_DEFINED, 33.0); // VALUE + USER_DEFINE = 0.0 + 33.0 = 33.0

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
