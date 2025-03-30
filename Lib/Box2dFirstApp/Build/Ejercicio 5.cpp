#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <cmath> 

class World
{
public:
    World(float angle) : angle(angle)
    {
        // Calcular la gravedad en dirección del plano inclinado
        float angleRad = angle * (b2_pi / 180.0f); // Convertir el angulo a radianes
        b2Vec2 gravity(-0.098f * sin(angleRad), -0.098f * cos(angleRad)); // Componente de gravedad en el plano inclinado
        world = new b2World(gravity);

        // Crear el piso (suelo) inclinado
        b2BodyDef groundBodyDef;
        groundBodyDef.position.Set(0.0f, 0.0f);
        groundBody = world->CreateBody(&groundBodyDef);

        // Crear la forma del plano inclinado (un rectángulo)
        b2PolygonShape groundBox;
        groundBox.SetAsBox(50.0f, 10.0f);

        // Crear el fixture del plano inclinado con coeficiente de fricción
        b2FixtureDef groundFixtureDef;
        groundFixtureDef.shape = &groundBox;
        groundFixtureDef.friction = 0.5f;
        groundBody->CreateFixture(&groundFixtureDef);

        // Rotar el suelo para que sea un plano inclinado
        groundBody->SetTransform(b2Vec2(0.0f, 0.0f), angleRad);

        // Crear un bloque (caja)
        b2BodyDef blockBodyDef;
        blockBodyDef.type = b2_dynamicBody;
        blockBodyDef.position.Set(10.0f, 20.0f);
        blockBody = world->CreateBody(&blockBodyDef);

        // Crear la forma del bloque 
        b2PolygonShape blockShape;
        blockShape.SetAsBox(1.0f, 1.0f);

        // Definir el bloque con una densidad de 1.0f
        b2FixtureDef blockFixtureDef;
        blockFixtureDef.shape = &blockShape;
        blockFixtureDef.density = 1.0f;
        blockFixtureDef.friction = 0.3f;
        blockBody->CreateFixture(&blockFixtureDef);
    }

    // Actualizar la simulación
    void update(float timeStep)
    {
        world->Step(timeStep, 8, 3); // Simular la física (con 8 iteraciones de posición y 3 de velocidad)
    }

    // Dibujar el mundo
    void draw(sf::RenderWindow& window)
    {
        // Dibujar el bloque (caja)
        sf::RectangleShape blockShape(sf::Vector2f(30.0f, 30.0f)); // Tamaño 30x30 píxeles (equivalente a 1x1 unidad en Box2D)
        b2Vec2 position = blockBody->GetPosition();

        // Establecer la rotación del bloque en SFML basada en la rotación de Box2D
        blockShape.setRotation(blockBody->GetAngle() * 180.0f / b2_pi); // Convertir de radianes a grados

        blockShape.setPosition(position.x * 30.0f, 600 - position.y * 30.0f); // Convertir de Box2D a píxeles (escala)
        blockShape.setFillColor(sf::Color::Red); // Color rojo

        window.draw(blockShape);
    }

private:
    b2World* world;
    b2Body* groundBody;
    b2Body* blockBody;
    float angle; // Ángulo de inclinación en grados
};

int main()
{
    // Crear la ventana 
    sf::RenderWindow window(sf::VideoMode(800, 600), "Ejercicio 5");

    // Ángulo de inclinación del plano (en grados)
    float angle = 30.0f;

    // Crear el mundo de Box2D
    World world(angle);


    float timeStep = 1.0f / 60.0f; // 60 FPS

    // Ciclo principal de la aplicación
    while (window.isOpen())
    {
        // Manejar eventos
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Limpiar la pantalla
        window.clear(sf::Color::White);

        // Actualizar la simulación 
        world.update(timeStep);

        // Dibujar el mundo
        world.draw(window);

        // Mostrar la ventana
        window.display();
    }

    return 0;
}
