#include "chipmunk/chipmunk.h"
#include "chipmunk/chipmunk_types.h"
#include "physics_hidden.h"


namespace physics {

    void Shape::initBox(Body* body, float width, float height) {
        this->body = body;
        this->shape = cpBoxShapeNew(this->body->body, width, height, 1.0f);
    }

    void Shape::initCircle(Body* body, float radius, const cpVect& offset) {
        this->body = body;
        this->shape = cpCircleShapeNew(this->body->body, radius, offset);
    }

    void Shape::release() {
        cpShapeFree(this->shape);
        this->body = nullptr;
    }

    void Shape::setFriction(float friction) {
        cpShapeSetFriction(this->shape, friction);
    }

    float Shape::getFriction() {
        return cpShapeGetFriction(this->shape);
    }

    void Shape::setSensor(bool sensor) {
        cpShapeSetSensor(this->shape, sensor);
    }

    bool Shape::isSensor() {
        return cpShapeGetSensor(this->shape);
    }

    void Shape::setElasticity(float elasticity) {
        cpShapeSetElasticity(this->shape, elasticity);
    }

    float Shape::getElasticity() {
        return cpShapeGetElasticity(this->shape);
    }
    
    void Shape::setSurfaceVelocity(const cpVect& v) {
        cpShapeSetSurfaceVelocity(this->shape, v);
    }

    cpVect Shape::getSurfaceVelocity() {
        return cpShapeGetSurfaceVelocity(this->shape);
    }

}