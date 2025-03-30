#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class World
{
public:
    World()
    {

        b2Vec2 gravity(0.0f, -5.8f); // Gravedad en el eje Y negativa
        world = new b2World(gravity);

        // Crear el piso 
        b2BodyDef groundBodyDef;
        groundBodyDef.position.Set(0.0f, -9.9f);
        groundBody = world->CreateBody(&groundBodyDef);

        // Definir la forma del piso (un rectángulo estático)
        b2PolygonShape groundBox;
        groundBox.SetAsBox(100.0f, 10.5f);
        // Crear el fixture del piso con coeficiente de fricción
        b2FixtureDef groundFixtureDef;
        groundFixtureDef.shape = &groundBox;
        groundFixtureDef.friction = 0.5f;
        groundBody->CreateFixture(&groundFixtureDef);

        // Crear un bloque (caja)
        b2BodyDef blockBodyDef;
        blockBodyDef.type = b2_dynamicBody;
        blockBodyDef.position.Set(12.5f, 20.0f);
        blockBody = world->CreateBody(&blockBodyDef);

        // Crear la forma del bloque (un cuadrado de 1x1)
        b2PolygonShape blockShape;
        blockShape.SetAsBox(1.0f, 1.0f);

        // Definir el bloque con una densidad de 1.0f
        b2FixtureDef blockFixtureDef;
        blockFixtureDef.shape = &blockShape;
        blockFixtureDef.density = 1.0f;
        blockFixtureDef.friction = 0.25f;
        blockFixtureDef.restitution = 0.2f;
        blockBody->CreateFixture(&blockFixtureDef);
    }

    // Actualizar la simulacion
    void update(float timeStep)
    {
        world->Step(timeStep, 8, 3);
    }

    // Aplicar fuerza a la caja
    void applyForce(bool moveLeft, bool moveRight)
    {
        // Fuerza de 10 N hacia la izquierda o derecha
        float force = 10.0f;

        if (moveLeft)
        {
            blockBody->ApplyForceToCenter(b2Vec2(-force, 0.0f), true); // Aplicar fuerza a la izquierda
        }
        if (moveRight)
        {
            blockBody->ApplyForceToCenter(b2Vec2(force, 0.0f), true); // Aplicar fuerza a la derecha
        }
    }

    // Dibujar el mundo
    void draw(sf::RenderWindow& window)
    {
        // Dibujar el bloque (caja)
        sf::RectangleShape blockShape(sf::Vector2f(30.0f, 30.0f)); // Tamaño 30x30 píxeles (equivalente al tamaño de 1x1 unidad en Box2D)
        b2Vec2 position = blockBody->GetPosition();
        blockShape.setPosition(position.x * 30.0f, 600 - position.y * 30.0f); // Convertir de Box2D a píxeles (escala)
        blockShape.setFillColor(sf::Color::Red); // Color rojo

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
    sf::RenderWindow window(sf::VideoMode(800, 600), "Ejercicio 4");

    // Crear el mundo de Box2D
    World world;

    // Tiempo de actualizacion
    float timeStep = 1.0f / 60.0f; // 60 FPS

    // Variables para controlar las teclas presionadas
    bool moveLeft = false;
    bool moveRight = false;

    // Ciclo principal de la aplicación
    while (window.isOpen())
    {
        // Manejar eventos
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            // Control de las teclas
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Left)
                    moveLeft = true; // Aplica fuerza a la izquierda
                if (event.key.code == sf::Keyboard::Right)
                    moveRight = true; // Aplica fuerza a la derecha
            }
            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Left)
                    moveLeft = false; // Deja de aplicar fuerza a la izquierda
                if (event.key.code == sf::Keyboard::Right)
                    moveRight = false; // Deja de aplicar fuerza a la derecha
            }
        }

        // Limpiar la pantalla
        window.clear(sf::Color::White);

        // Actualizar la simulacion 
        world.update(timeStep);

        // Aplicar fuerza al bloque basado en la entrada del usuario
        world.applyForce(moveLeft, moveRight);

        // Dibujar el mundo
        world.draw(window);

        // Mostrar la ventana
        window.display();
    }

    return 0;
}