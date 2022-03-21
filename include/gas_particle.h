#pragma once

#include "cinder/gl/gl.h"
using glm::vec2;

namespace idealgas {

/**
 * The particle inside the containers.
 */
    class GasParticle {
    public:
        GasParticle();
        GasParticle(float, float);
        GasParticle(vec2);

        GasParticle(const vec2 &position, char *color);

        vec2 GetPosition() const;
        float GetSize() const;

        vec2 GetVelocity() const;
        void SetVelocity(vec2);
        float getMass() const;
        void setMass(float mass);
        ci::Color GetColor() const;
        void SetColor(char *color);

        float GetSpeed() const;

        /**
         * Change velocity_ if particle collides with wall.
         * @param length The length of the container.
         * @param width The width of the container.
         */
        void CollideWithWall(float length, float width);

        /**
         * Change velocity_ if particle collides with another particle. Update the other particle at the same time.
         * @param particle the particle to check collision
         */
        void CollideWithParticle(GasParticle& particle);

        /**
         * Update the particle when AdvanceOneFrame is called in container. It would update the particle's
         * velocity while checking its collision with the walls.
         * @param length the length of the container
         * @param width the width of the container
         */
        void update(const float length, const float width);

    private:
        glm::vec2 position_;
        glm::vec2 velocity_;
        float size_;
        float mass_;
        ci::Color color_;
        const float kRedSize = 5.0;
        const float kRedMass = 10.0;
        const float kGreenSize = 15.0;
        const float kGreenMass = 20.0;
        const float kBlueSize = 30.0;
        const float kBlueMass = 15.0;
        const char* kRedColor = "red";
        const char* kGreenColor = "green";
        const char* kBlueColor = "blue";
        const float kMaxInitialSpeed = 5;
    };

}  // namespace idealgas
