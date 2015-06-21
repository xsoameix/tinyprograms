#include <gvc.h>

int
main(void) {
  Agraph_t * g;
  Agnode_t * n, * m;
  Agedge_t * e;
  GVC_t * gvc;
  gvc = gvContext();
  g = agopen("g", Agdirected, 0);
  n = agnode(g, "n", 1);
  m = agnode(g, "m", 1);
  e = agedge(g, n, m, 0, 1);
  agsafeset(e, "colorscheme", "blues3", "");
  agsafeset(e, "color", "3", "");
  agsafeset(n, "shape", "circle", "");
  agsafeset(m, "shape", "circle", "");
  agsafeset(n, "fontname", "Sans", "");
  agsafeset(m, "fontname", "Sans", "");
  gvLayout(gvc, g, "dot");
  gvRenderFilename(gvc, g, "png", "graphviz.png");
  gvFreeLayout(gvc, g);
  agclose(g);
  return 0;
}
