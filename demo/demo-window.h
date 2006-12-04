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

#ifndef DEMO_WINDOW_H
#define DEMO_WINDOW_H

#include <gtk/gtktreemodel.h>
#include <gtk/gtkwindow.h>

#include "demo-page.h"

G_BEGIN_DECLS

typedef struct _DemoWindow      DemoWindow;
typedef struct _GtkWindowClass DemoWindowClass;

#define DEMO_TYPE_WINDOW         (demo_window_get_type())
#define DEMO_WINDOW(i)           (G_TYPE_CHECK_INSTANCE_CAST((i), DEMO_TYPE_WINDOW, DemoWindow))
#define DEMO_WINDOW_CLASS(c)     (G_TYPE_CHECK_CLASS_CAST((c), DEMO_TYPE_WINDOW, DemoWindowClass))
#define DEMO_IS_WINDOW(i)        (G_TYPE_CHECK_INSTANCE_TYPE((i), DEMO_TYPE_WINDOW))
#define DEMO_IS_WINDOW_CLASS(c)  (G_TYPE_CHECK_CLASS_TYPE((c), DEMO_TYPE_WINDOW))
#define DEMO_WINDOW_GET_CLASS(i) (G_TYPE_INSTANCE_GET_CLASS((i), DEMO_TYPE_WINDOW, DemoWindowClass))

GType demo_window_get_type(void);

GtkWidget* demo_window_new(void);
void       demo_window_add(DemoWindow* self, DemoPage* page);

struct _DemoWindow {
	GtkWindow    base_instance;
	gboolean     disposed;

	GtkWidget   * treeview;
	GtkTreeModel* treemodel;

	GtkWidget   * notebook;

	GList       * pages;
};

G_END_DECLS

#endif /* !DEMO_WINDOW_H */

