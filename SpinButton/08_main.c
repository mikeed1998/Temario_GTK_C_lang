#include <gtk/gtk.h>

struct _values
{
	gdouble value;
	gdouble lower;
	gdouble upper;
	gdouble step_increment;
	gdouble page_increment;
	gdouble page_size; 
}values;

GtkWidget *createWindow(const gint, const gint, const gchar*);
void load_css(void);
void adjustment_callback(GtkAdjustment*);
void set_up_values(gdouble, gdouble, gdouble, gdouble, gdouble, gdouble);
void value_changed_callback(GtkSpinButton*);
void wrapped_callback(GtkSpinButton*);
gint input_callback(GtkSpinButton*);
gboolean output_output(GtkSpinButton*);

void main(void)
{
	GtkWidget *window; 
	GtkWidget *spinButton;
	GtkAdjustment *adjustment;

	gtk_init(NULL, NULL);
	load_css();

	window = createWindow(400, 300, "Spin button");
	
	set_up_values(20.0, 0.0, 100.0, 1.0, 10.0, 0.0);
	adjustment = gtk_adjustment_new(values.value, values.lower, values.upper, values.step_increment, values.page_increment, values.page_size);
	g_object_set(adjustment, "step-increment", 7.0, NULL);

	spinButton = gtk_spin_button_new(adjustment, 1.0, 2);
	g_object_set(spinButton, "wrap", TRUE, NULL);
	// g_signal_connect_swapped(spinButton, "value-changed", G_CALLBACK(value_changed_callback), spinButton);
	// g_signal_connect_swapped(spinButton, "wrapped", G_CALLBACK(wrapped_callback), spinButton);
	// g_signal_connect_swapped(spinButton, "input", G_CALLBACK(input_callback), spinButton);
	g_signal_connect_swapped(spinButton, "output", G_CALLBACK(output_output), spinButton);
	gtk_container_add(GTK_CONTAINER(window), spinButton);
	g_object_set(spinButton, "margin-top", 100, "margin-bottom", 100, NULL);

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

void adjustment_callback(GtkAdjustment *adjustment)
{
	gdouble temp_lower 			= gtk_adjustment_get_lower(adjustment);
	gdouble temp_upper 			= gtk_adjustment_get_upper(adjustment);
	gdouble temp_step_increment = gtk_adjustment_get_step_increment(adjustment);
	gdouble temp_page_increment = gtk_adjustment_get_page_increment(adjustment);
	gdouble temp_page_size 		= gtk_adjustment_get_page_size(adjustment);

	if((gint)values.lower != (gint)temp_lower)
	{
		g_print("The lower value was changed from %.2f to %.2f\n", values.lower, temp_lower);
		values.lower = temp_lower;
	}
	else if((gint)values.upper != (gint)temp_upper)
	{
		g_print("The upper value was changed from %.2f to %.2f\n", values.upper, temp_upper);
		values.upper = temp_upper;
	}
	else if((gint)values.step_increment != (gint)temp_step_increment)
	{
		g_print("The step_increment value was changed from %.2f to %.2f\n", values.step_increment, temp_step_increment);
		values.step_increment = temp_step_increment;
	}
	else if((gint)values.page_increment != (gint)temp_page_increment)
	{
		g_print("The page_increment value was changed from %.2f to %.2f\n", values.page_increment, temp_page_increment);
		values.page_increment = temp_page_increment;
	}
	else if((gint)values.page_size != (gint)temp_page_size)
	{
		g_print("The page_size value was changed from %.2f to %.2f\n", values.page_size, temp_page_size);
		values.page_size = temp_page_size;
	}
}

void set_up_values(gdouble _value, gdouble _lower, gdouble _upper, gdouble _step_increment, gdouble _page_increment, gdouble _page_size)
{
	values.value = _value;
	values.lower = _lower;
	values.upper = _upper;
	values.step_increment = _step_increment; 
	values.page_increment = _page_increment;
	values.page_size = _page_size;
}

void value_changed_callback(GtkSpinButton *spinButton)
{
	gdouble ret = gtk_spin_button_get_value(spinButton);
	g_print("The spin button value was changed to %.2f\n", ret);
	values.value = ret;
}

void wrapped_callback(GtkSpinButton *spinButton)
{
	(void)spinButton;
	g_print("spin button wrap detected\n");
}

gint input_callback(GtkSpinButton *spinButton)
{
	const gchar *text = gtk_entry_get_text(GTK_ENTRY(spinButton));
	gdouble ret = g_strtod(text, NULL);
	g_print("The detected Input was changed from %s to %f\n", text, ret);
	values.value = ret;
	return TRUE;
}

gboolean output_output(GtkSpinButton *spinButton)
{
	int ret = gtk_spin_button_get_value_as_int(spinButton);
	gchar *text = g_strdup_printf("%02d", ret);
	gtk_entry_set_text(GTK_ENTRY(spinButton), text);
	g_free(text);
	return TRUE;
}
