#include <gtk/gtk.h>

void load_css(void);
GtkWidget *createWindow(const gint, const gint, const gchar *const);
void destroy_callback(GtkWidget*, gpointer);
gboolean delete_event_callback(GtkWidget*, GdkEvent*, gpointer);
gboolean enter_callback(GtkWidget*, GdkEvent*, gpointer);
gboolean leave_callback(GtkWidget*, GdkEvent*, gpointer);

void main(void)
{
	GtkWidget *window;
	GtkWidget *button;

	gtk_init(NULL, NULL);
	load_css();
	
	window = createWindow(350, 300, "Events");
	
	g_signal_connect(window, "destroy", 	 		G_CALLBACK(destroy_callback), 	 	NULL);
	g_signal_connect(window, "delete-event", 		G_CALLBACK(delete_event_callback), 	NULL);
	
	button = gtk_button_new_with_mnemonic("_Quit");
	gtk_container_add(GTK_CONTAINER(window), button);
	g_signal_connect(button, "clicked", 	 		gtk_main_quit, 						NULL);
	g_signal_connect(button, "enter-notify-event", 	G_CALLBACK(enter_callback),  		window);
	g_signal_connect(button, "leave-notify-event", 	G_CALLBACK(leave_callback), 		window);
	
	
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
	gtk_container_set_border_width(GTK_CONTAINER(ventana), 10);
	g_signal_connect(ventana, "delete-event", gtk_main_quit, NULL);
	
	return ventana;
}

void destroy_callback(GtkWidget *object, gpointer user_data)
{
	(void)object;
	(void)user_data;
	
	gtk_main_quit();
}

gboolean delete_event_callback(GtkWidget *widget, GdkEvent *event, gpointer user_data)
{
	(void)widget;
	(void)user_data;
	
	if(event->type == GDK_DELETE)
	{
		return FALSE;
	}
	
	return TRUE;
}

gboolean enter_callback(GtkWidget *widget, GdkEvent *event, gpointer user_data)
{
	(void)widget;
	
	if(event->type == GDK_ENTER_NOTIFY)
	{
		g_print("The mouse enters the Button Area\n");
		gtk_window_set_title(GTK_WINDOW(user_data), "The mouse enters the Button Area");
		return TRUE;
	}
	
	return FALSE;
}

gboolean leave_callback(GtkWidget *widget, GdkEvent *event, gpointer user_data)
{
	(void)widget;
	
	if(event->type == GDK_LEAVE_NOTIFY)
	{
		g_print("The mouse leave the Button Area\n");
		gtk_window_set_title(GTK_WINDOW(user_data), "The mouse leave the Button Area");
		return TRUE;
	}
	
	return FALSE;
}




