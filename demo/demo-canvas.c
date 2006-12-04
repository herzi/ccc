/* this file is part of libccc, criawips' cairo-based canvas
 *
 * AUTHORS
 *       Sven Herzberg        <herzi@gnome-de.org>
 *
 * Copyright (C) 2005,2006 Sven Herzberg
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

#include "demo-canvas.h"

#ifdef HAVE_CONFIG_H
#include <cc-config.h>
#endif /* HAVE_CONFIG_H */

#include <math.h>
#include <ccc.h>

CcItem*
demo_canvas_create(void) {
	CcItem* retval = cc_item_new();
	gdouble center = DEMO_CANVAS_CENTER,
		radius = 125.0;
	CcItem* item;
	gint i;
	CcColor* color;
	CcBrush* brush;

	// the mid-point gets calculated, the top-left corner is -50.0 in each dimension

	/*item = cc_rectangle_new();
	cc_rectangle_set_position(CC_RECTANGLE(item), 0.0, 0.0, center, center);
	color = cc_color_new_rgb(0.0, 0.0, 0.0);
	brush = cc_brush_color_new(color);
	cc_shape_set_brush_border(CC_SHAPE(item), brush);
	cc_item_append(retval, item);*/

	for(i = 0; i < 12; i++) {
		item = cc_rectangle_new();
		cc_item_set_grid_aligned(item, TRUE);

		color = cc_color_new_rgb(0.0, 0.0, 0.0);
		brush = cc_brush_color_new(color);
		cc_shape_set_brush_border(CC_SHAPE(item), brush);

		color = cc_color_new_hsva(1.0 * i / 12, 0.75, 1.0, 0.5);
		brush = cc_brush_color_new(color);
		cc_shape_set_brush_content(CC_SHAPE(item), brush);

		cc_item_append(retval, item);

		cc_rectangle_set_position(CC_RECTANGLE(item),
					  center - 50.0 + sin(i*G_PI/6) * radius,
					  center - 50.0 + cos(i*G_PI/6) * radius,
					  100.0, 100.0);
	}

	item = cc_text_new(PACKAGE " " VERSION);
	cc_text_set_anchor(CC_TEXT(item), center, center);
	cc_text_set_anchor_type(CC_TEXT(item), GTK_ANCHOR_CENTER);
	cc_item_append(retval, item);

	return retval;
}

