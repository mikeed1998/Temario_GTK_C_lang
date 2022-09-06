#include <gtk/gtk.h>

GtkWidget *createWindow(const gint, const gint, const gchar*);
void load_css(void);
void run_dialog_callback(GtkWindow*);

void main(void)
{
	GtkWidget *window;
	GtkWidget *button;

	gtk_init(NULL, NULL);
	load_css();

	window = createWindow(400, 300, "Titulo");

	button = gtk_button_new_with_label("Open the dialog");
	g_signal_connect_swapped(button, "clicked", G_CALLBACK(run_dialog_callback), window);

	g_object_set(button, "margin", 50, NULL);
	gtk_container_add(GTK_CONTAINER(window), button);

	gtk_widget_show_all(window);
	gtk_main();
}

void load_css(void)
{
	GtkCssProvider 	*provider;
	GdkDisplay 		*display;
	GdkScreen 		*screen;
	
	const gchar *css_style_file = "";
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

GtkWidget *createWindow(const gint width, const gint height, const gchar *titulo)
{
	GtkWidget *window;
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(window, "destroy", gtk_main_quit, window);
	gtk_window_set_title(GTK_WINDOW(window), titulo);
	gtk_window_set_default_size(GTK_WINDOW(window), width, height);
	gtk_container_set_border_width(GTK_CONTAINER(window), 25);
	return window;
}

void run_dialog_callback(GtkWindow *window)
{
	if(!GTK_IS_WINDOW(window))
	{
		g_print("the provided parameter is wrgn\n");
		g_print("The expected Parameter should be GtkWindow\n");

		return;
	}

	GtkWidget *aboutDialog;

	aboutDialog = gtk_about_dialog_new();
	gtk_window_set_transient_for(GTK_WINDOW(aboutDialog), GTK_WINDOW(window));
	gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(aboutDialog), "myProgramName");
	gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(aboutDialog), "1.0.0");
	gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(aboutDialog), "my Copyright");
	gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(aboutDialog), "Here you can put a Set of comments");
	gtk_about_dialog_set_license(GTK_ABOUT_DIALOG(aboutDialog), "This is the part where you need to set you License Information");
	gtk_about_dialog_set_wrap_license(GTK_ABOUT_DIALOG(aboutDialog), FALSE);

	gtk_widget_show_all(aboutDialog);
}


