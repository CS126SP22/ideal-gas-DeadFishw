#include "gas_simulation_app.h"

namespace idealgas {

    IdealGasApp::IdealGasApp() {
        ci::app::setWindowSize(kWindowLength, kWindowWidth);
        red_histogram_ = Histogram(cinder::Color("red"),
                                   vec2(1000, 800) +
                                   vec2(kMargin, -800),
                                   kHistogramSize);
        green_histogram_ = Histogram(cinder::Color("green"),
                                   vec2(1000, 800) +
                                    vec2(kMargin, -800 + kHistogramSize + kHistogramMargin),
                                   kHistogramSize);
        blue_histogram_ = Histogram(cinder::Color("blue"),
                                   vec2(1000, 800) +
                                   vec2(kMargin, -800 + 2 * ( kHistogramSize + kHistogramMargin)),
                                   kHistogramSize);
    }

    void IdealGasApp::draw() {
        ci::Color background_color("black");
        ci::gl::clear(background_color);
        red_histogram_.Draw();
        green_histogram_.Draw();
        blue_histogram_.Draw();
        container_.Display();
    }

    void IdealGasApp::update() {
        container_.AdvanceOneFrame();
        red_histogram_.GenerateHistogram(container_.GetParticles());
        green_histogram_.GenerateHistogram(container_.GetParticles());
        blue_histogram_.GenerateHistogram(container_.GetParticles());
    }

    void IdealGasApp::keyDown(ci::app::KeyEvent event) {
        switch (event.getCode()) {
            case ci::app::KeyEvent::KEY_DELETE:
                container_.Accelerate();
                break;
            case ci::app::KeyEvent::KEY_r:
                container_.AddParticle("red");
                break;
            case ci::app::KeyEvent::KEY_b:
                container_.AddParticle("blue");
                break;
            case ci::app::KeyEvent::KEY_g:
                container_.AddParticle("green");
                break;
        }
    }
}// namespace idealgas