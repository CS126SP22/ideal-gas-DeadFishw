#include "gas_simulation_app.h"

namespace idealgas {

    IdealGasApp::IdealGasApp() {
        ci::app::setWindowSize(kWindowSize, kWindowSize);
    }

    void IdealGasApp::draw() {
        ci::Color background_color("black");
        ci::gl::clear(background_color);

        container_.Display();
    }

    void IdealGasApp::update() {
        container_.AdvanceOneFrame();
    }

    void IdealGasApp::keyDown(ci::app::KeyEvent event) {
        switch (event.getCode()) {
            case ci::app::KeyEvent::KEY_DELETE:
                container_.Accelerate();
                break;
        }
    }
}// namespace idealgas