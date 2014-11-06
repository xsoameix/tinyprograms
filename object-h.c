class Object {

  struct {
    union {
      @@ * class;
      @@ * _;
    };
  }

  methods {
    @ *    (* -new)       (void);
    void   (* -init)      (self);
    void   (* -delete)    (self);
    @@ *   (* -class)     (self);
    char * (* -class_name)(self);
    bool   (* -is_a)      (self, @@ * class);
  }
}
