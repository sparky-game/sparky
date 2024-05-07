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
#include <sk_defines.h>
#include <sk_darray_test.h>

static u8 sk_darray_test_create_destroy(void) {
  sk_darray x = sk_darray_create(sizeof(int));
  carbon_should_be(1, x.capacity);
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

static u8 sk_darray_test_push_element(void) {
  sk_darray x = sk_darray_create(sizeof(int));
  int i = 7;
  carbon_should_be_true(sk_darray_push(&x, &i));
  carbon_should_be(1, x.curr_len);
  sk_darray_destroy(&x);
  return 1;
}

static u8 sk_darray_test_pop_element(void) {
  sk_darray x = sk_darray_create(sizeof(int));
  int i = 7, j;
  sk_darray_push(&x, &i);
  carbon_should_be_true(sk_darray_pop(&x, &j));
  carbon_should_be(0, x.curr_len);
  carbon_should_be(i, j);
  sk_darray_destroy(&x);
  return 1;
}

static u8 sk_darray_test_pop_element_from_empty_array(void) {
  sk_darray x = sk_darray_create(sizeof(int));
  int i = 7;
  carbon_should_be_false(sk_darray_pop(&x, &i));
  carbon_should_be(7, i);
  sk_darray_destroy(&x);
  return 1;
}

static u8 sk_darray_test_access_element(void) {
  sk_darray x = sk_darray_create(sizeof(int));
  int i = 7;
  sk_darray_push(&x, &i);
  int j = ((int *) x.data)[0];
  carbon_should_be(i, j);
  sk_darray_destroy(&x);
  return 1;
}

static u8 sk_darray_test_resizing(void) {
  sk_darray x = sk_darray_create(sizeof(int));
  for (int i = 0; i < 100; ++i) sk_darray_push(&x, &i);
  carbon_should_be(2 << 6, x.capacity);
  sk_darray_destroy(&x);
  return 1;
}

void sk_darray_test_register(void) {
  CARBON_REGISTER_TEST(sk_darray_test_create_destroy);
  CARBON_REGISTER_TEST(sk_darray_test_push_element);
  CARBON_REGISTER_TEST(sk_darray_test_pop_element);
  CARBON_REGISTER_TEST(sk_darray_test_pop_element_from_empty_array);
  CARBON_REGISTER_TEST(sk_darray_test_access_element);
  CARBON_REGISTER_TEST(sk_darray_test_resizing);
}
