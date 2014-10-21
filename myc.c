struct Point

  x, y int

  def new(x, y int) *Point
    &Point(x: x, y: y)
  end

  def move(x, y int)
    .x += x
    .y += y
  end
end

type APoint Point

def main
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

  func := (x)
    * x += 1
  end
  ary each(func)
  ary each((x) * x += 1)
  ary each(x, * x += 1)
  ary each(* it += 1)
  ary each(it.value)

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
end

def create_ary(len int) *int
  calloc(len, int)
end
