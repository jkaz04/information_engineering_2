#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class CustomRectangleShape : public sf::RectangleShape{
private:
    int Vspeed_ = 0;
    int Hspeed_ = 0;
    int Rspeed_ = 0;

    int left;
    int right;
    int top;
    int bottom;



public:
    CustomRectangleShape(sf::Vector2f size, sf::Vector2f position){
        setPosition(position);
        setSize(size);
    }

    void setSpeed(int Vspeed,int Hspeed,int Rspeed){
        Vspeed_ = Vspeed;
        Hspeed_ = Hspeed;
        Rspeed_ = Rspeed;
    }

    void animate(const sf::Time &elapsed){
        move(Vspeed_*elapsed.asSeconds(), Hspeed_*elapsed.asSeconds());
        rotate(Rspeed_*elapsed.asSeconds());
    }

    void setBounds(int a, int b, int c, int d){
        left = a;
        right = b;
        top = c;
        bottom = d;
    }

    void bounds(){
        sf::FloatRect rectangle_bounds = getGlobalBounds();

        if(rectangle_bounds.top <= top){
            Hspeed_ = abs(Hspeed_);
        }

        if(rectangle_bounds.top + rectangle_bounds.height >= bottom){
            Hspeed_ = abs(Hspeed_) * -1;
        }

        if(rectangle_bounds.left <= left ){
            Vspeed_ = abs(Vspeed_);
        }

        if(rectangle_bounds.left + rectangle_bounds.width >= right){
            Vspeed_ = abs(Vspeed_) * -1;
        }
    }

    void moveInDirection(const sf::Time &elapsed){
        sf::FloatRect rectangle_bounds = getGlobalBounds();

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            if(rectangle_bounds.top <= top){
                move(0, 0);
            }
            else{
                move(0, abs(Vspeed_)*elapsed.asSeconds()*(-1));
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            if(rectangle_bounds.top + rectangle_bounds.height >= bottom){
                move(0,0);
            }
            else{
                move(0, abs(Vspeed_)*elapsed.asSeconds());
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            if(rectangle_bounds.left <= left ){
                move(0,0);
            }
            else{
                move(abs(Hspeed_)*elapsed.asSeconds()*(-1), 0);
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            if(rectangle_bounds.left + rectangle_bounds.width >= right){
                move(0,0);
            }
            else{
                move(abs(Hspeed_)*elapsed.asSeconds(), 0);
            }
        }
    }

    bool isClicked(sf::Vector2i &mouse_position){
        bool isclicked_;
        sf::FloatRect rectangle_bounds = getGlobalBounds();

        if ((mouse_position.y >= rectangle_bounds.top && mouse_position.y <= rectangle_bounds.top + rectangle_bounds.height) && (mouse_position.x >=rectangle_bounds.left && mouse_position.x <= rectangle_bounds.left + rectangle_bounds.width)){
            isclicked_ = true;
        }else{
            isclicked_ = false;
        }

        return isclicked_;
    }

};


int main() {
    // create the window

    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

    // create some shapes

    sf::Clock clock;

    sf::Vector2f size(120.0, 60.0);
    sf::Vector2f position(120.0, 60.0);
    CustomRectangleShape rectangle2(size, position);
    rectangle2.setFillColor(sf::Color(95, 55, 230));
    rectangle2.setSpeed(100, 100, 10);

    std::srand(std::time(nullptr));


    std::vector<CustomRectangleShape> rectangles;

    for(int i = 0 ; i < 10 ; i++){
        int randomNumber1 = std::rand() % 681;
        int randomNumber2 = std::rand() % 541;

        sf::Vector2f size(120.0, 60.0);
        sf::Vector2f position(randomNumber1, randomNumber2);

        rectangles.emplace_back(CustomRectangleShape(size, position));
    }

    for(auto &rec : rectangles){
        rec.setFillColor(sf::Color(0, 255, 0));
        rec.setBounds(0, window.getSize().x, 0, window.getSize().y);
    }

    // run the program as long as the window is open
    while (window.isOpen()) {
        sf::Time elapsed = clock.restart();

        sf::FloatRect rectangle2_bounds = rectangle2.getGlobalBounds();


        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();

            if(event.type == sf::Event::MouseButtonPressed){
                if(event.mouseButton.button == sf::Mouse::Left){
                    sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
                    rectangle2.isClicked(mouse_pos);

                    for(auto &rec : rectangles){
                        bool isclicked_ = rec.isClicked(mouse_pos);

                        if (isclicked_ == true) {
                            rec.moveInDirection(elapsed);
                            rec.setBounds(0, window.getSize().x, 0, window.getSize().y);
                            rec.bounds();
                        }
                    }
                }
            }
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        rectangle2.setBounds(0, window.getSize().x, 0, window.getSize().y);
        rectangle2.bounds();
        rectangle2.moveInDirection(elapsed);

        window.draw(rectangle2);

        for(auto &rec : rectangles){
            window.draw(rec);
        }

        // end the current frame
        window.display();
    }

    return 0;
}
