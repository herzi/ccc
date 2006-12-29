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

struct CcTestViewPrivate {
	CcItem * root;
	gdouble  zoom;
};
#define P(i) (G_TYPE_INSTANCE_GET_PRIVATE((i), CC_TYPE_TEST_VIEW, struct CcTestViewPrivate))

CcView*
cc_test_view_new(void)
{
	return g_object_new(CC_TYPE_TEST_VIEW, NULL);
}

gboolean
cc_test_view_motion_notify(CcTestView* self,
			   gdouble     x,
			   gdouble     y)
{
	gboolean retval = FALSE;
	g_warning("FIXME: implement cc_test_view_motion_notify()");
	return retval;
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
test_view_dispose(GObject* object)
{
	if(P(object)->root) {
		cc_view_set_root(CC_VIEW(object), NULL);
	}

	G_OBJECT_CLASS(cc_test_view_parent_class)->dispose(object);
}

static void
test_view_get_property(GObject   * object,
		       guint       prop_id,
		       GValue    * value,
		       GParamSpec* pspec)
{
	switch(prop_id) {
	case PROP_FOCUS:
#warning "FIXME: implement focus property"
		g_warning("FIXME: implement focus for CcTestView");
		break;
	case PROP_ROOT:
		g_value_set_object(value, P(object)->root);
		break;
	case PROP_SCROLLED_REGION:
#warning "FIXME: implement scrolled region property"
		g_warning("FIXME: implement scrolled region for CcTestView");
		break;
	case PROP_ZOOM:
		g_value_set_double(value, P(object)->zoom);
		break;
	case PROP_ZOOM_MODE:
#warning "FIXME: implement zoom mode property"
		g_warning("FIXME: implement zoom mode for CcTestView");
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
		break;
	}
}

static void
test_view_set_root(CcTestView* self,
		   CcItem    * root)
{
	g_return_if_fail(CC_IS_TEST_VIEW(self));
	g_return_if_fail(!root || CC_IS_ITEM(root));

	if(P(self)->root == root) {
		return;
	}

	if(P(self)->root) {
		g_object_unref(P(self)->root);
		P(self)->root = NULL;
	}

	if(root) {
		P(self)->root = g_object_ref(root);
	}

	g_object_notify(G_OBJECT(self), "root");
}

static void
test_view_set_property(GObject     * object,
		       guint         prop_id,
		       GValue const* value,
		       GParamSpec  * pspec)
{
	switch(prop_id) {
	case PROP_FOCUS:
#warning "FIXME: implement focus property"
		g_warning("FIXME: implement focus for CcTestView");
		break;
	case PROP_ROOT:
		test_view_set_root(CC_TEST_VIEW(object), g_value_get_object(value));
		break;
	case PROP_SCROLLED_REGION:
#warning "FIXME: implement scrolled region property"
		g_warning("FIXME: implement scrolled region for CcTestView");
		break;
	case PROP_ZOOM:
		P(object)->zoom = g_value_get_double(value);
		g_object_notify(object, "zoom");
		break;
	case PROP_ZOOM_MODE:
#warning "FIXME: implement zoom mode property"
		g_warning("FIXME: implement zoom mode for CcTestView");
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
		break;
	}
}

static void
cc_test_view_class_init(CcTestViewClass* self_class)
{
	GObjectClass* object_class = G_OBJECT_CLASS(self_class);

	object_class->dispose      = test_view_dispose;
	object_class->get_property = test_view_get_property;
	object_class->set_property = test_view_set_property;

	/* CcTestViewClass */
	g_type_class_add_private(self_class, sizeof(struct CcTestViewPrivate));

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

