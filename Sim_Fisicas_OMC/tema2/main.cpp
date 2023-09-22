#include <Box2D/Box2D.h>
#include <cmath>
#include <iostream>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

int main() {
    // Define the gravity vector
    b2Vec2 gravity(0.0f, -1.62f); //gravedad de la luna

    // Construct a world object, which will hold and simulate the rigid bodies
    b2World world(gravity);

    // Create a dynamic body for the bullet
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f, 0.0f);
    b2Body* body = world.CreateBody(&bodyDef);

    // Define another box shape for the bullet
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(0.016f, 0.016f);//el tamaño promedio de una bala de cañon de un mosquete es de 16 milimetros

    // Define the dynamic body fixture
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 0.01134f;//la mayoria de balas de mosquetes antiguos, eran de plomo, la densidad del plomo es de 11.34g
    //en la luna no hay atmosfera por lo tanto no deberia haber friccion que afecte a nuestro objeto

    // Add the shape to the body
    body->CreateFixture(&fixtureDef);

    // Set the initial velocity of the bullet
    float angle = 60.0f; // Angle in degrees, 60 grados
    float speed = 250.0f; // Speed in m/s 250 metros por segundo son 900km/h
    float vx = speed * std::cos(angle * M_PI / 180.0f);
    float vy = speed * std::sin(angle * M_PI / 180.0f);
    std::cout << vx << " " << vy << std::endl; // debug log solo para verificar si los calculos de velocidad son correctos

    body->SetLinearVelocity(b2Vec2(vx, vy));

    // Simulate the world
    float timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    for (int i = 0; i < 60; ++i)
    {
        world.Step(timeStep, velocityIterations, positionIterations);
        std::cout << body->GetPosition().x << " " << body->GetPosition().y << std::endl;

    }

    // Remember to clean up
    world.DestroyBody(body);

    return 0;
}