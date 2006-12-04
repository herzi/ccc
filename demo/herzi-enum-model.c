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

#include "herzi-enum-model.h"

#include "glib-helpers.h"

struct _HerziEnumModel {
	GtkListStore base_instance;
	GType type;
};

GtkTreeModel*
herzi_enum_model_new(GType enum_type) {
	g_return_val_if_fail(g_type_is_a(enum_type, G_TYPE_ENUM), NULL);

	return g_object_new(HERZI_TYPE_ENUM_MODEL, "type", enum_type, NULL);
}

GType
herzi_enum_model_get_gtype(HerziEnumModel const* self) {
	g_return_val_if_fail(HERZI_IS_ENUM_MODEL(self), G_TYPE_INVALID);

	return self->type;
}

/* GType stuff */
G_DEFINE_TYPE(HerziEnumModel, herzi_enum_model, GTK_TYPE_LIST_STORE);

enum {
	PROP_0,
	PROP_TYPE
};

static void
herzi_enum_model_init(HerziEnumModel* self) {
	GType columns[HERZI_ENUM_MODEL_N_COLUMNS];
	columns[HERZI_ENUM_MODEL_COL_VALUE] = G_TYPE_INT;
	columns[HERZI_ENUM_MODEL_COL_NAME]  = G_TYPE_STRING;
	columns[HERZI_ENUM_MODEL_COL_NICK]  = G_TYPE_STRING;

	gtk_list_store_set_column_types(GTK_LIST_STORE(self), HERZI_ENUM_MODEL_N_COLUMNS, columns);
}

static GObject*
hem_constructor(GType type, guint n_properties, GObjectConstructParam* properties) {
	// FIXME: check the type first
	GObject* object = G_OBJECT_CLASS(herzi_enum_model_parent_class)->constructor(type, n_properties, properties);
	HerziEnumModel* self = HERZI_ENUM_MODEL(object);
	GEnumClass* klass = g_type_class_ref(self->type);
	guint i;

	for(i = 0; i < klass->n_values; i++) {
		GtkTreeIter iter;
		gtk_list_store_append(GTK_LIST_STORE(self), &iter);
		gtk_list_store_set(GTK_LIST_STORE(self), &iter,
				   HERZI_ENUM_MODEL_COL_VALUE, klass->values[i].value,
				   HERZI_ENUM_MODEL_COL_NAME,  klass->values[i].value_name,
				   HERZI_ENUM_MODEL_COL_NICK,  klass->values[i].value_nick,
				   -1);
	}

	g_type_class_unref(klass);

	return object;
}

static void
hem_get_property(GObject* object, guint prop_id, GValue* value, GParamSpec* pspec) {
	HerziEnumModel* self = HERZI_ENUM_MODEL(object);

	switch(prop_id) {
	case PROP_TYPE:
		g_value_set_gtype(value, herzi_enum_model_get_gtype(self));
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
		break;
	}
}

static void
hem_set_property(GObject* object, guint prop_id, GValue const* value, GParamSpec* pspec) {
	HerziEnumModel* self = HERZI_ENUM_MODEL(object);

	switch(prop_id) {
	case PROP_TYPE:
		self->type = g_value_get_gtype(value);
		g_object_notify(object, "type");
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
		break;
	}
}

static void
herzi_enum_model_class_init(HerziEnumModelClass* self_class) {
	GObjectClass* go_class;

	/* GObjectClass */
	go_class = G_OBJECT_CLASS(self_class);
	go_class->constructor  = hem_constructor;
	go_class->get_property = hem_get_property;
	go_class->set_property = hem_set_property;

	g_object_class_install_property(go_class,
					PROP_TYPE,
					g_param_spec_gtype("type",
							   "Enum GType",
							   "Blurb",
							   G_TYPE_ENUM,
							   G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY));
}

