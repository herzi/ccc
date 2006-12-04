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
#include <ccc.h>

#include "herzi-enum-combo.h"
#include "herzi-properties.h"

#ifdef HAVE_CONFIG_H
# include <cc-config.h>
#endif
#include <glib/gi18n-lib.h>

static void
canvas_center_view_toggled(GtkToggleButton* toggle, CcViewWidget* view) {
	gboolean state = gtk_toggle_button_get_active(toggle);
	cc_view_widget_set_center_view(view, state);

	gtk_button_set_label(GTK_BUTTON(toggle), state ? "Centered" : "Not Centered");
}

static void
canvas_zoom_changed(GtkSpinButton* spin, CcView* view) {
	cc_view_set_zoom(view, gtk_spin_button_get_value(spin));
}

static void
pixbuf_position_x_changed(GtkSpinButton* spin, CcPixbuf* pixbuf) {
	cc_pixbuf_set_position_x(pixbuf, gtk_spin_button_get_value(spin));
}

static void
pixbuf_position_y_changed(GtkSpinButton* spin, CcPixbuf* pixbuf) {
	cc_pixbuf_set_position_y(pixbuf, gtk_spin_button_get_value(spin));
}

static void
pixbuf_rotation_changed(GtkSpinButton* spin, CcPixbuf* pbuf) {
	gdouble rotation = G_PI * gtk_spin_button_get_value(spin);
	cc_pixbuf_set_rotation(pbuf, rotation);
}

static void
text_text_changed(GtkEntry* entry, GParamSpec* pspec, CcText* text) {
	gchar const* t_layout = cc_text_get_text(text);
	gchar const* t_entry  = gtk_entry_get_text(entry);

	if(t_layout && t_entry && !strcmp(t_layout, t_entry)) {
		return;
	}

	cc_text_set_text(text, t_entry);
}

static void
update_bounds(CcItem* text, CcView* view, CcDRect* bounds, CcRectangle* rectangle) {
	if(!bounds) {
		return;
	}

	cc_rectangle_set_position(rectangle,
				  bounds->x1, bounds->y1,
				  bounds->x2 - bounds->x1,
				  bounds->y2 - bounds->y1);
}

static void
update_entry_from_layout(CcText* text, GParamSpec* pspec, GtkEntry* entry) {
	gchar const* t_layout = cc_text_get_text(text);
	gchar const* t_entry  = gtk_entry_get_text(entry);

	if(t_layout && t_entry && !strcmp(t_layout, t_entry)) {
		return;
	}

	g_object_freeze_notify(G_OBJECT(entry));
	gtk_entry_set_text(entry, t_layout);
	g_object_freeze_notify(G_OBJECT(entry));
}

static CcItem* root = NULL;
static CcItem* arrow = NULL;

DemoPage*
pixbuf_demo(void) {
	GtkWidget* canvas,
		 * notebook,
		 * widget,
		 * control,
		 * props,
		 * prop_group;
	CcItem   * pitem,
		 * rect;
	GdkPixbuf* pixbuf;
	DemoPage * retval = demo_page_new(gtk_vbox_new(FALSE, 6), _("Pixbuf"));

	root = cc_item_new();
	pitem = cc_pixbuf_new();
	//cc_pixbuf_set_position(CC_PIXBUF(pitem), 10, 10, 128, 128);
	pixbuf = gtk_icon_theme_load_icon(gtk_icon_theme_get_for_screen(gdk_screen_get_default()),
					  "folder", 128,
					  0, NULL);
	cc_pixbuf_set_pixbuf(CC_PIXBUF(pitem), pixbuf);
	g_object_unref(pixbuf);
	cc_item_append(root, pitem);
	rect = cc_rectangle_new();
	cc_item_set_grid_aligned(rect, TRUE);
	cc_item_append(root, rect);
	arrow = cc_line_new();
	cc_item_set_grid_aligned(arrow, TRUE);
	cc_line_line(CC_LINE(arrow), 5.0, 0.0);
	cc_line_line(CC_LINE(arrow), 0.0, 5.0);
	cc_line_line(CC_LINE(arrow), 0.0, 0.0);
	cc_line_line(CC_LINE(arrow), 5.0, 0.0);
	cc_item_append(root, arrow);
	cc_shape_set_brush_border(CC_SHAPE(arrow), cc_brush_color_new(cc_color_new_rgba(0.0, 0.0, 1.0, 0.5)));
	cc_shape_set_brush_border(CC_SHAPE(rect),  cc_brush_color_new(cc_color_new_rgba(1.0, 0.0, 0.0, 0.5)));

	g_signal_connect(pitem, "all-bounds-changed",
			 G_CALLBACK(update_bounds), rect);

	canvas = cc_view_widget_new_root(root);
	GTK_WIDGET_SET_FLAGS(canvas, GTK_CAN_FOCUS);
	gtk_box_pack_start_defaults(GTK_BOX(retval->widget), canvas);

	notebook = gtk_notebook_new();
	gtk_box_pack_start(GTK_BOX(retval->widget), notebook, FALSE, FALSE, 0);

	props = herzi_properties_new();
	prop_group = herzi_properties_add(HERZI_PROPERTIES(props), "Canvas View");

	// Center View
	widget = gtk_toggle_button_new();
	gtk_button_set_use_underline(GTK_BUTTON(widget), TRUE);
	g_signal_connect(widget, "toggled",
			 G_CALLBACK(canvas_center_view_toggled), canvas);
	canvas_center_view_toggled(GTK_TOGGLE_BUTTON(widget), CC_VIEW_WIDGET(canvas));
	herzi_properties_group_add(prop_group, "_Center View", widget);

	// Zoom
	widget = gtk_spin_button_new_with_range(G_MINDOUBLE, G_MAXDOUBLE, 0.01);
	g_signal_connect(widget, "value-changed",
			 G_CALLBACK(canvas_zoom_changed), canvas);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), cc_view_get_zoom(CC_VIEW(canvas)));
	herzi_properties_group_add(prop_group, "_Zoom", widget);

	gtk_notebook_append_page(GTK_NOTEBOOK(notebook),
			         props,
			         gtk_label_new("Canvas View"));

	props = herzi_properties_new();
	prop_group = herzi_properties_add(HERZI_PROPERTIES(props), "Pixbuf");

	// Position
	widget = gtk_spin_button_new_with_range(-G_MAXDOUBLE, G_MAXDOUBLE, 1.0);
	g_signal_connect(widget, "value-changed",
			 G_CALLBACK(pixbuf_position_x_changed), pitem);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), 0.0);
	herzi_properties_group_add(prop_group, "_Horizontal Position", widget);
	widget = gtk_spin_button_new_with_range(-G_MAXDOUBLE, G_MAXDOUBLE, 1.0);
	g_signal_connect(widget, "value-changed",
			 G_CALLBACK(pixbuf_position_y_changed), pitem);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), 0.0);
	herzi_properties_group_add(prop_group, "_Vertical Position", widget);

	// Rotation
	widget = gtk_hbox_new(FALSE, 0);
	control = gtk_spin_button_new_with_range(-1.0, 1.0, 0.002);
	g_signal_connect(control, "value-changed",
			 G_CALLBACK(pixbuf_rotation_changed), pitem);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(control), 0.0);
	gtk_box_pack_start(GTK_BOX(widget), control, FALSE, FALSE, 0);
	control = gtk_label_new("π");
	gtk_box_pack_start(GTK_BOX(widget), control, FALSE, FALSE, 0);
	herzi_properties_group_add(prop_group, "_Rotation", widget);
#if 0
	// Text
	widget = gtk_entry_new();
	g_signal_connect(widget, "notify::text",
			 G_CALLBACK(text_text_changed), text);
	gtk_entry_set_text(GTK_ENTRY(widget), PACKAGE " " VERSION);
	g_signal_connect(text, "notify::text",
			 G_CALLBACK(update_entry_from_layout), widget);
	herzi_properties_group_add(prop_group, "_Text", widget);
#endif
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook),
			         props,
			         gtk_label_new("Pixbuf"));
	return retval;
}

