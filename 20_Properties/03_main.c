#include <gtk/gtk.h>

GtkWidget *createWindow(const gint, const gint, const gchar*);
void load_css(void);

void main(void)
{
	GtkWidget *window;
	GtkWidget *button;
	GParamSpec *pspec;
	const gchar *property = "relief";
	gint *value;
	
	gtk_init(NULL, NULL);
	load_css();

	window = createWindow(200, 200, "GtkLinkProperties");

	button = gtk_button_new_with_label("Click");

	g_object_set(button, "relief", GTK_RELIEF_NORMAL, NULL);
	// g_object_get(button, "relief", &value, NULL);

	pspec = g_object_class_find_property(G_OBJECT_GET_CLASS(button), property);

	if(G_IS_PARAM_SPEC(pspec)) {
		if(pspec == NULL) {
			g_print("There is no property \'%s\' avaible for this object", property);
		} else {
			const gchar *prop_name = g_param_spec_get_name(pspec);
			g_print("the prop name is %s\n", prop_name);
			g_object_set(button, property, GTK_RELIEF_NONE, NULL);
		}
	}

	gtk_container_add(GTK_CONTAINER(window), button);
	gtk_widget_show_all(window);
	gtk_main();
}

void load_css(void)
{
	GtkCssProvider 	*provider;
	GdkDisplay 		*display;
	GdkScreen 		*screen;
	
	const gchar *css_style_file = "06_style.css";
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
