/* This file is part of libccc
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

#include "demo-polygon.h"

#include <math.h>
#include <glib/gi18n.h>

struct DemoPolygonPrivate {
	gint n_edges;
};
#define P(i) (G_TYPE_INSTANCE_GET_PRIVATE((i), DEMO_TYPE_POLYGON, struct DemoPolygonPrivate))

CcItem*
demo_polygon_new(gint n)
{
	return g_object_new(DEMO_TYPE_POLYGON, "n-edges", n, NULL);
}

/* GType */
G_DEFINE_TYPE(DemoPolygon, demo_polygon, CC_TYPE_SHAPE);

enum {
	PROP_0,
	PROP_N_EDGES
};

static void
demo_polygon_init(DemoPolygon* self)
{
	cc_shape_set_width_pixels(CC_SHAPE(self), 3.0);
	cc_shape_set_brush_border (CC_SHAPE(self), cc_brush_color_new(cc_color_new_rgb(0.254, 0.395, 0.64)));
	cc_shape_set_brush_content(CC_SHAPE(self), cc_brush_color_new(cc_color_new_rgb(0.984, 0.68,  0.25)));
}

static void
polygon_get_property(GObject   * object,
		     guint       prop_id,
		     GValue    * value,
		     GParamSpec* pspec)
{
	switch(prop_id) {
	case PROP_N_EDGES:
		g_value_set_int(value, P(object)->n_edges);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
		break;
	}
}

static void
polygon_set_property(GObject     * object,
		     guint         prop_id,
		     GValue const* value,
		     GParamSpec  * pspec)
{
	switch(prop_id) {
	case PROP_N_EDGES:
		if(P(object)->n_edges == g_value_get_int(value)) {
			break;
		}
		P(object)->n_edges = g_value_get_int(value);
		g_object_notify(object, "n-edges");
		cc_item_update_bounds(CC_ITEM(object), NULL);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
		break;
	}
}

static void
polygon_update_bounds(CcItem      * item,
		      CcView const* view,
		      gpointer      data)
{
	CcDRect* bounds = cc_hash_map_lookup(item->bounds, view);
	CcDRect drect = {0.0, 0.0, 0.0, 0.0};
	gdouble offset;
	gint i;

	if(P(item)->n_edges % 2) {
		offset = 0.0;
	}
	else {
		offset = 2*G_PI / P(item)->n_edges / 2;
	}
#define radius 20.0
	drect.x1 = radius * sin(offset) - cc_shape_get_width(CC_SHAPE(item), view);
	drect.x2 = radius * sin(offset) + cc_shape_get_width(CC_SHAPE(item), view);
	drect.y1 = radius * sin(offset) - cc_shape_get_width(CC_SHAPE(item), view);
	drect.y2 = radius * cos(offset) + cc_shape_get_width(CC_SHAPE(item), view);
	
	for(i = 1; i < P(item)->n_edges; i++) {
		gdouble x = radius * sin(offset + i*2*G_PI/P(item)->n_edges);
		gdouble y = radius * cos(offset + i*2*G_PI/P(item)->n_edges);
		drect.x1 = MIN(drect.x1, x - cc_shape_get_width(CC_SHAPE(item), view));
		drect.y1 = MIN(drect.y1, y - cc_shape_get_width(CC_SHAPE(item), view));
		drect.x2 = MAX(drect.x2, x + cc_shape_get_width(CC_SHAPE(item), view));
		drect.y2 = MAX(drect.y2, y + cc_shape_get_width(CC_SHAPE(item), view));
	}

        if(!bounds || !cc_d_rect_equal(*bounds, drect)) {
		if(bounds) {
			cc_item_dirty(item, view, *bounds);
			cc_hash_map_remove(item->bounds, view);
		}

		cc_hash_map_insert(item->bounds, (gpointer)view, cc_d_rect_copy(&drect));
		
		cc_item_dirty(item, view, drect);
		cc_item_bounds_changed(item, view);
	}
}

static void
polygon_path(CcShape* shape,
	     CcView * view,
	     cairo_t* cr)
{
	gdouble offset;
	gint i;

	if(P(shape)->n_edges % 2) {
		offset = 0.0;
	}
	else {
		offset = 2*G_PI / P(shape)->n_edges / 2;
	}
#define radius 20.0
	cairo_new_path(cr);
	
	for(i = 0; i < P(shape)->n_edges; i++) {
		gdouble x = radius * sin(offset + i*2*G_PI/P(shape)->n_edges);
		gdouble y = radius * cos(offset + i*2*G_PI/P(shape)->n_edges);
		cc_view_world_to_window(view, &x, &y);
		cairo_line_to(cr, x, y);
	}
	cairo_close_path(cr);
}

static void
demo_polygon_class_init(DemoPolygonClass* self_class)
{
	GObjectClass* object_class = G_OBJECT_CLASS(self_class);
	CcItemClass * item_class = CC_ITEM_CLASS(self_class);
	CcShapeClass* shape_class = CC_SHAPE_CLASS(self_class);

	object_class->get_property = polygon_get_property;
	object_class->set_property = polygon_set_property;
	g_object_class_install_property(object_class, PROP_N_EDGES,
					g_param_spec_int("n-edges",
							 _("N Edges"),
							 _("The number of edges (or corners) of this polygon"),
							 3, G_MAXINT,
							 3, G_PARAM_READWRITE));

	item_class->update_bounds = polygon_update_bounds;

	shape_class->path = polygon_path;

	g_type_class_add_private(self_class, sizeof(struct DemoPolygonPrivate));
}

