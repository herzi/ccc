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

#ifndef FIFTEEN_ITEM_H
#define FIFTEEN_ITEM_H

#include <ccc/cc-rectangle.h>

G_BEGIN_DECLS

typedef struct _FifteenItem      FifteenItem;
typedef struct _CcRectangleClass FifteenItemClass;

#define FIFTEEN_TYPE_ITEM         (fifteen_item_get_type())
#define FIFTEEN_ITEM(i)           (G_TYPE_CHECK_INSTANCE_CAST((i), FIFTEEN_TYPE_ITEM, FifteenItem))
#define FIFTEEN_ITEM_CLASS(c)     (G_TYPE_CHECK_CLASS_CAST((c), FIFTEEN_TYPE_ITEM, FifteenItemClass))
#define FIFTEEN_IS_ITEM(i)        (G_TYPE_CHECK_INSTANCE_TYPE((i), FIFTEEN_TYPE_ITEM))
#define FIFTEEN_IS_ITEM_CLASS(c)  (G_TYPE_CHECK_CLASS_TYPE((c), FIFTEEN_TYPE_ITEM))
#define FIFTEEN_ITEM_GET_CLASS(i) (G_TYPE_INSTANCE_GET_CLASS((i), FIFTEEN_TYPE_ITEM, FifteenItemClass))

GType fifteen_item_get_type(void);

CcItem* fifteen_item_new (guint        index);
void    fifteen_item_move(FifteenItem* self,
			  guint        position,
			  gdouble      edge);

struct _FifteenItem {
	CcRectangle  base_instance;
	guint        index;
	CcItem     * text;
};

G_END_DECLS

#endif /* !FIFTEEN_ITEM_H */

