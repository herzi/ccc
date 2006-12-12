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

#include <math.h>
#include <ccc/cc-brush-color.h>
#include <ccc/cc-circle.h>
#include <ccc/cc-linear-gradient.h>
#include <ccc/cc-radial-gradient.h>
#include <ccc/cc-rounded-rectangle.h>
#include <ccc/cc-text.h>
#include <ccc/cc-view-widget.h>

#ifdef HAVE_CONFIG_H
# include <cc-config.h>
#endif
#include <glib/gi18n-lib.h>

#undef DEBUG_GRADIENT

static CcItem* rrect     = NULL;
static CcItem* text      = NULL;
static CcItem* knobs[3]  = {};
static gdouble offset    = 0.25;
static CcDRect rect = {};

static void
update_stops(void)
{
	CcBrush* brush = cc_linear_gradient_new(rect.x1, rect.y1, rect.x2, rect.y2);
	cc_shape_set_brush_content(CC_SHAPE(rrect), brush);
	cc_gradient_add_stop(CC_GRADIENT(brush), 0.0,    cc_color_new_rgba(0.925, 0.16, 0.16, 0.75));
	cc_gradient_add_stop(CC_GRADIENT(brush), offset, cc_color_new_rgba(0.65,  0.0,  0.0,  1.0));
	cc_gradient_add_stop(CC_GRADIENT(brush), 1.0,    cc_color_new_rgba(0.925, 0.16, 0.16, 0.75));
}

static void
update_box(void)
{
	rect.x1 = (CC_CIRCLE(knobs[0])->x - CC_RECTANGLE(rrect)->x)/(CC_RECTANGLE(rrect)->w - CC_RECTANGLE(rrect)->x);
	rect.y1 = (CC_CIRCLE(knobs[0])->y - CC_RECTANGLE(rrect)->y)/(CC_RECTANGLE(rrect)->h - CC_RECTANGLE(rrect)->y);
	rect.x2 = (CC_CIRCLE(knobs[2])->x - CC_RECTANGLE(rrect)->x)/(CC_RECTANGLE(rrect)->w - CC_RECTANGLE(rrect)->x);
	rect.y2 = (CC_CIRCLE(knobs[2])->y - CC_RECTANGLE(rrect)->y)/(CC_RECTANGLE(rrect)->h - CC_RECTANGLE(rrect)->y);
	cc_circle_set_anchor(CC_CIRCLE(knobs[1]),
			     CC_CIRCLE(knobs[0])->x + offset * (CC_CIRCLE(knobs[2])->x - CC_CIRCLE(knobs[0])->x),
			     CC_CIRCLE(knobs[0])->y + offset * (CC_CIRCLE(knobs[2])->y - CC_CIRCLE(knobs[0])->y));
	update_stops();
}

static void
update_offset(gdouble x,
	      gdouble y)
{
	// FIXME: this calculation should be replaced by a correct one
	gdouble diff0,
		diff1,
		diff2;
	diff0 = hypot(x - CC_CIRCLE(knobs[0])->x,
		      y - CC_CIRCLE(knobs[0])->y);
	diff1 = hypot(CC_CIRCLE(knobs[2])->x - CC_CIRCLE(knobs[0])->x,
		      CC_CIRCLE(knobs[2])->y - CC_CIRCLE(knobs[0])->y);
	diff2 = hypot(x - CC_CIRCLE(knobs[2])->x,
		      y - CC_CIRCLE(knobs[2])->y);
	offset = CLAMP(diff0 / (diff0 + diff2), 0.0, 1.0);
	cc_circle_set_anchor(CC_CIRCLE(knobs[1]),
			     CC_CIRCLE(knobs[0])->x + offset * (CC_CIRCLE(knobs[2])->x - CC_CIRCLE(knobs[0])->x),
			     CC_CIRCLE(knobs[0])->y + offset * (CC_CIRCLE(knobs[2])->y - CC_CIRCLE(knobs[0])->y));
	update_stops();
}

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
knob_button_release_event(CcItem        * knob,
			  CcView        * view,
			  GdkEventButton* ev)
{
	gdouble* offset = g_object_get_data(G_OBJECT(knob), "CccDemoKnobOffset");
	if(knob == knobs[0] || knob == knobs[2]) {
		cc_circle_set_anchor(CC_CIRCLE(knob), ev->x + offset[0], ev->y + offset[1]);
		update_box();
	}
	else {
		update_offset(ev->x, ev->y);
	}
	g_object_set_data(G_OBJECT(knob), "CccDemoKnobOffset", NULL);
	cc_view_ungrab_item(view, CC_ITEM(knob), ev->time);
	return TRUE;
}

static gboolean
knob_motion_notify_event(CcItem        * knob,
			 CcView        * view,
			 GdkEventMotion* ev)
{
	gdouble* offset = g_object_get_data(G_OBJECT(knob), "CccDemoKnobOffset");
	if(G_LIKELY(offset)) {
		if(knob == knobs[0] || knob == knobs[2]) {
			cc_circle_set_anchor(CC_CIRCLE(knob), ev->x + offset[0], ev->y + offset[1]);
			update_box();
		}
		else {
			update_offset(ev->x, ev->y);
		}
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

	cc_text_set_anchor(CC_TEXT(text),
			   0.5 * (allocation->width - 50),
			   allocation->height - 65);
	cc_circle_set_anchor(CC_CIRCLE(knobs[0]),
			     rect.x1 * (allocation->width - 50),
			     rect.y1 * (allocation->height - 50));
	cc_circle_set_anchor(CC_CIRCLE(knobs[2]),
			     rect.x2 * (allocation->width - 50),
			     rect.y2 * (allocation->height - 50));
	update_box();
}

DemoPage*
gradient_demo(void)
{
	GtkWidget* widget;
	CcBrush  * brush;
	CcItem   * root = cc_item_new();

	rrect = cc_rounded_rectangle_new();
	CC_ITEM_SET_FLAGS(rrect, CC_GRID_ALIGNED);
	cc_shape_set_brush_border(CC_SHAPE(rrect), cc_brush_color_new(cc_color_new_rgb(0.8, 0.1, 0.2)));
	cc_shape_set_width_pixels(CC_SHAPE(rrect), 2.0);
	cc_rounded_rectangle_set_radius(CC_ROUNDED_RECTANGLE(rrect), 20.0);
	cc_item_append(root, rrect);

	text = cc_text_new(_("Drag the buttons to\nadjust the gradient"));
	cc_text_set_anchor_type(CC_TEXT(text), GTK_ANCHOR_SOUTH);
	brush = cc_linear_gradient_new(0.5, 0.0, 0.5, 1.0);
	cc_gradient_add_stop(CC_GRADIENT(brush), 0.0, cc_color_new_rgb(1.0, 1.0, 1.0));
	cc_gradient_add_stop(CC_GRADIENT(brush), 1.0, cc_color_new_rgb(0.8, 0.8, 0.8));
	cc_shape_set_brush_content(CC_SHAPE(text), brush);
	cc_item_append(root, text);

	rect.x1 = 0.5;
	rect.y1 = 0.0;
	rect.x2 = 0.5;
	rect.y2 = 1.0;

	brush = cc_radial_gradient_new(0.5, 0.5, 0.5);
	cc_gradient_add_stop(CC_GRADIENT(brush), 0.4, cc_color_new_rgb(0.36, 0.21, 0.40));
	cc_gradient_add_stop(CC_GRADIENT(brush), 1.0, cc_color_new_rgb(0.0, 0.0, 0.0));
	knobs[0] = cc_circle_new();
	cc_circle_set_radius(CC_CIRCLE(knobs[0]), 5.0);
	cc_shape_set_brush_content(CC_SHAPE(knobs[0]), brush);
	g_signal_connect(knobs[0], "button-press-event",
			 G_CALLBACK(knob_button_press_event), NULL);
	g_signal_connect(knobs[0], "button-release-event",
			 G_CALLBACK(knob_button_release_event), NULL);
	g_signal_connect(knobs[0], "motion-notify-event",
			 G_CALLBACK(knob_motion_notify_event), NULL);
	cc_item_append(root, knobs[0]);

	knobs[2] = cc_circle_new();
	cc_circle_set_radius(CC_CIRCLE(knobs[2]), 5.0);
	cc_shape_set_brush_content(CC_SHAPE(knobs[2]), brush);
	g_signal_connect(knobs[2], "button-press-event",
			 G_CALLBACK(knob_button_press_event), NULL);
	g_signal_connect(knobs[2], "button-release-event",
			 G_CALLBACK(knob_button_release_event), NULL);
	g_signal_connect(knobs[2], "motion-notify-event",
			 G_CALLBACK(knob_motion_notify_event), NULL);
	cc_item_append(root, knobs[2]);

	knobs[1] = cc_circle_new();
	cc_circle_set_radius(CC_CIRCLE(knobs[1]), 5.0);
	cc_shape_set_brush_content(CC_SHAPE(knobs[1]), brush);
	g_signal_connect(knobs[1], "button-press-event",
			 G_CALLBACK(knob_button_press_event), NULL);
	g_signal_connect(knobs[1], "button-release-event",
			 G_CALLBACK(knob_button_release_event), NULL);
	g_signal_connect(knobs[1], "motion-notify-event",
			 G_CALLBACK(knob_motion_notify_event), NULL);
	cc_item_append(root, knobs[1]);

	widget = cc_view_widget_new_root(root);
	g_signal_connect_after(widget, "size-allocate",
			       G_CALLBACK(view_size_allocate), NULL);
	return demo_page_new(widget, _("Gradient Editor"));
}

