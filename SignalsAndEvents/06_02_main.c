#include <gtk/gtk.h>

/*
 * gtk_widget_set_events();
 * gtk_widget_add_events();
 * name_event or name-event?
*/

void load_css(void);
GtkWidget *createWindow(const gint, const gint, const gchar *const);
gboolean scroll_callback(GtkWidget*, GdkEventScroll*);
void user_callback(gpointer);

void main(void)
{
	GtkWidget *window;
	GtkWidget *button;

	gtk_init(NULL, NULL);
	load_css();
	
	window = createWindow(400, 250, "My App");
	
	button = gtk_button_new_with_mnemonic("_Quit");
	gtk_container_add(GTK_CONTAINER(window), button);
	
	g_signal_connect(window, "destroy", gtk_main_quit, NULL);
	g_signal_connect_swapped(button, "clicked", G_CALLBACK(user_callback), (gpointer)"The button was pressed");
	
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
	gtk_container_set_border_width(GTK_CONTAINER(ventana), 10);
	g_signal_connect(ventana, "delete-event", gtk_main_quit, NULL);
	
	return ventana;
}

gboolean scroll_callback(GtkWidget *widget, GdkEventScroll *event)
{	
	if(event->type == GDK_SCROLL)
	{
		if(event->direction == GDK_SCROLL_DOWN)
		{
			g_print("The scroll down was catched\n");
			gtk_label_set_markup(GTK_LABEL(widget), "<span font='16px' color='red'>The scroll Down was catched</span>");
		}
		
		if(event->direction == GDK_SCROLL_UP)
		{
			g_print("The scroll Up was catched\n");
			gtk_label_set_markup(GTK_LABEL(widget), "<span font='20px' color='blue'>The scroll Up was catched</span>");
		}
		
		return FALSE;
	}
	
	return TRUE;
}

void user_callback(gpointer data) 
{
	g_print("%s\n", (char*)data);
}
















