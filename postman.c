:class Pman {

  struct {
    int hit;
  }
}

:class Proad {

  struct {
    int conn; // connected
  }
}

:class Pmans < Ary {}

· *
:new(int len) { return super(&Pmans, len); }

int
:size(void) { return sizeof(proad_t); }

:class Pmat < Matrix {

  struct {
    pmans_t * pmans;
  }
}

· *
:new(int len) {
  · * pmat = super(&Pmat, len);
  pmat->pmans = Pmans.new(len);
  return pmat;
}

int
:size(void) { return sizeof(pman_t); }

int
:conn(self, int from, int to) {
  pmans_t * pmans = @pmans;
  pman_t * pman = pmans·get(from);
  pman->hit = 1;
  int col = 0;
  for (; col < ·len; col++) {
    proad_t * road = ·get(from, col);
    pmans_t * pmans = @pmans;
    pman_t * pman = pmans·get(col);
    if (road->conn && !pman->hit) {
      pman->hit = 1;
      if (col == to) return 1;
      int conn = ·conn(col, to);
      if (conn) return 1;
    }
  }
  return 0;
}

int
main(void) {
  int len, from, to;
  while (scanf("%d%d%d", &len, &from, &to) == 3) {
    pmat_t * pmat = Pmat.new(len);
    int row = 0;
    for (; row < pmat·len; row++) {
      int col = 0;
      for (; col < pmat·len; col++) {
        proad_t * proad = pmat·get(row, col);
        scanf("%d", &proad->conn);
      }
    }
    int conn = pmat·conn(from, to);
    printf("%s\n", conn ? "Y" : "N");
    pmat·free;
  }
  return 0;
}
