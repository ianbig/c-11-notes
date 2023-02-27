#include <stdio.h>
#include <stdlib.h>


#define POINTER_SZ 8

typedef struct Shape_t {
  void * vtable;
  int length;
} Shape;

typedef struct circle_vtable_memory {
  int (*getLength)(Shape*);
  double (*getArea)(Shape*);
} circle_vtable_memory;

typedef struct Circle_t {
  void * vtable;
  int length;
  int padding;
} Circle;

double calc_circle(Shape * circle) {
  return 3.14 * circle->length;
}

int get_circle_length(Shape * shape) {
  return shape->length;
}

int getLength(Shape * shape) {
  return shape->length;
}

Circle * allocate_circle(int length) {
  Circle * circle = malloc(sizeof(*circle));

  circle->vtable = malloc(sizeof(circle_vtable_memory));
  ((circle_vtable_memory*)(circle->vtable))->getLength = get_circle_length;
  ((circle_vtable_memory*)(circle->vtable))->getArea = calc_circle;

  circle->length = length;
  circle->padding = 200;

  return circle;
}

int main() {
  Shape * circle = allocate_circle(10);
  double circle_area =  ((circle_vtable_memory*)(circle->vtable))->getArea(circle);
  printf("Circle Area is %f\n", circle_area);
  printf("Circle padding: %d\n", *(int*)(((void*)circle) + 12));

  return 0;
}