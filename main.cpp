#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream> // stream tockenizing
#include <vector>

int main (int argc, char* argv[])
{
    // create a new window of size w by h pixels
    // top-left of windows is (0,0) and bottom-right is (w,h)
    std::ifstream file("./config.txt");                   //declare input stream variable
    if (!file.is_open()) exit(-1);                        //could not exit file
    std::string word;                                     //iss >> word
    std::string line;

    int wWidth = 640;
    int wHeight = 480;

    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        iss >> word;

        if (word == "Window")
        {
            iss >> wWidth >> wHeight;
            std::cout << "width && height set successfully" << "\n";
        }
    }
    file.close();
    sf::RenderWindow window(sf::VideoMode(wWidth, wHeight), "SFML works!");
    window.setFramerateLimit(60);           // not do any more than 60fps


    // let's make a shape that will draw to the screen
    sf::CircleShape circle(50);             //create a circle shape with radius 50
    circle.setFillColor(sf::Color(255, 255, 0));  //set the circle color to green
    circle.setPosition(300.0f, 300.0f);     //set the top-left position of the circle
    std::vector <sf::Vector2f> Cspeed;
    std::vector <sf::Vector2f> Rspeed;
    float radius;

    // let's declare arrays to store these shapes
    std::vector<sf::CircleShape> circles;
    std::vector<sf::RectangleShape> rectangles;

    // let's try and load shapes
    file.open("config.txt");
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        float iniX;                         //initial position at X
        float iniY;                         // initial position at Y
        float SpeedX;
        float SpeedY;
        std::string Sname;                  // shape name
        int r, g, b;
        float width, height;
        iss >> word;

        if (word == "Circle")
        {
            circles.emplace_back();
            iss >> Sname;                   //shape name
            iss >> iniX >> iniY;            //shape pos
            iss >> SpeedX >> SpeedY;        //shape speed
            iss >> r >> g  >> b;            // shape color
            iss >> radius;
            circles.back().setRadius(radius);
            circles.back().setPosition(sf::Vector2f(iniX,iniY));
            circles.back().setFillColor(sf::Color(r, g, b));
            Cspeed.emplace_back(sf::Vector2f(SpeedX, SpeedY));
        } else if (word == "Rectangle")
        {
            rectangles.emplace_back();
            iss >> Sname;
            iss >> iniX >> iniY;
            iss >> SpeedX >> SpeedY;
            iss >> r >> g >> b;
            iss >> width >> height;
            rectangles.back().setSize(sf::Vector2f(width, height));
            rectangles.back().setFillColor(sf::Color(r, g, b));
            rectangles.back().setPosition(sf::Vector2f(iniX, iniY));
            Rspeed.emplace_back(sf::Vector2f(SpeedX, SpeedY));
        }
    }

    file.close();

    // let's load a font so we can display some text
    sf::Font myFont;
    int fontSize, r, g, b;
    file.open("config.txt");
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string name;
        iss >> word;

        if (word == "Font")
        {
            iss >> name >> fontSize >> r >> g >> b;

            if (!myFont.loadFromFile(name))
            {
                std::cout << "could not load font!\n";
                exit(-1);
            }
        }
        
    }
    file.close();


    // set up the text object that will be drawn to the screen
    sf::Text text("Sample Text", myFont, fontSize);
    text.setFillColor(sf::Color(r, g, b));

    // position the top-left corner of the text so that the text aligns on the bottom
    // text character size is int pixels, so move the text up from the bottom by its height
    text.setPosition(0, wHeight - (float)text.getCharacterSize());

    //  main loop - continues for each frame while window.isOpen()
    while (window.isOpen())
    {
        // event handling 
        sf::Event event;
        while (window.pollEvent(event))
        {
            // ts event triggers when the window is closed
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            
        }

        // basic animation
        for (std::size_t i = 0; i < circles.size(); i++)
        {
            circles[i].setPosition(circles[i].getPosition().x + Cspeed[i].x, circles[i].getPosition().y + Cspeed[i].y);
        }

        for (std::size_t i = 0; i < rectangles.size(); i++)
        {
            rectangles[i].setPosition(rectangles[i].getPosition().x + Rspeed[i].x, rectangles[i].getPosition().y + Rspeed[i].y);
        }

        // illusion of collision
        for (std::size_t i = 0; i < circles.size(); i++)
        {
            if ((circles[i].getPosition().x + circles[i].getLocalBounds().width) > wWidth)
                Cspeed[i].x *= -1;
            if ((circles[i].getPosition().y + circles[i].getLocalBounds().height) > wHeight)
                Cspeed[i].y *= -1;
            if (circles[i].getPosition().y  < 0)
                Cspeed[i].y *= -1;
            if (circles[i].getPosition().x < 0)
                Cspeed[i].x *= -1;
        }

        for (std::size_t i = 0; i < rectangles.size(); i++)
        {
            if ((rectangles[i].getPosition().x + rectangles[i].getLocalBounds().width) > wWidth)
                Rspeed[i].x *= -1;
            if ((rectangles[i].getPosition().y + rectangles[i].getLocalBounds().height) > wHeight)
                Rspeed[i].y *= -1;
            if (rectangles[i].getPosition().y  < 0)
                Rspeed[i].y *= -1;
            if (rectangles[i].getPosition().x  < 0)
                Rspeed[i].x *= -1;
        }
        //  basic rendering funcion calls
        window.clear();                      //clear buffer
        for (const auto& p : circles)
            window.draw(p);
        for (const auto& x : rectangles)
            window.draw(x);
        window.draw(text);
        window.display();                   //call the window display function 
    }

}
