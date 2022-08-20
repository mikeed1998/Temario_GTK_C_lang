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

	gtk_adjustmnet_set_value(adjustment, (value = 5));
	gtk_adjustmnet_set_lower(adjustment, (lower = 0));
	gtk_adjustmnet_set_upper(adjustment, (upper = 0));
	gtk_adjustmnet_set_step_increment(adjustment, (step_increment = 1));
	gtk_adjustmnet_set_page_increment(adjustment, (page_increment = 10));
	gtk_adjustment_new_page_size(adjustment, page_size = 22);

	gtk_adjustment_clamp_page(adjustment, lower, upper);
	gtk_adjustment_configure(adjustment, 0, 0, 10, 1, 2, 0);

	/*
	value <= lower
	lower >= value <= upper <= value + page_size
	upper > value >= lower <= value + page_size
	value + page_size >= upper > lower > value

	if((upper - lower) <= page_size)
	{
		TRUE;
	}
	else
	{
		LOWER;
	}
	*/

	gtk_main();
}