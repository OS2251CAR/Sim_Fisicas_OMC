<h5>Oscar Mora Chávez 11/4/2023</h5>
<p> En este proyecto veremos los joints principales de Box2d asi como una implementacion sencilla en SFML. he de decir de antemano que este codigo le hacen falta 2 joints que no pude hacer que es el de Soldar y el Gear. Pero tratare de explicar de la manera mas sencilla los demas</p>

<h5>Distancia</h5>
<p> Este es probablemente el mas sencillo, simplemente necesitamos 2 cuerpos y 2 anclas. los anclas son los mismos cuerpos entonces hasta ese punto esta sencillo. para que no tengamos problemas con la animacion tenemos que ponerle la frequencia de HZ y un damping. en mi codigo el joint de distancia quedaria asi</p>

	  
	b2DistanceJointDef jointDef;  
	jointDef.Initialize(cube.getBody(), cube2.getBody(), cube.getBody()->GetWorldCenter(), cube2.getBody()->GetWorldCenter());  
	  
	float frequencyHz = 30.0f;  
	float dampingRatio = 0.1f;  
	  
	b2LinearStiffness(jointDef.stiffness, jointDef.damping, frequencyHz, dampingRatio, jointDef.bodyA, jointDef.bodyB);  
	  
	world.CreateJoint( &jointDef);

<h5>Rotor</h5>
<p>Tambien se podria decir que es de rotacion, este tambien es muy sencillo necesitamos 2 cuerpos y 1 ancla, uno tiene que ser dinamico y otro estatico, va girar al rededor del estatico precisamente como si fuera un rotor. para este solo necesitamos ponerle si queremos o no motor, agrefarle torque y agregarle velocidad. el codigo quedaria asi</p>

	b2RevoluteJointDef jointDefR;  
	jointDefR.Initialize(cube3.getBody(), cube4.getBody(), cube4.getBody()->GetWorldCenter());  
	  
	float speed = 2.0f;  
	float torque = 1000.0f;  
	jointDefR.enableMotor = true;  
	jointDefR.maxMotorTorque = torque;  
	jointDefR.motorSpeed = speed;  
	world.CreateJoint(&jointDefR);

<h5>Prismatico</h5>

<p> este el nombre puede confundir porque en mi opinion no entiendo que tiene que ver con lo que hace realmente pero basicamente usamos igual un cuerpo como ancla 1 otro cuerpo dinamico pero el dinamico no se puede mover a donde sea, este es distinto, tiene un limite y nosotros podemos decidir si en x o en y.  esos parametros se los ponemos con lower translation y upper translation. el codigo quedaria asi(el eneble limit solo hace que si tenga limite)</p>

	b2PrismaticJointDef jointDefPr;  
	jointDefPr.Initialize(cube5.getBody(), cube6.getBody(), cube5.getBody()->GetWorldCenter(), b2Vec2(1.0f, 0.0f));  
	jointDefPr.lowerTranslation = -10.0f;  
	jointDefPr.upperTranslation =10.0f;  
	jointDefPr.enableLimit = true;  
	world.CreateJoint(&jointDefPr);

<h5>Rueda</h5>

<p>Por ultimo el de Rueda este basicamente hace que simplemente gire y ya,  siendo sinceros parece que es como el de revolucion pero mucho mas limitado ya que no se puede modificar tanto como el de revolucion. tal vez se usa este cuando estas seguro que tu cuerpo se va mover uicamente hacia una direccion especifico y quieres que gire ya sea en horario o antihorario. la verdad no le veo muchos usos</p>
	
	b2WheelJointDef jointDefW;  
	jointDefW.Initialize(cube7.getBody(),cube8.getBody(), cube7.getBody()->GetWorldCenter(), b2Vec2(1.0f, 0.0f));

