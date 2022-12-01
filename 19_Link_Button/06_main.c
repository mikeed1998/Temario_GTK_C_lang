#include <gtk/gtk.h>

#define EVENTS (GDK_ENTER_NOTIFY_MASK | GDK_LEAVE_NOTIFY_MASK)

GtkWidget *createWindow(const gint, const gint, const gchar*);
void load_css(void);
GtkWidget *createGrid(gboolean, gboolean);
gboolean enter_callback(GtkWidget*, GdkEvent*);
gboolean leave_callback(GtkWidget*, GdkEvent*);

void main(void)
{
	GtkWidget *window;
	GtkWidget *grid;
	GtkWidget *linkButton;
	const gchar *const uri = "https://www.youtube.com";
	const gchar *const label = "YouTube";

	gtk_init(NULL, NULL);
	load_css();

	window = createWindow(400, 300, "GtkLinkButton");

	grid = createGrid(FALSE, TRUE);
	gtk_container_add(GTK_CONTAINER(window), grid);

	linkButton = gtk_link_button_new_with_label(uri, label);
	gtk_widget_add_events(linkButton, (gtk_widget_get_events(linkButton) | EVENTS));
	gtk_container_add(GTK_CONTAINER(grid), linkButton);

	GtkStyleContext *context = gtk_widget_get_style_context(linkButton);
	gtk_style_context_add_class(context, "linkButton");

	g_signal_connect(linkButton, "enter-notify-event", G_CALLBACK(enter_callback), linkButton);
	g_signal_connect(linkButton, "leave-notify-event", G_CALLBACK(leave_callback), linkButton);

	gtk_widget_show_all(window);
	gtk_main();
}

void load_css(void)
{
	GtkCssProvider 	*provider;
	GdkDisplay 		*display;
	GdkScreen 		*screen;
	
	const gchar *css_style_file = "06_style.css";
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

gboolean enter_callback(GtkWidget *linkButton, GdkEvent *event)
{
	if(GTK_IS_LINK_BUTTON(linkButton)) {
		if(event->type == GDK_ENTER_NOTIFY) {
			// g_print("The mouse enters the linkButton Area\n");
			gtk_widget_set_name(linkButton, "enter_linkbutton");
			return TRUE;
		}
	}

	return FALSE;
}

gboolean leave_callback(GtkWidget *linkButton, GdkEvent *event)
{
	if(GTK_IS_LINK_BUTTON(linkButton)) {
		if(event->type == GDK_LEAVE_NOTIFY) {
			// g_print("The mouse leave the linkButton Area\n");
			gtk_widget_set_name(linkButton, "enter_linkbutton");
			return TRUE;
		}
	}

	return FALSE;
}


