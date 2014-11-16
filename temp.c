#include <stdio.h>

:class Object {

  struct {
    char * hello_world;
  }
}

void
:realloc(self, h_size_t capa) {
  @bins = realloc(@bins, capa * sizeof(h_entry *));
  memset(@bins, 0, capa * sizeof(h_entry *));
  @capa = capa;
}
