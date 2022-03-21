#include "gas_container.h"
#include "gas_particle.h"


namespace idealgas {

using glm::vec2;

GasContainer::GasContainer() {
    for (int i = 0; i < kNumberOfParticle; i++) {
        particles_.emplace_back(float(rand())/float((RAND_MAX)) * kLength, float(rand())/float((RAND_MAX)) * kWidth);
    }
    needAccelerate = false;
}

void GasContainer::Display() const {
  // This function has a lot of magic numbers; be sure to design your code in a way that avoids this.
  ci::gl::color(ci::Color("white"));
  ci::gl::drawStrokedRect(ci::Rectf(vec2(0, 0), vec2(kLength, kWidth)));

  for (const GasParticle particle: particles_) {
      ci::gl::color(particle.GetColor());
      ci::gl::drawSolidCircle(particle.GetPosition(), particle.GetSize());
  }

}

void GasContainer::AdvanceOneFrame() {
    for (GasParticle& particle: particles_) {
        particle.update(kLength, kWidth);
        if (needAccelerate) {
            particle.update(kLength, kWidth);
        }
    }

    for (size_t indexOfParticles = 0; indexOfParticles < particles_.size(); indexOfParticles++) {
        for (size_t currentIndex = indexOfParticles + 1; currentIndex < particles_.size(); currentIndex++) {
            GasParticle &particle = particles_.at(indexOfParticles);
            particles_.at(currentIndex).CollideWithParticle(particle);
        }
    }
}

    void GasContainer::RemoveParticles() {
        particles_.clear();
    }

    void GasContainer::AddParticle(GasParticle particle) {
        particles_.push_back(particle);
    }

    std::vector<GasParticle> GasContainer::GetParticles() {
        return particles_;
    }

    void GasContainer::Accelerate() {
        needAccelerate = !needAccelerate;
    }

    void GasContainer::AddParticle(char* color) {
        particles_.emplace_back(vec2(float(rand())/float((RAND_MAX)) * kLength, float(rand())/float((RAND_MAX)) * kWidth), color);
    }

}  // namespace idealgas
