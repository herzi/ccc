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

#include "s-item.h"

#include "cc-test-view.h"
#include <ccc/cc-rectangle.h>

START_TEST(test_item_distance_empty)
{
	/* we want to get the maximum distance if the item doesn't have a
	 * bounding box */
	CcItem* root = cc_item_new();
	CcItem* hit = NULL;
	gdouble distance;
	distance = cc_item_distance(root, 0.0, 0.0, &hit);
	fail_unless(distance == G_MAXDOUBLE);
	fail_if(CC_IS_ITEM(hit));
}
END_TEST

START_TEST(test_item_distance_self)
{
	// we want to get a points that's definitely inside of an item
	CcItem* root = cc_rectangle_new();
	CcItem* hit = NULL;
	gdouble distance;
	cc_rectangle_set_position(CC_RECTANGLE(root),
				  0.0, 0.0,
				  100.0, 100.0);
	distance = cc_item_distance(root, 200.0, 0.0, &hit);
	fail_unless(distance > 0.0);
	fail_if(CC_IS_ITEM(hit));
	distance = cc_item_distance(root, 50.0, 50.0, &hit);
	fail_if(distance > 0.0);
	fail_unless(CC_IS_ITEM(hit) && hit == root);
}
END_TEST

START_TEST(test_item_distance_children)
{
	CcItem* root  = cc_rectangle_new();
	CcItem* child = cc_rectangle_new();
	CcItem* hit = NULL;
	gdouble distance;
	cc_rectangle_set_position(CC_RECTANGLE(root),
				  0.0, 0.0,
				  100.0, 100.0);
	cc_rectangle_set_position(CC_RECTANGLE(child),
				  0.0, 0.0,
				  100.0, 100.0);
	cc_item_append(root, child);
	distance = cc_item_distance(root, 200.0, 0.0, &hit);
	fail_unless(distance > 0.0);
	fail_if(hit);
	distance = cc_item_distance(root, 50.0, 50.0, &hit);
	fail_if(distance > 0.0);
	fail_unless(CC_IS_ITEM(hit) && hit == child);
}
END_TEST

START_TEST(test_item_distance_order)
{
	gdouble distance;
	CcItem* root   = cc_item_new();
	CcItem* child1 = cc_rectangle_new();
	CcItem* child2 = cc_rectangle_new();
	CcItem* hit = NULL;
	cc_rectangle_set_position(CC_RECTANGLE(child1),
				  0.0, 0.0,
				  100.0, 100.0);
	cc_rectangle_set_position(CC_RECTANGLE(child2),
				  0.0, 0.0,
				  100.0, 100.0);
	cc_item_append(root, child1);
	cc_item_append(root, child2);
	distance = cc_item_distance(root, 200.0, 0.0, &hit);
	fail_unless(distance > 0.0);
	fail_if(CC_IS_ITEM(hit));
	distance = cc_item_distance(root, 50.0, 50.0, &hit);
	fail_if(distance > 0.0);
	fail_unless(CC_IS_ITEM(hit) && hit == child2);
}
END_TEST

TCase*
test_item_distance(void)
{
#warning "FIXME: iterate through the types"
	TCase* self = tcase_create("Distance Function");
	tcase_add_test(self, test_item_distance_empty);
	tcase_add_test(self, test_item_distance_self);
	tcase_add_test(self, test_item_distance_children);
	tcase_add_test(self, test_item_distance_order);
	return self;
}

