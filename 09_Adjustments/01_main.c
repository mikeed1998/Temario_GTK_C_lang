#include <gtk/gtk.h>

int main(void)
{
	GtkAdjustment *adjustment;

	gdouble value = 0;
	gdouble lower = 0;
	gdouble upper = 0;
	gdouble step_increment = 0;
	gdouble page_increment = 0;
	gdouble page_size = 0;

	gtk_init(NULL, NULL);

	adjustment = gtk_adjustment_new(value, lower, upper, step_increment, page_increment, page_size);

	value = 0;
	gtk_adjustmnet_set_value(adjustment, value);

	lower = 0;
	gtk_adjustmnet_set_lower(adjustment, lower);

	upper = 100.0;
	gtk_adjustmnet_set_upper(adjustment, upper);

	step_increment = 1.0;
	gtk_adjustmnet_set_step_increment(adjustment, step_increment);

	page_increment = 10;
	gtk_adjustmnet_set_page_increment(adjustment, page_increment);

	page_size = 0;

	gtk_main();
}

