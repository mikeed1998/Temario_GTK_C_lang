#include <gtk/gtk.h>

GtkWidget *createWindow(const gint, const gint, const gchar*);
void load_css(void);
void adjustment_value_changed(GtkAdjustment*);
void spin_button_value_changed(GtkSpinButton*);

void main(void)
{
	GtkWidget *window; 
	GtkWidget *spinButton;
	GtkAdjustment *adjustment;

	gtk_init(NULL, NULL);
	load_css();

	window = createWindow(400, 300, "Spin button");
	
	adjustment = gtk_adjustment_new(50.0, 0.0, 100.0, 5.0, 10.0, 0.0);

	spinButton = gtk_spin_button_new(GTK_ADJUSTMENT(adjustment), 1.0, 2);
	g_object_set(spinButton, "margin", 150, NULL);
	gtk_container_add(GTK_CONTAINER(window), spinButton);

	gtk_spin_button_set_snap_to_ticks(GTK_SPIN_BUTTON(spinButton), TRUE);
	// gtk_spin_button_set_update_policy(GTK_SPIN_BUTTON(spinButton), GTK_UPDATE_IF_VALID);
	gtk_spin_button_set_update_policy(GTK_SPIN_BUTTON(spinButton), GTK_UPDATE_ALWAYS);
	// **
	// g_signal_connect_swapped(adjustment, "value-changed", G_CALLBACK(adjustment_value_changed), adjustment);
	g_signal_connect_swapped(spinButton, "value-changed", G_CALLBACK(spin_button_value_changed), spinButton);
	// **
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

void adjustment_value_changed(GtkAdjustment *adjustment)
{
	g_print("The adjustment value was changed to %.2f\n", gtk_adjustment_get_value(adjustment));
}

void spin_button_value_changed(GtkSpinButton *spinButton)
{
	g_print("The spin button value was changed to %.2f\n", gtk_spin_button_get_value(spinButton));
	gtk_spin_button_update(spinButton);
}

