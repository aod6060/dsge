#ifndef PHYSICS_H
#define PHYSICS_H

#include "chipmunk/chipmunk.h"
#include "chipmunk/chipmunk_types.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace physics {

    enum BodyType {
        BT_STATIC = 0,
        BT_KINESTETIC,
        BT_DYNAMIC,
        BT_MAX_NUM
    };

    struct Body {
        BodyType type;
        float mass;
        float moment;
        cpBody* body = nullptr;

        void init();
        void release();

        void setPosition(const cpVect& p);
        cpVect getPosition();

        void setAngle(float angle);
        float getAngle();

        void setVelocity(const cpVect& p);
        cpVect getVelocity();

        void setCenterOfGravity(const cpVect& cog);
        cpVect getCenterOfGravity();

        void setForce(const cpVect& force);
        cpVect getForce();

        void setAngularVelocity(float angularVelocity);
        float getAngularVelocity();

        void setTorque(float torque);
        float getTorque();

        cpVect getRotation();

        void activate();
        void sleep();
        bool isSleeping();

        void setBodyType(const BodyType& type);
        void setMass(float mass);
        void setMoment(float moment);
    };

    struct Shape {
        cpShape* shape = nullptr;
        Body* body = nullptr;

        void initBox(Body* body, float width, float height);
        void initCircle(Body* body, float radius, const cpVect& offset);

        void release();

        void setFriction(float friction);
        float getFriction();

        void setSensor(bool sensor);
        bool isSensor();

        void setElasticity(float elasticity);
        float getElasticity();

        void setSurfaceVelocity(const cpVect& v);
        cpVect getSurfaceVelocity();
        
    };

    void init();
    void release();

    void setGravity(const cpVect& v);

    void addBody(Body* body);
    void addShape(Shape* shape);

    void removeBody(Body* body);
    void removeShape(Shape* shape);

    float toBoxMoment(float mass, float width, float height);
    float toCircleMoment(float mass, float radius1, float radius2, cpVect offset);
}

#endif