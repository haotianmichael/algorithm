#include <iostream>


using namespace std;



typedef struct {
    
    float x, y, z;
    
}Point;

Point global;
Point foobar() {

    Point local;
    Point *heap = new Point;
    *heap = local;

    delete heap;
    return local;
}
