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

#include "cc-test-view.h"

#include <ccc/cc-item-view.h>

CcView*
cc_test_view_new(void)
{
	return g_object_new(CC_TYPE_TEST_VIEW, NULL);
}

/* GType */
static void test_view_init_item_view(CcItemViewIface* iface);
static void test_view_init_view     (CcViewIface    * iface);
G_DEFINE_TYPE_WITH_CODE(CcTestView, cc_test_view, G_TYPE_OBJECT,
			G_IMPLEMENT_INTERFACE(CC_TYPE_ITEM_VIEW, test_view_init_item_view);
			G_IMPLEMENT_INTERFACE(CC_TYPE_VIEW, test_view_init_view));

enum {
	PROP_0,
	PROP_FOCUS,
	PROP_ROOT,
	PROP_SCROLLED_REGION,
	PROP_ZOOM,
	PROP_ZOOM_MODE
};

static void
cc_test_view_init(CcTestView* self G_GNUC_UNUSED)
{}

static void
cc_test_view_class_init(CcTestViewClass* self_class)
{
	GObjectClass* object_class = G_OBJECT_CLASS(self_class);

	/* CcViewIface */
	_cc_view_install_property(object_class, PROP_ROOT,
				  PROP_SCROLLED_REGION, PROP_ZOOM,
				  PROP_ZOOM_MODE, PROP_FOCUS);
}

/* CcViewIface */
static void
test_view_init_item_view(CcItemViewIface* iface G_GNUC_UNUSED)
{}

/* CcViewIface */
static void
test_view_init_view(CcViewIface* iface G_GNUC_UNUSED)
{}

