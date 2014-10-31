require(
  Point,
  create_ary
)

struct(Point,

  x, y int

  def(new(x, y int) *Point,
    &Point(x: x, y: y)
  )

  def(move(x, y int),
    .x += x
    .y += y
  )
)

type(APoint, Point)

def(main,
  len := scanf("%d\n")
  # len: int(class Int, value int)

  ary := len times map(i,
    Point new(x, y)
  )
  # ary: &Array(class Array, type: Point, values)

  ary = create_ary(len)
  # ary: &Array(class Array, type: Int, values)

  ary : [4]int

  ary each(x,
    # x: &int(class Int, value int)
    * x += 1
  )
  puts(ary)

  func := def((x)
    * x += 1
  )
  ary each(func)
  ary each(def((x) * x += 1))
  ary each(x, * x += 1)
  ary each(* it += 1)
  ary each(it.value)
  ary each(.value)

  if(ary len == 1,
    ary[0] += 1,
    ary[1] = 2
  )
  (ary len == 1) if_true(ary[0] += 1) if_false(ary[1] = 2)

  cond(
    x == 1, puts("one"),
    x == -1, puts("two")
  )
  loop(
    if(x > 5, break)
    x += 1
  )
  while(x < 10,
    puts(x)
    x++
  )

  ary = ary map(x,
    Point new(0, 0)
  )
  # ary: &Array(class Array, type: Point, values)
)

def(main, puts("hello world"))
def(main(argc, argv), puts("hello world"))
def(main(argc int, argv []string) int, puts("hello world"))
def(main int, puts("hello world"))

def(create_ary(len int) *int,
  calloc(len, int)
  def((len int) int,
    len + 1)
)

def(create_ary(len),
  calloc(len, int)
  def((len),
    len + 1)
)

export(
  Point,
  create_ary
)
