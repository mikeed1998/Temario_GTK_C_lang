#include <gtk/gtk.h>

void load_css(void);
GtkWidget *createWindow(const gint, const gint, const gchar *const);

void main(void)
{
	GtkWidget *window;
	GtkWidget *label;
	PangoAttrList *attrs_list;
	PangoAttribute *attribute;

	gtk_init(NULL, NULL);
	load_css();
	
	window = createWindow(200, 200, "My App");
	
	label = gtk_label_new("Hello World hello");
	// gtk_label_set_width_chars(GTK_LABEL(label), 100);
	
	attrs_list = pango_attr_list_new();
	
	attribute = pango_attr_size_new(100 * PANGO_SCALE);
	pango_attr_list_insert(attrs_list, attribute);
	
	attribute = pango_attr_foreground_new(255, 255, 255);
	pango_attr_list_insert(attrs_list, attribute);
	
	// attribute = pango_attr_background_new(125, 0, 255);
	// pango_attr_list_insert(attrs_list, attribute);
	
	gtk_label_set_attributes(GTK_LABEL(label), attrs_list);
	
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

