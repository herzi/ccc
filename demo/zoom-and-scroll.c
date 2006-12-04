/* this file is part of libccc, criawips' cairo-based canvas
 *
 * AUTHORS
 *       Sven Herzberg        <herzi@gnome-de.org>
 *
 * Copyright (C) 2005,2006 Sven Herzberg
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

#include "zoom-and-scroll.h"

#include <gtk/gtk.h>
#include <ccc.h>

#include "demo-canvas.h"
#include "herzi-enum-combo.h"

static void
spinbutton_update_zoom(GtkSpinButton* spin, CcView* view) {
	g_return_if_fail(GTK_IS_SPIN_BUTTON(spin));
	g_return_if_fail(CC_IS_VIEW(view));

	cc_view_set_zoom(view, gtk_spin_button_get_value(spin));
}

static void
update_center_view(CcViewWidget* view, GtkToggleButton* toggle) {
	g_return_if_fail(CC_IS_VIEW_WIDGET(view));
	g_return_if_fail(GTK_IS_TOGGLE_BUTTON(toggle));

	cc_view_widget_set_center_view(view, gtk_toggle_button_get_active(toggle));
}

static void
update_zoom_mode(CcViewWidget* view, HerziEnumCombo* combo) {
	g_object_set(view, "zoom-mode", herzi_enum_combo_get_value(combo), NULL);
}

static void
update_scrolled_region(CcView* view, GtkToggleButton* toggle) {
	CcDRect rect = {100.0, 100.0, 300.0, 300.0};

	cc_view_set_scrolled_region(view, gtk_toggle_button_get_active(toggle) ? &rect : NULL);
}

DemoPage*
zoom_and_scroll(void) {
	DemoPage * page = g_object_new(DEMO_TYPE_PAGE, NULL);
	GtkWidget* widget_one,
		 * widget_two;

	page->title = "Zoom and Scroll";
	page->widget = gtk_table_new(2, 3, FALSE);
	widget_two = gtk_label_new(NULL);
	gtk_label_set_markup_with_mnemonic(GTK_LABEL(widget_two), "<span weight='bold'>_Zoom</span>");
	gtk_misc_set_alignment(GTK_MISC(widget_two), 0.0, 0.5);
	gtk_misc_set_padding(GTK_MISC(widget_two), 6, 0);
	gtk_table_attach(GTK_TABLE(page->widget), widget_two,
			 0,1, 0,1,
			 GTK_EXPAND | GTK_FILL, GTK_FILL,
			 0,0);
	widget_one = gtk_spin_button_new_with_range(0.01, G_MAXDOUBLE, 0.01);
	gtk_label_set_mnemonic_widget(GTK_LABEL(widget_two), widget_one);
	widget_two = NULL;
	widget_two = cc_view_widget_new_root(demo_canvas_create());
	g_signal_connect(widget_one, "value-changed",
			 G_CALLBACK(spinbutton_update_zoom), widget_two);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget_one), 1.0);
	gtk_table_attach(GTK_TABLE(page->widget), widget_one,
			 1,2, 0,1,
			 GTK_FILL, GTK_FILL,
			 0,0);
	widget_one = NULL;

	widget_one = gtk_label_new(NULL);
	gtk_label_set_markup_with_mnemonic(GTK_LABEL(widget_one), "<span weight='bold'>Zoom-_Mode</span>");
	gtk_misc_set_alignment(GTK_MISC(widget_one), 0.0, 0.5);
	gtk_misc_set_padding(GTK_MISC(widget_one), 6, 0);
	gtk_table_attach(GTK_TABLE(page->widget), widget_one,
			 0,1, 1,2,
			 GTK_EXPAND | GTK_FILL, GTK_FILL,
			 0,0);
	widget_one = herzi_enum_combo_new(CC_TYPE_ZOOM_MODE);
	g_signal_connect_swapped(widget_one, "changed",
				 G_CALLBACK(update_zoom_mode), widget_two);
	gtk_table_attach(GTK_TABLE(page->widget), widget_one,
			 1,2, 1,2,
			 GTK_EXPAND | GTK_FILL, GTK_FILL,
			 0,0);

	widget_one = gtk_check_button_new_with_mnemonic("_Center View");
	g_signal_connect_swapped(widget_one, "toggled",
				 G_CALLBACK(update_center_view), widget_two);
	update_center_view(CC_VIEW_WIDGET(widget_two), GTK_TOGGLE_BUTTON(widget_one));
	gtk_table_attach(GTK_TABLE(page->widget), widget_one,
			 0,2, 2,3,
			 GTK_EXPAND | GTK_FILL, GTK_FILL,
			 0,0);
	widget_one = NULL;
	widget_one = gtk_check_button_new_with_mnemonic("_Set Scrolled region to (100,100)=>(300,300)");
	g_signal_connect_swapped(widget_one, "toggled",
				 G_CALLBACK(update_scrolled_region), widget_two);
	update_scrolled_region(CC_VIEW(widget_two), GTK_TOGGLE_BUTTON(widget_one));
	gtk_table_attach(GTK_TABLE(page->widget), widget_one,
			 0,2, 3,4,
			 GTK_EXPAND | GTK_FILL, GTK_FILL,
			 0,0);
	widget_one = NULL;
	widget_one = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(widget_one), GTK_SHADOW_IN);
	gtk_table_attach(GTK_TABLE(page->widget), widget_one,
			 0,2, 4,5,
			 GTK_EXPAND | GTK_FILL, GTK_EXPAND | GTK_FILL,
			 0,0);
	gtk_container_add(GTK_CONTAINER(widget_one), widget_two);
	widget_one = NULL;
	gtk_widget_show_all(page->widget);

	return page;
}

