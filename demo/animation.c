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

#include <ccc/cc-text.h>
#include <ccc/cc-view-widget.h>

#ifdef HAVE_CONFIG_H
# include <cc-config.h>
#endif
#include <glib/gi18n-lib.h>

static gint step = 0;

static gboolean
animate(gpointer data)
{
	CcText* text = data;
	gdouble pos = 100.0*(step > 100 ? 200 - step : step)/100-50.0;
	cc_text_set_anchor(text, pos, text->y);
	step = (step+1)%200;
	return TRUE;
}

DemoPage*
animation_demo(void)
{
	GtkWidget* view = cc_view_widget_new();
	CcItem   * root = cc_item_new();
	CcItem   * text = cc_text_new(PACKAGE " " VERSION);
	cc_view_set_root(CC_VIEW(view), root);
	cc_item_append(root, text);
	cc_text_set_anchor_type(CC_TEXT(text), GTK_ANCHOR_CENTER);
	cc_view_set_scrolled_region(CC_VIEW(view), cc_item_get_all_bounds(root, CC_VIEW(view)));
	g_timeout_add(30, animate, text);
	return demo_page_new(view, _("Animation"));
}

