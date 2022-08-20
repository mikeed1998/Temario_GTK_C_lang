#include <gtk/gtk.h>

void load_css(void);
GtkWidget *createWindow(const gint, const gint, const gchar *const);
void clicked_callback(GtkEditable*);

void main(void)
{
	GtkWidget *window;
	GtkWidget *entry;
	GtkWidget *button;
	GtkWidget *grid;

	gtk_init(NULL, NULL);
	load_css();
	
	window = createWindow(200, 200, "My App");
	g_signal_connect(window, "destroy", gtk_main_quit, NULL);
	
	grid = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(window), grid);
	
	button = gtk_button_new_with_label("Click Me");
	gtk_grid_attach(GTK_GRID(grid), button, 0, 1, 1, 1);
	
	entry = gtk_entry_new();
	g_signal_connect_swapped(button, "clicked", G_CALLBACK(clicked_callback), entry);
	gtk_widget_set_name(entry, "entry-1");
	gtk_container_add(GTK_CONTAINER(grid), entry);
	
	/*
	gtk_entry_set_text(GTK_ENTRY(entry), "Hello World");
	gtk_editable_delete_text(GTK_EDITABLE(entry), 4, 7);
	gtk_editable_select_region(GTK_EDITABLE(entry), 4, 7);
	gchar *text = gtk_editable_get_chars(GTK_EDITABLE(entry), 0, -1);
	g_print("Text = %s\n", text);
	*/
	
	gtk_widget_show_all(window);
	gtk_main();
}

void load_css(void)
{
	GtkCssProvider 	*provider;
	GdkDisplay 		*display;
	GdkScreen 		*screen;
	
	const gchar *css_style_file = "01_main.css";
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

void clicked_callback(GtkEditable *entry)
{
	gtk_entry_get_text(GTK_ENTRY(entry));
	gtk_editable_select_region(GTK_EDITABLE(entry), 4, 7);
}


