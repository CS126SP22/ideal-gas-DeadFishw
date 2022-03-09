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
        GasParticle(vec2, char*);
        vec2 GetPosition() const;
        float GetSize() const;
        char* GetColor() const;

        /**
         * Update the particle by one frame.
         */
        void AdvanceOneFrame();

        float GetSpeed() const;

        /**
         * Change velocity_ if particle collides with wall; do nothing otherwise.
         * @param length The length of the container.
         * @param width The width of the container.
         */
        void CollideWithWall(float length, float width);

        /**
         * Change velocity_ if particle collides with another particle.
         * @param particle the particle to check collision
         */
        void CollideWithParticle(GasParticle& particle);
        void SetVelocity(vec2);
        vec2 GetVelocity();
        vec2 GetPosition();
        float GetSize();

        void update(const float d, const float d1);

    private:
        glm::vec2 position_;
        glm::vec2 velocity_;
        float size_;
    };

}  // namespace idealgas
