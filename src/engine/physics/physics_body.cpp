#include "chipmunk/chipmunk.h"
#include "physics.h"
#include "physics_hidden.h"

namespace physics {


    void Body::init() {
        if(this->type == BodyType::BT_STATIC) {
            this->body = cpBodyNewStatic();
        } else if(this->type == BodyType::BT_KINESTETIC) {
            this->body = cpBodyNewKinematic();
        } else if(this->type == BodyType::BT_DYNAMIC) {
            this->body = cpBodyNew(this->mass, this->moment);
        }
    }

    void Body::release() {
        cpBodyFree(this->body);
    }

    void Body::setPosition(const cpVect& p) {
        cpBodySetPosition(this->body, p);
    }

    cpVect Body::getPosition() {
        return cpBodyGetPosition(this->body);
    }

    void Body::setAngle(float angle) {
        cpBodySetAngle(body, angle);
    }

    float Body::getAngle() {
        return cpBodyGetAngle(this->body);
    }

    void Body::setVelocity(const cpVect& p) {
        cpBodySetVelocity(this->body, p);
    }

    cpVect Body::getVelocity() {
        return cpBodyGetVelocity(this->body);
    }

    void Body::setCenterOfGravity(const cpVect& cog) {
        cpBodySetCenterOfGravity(this->body, cog);
    }

    cpVect Body::getCenterOfGravity() {
        return cpBodyGetCenterOfGravity(this->body);
    }

    void Body::setForce(const cpVect& force) {
        cpBodySetForce(this->body, force);
    }

    cpVect Body::getForce() {
        return cpBodyGetForce(this->body);
    }

    void Body::setAngularVelocity(float angularVelocity) {
        cpBodySetAngularVelocity(this->body, angularVelocity);
    }

    float Body::getAngularVelocity() {
        return cpBodyGetAngularVelocity(this->body);
    }

    void Body::setTorque(float torque) {
        cpBodySetTorque(this->body, torque);
    }

    float Body::getTorque() {
        return cpBodyGetTorque(this->body);
    }

    cpVect Body::getRotation() {
        return cpBodyGetRotation(this->body);
    }

    void Body::activate() {
        cpBodyActivate(this->body);
    }

    void Body::sleep() {
        cpBodySleep(this->body);
    }

    bool Body::isSleeping() {
        return cpBodyIsSleeping(this->body);
    }

    void Body::setBodyType(const BodyType& type) {
        this->type = type;
    }

    void Body::setMass(float mass) {
        this->mass = mass;
    }

    void Body::setMoment(float moment) {
        this->moment = moment;
    }
}