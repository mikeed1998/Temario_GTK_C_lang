#include <gtk/gtk.h>

void load_css(void);

void main(void)
{
	GtkWidget *ventana;
	GtkWidget *boton, *boton2, *boton3, *boton4, *boton5, *boton6;
	GtkWidget *box;
	
	gtk_init(NULL, NULL);
	load_css();
	
	ventana = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(ventana), "My App");
	gtk_window_set_default_size(GTK_WINDOW(ventana), 200, 200);
	gtk_container_set_border_width(GTK_CONTAINER(ventana), 10);
	g_signal_connect(ventana, "delete-event", gtk_main_quit, NULL);
	
	box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	
	// >>>
	boton = gtk_button_new_with_mnemonic("C_lick Me");
	gtk_box_pack_start(GTK_BOX(box), boton, TRUE, TRUE, 0);
	g_signal_connect(boton, "clicked", gtk_main_quit, NULL);
	// >>>
	boton2 = gtk_button_new_from_icon_name("media-playback-start", GTK_ICON_SIZE_LARGE_TOOLBAR);
	gtk_button_set_relief(GTK_BUTTON(boton2), GTK_RELIEF_NORMAL);
	gtk_box_pack_start(GTK_BOX(box), boton2, TRUE, TRUE, 0);
	g_signal_connect(boton2, "clicked", gtk_main_quit, NULL);
	// >>>
	boton3 = gtk_button_new_with_label("Mike");
	gtk_button_set_relief(GTK_BUTTON(boton3), GTK_RELIEF_NONE);
	const gchar *ptr = gtk_button_get_label(GTK_BUTTON(boton3));
	g_print("%s\n", ptr);
	gtk_button_set_label(GTK_BUTTON(boton3), "Michael");
	g_print("%s\n", gtk_button_get_label(GTK_BUTTON(boton3)));
	gtk_box_pack_start(GTK_BOX(box), boton3, TRUE, TRUE, 0);
	g_signal_connect(boton3, "clicked", gtk_main_quit, NULL);
	// >>>
	boton4 = gtk_button_new_with_mnemonic("Mike");
	if(gtk_button_get_use_underline(GTK_BUTTON(boton4)))
	{
		g_print("Mnemonic was detected\n");
	}
	else
	{
		g_print("Mnemonic was not detected\n");
	}
	gtk_box_pack_start(GTK_BOX(box), boton4, TRUE, TRUE, 0);
	g_signal_connect(boton4, "clicked", gtk_main_quit, NULL);
	// >>>
	boton5 = gtk_button_new_with_mnemonic("M_ike");
	gtk_button_set_use_underline(GTK_BUTTON(boton5), FALSE);
	gtk_box_pack_start(GTK_BOX(box), boton5, TRUE, TRUE, 0);
	g_signal_connect(boton5, "clicked", gtk_main_quit, NULL);
	// >>>
	boton6 = gtk_button_new();
	GtkWidget *image = gtk_image_new_from_file("icon.png");
	gtk_button_set_image(GTK_BUTTON(boton6), image);
	gtk_box_pack_start(GTK_BOX(box), boton6, TRUE, TRUE, 0);
	g_signal_connect(boton6, "clicked", gtk_main_quit, NULL);
	
	gtk_container_add(GTK_CONTAINER(ventana), box);
	
	gtk_widget_show_all(ventana);
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





