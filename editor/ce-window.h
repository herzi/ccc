/* This file is part of libccc
 *
 * AUTHORS
 *     Sven Herzberg  <herzi@gnome-de.org>
 *
 * Copyright (C) 2006  Sven Herzberg <herzi@gnome-de.org>
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

#ifndef CE_WINDOW_H
#define CE_WINDOW_H

#include "herzi-main-window.h"
#include "ce-canvas-tree-model.h"

G_BEGIN_DECLS

typedef struct _CEWindow      CEWindow;
typedef struct _CEWindowClass CEWindowClass;

#define CE_TYPE_WINDOW         (ce_window_get_type())
#define CE_WINDOW(i)           (G_TYPE_CHECK_INSTANCE_CAST((i), CE_TYPE_WINDOW, CEWindow))
#define CE_WINDOW_CLASS(c)     (G_TYPE_CHECK_CLASS_CAST((c), CE_TYPE_WINDOW, CEWindowClass))
#define CE_IS_WINDOW(i)        (G_TYPE_CHECK_INSTANCE_TYPE((i), CE_TYPE_WINDOW))
#define CE_IS_WINDOW_CLASS(c)  (G_TYPE_CHECK_CLASS_TYPE((c), CE_TYPE_WINDOW))
#define CE_WINDOW_GET_CLASS(i) (G>_TYPE_INSTANCE_GET_CLASS((i), CE_TYPE_WINDOW, CEWindowClass))

GType ce_window_get_type(void);

GtkWidget* ce_window_new(void);

struct _CEWindow {
	HerziMainWindow base_instance;

	GtkWidget* canvas_view;
	GtkWidget* sidebar;
	GtkWidget* item_tree;

	GtkTreeModel* canvas_tree;
};

struct _CEWindowClass {
	HerziMainWindowClass base_class;
};

G_END_DECLS

#endif /* !CE_WINDOW_H */
