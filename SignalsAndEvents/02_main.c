#include <gtk/gtk.h>

void load_css(void);
GtkWidget *createWindow(const gint, const gint, const gchar *const);
void user_function(GtkWidget*, gpointer);
gboolean user_function2(GtkWidget*, GdkEvent*, gpointer);
void button_was_clicked(GtkWidget*, gpointer);

void main(void)
{
	GtkWidget *window;
	GtkWidget *button;

	gtk_init(NULL, NULL);
	load_css();
	
	window = createWindow(400, 300, "Events");
	button = gtk_button_new_with_mnemonic("_Quit");
	
	gtk_container_add(GTK_CONTAINER(window), button);
	g_signal_connect(button, "clicked", 	 G_CALLBACK(button_was_clicked), NULL);
	
	g_signal_connect(window, "destroy", 	 G_CALLBACK(user_function), 	 NULL);
	g_signal_connect(window, "delete-event", G_CALLBACK(user_function2), 	 NULL);
	
	gtk_widget_show_all(window);
	gtk_main();
}

void load_css(void)
{
	GtkCssProvider 	*provider;
	GdkDisplay 		*display;
	GdkScreen 		*screen;
	
	const gchar *css_style_file = "02_main.css";
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

void user_function(GtkWidget *object, gpointer user_data)
{
	(void)object;
	(void)user_data;
	
	g_print("Goodbye\n");
	
	gtk_main_quit();
}

gboolean user_function2(GtkWidget *widget, GdkEvent *event, gpointer user_data)
{
	(void)widget;
	(void)user_data;
	
	if(event->type == GDK_DELETE)
	{
		g_print("Please use Quit button\n");
		return TRUE;
	}
	
	return FALSE;
}

void button_was_clicked(GtkWidget *widget, gpointer user_data)
{
	(void)widget;
	(void)user_data;
	
	g_print("The Quit button was clicked\n\tGoodbye.\n");
	
	gtk_main_quit();
}



