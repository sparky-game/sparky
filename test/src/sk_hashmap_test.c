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
#include <sk_hashmap.h>
#include <sk_hashmap_test.h>

static u8 sk_hashmap_test_create_destroy(void) {
  sk_hashmap x = sk_hashmap_create(2 << 1, sizeof(int));
  carbon_should_be(2 << 1, x.capacity);
  carbon_should_be(sizeof(int), x.element_size);
  carbon_should_be_true(x.data);
  sk_hashmap_destroy(&x);
  carbon_should_be(0, x.capacity);
  carbon_should_be(0, x.element_size);
  carbon_should_be_p(0, x.data);
  return 1;
}

static u8 sk_hashmap_test_set_get_element(void) {
  sk_hashmap x = sk_hashmap_create(2 << 1, sizeof(int));
  int i = 7, j;
  carbon_should_be_true(sk_hashmap_set(&x, "seven", &i));
  carbon_should_be_true(sk_hashmap_get(&x, "seven", &j));
  carbon_should_be(i, j);
  sk_hashmap_destroy(&x);
  return 1;
}

void sk_hashmap_test_register(void) {
  CARBON_REGISTER_TEST(sk_hashmap_test_create_destroy);
  CARBON_REGISTER_TEST(sk_hashmap_test_set_get_element);
}
