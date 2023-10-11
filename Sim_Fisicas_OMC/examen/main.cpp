#include <Box2D/Box2D.h>
#include <iostream>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
int main() {
    b2Vec2 gravity(0.0f, -10.0f);
    b2World world(gravity);
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f, 0.0f);
    b2Body* body = world.CreateBody(&bodyDef);
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 1.0f);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    body->CreateFixture(&fixtureDef);
    float angle = 45.0f;
    float speed = 400.0f;
    float vx = speed * std::cos(angle * M_PI / 180.0f);
    float vy = speed * std::sin(angle * M_PI / 180.0f);
    body->SetLinearVelocity(b2Vec2(vx, vy));
    body->SetLinearDamping(0.5f);
    float timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;
    for (int i = 0; i < 60; ++i)
    {
        world.Step(timeStep, velocityIterations, positionIterations);
        std::cout << body->GetPosition().x << " " << body->GetPosition().y << std::endl;
    }
    world.DestroyBody(body);
    return 0;
}