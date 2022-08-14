#include <gtk/gtk.h>

int main(void)
{
	GtkAdjustment *adjustment;

	gdouble value = 50;
	gdouble lower = 0;
	gdouble upper = 100;
	gdouble step_increment = 1;
	gdouble page_increment = 10;
	gdouble page_size = 10;

	gtk_init(NULL, NULL);

	adjustment = gtk_adjustment_new(value, lower, upper, step_increment, page_increment, page_size);

	g_print("\tBefore\n\n");
	g_print("The value is %f\n", gtk_adjustment_get_value(adjustment));
	g_print("The lower is %f\n", gtk_adjustment_get_lower(adjustment));
	g_print("The upper is %f\n", gtk_adjustment_get_upper(adjustment));
	g_print("The step increment is %f\n", gtk_adjustment_get_step_increment(adjustment));
	g_print("The page increment is %f\n", gtk_adjustment_get_page_increment(adjustment));
	g_print("The page size is %f\n\n", gtk_adjustment_get_page_size(adjustment));

	gtk_adjustment_configure(adjustment, 0, 0, 10, 1, 2, 0);

	g_print("\tAfter\n\n");
	g_print("The value is %f\n", gtk_adjustment_get_value(adjustment));
	g_print("The lower is %f\n", gtk_adjustment_get_lower(adjustment));
	g_print("The upper is %f\n", gtk_adjustment_get_upper(adjustment));
	g_print("The step increment is %f\n", gtk_adjustment_get_step_increment(adjustment));
	g_print("The page increment is %f\n", gtk_adjustment_get_page_increment(adjustment));
	g_print("The page size is %f\n\n", gtk_adjustment_get_page_size(adjustment));

	gtk_main();
}


