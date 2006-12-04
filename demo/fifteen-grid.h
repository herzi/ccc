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

#ifndef FIFTEEN_GRID_H
#define FIFTEEN_GRID_H

#include <ccc/cc-rectangle.h>

G_BEGIN_DECLS

typedef struct _FifteenGrid      FifteenGrid;
typedef struct _CcRectangleClass FifteenGridClass;

#define FIFTEEN_TYPE_GRID         (fifteen_grid_get_type())
#define FIFTEEN_GRID(i)           (G_TYPE_CHECK_INSTANCE_CAST((i), FIFTEEN_TYPE_GRID, FifteenGrid))
#define FIFTEEN_GRID_CLASS(c)     (G_TYPE_CHECK_CLASS_CAST((c), FIFTEEN_TYPE_GRID, FifteenGridClass))
#define FIFTEEN_IS_GRID(i)        (G_TYPE_CHECK_INSTANCE_TYPE((i), FIFTEEN_TYPE_GRID))
#define FIFTEEN_IS_GRID_CLASS(c)  (G_TYPE_CHECK_CLASS_TYPE((c), FIFTEEN_TYPE_GRID))
#define FIFTEEN_GRID_GET_CLASS(i) (G_TYPE_INSTANCE_GET_CLASS((i), FIFTEEN_TYPE_GRID, FifteenGridClass))

GType fifteen_grid_get_type(void);

CcItem* fifteen_grid_new     (PangoFontDescription* desc);
void    fifteen_grid_scramble(FifteenGrid* self);

struct _FifteenGrid {
	CcRectangle           base_instance;

	CcItem              * elements[16];
	PangoFontDescription* font_description;
};

G_END_DECLS

#endif /* !FIFTEEN_GRID_H */

