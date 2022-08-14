#include <gtk/gtk.h>

int main(void)
{
	GtkAdjustment *adjustment;

	gtk_init(NULL, NULL);

	adjustment = gtk_adjustment_new(0, 0, 0, 0, 0, 0);

	g_print("\tBefore\n\n");
	g_print("The value is %.0f\n", gtk_adjustment_get_value(adjustment));
	g_print("The lower is %.0f\n", gtk_adjustment_get_lower(adjustment));
	g_print("The upper is %.0f\n", gtk_adjustment_get_upper(adjustment));
	g_print("The step increment is %.0f\n", gtk_adjustment_get_step_increment(adjustment));
	g_print("The page increment is %.0f\n", gtk_adjustment_get_page_increment(adjustment));
	g_print("The page size is %.0f\n\n", gtk_adjustment_get_page_size(adjustment));

	g_object_set(
		adjustment,
		"value", 0.0,
		"lower", 100.0,
		"upper", 50.0,
		"step-increment", 1.0,
		"page-increment", 10.0,
		"page-size", 0.0,
		NULL);

	g_print("\tAfter\n\n");
	g_print("The value is %.0f\n", gtk_adjustment_get_value(adjustment));
	g_print("The lower is %.0f\n", gtk_adjustment_get_lower(adjustment));
	g_print("The upper is %.0f\n", gtk_adjustment_get_upper(adjustment));
	g_print("The step increment is %.0f\n", gtk_adjustment_get_step_increment(adjustment));
	g_print("The page increment is %.0f\n", gtk_adjustment_get_page_increment(adjustment));
	g_print("The page size is %.0f\n\n", gtk_adjustment_get_page_size(adjustment));

	gtk_main();
}


