/*
This file shows the basics of using binn objects. It does not show lists and maps.
For more examples check https://github.com/liteserver/binn/blob/master/usage.md
*/

#include <binn.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stddef.h>

void read_example_3a(binn *obj);
void create_and_pass_binn();

int main(){
    create_and_pass_binn();

}

void read_example_3a(binn *obj) {
  int id;
  char *name;
  double price;

  id = binn_object_int32(obj, "id");
  name = binn_object_str(obj, "name");
  price = binn_object_double(obj, "price");

  printf("%s", name);

}

void create_and_pass_binn() {
  binn *obj;

  // create a new object
  obj = binn_object();

  // add values to it
  binn_object_set_int32(obj, "id", 123);
  binn_object_set_str(obj, "name", "Samsung Galaxy");
  binn_object_set_double(obj, "price", 299.90);

  // pass the binn pointer to another function

  read_example_3a(obj);

  // release the object
  binn_free(obj);

}