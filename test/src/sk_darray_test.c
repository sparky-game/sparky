/*
 * GNU Sparky --- A 5v5 character-based libre tactical shooter
 * Copyright (C) 2024 Wasym A. Alonso
 *
 * This file is part of Sparky.
 *
 * Sparky is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Sparky is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Sparky.  If not, see <http://www.gnu.org/licenses/>.
 */


#include <carbon.h>
#include <sk_darray.h>
#include <sk_darray_test.h>

static unsigned char sk_darray_test_create_destroy(void) {
  sk_darray x = sk_darray_create(sizeof(int));
  carbon_should_be_true(x.capacity);
  carbon_should_be(sizeof(int), x.element_size);
  carbon_should_be(0, x.curr_len);
  carbon_should_be_true(x.data);
  sk_darray_destroy(&x);
  carbon_should_be(0, x.capacity);
  carbon_should_be(0, x.element_size);
  carbon_should_be(0, x.curr_len);
  carbon_should_be(0, x.data);
  return 1;
}

void sk_darray_test_register(void) {
  CARBON_REGISTER_TEST(sk_darray_test_create_destroy);
}
