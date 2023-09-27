#include <iostream>
#include <box2d/box2d.h>

int main()
{
    //creacion de mundo
    b2Vec2 gravity(0.0f, -24.79f);//Gravedad de jupiter
    b2World world(gravity);
    //caracteristicas del cuerpo
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f,-10.0f);
    //Agregarlo al mundo(instanciamos)
    b2Body* groundBody = world.CreateBody(&groundBodyDef);
    //Crear Forma
    b2PolygonShape groundBox;
    groundBox.SetAsBox(50.0f,1.0f);

    groundBody ->CreateFixture(&groundBox, 0.0f);

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f, 15.0f);//Cambio de posicion
    b2Body* body = world.CreateBody(&bodyDef);

    b2PolygonShape dynamicbox;
    dynamicbox.SetAsBox(1.0f,1.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicbox;
    fixtureDef.density = 0.015600f;//densidad del Carburo de tungsteno
    fixtureDef.friction = 0.9f;

    body ->CreateFixture(&fixtureDef);

    float timeStep = 1.0f/60.0f;

    int velocityIterations = 6;
    int positionIterations = 2;

    for (int i = 0; i < 60; ++i)
    {
        world.Step(timeStep, velocityIterations, positionIterations);
        b2Vec2 position = body->GetPosition();
        float angle = body->GetAngle();
        printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
    }

    return  0;
}
