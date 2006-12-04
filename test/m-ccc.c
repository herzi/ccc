/* This file is part of libccc
 *
 * AUTHORS
 *     Sven Herzberg  <herzi@gnome-de.org>
 *
 * Copyright (C) 2006  Sven Herzberg
 *
 * This work is provided "as is"; redistribution and modification
 * in whole or in part, in any medium, physical or electronic is
 * permitted without restriction.
 * 		
 * This work is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * 		
 * In no event shall the authors or contributors be liable for any
 * direct, indirect, incidental, special, exemplary, or consequential
 * damages (including, but not limited to, procurement of substitute
 * goods or services; loss of use, data, or profits; or business
 * interruption) however caused and on any theory of liability, whether
 * in contract, strict liability, or tort (including negligence or
 * otherwise) arising in any way out of the use of this software, even
 * if advised of the possibility of such damage.
 */

#include <glib-object.h>

#include "s-text.h"

#include <glib/gi18n.h>
#include <gtk/gtkmain.h>

int
main(int argc, char** argv)
{
	SRunner* r;
	Suite  * s;
	int      failed = 0;

	gtk_init(&argc, &argv);

	s = suite_text_item();
	r = srunner_create(s);
	srunner_set_fork_status(r, CK_NOFORK);
	srunner_run_all(r, CK_NORMAL);
	failed = srunner_ntests_failed(r);
	srunner_free(r);

	return failed != 0;
}
