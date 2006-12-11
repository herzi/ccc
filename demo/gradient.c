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
#include <ccc/cc-circle.h>
#include <ccc/cc-linear-gradient.h>
#include <ccc/cc-rounded-rectangle.h>
#include <ccc/cc-view-widget.h>

#ifdef HAVE_CONFIG_H
# include <cc-config.h>
#endif
#include <glib/gi18n-lib.h>

#undef DEBUG_GRADIENT

static CcItem* rrect    = NULL;

static gboolean
knob_button_press_event(CcCircle      * knob,
			CcView        * view,
			GdkEventButton* event)
{
	gdouble* offset = g_new0(gdouble, 2);
	offset[0] = knob->x - event->x;
	offset[1] = knob->y - event->y;
	g_object_set_data_full(G_OBJECT(knob), "CccDemoKnobOffset", offset, g_free);
	cc_view_grab_item(view, CC_ITEM(knob), GDK_BUTTON_RELEASE_MASK | GDK_BUTTON_MOTION_MASK,
			  gdk_cursor_new(GDK_CROSSHAIR), event->time);
	return TRUE;
}

static gboolean
knob_button_release_event(CcCircle      * knob,
			  CcView        * view,
			  GdkEventButton* ev)
{
	gdouble* offset = g_object_get_data(G_OBJECT(knob), "CccDemoKnobOffset");
	cc_circle_set_anchor(knob, ev->x + offset[0], ev->y + offset[1]);
	g_object_set_data(G_OBJECT(knob), "CccDemoKnobOffset", NULL);
	cc_view_ungrab_item(view, CC_ITEM(knob), ev->time);
	return TRUE;
}

static gboolean
knob_motion_notify_event(CcCircle      * knob,
			 CcView        * view,
			 GdkEventMotion* ev)
{
	gdouble* offset = g_object_get_data(G_OBJECT(knob), "CccDemoKnobOffset");
	if(G_LIKELY(offset)) {
		cc_circle_set_anchor(knob, ev->x + offset[0], ev->y + offset[1]);
		return TRUE;
	}
	return FALSE;
}

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
	GtkWidget* widget;
	CcBrush  * brush;
	CcItem   * root = cc_item_new();
	CcItem   * knob;

	rrect = cc_rounded_rectangle_new();
	CC_ITEM_SET_FLAGS(rrect, CC_GRID_ALIGNED);
	cc_shape_set_brush_border(CC_SHAPE(rrect), cc_brush_color_new(cc_color_new_rgb(0.8, 0.1, 0.2)));
	cc_shape_set_width_pixels(CC_SHAPE(rrect), 2.0);
	cc_rounded_rectangle_set_radius(CC_ROUNDED_RECTANGLE(rrect), 20.0);
	cc_item_append(root, rrect);

	brush = cc_linear_gradient_new(0.5, 0.0, 0.5, 1.0);
	cc_gradient_add_stop(CC_GRADIENT(brush), 0.0,  cc_color_new_rgba(0.925, 0.16, 0.16, 0.75));
	cc_gradient_add_stop(CC_GRADIENT(brush), 0.25, cc_color_new_rgba(0.65,  0.0,  0.0,  1.0));
	cc_gradient_add_stop(CC_GRADIENT(brush), 1.0,  cc_color_new_rgba(0.925, 0.16, 0.16, 0.75));
	cc_shape_set_brush_content(CC_SHAPE(rrect), brush);

	knob = cc_circle_new();
	cc_circle_set_anchor(CC_CIRCLE(knob), 100.0, 100.0);
	cc_circle_set_radius(CC_CIRCLE(knob), 5.0);
	cc_shape_set_brush_content(CC_SHAPE(knob), cc_brush_color_new(cc_color_new_rgba(0.36, 0.21, 0.40, 0.75)));
	g_signal_connect(knob, "button-press-event",
			 G_CALLBACK(knob_button_press_event), NULL);
	g_signal_connect(knob, "button-release-event",
			 G_CALLBACK(knob_button_release_event), NULL);
	g_signal_connect(knob, "motion-notify-event",
			 G_CALLBACK(knob_motion_notify_event), NULL);
	cc_item_append(root, knob);

	knob = cc_circle_new();
	cc_circle_set_anchor(CC_CIRCLE(knob), 150.0, 100.0);
	cc_circle_set_radius(CC_CIRCLE(knob), 5.0);
	cc_shape_set_brush_content(CC_SHAPE(knob), cc_brush_color_new(cc_color_new_rgba(0.36, 0.21, 0.40, 0.75)));
	g_signal_connect(knob, "button-press-event",
			 G_CALLBACK(knob_button_press_event), NULL);
	g_signal_connect(knob, "button-release-event",
			 G_CALLBACK(knob_button_release_event), NULL);
	g_signal_connect(knob, "motion-notify-event",
			 G_CALLBACK(knob_motion_notify_event), NULL);
	cc_item_append(root, knob);

	knob = cc_circle_new();
	cc_circle_set_anchor(CC_CIRCLE(knob), 200.0, 100.0);
	cc_circle_set_radius(CC_CIRCLE(knob), 5.0);
	cc_shape_set_brush_content(CC_SHAPE(knob), cc_brush_color_new(cc_color_new_rgba(0.36, 0.21, 0.40, 0.75)));
	g_signal_connect(knob, "button-press-event",
			 G_CALLBACK(knob_button_press_event), NULL);
	g_signal_connect(knob, "button-release-event",
			 G_CALLBACK(knob_button_release_event), NULL);
	g_signal_connect(knob, "motion-notify-event",
			 G_CALLBACK(knob_motion_notify_event), NULL);
	cc_item_append(root, knob);

	widget = cc_view_widget_new_root(root);
	g_signal_connect_after(widget, "size-allocate",
			       G_CALLBACK(view_size_allocate), NULL);
	return demo_page_new(widget, _("Gradient Editor"));
}

