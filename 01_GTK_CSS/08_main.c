#include <gtk/gtk.h>

void load_css(void);
GtkWidget *createWindow(void);
void user_function(GtkToggleButton*, gpointer);

void main(void)
{
	GtkWidget *ventana;
	GtkWidget *box;
	GtkWidget *tgl_boton;
	
	gtk_init(NULL, NULL);
	load_css();
	
	ventana = createWindow();
	box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	
	tgl_boton = gtk_toggle_button_new_with_mnemonic("_Click Me");
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(tgl_boton), TRUE);
	g_signal_connect(tgl_boton, "toggled", G_CALLBACK(user_function), NULL);
	gtk_box_pack_start(GTK_BOX(box), tgl_boton, TRUE, TRUE, 0);
	
	gtk_container_add(GTK_CONTAINER(ventana), box);
	
	gtk_widget_show_all(ventana);
	gtk_main();
}

void load_css(void)
{
	GtkCssProvider 	*provider;
	GdkDisplay 		*display;
	GdkScreen 		*screen;
	
	const gchar *css_style_file = "08_main.css";
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

GtkWidget *createWindow(void)
{
	GtkWidget *ventana;
	
	ventana = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(ventana), "My App");
	gtk_window_set_default_size(GTK_WINDOW(ventana), 200, 200);
	gtk_container_set_border_width(GTK_CONTAINER(ventana), 10);
	g_signal_connect(ventana, "delete-event", gtk_main_quit, NULL);
	
	return ventana;
}

void user_function(GtkToggleButton *toggleButton, gpointer user_data)
{
	(void)toggleButton;
	(void)user_data;
	
	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggleButton)))
	{
		g_print("The button was clicked\n");
	}
	else
	{
		g_print("The button was released\n");
	}
}



