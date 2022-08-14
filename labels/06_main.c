#include <gtk/gtk.h>

void load_css(void);
GtkWidget *createWindow(const gint, const gint, const gchar *const);

void main(void)
{
	GtkWidget *window;
	GtkWidget *label;

	gtk_init(NULL, NULL);
	load_css();
	
	window = createWindow(200, 200, "My App");
	
	label = gtk_label_new("Hello World");
	
	/*
	label = gtk_label_new("Hello World");
	gtk_label_set_pattern(GTK_LABEL(label), "___   ___");
	gtk_container_add(GTK_CONTAINER(window), label);
	*/
	
	// const gchar *str = "Hi, I am Michael";
	// char *markup = g_markup_printf_escaped("<span style=\"italic\">%s</span>", str);
	// gtk_label_set_markup(GTK_LABEL(label), markup);
	// g_free(markup);
	
	gtk_label_set_markup(GTK_LABEL(label), "<span underline_color=\"black\" underline=\"double\" background=\"white\" foreground=\"#00FFA0\" weight=\"heavy\" style=\"oblique\" font=\"25px\"><big>My name is Michael</big></span>");
	gtk_container_add(GTK_CONTAINER(window), label);
	
	gtk_widget_show_all(window);
	gtk_main();
}

void load_css(void)
{
	GtkCssProvider 	*provider;
	GdkDisplay 		*display;
	GdkScreen 		*screen;
	
	const gchar *css_style_file = "06_main.css";
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

GtkWidget *createWindow(const gint width, const gint height, const gchar *const title)
{
	GtkWidget *ventana;
	
	ventana = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(ventana), title);
	gtk_window_set_default_size(GTK_WINDOW(ventana), width, height);
	// gtk_widget_set_size_request(ventana, width, height);
	gtk_container_set_border_width(GTK_CONTAINER(ventana), 50);
	g_signal_connect(ventana, "delete-event", gtk_main_quit, NULL);
	
	return ventana;
}

