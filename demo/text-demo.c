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
text_anchor_type_changed(HerziEnumCombo* combo, CcText* text) {
	cc_text_set_anchor_type(text, herzi_enum_combo_get_value(combo));
}

static void
text_size_pixels_toggled(GtkToggleButton* toggle, CcText* text) {
	gboolean state = gtk_toggle_button_get_active(toggle);
	cc_text_set_size_pixels(text, state);

	gtk_button_set_label(GTK_BUTTON(toggle), state ? "Size in Pixels" : "Size in Canvas Units");
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
				  bounds->x1 - 1.0, bounds->y1 - 1.0,
				  bounds->x2 - bounds->x1 + 2.0,
				  bounds->y2 - bounds->y1 + 2.0);
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

static void
text_focus_in(CcText          * text,
	      CcView          * view,
	      GtkDirectionType  dir,
	      CcRectangle     * rect)
{
	cc_shape_set_brush_border(CC_SHAPE(rect),  cc_brush_color_new(cc_color_new_rgba(0.0, 0.0, 0.0, 1.0)));
}

static void
text_focus_out(CcText          * text,
	       CcView          * view,
	       GtkDirectionType  dir,
	       CcRectangle     * rect)
{
	cc_shape_set_brush_border(CC_SHAPE(rect),  cc_brush_color_new(cc_color_new_rgba(0.5, 0.5, 0.5, 0.5)));
}

static CcItem* root = NULL;
static CcItem* arrow = NULL;

DemoPage*
text_demo(void) {
	GtkWidget* canvas,
		 * notebook,
		 * widget,
		 * props,
		 * prop_group;
	CcItem   * text,
		 * rect;
	DemoPage * retval = demo_page_new(gtk_vbox_new(FALSE, 6), _("Text Element"));

	root = cc_item_new();
	text = cc_text_new("");
	CC_ITEM_SET_FLAGS(text, CC_CAN_FOCUS);
	cc_text_set_editable(CC_TEXT(text), TRUE);
	cc_item_append(root, text);
	rect = cc_rectangle_new();
	g_signal_connect(text, "focus-enter",
			 G_CALLBACK(text_focus_in), rect);
	g_signal_connect(text, "focus-leave",
			 G_CALLBACK(text_focus_out), rect);
	cc_item_set_grid_aligned(rect, TRUE);
	cc_item_append(root, rect);
	arrow = cc_line_new();
	cc_item_set_grid_aligned(arrow, TRUE);
	cc_line_line(CC_LINE(arrow), 5.0, 0.0);
	cc_line_line(CC_LINE(arrow), 0.0, 5.0);
	cc_line_line(CC_LINE(arrow), 0.0, 0.0);
	cc_line_line(CC_LINE(arrow), 5.0, 0.0);
	cc_item_append(root, arrow);
	text_focus_out(CC_TEXT(text), NULL, GTK_DIR_TAB_BACKWARD, CC_RECTANGLE(rect));
	cc_shape_set_brush_border(CC_SHAPE(arrow), cc_brush_color_new(cc_color_new_rgba(0.0, 0.0, 1.0, 0.5)));

	g_signal_connect(text, "all-bounds-changed",
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
	prop_group = herzi_properties_add(HERZI_PROPERTIES(props), "Text Element");
	// Anchor
	widget = herzi_enum_combo_new(GTK_TYPE_ANCHOR_TYPE);
	g_signal_connect(widget, "changed",
			 G_CALLBACK(text_anchor_type_changed), text);
	herzi_properties_group_add(prop_group, "_Anchor Type", widget);
	// Size in Pixels
	widget = gtk_toggle_button_new();
	gtk_button_set_use_underline(GTK_BUTTON(widget), TRUE);
	g_signal_connect(widget, "toggled",
			 G_CALLBACK(text_size_pixels_toggled), text);
	text_size_pixels_toggled(GTK_TOGGLE_BUTTON(widget), CC_TEXT(text));
	herzi_properties_group_add(prop_group, "_Size in Pixels", widget);

	// Text
	widget = gtk_entry_new();
	g_signal_connect(widget, "notify::text",
			 G_CALLBACK(text_text_changed), text);
	gtk_entry_set_text(GTK_ENTRY(widget), PACKAGE " " VERSION);
	g_signal_connect(text, "notify::text",
			 G_CALLBACK(update_entry_from_layout), widget);
	herzi_properties_group_add(prop_group, "_Text", widget);
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook),
			         props,
			         gtk_label_new("Text Element"));
	return retval;
}

