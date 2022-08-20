#include <gtk/gtk.h>

/*
 * gtk_widget_set_events();
 * gtk_widget_add_events();
 * name_event or name-event?
*/

void load_css(void);
GtkWidget *createWindow(const gint, const gint, const gchar *const);
gboolean scroll_callback(GtkWidget*, GdkEventScroll*, gpointer);

void main(void)
{
	GtkWidget *window;
	GtkWidget *event_box;
	GtkWidget *label;

	gtk_init(NULL, NULL);
	load_css();
	
	window = createWindow(350, 250, "My App");
	
	event_box = gtk_event_box_new();
	gtk_widget_set_events(event_box, GDK_SCROLL_MASK);
	gtk_container_add(GTK_CONTAINER(window), event_box);
	
	label = gtk_label_new("Hello there");
	gtk_container_add(GTK_CONTAINER(event_box), label);
	
	g_signal_connect(window, "destroy", gtk_main_quit, NULL);
	g_signal_connect_swapped(event_box, "scroll_event", G_CALLBACK(scroll_callback), label);
	
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

gboolean scroll_callback(GtkWidget *widget, GdkEventScroll *event, gpointer user_data)
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


