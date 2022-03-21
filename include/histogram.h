#pragma once

#include "cinder/gl/gl.h"
#include "gas_particle.h"
#include <cinder/Color.h>
#include <math.h>


namespace idealgas {

    class Histogram {
    private:

        std::vector<GasParticle> particles_;
        float FindHighestSpeed();

        glm::vec2 position_;
        float size_;
        ci::Color color_;
        ci::Color borderColor = ci::Color("white");
        float lineWidth = 1;

        float speed_diff_;
        std::vector<float> column_values_;
        std::vector<size_t> num_particles_column_;
        size_t num_of_columns_;

    public:
        Histogram();
        Histogram(cinder::Color color, vec2 top_left_corner_position,
                  float length);

        /**
         * generate the histogram given the particles
         * @param GasParticles
         */
        void GenerateHistogram(const std::vector<GasParticle> &GasParticles);

        /**
         * draw the histogram
         */
        void Draw();
    };

} // namespace idealgas