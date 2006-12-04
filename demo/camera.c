/* This file is part of CCC, a cairo-based canvas
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

#include <gtk/gtkscrolledwindow.h>
#include <ccc/cc-camera.h>
#include <ccc/cc-view-widget.h>
#include "demo-canvas.h"

#ifdef HAVE_CONFIG_H
# include <cc-config.h>
#endif
#include <glib/gi18n-lib.h>

/* Camera Demo
 *
 * This demo is supposed to create a very nice demonstration of the camera
 * possibilities.
 *
 * Desired end result:
 * -------------------
 * We want to display a canvas (either the current demo canvas or a fancy large
 * graph). The general idea is to have this canvas larger than the scrollable
 * area. Then we want to have some kind of "overview area" (in the corner) that
 * displays the whole canvas together with a nice rectangle visualizing the
 * currently visible area.
 *
 * This rectangle could also be draggable to adjust the currently visible area.
 *
 * (Extra bonus: render the visible area a bit more opaque than the rest)
 * (Extra bonus 2: render a shadow for the preview)
 */

static CcItem*
camera_canvas_new(void)
{
	CcItem* canvas = cc_item_new();
	CcItem* demo   = demo_canvas_create();
	CcItem* camera = cc_camera_new_root(demo);
	cc_item_append(canvas, demo);
	cc_item_append(canvas, camera);
	return canvas;
}

DemoPage*
camera_demo(void)
{
	GtkWidget* swin   = gtk_scrolled_window_new(NULL, NULL);
	GtkWidget* widget = cc_view_widget_new_root(camera_canvas_new());
	gtk_container_add(GTK_CONTAINER(swin), widget);
	return demo_page_new(swin, _("Cameras"));
}

