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

#include "cc-gradient.h"

CcBrush*
cc_gradient_new(void)
{
	return g_object_new(CC_TYPE_GRADIENT, NULL);
}

/* GType */
G_DEFINE_TYPE(CcGradient, cc_gradient, CC_TYPE_BRUSH);

static void
cc_gradient_init(CcGradient* self G_GNUC_UNUSED)
{}

static void
cc_gradient_class_init(CcGradientClass* self_class G_GNUC_UNUSED)
{}

