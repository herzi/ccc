/* This file is part of libccc
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

#include "s-text.h"

#include <gdk/gdkkeysyms.h>
#include <gtk/gtkmain.h>
#include <gtk/gtkwindow.h>
#include <ccc/cc-text.h>
#include <ccc/cc-view-widget.h>

#include "gtk-helpers.h"

static void
check_cursor(CcText* text, gint expected_position, gint expected_trail)
{
	fail_unless(text->cursor == expected_position);
	fail_unless(text->cursor_trail == expected_trail);
}

START_TEST(test_cursor_navigation)
{
	GtkWidget* win;
	CcText* text;
	CcView* view;
	guint i = 0;
	gint positions[][2] = {
		{0,0}, {1,0}, {2,0}, {4,0}, {5,0}, {5,1}, {5,1}
	};
	gint positions_back[][2] = {
		{5,0}, {4,0}, {2,0}, {1,0}, {0,0}, {0,0}
	};
	GdkEventKey key = {
		GDK_KEY_PRESS,
		NULL,
		TRUE,
		GDK_CURRENT_TIME,
		0,
		GDK_Right,
		0,
		NULL,
		0, 0,
		FALSE
	};
	gboolean retval = FALSE;
	gtk_init(NULL, NULL);
	text = CC_TEXT(cc_text_new("Zwölf"));
	view = CC_VIEW(cc_view_widget_new_root(CC_ITEM(text)));
	win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_container_add(GTK_CONTAINER(win), GTK_WIDGET(view));
	gtk_widget_show_all(win);
	gtk_main_flush();
	key.window = GTK_WIDGET(view)->window;
	check_cursor(text, positions[i][0], positions[i][1]);
	for(i = 1; i < G_N_ELEMENTS(positions); i++) {
		g_signal_emit_by_name(text, "event", view, &key, &retval);
		check_cursor(text, positions[i][0], positions[i][1]);
	}
	key.keyval = GDK_Left;
	for(i = 0; i < G_N_ELEMENTS(positions_back); i++) {
		g_signal_emit_by_name(text, "event", view, &key, &retval);
		check_cursor(text, positions_back[i][0], positions_back[i][1]);
	}
	// move left, expect:  5,4,2,1,0,  0
	g_object_unref(text);
}
END_TEST

START_TEST(test_utf8_backspace)
{
	GdkEventKey key = {
		GDK_KEY_PRESS,
		NULL,
		TRUE,
		GDK_CURRENT_TIME,
		0,
		0,
		0,
		NULL,
		0, 0,
		FALSE
	};
	struct {
		guint        keyval;
		gchar const* expected;
	} iterations[] = {
		{GDK_Z, "Z"},
		{GDK_w, "Zw"},
		{GDK_odiaeresis, "Zwö"},
		{GDK_BackSpace, "Zw"},
		{GDK_a, "Zwa"},
		{GDK_n, "Zwan"},
		{GDK_z, "Zwanz"},
		{GDK_i, "Zwanzi"},
		{GDK_g, "Zwanzig"}
	};
	// FIXME: check cursor position
	// FIXME: check multiple backspace hits
	// FIXME: check backspace IN the string, not just at the end
#define implemented 0
	fail_unless(implemented);
#undef implemented
}
END_TEST

START_TEST(test_utf8_delete)
{
	// FIXME: check cursor position
	// FIXME: check mutiple delete presses
	// FIXME: check both in the beginning and IN the string
#define implemented 0
	fail_unless(implemented);
#undef implemented
}
END_TEST

TCase*
test_text_utf8_editing(void)
{
	TCase* self = tcase_create("UTF8 Editing");
	tcase_add_test(self, test_cursor_navigation);
	tcase_add_test(self, test_utf8_delete);
	tcase_add_test(self, test_utf8_backspace);
	return self;
}

