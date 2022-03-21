#include <gas_particle.h>
using glm::vec2;

namespace idealgas {
    GasParticle::GasParticle() {

    }

    GasParticle::GasParticle(float x, float y) {
        size_ = kMaxInitialSpeed;
        color_ = ci::Color("red");
        position_ = vec2(x, y);
        velocity_ = vec2(float(rand())/float((RAND_MAX)) * kMaxInitialSpeed,
                                        float(rand())/float((RAND_MAX)) * kMaxInitialSpeed);

    }

    GasParticle::GasParticle(vec2 position) {
        position_ = position;
        velocity_ = vec2(float(rand())/float((RAND_MAX)) * kMaxInitialSpeed,
                                        float(rand())/float((RAND_MAX)) * kMaxInitialSpeed);
        size_ = kRedSize;
        mass_ = kRedMass;
        color_ = ci::Color(kRedColor);
    }

    void GasParticle::CollideWithWall(float length, float width) {
        if ((velocity_.y < 0 && position_.y - size_ < 0) ||
            (velocity_.y > 0 && position_.y + size_ > width)) {
            velocity_ = vec2(velocity_.x, -velocity_.y);
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
        if (pos.x * pos.x + pos.y * pos.y <= (size_ + particle.size_) * (size_ + particle.size_) && dot(vel, pos) < 0) {
            velocity_ =  velocity_ -
                    2 * particle.mass_ / (particle.mass_ + mass_) * dot(vel, pos) /
                    (pos.x * pos.x + pos.y * pos.y) * (pos);
            particle.velocity_ = particle.velocity_ -
                    2 * mass_ / (particle.mass_ + mass_) * dot(negVel, negPos) /
                    (negPos.x * negPos.x + negPos.y * negPos.y) * (negPos);
        }
    }

    void GasParticle::SetVelocity(vec2 velocity) {
        velocity_ = velocity;
    }

    vec2 GasParticle::GetVelocity() const {
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

    float GasParticle::getMass() const {
        return mass_;
    }

    void GasParticle::setMass(float mass) {
        mass_ = mass;
    }

    ci::Color GasParticle::GetColor() const {
        return color_;
    }

    void GasParticle::SetColor(char* color) {
        color_ = ci::Color(color);
    }

    GasParticle::GasParticle(const vec2 &position, char *color) {
        position_ = position;
        position_ = position;
        velocity_ = vec2(float(rand())/float((RAND_MAX)) * kMaxInitialSpeed,
                         float(rand())/float((RAND_MAX)) * kMaxInitialSpeed);
        if (!strcmp(color,kRedColor)) {
            color_ = ci::Color(color);
            size_ = kRedSize;
            mass_ = kRedMass;
        } else if (!strcmp(color,kGreenColor)) {
            color_ = ci::Color(color);
            size_ = kGreenSize;
            mass_ = kGreenMass;
        } else {
            color_ = ci::Color(kBlueColor);
            size_ = kBlueSize;
            mass_ = kBlueMass;
        }
    }

    float GasParticle::GetSpeed() const {
        return sqrt(velocity_.x * velocity_.x + velocity_.y * velocity_.y);
    }

}  // namespace idealgas

