class String < Object

@ *
·new(char *) {
}

void
·init(self, char * val) {
  ··initialize();
  ·string = val;
  string_t * str = String.new("abc");
  str·len + 1;
  str·concat("def") + 1;
  str->_->len(str) + 1;
  str->_->concat(str, "def") + 1;

  string_t str = String.new("abc");
  str˙len + 1;
  str˙concat("def") + 1;
  str˙+("def")˙+("def");
  str˙add("def")˙add("def");
  str˙at(1);

  str._->len(&str) + 1;
  str._->concat(&str, "def") + 1;
  str._->add(&str, "def")._->add(&str, "def");
  str._->at(&str, 1)
}

char *
·string(self) {
  return ·string;
}

size_t
·len(self) {
  return strlen(·string);
}
