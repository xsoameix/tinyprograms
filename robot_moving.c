typedef long long int num_t;

:class Cell {

  struct {
    num_t count;
  }
}

:class Cells < Matrix {

  struct {
    int left;
    int right;
  }
}

· *
:new(int len, int left, int right) {
  · * self = super(&Cells, len);
  left = - left;
  right = - right;
  if (right < left) {
    int tmp = left;
    left = right;
    right = tmp;
  }
  @left = left;
  @right = right;
  return self;
}

int
:size(void) { return sizeof(cell_t); }

void
:move(self) {
  int row = 0;
  for (; row < @len - @left; row++) {
    int col = @left + row;
    for (; col <= @right + row && col < @len; col++) {
      cell_t * cell = ·get(row, col);
      if (row == 0) {
        cell->count = 1;
        continue;
      }
      cell_t * below = ·get(row - 1, col);
      cell_t * left = ·get(row, col - 1);
      if (col == @left + row) {
        cell->count = below->count;
        continue;
      }
      if (col == @right + row) {
        cell->count = left->count;
        continue;
      }
      cell->count = left->count + below->count;
    }
  }
}

void
:print(self) {
  int row = 0;
  for (; row < @len; row++) {
    int col = 0;
    for (; col < @len; col++) {
      cell_t * cell = ·get(row, col);
      printf("%lld", cell->count);
      if (col != @len - 1) {
        printf(" ");
      }
    }
    puts("");
  }
}

int
main(void) {
  int len, left, right;
  while (scanf("%d%d%d", &len, &left, &right) == 3) {
    cells_t * cells = Cells.new(len + 1, left, right);
    cells·move;
    cell_t * cell = cells·get(len, len);
    printf("%lld\n", cell->count);
    cells·free;
  }
  return 0;
}
