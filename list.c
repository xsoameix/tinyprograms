:class Lnode {

  struct {
    · * fore;
    · * back;
    void * obj;
  }
}

void *
:new(void * class, void * obj) {
  · * self = calloc(1, sizeof(·));
  @obj = obj;
  return self;
}

:class List {

  struct {
    int len;
    lnode_t * head;
    lnode_t * tail;
  }
}

void *
:new(void * class) {
  · * self = calloc(1, sizeof(·));
  @class = class;
  return self;
}

void
:add(self, void * obj) {
  lnode_t * new = obj;
  if (@len) {
    @tail->back = new;
    new->fore = @tail;
    @tail = new;
  } else {
    @head = @tail = new;
  }
  @len++;
}

int
:remove(self, void * obj) {
  lnode_t * node = @head;
  for (; node; node = node->back) {
    if (node != obj) continue;
    if (node->fore) {
      node->fore->back = node->back;
    }
    if (node->back) {
      node->back->fore = node->fore;
    }
    if (node == @head) {
      @head = node->back;
    } else if (node == @tail) {
      @tail = node->fore;
    }
    free(node);
    @len--;
    return 1;
  }
  return 0;
}

int
:len(self) {
  return @len;
}

void *
:min(self) {
  lnode_t * node = @head;
  lnode_t * min = node;
  for (; node; node = node->back) {
    void * tmin = min->obj;
    void * town = node->obj;
    if (·cmp(town, tmin) < 0) {
      min = node;
    }
  }
  return min;
}

int
:cmp(self, void * a, void * b) {
  return a - b;
}

void
:free(self) {
  free(self);
}
