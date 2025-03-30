#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class World
{
public:
    World()
    {

        b2Vec2 gravity(0.0f, -0.098f);
        world = new b2World(gravity);

        // Crear la pelota
        b2BodyDef ballBodyDef;
        ballBodyDef.type = b2_dynamicBody;
        ballBodyDef.position.Set(10.0f, 20.0f);
        ballBody = world->CreateBody(&ballBodyDef);

        // Forma de la pelota (un círculo)
        b2CircleShape ballShape;
        ballShape.m_radius = 1.0f;

        // Definir la pelota con una densidad de 1.0f
        b2FixtureDef ballFixtureDef;
        ballFixtureDef.shape = &ballShape;
        ballFixtureDef.density = 1.0f;
        ballFixtureDef.friction = 0.3f;
        ballFixtureDef.restitution = 0.2f;
        ballBody->CreateFixture(&ballFixtureDef);

        b2Vec2 initialVelocity(3.5f, 0.0f);
        ballBody->SetLinearVelocity(initialVelocity);

        createTopWall();
        createBottomWall();
        createLeftWall();
        createRightWall();


        createStaticSquare();
    }

    // Actualizar la simulacion
    void update(float timeStep)
    {
        world->Step(timeStep, 8, 3);
    }

    // Dibujar el mundo
    void draw(sf::RenderWindow& window)
    {
        // Dibujar las barreras 
        sf::RectangleShape topWall(sf::Vector2f(800.0f, 10.0f)); // Techo
        topWall.setPosition(0.0f, 0.0f);
        topWall.setFillColor(sf::Color::Red);
        window.draw(topWall);

        sf::RectangleShape bottomWall(sf::Vector2f(800.0f, 10.0f)); // Piso
        bottomWall.setPosition(0.0f, 590.0f);
        bottomWall.setFillColor(sf::Color::Red);
        window.draw(bottomWall);

        sf::RectangleShape leftWall(sf::Vector2f(10.0f, 600.0f)); // Pared izquierda
        leftWall.setPosition(0.0f, 0.0f);
        leftWall.setFillColor(sf::Color::Red);
        window.draw(leftWall);

        sf::RectangleShape rightWall(sf::Vector2f(10.0f, 600.0f)); // Pared derecha
        rightWall.setPosition(790.0f, 0.0f);
        rightWall.setFillColor(sf::Color::Red);
        window.draw(rightWall);

        // Dibujar el cuadrado estático
        sf::RectangleShape staticSquare(sf::Vector2f(60.0f, 60.0f));
        staticSquare.setPosition(370.0f, 270.0f);
        staticSquare.setFillColor(sf::Color::Blue);
        window.draw(staticSquare);

        // Dibujar la pelota
        sf::CircleShape ballShape(30.0f);
        b2Vec2 position = ballBody->GetPosition();
        ballShape.setPosition(position.x * 30.0f, 600 - position.y * 30.0f);
        ballShape.setFillColor(sf::Color::Green);

        window.draw(ballShape);
    }

private:
    b2World* world;
    b2Body* ballBody;

    // Crear las paredes usando b2PolygonShape
    void createTopWall()
    {
        b2BodyDef wallBodyDef;
        wallBodyDef.position.Set(0.0f, 30.7f); //techo 
        b2Body* topWall = world->CreateBody(&wallBodyDef);

        b2PolygonShape wallShape;
        wallShape.SetAsBox(50.0f, 10.0f);

        b2FixtureDef wallFixtureDef;
        wallFixtureDef.shape = &wallShape;
        wallFixtureDef.density = 0.0f;
        wallFixtureDef.friction = 0.3f;
        wallFixtureDef.restitution = 0.95f;
        topWall->CreateFixture(&wallFixtureDef);
    }

    void createBottomWall()
    {
        b2BodyDef wallBodyDef;
        wallBodyDef.position.Set(0.0f, -8.7f); // El piso se coloca en Y 
        b2Body* bottomWall = world->CreateBody(&wallBodyDef);

        b2PolygonShape wallShape;
        wallShape.SetAsBox(50.0f, 10.0f);

        b2FixtureDef wallFixtureDef;
        wallFixtureDef.shape = &wallShape;
        wallFixtureDef.density = 0.0f;
        wallFixtureDef.friction = 0.3f;
        wallFixtureDef.restitution = 0.95f;
        bottomWall->CreateFixture(&wallFixtureDef);
    }

    void createLeftWall()
    {
        b2BodyDef wallBodyDef;
        wallBodyDef.position.Set(-10.7f, 0.0f); // La pared izquierda
        b2Body* leftWall = world->CreateBody(&wallBodyDef);

        b2PolygonShape wallShape;
        wallShape.SetAsBox(10.0f, 50.0f);

        b2FixtureDef wallFixtureDef;
        wallFixtureDef.shape = &wallShape;
        wallFixtureDef.density = 0.0f;
        wallFixtureDef.friction = 0.3f;
        wallFixtureDef.restitution = 1.0f;
        leftWall->CreateFixture(&wallFixtureDef);
    }

    void createRightWall()
    {
        b2BodyDef wallBodyDef;
        wallBodyDef.position.Set(35.4f, 0.0f); // La pared derecha 
        b2Body* rightWall = world->CreateBody(&wallBodyDef);

        b2PolygonShape wallShape;
        wallShape.SetAsBox(10.0f, 50.0f);

        b2FixtureDef wallFixtureDef;
        wallFixtureDef.shape = &wallShape;
        wallFixtureDef.density = 0.0f;
        wallFixtureDef.friction = 0.3f;
        wallFixtureDef.restitution = 1.0f;
        rightWall->CreateFixture(&wallFixtureDef);
    }

    // Crear un cuadrado estático en el centro de la pantalla
    void createStaticSquare()
    {
        b2BodyDef squareBodyDef;
        squareBodyDef.type = b2_staticBody;
        squareBodyDef.position.Set(12.3f, 11.0f);  // Colocar en el centro de la pantalla (en coordenadas de Box2D)
        b2Body* squareBody = world->CreateBody(&squareBodyDef);

        b2PolygonShape squareShape;
        squareShape.SetAsBox(1.0f, 1.0f);

        b2FixtureDef squareFixtureDef;
        squareFixtureDef.shape = &squareShape;
        squareFixtureDef.density = 0.0f;
        squareFixtureDef.friction = 0.25f;
        squareFixtureDef.restitution = 1.0f;
        squareBody->CreateFixture(&squareFixtureDef);
    }
};

int main()
{
    // Crear la ventana de 800x600 píxeles
    sf::RenderWindow window(sf::VideoMode(800, 600), "Ejercicio 2");

    // Crear el mundo de Box2D
    World world;

    float timeStep = 1.0f / 60.0f; // 60 FPS

    // Ciclo principal
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Limpiar la pantalla
        window.clear(sf::Color::White);

        // Actualizar la simulación física
        world.update(timeStep);

        // Dibujar el mundo
        world.draw(window);

        // Mostrar la ventana
        window.display();
    }

    return 0;
}