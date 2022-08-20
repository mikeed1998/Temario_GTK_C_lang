#include <gtk/gtk.h>

void load_css(void);
GtkWidget *createWindow(const gint, const gint, const gchar *const);
GtkWidget *createChild(const gchar *const, const guint, const gint, const gint);

void main(void)
{
	GtkWidget *window;
	GtkWidget *grid;
	GtkWidget *child1;
	GtkWidget *child2;
	GtkWidget *child3;
	GtkWidget *child4;

	gtk_init(NULL, NULL);
	load_css();
	
	window = createWindow(400, 400, "My App");

	grid = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(window), grid);

	child1 = createChild("my-child", 3, 100, 100);
	child2 = createChild("my-child", 3, 100, 100);
	child3 = createChild("my-child", 3, 100, 100);
	child4 = createChild("my-child", 3, 100, 100);

	gtk_grid_attach(GTK_GRID(grid), child1, 0, 0, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(grid), child2, child1, GTK_POS_RIGHT, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(grid), child3, child1, GTK_POS_BOTTOM, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(grid), child4, child3, GTK_POS_RIGHT, 1, 1);

	GtkWidget *get_child = gtk_grid_get_child_at(GTK_GRID(grid), 0, 1);

	if(get_child == child3)
	{
		g_print("The child was found\n");
		gtk_widget_set_name(get_child, "get-child");
	}

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

GtkWidget *createChild(const gchar *const name, const guint border, const gint width, const gint height)
{
	GtkWidget *child = gtk_grid_new();

	gtk_widget_set_name(child, name);
	gtk_container_set_border_width(GTK_CONTAINER(child), border);
	gtk_widget_set_size_request(child, width, height);

	return child;
}