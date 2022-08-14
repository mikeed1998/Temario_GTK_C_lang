#include <gtk/gtk.h>

void load_css(void);
GtkWidget *createWindow(const gint, const gint, const gchar *const);
void changed_callback(GtkEditable*);
void delete_text_callback(GtkEditable*, gint, gint);
void insert_text_callback(GtkEditable*, gchar*, gint, gpointer);

void main(void)
{
	GtkWidget *window;
	GtkWidget *entry;

	gtk_init(NULL, NULL);
	load_css();
	
	window = createWindow(200, 200, "My App");
	g_signal_connect_swapped(window, "destroy", gtk_main_quit, window);
	
	entry = gtk_entry_new();
	gtk_widget_set_name(entry, "entry-1");
	gtk_container_add(GTK_CONTAINER(window), entry);
	
	gtk_entry_set_text(GTK_ENTRY(entry), "Hello World");
	
	gtk_editable_set_editable(GTK_EDITABLE(entry), FALSE);
	gtk_editable_set_position(GTK_EDITABLE(entry), 5);
	
	if(gtk_editable_get_editable(GTK_EDITABLE(entry)))
	{
		g_print("TRUE\n");
	}
	
	gchar array[] = "_NEW_TEXT_";
	gint length = sizeof(array);
	gint position = 5;
	gtk_editable_insert_text(GTK_EDITABLE(entry), array, length, &position);
	
	g_print("%d\n", gtk_editable_get_position(GTK_EDITABLE(entry)));
	
	gtk_widget_show_all(window);
	gtk_main();
}

void load_css(void)
{
	GtkCssProvider 	*provider;
	GdkDisplay 		*display;
	GdkScreen 		*screen;
	
	const gchar *css_style_file = "03_main.css";
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

void changed_callback(GtkEditable *editable)
{
	(void)editable;
	g_print("The text was changed\n");
}

void delete_text_callback(GtkEditable *editable, gint start_pos, gint end_pos)
{
	(void)editable;
	g_print("The text was deleted from position: %d to %d\n", start_pos, end_pos);
}

void insert_text_callback(GtkEditable *editable, gchar *new_text, gint new_text_length, gpointer position)
{
	(void)editable;
	g_print("The position is:               %d\n", *(int*)position);
	g_print("The inserted text is:          %s\n", new_text);
	g_print("The inserted text length is:   %d\n", new_text_length);
}

