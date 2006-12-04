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

#ifndef HERZI_ENUM_COMBO_H
#define HERZI_ENUM_COMBO_H

#include <gtk/gtkcombobox.h>

G_BEGIN_DECLS

typedef struct _HerziEnumCombo      HerziEnumCombo;
typedef struct _HerziEnumComboClass HerziEnumComboClass;

#define HERZI_TYPE_ENUM_COMBO         (herzi_enum_combo_get_type())
#define HERZI_ENUM_COMBO(i)           (G_TYPE_CHECK_INSTANCE_CAST((i), HERZI_TYPE_ENUM_COMBO, HerziEnumCombo))

GType herzi_enum_combo_get_type(void);

GtkWidget* herzi_enum_combo_new      (GType enum_type);
gint       herzi_enum_combo_get_value(HerziEnumCombo const* self);

struct _HerziEnumCombo {
	GtkComboBox base_instance;
};

struct _HerziEnumComboClass {
	GtkComboBoxClass base_class;
};

G_END_DECLS

#endif /* !HERZI_ENUM_COMBO_H */
