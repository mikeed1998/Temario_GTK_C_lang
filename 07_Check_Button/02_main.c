#include <gtk/gtk.h>

void load_css(void);
GtkWidget *createWindow(const gint, const gint, const gchar *const);
GtkWidget *createGrid(const guint, gboolean, gboolean, guint, guint);

void main(void)
{
	GtkWidget *window;
	GtkWidget *grid;
	GtkWidget *check_button;	

	gtk_init(NULL, NULL);
	load_css();
	
	window = createWindow(400, 400, "My App");

	grid = createGrid(3, FALSE, FALSE, 3, 3);
	gtk_container_add(GTK_CONTAINER(window), grid);

	check_button = gtk_check_button_new_with_mnemonic("_Check the button");
	gtk_grid_attach(GTK_GRID(grid), check_button, 0, 0, 1, 1);

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
	gtk_widget_set_events(ventana, GDK_KEY_PRESS_MASK);
	gtk_container_set_border_width(GTK_CONTAINER(ventana), 50);
	g_signal_connect(ventana, "destroy", gtk_main_quit, NULL);
	
	return ventana;
}

GtkWidget *createGrid(const guint border, gboolean row_homogeneous, gboolean column_homogeneous, guint row_spacing, guint column_spacing)
{
	GtkWidget *grid = gtk_grid_new();

	gtk_grid_set_row_homogeneous(GTK_GRID(grid), row_homogeneous);
	gtk_grid_set_column_homogeneous(GTK_GRID(grid), column_homogeneous);
	gtk_grid_set_row_spacing(GTK_GRID(grid), row_spacing);
	gtk_grid_set_column_spacing(GTK_GRID(grid), column_spacing);
	gtk_container_set_border_width(GTK_CONTAINER(grid), border);

	g_object_set(grid, "tooltip-text", "Grid", NULL);

	return grid;
}


