#include <gtk/gtk.h>

GtkWidget *createWindow(const gint, const gint, const gchar*);
void load_css(void);
void v1(void);
void v2(void);

void main(void)
{
	GtkWidget *window;
	GtkWidget *frame;
	GtkWidget *button;

	gtk_init(NULL, NULL);
	load_css();

	window = createWindow(400, 300, "Titulo");

	button = gtk_button_new_with_label("Click Me");
	gtk_widget_set_size_request(button, 20, 20);

	// frame = gtk_frame_new("myFrame");
	frame = gtk_aspect_frame_new("myFrame", 0.5, 0.5, 1.0, FALSE);
	gtk_container_add(GTK_CONTAINER(window), frame);

	gtk_container_add(GTK_CONTAINER(frame), button);

	gtk_widget_show_all(window);
	gtk_main();
}

void load_css(void)
{
	GtkCssProvider 	*provider;
	GdkDisplay 		*display;
	GdkScreen 		*screen;
	
	const gchar *css_style_file = "01_main.css";
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

void v1(void)
{
	GtkWidget *window;
	GtkWidget *frame;
	GtkWidget *button;

	gtk_init(NULL, NULL);
	load_css();

	window = createWindow(400, 300, "Titulo");

	g_object_set(
		window,
		"expand", FALSE,
		"hexpand", FALSE,
		"vexpand", FALSE,
		"hexpand-set", FALSE,
		"vexpand-set", FALSE,
		NULL
	);

	frame = gtk_frame_new("myFrame");

	g_object_set(
		frame,
		"expand", FALSE,
		"hexpand", FALSE,
		"vexpand", FALSE,
		"hexpand-set", FALSE,
		"vexpand-set", FALSE,
		NULL
	);

	gtk_container_add(GTK_CONTAINER(window), frame);

	button = gtk_button_new_with_label("Click Me");
	gtk_widget_set_size_request(button, 100, 100);
	g_object_set(
		button,
		"expand", FALSE,
		"hexpand", FALSE,
		"vexpand", FALSE,
		"hexpand-set", FALSE,
		"vexpand-set", FALSE,
		NULL
	);

	gtk_container_add(GTK_CONTAINER(frame), button);

	gtk_widget_show_all(window);
	gtk_main();
}

void v2(void)
{
	GtkWidget *window;

	gtk_init(NULL, NULL);
	load_css();

	window = createWindow(400, 300, "Titulo");

	g_object_set(
		window,
		"decorated", TRUE,
		NULL
	);

	gtk_widget_show_all(window);
	gtk_main();	
}