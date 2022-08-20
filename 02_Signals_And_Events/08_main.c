#include <gtk/gtk.h>

GtkWidget *createWindow(const gint, const gint, const gchar *const);
gboolean zero_to_nine_keys_callback(GtkWidget*, GdkEventKey*);
gboolean a_to_z_keys_callback(GtkWidget*, GdkEventKey*);
gboolean capslock_on_off_callback(GtkWidget*, GdkEventKey*);
gboolean ctrl_plus_C_key_callback(GtkWidget*, GdkEventKey*);
gboolean shift_plus_C_key_callback(GtkWidget*, GdkEventKey*);
gboolean ctrl_plus_shift_plus_C_key_callback(GtkWidget*, GdkEventKey*);

void main(void)
{
	GtkWidget *window;

	gtk_init(NULL, NULL);
	
	window = createWindow(200, 200, "My App");
	
	gtk_widget_set_events(window, GDK_KEY_PRESS_MASK);
	
	// g_signal_connect_swapped(window, "key_press_event", G_CALLBACK(zero_to_nine_keys_callback), window);
	// g_signal_connect_swapped(window, "key_press_event", G_CALLBACK(a_to_z_keys_callback), window);
	// g_signal_connect_swapped(window, "key_press_event", G_CALLBACK(capslock_on_off_callback), window);
	// g_signal_connect_swapped(window, "key_press_event", G_CALLBACK(ctrl_plus_C_key_callback), window);
	// g_signal_connect_swapped(window, "key_press_event", G_CALLBACK(shift_plus_C_key_callback), window);
	g_signal_connect_swapped(window, "key_press_event", G_CALLBACK(ctrl_plus_shift_plus_C_key_callback), window);
	
	gtk_widget_show_all(window);
	gtk_main();
}

GtkWidget *createWindow(const gint width, const gint height, const gchar *const title)
{
	GtkWidget *ventana;
	
	ventana = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(ventana), title);
	gtk_window_set_default_size(GTK_WINDOW(ventana), width, height);
	gtk_container_set_border_width(GTK_CONTAINER(ventana), 10);
	g_signal_connect(ventana, "delete-event", gtk_main_quit, NULL);
	
	return ventana;
}

gboolean zero_to_nine_keys_callback(GtkWidget *widget, GdkEventKey *event)
{
	(void)widget;
	
	guint keys[10] = {
		GDK_KEY_0, GDK_KEY_1, GDK_KEY_2, GDK_KEY_3, GDK_KEY_4, GDK_KEY_5, GDK_KEY_6, GDK_KEY_7, GDK_KEY_8, GDK_KEY_9
	};
	
	for(guint i = 0; i < 10; i++)
	{
		if(event->keyval == keys[i])
		{
			g_print("The key yo pressed was %c\n", keys[i]);
			return FALSE;
		}
	}
	
	if(event->keyval == GDK_KEY_5)
	{
		g_print("The key you pressed was %c\n", GDK_KEY_5);
		return FALSE;
	}
	
	return TRUE;
}

gboolean a_to_z_keys_callback(GtkWidget *widget, GdkEventKey *event)
{
	(void)widget;
	
	if(event->keyval == GDK_KEY_BackSpace) // Alt_L, tab, Shift_L, Shift_R, Control_L
	{
		g_print("The GDK_KEY_BackSpace was pressed\n");
		return FALSE;
	}
	
	return TRUE;
}

gboolean capslock_on_off_callback(GtkWidget *widget, GdkEventKey *event)
{
	(void)widget;
	
	if(event->state & GDK_LOCK_MASK)
	{
		g_print("Capslock is OFF\n");
		return FALSE;
	}
	
	g_print("Capslock is ON\n");
	return TRUE;
}

gboolean ctrl_plus_C_key_callback(GtkWidget *widget, GdkEventKey *event)
{
	(void)widget;
	
	if(event->state & GDK_CONTROL_MASK)
	{
		if(event->keyval == GDK_KEY_c || event->keyval == GDK_KEY_C)
		{
			g_print("CTRL + C was catched\n");
		}
		
		return FALSE;
	}
	
	return TRUE;
}

gboolean shift_plus_C_key_callback(GtkWidget *widget, GdkEventKey *event)
{
	(void)widget;
	
	if(event->state & GDK_SHIFT_MASK)
	{
		if(event->keyval == GDK_KEY_c || event->keyval == GDK_KEY_C)
		{
			g_print("SHIFT + C was catched\n");
		}
		
		return FALSE;
	}
	
	return TRUE;
}

gboolean ctrl_plus_shift_plus_C_key_callback(GtkWidget *widget, GdkEventKey *event)
{
	(void)widget;
	/*
	g_print("event-state       %u\n", event->state);
	g_print("GDK_SHIFT_MASK    %u\n", GDK_SHIFT_MASK);
	g_print("GDK_CONTROL_MASK  %u\n", event->state);
	*/
	
	if((event->state & (GDK_SHIFT_MASK | GDK_CONTROL_MASK)) == ((GDK_SHIFT_MASK | GDK_CONTROL_MASK)))
	{
		if(event->keyval == GDK_KEY_c || event->keyval == GDK_KEY_C)
		{
			g_print("CTRL + SHIFT + C was catched\n");
		}
		
		return FALSE;
	}
	
	return TRUE;
}




















