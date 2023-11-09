<h5>Maquina de Goldberg con box2d</h5>
<p> en este proyecto recrearemos una maquina de golberg coon box2d y la haremos de manera grafica con sfml, estaremos utilizando todo lo que hemos visto hasta la fecha, joints de distancia, prismatico, polea y revolucion. ademas usaremos sensores para que funcionen bien las cosas. este es hasta la fecha el prooyecto mas complejo que he hecho asi que tratare de explicarlo paso por paso, lo nuevo porque cosas como crear un cuadro o un circulo ya lo tenemos claro</p>

<p>Primero que nada Tendremos que crear las clases que necesitamos, cubo, plataforma(rectangulo), rampa(triangulo). lo que si es que mostrare que parametros tiene cada uno <code>Cube(b2World &world, float x, float y, int state = 0)</code> <code> Platform(b2World &world, float x, float y, float width, float height, float angle, bool state = false, float density = 1.0f)</code> <code> Ramps(b2World& world, float x, float y, float sideLength)</code> <code> Circle(b2World &world, float x, float y, float radius)</code></p>

<p> lo que si es nuevo es el contact listener que necesitaremos para que este revisando todo el tiempo las colisiones que esta haciendo un cuerpo con otro</p>

	class MyContactListener : public b2ContactListener{  
	    void BeginContact(b2Contact* contact) override{  
	        b2Fixture* fixtureA = contact->GetFixtureA();  
	        b2Fixture* fixtureB = contact->GetFixtureB();  
	  
	    }  
	  
	    void EndContact(b2Contact* contact) override  
	    {  
	  
	    }  
	};

<p>Despues necesitaremos instanciar todos los cuerpos que vamos usar, estos aunque estan en el mismo lugar obvio no fueron instanciados todos al mismo tiempo, fueron siendo agregados conforme avanzaba el proyecto</p>

<p> Hay mecanismos muy interesantes que merecen ser enseñados como los molinos, hice 2 y practicamente son iguales lo unico que cambia es la posicion y que uno gira en sentido horario y el otro en antihorario</p>

	//Distancia  
	b2DistanceJointDef jointDefD;  
	jointDefD.Initialize(molino1.getBody(), molino2.getBody(), molino1.getBody()->GetWorldCenter(),molino2.getBody()->GetWorldCenter());  
	world.CreateJoint(&jointDefD);  
	  
	b2DistanceJointDef jointDefD2;  
	jointDefD2.Initialize(molino2.getBody(), molino3.getBody(), molino2.getBody()->GetWorldCenter(),molino3.getBody()->GetWorldCenter());  
	world.CreateJoint(&jointDefD2);  
	  
	b2DistanceJointDef jointDefD3;  
	jointDefD3.Initialize(molino3.getBody(), molino4.getBody(), molino3.getBody()->GetWorldCenter(),molino4.getBody()->GetWorldCenter());  
	world.CreateJoint(&jointDefD3);  
	  
	b2DistanceJointDef jointDefD4;  
	jointDefD4.Initialize(molino4.getBody(), molino1.getBody(), molino4.getBody()->GetWorldCenter(),molino1.getBody()->GetWorldCenter());  
	world.CreateJoint(&jointDefD4);  
	//Revolucion  
	b2RevoluteJointDef jointDefR;  
	jointDefR.Initialize(molino1.getBody(), cube3.getBody(),cube3.getBody()->GetWorldCenter());  
	jointDefR.enableMotor = true;  
	jointDefR.maxMotorTorque = 25.0f;  
	jointDefR.motorSpeed = 0.02f;  
	world.CreateJoint(&jointDefR);  
	  
	b2RevoluteJointDef jointDefR2;  
	jointDefR2.Initialize(molino2.getBody(), cube3.getBody(),cube3.getBody()->GetWorldCenter());  
	jointDefR2.enableMotor = true;  
	jointDefR2.maxMotorTorque = 25.0f;  
	jointDefR2.motorSpeed = 0.02f;  
	world.CreateJoint(&jointDefR2);  
	  
	b2RevoluteJointDef jointDefR3;  
	jointDefR3.Initialize(molino3.getBody(), cube3.getBody(),cube3.getBody()->GetWorldCenter());  
	jointDefR3.enableMotor = true;  
	jointDefR3.maxMotorTorque = 25.0f;  
	jointDefR3.motorSpeed = 0.02f;  
	world.CreateJoint(&jointDefR3);  
	  
	b2RevoluteJointDef jointDefR4;  
	jointDefR4.Initialize(molino4.getBody(), cube3.getBody(),cube3.getBody()->GetWorldCenter());  
	jointDefR4.enableMotor = true;  
	jointDefR4.maxMotorTorque = 25.0f;  
	jointDefR4.motorSpeed = 0.02f;  
	world.CreateJoint(&jointDefR4);

<p> otro joint que tambien vale la pena mostrar es el prismatico. basicamente hize una compuerta que abre una zona para que pase nuestra bolita</p>

	b2PrismaticJointDef jointDefPr;  
	jointDefPr.Initialize(cube.getBody(), cube2.getBody(), cube.getBody()->GetWorldCenter(), b2Vec2(1.0f, 0.0f));  
	jointDefPr.lowerTranslation = -3.0f;  
	jointDefPr.upperTranslation = 3.0f;  
	jointDefPr.enableLimit = true;  
	jointDefPr.enableMotor = true;  
	jointDefPr.motorSpeed = -0.02f;  
	jointDefPr.maxMotorForce = 25.0f;  
	world.CreateJoint(&jointDefPr);

<p>El mecanismo de polea fue dificil pero basicamente aqui se esta usando 2 prisma para que no se muevan en x las plataformas y una polea para que jale el elevador. esto estuvo complicado pero no se acerca al siguiente</p>

	#pragma region Prisma2  
	b2PrismaticJointDef jointDefPr2;  
	jointDefPr2.Initialize(elevador1.getBody(), cube6.getBody(), cube6.getBody()->GetWorldCenter(), b2Vec2(0.0f, 1.0f));  
	jointDefPr2.lowerTranslation = 0.0f;  
	jointDefPr2.upperTranslation = 13.5f;  
	jointDefPr2.enableLimit = true;  
	world.CreateJoint(&jointDefPr2);  
	#pragma endregion  
	  
	#pragma region Prisma3  
	b2PrismaticJointDef jointDefPr3;  
	jointDefPr3.Initialize(elevador2.getBody(), cube5.getBody(), cube5.getBody()->GetWorldCenter(), b2Vec2(0.0f, 1.0f));  
	jointDefPr3.lowerTranslation = -13.5f;  
	jointDefPr3.upperTranslation = 0.0f;  
	jointDefPr3.enableLimit = true;  
	world.CreateJoint(&jointDefPr3);  
	#pragma endregion
	
	#pragma region Polea  
	b2PulleyJointDef jointPulley;  
	  
	jointPulley.Initialize(elevador1.getBody(),elevador2.getBody(),cube6.getBody()->GetWorldCenter(),cube5.getBody()->GetWorldCenter(),elevador1.getBody()->GetWorldCenter(),elevador2.getBody()->GetWorldCenter(), 1);  
	world.CreateJoint(&jointPulley);  
	#pragma endregion

<p>Por ultimo queda lo de los sensores. que decir esto fue muy complicado pero para empezar hay que hacer lo que queremos activar, en este caso una compuerta que deja caer muchas bolitas(tienen que ser muchos probe cambiando la densidad de 1 pero no funciono) para que caigan en la parte de la polea que queremos que baje para que suba a la otra. por lo tanto hasta que estemos en el elevador esta compuerta tiene que desaparecer para poder hacer que las pelotas bajen</p>

	#pragma region Prisma4  
	b2PrismaticJointDef jointDefPr4;  
	jointDefPr4.Initialize(cube7.getBody(), cube8.getBody(), cube7.getBody()->GetWorldCenter(), b2Vec2(1.0f, 0.0f));  
	jointDefPr4.lowerTranslation = -3.0f;  
	jointDefPr4.upperTranslation = 3.0f;  
	jointDefPr4.enableLimit = true;  
	//jointDefPr4.motorSpeed = 0.02f;  
	//jointDefPr4.maxMotorForce = 0.2f;  
	world.CreateJoint(&jointDefPr4);  
	#pragma endregion

<p> la parte complicada fue hacer que se destruya la plataforma, primero quise moverla pero fue imposible nomas no se movia y el motor se estaba actualizando constantemente por lo que tuve que mejor destruirla. basicamente la logica es que cuando nuestro personaje entre al sensor se va activar un if (que solo funciona con un bool true si no crashea) que destruya el "cubo7" que es la plataforma que queremos que sea destruida.  todo quedaria asi</p>

	for (b2Contact* WorldContactList = world.GetContactList(); WorldContactList; WorldContactList = WorldContactList->GetNext())  
	{  
	    if (WorldContactList->IsTouching())  
	    {  
	        b2Fixture* fixtureA = WorldContactList->GetFixtureA();  
	        b2Fixture* fixtureB = WorldContactList->GetFixtureB();  
	        if(fixtureA->IsSensor() && fixtureB->GetBody() == personaje.getBody() || fixtureB->IsSensor() && fixtureA->GetBody() == personaje.getBody())  
	        {  
	            if(sinestonofunciona)  
	            {  
	                world.DestroyBody(cube7.getBody());  
	                sinestonofunciona = false;  
	            }  
	            std::cout << "porfavorsirve" << std::endl;  
	        }  
	    }  
	}

<p> el for es mientras este teniendo contacto entonces esta hecho para que sea infinito, el primer if es para ver si esta tocando y se setean el fixture A y B el siguiente if es el que detecta la colision con nuestro sensor y el ultimo if es una forma sencilla para que solo se destruya el cuerpo si el cuerpo no es nulo pero lo que mas necesitamos hacer es que inmediatamente despues de hacer eso hacer que el bool sea falso si no crashea el programa</p>

<p> El codigo completo quedaria asi</p>

	#include <SFML/Graphics.hpp>  
	#include <Box2D/Box2D.h>  
	#include <iostream>  
	  
	constexpr float SCALE = 30.0f;  
	  
	class Cube {  
	public:  
	    Cube(b2World &world, float x, float y, int state = 0)  
	    {  
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
	  
	class Platform  
	{  
	public:  
	    Platform(b2World &world, float x, float y, float width, float height, float angle, bool state = false, float density = 1.0f)  
	    {  
	        b2BodyDef bodydef;  
	        bodydef.position.Set(x / SCALE, y / SCALE);  
	        bodydef.angle = angle * (b2_pi / 180);  
	        if (!state)  
	        {  
	            bodydef.type = b2_staticBody;  
	        }  
	        else  
	        {  
	            bodydef.type = b2_dynamicBody;  
	        }  
	        body = world.CreateBody(&bodydef);  
	  
	        b2PolygonShape shape;  
	        shape.SetAsBox((width / 2) / SCALE, (height / 2) / SCALE);  
	  
	        b2FixtureDef fixturedef;  
	        fixturedef.shape = &shape;  
	        fixturedef.density = density;  
	        body->CreateFixture(&fixturedef);  
	  
	        box.setSize(sf::Vector2f(width, height));  
	        box.setFillColor(sf::Color::Red);  
	        box.setOrigin(width/2, height/2);  
	        box.setRotation(body->GetAngle() * 180.0f / b2_pi);  
	  
	    }  
	  
	    void update(bool canRotate = true) {  
	        box.setPosition(SCALE * body->GetPosition().x, SCALE * body->GetPosition().y);  
	  
	            box.setRotation(body->GetAngle() * 180.0f / b2_pi);  
	  
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
	  
	class Ramps  
	{  
	    public:  
	        Ramps(b2World& world, float x, float y, float sideLength)  
	        {  
	            b2BodyDef bodyDef;  
	            bodyDef.position.Set(x / SCALE, y / SCALE);  
	            bodyDef.type = b2_staticBody;  
	            body = world.CreateBody(&bodyDef);  
	  
	            b2PolygonShape shape;  
	            b2Vec2 vertices[3];  
	            float halfSide = sideLength / 2.0f;  
	            vertices[0].Set(0, -halfSide);  
	            vertices[1].Set(halfSide, halfSide);  
	            vertices[2].Set(-halfSide, halfSide);  
	            shape.Set(vertices, 3);  
	  
	            b2FixtureDef fixtureDef;  
	            fixtureDef.shape = &shape;  
	            fixtureDef.density = 1.0f;  
	            body->CreateFixture(&fixtureDef);  
	  
	            triangle.setPointCount(3);  
	            triangle.setPoint(0, sf::Vector2f(0, -halfSide) * SCALE);  
	            triangle.setPoint(1, sf::Vector2f(halfSide, halfSide) * SCALE);  
	            triangle.setPoint(2, sf::Vector2f(-halfSide, halfSide) * SCALE);  
	            triangle.setFillColor(sf::Color::Yellow);  
	        }  
	  
	        void update() {  
	            triangle.setPosition(SCALE * body->GetPosition().x, SCALE * body->GetPosition().y);  
	            triangle.setRotation(body->GetAngle() * 180 / b2_pi);  
	        }  
	  
	        void draw(sf::RenderWindow& win) const {  
	            win.draw(triangle);  
	        }  
	  
	        void resetPosition() {  
	            body->SetTransform(b2Vec2(0, 0), body->GetAngle());  
	        }  
	  
	        void stop() {  
	            body->SetLinearVelocity(b2Vec2(0, 0));  
	        }  
	  
	        b2Body* getBody() {  
	            return body;  
	        }  
	  
	    private:  
	        sf::ConvexShape triangle;  
	        b2Body* body;  
	};  
	  
	class Circle {  
	public:  
	    Circle(b2World &world, float x, float y, float radius)  
	    {  
	        b2BodyDef bodyDef;  
	        bodyDef.position.Set(x / SCALE, y / SCALE);  
	        bodyDef.type = b2_dynamicBody;  
	        body = world.CreateBody(&bodyDef);  
	  
	        b2CircleShape shape;  
	        shape.m_radius = radius / SCALE;  
	  
	        b2FixtureDef fixtureDef;  
	        fixtureDef.shape = &shape;  
	        fixtureDef.density = 1.0f;  
	        fixtureDef.friction = 0.3f;  
	        fixtureDef.restitution = 0.5f;  
	  
	        body->CreateFixture(&fixtureDef);  
	  
	        circle.setRadius(radius);  
	        circle.setOrigin(radius, radius);  
	        circle.setFillColor(sf::Color::Blue);  
	    }  
	  
	    void update() {  
	        circle.setPosition(SCALE * body->GetPosition().x, SCALE * body->GetPosition().y);  
	        circle.setRotation(body->GetAngle() * 180 / b2_pi);  
	    }  
	  
	    void draw(sf::RenderWindow &win) const {  
	        win.draw(circle);  
	    }  
	  
	    void applyForce(float forceX, float forceY) {  
	        body->ApplyForceToCenter(b2Vec2(forceX, forceY), true);  
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
	    sf::CircleShape circle;  
	    b2Body *body;  
	};  
	  
	class MyContactListener : public b2ContactListener{  
	    void BeginContact(b2Contact* contact) override{  
	        b2Fixture* fixtureA = contact->GetFixtureA();  
	        b2Fixture* fixtureB = contact->GetFixtureB();  
	  
	    }  
	  
	    void EndContact(b2Contact* contact) override  
	    {  
	  
	    }  
	};  
	  
	int main()  
	{  
	    //Configuraciones Globales  
	    bool sinestonofunciona = true;  
	    sf::RenderWindow window(sf::VideoMode(1000, 900), "SFML works!");  
	    b2Vec2 gravity(0.0f, 0.1f);  
	    b2World world(gravity);  
	    MyContactListener escuchadorDeContacto;  
	    world.SetContactListener(&escuchadorDeContacto);  
	    #pragma region Instancias  
	  
	    bool muevete = false;  
	  
	    //Joints  
	    Platform cube(world, 450, 530,95,5, 0, true);  
	    Cube cube2(world, 550, 530, 0);  
	    Cube cube3(world, 370, 430, 0);  
	    Cube cube4(world, 440, 630, 0);  
	    Cube cube5(world, 740,100, 0);  
	    Cube cube6(world, 660,100, 0);  
	    Cube cube8(world, 850,250, 0);  
	    Platform cube7(world, 750, 250,95,5, 0, true);  
	  
	    //Sensores  
	    Platform sensor1(world, 650,740,90,20,0, false);  
	    sensor1.getBody()->GetFixtureList()->SetSensor(true);  
	    sensor1.getBody()->GetFixtureList()->SetDensity(0.0f);  
	    sensor1.getBody()->ResetMassData();  
	  
	    //Dinamicos  
	    Circle personaje (world, 170, 200,10.0f);  
	    Circle personaje2 (world, 750, 200,10.0f);  
	    Circle personaje3 (world, 750, 200,1.0f);  
	    Circle personaje4 (world, 750, 200,1.0f);  
	    Circle personaje5 (world, 750, 200,1.0f);  
	    Circle personaje6 (world, 750, 200,1.0f);  
	    Circle personaje7 (world, 750, 200,1.0f);  
	    Circle personaje8 (world, 750, 200,1.0f);  
	    Circle personaje9 (world, 750, 200,1.0f);  
	    Circle personaje10 (world, 750, 200,1.0f);  
	    Circle personaje11 (world, 750, 200,1.0f);  
	    Circle personaje12 (world, 750, 200,1.0f);  
	    Circle personaje13 (world, 750, 200,1.0f);  
	    Circle personaje14 (world, 750, 200,1.0f);  
	  
	    personaje2.getBody()->GetFixtureList()->SetDensity(10.0f);  
	  
	    Platform molino1(world, 370, 400, 40, 5, 90, true);  
	    Platform molino2(world, 370, 460, 40, 5, 90, true);  
	    Platform molino3(world, 340, 430, 40, 5, 0, true);  
	    Platform molino4(world, 400, 430, 40, 5, 0, true);  
	  
	    Platform molino5(world, 440, 600, 40, 5, 90, true);  
	    Platform molino6(world, 440, 660, 40, 5, 90, true);  
	    Platform molino7(world, 410, 630, 40, 5, 0, true);  
	    Platform molino8(world, 470, 630, 40, 5, 0, true);  
	  
	    Platform elevador1(world, 645,750, 100,5, 0, true);  
	    Platform elevador2(world, 755,350, 100,5, 0, true);  
	  
	    elevador1.getBody()->GetFixtureList()->SetRestitution(0.0f);  
	    elevador2.getBody()->GetFixtureList()->SetRestitution(0.0f);  
	    //Plataformas  
	    Platform plataforma(world, 300,338, 250,5, 5);  
	    Platform plataforma2(world, 340,490, 180,5, 0);  
	    Platform plataforma3(world, 430,440, 100,5, 90);  
	    Platform plataforma4(world, 310,530, 180,5, 0);  
	    Platform plataforma5(world, 490,475, 100,5, 90);  
	    Platform plataforma6(world, 380,610, 150,5, 90);  
	    Platform plataforma7(world, 470,690, 180,5, 0);  
	    Platform plataforma8(world, 700,550, 400,5, 90);  
	    Platform plataforma9(world, 800,200, 60,5, 90);  
	    Platform plataforma10(world, 700,200, 60,5, 90);  
	  
	  
	    //Rampas  
	    Ramps rampa(world, 150, 300,2);  
	    Ramps rampa2(world, 465, 350,2);  
	    Ramps rampa3(world, 190, 500,2);  
	    Ramps rampa4(world, 560, 720,2);  
	    #pragma endregion  
	    //Joints  
	  
	    //Molinos    #pragma region molino1  
	  
	    //Distancia  
	    b2DistanceJointDef jointDefD;  
	    jointDefD.Initialize(molino1.getBody(), molino2.getBody(), molino1.getBody()->GetWorldCenter(),molino2.getBody()->GetWorldCenter());  
	    world.CreateJoint(&jointDefD);  
	  
	    b2DistanceJointDef jointDefD2;  
	    jointDefD2.Initialize(molino2.getBody(), molino3.getBody(), molino2.getBody()->GetWorldCenter(),molino3.getBody()->GetWorldCenter());  
	    world.CreateJoint(&jointDefD2);  
	  
	    b2DistanceJointDef jointDefD3;  
	    jointDefD3.Initialize(molino3.getBody(), molino4.getBody(), molino3.getBody()->GetWorldCenter(),molino4.getBody()->GetWorldCenter());  
	    world.CreateJoint(&jointDefD3);  
	  
	    b2DistanceJointDef jointDefD4;  
	    jointDefD4.Initialize(molino4.getBody(), molino1.getBody(), molino4.getBody()->GetWorldCenter(),molino1.getBody()->GetWorldCenter());  
	    world.CreateJoint(&jointDefD4);  
	    //Revolucion  
	    b2RevoluteJointDef jointDefR;  
	    jointDefR.Initialize(molino1.getBody(), cube3.getBody(),cube3.getBody()->GetWorldCenter());  
	    jointDefR.enableMotor = true;  
	    jointDefR.maxMotorTorque = 25.0f;  
	    jointDefR.motorSpeed = 0.02f;  
	    world.CreateJoint(&jointDefR);  
	  
	    b2RevoluteJointDef jointDefR2;  
	    jointDefR2.Initialize(molino2.getBody(), cube3.getBody(),cube3.getBody()->GetWorldCenter());  
	    jointDefR2.enableMotor = true;  
	    jointDefR2.maxMotorTorque = 25.0f;  
	    jointDefR2.motorSpeed = 0.02f;  
	    world.CreateJoint(&jointDefR2);  
	  
	    b2RevoluteJointDef jointDefR3;  
	    jointDefR3.Initialize(molino3.getBody(), cube3.getBody(),cube3.getBody()->GetWorldCenter());  
	    jointDefR3.enableMotor = true;  
	    jointDefR3.maxMotorTorque = 25.0f;  
	    jointDefR3.motorSpeed = 0.02f;  
	    world.CreateJoint(&jointDefR3);  
	  
	    b2RevoluteJointDef jointDefR4;  
	    jointDefR4.Initialize(molino4.getBody(), cube3.getBody(),cube3.getBody()->GetWorldCenter());  
	    jointDefR4.enableMotor = true;  
	    jointDefR4.maxMotorTorque = 25.0f;  
	    jointDefR4.motorSpeed = 0.02f;  
	    world.CreateJoint(&jointDefR4);  
	  
	    #pragma endregion  
	  
	    #pragma region molino2  
	  
	    //Distancia  
	    b2DistanceJointDef jointDefD5;  
	    jointDefD5.Initialize(molino5.getBody(), molino6.getBody(), molino5.getBody()->GetWorldCenter(),molino6.getBody()->GetWorldCenter());  
	    world.CreateJoint(&jointDefD5);  
	  
	    b2DistanceJointDef jointDefD6;  
	    jointDefD6.Initialize(molino6.getBody(), molino7.getBody(), molino6.getBody()->GetWorldCenter(),molino7.getBody()->GetWorldCenter());  
	    world.CreateJoint(&jointDefD6);  
	  
	    b2DistanceJointDef jointDefD7;  
	    jointDefD7.Initialize(molino7.getBody(), molino8.getBody(), molino7.getBody()->GetWorldCenter(),molino8.getBody()->GetWorldCenter());  
	    world.CreateJoint(&jointDefD7);  
	  
	    b2DistanceJointDef jointDefD8;  
	    jointDefD8.Initialize(molino8.getBody(), molino5.getBody(), molino8.getBody()->GetWorldCenter(),molino5.getBody()->GetWorldCenter());  
	    world.CreateJoint(&jointDefD8);  
	    //Revolucion  
	    b2RevoluteJointDef jointDefR5;  
	    jointDefR5.Initialize(molino5.getBody(), cube4.getBody(),cube4.getBody()->GetWorldCenter());  
	    jointDefR5.enableMotor = true;  
	    jointDefR5.maxMotorTorque = 25.0f;  
	    jointDefR5.motorSpeed = -0.02f;  
	    world.CreateJoint(&jointDefR5);  
	  
	    b2RevoluteJointDef jointDefR6;  
	    jointDefR6.Initialize(molino6.getBody(), cube4.getBody(),cube4.getBody()->GetWorldCenter());  
	    jointDefR6.enableMotor = true;  
	    jointDefR6.maxMotorTorque = 25.0f;  
	    jointDefR6.motorSpeed = -0.02f;  
	    world.CreateJoint(&jointDefR6);  
	  
	    b2RevoluteJointDef jointDefR7;  
	    jointDefR7.Initialize(molino7.getBody(), cube4.getBody(),cube4.getBody()->GetWorldCenter());  
	    jointDefR7.enableMotor = true;  
	    jointDefR7.maxMotorTorque = 25.0f;  
	    jointDefR7.motorSpeed = -0.02f;  
	    world.CreateJoint(&jointDefR7);  
	  
	    b2RevoluteJointDef jointDefR8;  
	    jointDefR8.Initialize(molino8.getBody(), cube4.getBody(),cube4.getBody()->GetWorldCenter());  
	    jointDefR8.enableMotor = true;  
	    jointDefR8.maxMotorTorque = 25.0f;  
	    jointDefR8.motorSpeed = -0.02f;  
	    world.CreateJoint(&jointDefR8);  
	  
	    #pragma endregion  
	  
	    //Prismatic  
	    #pragma region Prisma1  
	    b2PrismaticJointDef jointDefPr;  
	    jointDefPr.Initialize(cube.getBody(), cube2.getBody(), cube.getBody()->GetWorldCenter(), b2Vec2(1.0f, 0.0f));  
	    jointDefPr.lowerTranslation = -3.0f;  
	    jointDefPr.upperTranslation = 3.0f;  
	    jointDefPr.enableLimit = true;  
	    jointDefPr.enableMotor = true;  
	    jointDefPr.motorSpeed = -0.02f;  
	    jointDefPr.maxMotorForce = 25.0f;  
	    world.CreateJoint(&jointDefPr);  
	    #pragma endregion  
	  
	    #pragma region Prisma2  
	    b2PrismaticJointDef jointDefPr2;  
	    jointDefPr2.Initialize(elevador1.getBody(), cube6.getBody(), cube6.getBody()->GetWorldCenter(), b2Vec2(0.0f, 1.0f));  
	    jointDefPr2.lowerTranslation = 0.0f;  
	    jointDefPr2.upperTranslation = 13.5f;  
	    jointDefPr2.enableLimit = true;  
	    world.CreateJoint(&jointDefPr2);  
	    #pragma endregion  
	  
	    #pragma region Prisma3  
	    b2PrismaticJointDef jointDefPr3;  
	    jointDefPr3.Initialize(elevador2.getBody(), cube5.getBody(), cube5.getBody()->GetWorldCenter(), b2Vec2(0.0f, 1.0f));  
	    jointDefPr3.lowerTranslation = -13.5f;  
	    jointDefPr3.upperTranslation = 0.0f;  
	    jointDefPr3.enableLimit = true;  
	    world.CreateJoint(&jointDefPr3);  
	    #pragma endregion  
	  
	    #pragma region Prisma4  
	    b2PrismaticJointDef jointDefPr4;  
	    jointDefPr4.Initialize(cube7.getBody(), cube8.getBody(), cube7.getBody()->GetWorldCenter(), b2Vec2(1.0f, 0.0f));  
	    jointDefPr4.lowerTranslation = -3.0f;  
	    jointDefPr4.upperTranslation = 3.0f;  
	    jointDefPr4.enableLimit = true;  
	    jointDefPr4.motorSpeed = 0.02f;  
	    jointDefPr4.maxMotorForce = 0.2f;  
	    world.CreateJoint(&jointDefPr4);  
	    #pragma endregion  
	  
	    //Poleas  
	    #pragma region Polea  
	    b2PulleyJointDef jointPulley;  
	  
	    jointPulley.Initialize(elevador1.getBody(),elevador2.getBody(),cube6.getBody()->GetWorldCenter(),cube5.getBody()->GetWorldCenter(),elevador1.getBody()->GetWorldCenter(),elevador2.getBody()->GetWorldCenter(), 1);  
	    world.CreateJoint(&jointPulley);  
	    #pragma endregion  
	  
	  
	    //Game loop  
	    while (window.isOpen())  
	    {  
	        for (b2Contact* WorldContactList = world.GetContactList(); WorldContactList; WorldContactList = WorldContactList->GetNext())  
	        {  
	            if (WorldContactList->IsTouching())  
	            {  
	                b2Fixture* fixtureA = WorldContactList->GetFixtureA();  
	                b2Fixture* fixtureB = WorldContactList->GetFixtureB();  
	                if(fixtureA->IsSensor() && fixtureB->GetBody() == personaje.getBody() || fixtureB->IsSensor() && fixtureA->GetBody() == personaje.getBody())  
	                {  
	                    if(sinestonofunciona)  
	                    {  
	                        world.DestroyBody(cube7.getBody());  
	                        sinestonofunciona = false;  
	                    }  
	                    std::cout << "porfavorsirve" << std::endl;  
	                }  
	            }  
	        }  
	        sf::Event event;  
	        while (window.pollEvent(event))  
	        {  
	            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))  
	            {  
	                cube.getBody()->ApplyForceToCenter(b2Vec2(0.1f, 0.0f), true);  
	                cube2.getBody()->ApplyForceToCenter(b2Vec2(0.1f, 0.0f), true);  
	  
	            }  
	  
	            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))  
	            {  
	                cube.getBody()->ApplyForceToCenter(b2Vec2(-0.1f, 0.0f), true);  
	                cube2.getBody()->ApplyForceToCenter(b2Vec2(-0.1f, 0.0f), true);  
	  
	  
	            }  
	  
	            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))  
	            {  
	                cube.getBody()->ApplyForceToCenter(b2Vec2(0.0f, -0.1f), true);  
	                cube2.getBody()->ApplyForceToCenter(b2Vec2(0.0f, -0.1f), true);  
	  
	  
	            }  
	  
	            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))  
	            {  
	                cube.getBody()->ApplyForceToCenter(b2Vec2(0.0f, 0.1f), true);  
	                cube2.getBody()->ApplyForceToCenter(b2Vec2(0.0f, 0.1f), true);  
	  
	  
	            }  
	  
	            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))  
	            {  
	                cube.resetPosition();  
	                cube2.resetPosition();  
	  
	  
	            }  
	  
	            if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))  
	            {  
	                cube.stop();  
	                cube2.stop();  
	  
	  
	            }  
	  
	            // The Z key event to close the window  
	            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))  
	            {  
	                window.close();  
	                return 0; // return from the main function, effectively ending the program  
	            }  
	        }  
	  
	        //steps  
	        world.Step(1 / 60.f, 8, 3);  
	        //joints  
	        cube.update();  
	        cube2.update();  
	        cube3.update();  
	        cube4.update();  
	        cube5.update();  
	        cube6.update();  
	        cube7.update();  
	        cube8.update();  
	  
	  
	        //plataformas  
	        plataforma.update();  
	        plataforma2.update();  
	        plataforma3.update();  
	        plataforma4.update();  
	        plataforma5.update();  
	        plataforma6.update();  
	        plataforma7.update();  
	        plataforma8.update();  
	        plataforma9.update();  
	        plataforma10.update();  
	        //Rampas  
	        rampa.update();  
	        rampa2.update();  
	        rampa3.update();  
	        rampa4.update();  
	  
	        //dinamicos que no sean joints  
	        personaje.update();  
	        personaje2.update();  
	        personaje3.update();  
	        personaje4.update();  
	        personaje5.update();  
	        personaje6.update();  
	        personaje7.update();  
	        personaje8.update();  
	        personaje9.update();  
	        personaje10.update();  
	        personaje11.update();  
	        personaje12.update();  
	        personaje13.update();  
	        personaje14.update();  
	  
	        molino1.update();  
	        molino2.update();  
	        molino3.update();  
	        molino4.update();  
	        molino5.update();  
	        molino6.update();  
	        molino7.update();  
	        molino8.update();  
	        elevador1.update();  
	        elevador2.update();  
	  
	        //Sensores  
	        sensor1.update();  
	  
	        window.clear();  
	        //Joints  
	        cube.draw(window);  
	        cube2.draw(window);  
	        cube3.draw(window);  
	        cube4.draw(window);  
	        cube5.draw(window);  
	        cube6.draw(window);  
	        cube7.draw(window);  
	        cube8.draw(window);  
	  
	        //Plataformas  
	        plataforma.draw(window);  
	        plataforma2.draw(window);  
	        plataforma3.draw(window);  
	        plataforma4.draw(window);  
	        plataforma5.draw(window);  
	        plataforma6.draw(window);  
	        plataforma7.draw(window);  
	        plataforma8.draw(window);  
	        plataforma9.draw(window);  
	        plataforma10.draw(window);  
	  
	        //Rampas  
	        rampa.draw(window);  
	        rampa2.draw(window);  
	        rampa3.draw(window);  
	        rampa4.draw(window);  
	        //dinamicos que no sean joints  
	        personaje.draw(window);  
	        personaje2.draw(window);  
	        molino1.draw(window);  
	        molino2.draw(window);  
	        molino3.draw(window);  
	        molino4.draw(window);  
	        molino5.draw(window);  
	        molino6.draw(window);  
	        molino7.draw(window);  
	        molino8.draw(window);  
	        elevador1.draw(window);  
	        elevador2.draw(window);  
	  
	        //sensores  
	        sensor1.draw(window);  
	        window.display();  
	    }  
	    return 0;  
	}

