#pragma once

#include "cinder/gl/gl.h"
#include "gas_particle.h"

using glm::vec2;

namespace idealgas {

/**
 * The container in which all of the gas particles are contained. This class
 * stores all of the particles and updates them on each frame of the simulation.
 */
class GasContainer {
 public:
  /**
   * Build a container with a certain
   */
  GasContainer();

  std::vector<GasParticle> GetParticles();

  /**
   * Displays the container walls and the current positions of the particles.
   */
  void Display() const;

  /**
   * Updates the positions and velocities of all particles (based on the rules
   * described in the assignment documentation).
   */
  void AdvanceOneFrame();

  /**
   * Toggle if the container is in accelarate mode
   */
  void Accelerate();

  /**
   * Remove all particles in the container.
   */
  void RemoveParticles();

  /**
   * Add a particle into the container
   * @param particle the particle to be added
   */
  void AddParticle(GasParticle particle);

  void AddParticle(char *particle);

private:
    const float kLength = 1000.0;
    const float kWidth = 800.0;
    const int kNumberOfParticle = 1;
    bool needAccelerate;
    std::vector<GasParticle> particles_;


};

}  // namespace idealgas
