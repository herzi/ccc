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

#include <ccc/cc-rectangle.h>
#include "cc-test-view.h"

static gint implemented = FALSE;

START_TEST(test_item_crossing_single)
{
	CcView* view = cc_test_view_new();
	CcItem* root = cc_rectangle_new();
	cc_rectangle_set_position(CC_RECTANGLE(root),
				  0.0, 0.0, 100.0, 100.0);
	cc_view_set_root(view, root);
#warning "FIXME: finish"
	g_object_unref(view);
	fail_unless(implemented);
}
END_TEST

START_TEST(test_item_crossing_into)
{
	fail_unless(implemented);
}
END_TEST

START_TEST(test_item_crossing_into_jumping)
{
	fail_unless(implemented);
}
END_TEST

START_TEST(test_item_crossing_out)
{
	fail_unless(implemented);
}
END_TEST

START_TEST(test_item_crossing_out_jumping)
{
	fail_unless(implemented);
}
END_TEST

TCase*
test_item_crossing(void)
{
	TCase* self = tcase_create("Crossing Events");
	tcase_add_test(self, test_item_crossing_single);
	tcase_add_test(self, test_item_crossing_into);
	tcase_add_test(self, test_item_crossing_into_jumping);
	tcase_add_test(self, test_item_crossing_out);
	tcase_add_test(self, test_item_crossing_out_jumping);
	return self;
}

