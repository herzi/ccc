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

#include "fifteen-item.h"

#include <ccc.h>

G_DEFINE_TYPE(FifteenItem, fifteen_item, CC_TYPE_RECTANGLE);

CcItem*
fifteen_item_new(guint index) {
	CcItem * retval = g_object_new(FIFTEEN_TYPE_ITEM, NULL);
	CcColor* color  = cc_color_new_hsva(1.0 * index / 15, 0.75, 1.0, 0.5);
	CcBrush* brush  = cc_brush_color_new(color);
	cc_shape_set_brush_content(CC_SHAPE(retval), brush);
	// make this a GObject property later
	FIFTEEN_ITEM(retval)->index = index;

	gchar* text = g_strdup_printf("%d", index + 1);
	FIFTEEN_ITEM(retval)->text = cc_text_new(text);
	cc_text_set_anchor_type(CC_TEXT(FIFTEEN_ITEM(retval)->text), GTK_ANCHOR_CENTER);
	cc_item_append(retval, FIFTEEN_ITEM(retval)->text);
	g_free(text);
	text = NULL;

	return retval;
}

void
fifteen_item_move(FifteenItem* self, guint position, gdouble edge) {
	cc_rectangle_set_position(CC_RECTANGLE(self),
				  (position%4)*edge, (position/4)*edge, edge, edge);
	cc_text_set_anchor(CC_TEXT(self->text), (position%4 + 0.5)*edge, (position/4 + 0.5)*edge);
}

/* GType stuff */
static void
fifteen_item_init(FifteenItem* self) {
	CC_ITEM_SET_FLAGS(self, CC_CAN_FOCUS);
}

static gboolean
fi_focus_enter(CcItem       * self,
	       CcView       * view,
	       GdkEventFocus* ev G_GNUC_UNUSED)
{
	g_message("Focus on '%s'", pango_layout_get_text(CC_TEXT(FIFTEEN_ITEM(self)->text)->layout));
	return FALSE;
}

static gboolean
fi_focus_leave(CcItem       * self,
	       CcView       * view,
	       GdkEventFocus* ev G_GNUC_UNUSED)
{
	g_message("Focus off '%s'", pango_layout_get_text(CC_TEXT(FIFTEEN_ITEM(self)->text)->layout));
	return FALSE;
}

static void
fifteen_item_class_init(FifteenItemClass* self_class) {
	CcItemClass* ci_class = CC_ITEM_CLASS(self_class);
	ci_class->focus_enter = fi_focus_enter;
	ci_class->focus_leave = fi_focus_leave;
}

