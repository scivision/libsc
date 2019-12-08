/*
  This file is part of the SC Library, version 3.
  The SC Library provides support for parallel scientific applications.

  Copyright (C) 2019 individual authors

  The SC Library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  The SC Library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with the SC Library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
  02110-1301, USA.
*/

#include <sc3_error.h>

struct sc3_error
{
  sc3_error_severity_t sev;
  sc3_error_sync_t    syn;
  char               *filename;
  int                 line;
  char               *errmsg;
  sc3_error_t        *stack;
};

/* TODO write error_new */

void
sc3_error_destroy (sc3_error_t * e)
{
  /* TODO: finish and think about allocation */
  SC3_FREE (e);
}

sc3_error_t        *
sc3_error_new_stack (sc3_error_t * stack, const char *filename,
                     int line, const char *errmsg)
{
  /* TODO write */
  return NULL;
}

sc3_error_t        *
sc3_error_new_fatal (const char *filename, int line, const char *errmsg)
{
  sc3_error_t        *e;

  /* TODO: generalize memory allocation */

  e = SC3_MALLOC (sc3_error_t, 1);
  e->filename = NULL;
  e->line = line;
  e->errmsg = NULL;
  e->stack = NULL;
  return e;
}

sc3_error_t        *
sc3_error_is_fatal (sc3_error_t * e, int *ir)
{
  SC3A_CHECK (e != NULL);
  SC3A_RETVAL (ir, e->sev == SC3_ERROR_FATAL);
  return NULL;
}