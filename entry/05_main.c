#include <gtk/gtk.h>

#define MAX_LENGTH 8

void load_css(void);
GtkWidget *createWindow(const gint, const gint, const gchar *const);
void entry_callback(GtkEntry*);
void insert_text_callback(GtkWidget*);

void main(void)
{
	GtkWidget *window;
	GtkWidget *entry;

	gtk_init(NULL, NULL);
	load_css();
	
	window = createWindow(200, 200, "My App");
	
	entry = gtk_entry_new();
	gtk_widget_set_name(entry, "entry-1");
	gtk_container_add(GTK_CONTAINER(window), entry);
	
	gtk_entry_set_max_length(GTK_ENTRY(entry), MAX_LENGTH);
	
	gtk_entry_set_visibility(GTK_ENTRY(entry), FALSE);
	
	gtk_entry_set_invisible_char(GTK_ENTRY(entry), '*');
	
	g_signal_connect_swapped(entry, "activate", 	G_CALLBACK(entry_callback), 		entry);
	g_signal_connect_swapped(entry, "insert-text", 	G_CALLBACK(insert_text_callback), 	entry);
	
	gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "Entry is here...");
	
	gtk_widget_show_all(window);
	gtk_main();
}

void load_css(void)
{
	GtkCssProvider 	*provider;
	GdkDisplay 		*display;
	GdkScreen 		*screen;
	
	const gchar *css_style_file = "05_main.css";
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

void entry_callback(GtkEntry *entry)
{
	const gchar *text = gtk_entry_get_text(entry);
	guint16 length = gtk_entry_get_text_length(GTK_ENTRY(entry));
	g_print("Text = %s | Length = %d\n", text, length);
	gtk_entry_set_text(GTK_ENTRY(entry), "");
}

void insert_text_callback(GtkWidget *widget)
{
	guint16 text_length = gtk_entry_get_text_length(GTK_ENTRY(widget));
	
	if(text_length < MAX_LENGTH)
	{
		gtk_entry_set_icon_from_icon_name(GTK_ENTRY(widget), GTK_ENTRY_ICON_SECONDARY, "media-seek-forward");
		gtk_entry_set_progress_fraction(GTK_ENTRY(widget), text_length / 10.0);
	}
	else
	{
		gtk_entry_set_progress_fraction(GTK_ENTRY(widget), 1.0);
		g_print("Maximal msg length was reached\n");
		gtk_entry_set_icon_from_icon_name(GTK_ENTRY(widget), GTK_ENTRY_ICON_SECONDARY, "media-playback-stop");
	}
}







