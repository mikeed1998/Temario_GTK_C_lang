#include <gtk/gtk.h>

#define EVENTS_MASK ( GDK_ENTER_NOTIFY_MASK | GDK_LEAVE_NOTIFY_MASK | GDK_KEY_PRESS )

void load_css(void);
GtkWidget *createWindow(const gint, const gint, const gchar *const);
GtkWidget *createChild(const gchar *const, const guint, const gint, const gint, const gchar *const);
gboolean enter_event_callback(GtkWidget*, GdkEvent*);
gboolean leave_event_callback(GtkWidget*, GdkEvent*);

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

	child1 = createChild("my-child", 3, 100, 100, "1");
	child2 = createChild("my-child", 3, 100, 100, "2");
	child3 = createChild("my-child", 3, 100, 100, "3");
	child4 = createChild("my-child", 3, 100, 100, "4");

	gtk_grid_attach(GTK_GRID(grid), child1, 0, 0, 1, 1);

	gtk_grid_attach(GTK_GRID(grid), child2, 0, 1, 1, 1);
	
	gtk_grid_attach(GTK_GRID(grid), child3, 1, 0, 1, 1);

	gtk_grid_attach(GTK_GRID(grid), child4, 1, 1, 1, 1);

	gtk_widget_show_all(window);
	gtk_main();
}

void load_css(void)
{
	GtkCssProvider 	*provider;
	GdkDisplay 		*display;
	GdkScreen 		*screen;
	
	const gchar *css_style_file = "07_main.css";
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

GtkWidget *createChild(const gchar *const name, const guint border, const gint width, const gint height, const gchar *const label_text)
{
	GtkWidget *eventBox = gtk_event_box_new();
	GtkWidget *label = gtk_label_new(NULL);
	GtkWidget *child = gtk_grid_new();

	gtk_widget_set_events(eventBox, EVENTS_MASK);
	g_signal_connect_swapped(eventBox, "enter-notify-event", G_CALLBACK(enter_event_callback), child);
	g_signal_connect_swapped(eventBox, "leave-notify-event", G_CALLBACK(leave_event_callback), child);

	gtk_container_add(GTK_CONTAINER(child), eventBox);
	gtk_container_add(GTK_CONTAINER(eventBox), label);

	gtk_widget_set_name(child, name);
	gtk_container_set_border_width(GTK_CONTAINER(child), border);
	gtk_widget_set_size_request(child, width, height);

	g_object_set(
		label, 
		"label", label_text,
		"name", "my-label",
		"margin", 40,
		"tooltip-text", label_text,
		NULL
	);

	return child;
}

gboolean enter_event_callback(GtkWidget *widget, GdkEvent *event)
{
	if(event->type == GDK_ENTER_NOTIFY)
	{
		g_print("Enter\n");
		gtk_widget_set_name(widget, "HOVER");
		return TRUE;
	}

	return FALSE;
}

gboolean leave_event_callback(GtkWidget *widget, GdkEvent *event)
{
	if(event->type == GDK_LEAVE_NOTIFY)
	{
		g_print("Leave\n");
		gtk_widget_set_name(widget, "my-child");
		return TRUE;
	}

	return FALSE;
}


