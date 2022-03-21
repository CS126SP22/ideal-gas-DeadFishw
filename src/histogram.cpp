#include <cinder/gl/gl.h>
#include "histogram.h"

namespace idealgas {

    Histogram::Histogram(ci::Color color, glm::vec2 position, float size){
        color_ = color;
        position_ = position;
        size_ = size;
    }

    void Histogram::GenerateHistogram(const std::vector<GasParticle> &particles) {
        column_values_.clear();
        num_particles_column_.clear();
        particles_.clear();
        for (auto& particle: particles) {
            if (particle.GetColor() == color_) {
                particles_.push_back(particle);
            }
        }
        if (particles.size() == 0) {
            return;
        }
        if (particles_.size() > 1) {
                float highest_speed;
                if (particles_.size() == 0) {
                    highest_speed = 0;
                }
                float highest = 0;
                for (const GasParticle particle: particles_) {
                    if (particle.GetSpeed() > highest) {
                        highest_speed = particle.GetSpeed();
                    }
                }
                speed_diff_ = highest_speed / 4;
                num_of_columns_ = 4;
        } else {
                speed_diff_ = 20;
                num_of_columns_ = 1;
        }
        for(size_t column = 0; column < num_of_columns_; ++column) {
            column_values_.push_back(column * speed_diff_);
        }
        for(size_t range = 0; range < column_values_.size() - 1; ++range) {
            size_t numberOfParticles = 0;
            for(size_t particle = 0; particle < particles_.size(); ++particle) {
                if(particles_.at(particle).GetSpeed() >= column_values_.at(range) &&
                   particles_.at(particle).GetSpeed() < column_values_.at(range + 1)) {
                    ++numberOfParticles;
                }
            }
            num_particles_column_.push_back(numberOfParticles);
        }
    }

    void Histogram::Draw() {
        ci::gl::color(borderColor);
        ci::gl::drawStrokedRect(ci::Rectf(position_,
                                          position_ + vec2(size_, size_)), lineWidth);

        if(particles_.size() > 1) {
            float width = (size_ / num_of_columns_);
            for(size_t index = 0; index < num_particles_column_.size(); ++index) {
                float height = num_particles_column_.at(index) * (size_ / particles_.size());
                ci::gl::color(color_);
                ci::gl::drawSolidRect(
                        ci::Rectf(
                        vec2(position_.x + (index * width),position_.y + size_ - height),
                        vec2(position_.x + ((index + 1) * width),position_.y + size_)));
            }
        }
        else if(particles_.size() == 1) {
            float width = size_;
            ci::gl::color(color_);
            ci::gl::drawSolidRect(ci::Rectf(
                    vec2(position_.x,
                         position_.y),
                    vec2(position_.x + width,
                         position_.y + size_)));
        }
        ci::gl::drawString("velocity",
                           position_ + vec2(size_ - 80, size_ + 8), ci::Color("white"), ci::Font("Arial", 30.0f));
        ci::gl::drawString("freq",
                           position_ - vec2(50, 0), ci::Color("white"), ci::Font("Arial", 30.0f));
    }

    Histogram::Histogram() {

    }



} // namespace idealgas
