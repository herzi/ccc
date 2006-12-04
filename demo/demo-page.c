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

#include "demo-page.h"

DemoPage*
demo_page_new(GtkWidget* w, gchar const* text) {
	DemoPage* page = g_object_new(DEMO_TYPE_PAGE, NULL);
	page->widget = w;
	page->title = text;
	return page;
}

/* GType stuff */
G_DEFINE_TYPE(DemoPage, demo_page, G_TYPE_OBJECT);

static void
demo_page_init(DemoPage* self) {}

static void
demo_page_class_init(DemoPageClass* self_class) {}

