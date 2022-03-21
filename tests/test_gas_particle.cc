#include <catch2/catch.hpp>

#include <gas_container.h>

using idealgas::GasContainer;

double static kThreshold = 0.001;

TEST_CASE("Test that particles are updated based on velocity") {
    GasContainer container;
    container.RemoveParticles();
    idealgas::GasParticle particle1 = idealgas::GasParticle(vec2(19.9, 20.0));
    particle1.SetVelocity(vec2(0.1, 0));
    container.AddParticle(particle1);
    container.AdvanceOneFrame();
    REQUIRE(container.GetParticles().at(0).GetPosition().x == 20.0);
    REQUIRE(container.GetParticles().at(0).GetPosition().y == 20.0);
}

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
        REQUIRE(abs(container.GetParticles().at(0).GetVelocity().x) < kThreshold);
        REQUIRE(abs(container.GetParticles().at(0).GetVelocity().y + 0.1) < kThreshold);
        REQUIRE(abs(container.GetParticles().at(1).GetVelocity().x) < kThreshold);
        REQUIRE(abs(container.GetParticles().at(1).GetVelocity().y - 0.1) < kThreshold);
    }
    SECTION("Test that two particles with different mass collide good") {
        GasContainer container;
        container.RemoveParticles();
        idealgas::GasParticle particle1 = idealgas::GasParticle(vec2(11, 45.0), "red");
        particle1.SetVelocity(vec2(9, 5));
        idealgas::GasParticle particle2 = idealgas::GasParticle(vec2(60, 43), "blue");
        particle2.SetVelocity(vec2(-5, 7));
        container.AddParticle(particle1);
        container.AddParticle(particle2);
        container.AdvanceOneFrame();
        container.AdvanceOneFrame();
        REQUIRE(abs(container.GetParticles().at(0).GetVelocity().x + 7.8) < kThreshold);
        REQUIRE(abs(container.GetParticles().at(0).GetVelocity().y - 5)  < kThreshold);
        REQUIRE(abs(container.GetParticles().at(1).GetVelocity().x - 6.2) < kThreshold);
        REQUIRE(abs(container.GetParticles().at(1).GetVelocity().y - 7) < kThreshold);
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
        REQUIRE(abs(container.GetParticles().at(0).GetVelocity().x - 0.1) < kThreshold);
        REQUIRE(abs(container.GetParticles().at(0).GetVelocity().y)  < kThreshold);
        REQUIRE(abs(container.GetParticles().at(1).GetVelocity().x + 0.1) < kThreshold);
        REQUIRE(abs(container.GetParticles().at(1).GetVelocity().y) < kThreshold);
    }
    SECTION("Test that two particles not colliding with different radii stay the same") {
        GasContainer container;
        container.RemoveParticles();
        idealgas::GasParticle particle1 = idealgas::GasParticle(vec2(19.9, 50.0), "red");
        particle1.SetVelocity(vec2(0.1, 0));
        idealgas::GasParticle particle2 = idealgas::GasParticle(vec2(21.5, 150.4), "blue");
        particle2.SetVelocity(vec2(-0.1, 0));
        container.AddParticle(particle1);
        container.AddParticle(particle2);
        container.AdvanceOneFrame();
        container.AdvanceOneFrame();
        REQUIRE(abs(container.GetParticles().at(0).GetVelocity().x - 0.1) < kThreshold);
        REQUIRE(abs(container.GetParticles().at(0).GetVelocity().y)  < kThreshold);
        REQUIRE(abs(container.GetParticles().at(1).GetVelocity().x + 0.1) < kThreshold);
        REQUIRE(abs(container.GetParticles().at(1).GetVelocity().y) < kThreshold);
    }
    SECTION("Test that two particles collide correctly with container more than 2 particles") {
        GasContainer container;
        container.RemoveParticles();
        idealgas::GasParticle particle1 = idealgas::GasParticle(vec2(9.9, 50.0));
        particle1.SetVelocity(vec2(0.1, 0));
        idealgas::GasParticle particle2 = idealgas::GasParticle(vec2(11.5, 51.4));
        particle2.SetVelocity(vec2(-0.1, 0));
        idealgas::GasParticle particle3 = idealgas::GasParticle(vec2(50.5, 51.4));
        particle3.SetVelocity(vec2(-0.1, 0));
        container.AddParticle(particle1);
        container.AddParticle(particle2);
        container.AddParticle(particle3);
        container.AdvanceOneFrame();
        container.AdvanceOneFrame();
        REQUIRE(abs(container.GetParticles().at(0).GetVelocity().x) < kThreshold);
        REQUIRE(abs(container.GetParticles().at(0).GetVelocity().y + 0.1) < kThreshold);
        REQUIRE(abs(container.GetParticles().at(1).GetVelocity().x) < kThreshold);
        REQUIRE(abs(container.GetParticles().at(1).GetVelocity().y - 0.1) < kThreshold);
    }
    SECTION("Test that two particles not colliding if moving apart from each other") {
        GasContainer container;
        container.RemoveParticles();
        idealgas::GasParticle particle1 = idealgas::GasParticle(vec2(10, 50.0));
        particle1.SetVelocity(vec2(-0.1, 0));
        idealgas::GasParticle particle2 = idealgas::GasParticle(vec2(19, 50));
        particle2.SetVelocity(vec2(0.1, 0));
        container.AddParticle(particle1);
        container.AddParticle(particle2);
        container.AdvanceOneFrame();
        container.AdvanceOneFrame();
        REQUIRE(abs(container.GetParticles().at(0).GetVelocity().x + 0.1) < kThreshold);
        REQUIRE(abs(container.GetParticles().at(0).GetVelocity().y) < kThreshold);
        REQUIRE(abs(container.GetParticles().at(1).GetVelocity().x - 0.1) < kThreshold);
        REQUIRE(abs(container.GetParticles().at(1).GetVelocity().y) < kThreshold);
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
        idealgas::GasParticle particle4 = idealgas::GasParticle(vec2(50, 398));
        particle4.SetVelocity(vec2(0, 3));
        container.AddParticle(particle4);
        container.AdvanceOneFrame();
        container.AdvanceOneFrame();
        REQUIRE(container.GetParticles().at(0).GetVelocity().x < kThreshold);
        REQUIRE(container.GetParticles().at(0).GetVelocity().y + 3 < kThreshold);
    }
    SECTION("Test that particle hit corner wall correctly") {
        idealgas::GasParticle particle4 = idealgas::GasParticle(vec2(598, 398));
        particle4.SetVelocity(vec2(3, 3));
        container.AddParticle(particle4);
        container.AdvanceOneFrame();
        container.AdvanceOneFrame();
        REQUIRE(container.GetParticles().at(0).GetVelocity().x + 3< kThreshold);
        REQUIRE(container.GetParticles().at(0).GetVelocity().y + 3 < kThreshold);
    }
    SECTION("Test that particle velocity does not change if not hitting walls") {
        idealgas::GasParticle particle5 = idealgas::GasParticle(vec2(200, 200));
        particle5.SetVelocity(vec2(3, 3));
        container.AddParticle(particle5);
        container.AdvanceOneFrame();
        container.AdvanceOneFrame();
        REQUIRE(container.GetParticles().at(0).GetVelocity().x - 3< kThreshold);
        REQUIRE(container.GetParticles().at(0).GetVelocity().y - 3 < kThreshold);
    }
}