#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef struct {
  int32_t left;
  int32_t right;
} node_t;

typedef char step_t;

int32_t
path_len(node_t node, step_t * steps) {
  int32_t i = 0;
  while (!(node.left == 1 &&
           node.right == 1)) {
    if (node.left < node.right) {
      node.right -= node.left;
      if (steps) steps[i] = 'L';
    } else {
      node.left -= node.right;
      if (steps) steps[i] = 'R';
    }
    i++;
  }
  return i;
}

void
node_path(node_t node) {
  int32_t len = path_len(node, 0);
  static step_t steps_storage[100000];
  memset(steps_storage, 0, 100000);
  step_t * steps = steps_storage;
  //step_t * steps = calloc(len, sizeof(step_t));
  path_len(node, steps);
  printf("%s\n", steps);
  //free(steps);
}

int32_t
main(void) {
  node_t key;
  while (1) {
    scanf("%d%d", &key.left, &key.right);
    if (key.left == 0 &&
        key.right == 0) break;
    node_path(key);
  }
  return 0;
}
