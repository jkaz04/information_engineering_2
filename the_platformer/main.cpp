#include <iostream>
#include <memory>
#include <vector>
#include <cmath>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace std;


class AnimatedSprite : public sf::Sprite {
public:
    AnimatedSprite(const int fps, const std::string& path) : fps_(fps) //make an initializer list for fps_
    {

        if (!texture_.loadFromFile(path)) {
            std::cerr << "Could not load texture" << path << std::endl;
        }

        // TODO:  set the texture here
        setTexture(texture_);

        // TODO:  set the texture rectangle here
        setTextureRect(sf::IntRect(50, 0, 50, 37));
    }

    void setSpeed(const int& x_speed, const int& y_speed, const int & ro_speed) {
        x_speed_ = x_speed;
        y_speed_ = y_speed;
        ro_speed_ = ro_speed;
    }

    void fall(const sf::Time &elapsed){
        float dt = elapsed.asSeconds();

        // Calculate duration of falling
        t_falling += dt;
        float duration = 0.001 * 9.81 * t_falling * t_falling;

        // TODO:  move(0,0);
        move(0, duration);
    }

    void animate(const sf::Time &elapsed){
        bouncce();
        float dt = elapsed.asSeconds();

        // TODO:  t_ is equal to t_ + dt
        t_ = t_ + dt;

        // TODO:  if t_ became bigger than duration between two frames, then fragments_index would be added by one
        if(t_ > 1.0/fps_){
            fragments_index++;
            t_ = 0;
        }

        // TODO:  if fragments_index reached the end of the vector, fragments_index becaomes zero
        if(fragments_index == intrect_.size()-1){
            fragments_index = 0;
        }

        // TODO:  now setTextureRect by rectangle of the current index of the vector of rectangles
        setTextureRect(intrect_[fragments_index]);



        move(x_speed_*dt,y_speed_*dt);
    }

    void animate_left(const sf::Time &elapsed){
        bouncce_left();
        float dt = elapsed.asSeconds();

        // TODO:  t_ is equal to t_ + dt
        t_ = t_ + dt;

        // TODO:  if t_ became bigger than duration between two frames, then fragments_index would be added by one
        if(t_ > 1.0/fps_){
            fragments_index++;
            t_ = 0;
        }

        // TODO:  if fragments_index reached the end of the vector, fragments_index becaomes zero
        if(fragments_index == intrect_.size()-1){
            fragments_index = 0;
        }

        // TODO:  now setTextureRect by rectangle of the current index of the vector of rectangles
        setTextureRect(intrect_[fragments_index]);



        move(-(x_speed_*dt),y_speed_*dt);
    }

    void setBounds(const float& l_bound, const float& r_bound,const float& u_bound,const float& d_bound){
        l_bound_  = l_bound  ;
        r_bound_  = r_bound  ;
        u_bound_  = u_bound  ;
        d_bound_  = d_bound  ;
    }

    void add_animation_frame(const sf::IntRect& frame){

        // TODO:  add the rectnagle frame to the vector of rectangle frames
        intrect_.emplace_back(frame);
    }

    void reset_falling(){
        t_falling = 0;
    }

    void falling(const sf::Time &elapsed, sf::FloatRect wall_bounds){
        sf::FloatRect guy_bounds = getGlobalBounds();
        if(guy_bounds.left <= wall_bounds.left || guy_bounds.left + guy_bounds.width >= wall_bounds.left + wall_bounds.width ||
            guy_bounds.top + guy_bounds.width < wall_bounds.top){
            fall(elapsed);
        }
        else{
            reset_falling();
        }
    }

    void jump(float jumpHeight) {
        if (!isJumping_) {
            isJumping_ = true;
            JumpVelocity_ = sqrt(1.0 * 9.81 * jumpHeight);

            y_speed_ = -JumpVelocity_;
        }
    }

    void updateJump(const sf::Time& elapsed) {
        if (isJumping_) {
            jumpTime_ += elapsed.asSeconds();

            float newY = JumpVelocity_ * jumpTime_ + 0.5 * 9.81 * jumpTime_ * jumpTime_;

            if (newY >= 0.0) {
                isJumping_ = false;
                jumpTime_ = 0.0;
                y_speed_ = 0.0;
            }
            setPosition(getPosition().x, newY);
        }
    }

private:
    sf::Texture texture_;
    int fps_;
    int x_speed_ = 0 ;
    int y_speed_ = 0 ;
    int ro_speed_ = 0 ;
    float l_bound_ = 0;
    float r_bound_ = 0;
    float u_bound_ = 0;
    float d_bound_ = 0;
    float t_ = 0.0;
    float t_falling = 0.0;
    unsigned int fragments_index = 0;
    bool isJumping_ = false;
    float JumpVelocity_ = 0.0;
    float jumpTime_ = 0.0;

    // TODO: create a vector of sf::IntRect
    vector<sf::IntRect> intrect_ = {};





    void bouncce(){
        sf::FloatRect rectangle_bounds = getGlobalBounds();

        if(rectangle_bounds.top <= u_bound_){
            y_speed_ = abs(y_speed_);
        }

        if(rectangle_bounds.top + rectangle_bounds.height >= d_bound_){
            y_speed_ = abs(y_speed_) * -1;
        }

        if(rectangle_bounds.left <= l_bound_ ){
            x_speed_ = abs(x_speed_);
        }

        if(rectangle_bounds.left + rectangle_bounds.width >= r_bound_){
            x_speed_ = abs(x_speed_) * -1;
        }
    }

    void bouncce_left(){
        sf::FloatRect rectangle_bounds = getGlobalBounds();

        if(rectangle_bounds.top <= u_bound_){
            y_speed_ = abs(y_speed_);
        }

        if(rectangle_bounds.top + rectangle_bounds.height >= d_bound_){
            y_speed_ = abs(y_speed_) * -1;
        }

        if(rectangle_bounds.left <= l_bound_ ){
            x_speed_ = abs(x_speed_) * -1;
        }

        if(rectangle_bounds.left + rectangle_bounds.width >= r_bound_){
            x_speed_ = abs(x_speed_);
        }
    }


};





int main() {
    // create the window
    sf::RenderWindow window(sf::VideoMode(1080, 300), "My window");


    AnimatedSprite hero(12, "/Users/kazmi/OneDrive/Dokumenty/GitHub/information_engineering_2/the_platformer/Character/character.png");
    hero.setBounds(0, window.getSize().x, 0, window.getSize().y);
    hero.setSpeed(150,0,0);
    hero.setPosition(2, 200);


    //    hero.add_animation_frame(sf::IntRect(0, 0, 50, 37)); // hero standing frame 1
    //    hero.add_animation_frame(sf::IntRect(50, 0, 50, 37)); // hero standing frame 2
    //    hero.add_animation_frame(sf::IntRect(100, 0, 50, 37)); // hero standing frame 3
    hero.add_animation_frame(sf::IntRect(150, 0, 50, 37)); // hero running frame 1
    hero.add_animation_frame(sf::IntRect(200, 0, 50, 37)); // hero running frame 1
    hero.add_animation_frame(sf::IntRect(250, 0, 50, 37)); // hero running frame 1
    hero.add_animation_frame(sf::IntRect(300, 0, 50, 37)); // hero running frame 1
    hero.add_animation_frame(sf::IntRect(350, 0, 50, 37)); // hero running frame 1
    hero.add_animation_frame(sf::IntRect(400, 0, 50, 37)); // hero running frame 1



    sf::Clock clock;

    sf::Texture grass_tex;
    if(!grass_tex.loadFromFile("/Users/kazmi/OneDrive/Dokumenty/GitHub/information_engineering_2/labirnyth/grass.png")){
        return 1;
    }
    grass_tex.setRepeated(true);

    sf::Sprite grass;
    grass.setTexture(grass_tex);
    grass.setPosition(0, 270);

    sf::Sprite grass2;
    grass2.setTexture(grass_tex);
    grass2.setPosition(400, 270);

    sf::Sprite grass3;
    grass3.setTexture(grass_tex);
    grass3.setPosition(800, 150);



    // run the program as long as the window is open
    while (window.isOpen()) {

        sf::Vector2i position = sf::Mouse::getPosition(window);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            cout << "x: " << position.x << endl;
            cout << "y: " << position.y << endl;
        }


        hero.setTextureRect(sf::IntRect(50, 0, 50, 37));
        hero.setScale(1.5,1.5);

        sf::Time elapsed = clock.restart();

        sf::Event event;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // TODO:  pressing Right on keyboard would call hero.animate
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            hero.animate(elapsed);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            hero.animate_left(elapsed);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            hero.jump(0.2);
        }
        hero.updateJump(elapsed);


        // TODO: pressing Down on keyboard would call hero.fall

        hero.falling(elapsed, grass.getGlobalBounds());
        hero.falling(elapsed, grass2.getGlobalBounds());
        hero.falling(elapsed, grass3.getGlobalBounds());


        window.clear(sf::Color::Black);

        sf::Texture texture;
        if (!texture.loadFromFile("C:/Users/kazmi/OneDrive/Dokumenty/GitHub/information_engineering_2/the_platformer/Map/sky.png")) {
            std::cerr << "Could not load texture" << std::endl;
            return 1;
        }


        sf::Sprite sprite;
        // TODO: make this sprite to cover the window with grass
        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(0, 0, 1080, 300));



        // draw everything here...
        window.draw(sprite);
        window.draw(hero);
        window.draw(grass);
        window.draw(grass2);
        window.draw(grass3);



        // end the current frame
        window.display();
    }

    return 0;
}
