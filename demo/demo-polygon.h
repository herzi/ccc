/* This file is part of libccc
 *
 * AUTHORS
 *     Sven Herzberg  <herzi@gnome-de.org>
 *
 * Copyright (C) 2006  Sven Herzberg
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

#ifndef DEMO_POLYGON_H
#define DEMO_POLYGON_H

#include <ccc/cc-shape.h>
#include <ccc/cc-brush-color.h>

G_BEGIN_DECLS

typedef CcShape      DemoPolygon;
typedef CcShapeClass DemoPolygonClass;

#define DEMO_TYPE_POLYGON         (demo_polygon_get_type())

GType   demo_polygon_get_type(void);
CcItem* demo_polygon_new     (gint i);

G_END_DECLS

#endif /* !DEMO_POLYGON_H */
