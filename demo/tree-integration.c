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

#include "main.h"

#include <gtk/gtk.h>
#include <ccc.h>

#include "demo-polygon.h"

enum {
	COL_NUM,
	COL_TEXT,
	COL_POLYGON,
	COL_POLYGRAM,
	N_COLUMNS
};

DemoPage*
tree_integration(void) {
	GtkWidget   * tree;
	DemoPage    * page  = g_object_new(DEMO_TYPE_PAGE, NULL);
	GtkTreeModel* model;
	GtkTreeIter   iter;
	guint i;
	GtkTargetEntry targets[] = {
		{"text/plain", 0, 0}
	};

	page->title = "Tree Integration";
	page->widget = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(page->widget), GTK_SHADOW_IN);
	tree = gtk_tree_view_new();
	gtk_tree_view_enable_model_drag_source(GTK_TREE_VIEW(tree), 0,
					       targets, G_N_ELEMENTS(targets),
					       GDK_ACTION_COPY);
	// FIXME: add drag source at some point
	gtk_container_add(GTK_CONTAINER(page->widget), tree);

	model = GTK_TREE_MODEL(gtk_list_store_new(N_COLUMNS, G_TYPE_INT, G_TYPE_STRING, CC_TYPE_ITEM, CC_TYPE_ITEM));

	for(i = 3; i <= 12; i++) {
		gchar* text = g_strdup_printf("%d", i);
		gtk_list_store_append(GTK_LIST_STORE(model), &iter);
		gtk_list_store_set(GTK_LIST_STORE(model), &iter,
				   COL_NUM,  i,
				   COL_TEXT, text,
				   COL_POLYGON,  demo_polygon_new(i), // FIXME make this a polygon with i corners
				   COL_POLYGRAM, cc_item_new(),       // FIXME make this a polygram with i corners
				   -1);
		g_free(text);
	}

	gtk_tree_view_set_model(GTK_TREE_VIEW(tree), model);
	gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(tree), -1,
						    "Corners", gtk_cell_renderer_text_new(),
						    "text", COL_TEXT,
						    NULL);
	gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(tree), -1,
						    "Polygon", cc_view_cell_renderer_new(),
						    "root", COL_POLYGON,
						    NULL);
	gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(tree), -1,
						    "Polygram", cc_view_cell_renderer_new(),
						    "root", COL_POLYGRAM,
						    NULL);
	gtk_widget_show_all(page->widget);

	return page;
}

