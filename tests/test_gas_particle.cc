#include <catch2/catch.hpp>

#include <gas_container.h>

using idealgas::GasContainer;

double static kThreshold = 0.001;

TEST_CASE("Test CollideWithParticle") {
    SECTION("Test that two particles collide correctly") {
        GasContainer container;
        container.RemoveParticles();
        idealgas::GasParticle particle1 = idealgas::GasParticle(vec2(9.9, 50.0));
        particle1.SetVelocity(vec2(0.1, 0));
        idealgas::GasParticle particle2 = idealgas::GasParticle(vec2(11.5, 51.4));
        particle2.SetVelocity(vec2(-0.1, 0));
        container.AddParticle(particle1);
        container.AddParticle(particle2);
        container.AdvanceOneFrame();
        container.AdvanceOneFrame();
        REQUIRE(container.GetParticles().at(0).GetVelocity().x < kThreshold);
        REQUIRE(container.GetParticles().at(0).GetVelocity().y + 0.1 < kThreshold);
        REQUIRE(container.GetParticles().at(1).GetVelocity().x < kThreshold);
        REQUIRE(container.GetParticles().at(1).GetVelocity().y - 0.1 < kThreshold);
    }
    SECTION("Test that two particles not colliding stay the same") {
        GasContainer container;
        container.RemoveParticles();
        idealgas::GasParticle particle1 = idealgas::GasParticle(vec2(19.9, 50.0));
        particle1.SetVelocity(vec2(0.1, 0));
        idealgas::GasParticle particle2 = idealgas::GasParticle(vec2(21.5, 21.4));
        particle2.SetVelocity(vec2(-0.1, 0));
        container.AddParticle(particle1);
        container.AddParticle(particle2);
        container.AdvanceOneFrame();
        container.AdvanceOneFrame();
        REQUIRE(container.GetParticles().at(0).GetVelocity().x - 0.1 < kThreshold);
        REQUIRE(container.GetParticles().at(0).GetVelocity().y  < kThreshold);
        REQUIRE(container.GetParticles().at(1).GetVelocity().x + 0.1 < kThreshold);
        REQUIRE(container.GetParticles().at(1).GetVelocity().y < kThreshold);
    }
}

TEST_CASE("Test CollideWithWall") {
    GasContainer container;
    container.RemoveParticles();
    SECTION("Test that particle hit right wall correctly") {
        idealgas::GasParticle particle1 = idealgas::GasParticle(vec2(598, 50));
        particle1.SetVelocity(vec2(3, 0));
        container.AddParticle(particle1);
        container.AdvanceOneFrame();
        container.AdvanceOneFrame();
        REQUIRE(container.GetParticles().at(0).GetVelocity().x + 3 < kThreshold);
        REQUIRE(container.GetParticles().at(0).GetVelocity().y< kThreshold);
    }
    SECTION("Test that particle hit left wall correctly") {
        idealgas::GasParticle particle2 = idealgas::GasParticle(vec2(3, 50));
        particle2.SetVelocity(vec2(-3.0, 0));
        container.AddParticle(particle2);
        container.AdvanceOneFrame();
        container.AdvanceOneFrame();
        REQUIRE(container.GetParticles().at(0).GetVelocity().x - 3 < kThreshold);
        REQUIRE(container.GetParticles().at(0).GetVelocity().y< kThreshold);
    }
    SECTION("Test that particle hit left wall correctly") {
        idealgas::GasParticle particle3 = idealgas::GasParticle(vec2(598, 5));
        particle3.SetVelocity(vec2(0, -3));
        container.AddParticle(particle3);
        container.AdvanceOneFrame();
        container.AdvanceOneFrame();
        REQUIRE(container.GetParticles().at(0).GetVelocity().x < kThreshold);
        REQUIRE(container.GetParticles().at(0).GetVelocity().y - 3 < kThreshold);
    }
    SECTION("Test that particle hit top wall correctly") {
        idealgas::GasParticle particle4 = idealgas::GasParticle(vec2(598, 398));
        particle4.SetVelocity(vec2(0, 3));
        container.AddParticle(particle4);
        container.AdvanceOneFrame();
        container.AdvanceOneFrame();
        REQUIRE(container.GetParticles().at(0).GetVelocity().x < kThreshold);
        REQUIRE(container.GetParticles().at(0).GetVelocity().y + 3 < kThreshold);
    }
}