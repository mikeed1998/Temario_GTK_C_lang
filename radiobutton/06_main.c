#include <gtk/gtk.h>

void load_css(void);
GtkWidget *createWindow(const gint, const gint, const gchar *const);
GtkWidget *createGrid(const guint, gboolean, gboolean, guint, guint);
void toggle_callback(GtkRadioButton*);
void clicked_callback(GtkRadioButton*);
void enter_callback(GtkRadioButton*);
void leave_callback(GtkRadioButton*);

void main(void)
{
	GtkWidget *window;
	GtkWidget *grid;
	GtkWidget *radio_button;
	GtkWidget *radio_button2;
	GtkWidget *new_radio_button;
	GtkWidget *label;

	gtk_init(NULL, NULL);
	load_css();
	
	window = createWindow(400, 350, "My App");

	grid = createGrid(3, FALSE, FALSE, 3, 3);
	gtk_container_add(GTK_CONTAINER(window), grid);

	radio_button = gtk_radio_button_new_with_mnemonic(NULL, "_Click the button");
	radio_button2 = gtk_radio_button_new_with_mnemonic_from_widget(GTK_RADIO_BUTTON(radio_button), "_Now click this button");
	new_radio_button = gtk_radio_button_new(NULL);

	gtk_grid_attach(GTK_GRID(grid), new_radio_button, 	0, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), radio_button2, 		0, 1, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), radio_button,		0, 2, 1, 1);

	label = gtk_label_new("Another RadioButton");

	g_object_set(
		new_radio_button,
		"group", radio_button,
		"active", TRUE,
		"draw-indicator", TRUE,
		"inconsistent", FALSE,
		"child", label,
		"border-width", 0,
		"margin", 20,
		NULL
	);

	g_signal_connect_swapped(radio_button, "toggled", G_CALLBACK(toggle_callback), radio_button);
	g_signal_connect_swapped(radio_button2, "toggled", G_CALLBACK(toggle_callback), radio_button2);
	g_signal_connect_swapped(new_radio_button, "toggled", G_CALLBACK(toggle_callback), new_radio_button);
	g_signal_connect_swapped(new_radio_button, "clicked", G_CALLBACK(clicked_callback), new_radio_button);
	g_signal_connect_swapped(new_radio_button, "enter", G_CALLBACK(enter_callback), new_radio_button);
	g_signal_connect_swapped(new_radio_button, "leave", G_CALLBACK(leave_callback), new_radio_button);

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

void toggle_callback(GtkRadioButton *radioButton)
{
	static gint flag = 1;
	GSList *group = gtk_radio_button_get_group(radioButton);

	while(group != NULL)
	{
		if(gtk_toggle_button_get_active(group->data) && group->data == radioButton)
		{
			g_print("RadioButton %d is active\n", flag);
			break;
		}

		flag++;
		group = group->next;
	}

	flag = 1;
}

void clicked_callback(GtkRadioButton *radioButton)
{
	(void)radioButton;
	g_print("The RadioButton was clicked\n");
}

void enter_callback(GtkRadioButton *radioButton)
{
	(void)radioButton;
	g_print("The mouse is enter on RadioButton surface\n");
}

void leave_callback(GtkRadioButton *radioButton)
{
	(void)radioButton;
	g_print("\nThe mouse is leaving the RadioButton surface\n");
}

