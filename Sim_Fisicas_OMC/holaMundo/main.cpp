#include <iostream> //Libreria estandar de c++
#include <box2d/box2d.h>//Libreria de Box2D

int main()//Ciclo Main Obligatorio por cada proyecto en C++
{
    //creacion de mundo
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

    b2BodyDef bodyDef; //Crear un cuerpo
    bodyDef.type = b2_dynamicBody;//Definir tipo de cuerpo
    bodyDef.position.Set(0.0f, 20.0f);//Establecer posicion
trian
    b2PolygonShape dynamicbox;//Crear nuestra forma
    dynamicbox.SetAsBox(1.0f,1.0f);//Establecer tamaño de forma

    b2FixtureDef fixtureDef;//Crear variable para parametros
    fixtureDef.shape = &dynamicbox;//Asignar forma
    fixtureDef.density = 1.0f;//Asignar densidad
    fixtureDef.friction = 1.0f;//Asignar friccion

    body ->CreateFixture(&fixtureDef);//Asignar parametros

    float timeStep = 1.0f/60.0f;//Variable de tipo flotante que medira un step en  nuestra simulacion, en este caso 1
    //step es 1/60 de segundo

    //Variables de iteracion de velocidad y posicion, son necesarias para el metodo world.step
    int velocityIterations = 6;//Estos valores ahorita no importan porque no hay colisiones
    int positionIterations = 2;

    for (int i = 0; i < 60; ++i)//Ciclo for que se repetira 60 veces
    {
        world.Step(timeStep, velocityIterations, positionIterations);//nuestro step que en este caso es 1/60
        b2Vec2 position = body->GetPosition();//Agarramos nuestra posicion para saber donde esta en cada step
        float angle = body->GetAngle();//Agarramos nuestro angulo
        printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);//Imprimimos posicion y angulo por cada step
        //Esta simulacion dura 1 segundo. porque son 60 steps y nuestro step mide 1/60 segundos
    }

    return  0;//la funcion main acaba hasta que retorna algo, esto hace que el programa acabe exitosamente
}
