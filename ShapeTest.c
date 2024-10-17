#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <math.h>
using namespace std;

typedef struct Shape {
    struct ShapeVTable* vptr;
    string name;
} Shape;

typedef struct ShapeVTable {
    void (*print)(Shape* _this);
    void (*draw)(Shape* _this);
    double (*area)(Shape* _this);
} ShapeVTable;

void Shape_print(Shape* _this) {
    cout << _this->name << endl;
}

void Shape_draw(Shape* _this) {
    cout << "Base class does not draw" << endl;
}

double Shape_area(Shape* _this) {
    return 0.0;
}

ShapeVTable shape_vtable = {Shape_print, Shape_draw, Shape_area};

void Shape_init(Shape* _this, string name) {
    _this->vptr = &shape_vtable;
    _this->name = name;
}

typedef struct Circle {
    Shape base;
    int radius;
} Circle;

void Circle_draw(Shape* _this) {
    cout << "   ***   " << endl;
    cout << " *     * " << endl;
    cout << " *     * " << endl;
    cout << "   ***   " << endl;
}

double Circle_area(Shape* _this) {
    Circle* circle = (Circle*)_this;
    return M_PI * circle->radius * circle->radius;
}

void Circle_print(Shape* _this) {
    Circle* circle = (Circle*)_this;
    printf("%s(%d) : %.2f\n", circle->base.name.c_str(), circle->radius, Circle_area(_this));
}

ShapeVTable circle_vtable = {Circle_print, Circle_draw, Circle_area};

Circle* new_Circle(string name, int radius) {
    Circle* circle = (Circle*)malloc(sizeof(Circle));
    Shape_init(&circle->base, name);
    circle->base.vptr = &circle_vtable;
    circle->radius = radius;
    return circle;
}

typedef struct Square {
    Shape base;
    int side;
} Square;

void Square_draw(Shape* _this) {
    cout << "****" << endl;
    cout << "*  *" << endl;
    cout << "****" << endl;
}

double Square_area(Shape* _this) {
    Square* square = (Square*)_this;
    return square->side * square->side;
}

void Square_print(Shape* _this) {
    Square* square = (Square*)_this;
    printf("%s(%d) : %.2f\n", square->base.name.c_str(), square->side, Square_area(_this));
}

ShapeVTable square_vtable = {Square_print, Square_draw, Square_area};

Square* new_Square(string name, int side) {
    Square* square = (Square*)malloc(sizeof(Square));
    Shape_init(&square->base, name);
    square->base.vptr = &square_vtable;
    square->side = side;
    return square;
}

typedef struct Rectangle {
    Square base;
    int width;
} Rectangle;


void Rectangle_draw(Shape* _this) {
    cout << "****" << endl;
    cout << "*  *" << endl;
    cout << "*  *" << endl;
    cout << "*  *" << endl;
    cout << "****" << endl;
}

double Rectangle_area(Shape* _this) {
    Rectangle* rect = (Rectangle*)_this;
    return rect->base.side * rect->width;
}

void Rectangle_print(Shape* _this) {
    Rectangle* rect = (Rectangle*)_this;
    printf("%s(%d, %d) : %.2f\n", rect->base.base.name.c_str(), rect->base.side, rect->width, Rectangle_area(_this));
}

ShapeVTable rectangle_vtable = {Rectangle_print, Rectangle_draw, Rectangle_area};

Rectangle* new_Rectangle(string name, int side, int width) {
    Rectangle* rect = (Rectangle*)malloc(sizeof(Rectangle));
    Shape_init(&rect->base.base, name);
    rect->base.base.vptr = &rectangle_vtable;
    rect->base.side = side;
    rect->width = width;
    return rect;
}

typedef struct Triangle {
    Shape base;
    int base_length, height;
} Triangle;

void Triangle_draw(Shape* _this) {
    cout << "   *   " << endl;
    cout << "  * *  " << endl;
    cout << " *   * " << endl;
    cout << "*******" << endl;
}

double Triangle_area(Shape* _this) {
    Triangle* tri = (Triangle*)_this;
    return 0.5 * tri->base_length * tri->height;
}

void Triangle_print(Shape* _this) {
    Triangle* tri = (Triangle*)_this;
    printf("%s(%d, %d) : %.2f\n", tri->base.name.c_str(), tri->base_length, tri->height, Triangle_area(_this));
}

ShapeVTable triangle_vtable = {Triangle_print, Triangle_draw, Triangle_area};

Triangle* new_Triangle(string name, int base_length, int height) {
    Triangle* tri = (Triangle*)malloc(sizeof(Triangle));
    Shape_init(&tri->base, name);
    tri->base.vptr = &triangle_vtable;
    tri->base_length = base_length;
    tri->height = height;
    return tri;
}

void drawAll(Shape** shapes, int count) {
    for (int i = 0; i < count; i++) {
        shapes[i]->vptr->draw(shapes[i]);
    }
}

void printAll(Shape** shapes, int count) {
    for (int i = 0; i < count; i++) {
        shapes[i]->vptr->print(shapes[i]);
    }
}

double totalArea(Shape** shapes, int count) {
    double total = 0;
    for (int i = 0; i < count; i++) {
        total += shapes[i]->vptr->area(shapes[i]);
    }
    return total;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: ./main <arg1> <arg2>\n");
        return 1;
    }
    int arg1 = atoi(argv[1]);
    int arg2 = atoi(argv[2]);

    Shape* shapes[8];
    shapes[0] = (Shape*)new_Triangle("FirstTriangle", arg1, arg2);
    shapes[1] = (Shape*)new_Triangle("SecondTriangle", arg1 - 1, arg2 - 1);

    shapes[2] = (Shape*)new_Circle("FirstCircle", arg1);
    shapes[3] = (Shape*)new_Circle("SecondCircle", arg1 - 1);

    shapes[4] = (Shape*)new_Square("FirstSquare", arg1);
    shapes[5] = (Shape*)new_Square("SecondSquare", arg1 - 1);

    shapes[6] = (Shape*)new_Rectangle("FirstRectangle", arg1, arg2);
    shapes[7] = (Shape*)new_Rectangle("SecondRectangle", arg1 - 1, arg2 - 1);
    printAll(shapes, 8);
    drawAll(shapes, 8);
    printf("Total : %.2f\n", totalArea(shapes, 8));

    for (int i = 0; i < 8; i++) {
        free(shapes[i]);
    }

    return 0;
}

