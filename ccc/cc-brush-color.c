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

#include <ccc/cc-brush-color.h>

G_DEFINE_TYPE(CcBrushColor, cc_brush_color, CC_TYPE_BRUSH);

CcBrush*
cc_brush_color_new(CcColor* color) {
	g_return_val_if_fail(color, NULL);

	return g_object_new(CC_TYPE_BRUSH_COLOR, "color", color, NULL);
}

CcColor*
cc_brush_color_get_color(CcBrushColor* self) {
	g_return_val_if_fail(CC_IS_BRUSH_COLOR(self), NULL);

	return self->color;
}

void
cc_brush_color_set_color(CcBrushColor* self, CcColor* color) {
	g_return_if_fail(CC_IS_BRUSH_COLOR(self));
	g_return_if_fail(color);

	if(self->color == color) {
		return;
	}

	if(self->color) {
		g_object_unref(self->color);
		self->color = NULL;
	}

	if(color) {
		self->color = g_object_ref_sink(color);
	}

	g_object_notify(G_OBJECT(self), "color");
}

/* GType stuff */
enum {
	PROP_0,
	PROP_COLOR
};

static void
cc_brush_color_init(CcBrushColor* self) {}

static void
cbc_dispose(GObject* object) {
	CcBrushColor* self = CC_BRUSH_COLOR(object);
	if(self->disposed) {
		return;
	}
	self->disposed = TRUE;

	g_object_unref(self->color);
	self->color = NULL;

	G_OBJECT_CLASS(cc_brush_color_parent_class)->dispose(object);
}

static void
cbc_get_property(GObject* object, guint prop_id, GValue* value, GParamSpec* pspec) {
	CcBrushColor* self = CC_BRUSH_COLOR(object);

	switch(prop_id) {
	case PROP_COLOR:
		g_value_set_object(value, cc_brush_color_get_color(self));
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
		break;
	}
}

static void
cbc_set_property(GObject* object, guint prop_id, GValue const* value, GParamSpec* pspec) {
	CcBrushColor* self = CC_BRUSH_COLOR(object);

	switch(prop_id) {
	case PROP_COLOR:
		cc_brush_color_set_color(self, g_value_get_object(value));
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
		break;
	}
}

static void
cbc_apply(CcBrush* brush, cairo_t* cr) {
	CcBrushColor* self = CC_BRUSH_COLOR(brush);

	if(CC_IS_COLOR(self->color)) {
		cc_color_apply(self->color, cr);
	}
}

static void
cc_brush_color_class_init(CcBrushColorClass* self_class) {
	GObjectClass* go_class;
	CcBrushClass* cb_class;

	/* GObjectClass */
	go_class = G_OBJECT_CLASS(self_class);
	go_class->dispose      = cbc_dispose;
	go_class->get_property = cbc_get_property;
	go_class->set_property = cbc_set_property;

	g_object_class_install_property(go_class,
					PROP_COLOR,
					g_param_spec_object("color",
							    "Color",
							    "The color",
							    CC_TYPE_COLOR,
							    G_PARAM_READWRITE | G_PARAM_CONSTRUCT));

	/* CcBrushClass */
	cb_class = CC_BRUSH_CLASS(self_class);
	cb_class->apply = cbc_apply;
}

