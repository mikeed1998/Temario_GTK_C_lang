#include <gtk/gtk.h>

void load_css(void);
GtkWidget *createWindow(const gint, const gint, const gchar *const);
void entry_callback(GtkEntry*, gpointer);
void icon_press_callback(GtkEntry*, GtkEntryIconPosition*, GdkEvent*, gpointer);
void icon_release_callback(GtkEntry*, GtkEntryIconPosition*, GdkEvent*, gpointer);

void main(void)
{
	GtkWidget *window;
	GtkWidget *entry;

	gtk_init(NULL, NULL);
	load_css();
	
	window = createWindow(200, 200, "My App");
	
	entry = gtk_entry_new();
	gtk_widget_set_name(entry, "entry-1");
	
	gtk_entry_set_max_length(GTK_ENTRY(entry), 100);
	
	gtk_entry_set_width_chars(GTK_ENTRY(entry), 50);
	
	gtk_entry_set_alignment(GTK_ENTRY(entry), 0); // 0.15f 0.45f...
	
	gtk_entry_set_icon_from_icon_name(GTK_ENTRY(entry), GTK_ENTRY_ICON_PRIMARY, "contact-new");
	gtk_entry_set_icon_activatable(GTK_ENTRY(entry), GTK_ENTRY_ICON_PRIMARY, TRUE);
	g_signal_connect_swapped(entry, "activate", G_CALLBACK(entry_callback), entry);
	g_signal_connect_swapped(entry, "icon-press", G_CALLBACK(icon_press_callback), entry);
	g_signal_connect_swapped(entry, "icon-release", G_CALLBACK(icon_release_callback), entry);
	
	gtk_container_add(GTK_CONTAINER(window), entry);
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

void entry_callback(GtkEntry *entry, gpointer user_data)
{
	const gchar *text = gtk_entry_get_text(entry);
	guint16 length = gtk_entry_get_text_length(GTK_ENTRY(entry));
	g_print("Text = %s | Length = %d\n", text, length);
	gtk_entry_set_text(GTK_ENTRY(entry), "");
}

void icon_press_callback(GtkEntry *entry, GtkEntryIconPosition *icon_pos, GdkEvent *event, gpointer user_data)
{
	(void)entry;
	(void)icon_pos;
	(void)event;
	(void)user_data;
	
	g_print("The icon was pressed\n");
}

void icon_release_callback(GtkEntry *entry, GtkEntryIconPosition *icon_pos, GdkEvent *event, gpointer user_data)
{
	(void)entry;
	(void)icon_pos;
	(void)event;
	(void)user_data;
	
	g_print("The icon was released\n");
}





