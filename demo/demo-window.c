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

#include "demo-window.h"

#include <gtk/gtkcellrenderertext.h>
#include <gtk/gtkhpaned.h>
#include <gtk/gtklabel.h>
#include <gtk/gtkliststore.h>
#include <gtk/gtknotebook.h>
#include <gtk/gtkscrolledwindow.h>
#include <gtk/gtktreemodelsort.h>
#include <gtk/gtktreeselection.h>
#include <gtk/gtktreeview.h>

#include <ccc/glib-helpers.h>

#ifdef HAVE_CONFIG_H
# include <cc-config.h>
#endif
#include <glib/gi18n-lib.h>

enum {
	COL_TEXT,
	COL_PAGE,
	N_COLUMNS
};

G_DEFINE_TYPE(DemoWindow, demo_window, GTK_TYPE_WINDOW);

GtkWidget*
demo_window_new(void) {
	return g_object_new(DEMO_TYPE_WINDOW,
			    "type", GTK_WINDOW_TOPLEVEL,
			    "title", "libccc demonstration",
			    NULL);
}

void
demo_window_add(DemoWindow* self, DemoPage* page) {
	GtkTreeIter iter;
	g_return_if_fail(DEMO_IS_PAGE(page));
	g_return_if_fail(GTK_IS_WIDGET(page->widget));

#ifndef G_DISABLE_CHECKS
	if(G_UNLIKELY(!page->title)) {
		page->title = _("Untitled Page");
	}
#endif
	self->pages = g_list_prepend(self->pages, page);
	gint insert_id = gtk_notebook_append_page(GTK_NOTEBOOK(self->notebook),
						  page->widget, gtk_label_new(page->title));
	gtk_list_store_append(GTK_LIST_STORE(self->treemodel), &iter);
	gtk_list_store_set(GTK_LIST_STORE(self->treemodel), &iter,
			   COL_TEXT, page->title,
			   COL_PAGE, insert_id,
			   -1);
}

/* GType stuff */
static void
tree_selection_changed(GtkTreeSelection* selection, DemoWindow* self) {
	GtkTreeModel* model;
	GtkTreeIter   iter;
	if(gtk_tree_selection_get_selected(selection, &model, &iter)) {
		gint page;
		gtk_tree_model_get(model, &iter, COL_PAGE, &page, -1);
		gtk_notebook_set_current_page(GTK_NOTEBOOK(self->notebook), page);
	}
}

static void
demo_window_init(DemoWindow* self) {
	GtkWidget* paned = gtk_hpaned_new();
	GtkWidget* swin  = gtk_scrolled_window_new(NULL, NULL);
	GtkTreeModel* model;

	gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(swin), GTK_SHADOW_IN);

	self->treemodel = GTK_TREE_MODEL(gtk_list_store_new(N_COLUMNS, G_TYPE_STRING, G_TYPE_INT));
	model = gtk_tree_model_sort_new_with_model(self->treemodel);
	gtk_tree_sortable_set_sort_column_id(GTK_TREE_SORTABLE(model), COL_TEXT, GTK_SORT_ASCENDING);
	self->treeview = gtk_tree_view_new_with_model(model);
	gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(self->treeview), -1,
						    "Feature", gtk_cell_renderer_text_new(),
						    "text", COL_TEXT,
						    NULL);
	gtk_widget_show(self->treeview);
	gtk_container_add(GTK_CONTAINER(swin), self->treeview);
	gtk_paned_pack1(GTK_PANED(paned), swin, FALSE, FALSE);

	self->notebook = gtk_notebook_new();
	gtk_notebook_set_show_tabs(GTK_NOTEBOOK(self->notebook), FALSE);
	gtk_widget_show(self->notebook);
	gtk_paned_pack2(GTK_PANED(paned), self->notebook, TRUE, FALSE);

	g_signal_connect(gtk_tree_view_get_selection(GTK_TREE_VIEW(self->treeview)), "changed",
			 G_CALLBACK(tree_selection_changed), self);

	gtk_widget_show(paned);
	gtk_container_add(GTK_CONTAINER(self), paned);

	//gtk_window_set_default_size(GTK_WINDOW(self), 300, 200);
}

static void
dw_dispose(GObject* object) {
	DemoWindow* self = DEMO_WINDOW(object);

	if(self->disposed) {
		return;
	}
	self->disposed = TRUE;

	if(self->treemodel) {
		g_object_unref(self->treemodel);
		self->treemodel = NULL;
	}

	G_OBJECT_CLASS(demo_window_parent_class)->dispose(object);
}

static void
dw_finalize(GObject* object) {
	DemoWindow* self = DEMO_WINDOW(object);

	g_list_free(self->pages);
	self->pages = NULL;

	G_OBJECT_CLASS(demo_window_parent_class)->finalize(object);
}

static void
demo_window_class_init(DemoWindowClass* self_class) {
	GObjectClass* go_class;
	go_class = G_OBJECT_CLASS(self_class);
	go_class->dispose  = dw_dispose;
	go_class->finalize = dw_finalize;
}

