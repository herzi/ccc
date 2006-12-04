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

#ifndef DEMO_PAGE_H
#define DEMO_PAGE_H

#include <gtk/gtkwidget.h>

G_BEGIN_DECLS

typedef struct _DemoPage      DemoPage;
typedef struct _DemoPageClass DemoPageClass;

#define DEMO_TYPE_PAGE         (demo_page_get_type())
#define DEMO_PAGE(i)           (G_TYPE_CHECK_INSTANCE_CAST((i), DMEO_TYPE_PAGE, DemoPage))
#define DEMO_PAGE_CLASS(c)     (G_TYPE_CHECK_CLASS_CAST((c), DEMO_TYPE_PAGE, DemoPageClass))
#define DEMO_IS_PAGE(i)        (G_TYPE_CHECK_INSTANCE_TYPE((i), DEMO_TYPE_PAGE))
#define DEMO_IS_PAGE_CLASS(c)  (G_TYPE_CHECK_CLASS_TYPE((c), DEMO_TYPE_PAGE))
#define DEMO_PAGE_GET_CLASS(i) (G_TYPE_INSTANCE_GET_CLASS((i), DEMO_TYPE_PAGE, DemoPageClass))

GType demo_page_get_type(void);

DemoPage* demo_page_new(GtkWidget  * page,
			gchar const* text);

struct _DemoPage {
	GObject       base_instance;

	gchar       * title;
	GtkWidget   * widget;
};

struct _DemoPageClass {
	GObjectClass  base_class;
};

G_END_DECLS

#endif /* !DEMO_PAGE_H */

