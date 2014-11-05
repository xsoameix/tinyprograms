class String < Object {

  struct {
    char * string;
  }

  methods {
    @    * (* !new)  (char *);
    void   (* !init) (self, char *);
    char * (* string)(self);
    size_t (* len)   (self);
  }
}
