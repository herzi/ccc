/* This file is part of CCC
 *
 * AUTHORS
 *     Sven Herzberg  <herzi@gnome-de.org>
 *
 * Copyright (C) 2006  Sven Herzberg
 *
 * This work is provided "as is"; redistribution and modification
 * in whole or in part, in any medium, physical or electronic is
 * permitted without restriction.
 * 		
 * This work is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * 		
 * In no event shall the authors or contributors be liable for any
 * direct, indirect, incidental, special, exemplary, or consequential
 * damages (including, but not limited to, procurement of substitute
 * goods or services; loss of use, data, or profits; or business
 * interruption) however caused and on any theory of liability, whether
 * in contract, strict liability, or tort (including negligence or
 * otherwise) arising in any way out of the use of this software, even
 * if advised of the possibility of such damage.
 */

#include "main.h"

#include <ccc/cc-brush-color.h>
#include <ccc/cc-rounded-rectangle.h>
#include <ccc/cc-view-widget.h>

#ifdef HAVE_CONFIG_H
# include <cc-config.h>
#endif
#include <glib/gi18n-lib.h>

#undef DEBUG_GRADIENT

#ifdef DEBUG_GRADIENT
static void
item_debug_bounds(CcItem* item,
		  CcView* view)
{
	CcDRect const* drect = cc_item_get_all_bounds(item, view);
	g_return_if_fail(drect);
	g_debug("%p: Bounds: (%.0fx%.0f) => (%.0fx%.0f)",
		item, drect->x1, drect->y1, drect->x2, drect->y2);
}
#endif

static CcItem* rrect = NULL;

static void
view_size_allocate(GtkWidget    * widget,
		   GtkAllocation* allocation)
{
#ifdef DEBUG_GRADIENT
	g_debug("start resize (%dx%d) => (%dx%d)",
		allocation->x, allocation->y,
		allocation->x + allocation->width - 1,
		allocation->y + allocation->height - 1);
	item_debug_bounds(rrect, CC_VIEW(widget));
#endif
	cc_rectangle_set_position(CC_RECTANGLE(rrect),
				  0.0, 0.0,
				  allocation->width - 50,
				  allocation->height - 50);
#ifdef DEBUG_GRADIENT
	item_debug_bounds(rrect, CC_VIEW(widget));
	g_debug("end resize");
#endif
}

DemoPage*
gradient_demo(void)
{
	CcItem   * root = cc_item_new();
	GtkWidget* widget = cc_view_widget_new_root(root);
	rrect = cc_rounded_rectangle_new();
	CC_ITEM_SET_FLAGS(rrect, CC_GRID_ALIGNED);
	cc_shape_set_brush_border(CC_SHAPE(rrect), cc_brush_color_new(cc_color_new_rgb(0.8, 0.1, 0.2)));
	cc_shape_set_width_pixels(CC_SHAPE(rrect), 2.0);
	cc_rounded_rectangle_set_radius(CC_ROUNDED_RECTANGLE(rrect), 20.0);
	cc_item_append(root, rrect);
	g_signal_connect_after(widget, "size-allocate",
			       G_CALLBACK(view_size_allocate), NULL);
	return demo_page_new(widget, _("Gradient Editor"));
}

