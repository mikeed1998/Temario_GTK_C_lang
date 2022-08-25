#include <gtk/gtk.h>

GtkWidget *createWindow(const gint, const gint, const gchar*);
void load_css(void);

void main(void)
{
	GtkWidget *window;
	// GtkAdjustment *adjustment;
	GtkWidget *scale;

	gtk_init(NULL, NULL);
	load_css();

	window = createWindow(400, 300, "Titulo");

	// adjustment = gtk_adjustment_new(0.0, 0.0, 10.0, 1.0, 2.0, 0.0);

	// scale = gtk_scale_new(GTK_ORIENTATION_HORIZONTAL, adjustment);
	scale = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 0.0, 10.0, 1.0);

	gtk_range_set_value(GTK_RANGE(scale), 10.0);

	gtk_container_add(GTK_CONTAINER(window), scale);

	// Set the drag value option
	gtk_scale_set_draw_value(GTK_SCALE(scale), TRUE);
	// Set the position of the value
	gtk_scale_set_value_pos(GTK_SCALE(scale), GTK_POS_TOP);
	// Set digits .000
	gtk_scale_set_digits(GTK_SCALE(scale), 3);
	// Setting up the origin
	gtk_scale_set_has_origin(GTK_SCALE(scale), FALSE);
	// Adding marks
	gtk_scale_add_mark(GTK_SCALE(scale), 0, GTK_POS_BOTTOM, "<span background='blue' color='red' size='small'>0</span>");
	gtk_scale_add_mark(GTK_SCALE(scale), 1, GTK_POS_BOTTOM, "<span background='blue' color='red' size='small'>1</span>");
	gtk_scale_add_mark(GTK_SCALE(scale), 2, GTK_POS_BOTTOM, "<span background='blue' color='red' size='small'>2</span>");
	gtk_scale_add_mark(GTK_SCALE(scale), 3, GTK_POS_BOTTOM, "<span background='blue' color='red' size='small'>3</span>");
	gtk_scale_add_mark(GTK_SCALE(scale), 4, GTK_POS_BOTTOM, "<span background='blue' color='red' size='small'>4</span>");
	gtk_scale_add_mark(GTK_SCALE(scale), 5, GTK_POS_BOTTOM, "<span background='blue' color='red' size='small'>5</span>");
	// gtk_scale_clear_marks(GTK_SCALE(scale));
	gtk_scale_add_mark(GTK_SCALE(scale), 6, GTK_POS_BOTTOM, "<span background='blue' color='red' size='small'>6</span>");
	gtk_scale_add_mark(GTK_SCALE(scale), 7, GTK_POS_BOTTOM, "<span background='blue' color='red' size='small'>7</span>");
	gtk_scale_add_mark(GTK_SCALE(scale), 8, GTK_POS_BOTTOM, "<span background='blue' color='red' size='small'>8</span>");
	gtk_scale_add_mark(GTK_SCALE(scale), 9, GTK_POS_BOTTOM, "<span background='blue' color='red' size='small'>9</span>");
	gtk_scale_add_mark(GTK_SCALE(scale), 10, GTK_POS_BOTTOM, "<span background='blue' color='red' size='small'>10</span>");
	// Clear marks
	//***** gtk_scale_clear_marks(GTK_SCALE(scale));
	// Get layout
	PangoLayout *layout = gtk_scale_get_layout(GTK_SCALE(scale));
	// gint ret = pango_layout_get_character_count(layout);
	// g_print("Ret = %d\n", ret);

	const gchar *const markup = "<span color='red' size='small'>1.0000</span>"; // the digits + 1 digit more at the end
	pango_layout_set_markup(layout, markup, (gint)strlen(markup)); 

	/*
	g_object_set(
		scale,
		"digits", 3,
		NULL
	);
	*/

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

