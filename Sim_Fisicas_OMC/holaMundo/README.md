<h2>Introduccion breve</h2>
<p>En este proyecto veremos que es Box2D, algunos métodos, el concepto de gravedad, densidad y fricción</p>
<h2>Que es Box2D?</h2>
<p>Para empezar, que es Box2d?, En resumen: Box2D es una librería de código abierto y gratis de c++, que se puede descargar desde GitHub, que se usa para la simulación de física en tiempo real. esta librería además de ser útil, es famosa, diversos juegos se han creado con apoyo de esta librería(ejemplo: Angry Birds), incluso el motor de físicas del motor de videojuegos Unity esta enteramente basado en Box2D. por lo que podríamos incluso considerarlo como un Estándar de la industria</p>
<h2>Como la usamos?</h2>
<p>En nuestro caso usaremos la herramienta CMake para poder usar correctamente Box2D, y para que se nos sea aun mas sencillo nuestro entorno de programación, usaremos el IDE CLion de JetBrains, para poder instalar de manera sencilla y eficaz, la librería Box2D, a través de vcpkg</p>
<h2>Que es la Gravedad</h2>
<p>En términos simples la gravedad es una fuerza de atracción que ejerce un cuerpo con una gran cantidad de masa, a cuerpos con menos cantidad de masa que ellos. en resumen un cuerpo que ya tiene fuerza gravitacional, entre mas densidad tenga mayor será su fuerza gravitacional. otra característica importante de la gravedad es que en mayor o menor medida deforma el espacio y el tiempo como se ve en la imagen. esta deformación del tiempo también es mayor dependiendo de la gravedad del cuerpo</p>
![[R.webp]]
<h2>Que es la Densidad?</h2>
<p>La densidad es la cantidad de masa que hay en un volumen, es decir un objeto "denso" es un objeto con una gran cantidad de masa en un volumen pequeño. Por ejemplo, el plomo es denso porque una pequeña cantidad pesa mucho, mientras que el algodón es menos denso porque una cantidad similar pesa menos. esto de cantidad es relativa, si nos basamos por gramo pues ambos pesan lo mismo porque logicamente 100 gramos de plomo pesan lo mismo que 100 de algodon. pero veremos mas cantidad de algodon porque su volumen sera mayor al del plomo debido a la baja densidad del algodon</p>
<h2>Que es la Fricción?</h2>
<p>En términos más simples, la fricción es lo que hace que sea más difícil deslizar o mover un objeto sobre otra superficie. Esta fuerza es el resultado de la interacción entre las asperezas microscópicas de las superficies en contacto. por ejemplo un objeto con alta fricción opondrá mas resistencia al movimiento que uno con menos fricción. no necesariamente el objeto debe ser solido, incluso el aire tiene fricción, muy poca pero tiene</p>


<h2>Como se ve nuestro código?</h2>
<p>Aquí esta nuestro código con cada linea comentada y explicada. Este codigo de ejemplo simula una caida de un cubo en la tierra</p>

	#include <iostream> //Libreria estandar de c++  
	#include <box2d/box2d.h>//Libreria de Box2D  
	  
	int main()//Ciclo Main Obligatorio por cada proyecto en C++  
	{  
	    //creacion de mundo  
	    b2Vec2 gravity(0.0f, -9.8f); //Establecer Gravedad de la tierra  
	    b2World world(gravity); //Crear Mundo con Nuestra Gravedad Establecida  
	    //caracteristicas del cuerpo    b2BodyDef groundBodyDef; //Crear un cuerpo  
	    groundBodyDef.position.Set(0.0f,-10.0f); //Establecer posicion  
	    //Agregarlo al mundo(instanciamos)    b2Body* groundBody = world.CreateBody(&groundBodyDef);  
	    //Crear Forma  
	    b2PolygonShape groundBox;  
	    groundBox.SetAsBox(50.0f,1.0f); //Establecer tamaño de forma  
	  
	    groundBody ->CreateFixture(&groundBox, 0.0f); //Asignar parametros  
	  
	    b2BodyDef bodyDef; //Crear un cuerpo  
	    bodyDef.type = b2_dynamicBody;//Definir tipo de cuerpo  
	    bodyDef.position.Set(0.0f, 20.0f);//Establecer posicion  
	    b2Body* body = world.CreateBody(&bodyDef);//Instanciar al mundo  
	  
	    b2PolygonShape dynamicbox;//Crear nuestra forma  
	    dynamicbox.SetAsBox(1.0f,1.0f);//Establecer tamaño de forma  
	  
	    b2FixtureDef fixtureDef;//Crear variable para parametros  
	    fixtureDef.shape = &dynamicbox;//Asignar forma  
	    fixtureDef.density = 1.0f;//Asignar densidad  
	    fixtureDef.friction = 1.0f;//Asignar friccion  
	  
	    body ->CreateFixture(&fixtureDef);//Asignar parametros  
	  
	    float timeStep = 1.0f/60.0f;//Variable de tipo flotante que medira un step en  nuestra simulacion, en este caso 1  
	    //step es 1/60 de segundo  
	    //Variables de iteracion de velocidad y posicion, son necesarias para el metodo world.step    int velocityIterations = 6;//Estos valores ahorita no importan porque no hay colisiones  
	    int positionIterations = 2;  
	  
	    for (int i = 0; i < 60; ++i)//Ciclo for que se repetira 60 veces  
	    {  
	        world.Step(timeStep, velocityIterations, positionIterations);//nuestro step que en este caso es 1/60  
	        b2Vec2 position = body->GetPosition();//Agarramos nuestra posicion para saber donde esta en cada step  
	        float angle = body->GetAngle();//Agarramos nuestro angulo  
	        printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);//Imprimimos posicion y angulo por cada step  
	        //Esta simulacion dura 1 segundo. porque son 60 steps y nuestro step mide 1/60 segundos    }  
	  
	    return  0;//la funcion main acaba hasta que retorna algo, esto hace que el programa acabe exitosamente  
	}


