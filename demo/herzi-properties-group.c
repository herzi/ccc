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

#include "herzi-properties-group.h"

#include <gtk/gtkalignment.h>
#include <gtk/gtkhbox.h>
#include <gtk/gtklabel.h>
#include <gtk/gtksizegroup.h>
#include <gtk/gtkvbox.h>

struct _HerziPropertiesGroup {
	GtkVBox    base_instance;

	gchar       * label;
	GtkLabel    * label_w;

	GtkWidget   * alignment;
	GtkBox      * intern;
	GtkSizeGroup* groups[2]; // the one for the labels and the one for the settings
};

struct _HerziPropertiesGroupClass {
	GtkHBoxClass base_class;
};

HerziPropertiesGroup*
herzi_properties_group_new(gchar const* label) {
	return g_object_new(HERZI_TYPE_PROPERTIES_GROUP, "label", label, NULL);
}

void
herzi_properties_group_add(HerziPropertiesGroup* self, gchar const* label, GtkWidget* widget) {
	GtkWidget* label_w;
	GtkWidget* box;

	g_return_if_fail(HERZI_IS_PROPERTIES_GROUP(self));
	label_w = gtk_label_new(NULL);
	box = gtk_hbox_new(FALSE, 6);

	gtk_label_set_markup_with_mnemonic(GTK_LABEL(label_w), label);
	gtk_label_set_mnemonic_widget(GTK_LABEL(label_w), widget);
	gtk_misc_set_alignment(GTK_MISC(label_w), 0.0, 0.5);

	gtk_size_group_add_widget(self->groups[0], label_w);
	gtk_box_pack_start_defaults(GTK_BOX(box), label_w);

	gtk_size_group_add_widget(self->groups[1], widget);
	gtk_box_pack_start(GTK_BOX(box), widget, FALSE, FALSE, 0);

	gtk_box_pack_start(self->intern, box, FALSE, FALSE, 0);
}

/* GType stuff */
G_DEFINE_TYPE(HerziPropertiesGroup, herzi_properties_group, GTK_TYPE_VBOX);

enum {
	PROP_0,
	PROP_LABEL
};

static void
herzi_properties_group_init(HerziPropertiesGroup* self) {
	gtk_box_set_spacing(GTK_BOX(self), 12);

	self->label_w = GTK_LABEL(gtk_label_new(NULL));
	gtk_misc_set_alignment(GTK_MISC(self->label_w), 0.0, 0.5);
	gtk_box_pack_start(GTK_BOX(self), GTK_WIDGET(self->label_w), FALSE, FALSE, 0);

	self->alignment = gtk_alignment_new(0.0, 0.5, 1.0, 1.0);
	gtk_alignment_set_padding(GTK_ALIGNMENT(self->alignment), 0, 0, 6, 0);;
	gtk_box_pack_start(GTK_BOX(self), self->alignment, FALSE, FALSE, 0);

	self->intern = GTK_BOX(gtk_vbox_new(FALSE, 6));
	gtk_container_add(GTK_CONTAINER(self->alignment), GTK_WIDGET(self->intern));

	self->groups[0] = gtk_size_group_new(GTK_SIZE_GROUP_HORIZONTAL);
	self->groups[1] = gtk_size_group_new(GTK_SIZE_GROUP_HORIZONTAL);
}

static void
hpg_dispose(GObject* object) {
	HerziPropertiesGroup* self = HERZI_PROPERTIES_GROUP(object);
	gint i;

	for(i = 0; i < 2; i++) {
		if(self->groups[i]) {
			g_object_unref(self->groups[i]);
			self->groups[i] = NULL;
		}
	}

	G_OBJECT_CLASS(herzi_properties_group_parent_class)->dispose(object);
}

static void
hpg_get_property(GObject* object, guint prop_id, GValue* value, GParamSpec* pspec) {
	HerziPropertiesGroup* self = HERZI_PROPERTIES_GROUP(object);

	switch(prop_id) {
	case PROP_LABEL:
		g_value_set_string(value, self->label);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
		break;
	}
}

static void
hpg_set_property(GObject* object, guint prop_id, GValue const* value, GParamSpec* pspec) {
	HerziPropertiesGroup* self = HERZI_PROPERTIES_GROUP(object);

	switch(prop_id) {
	case PROP_LABEL:
		g_free(self->label);
		self->label = g_strdup(g_value_get_string(value));
		{
			gchar* markup = g_strdup_printf("<span weight='bold'>%s</span>", self->label);
			gtk_label_set_markup(self->label_w, markup);
			g_free(markup);
		}
		g_object_notify(object, "label");
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
		break;
	}
}

static void
herzi_properties_group_class_init(HerziPropertiesGroupClass* self_class) {
	GObjectClass* go_class;

	/* GObjectClass */
	go_class = G_OBJECT_CLASS(self_class);
	go_class->dispose      = hpg_dispose;
	go_class->get_property = hpg_get_property;
	go_class->set_property = hpg_set_property;

	g_object_class_install_property(go_class,
					PROP_LABEL,
					g_param_spec_string("label",
							    "Label",
							    "Blurb",
							    NULL,
							    G_PARAM_READWRITE));
}

