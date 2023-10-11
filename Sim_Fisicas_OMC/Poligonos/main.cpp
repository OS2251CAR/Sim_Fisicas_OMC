#include <iostream>
#include <box2d/box2d.h>

int main()
{
    //Plantilla de Mundo

    b2Vec2 gravity(0.0f, -9.8f); //Establecer Gravedad de la tierra
    b2World world(gravity); //Crear Mundo con Nuestra Gravedad Establecida
    //caracteristicas del cuerpo
    b2BodyDef groundBodyDef; //Crear un cuerpo
    groundBodyDef.position.Set(0.0f,-10.0f); //Establecer posicion
    //Agregarlo al mundo(instanciamos)
    b2Body* groundBody = world.CreateBody(&groundBodyDef);
    //Crear Forma
    b2PolygonShape groundBox;
    groundBox.SetAsBox(50.0f,1.0f); //Establecer tamaño de forma

    groundBody ->CreateFixture(&groundBox, 0.0f); //Asignar parametros

    //Basandome en la documentacion de Box2d y su ejemplo de como crear el triangulo Creare las demas formas

    //Crear Tipo de cuerpo
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    //Crear formas
    //
    b2PolygonShape triangle;

    b2Vec2 tVertices[3];
    tVertices[0].Set(0.0f, 0.0f);
    tVertices[1].Set(1.0f, 0.0f);
    tVertices[2].Set(0.0f, 1.0f);

    int32 tCount = 3;
    triangle.Set(tVertices, tCount);
    b2Body* tBody = world.CreateBody(&bodyDef);
    tBody->CreateFixture(&triangle, 1.0f);

    //
    b2PolygonShape rectangle;
    rectangle.SetAsBox(1.0f, 0.5f);
    b2Body* rBody = world.CreateBody(&bodyDef);
    rBody->CreateFixture(&rectangle, 1.0f);
    //
    b2PolygonShape square;
    square.SetAsBox(1.0f, 1.0f);
    b2Body* sBody = world.CreateBody(&bodyDef);
    sBody->CreateFixture(&square, 1.0f);
    //
    b2PolygonShape pentagon;

    b2Vec2 pVertices[5];
    pVertices[0].Set(0.0f, 0.0f);
    pVertices[1].Set(1.0f, 0.0f);
    pVertices[2].Set(1.5f, 1.0f);
    pVertices[3].Set(0.5f, 1.5f);
    pVertices[4].Set(-0.5f, 1.0f);

    int32 pCount = 5;
    pentagon.Set(pVertices, pCount);
    b2Body* pBody = world.CreateBody(&bodyDef);
    pBody->CreateFixture(&pentagon, 1.0f);
    //
    b2PolygonShape hexagon;

    b2Vec2 hVertices[6];
    hVertices[0].Set(0.0f, 0.0f);
    hVertices[1].Set(1.0f, 0.0f);
    hVertices[2].Set(1.5f, 1.0f);
    hVertices[3].Set(1.0f, 1.5f);
    hVertices[4].Set(0.0f, 1.5f);
    hVertices[5].Set(-0.5f, 1.0f);

    int32 hCount = 6;
    hexagon.Set(hVertices, hCount);
    b2Body* hBody = world.CreateBody(&bodyDef);
    hBody->CreateFixture(&hexagon, 1.0f);
    //
    b2PolygonShape octagon;

    b2Vec2 oVertices[8];
    oVertices[0].Set(0.0f, 0.0f);
    oVertices[1].Set(1.0f, 0.0f);
    oVertices[2].Set(1.5f, 0.5f);
    oVertices[3].Set(1.5f, 1.5f);
    oVertices[4].Set(1.0f, 2.0f);
    oVertices[5].Set(0.0f, 2.0f);
    oVertices[6].Set(-0.5f, 1.5f);
    oVertices[7].Set(-0.5f, 0.5f);


    int32 oCount = 8;
    octagon.Set(oVertices, oCount);
    b2Body* oBody = world.CreateBody(&bodyDef);
    oBody->CreateFixture(&octagon, 1.0f);

    return 0;
}
