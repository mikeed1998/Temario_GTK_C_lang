#include <gtk/gtk.h>

void load_css(void);
GtkWidget *createWindow(const gint, const gint, const gchar*);
gchar *format_value_callback(GtkScale*, gdouble);
void value_changed_callback(GtkRange*);
void move_slider_callback(GtkRange*, GtkScrollType);

void main(void)
{
	GtkWidget *window;
	GtkAdjustment *adjustment;
	GtkWidget *scale;

	gtk_init(NULL, NULL);
	load_css();

	window = createWindow(400, 300, "Titulo");

	adjustment = gtk_adjustment_new(5.0, 0.0, 10.0, 1.0, 2.0, 0.0);

	scale = gtk_scale_new(GTK_ORIENTATION_HORIZONTAL, adjustment);
	g_object_set(scale, "digits", 2, NULL);
	gtk_container_add(GTK_CONTAINER(window), scale);

	// g_signal_connect_swapped(scale, "format-value", G_CALLBACK(format_value_callback), scale);
	// g_signal_connect_swapped(scale, "value-changed", G_CALLBACK(value_changed_callback), scale);
	g_signal_connect_swapped(scale, "move-slider", G_CALLBACK(move_slider_callback), scale);

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

gchar *format_value_callback(GtkScale *scale, gdouble value)
{
	(void)value;
	gdouble get_value = gtk_range_get_value(GTK_RANGE(scale));

	if(GTK_IS_SCALE(scale))
	{
		return g_strdup_printf("-->%.2f<--", get_value);
	}

	return NULL;
}

void value_changed_callback(GtkRange *scale)
{
	if(GTK_IS_RANGE(scale))
	{
		gdouble ret = gtk_range_get_value(scale);
		g_print("Ret = %f\n", ret);
	}
	else
	{
		g_print("Wrong parameter used. Expected GtkRange");
	}
}

void move_slider_callback(GtkRange *range, GtkScrollType step)
{
	g_print("move_slider\n");

	if(GTK_IS_RANGE(range))
	{
		if(step == GTK_SCROLL_JUMP)
		{
			// g_print(" the value is %f\n", gtk_range_get_value(scale));
		}
		else if(step == GTK_SCROLL_STEP_UP) /// up arrow
		{
			g_print("step up was pressed (up arrow)\n");
		}
		else if(step == GTK_SCROLL_STEP_DOWN) /// down arrow
		{
			g_print("step down was pressed (down arrow)\n");
		}
		else if(step == GTK_SCROLL_STEP_LEFT) /// left arrow
		{
			g_print("step left was pressed (left arrow)\n");
		}
		else if(step == GTK_SCROLL_STEP_FORWARD) /// forward arrow
		{
			g_print("step forward was pressed (forward arrow)\n");
		}
		else if(step == GTK_SCROLL_STEP_BACKWARD) /// backward arrow
		{
			g_print("step backward was pressed (backward arrow)\n");
		}
		else if(step == GTK_SCROLL_START) /// start arrow
		{
			g_print("step start was pressed (start arrow)\n");
		}
		else if(step == GTK_SCROLL_END) /// end arrow
		{
			g_print("step end was pressed (end arrow)\n");
		}
		else if(step == GTK_SCROLL_PAGE_UP)
		{
			g_print("CTRL + Up arrow was pressed\n");
		}
	}
}


