/* This file is part of ccc
 *
 * AUTHORS
 *     Canek Pelaez <canek@ciencias.unam.mx>
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

#include "demo-layers.h"
#include <gtk/gtkscrolledwindow.h>
#include <gtk/gtkvbox.h>
#include <gtk/gtkhbox.h>
#include <gtk/gtkbutton.h>

#include <ccc.h>

#ifdef HAVE_CONFIG_H
# include <cc-config.h>
#endif
#include <glib/gi18n-lib.h>

#define RECT_RADIUS 3

CcItem *layer_demo_root;

static void
raise_to_top (GtkWidget *button, CcItem* circle) 
{
	cc_item_raise_to_top(circle, layer_demo_root);
}

static void
raise (GtkWidget *button, CcItem* circle) 
{
	cc_item_raise(circle, layer_demo_root);
}

static void
lower (GtkWidget *button, CcItem* circle) 
{
	cc_item_lower(circle, layer_demo_root);
}

static void
lower_to_bottom (GtkWidget *button, CcItem* circle) 
{
	cc_item_lower_to_bottom(circle, layer_demo_root);
}

DemoPage*
layers_demo(void) {
	CcItem* root = cc_item_new();
	GtkWidget* view = cc_view_widget_new_root(root);

	CcColor* red_color = cc_color_new_rgb(1.0, 0.0, 0.0);
	CcColor* green_color = cc_color_new_rgb(0.0, 1.0, 0.0);
	CcColor* blue_color = cc_color_new_rgb(0.0, 0.0, 1.0);
	CcColor* gray_color = cc_color_new_rgb(0.5, 0.5, 0.5);
	CcColor* black_color = cc_color_new_rgb(0.0, 0.0, 0.0);
	CcBrush* black_brush = cc_brush_color_new(black_color);

	GtkWidget* swin = gtk_scrolled_window_new(NULL, NULL);
	DemoPage* retval = demo_page_new(gtk_vbox_new(FALSE, 2), _("Layers"));

	gtk_container_set_border_width(GTK_CONTAINER(retval->widget), 6);

	gtk_box_pack_start_defaults(GTK_BOX(retval->widget), swin);
	gtk_container_add(GTK_CONTAINER(swin), view);

	CcItem* circle = cc_circle_new();
	cc_circle_set_anchor(CC_CIRCLE(circle), 275, 300);
	cc_circle_set_radius(CC_CIRCLE(circle), 100);
	cc_shape_set_brush_border(CC_SHAPE(circle), black_brush);
	cc_shape_set_brush_content(CC_SHAPE(circle), cc_brush_color_new(gray_color));
	cc_item_append(root, circle);
	
	CcItem* rect = cc_rounded_rectangle_new();
	cc_rounded_rectangle_set_radius(CC_ROUNDED_RECTANGLE(rect), RECT_RADIUS);
	cc_rectangle_set_position(CC_RECTANGLE(rect), 200, 200, 300, 175);
	cc_shape_set_brush_border(CC_SHAPE(rect), black_brush);
	cc_shape_set_brush_content(CC_SHAPE(rect), cc_brush_color_new(red_color));
	cc_item_append(root, rect);
	
	rect = cc_rounded_rectangle_new();
	cc_rounded_rectangle_set_radius(CC_ROUNDED_RECTANGLE(rect), RECT_RADIUS);
	cc_rectangle_set_position(CC_RECTANGLE(rect), 220, 180, 300, 175);
	cc_shape_set_brush_border(CC_SHAPE(rect), black_brush);
	cc_shape_set_brush_content(CC_SHAPE(rect), cc_brush_color_new(green_color));
	cc_item_append(root, rect);

	rect = cc_rounded_rectangle_new();
	cc_rounded_rectangle_set_radius(CC_ROUNDED_RECTANGLE(rect), RECT_RADIUS);
	cc_rectangle_set_position(CC_RECTANGLE(rect), 240, 160, 300, 175);
	cc_shape_set_brush_border(CC_SHAPE(rect), black_brush);
	cc_shape_set_brush_content(CC_SHAPE(rect), cc_brush_color_new(blue_color));
	cc_item_append(root, rect);
	
	GtkWidget* hbox = gtk_hbox_new(FALSE, 4);
	GtkWidget* button = gtk_button_new_with_label("Raise circle to top");
	g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(raise_to_top), circle);
	gtk_box_pack_start_defaults(GTK_BOX(hbox), button);
	button = gtk_button_new_with_label("Raise circle");
	g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(raise), circle);
	gtk_box_pack_start_defaults(GTK_BOX(hbox), button);
	button = gtk_button_new_with_label("Lower circle");
	g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(lower), circle);
	gtk_box_pack_start_defaults(GTK_BOX(hbox), button);
	button = gtk_button_new_with_label("Lower circle to bottom");
	g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(lower_to_bottom), circle);
	gtk_box_pack_start_defaults(GTK_BOX(hbox), button);

	gtk_box_pack_start(GTK_BOX(retval->widget), hbox, FALSE, FALSE, 0);

	layer_demo_root = root;

	return retval;
}
