#include <gtk/gtk.h>

void changed_callback(GtkAdjustment*);
void value_changed_callback(GtkAdjustment*);

int main(void)
{
	GtkAdjustment *adjustment;

	gtk_init(NULL, NULL);

	adjustment = gtk_adjustment_new(0.0, 0.0, 100.0, 1.0, 10.0, 0.0);
	g_signal_connect_swapped(adjustment, "changed", G_CALLBACK(changed_callback), adjustment);
	g_signal_connect_swapped(adjustment, "value-changed", G_CALLBACK(value_changed_callback), adjustment);

	g_print("\tThe values are: \n\n");
	g_print("The value is %.0f\n", gtk_adjustment_get_value(adjustment));
	g_print("The lower is %.0f\n", gtk_adjustment_get_lower(adjustment));
	g_print("The upper is %.0f\n", gtk_adjustment_get_upper(adjustment));
	g_print("The step increment is %.0f\n", gtk_adjustment_get_step_increment(adjustment));
	g_print("The page increment is %.0f\n", gtk_adjustment_get_page_increment(adjustment));
	g_print("The page size is %.0f\n\n", gtk_adjustment_get_page_size(adjustment));

	g_object_set(adjustment, "lower", 10.0, NULL);
	g_object_set(adjustment, "value", 50.0, NULL);

	gtk_main();
}

void changed_callback(GtkAdjustment *adjustment)
{
	(void)adjustment;
	g_print("One of the values was changed\n");
}

void value_changed_callback(GtkAdjustment *adjustment)
{
	g_print("The value was changed to %.2f\n", gtk_adjustment_get_value(adjustment));
}


