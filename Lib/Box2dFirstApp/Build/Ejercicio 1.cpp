#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class World
{
public:
    World()
    {

        b2Vec2 gravity(0.0f, -9.8f);
        world = new b2World(gravity);

        // Crear el piso (suelo)
        b2BodyDef groundBodyDef;
        groundBodyDef.position.Set(0.0f, -9.9f);
        groundBody = world->CreateBody(&groundBodyDef);


        b2PolygonShape groundBox;
        groundBox.SetAsBox(50.0f, 10.5f);
        groundBody->CreateFixture(&groundBox, 0.0f);

        // Crear un bloque
        b2BodyDef blockBodyDef;
        blockBodyDef.type = b2_dynamicBody;
        blockBodyDef.position.Set(12.5f, 20.0f);
        blockBody = world->CreateBody(&blockBodyDef);

        // Crear la forma del bloque (un cuadrado de 1x1)
        b2PolygonShape blockShape;
        blockShape.SetAsBox(1.0f, 1.0f);

        // Definir el bloque 
        b2FixtureDef blockFixtureDef;
        blockFixtureDef.shape = &blockShape;
        blockFixtureDef.density = 1.0f;
        blockFixtureDef.friction = 0.3f;
        blockBody->CreateFixture(&blockFixtureDef);
    }

    // Actualizar la simulación
    void update(float timeStep)
    {
        world->Step(timeStep, 8, 2);
    }

    // Dibujar el mundo
    void draw(sf::RenderWindow& window)
    {
        // Dibujar el bloque
        sf::RectangleShape blockShape(sf::Vector2f(50.0f, 50.0f));
        b2Vec2 position = blockBody->GetPosition();
        blockShape.setPosition(position.x * 30.0f, 600 - position.y * 30.0f);
        blockShape.setFillColor(sf::Color::Red);

        window.draw(blockShape);
    }

private:
    b2World* world;
    b2Body* groundBody;
    b2Body* blockBody;
};

int main()
{
    // Crear la ventana 
    sf::RenderWindow window(sf::VideoMode(800, 600), "Ejercicio 1");

    // Crear el mundo de Box2D
    World world;

    // Tiempo de actualización
    float timeStep = 1.0f / 60.0f; // 60 FPS

    // Ciclo principal
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