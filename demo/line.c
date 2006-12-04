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

#include "line.h"

#include <gtk/gtklabel.h>
#include <ccc.h>

#ifdef HAVE_CONFIG_H
# include <cc-config.h>
#endif
#include <glib/gi18n-lib.h>

static void
update_bounds(CcItem* line, CcView* view, CcDRect* bounds, CcRectangle* rect) {
	if(!bounds) {
		return;
	}

	cc_rectangle_set_position(rect,
				  bounds->x1, bounds->y1,
				  bounds->x2 - bounds->x1,
				  bounds->y2 - bounds->y1);
}

DemoPage*
line(void) {
	CcItem* item   = cc_item_new();
	CcItem* line   = cc_line_new();
	CcItem* rect   = cc_rectangle_new();
	DemoPage* page = demo_page_new(cc_view_widget_new_root(item), _("Lines"));
	g_signal_connect(line, "all-bounds-changed",
			 G_CALLBACK(update_bounds), rect);
	cc_line_move(CC_LINE(line), 5.0, 5.0);
	cc_line_line(CC_LINE(line), 95.0, 95.0);
	cc_shape_set_brush_border(CC_SHAPE(rect), cc_brush_color_new(cc_color_new_rgb(1.0, 0.0, 0.0)));
	cc_shape_set_brush_border(CC_SHAPE(line), cc_brush_color_new(cc_color_new_rgb(0.0, 0.0, 1.0)));
	cc_item_append(item, line);
	cc_item_append(item, rect);
	return page;
}
