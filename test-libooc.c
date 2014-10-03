extern const void * Array;
void Array_init(void);
void Array_ctor(void * self, va_list * args_ptr);
void Array_dtor(void * self);
ooc_uint Array_len(void * self);
void * Array_get(void * self, ooc_uint index);
void * Array_first(void * self);
void * Array_last(void * self);
void Array_push(void * self, void * data);
void * Array_pop(void * self);
void Array_unshift(void * self, void * data);
void * Array_shift(void * self);
void Array_each(void * self, void (* iter)(void * _self_, void * obj, ooc_uint index), void * _self_);
void Array_reverse_each(void * self, void (* iter)(void * _self_, void * obj, ooc_uint index), void * _self_);
_Bool Array_any_p(void * self, _Bool (* iter)(void * _self_, void * obj, ooc_uint index), void * _self_);
struct Array {
	struct Object super;
	ooc_uint len;
	ooc_uint capa;
	void ** values;
}
;
struct ArrayClass {
	const struct ObjectClass class;
	ooc_uint (* len)(struct Array * self);
	void * (* get)(struct Array * self, ooc_uint index);
	void * (* first)(struct Array * self);
	void * (* last)(struct Array * self);
	void (* push)(struct Array * self, void * data);
	void * (* pop)(struct Array * self);
	void (* unshift)(struct Array * self, void * data);
	void * (* shift)(struct Array * self);
	void (* each)(struct Array * self, void (* iter)(void * _self_, void * obj, ooc_uint index), void * _self_);
	void (* reverse_each)(struct Array * self, void (* iter)(void * _self_, void * obj, ooc_uint index), void * _self_);
	_Bool (* any_p)(struct Array * self, _Bool (* iter)(void * _self_, void * obj, ooc_uint index), void * _self_);
}
;
static ooc_uint len(struct Array * self) __attribute__((weakref("Array" "_" "len")));
static void * get(struct Array * self, ooc_uint index) __attribute__((weakref("Array" "_" "get")));
static void * first(struct Array * self) __attribute__((weakref("Array" "_" "first")));
static void * last(struct Array * self) __attribute__((weakref("Array" "_" "last")));
static void push(struct Array * self, void * data) __attribute__((weakref("Array" "_" "push")));
static void * pop(struct Array * self) __attribute__((weakref("Array" "_" "pop")));
static void unshift(struct Array * self, void * data) __attribute__((weakref("Array" "_" "unshift")));
static void * shift(struct Array * self) __attribute__((weakref("Array" "_" "shift")));
static void each(struct Array * self, void (* iter)(void * _self_, void * obj, ooc_uint index), void * _self_) __attribute__((weakref("Array" "_" "each")));
static void reverse_each(struct Array * self, void (* iter)(void * _self_, void * obj, ooc_uint index), void * _self_) __attribute__((weakref("Array" "_" "reverse_each")));
static _Bool any_p(struct Array * self, _Bool (* iter)(void * _self_, void * obj, ooc_uint index), void * _self_) __attribute__((weakref("Array" "_" "any_p")));
typedef ooc_int int_t;
typedef ooc_uint uint_t;
static const void * ArrayClass;
const void * Array;
static void ArrayClass_ctor(struct ArrayClass * class, va_list * args_ptr) {
	const struct ObjectClass * superclass = ((const struct ObjectClass *) class)->class->super;
	superclass->ctor(class, args_ptr);
	va_list args;
	__builtin_va_copy(args,* args_ptr);
	typedef void (* func)(void);
	func select, method;
	while(select = __builtin_va_arg(args,func)) {
		method = __builtin_va_arg(args,func);
		if(select == (func) Array_len) {
			* (func *) &class->len = method;
		} else if(select == (func) Array_get) {
			* (func *) &class->get = method;
		} else if(select == (func) Array_first) {
			* (func *) &class->first = method;
		} else if(select == (func) Array_last) {
			* (func *) &class->last = method;
		} else if(select == (func) Array_push) {
			* (func *) &class->push = method;
		} else if(select == (func) Array_pop) {
			* (func *) &class->pop = method;
		} else if(select == (func) Array_unshift) {
			* (func *) &class->unshift = method;
		} else if(select == (func) Array_shift) {
			* (func *) &class->shift = method;
		} else if(select == (func) Array_each) {
			* (func *) &class->each = method;
		} else if(select == (func) Array_reverse_each) {
			* (func *) &class->reverse_each = method;
		} else if(select == (func) Array_any_p) {
			* (func *) &class->any_p = method;
		} else {
		}
	}
}
void Array_ctor(void * self, va_list * args_ptr) {
	struct Object * _self = self;
	const struct ObjectClass * _class = (struct ObjectClass *) ((struct Object *) _self)->class;
	return _class->ctor(_self, args_ptr);
}
void Array_dtor(void * self) {
	struct Object * _self = self;
	const struct ObjectClass * _class = (struct ObjectClass *) ((struct Object *) _self)->class;
	return _class->dtor(_self);
}
ooc_uint Array_len(void * self) {
	struct Array * _self = self;
	const struct ArrayClass * _class = (struct ArrayClass *) ((struct Object *) _self)->class;
	return _class->len(_self);
}
void * Array_get(void * self, ooc_uint index) {
	struct Array * _self = self;
	const struct ArrayClass * _class = (struct ArrayClass *) ((struct Object *) _self)->class;
	return _class->get(_self, index);
}
void * Array_first(void * self) {
	struct Array * _self = self;
	const struct ArrayClass * _class = (struct ArrayClass *) ((struct Object *) _self)->class;
	return _class->first(_self);
}
void * Array_last(void * self) {
	struct Array * _self = self;
	const struct ArrayClass * _class = (struct ArrayClass *) ((struct Object *) _self)->class;
	return _class->last(_self);
}
void Array_push(void * self, void * data) {
	struct Array * _self = self;
	const struct ArrayClass * _class = (struct ArrayClass *) ((struct Object *) _self)->class;
	return _class->push(_self, data);
}
void * Array_pop(void * self) {
	struct Array * _self = self;
	const struct ArrayClass * _class = (struct ArrayClass *) ((struct Object *) _self)->class;
	return _class->pop(_self);
}
void Array_unshift(void * self, void * data) {
	struct Array * _self = self;
	const struct ArrayClass * _class = (struct ArrayClass *) ((struct Object *) _self)->class;
	return _class->unshift(_self, data);
}
void * Array_shift(void * self) {
	struct Array * _self = self;
	const struct ArrayClass * _class = (struct ArrayClass *) ((struct Object *) _self)->class;
	return _class->shift(_self);
}
void Array_each(void * self, void (* iter)(void * _self_, void * obj, ooc_uint index), void * _self_) {
	struct Array * _self = self;
	const struct ArrayClass * _class = (struct ArrayClass *) ((struct Object *) _self)->class;
	return _class->each(_self, iter, _self_);
}
void Array_reverse_each(void * self, void (* iter)(void * _self_, void * obj, ooc_uint index), void * _self_) {
	struct Array * _self = self;
	const struct ArrayClass * _class = (struct ArrayClass *) ((struct Object *) _self)->class;
	return _class->reverse_each(_self, iter, _self_);
}
_Bool Array_any_p(void * self, _Bool (* iter)(void * _self_, void * obj, ooc_uint index), void * _self_) {
	struct Array * _self = self;
	const struct ArrayClass * _class = (struct ArrayClass *) ((struct Object *) _self)->class;
	return _class->any_p(_self, iter, _self_);
}
static void __Array_ctor(struct Array * self, va_list * args_ptr);
static void __Array_dtor(struct Array * self);
static ooc_uint __Array_len(struct Array * self);
static void * __Array_get(struct Array * self, ooc_uint index);
static void * __Array_first(struct Array * self);
static void * __Array_last(struct Array * self);
static void __Array_push(struct Array * self, void * data);
static void * __Array_pop(struct Array * self);
static void __Array_unshift(struct Array * self, void * data);
static void * __Array_shift(struct Array * self);
static void __Array_each(struct Array * self, void (* iter)(void * _self_, void * obj, ooc_uint index), void * _self_);
static void __Array_reverse_each(struct Array * self, void (* iter)(void * _self_, void * obj, ooc_uint index), void * _self_);
static _Bool __Array_any_p(struct Array * self, _Bool (* iter)(void * _self_, void * obj, ooc_uint index), void * _self_);
static void __Array_double_capa(struct Array * self, ooc_uint offset);
void Array_init(void) {
	if(!ArrayClass) {
		ooc_uint name = (ooc_uint) "Array" "Class";
		ooc_uint size = sizeof(struct ArrayClass);
		ArrayClass = new(Class, Class, name, size, (ooc_uint) 0, Object_ctor, ArrayClass_ctor, (ooc_uint) 0);
	}
	if(!Array) {
		ooc_uint name = (ooc_uint) "Array";
		ooc_uint size = sizeof(struct Array);
		Array = new(ArrayClass, Object, name, size, (ooc_uint) 0, Object_ctor, __Array_ctor, Object_dtor, __Array_dtor, Array_len, __Array_len, Array_get, __Array_get, Array_first, __Array_first, Array_last, __Array_last, Array_push, __Array_push, Array_pop, __Array_pop, Array_unshift, __Array_unshift, Array_shift, __Array_shift, Array_each, __Array_each, Array_reverse_each, __Array_reverse_each, Array_any_p, __Array_any_p, (ooc_uint) 0);
	}
}
static void double_capa(struct Array * self, ooc_uint offset) __attribute__((alias("__" "Array" "_" "double_capa")));
static void __Array_ctor(struct Array * self, va_list * args_ptr) {
	self->len = 0;
	self->capa = 2;
	self->values = malloc(2 * sizeof(void *));
}
static void __Array_dtor(struct Array * self) {
	free(self->values);
	free(self);
}
static ooc_uint __Array_len(struct Array * self) {
	return self->len;
}
static void * __Array_get(struct Array * self, ooc_uint index) {
	return self->len > index ? self->values[index] : ((void *)0);
}
static void * __Array_first(struct Array * self) {
	return self->len > 0 ? self->values[0] : ((void *)0);
}
static void * __Array_last(struct Array * self) {
	uint_t len = self->len;
	return len > 0 ? self->values[len - 1] : ((void *)0);
}
static void __Array_push(struct Array * self, void * data) {
	if(self->len == self->capa) {
		double_capa(self, 0);
	}
	self->values[self->len++] = data;
}
static void * __Array_pop(struct Array * self) {
	if(self->len == 0) return ((void *)0);
	return self->values[--self->len];
}
static void __Array_unshift(struct Array * self, void * data) {
	if(self->len == self->capa) {
		double_capa(self, 1);
	}
	self->values[0] = data;
}
static void * __Array_shift(struct Array * self) {
	if(self->len == 0) return ((void *)0);
	void ** values = self->values;
	void * element = values[0];
	memmove(values, &values[1], --self->len * sizeof(void *));
	return element;
}
static void __Array_each(struct Array * self, void (* iter)(void * _self_, void * obj, ooc_uint index), void * _self_) {
	void ** values = self->values;
	for (uint_t i = 0, len = self->len; i < len; i++) {
		iter(_self_, values[i], i);
	}
}
static void __Array_reverse_each(struct Array * self, void (* iter)(void * _self_, void * obj, ooc_uint index), void * _self_) {
	void ** values = self->values;
	uint_t len = self->len;
	uint_t i = len;
	while(i > 0) {
		i -= 1;
		iter(_self_, values[i], len - i - 1);
	}
}
static _Bool __Array_any_p(struct Array * self, _Bool (* iter)(void * _self_, void * obj, ooc_uint index), void * _self_) {
	void ** values = self->values;
	for (uint_t i = 0, len = self->len; i < len; i++) {
		if(iter(_self_, values[i], i)) {
			return 1;
		}
	}
	return 0;
}
static void __Array_double_capa(struct Array * self, ooc_uint offset) {
	uint_t capa = self->len * 2;
	void ** values = malloc(capa * sizeof(void *));
	memcpy(&values[offset], self->values, self->len * sizeof(void *));
	free(self->values);
	self->values = values;
	self->capa = capa;
}
