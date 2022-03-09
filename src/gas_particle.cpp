#include <gas_particle.h>
using glm::vec2;

namespace idealgas {
    GasParticle::GasParticle() {

    }

    GasParticle::GasParticle(float x, float y) {
        size_ = 5;
        position_ = vec2(x, y);
        velocity_ = vec2(float(rand())/float((RAND_MAX)) * 5, float(rand())/float((RAND_MAX)) * 5);

    }

    GasParticle::GasParticle(vec2 position) {
        position_ = position;
        velocity_ = vec2(float(rand())/float((RAND_MAX)) * 5, float(rand())/float((RAND_MAX)) * 5);
        size_ = 5;
    }

    void GasParticle::CollideWithWall(float length, float width) {
        if (position_.x - size_ > 0 && position_.x + size_ < length) {
            if ((velocity_.y < 0 && position_.y - size_ < 0) ||
                (velocity_.y > 0 && position_.y + size_ > width)) {
                velocity_ = vec2(velocity_.x, -velocity_.y);
            }
        }
        if ((velocity_.x < 0 && position_.x - size_ < 0) ||
            (velocity_.x > 0 && position_.x + size_ > length)) {
            velocity_ = vec2(-velocity_.x, velocity_.y);
        }
    }

    void GasParticle::CollideWithParticle(GasParticle& particle) {
        vec2 pos = position_ - particle.position_;
        vec2 vel = velocity_ - particle.velocity_;
        vec2 negPos = - position_ + particle.position_;
        vec2 negVel = - velocity_ + particle.velocity_;
        if (pos.x * pos.x + pos.y * pos.y <= 4 * size_ * size_) {
            if (dot(vel, pos) < 0) {
                velocity_ = velocity_ -
                            dot(vel, pos) /
                            (pos.x * pos.x + pos.y * pos.y) * (pos);
                particle.velocity_ = particle.velocity_ -
                        dot(negVel, negPos) /
                        (negPos.x * negPos.x + negPos.y * negPos.y) * (negPos);
            }
        }
    }

    void GasParticle::SetVelocity(vec2 velocity) {
        velocity_ = velocity;
    }

    vec2 GasParticle::GetVelocity() {
        return velocity_;
    }

    vec2 GasParticle::GetPosition() const {
        return position_;
    }

    float GasParticle::GetSize() const {
        return size_;
    }

    void GasParticle::update(const float length, const float width) {
        position_ += velocity_;
        CollideWithWall(length, width);
    }
}  // namespace idealgas

