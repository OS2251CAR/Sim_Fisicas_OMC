<h2>Introduccion breve</h2>

<p>En este proyecto cambiaremos Algunos parámetros de nuestro código para simular una caída de un cubo de carburo de tungsteno en Jupiter</p>

<h2>Que tenemos que cambiar</h2>

<p> la base del código seguirá siendo la misma pero cambiaremos la densidad del cubo, ya que el carburo de tungsteno su densidad es de 15.5g  del mismo tamaño eso si. tendremos que intentar recrear las condiciones de la Júpiter, por lo que cambiaremos será, la gravedad de Jupiter y la fricción del cubo</p>
  
<p> la gravedad de la Júpiter es de 24.79 m/s2 hasta ahí ya recreamos la gravedad, pero porque cambiamos la fricción? ya que júpiter tiene una gran atmosfera es necesario agregar fricción. también cambiaremos la altura a 15 en vez de 20  exceptuando lo que cambiamos cosas nuestro código termina siendo el mismo</p>

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