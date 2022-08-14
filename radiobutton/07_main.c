#include <gtk/gtk.h>

void load_css(void);
GtkWidget *createWindow(const gint, const gint, const gchar *const);
GtkWidget *createGrid(const guint, gboolean, gboolean, guint, guint);
void toggle_callback(GtkRadioButton*, GtkRadioButton*);
void group_changed_callback(GtkRadioButton*);

void main(void)
{
	GtkWidget *window;
	GtkWidget *grid;
	GtkWidget *radio_button1;
	GtkWidget *radio_button2;
	GtkWidget *radio_button3;
	GtkWidget *i_am_an_alone_radio_button;

	gtk_init(NULL, NULL);
	load_css();
	
	window = createWindow(400, 350, "My App");

	grid = createGrid(3, FALSE, FALSE, 3, 3);
	gtk_container_add(GTK_CONTAINER(window), grid);

	radio_button1 = gtk_radio_button_new_with_label(NULL, "This is the RadioButton 3");
	radio_button2 = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radio_button1), "This is the RadioButton 2");
	radio_button3 = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radio_button1), "This is the RadioButton 1");
	i_am_an_alone_radio_button = gtk_radio_button_new_with_label(NULL, "I am an alone RadioButton");

	gtk_grid_attach(GTK_GRID(grid), radio_button3, 				0, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), radio_button2, 				0, 1, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), radio_button1,				0, 2, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), i_am_an_alone_radio_button,	0, 3, 1, 1);

	g_object_set(
		radio_button3,
		"margin", 20,
		NULL
	);

	g_signal_connect_swapped(radio_button1, "toggled", G_CALLBACK(toggle_callback), radio_button1);
	g_signal_connect_swapped(radio_button2, "toggled", G_CALLBACK(toggle_callback), radio_button2);
	// g_signal_connect_swapped(radio_button3, "toggled", G_CALLBACK(toggle_callback), radio_button3);
	g_signal_connect(radio_button3, "toggled", G_CALLBACK(toggle_callback), i_am_an_alone_radio_button);
	g_signal_connect_swapped(i_am_an_alone_radio_button, "group-changed", G_CALLBACK(group_changed_callback), radio_button2);

	gtk_widget_show_all(window);
	gtk_main();
}

void load_css(void)
{
	GtkCssProvider 	*provider;
	GdkDisplay 		*display;
	GdkScreen 		*screen;
	
	const gchar *css_style_file = "06_main.css";
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

void toggle_callback(GtkRadioButton *radioButton, GtkRadioButton *i_am_an_alone_radio_button)
{
	GSList *group = gtk_radio_button_get_group(radioButton);

	while(group != NULL)
	{
		if(gtk_toggle_button_get_active(group->data) && group->data == radioButton)
		{
			// g_print("RadioButton %d is active\n", flag);
			g_object_set(i_am_an_alone_radio_button, "group", radioButton, NULL);
			break;
		}

		group = group->next;
	}
}

void group_changed_callback(GtkRadioButton *radioButton)
{
	(void)radioButton;
	g_print("The group of \"i_am_an_alone_radio_button\" was changed\n");
}

