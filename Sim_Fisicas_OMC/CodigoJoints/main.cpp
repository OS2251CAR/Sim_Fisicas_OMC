#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

constexpr float SCALE = 30.0f;

class Cube {
public:
    Cube(b2World &world, float x, float y, int state = 0) {
        b2BodyDef bodydef;
        bodydef.position.Set(x / SCALE, y / SCALE);
        switch (state)
        {
            case 0:
                bodydef.type = b2_staticBody;
                break;
            case 1:
                bodydef.type = b2_dynamicBody;
                break;
            case 2:
                bodydef.type = b2_kinematicBody;
                break;
        }

        body = world.CreateBody(&bodydef);

        b2PolygonShape shape;
        shape.SetAsBox((10.f / 2) / SCALE, (10.f / 2) / SCALE);

        b2FixtureDef fixturedef;
        fixturedef.shape = &shape;
        fixturedef.density = 1.0f;
        body->CreateFixture(&fixturedef);

        box.setSize(sf::Vector2f(10.f, 10.f));
        box.setFillColor(sf::Color::Red);
        box.setOrigin(5.f, 5.f);
    }

    void update() {
        box.setPosition(SCALE * body->GetPosition().x, SCALE * body->GetPosition().y);
        box.setRotation(body->GetAngle() * 180 / b2_pi);
    }

    void draw(sf::RenderWindow &win) const {
        win.draw(box);
    }

    void resetPosition() {
        body->SetTransform(b2Vec2(0, 0), body->GetAngle());
    }

    void stop() {
        body->SetLinearVelocity(b2Vec2(0, 0));
    }

    b2Body *getBody() {
        return body;
    }

private:
    sf::RectangleShape box;
    b2Body *body;
};

int main() {
    sf::RenderWindow window(sf::VideoMode(1000, 900), "SFML works!");

    b2Vec2 gravity(0.0f, 0.0f);
    b2World world(gravity);

    Cube cube(world, 400, 300, 1);
    Cube cube2(world, 600, 300, 1);

    Cube cube3(world, 400, 500, 1);
    Cube cube4(world, 400, 500, 0);

    Cube cube5(world, 100, 600, 1);
    Cube cube6(world, 100, 600, 0);

    Cube cube7(world, 800, 400, 0);

    Cube cube8(world, 700, 400, 1);



    b2WheelJointDef jointDefW;
    jointDefW.Initialize(cube7.getBody(),cube8.getBody(), cube7.getBody()->GetWorldCenter(), b2Vec2(1.0f, 0.0f));

    b2PrismaticJointDef jointDefPr;
    jointDefPr.Initialize(cube5.getBody(), cube6.getBody(), cube5.getBody()->GetWorldCenter(), b2Vec2(1.0f, 0.0f));
    jointDefPr.lowerTranslation = -10.0f;
    jointDefPr.upperTranslation =10.0f;
    jointDefPr.enableLimit = true;
    world.CreateJoint(&jointDefPr);

    b2RevoluteJointDef jointDefR;
    jointDefR.Initialize(cube3.getBody(), cube4.getBody(), cube4.getBody()->GetWorldCenter());

    float speed = 2.0f;
    float torque = 1000.0f;
    jointDefR.enableMotor = true;
    jointDefR.maxMotorTorque = torque;
    jointDefR.motorSpeed = speed;
    world.CreateJoint(&jointDefR);



    b2DistanceJointDef jointDef;
    jointDef.Initialize(cube.getBody(), cube2.getBody(), cube.getBody()->GetWorldCenter(), cube2.getBody()->GetWorldCenter());

    float frequencyHz = 30.0f;
    float dampingRatio = 0.1f;

    b2LinearStiffness(jointDef.stiffness, jointDef.damping, frequencyHz, dampingRatio, jointDef.bodyA, jointDef.bodyB);

    world.CreateJoint( &jointDef);


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                cube.getBody()->ApplyForceToCenter(b2Vec2(0.1f, 0.0f), true);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                cube.getBody()->ApplyForceToCenter(b2Vec2(-0.1f, 0.0f), true);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                cube.getBody()->ApplyForceToCenter(b2Vec2(0.0f, -0.1f), true);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                cube.getBody()->ApplyForceToCenter(b2Vec2(0.0f, 0.1f), true);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                cube.resetPosition();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
                cube.stop();
            }

            // The Z key event to close the window
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
                window.close();
                return 0; // return from the main function, effectively ending the program
            }
        }

        world.Step(1 / 60.f, 8, 3);
        cube.update();
        cube2.update();
        cube3.update();
        cube4.update();
        cube5.update();
        cube6.update();
        cube7.update();
        cube8.update();

        window.clear();
        cube.draw(window);
        cube2.draw(window);
        cube3.draw(window);
        cube4.draw(window);
        cube5.draw(window);
        cube7.draw(window);
        cube8.draw(window);

        window.display();
    }
    return 0;
}