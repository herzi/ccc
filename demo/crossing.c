/* This file is part of ccc
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

#include "crossing.h"

#include <math.h>
#include <gtk/gtklabel.h>
#include <gtk/gtkscrolledwindow.h>
#include <gtk/gtkvbox.h>
#include <ccc.h>

#ifdef HAVE_CONFIG_H
# include <cc-config.h>
#endif
#include <glib/gi18n-lib.h>

static gboolean
enter_callback(CcShape* shape, CcView* view, GdkEventCrossing* ev) {
	CcColor* color = cc_color_new_rgb(1.0, 0.0, 0.0);
	CcBrush* brush = cc_brush_color_new(color);
	cc_shape_set_brush_border(shape, brush);
	return TRUE;
}

static gboolean
leave_callback(CcShape* shape, CcView* view, GdkEventCrossing* ev) {
	CcColor* color = cc_color_new_rgb(0.0, 0.0, 0.0);
	CcBrush* brush = cc_brush_color_new(color);
	cc_shape_set_brush_border(shape, brush);
	return FALSE;
}

DemoPage*
crossing(void) {
	CcItem* root = cc_item_new();
	GtkWidget* view = cc_view_widget_new_root(root);
	gint i;
	CcColor* color = cc_color_new_rgb(0.0, 0.0, 0.0);
	CcBrush* brush = cc_brush_color_new(color);

	GtkWidget* swin = gtk_scrolled_window_new(NULL, NULL);
	DemoPage* retval = demo_page_new(gtk_vbox_new(FALSE, 6), _("Crossing"));

	gtk_container_set_border_width(GTK_CONTAINER(retval->widget), 6);

	gtk_box_pack_start_defaults(GTK_BOX(retval->widget), swin);
	gtk_container_add(GTK_CONTAINER(swin), view);
	gtk_box_pack_start(GTK_BOX(retval->widget), gtk_label_new("Move the mouse over a circle"), FALSE, FALSE, 0);

#define CENTER 130.0
#define RADIUS 125.0
#define N_CIRCLES 12
	for(i = 0; i < 12; i++) {
		guint j;
		gdouble r[] = {
			25.5,
			15.0,
			 9.0,
			 5.4,
			 3.24,
			 r[4] * 0.6,
			 r[5] * 0.6,
			 r[6] * 0.6
		};
		gdouble out = 0.0;
		for(j = 0; j < G_N_ELEMENTS(r); j++) {
			CcItem* circle = cc_circle_new();
			out += r[j];

			cc_circle_set_anchor(CC_CIRCLE(circle),
					     CENTER + (RADIUS - out) * sin(2.0*G_PI*i/N_CIRCLES),
					     CENTER - (RADIUS - out) * cos(2.0*G_PI*i/N_CIRCLES));
			cc_circle_set_radius(CC_CIRCLE(circle), r[j]);
			cc_shape_set_brush_border(CC_SHAPE(circle), brush);

			g_signal_connect(circle, "enter-notify-event",
					 G_CALLBACK(enter_callback), NULL);
			g_signal_connect(circle, "leave-notify-event",
					 G_CALLBACK(leave_callback), NULL);

			cc_item_append(root, circle);
			out += r[j];
		}
	}
#undef N_CIRCLES

	return retval;
}

