#include <gtk/gtk.h>

GtkWidget *createWindow(const gint, const gint, const gchar*);
void load_css(void);
GtkWidget *createGrid(gboolean, gboolean);

void main(void)
{
	GtkWidget *window;
	GtkWidget *grid;
	GtkWidget *linkButton;
	const gchar *const uri = "https://www.youtube.com";

	gtk_init(NULL, NULL);
	load_css();

	window = createWindow(400, 300, "GtkLinkButton");

	grid = createGrid(FALSE, TRUE);
	gtk_container_add(GTK_CONTAINER(window), grid);

	linkButton = gtk_link_button_new(uri);
	gtk_container_add(GTK_CONTAINER(grid), linkButton);

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

GtkWidget *createGrid(gboolean row, gboolean col)
{
	GtkWidget *grid = gtk_grid_new();
	gtk_grid_set_row_homogeneous(GTK_GRID(grid), row);
	gtk_grid_set_column_homogeneous(GTK_GRID(grid), col);
	return grid;
}