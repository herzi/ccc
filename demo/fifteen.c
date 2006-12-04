/* this file is part of libccc, criawips' cairo-based canvas
 *
 * AUTHORS
 *       Sven Herzberg        <herzi@gnome-de.org>
 *
 * Copyright (C) 2005 Sven Herzberg
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

#include "fifteen.h"

#include <gtk/gtk.h>
#include <ccc.h>
#include "fifteen-grid.h"

#ifdef HAVE_CONFIG_H
# include <cc-config.h>
#endif
#include <glib/gi18n-lib.h>

DemoPage*
fifteen(void) {
	DemoPage * page = demo_page_new(gtk_vbox_new(FALSE, 6), _("Fifteen"));
	GtkWidget* widget;
	CcItem   * canvas;

	gtk_container_set_border_width(GTK_CONTAINER(page->widget), 6);

	widget = cc_view_widget_new();
	GTK_WIDGET_SET_FLAGS(widget, GTK_CAN_FOCUS);
	canvas = fifteen_grid_new(gtk_widget_get_style(widget)->font_desc);
	cc_view_set_root(CC_VIEW(widget), canvas);
	gtk_box_pack_start(GTK_BOX(page->widget), widget, TRUE, TRUE, 0);

	widget = gtk_button_new_with_mnemonic("_Scramble");
	g_signal_connect_swapped(widget, "clicked",
				 G_CALLBACK(fifteen_grid_scramble), canvas);
	gtk_box_pack_start(GTK_BOX(page->widget), widget, FALSE, FALSE, 0);

	return page;
}

