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

#include "herzi-enum-combo.h"

#include <gtk/gtkcelllayout.h>
#include <gtk/gtkcellrenderertext.h>
#include "glib-helpers.h"
#include "herzi-enum-model.h"

GtkWidget*
herzi_enum_combo_new(GType enum_type) {
	g_return_val_if_fail(g_type_is_a(enum_type, G_TYPE_ENUM), NULL);

	return g_object_new(HERZI_TYPE_ENUM_COMBO, "type", enum_type, NULL);
}

gint
herzi_enum_combo_get_value(HerziEnumCombo const* self) {
	GtkTreeIter iter;
	gint        retval = 0;

	gtk_combo_box_get_active_iter(GTK_COMBO_BOX(self), &iter);
	gtk_tree_model_get(gtk_combo_box_get_model(GTK_COMBO_BOX(self)), &iter,
			   HERZI_ENUM_MODEL_COL_VALUE, &retval,
			   -1);

	return retval;
}

/* GType stuff */
G_DEFINE_TYPE(HerziEnumCombo, herzi_enum_combo, GTK_TYPE_COMBO_BOX);

enum {
	PROP_0,
	PROP_TYPE
};

static void
herzi_enum_combo_init(HerziEnumCombo* self) {
	GtkCellLayout* layout = GTK_CELL_LAYOUT(self);
	GtkCellRenderer* cell = gtk_cell_renderer_text_new();

	gtk_cell_layout_pack_start(layout, cell, TRUE);
	gtk_cell_layout_add_attribute(layout, cell, "text", HERZI_ENUM_MODEL_COL_NICK);
}

static void
hec_get_property(GObject* object, guint prop_id, GValue* value, GParamSpec* pspec) {
	HerziEnumCombo* self = HERZI_ENUM_COMBO(object);
	gpointer        pointer;

	switch(prop_id) {
	case PROP_TYPE:
		pointer = gtk_combo_box_get_model(GTK_COMBO_BOX(self));
		g_value_set_gtype(value, HERZI_IS_ENUM_MODEL(pointer) ? herzi_enum_model_get_gtype(HERZI_ENUM_MODEL(pointer)) : G_TYPE_INVALID);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
		break;
	}
}

static void
hec_set_property(GObject* object, guint prop_id, GValue const* value, GParamSpec* pspec) {
	HerziEnumCombo* self = HERZI_ENUM_COMBO(object);

	switch(prop_id) {
	case PROP_TYPE:
		{
			GType type = g_value_get_gtype(value);
			GtkTreeModel* model = herzi_enum_model_new(type);
			gtk_combo_box_set_model(GTK_COMBO_BOX(self), model);
			gtk_combo_box_set_active(GTK_COMBO_BOX(self), 0);
			g_object_unref(model);
		}
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
		break;
	}
}

static void
herzi_enum_combo_class_init(HerziEnumComboClass* self_class) {
	GObjectClass* go_class;

	/* GObjectClass */
	go_class = G_OBJECT_CLASS(self_class);
	go_class->get_property = hec_get_property;
	go_class->set_property = hec_set_property;

	g_object_class_install_property(go_class,
					PROP_TYPE,
					g_param_spec_gtype("type",
							   "Type",
							   "Type",
							   G_TYPE_ENUM,
							   G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY));
}

