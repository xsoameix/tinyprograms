#include <stdio.h>
#include <math.h>

typedef struct point {
  double x;
  double y;
} point_t;

typedef struct rectangle {
  point_t left;
  point_t right;
} rectangle_t;

typedef struct circle {
  point_t center;
  double radius;
} circle_t;

typedef struct triangle {
  point_t points[3];
} triangle_t;

typedef struct shape {
  int id;
  char type;
  union shape_poly {
    rectangle_t rectangle;
    circle_t circle;
    triangle_t triangle;
  } shape;
} shape_t;

double
area(point_t * a, point_t * b, point_t * c) {
  return fabs(a->x * b->y + b->x * c->y + c->x * a->y -
              a->y * b->x - b->y * c->x - c->y * a->x) / 2;
}

int
main(void) {
  shape_t shapes[10];
  int i = 0;
  for (; 1; i++) {
    char type;
    scanf("%c", &type);
    shape_t * shape = &shapes[i];
    shape->id = i + 1;
    shape->type = type;
    if (type == 'r') {
      rectangle_t * rect = &shape->shape.rectangle;
      scanf("%lf %lf %lf %lf\n",
            &rect->left.x,  &rect->left.y,
            &rect->right.x, &rect->right.y);
    } else if (type == 'c') {
      circle_t * circle = &shape->shape.circle;
      scanf("%lf %lf %lf\n",
            &circle->center.x, &circle->center.y,
            &circle->radius);
    } else if (type == 't') {
      triangle_t * triangle = &shape->shape.triangle;
      scanf("%lf %lf %lf %lf %lf %lf\n",
            &triangle->points[0].x, &triangle->points[0].y,
            &triangle->points[1].x, &triangle->points[1].y,
            &triangle->points[2].x, &triangle->points[2].y);
    } else if (type == '*') {
      break;
    }
  }
  int point_i = 1;
  for (; 1; point_i++) {
    point_t point;
    scanf("%lf %lf\n", &point.x, &point.y);
    if (fabs(point.x - 9999.9) < 0.00001 &&
        fabs(point.y - 9999.9) < 0.00001) {
      break;
    }
    int is_in_any_shape = 0;
    int len = i;
    i = 0;
    for (; i < len; i++) {
      shape_t * shape = &shapes[i];
      int is_in_shape = 0;
      if (shape->type == 'r') {
        rectangle_t * rectangle = &shape->shape.rectangle;
        is_in_shape = (point.x > rectangle->left.x &&
                       point.x < rectangle->right.x &&
                       point.y < rectangle->left.y &&
                       point.y > rectangle->right.y);
      } else if (shape->type == 'c') {
        circle_t * circle = &shape->shape.circle;
        is_in_shape = (pow(fabs(point.x - circle->center.x), 2) +
                       pow(fabs(point.y - circle->center.y), 2) <
                       pow(circle->radius, 2));
      } else if (shape->type == 't') {
        triangle_t * triangle = &shape->shape.triangle;
        point_t * points = triangle->points;
        is_in_shape = (area(&point, &points[0], &points[1]) +
                       area(&point, &points[1], &points[2]) +
                       area(&point, &points[0], &points[2]) -
                       area(&points[0], &points[1], &points[2]) < 0.00001);
      } else if (shape->type == '*') {
        break;
      }
      if (is_in_shape) {
        is_in_any_shape = 1;
        printf("Point %d is contained in figure %d\n",
               point_i, shape->id);
      }
    }
    if (!is_in_any_shape) {
      printf("Point %d is not contained in any figure\n",
             point_i);
    }
  }
  return 0;
}
