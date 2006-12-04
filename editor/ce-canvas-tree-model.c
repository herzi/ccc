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

#include "ce-canvas-tree-model.h"

#include <ccc/cc-item-view.h>

static GType column_types[CE_CANVAS_TREE_MODEL_N_COLUMNS] = {0};

GtkTreeModel*
ce_canvas_tree_model_new(void) {
	return g_object_new(CE_TYPE_CANVAS_TREE_MODEL, NULL);
}

void
ce_canvas_tree_model_set_root(GtkTreeModel* model, CcItem* root) {
	CECanvasTreeModel* self = NULL;
	GtkTreePath* path = NULL;
/*	GtkTreeIter iter;*/

	g_return_if_fail(CE_IS_CANVAS_TREE_MODEL(model));
	g_return_if_fail(CC_IS_ITEM(root));

	self = CE_CANVAS_TREE_MODEL(model);

	if(self->root == root) {
		return;
	}

	if(self->root) {
/*		path = gtk_tree_path_new();
		gtk_tree_path_append_index(path, 0);
		gtk_tree_model_row_deleted(model, path);*/
		cc_item_view_unregister(CC_ITEM_VIEW(self), self->root);
		g_object_unref(self->root);
		self->root = NULL;
		gtk_tree_path_free(path);
		path = NULL;
	}

	self->root = g_object_ref_sink(root);
	cc_item_view_register(CC_ITEM_VIEW(self), self->root);

/*	path = gtk_tree_path_new();
	gtk_tree_path_append_index(path, 0);
	gtk_tree_model_get_iter(model, &iter, path);
	gtk_tree_model_row_inserted(model, path, &iter);
	gtk_tree_path_free(path);*/

	// FIXME: enable this one
	//g_object_notify(G_OBJECT(self), "root");
}

/* GType */
static void cctm_init_tree_model(GtkTreeModelIface* iface);
static void cctm_init_item_view (CcItemViewIface* iface);
G_DEFINE_TYPE_WITH_CODE(CECanvasTreeModel, ce_canvas_tree_model, G_TYPE_OBJECT,
			G_IMPLEMENT_INTERFACE(CC_TYPE_ITEM_VIEW,   cctm_init_item_view);
			G_IMPLEMENT_INTERFACE(GTK_TYPE_TREE_MODEL, cctm_init_tree_model));

static void
ce_canvas_tree_model_init(CECanvasTreeModel* self) {}

static void
ce_canvas_tree_model_class_init(CECanvasTreeModelClass* self_class) {
	column_types[CE_CANVAS_TREE_MODEL_COL_NAME] = G_TYPE_STRING;
}

/* GtkTreeModelIface */
static gint
cctm_get_n_columns(GtkTreeModel* model) {
	return CE_CANVAS_TREE_MODEL_N_COLUMNS;
}

static GType
cctm_get_column_type(GtkTreeModel* model, gint index) {
	g_return_val_if_fail(0 <= index && index < CE_CANVAS_TREE_MODEL_N_COLUMNS, G_TYPE_INVALID);

	return column_types[index];
}

static gboolean
cctm_get_iter(GtkTreeModel* model, GtkTreeIter* iter, GtkTreePath* path) {
	CECanvasTreeModel* self = CE_CANVAS_TREE_MODEL(model);
	g_return_val_if_fail(iter, FALSE);

	iter->user_data = NULL;
	if(gtk_tree_path_get_depth(path) == 1 && gtk_tree_path_get_indices(path)[0] == 0) {
		// FIXME: set iter's stamp
		iter->user_data = self->root;
	} else {
		gchar* string = gtk_tree_path_to_string(path);
		g_print("%s\n", string);
		g_free(string);
		// FIXME: implement this one
	}
	return iter->user_data != NULL; // FIXME: check stamp too
}

static void
cctm_get_value(GtkTreeModel* model, GtkTreeIter* iter, gint index, GValue* value) {
	CcItem* item = NULL;

	g_return_if_fail(0 <= index && index < CE_CANVAS_TREE_MODEL_N_COLUMNS);
	// FIXME: check stamp

	item = CC_ITEM(iter->user_data);

	g_value_init(value, cctm_get_column_type(model, index));

	switch(index) {
	case CE_CANVAS_TREE_MODEL_COL_NAME:
		g_value_set_string(value, G_OBJECT_TYPE_NAME(item));
		break;
	}
}

static gboolean
cctm_iter_next() {
	return FALSE;
}

static gboolean
cctm_iter_nth_child() {
	return FALSE;
}

static void
cctm_init_tree_model(GtkTreeModelIface* iface) {
	// FIXME: implement get_flags
	iface->get_n_columns   = cctm_get_n_columns;
	iface->get_column_type = cctm_get_column_type;
	iface->get_iter        = cctm_get_iter;
	// FIXME: implement get_path
	iface->get_value       = cctm_get_value;
	iface->iter_next       = cctm_iter_next;
	// FIXME: implement iter_children
	// FIXME: implement iter_has_child
	// FIXME: implement iter_n_children
	iface->iter_nth_child  = cctm_iter_nth_child;
	// FIXME: implement iter_parent
	// FIXME: implement ref_node
	// FIXME: implement unref_node
}

/* CcItemViewIface */
static void
cctm_item_added(CcItemView* view, CcItem* item, gint position, CcItem* child) {
	CECanvasTreeModel* self = CE_CANVAS_TREE_MODEL(view);
	//GtkTreePath* path = cctm_get_path_from_item(self, item);
}

static void
cctm_item_removed(CcItemView* view, CcItem* item, gint position, CcItem* child) {
}

static void
cctm_init_item_view(CcItemViewIface* iface) {
	iface->item_added   = cctm_item_added;
	iface->item_removed = cctm_item_removed;
}

