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

#include "ce-window.h"

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <glib/gi18n.h>
#include <gtk/gtk.h>
#include <ccc.h>

#include "demo-canvas.h"

GtkWidget*
ce_window_new(void) {
	return g_object_new(CE_TYPE_WINDOW, NULL);
}

/* GType */
G_DEFINE_TYPE(CEWindow, ce_window, HERZI_TYPE_MAIN_WINDOW);

static gchar const * const ce_user_interface =
"<ui>"
"	<menubar name='menubar'>"
"		<menu action='File'>"
"			<placeholder name='FileOpen'>"
"				<menuitem action='CanvasNew' />"
"			</placeholder>"
"		</menu>"
"	</menubar>"
"	<toolbar name='toolbar'>"
"		<toolitem action='CanvasNew' />"
"	</toolbar>"
"</ui>";

static void
cw_action_canvas_new(GtkAction* action, CEWindow* self) {
	cc_view_set_root(CC_VIEW(self->canvas_view), demo_canvas_create());//cc_item_new());
}

static GtkActionEntry const ce_window_entries[] = {
	{"File",	NULL,		N_("_Canvas")},
	{"CanvasNew",	GTK_STOCK_NEW,	NULL,
	 NULL,		NULL,
	 G_CALLBACK(cw_action_canvas_new)}
};

static void
cw_notify_root(CEWindow* self, GParamSpec* pspec, CcView* view) {
	ce_canvas_tree_model_set_root(self->canvas_tree, cc_view_get_root(view));
}

static void
ce_window_init(CEWindow* self) {
	GtkWidget* hpaned = gtk_hpaned_new();
	GtkWidget* container = gtk_scrolled_window_new(NULL, NULL);
	GtkActionGroup* actions = NULL;
	HerziMainWindow* mainwin = HERZI_MAIN_WINDOW(self);
	GError* error = NULL;

	/* set up the window itself */
	gtk_window_set_title(GTK_WINDOW(self), _("Canvas Editor"));

	actions = gtk_action_group_new("ce-window-actions");
	gtk_action_group_add_actions(actions, ce_window_entries, G_N_ELEMENTS(ce_window_entries), self);
	gtk_ui_manager_insert_action_group(mainwin->ui_manager, actions, 0);
	gtk_ui_manager_add_ui_from_string(mainwin->ui_manager, ce_user_interface, -1, &error);

	if(error) {
		g_warning("Couldn't create the user interface: %s", error->message);
		g_error_free(error);
		error = NULL;
	}

	gtk_box_pack_start(GTK_BOX(mainwin->vbox), gtk_ui_manager_get_widget(mainwin->ui_manager, "/toolbar"), FALSE, FALSE, 0);

	self->canvas_view = cc_view_widget_new();
	g_signal_connect_swapped(self->canvas_view, "notify::root",
				 G_CALLBACK(cw_notify_root), self);
	gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(container), GTK_SHADOW_IN);
	gtk_container_add(GTK_CONTAINER(container), self->canvas_view);
	gtk_paned_pack1(GTK_PANED(hpaned), container, TRUE, FALSE);

	self->sidebar = gtk_vpaned_new();
	gtk_paned_pack2(GTK_PANED(hpaned), self->sidebar, FALSE, FALSE);

	self->item_tree = gtk_tree_view_new();
	gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(self->item_tree), -1,
						    _("Canvas"), gtk_cell_renderer_text_new(),
						    "text", CE_CANVAS_TREE_MODEL_COL_NAME,
						    NULL);
	container = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(container), GTK_SHADOW_IN);
	gtk_container_add(GTK_CONTAINER(container), self->item_tree);
	gtk_paned_pack1(GTK_PANED(self->sidebar), container, FALSE, FALSE);

	self->canvas_tree = ce_canvas_tree_model_new();
	gtk_tree_view_set_model(GTK_TREE_VIEW(self->item_tree), self->canvas_tree);
	g_object_unref(self->canvas_tree);

	gtk_widget_show_all(hpaned);
	gtk_box_pack_start_defaults(GTK_BOX(mainwin->vbox), hpaned);

	/* put the window into a usable state */
	cw_action_canvas_new(NULL, self);

	gtk_action_set_visible(gtk_ui_manager_get_action(mainwin->ui_manager,
							 "/menubar/File/FileClose"),
			       FALSE);
}

static void
ce_window_class_init(CEWindowClass* self_class) {}

