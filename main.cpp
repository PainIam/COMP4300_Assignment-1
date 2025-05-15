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
    float circleMoveSpeed = 0.95f;          // use t move the circle later

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
        float iniSpeedX;                    // initial speed towards the X-axis
        float iniSpeedY;                    // initial speed towards the Y-axis
        float radius;
        std::string Sname;                  // shape name
        int r, g, b;
        float width, height;
        iss >> word;

        if (word == "Circle")
        {
            circles.emplace_back();
            iss >> Sname;                   //shape name
            iss >> iniX >> iniY;            //shape pos
            iss >> iniSpeedX >> iniSpeedY;  //shape speed
            iss >> r >> g  >> b;            // shape color
            iss >> radius;
            circles.back().setRadius(radius);
            circles.back().setPosition(sf::Vector2f(iniX,iniY));
            circles.back().setFillColor(sf::Color(r, g, b));
        } else if (word == "Rectangle")
        {
            rectangles.emplace_back();
            iss >> Sname;
            iss >> iniX >> iniY;
            iss >> iniSpeedX >> iniSpeedY;
            iss >> r >> g >> b;
            iss >> width >> height;
            rectangles.back().setSize(sf::Vector2f(width, height));
            rectangles.back().setFillColor(sf::Color(r, g, b));
            rectangles.back().setPosition(sf::Vector2f(iniX, iniY));
        }
    }


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

            // ts event is triggered when a key is pressed
            if (event.type == sf::Event::KeyPressed)
            {
                // print the key that was pressed to the console
                std::cout << "key pressed with code = " << event.key.code << "\n";

                // example, what happens when x is pressed
                if (event.key.code == sf::Keyboard::X)
                {
                    // reverse the direction of the circle on the screen
                    circleMoveSpeed *= -1.0f;
                }
            }
        }

        // basic animation  move each frame if it's still in frame
        circle.setPosition(circle.getPosition().x + circleMoveSpeed, circle.getPosition().y 
        + circleMoveSpeed);

        //  basic rendering funcion calls
        window.clear();                      //clear buffer
        // window.draw(circle);             //draw
        for (const auto& p : circles)
            window.draw(p);
        for (const auto& x : rectangles)
            window.draw(x);
        window.draw(text);
        window.display();                   //call the window display function 
    }

}
