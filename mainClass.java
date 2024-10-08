abstract class Shape {
    String name;

    Shape(String name) {
        this.name = name;
    }

    abstract void print();
    abstract void draw();
    abstract double area();
}

class Circle extends Shape {
    int radius;

    Circle(String name, int radius) {
        super(name);
        this.radius = radius;
    }

    void print() {
        System.out.printf("%s(%d) : %.2f\n", name, radius, area());
    }

    void draw() {
        System.out.println("   ***   ");
        System.out.println(" *     * ");
        System.out.println(" *     * ");
        System.out.println("   ***   ");
    }
    double area() {
        return Math.PI * radius * radius;
    }
}

class Square extends Shape {
    int side;

    Square(String name, int side) {
        super(name);
        this.side = side;
    }

    void print() {
        System.out.printf("%s(%d) : %.2f\n", name, side, area());
    }

    void draw(){
        System.out.println("****");
        System.out.println("*  *");
        System.out.println("****");
    }
    double area() {
        return side * side;
    }
}

class Triangle extends Shape {
    int base, height;

    Triangle(String name, int base, int height) {
        super(name);
        this.base = base;
        this.height = height;
    }

    void print() {
        System.out.printf("%s(%d, %d) : %.2f\n", name, base, height, area());
    }

    void draw() {
        System.out.println("   *   ");
        System.out.println("  * *  ");
        System.out.println(" *   * ");
        System.out.println("*******");
    }

    double area() {
        return 0.5 * base * height;
    }
}

class Rectangle extends Square {
    int width;

    Rectangle(String name, int side, int width) {
        super(name, side);
        this.width = width;
    }

    void print() {
        System.out.printf("%s(%d, %d) : %.2f\n", name, side, width, area());
    }

    void draw() {
        System.out.println("****");
        System.out.println("*  *");
        System.out.println("*  *");
        System.out.println("*  *");
        System.out.println("****");
    }

    double area() {
        return width * side;
    }
}

class ListNode {
    Shape shape;
    ListNode next;

    ListNode(Shape shape) {
        this.shape = shape;
        this.next = null;
    }
}

class Picture {
    ListNode head;

    Picture() {
        head = null;
    }

    void add(Shape sh) {
        ListNode temp = new ListNode(sh);
        temp.next = head;
        head = temp;
    }

    void printAll() {
        for (ListNode temp = head; temp != null; temp = temp.next) {
            temp.shape.print();
        }
    }

    void drawAll() {
        for (ListNode temp = head; temp != null; temp = temp.next) {
            temp.shape.draw();
        }
    }

    double totalArea() {
        double total = 0;
        for (ListNode temp = head; temp != null; temp = temp.next) {
            total += temp.shape.area();
        }
        return total;
    }
}

public class mainClass {
    public static void main(String[] args) {
        int arg1 = Integer.parseInt(args[0]);
        int arg2 = Integer.parseInt(args[1]);

        Picture picture = new Picture();

        picture.add(new Triangle("FirstTriangle", arg1, arg2));
        picture.add(new Triangle("SecondTriangle", arg1 - 1, arg2 - 1));

        picture.add(new Circle("FirstCircle", arg1));
        picture.add(new Circle("SecondCircle", arg1 - 1));

        picture.add(new Square("FirstSquare", arg1));
        picture.add(new Square("SecondSquare", arg1 - 1));

        picture.add(new Rectangle("FirstRectangle", arg1, arg2));
        picture.add(new Rectangle("SecondRectangle", arg1 - 1, arg2 - 1));

        picture.printAll();
        picture.drawAll();
        System.out.printf("Total : %.2f\n", picture.totalArea());
    }
}
