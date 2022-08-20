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
	
	label = gtk_label_new("dhadkad fdfffffffffffffffffffffffffffffff sssssssssssss.\n fdfdhfkhfka  faketeertertyertret  gdfdg");
	gtk_label_set_line_wrap(GTK_LABEL(label), TRUE);
	
	if(gtk_label_get_line_wrap(GTK_LABEL(label)))
	{
		gtk_label_set_line_wrap_mode(GTK_LABEL(label), PANGO_WRAP_CHAR);
	}
	
	PangoWrapMode wrap = gtk_label_get_line_wrap_mode(GTK_LABEL(label));
	g_print("Wrap is %d\n", wrap);
	
	gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER);
	GtkJustification justification = gtk_label_get_justify(GTK_LABEL(label));
	g_print("Justify = %d\n", justification);
	
	gtk_container_add(GTK_CONTAINER(window), label);
	
	gtk_widget_show_all(window);
	gtk_main();
}

void load_css(void)
{
	GtkCssProvider 	*provider;
	GdkDisplay 		*display;
	GdkScreen 		*screen;
	
	const gchar *css_style_file = "04_main.css";
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

