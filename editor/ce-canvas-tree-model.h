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

#ifndef CE_CANVAS_TREE_MODEL_H
#define CE_CANVAS_TREE_MODEL_H

#include <gtk/gtktreemodel.h>
#include <ccc/cc-item.h>

G_BEGIN_DECLS

typedef struct _CECanvasTreeModel      CECanvasTreeModel;
typedef struct _CECanvasTreeModelClass CECanvasTreeModelClass;

#define CE_TYPE_CANVAS_TREE_MODEL         (ce_canvas_tree_model_get_type())
#define CE_CANVAS_TREE_MODEL(i)           (G_TYPE_CHECK_INSTANCE_CAST((i), CE_TYPE_CANVAS_TREE_MODEL, CECanvasTreeModel))
#define CE_CANVAS_TREE_MODEL_CLASS(c)     (G_TYPE_CHECK_CLASS_CAST((c), CE_TYPE_CANVAS_TREE_MODEL, CECanvasTreeModelClass))
#define CE_IS_CANVAS_TREE_MODEL(i)        (G_TYPE_CHECK_INSTANCE_TYPE((i), CE_TYPE_CANVAS_TREE_MODEL))
#define CE_IS_CANVAS_TREE_MODEL_CLASS(c)  (G_TYPE_CHECK_CLASS_TYPE((c), CE_TYPE_CANVAS_TREE_MODEL))
#define CE_CANVAS_TREE_MODEL_GET_CLASS(i) (G_TYPE_INSTANCE_GET_CLASS((i), CE_TYPE_CANVAS_TREE_MODEL, CECanvasTreeModelClass))

enum {
	CE_CANVAS_TREE_MODEL_COL_NAME,
	CE_CANVAS_TREE_MODEL_N_COLUMNS
};

GType         ce_canvas_tree_model_get_type(void);
GtkTreeModel* ce_canvas_tree_model_new     (void);
void          ce_canvas_tree_model_set_root(GtkTreeModel* model,
					    CcItem      * root);

struct _CECanvasTreeModel {
	GObject base_instance;

	CcItem* root;
};

struct _CECanvasTreeModelClass {
	GObjectClass base_class;
};

G_END_DECLS

#endif /* !CE_CANVAS_TREE_MODEL_H */
