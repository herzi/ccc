/* This file is part of CCC
 *
 * AUTHORS
 *     Sven Herzberg  <herzi@gnome-de.org>
 *
 * Copyright (C) 2006  Sven Herzberg
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

#include "cc-gradient.h"

struct CcGradientPrivate {
	cairo_pattern_t* pattern;
};
#define P(i) (G_TYPE_INSTANCE_GET_PRIVATE((i), CC_TYPE_GRADIENT, struct CcGradientPrivate))

CcBrush*
cc_gradient_new(void)
{
	return g_object_new(CC_TYPE_GRADIENT, NULL);
}

void
cc_gradient_set_pattern(CcGradient     * self,
			cairo_pattern_t* pattern)
{
	g_return_if_fail(CC_IS_GRADIENT(self));
	g_return_if_fail(!pattern || cairo_pattern_status(pattern) == CAIRO_STATUS_SUCCESS);

	if(P(self)->pattern == pattern) {
		return;
	}

	if(P(self)->pattern) {
		cairo_pattern_destroy(P(self)->pattern);
		P(self)->pattern = NULL;
	}

	if(pattern) {
		P(self)->pattern = cairo_pattern_reference(pattern);
	}

	// FIXME: enable
	// g_object_notify(G_OBJECT(self), "pattern");
}

/* GType */
G_DEFINE_TYPE(CcGradient, cc_gradient, CC_TYPE_BRUSH);

static void
cc_gradient_init(CcGradient* self G_GNUC_UNUSED)
{}

static void
gradient_finalize(GObject* object)
{
	cc_gradient_set_pattern(CC_GRADIENT(object), NULL);

	G_OBJECT_CLASS(cc_gradient_parent_class)->finalize(object);
}

static void
gradient_apply(CcBrush* brush,
	       CcView * view,
	       cairo_t* cr)
{
	if(P(brush)->pattern) {
		cairo_set_source(cr, P(brush)->pattern);
	}
	else
	{
		cairo_set_source_rgba(cr, 0.925, 0.16, 0.16, 0.0);
	}
}

static void
cc_gradient_class_init(CcGradientClass* self_class)
{
	GObjectClass* object_class = G_OBJECT_CLASS(self_class);
	CcBrushClass* brush_class = CC_BRUSH_CLASS(self_class);

	/* GObjectClass */
	object_class->finalize = gradient_finalize;

	/* CcBrushClass */
	brush_class->apply = gradient_apply;

	/* CcGradientClass */
	g_type_class_add_private(self_class, sizeof(struct CcGradientPrivate));
}

