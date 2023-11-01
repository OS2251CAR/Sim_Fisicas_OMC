<h2>Introduccion breve</h2>
<p>Este proyecto es muy sencillo unicamente tenemos que crear las siguientes formas:Triangulo Rectangulo, Cuadrado, Pentagono, Hexagono y Octagono. no hace falta interactuar con ellas </p>
<h2>Aspectos nuevos de nuestro nuevo codigo</h2>
<p>Como esto es un nuevo tema usaremos un codigo desde 0 que el mismo profesor nos proporciono solo para verificar que sfml funciona de manera correcta. pero como hacemos que sfml funcione de manera correcta?. pues primero que nada en nuestro IDE que en nuestro caso es Clion tenemos que agregar una nueva herramienta al vcpkg la cual es SFML, asi tal cual se llama.
cuando lo descarguemos nos dara estos codigos</p>

	find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
	target_link_libraries(main PRIVATE sfml-system sfml-network sfml-graphics sfml-window)

<p> sin embargo no funciona realmente, por una razon que no se lo mismo que nos proporciona la herramienta no es suficiente, por lo que tuve que investigar como y gracias a un video de youtube[1] me di cuenta de que era lo que faltaba, ya nomas lo que hice fue que en el target link libraries ademas de agregar lo de sfml agregara ahi mismo lo de box2d. El codigo completo del cmaketextlist quedo asi</p>

	cmake_minimum_required(VERSION 3.26)  
	project(CodigoProfe)  
	  
	include(FetchContent)  
	set(BUILD_SHARED_LIBS OFF)  
	FETCHCONTENT_DECLARE(SFML GIT_REPOSITORY https://github.com/SFML/SFML.git GIT_TAG 2.5.1)  
	FETCHCONTENT_MAKEAVAILABLE(SFML)  
	  
	find_package(box2d CONFIG REQUIRED)  
	  
	set(CMAKE_CXX_STANDARD 17)  
	  
	add_executable(CodigoProfe main.cpp)  
	  
	target_link_libraries(CodigoProfe PRIVATE sfml-system sfml-window sfml-graphics sfml-audio box2d::box2d)

<p> Y el codigo que tenia que correr con sfml es el siguiente: </p>

	#include <SFML/Graphics.hpp>  
	#include <Box2D/Box2D.h>  
	  
	constexpr float SCALE = 30.0f;  
	  
	class Cube {  
	public:  
	    Cube(b2World &world, float x, float y) {  
	        b2BodyDef bodydef;  
	        bodydef.position.Set(x / SCALE, y / SCALE);  
	        bodydef.type = b2_dynamicBody;  
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
	  
	    Cube cube(world, 400, 300);  
	  
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
	  
	        window.clear();  
	        cube.draw(window);  
	        window.display();  
	    }  
	    return 0;  
	}

<p> Este codigo lo que hace es crear una pestaña y no estoy seguro si sea el termino correcto pero "renderiza" un cubo, el cual es un cubo que creamos con box2d pero por el momento no hace nada. es importante agregar una tecla para cerrar la ventana, en este caso es la Z porque con el clic no cierra, incluso no la encontre en el administrador de tareas entonces lo mas seguro es agregar esa tecla.</p>


<h3>Referencias/Bibliografia</h3>

<p>[1] Radosław Opacki, «How include SFML in CLion using CMAKE», _YouTube_. 11 de agosto de 2023. [En línea]. Disponible en: https://www.youtube.com/watch?v=R3x2OvsUHOU</p>
