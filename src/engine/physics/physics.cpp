#include "chipmunk/chipmunk.h"
#include "physics_hidden.h"


namespace physics {

    static cpSpace* space = nullptr;

    void init() {
        space = cpSpaceNew();
    }

    void release() {
        cpSpaceFree(space);
    }

    void setGravity(const cpVect& v) {
        cpSpaceSetGravity(space, v);
    }

    void addBody(Body* body) {
        cpSpaceAddBody(space, body->body);
    }

    void addShape(Shape* shape) {
        cpSpaceAddShape(space, shape->shape);
    }

    void removeBody(Body* body) {
        cpSpaceRemoveBody(space, body->body);
    }

    void removeShape(Shape* shape) {
        cpSpaceRemoveShape(space, shape->shape);
    }

    float toBoxMoment(float mass, float width, float height) {
        return cpMomentForBox(mass, width, height);
    }

    float toCircleMoment(float mass, float radius1, float radius2, cpVect offset) {
        return cpMomentForCircle(mass, radius1, radius2, offset);
    }

    // Hidden Functions
    cpSpace* getSpace() {
        return space;
    }
}