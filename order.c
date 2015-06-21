int
P(int * s) {
  return 1;
}

int
main(void) {
  int d, s[10], h[10], j, k = 0;
  d = s[j = h[--k]] = P(s+h[k]); /* -Wsequence-point */
  j = h[--k], d = s[j] = P(s+j); /* correct */
  return 0;
}
