#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "gas_container.h"
#include "histogram.h"

namespace idealgas {

/**
 * An app for visualizing the behavior of an ideal gas.
 */
class IdealGasApp : public ci::app::App {
 public:
  IdealGasApp();

  void draw() override;
  void update() override;

 private:
  GasContainer container_;

    void keyDown(ci::app::KeyEvent event);
    const float kHistogramSize = 250;
    const float kHistogramMargin = 50;
    const int kWindowLength = 1440;
    const int kWindowWidth = 960;

    const int kMargin = 100;
    const int kContainerLength = 1000;
    const int kContainerWidth = 800;
    Histogram red_histogram_;
    Histogram green_histogram_;
    Histogram blue_histogram_;
};

}  // namespace idealgas
