/* This file is part of CCC
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

#ifndef CC_RADIAL_GRADIENT_H
#define CC_RADIAL_GRADIENT_H

#include <ccc/cc-gradient.h>

G_BEGIN_DECLS

typedef CcGradient      CcRadialGradient;
typedef CcGradientClass CcRadialGradientClass;

#define CC_TYPE_RADIAL_GRADIENT         (cc_radial_gradient_get_type())

GType    cc_radial_gradient_get_type(void);
CcBrush* cc_radial_gradient_new(gdouble x,
				gdouble y,
				gdouble rad);

G_END_DECLS

#endif /* !CC_RADIAL_GRADIENT_H */
