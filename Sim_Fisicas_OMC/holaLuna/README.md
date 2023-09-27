<h2>Introduccion breve</h2>

<p>En este proyecto cambiaremos Algunos parámetros de nuestro código para simular una caída de un cubo en la luna</p>
<h2>Que tenemos que cambiar</h2>
<p> la base del código seguirá siendo la misma ya que el cubo sigue siendo igual, del mismo tamaño, solo tendremos que intentar recrear las condiciones de la luna, por lo que cambiaremos será, la gravedad de la luna y la fricción del cubo</0>

<p> la gravedad de la luna es de 1.62 m/s2 hasta ahi ya recreamos la gravedad, pero porque cambiamos la friccion? porque en el cubo anterior le asignamos una friccion de 1, debido al aire, pero en la luna no hay atmosfera ni aire, por lo tanto es necesario quitar la friccion. quitando esas 2 cosas nuestro codigo termina siendo el mismo</p>

	#include <iostream>  
	#include <box2d/box2d.h>  
	  
	int main()  
	{  
	    //creacion de mundo  
	    b2Vec2 gravity(0.0f, -1.62f);//Gravedad de la luna  
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
	    bodyDef.position.Set(0.0f, 20.0f);  
	    b2Body* body = world.CreateBody(&bodyDef);  
	  
	    b2PolygonShape dynamicbox;  
	    dynamicbox.SetAsBox(1.0f,1.0f);  
	  
	    b2FixtureDef fixtureDef;  
	    fixtureDef.shape = &dynamicbox;  
	    fixtureDef.density = 1.0f;  
	    //Quitamos friccion porque en la luna no hay friccion  
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
