/* This file is part of libccc
 *
 * AUTHORS
 *     Sven Herzberg  <herzi@gnome-de.org>
 *
 * Copyright (C) 2006  Sven Herzberg <herzi@gnome-de.org>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 2.1 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
 * USA
 */

#include "main.h"

#ifdef HAVE_CONFIG_H
# include <cc-config.h>
#endif /* HAVE_CONFIG_H */

#include <string.h>
#include <gtk/gtk.h>
#include <gtk/gtkprintunixdialog.h>
#include <ccc.h>

#ifdef HAVE_CONFIG_H
# include <cc-config.h>
#endif
#include <glib/gi18n-lib.h>

static void
print_canvas(GtkButton* button)
{
	GtkWidget* dialog = gtk_print_unix_dialog_new(_("Printing the demo canvas"),
						      GTK_WINDOW(gtk_widget_get_toplevel(button)));
	switch(gtk_dialog_run(GTK_DIALOG(dialog))) {
	case GTK_RESPONSE_OK:
		//gtk_print_unix_dialog_get_selected_printer()
		//gtk_print_job_new()
		//gtk_print_job_get_surface()
		break;
	case GTK_RESPONSE_APPLY:
		break;
	case GTK_RESPONSE_CANCEL:
		break;
	}
	gtk_widget_destroy(dialog);
}

DemoPage*
printer_demo(void) {
	DemoPage * retval = g_new0(DemoPage, 1);

	retval->title  = _("Printing");
	retval->widget = gtk_button_new_from_stock(GTK_STOCK_PRINT);
	g_signal_connect(retval->widget, "clicked",
			 G_CALLBACK(print_canvas), NULL);

	return retval;
}

