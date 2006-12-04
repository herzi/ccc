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

#include "fifteen-grid.h"

#include <ccc.h>

#include "fifteen-item.h"
#include "glib-helpers.h"

#define TILE_SIZE 50.0

CcItem*
fifteen_grid_new(PangoFontDescription* desc) {
	return g_object_new(FIFTEEN_TYPE_GRID, "font-description", desc, NULL);
}

void
fifteen_grid_scramble(FifteenGrid* self) {
	CcItem* elements[16];
	guint   i;

	// fill elements
	for(i = 16; i > 0; i--) {
		gint picked = g_random_int_range(0, i); // random int x: 0 <= x < i
		elements[i - 1] = self->elements[picked];
		self->elements[picked] = self->elements[i - 1];
	}

	for(i = 0; i < 16; i++) {
		self->elements[i] = elements[i];
		if(elements[i]) {
			fifteen_item_move(FIFTEEN_ITEM(elements[i]), i, TILE_SIZE);
		}
	}
}

/* GType stuff */
G_DEFINE_TYPE(FifteenGrid, fifteen_grid, CC_TYPE_RECTANGLE);

enum {
	PROP_0,
	PROP_FONT
};

static guint
fg_position(FifteenGrid* self, FifteenItem* item) {
	guint i;
	for(i = 0; i < 16; i++) {
		if(self->elements[i] == CC_ITEM(item)) {
			return i;
		}
	}

	return -1;
}

static gboolean
fg_element_clicked(FifteenGrid* self, CcView* view, GdkEventButton* ev, FifteenItem* item) {
	gboolean         can_move = FALSE;
	GtkDirectionType direction = 0;
	guint            i;

	i = fg_position(self, item);

	if(i%4 && !self->elements[i-1]) {
		can_move = TRUE;
		direction = GTK_DIR_LEFT;
	} else if((i%4 < 3) && !self->elements[i+1]) {
		can_move = TRUE;
		direction = GTK_DIR_RIGHT;
	} else if((i/4 > 0) && !self->elements[i-4]) {
		can_move = TRUE;
		direction = GTK_DIR_UP;
	} else if((i/4 < 3) && !self->elements[i+4]) {
		can_move = TRUE;
		direction = GTK_DIR_DOWN;
	}

	if(can_move) {
		guint new_i = i;
		switch(direction) {
		case GTK_DIR_UP:
			new_i -= 4;
			break;
		case GTK_DIR_RIGHT:
			new_i += 1;
			break;
		case GTK_DIR_DOWN:
			new_i += 4;
			break;
		case GTK_DIR_LEFT:
			new_i -= 1;
			break;
		default:
			g_assert_not_reached();
			break;
		}

		self->elements[new_i] = CC_ITEM(item);
		self->elements[i] = NULL;

		fifteen_item_move(item, new_i, TILE_SIZE);
	}

	return !can_move;
}

static void
fifteen_grid_init(FifteenGrid* self) {
	CcRectangle* rectangle = CC_RECTANGLE(self);
	CcColor    * color     = cc_color_new_rgb(0.0, 0.0, 0.0);
	CcBrush    * brush     = cc_brush_color_new(color);
	guint        i;

	cc_rectangle_set_position(rectangle, 0.0, 0.0, 4*TILE_SIZE, 4*TILE_SIZE);
	cc_shape_set_brush_border(CC_SHAPE(rectangle), brush);

	cc_item_set_grid_aligned(CC_ITEM(self), TRUE);

	for(i = 0; i < 15; i++) {
		self->elements[i] = fifteen_item_new(i);
		cc_item_set_grid_aligned(CC_ITEM(self->elements[i]), TRUE);
		cc_shape_set_brush_border(CC_SHAPE(self->elements[i]), brush);
		cc_item_append(CC_ITEM(self), self->elements[i]);

		fifteen_item_move(FIFTEEN_ITEM(self->elements[i]), i, TILE_SIZE);

		g_signal_connect_swapped(self->elements[i], "button-press-event",
					 G_CALLBACK(fg_element_clicked), self);
	}

	self->elements[i] = NULL;
}

static void
fg_finalize(GObject* object) {
	FifteenGrid* self = FIFTEEN_GRID(object);

	if(self->font_description) {
		pango_font_description_free(self->font_description);
		self->font_description = NULL;
	}

	G_OBJECT_CLASS(fifteen_grid_parent_class)->dispose(object);
}

static void
fg_get_property(GObject* object, guint prop_id, GValue* value, GParamSpec* pspec) {
	FifteenGrid* self = FIFTEEN_GRID(object);

	switch(prop_id) {
	case PROP_FONT:
		g_value_set_boxed(value, self->font_description);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
		break;
	}
}

static void
fg_child_set_font(FifteenItem* item, PangoFontDescription* desc) {
	cc_text_set_font_description(CC_TEXT(item->text), desc);
}

static void
fg_set_property(GObject* object, guint prop_id, GValue const* value, GParamSpec* pspec) {
	FifteenGrid* self = FIFTEEN_GRID(object);

	switch(prop_id) {
	case PROP_FONT:
		if(self->font_description) {
			pango_font_description_free(self->font_description);
			self->font_description = NULL;
		}

		self->font_description = g_value_dup_boxed(value);

		g_list_foreach(CC_ITEM(self)->children, G_FUNC(fg_child_set_font), self->font_description);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
		break;
	}
}

static void
fifteen_grid_class_init(FifteenGridClass* self_class) {
	GObjectClass* go_class;

	/* GObjectClass */
	go_class = G_OBJECT_CLASS(self_class);
	go_class->finalize     = fg_finalize;
	go_class->get_property = fg_get_property;
	go_class->set_property = fg_set_property;

	g_object_class_install_property(go_class,
					PROP_FONT,
					g_param_spec_boxed("font-description",
							   "Font Description",
							   "Font",
							   PANGO_TYPE_FONT_DESCRIPTION,
							   G_PARAM_READWRITE));
}

