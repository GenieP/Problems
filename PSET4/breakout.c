// breakout.c
//
// Computer Science 50
// Problem Set 4
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include "gevents.h"
#include "gobjects.h"
#include "gwindow.h"

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

//height and width of paddle
#define PADDLEH 20
#define PADDLEW 80

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 1;
    
    // set velocity
    double Xvelocity = 3.0 + drand48();
    double Yvelocity = 2.0;

    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {    
        //detect eventc
        GEvent event = getNextEvent(MOUSE_EVENT);

        if (event != NULL)
        {
            // if event was movement of mouse
            if (getEventType(event) == MOUSE_MOVED)
            {
                // ensure paddle follows cursor on x axis
                double x = getX(event) - (PADDLEW / 2);
                double y = getY(paddle);
                setLocation(paddle, x, y);
            }
        }
    {  
        // move ball
        move(ball, Xvelocity, Yvelocity);
        // lose a life if ball hits bottom of window and reset ball
        if(getY(ball) + getWidth(ball) > getHeight(window))
        {
            lives --;
            setLocation(ball, (getWidth(window)/2 - RADIUS), (getHeight(window)/2 - RADIUS));
            waitForClick();
        }
        // bounce off right edge of window
        else if (getX(ball) + getWidth(ball) >= getWidth(window))
        {
            Xvelocity = -Xvelocity;
        }
        // bounce off left edge of window
        else if(getX(ball) <= 0 )
        {
            Xvelocity = -Xvelocity;
        }
        // bounce off top edge of window
        else if (getY(ball) <= 0)
        {
            Yvelocity = -Yvelocity;
        }        
    }
    pause(10);
    
    // Detect collisions with objects and return object
    GObject object = detectCollision(window, ball);
       // if there is no collision, continue
        if(detectCollision(window, ball) == NULL)
        {
            continue;
        }
        // bounce off paddle
        else if(object == paddle)
        {
            Yvelocity = -Yvelocity;
        }
        // bounce off and remove bricks, increase score
        else if(strcmp(getType(object), "GRect") == 0)
        {
            removeGWindow(window, object);
            updateScoreboard(window, label, points++);
            Yvelocity = -Yvelocity;   
        }
        else continue;
        }
    //If you have deleted all bricks, you win
    if (bricks == 0)
    {
        GLabel text = newGLabel("YOU WIN" );
        setFont(text, "SansSerif-40");
        setColor(text, "RED");
        //set co-ordinates for centre, above scoreboard
        double x = (getWidth(window) - getWidth(text))/2;
        double y = (getHeight(window)/2) - (RADIUS*6);
        setLocation(text, x, y);
        add(window, text);
    }
    // if you have used all your lives, you lose
    else if (lives == 0)
    {
        GLabel text = newGLabel("NO MORE LIVES!" );
        setFont(text, "SansSerif-40");
        setColor(text, "RED");
        //set co-ordinates for centre, above scoreboard
        double x = (getWidth(window) - getWidth(text))/2;
        double y = (getHeight(window)/2) - (RADIUS*6);
        setLocation(text, x, y);
        add(window, text);
    }
    // wait for click before exiting
    waitForClick();
    // game over
    closeGWindow(window);
    return 0;    
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    for (int x = 0; x < COLS; x++)
    { 
        for (int y = 0; y < ROWS; y++)
        {
            //initiate variables for x and y positions of bricks
            int pos_x = x * 40;
            int pos_y = y * 15;
            //create bricks, with colour dependent on row number
            GRect bricks = newGRect(pos_x, pos_y, 35, 10);
            setFilled (bricks, true);
            add(window, bricks);
            if(y % 2 == 0)
            {
                setColor (bricks, "RED");
            }
            else
            {
                setColor (bricks, "GREEN");
            }
        }      
    }
}
/**
 * Instantiates ball in centre of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    GOval ball = newGOval((getWidth(window)/2 - RADIUS), (getHeight(window)/2 - RADIUS), 20, 20 );
    add(window, ball);
    setFilled(ball, true);
    setColor(ball, "CYAN");
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    GRect paddle = newGRect((getWidth(window) - PADDLEW)/2, 520, PADDLEW, PADDLEH);
    add(window, paddle);
    setFilled(paddle, true);
    setColor(paddle, "DARK_GRAY");
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel label = newGLabel("0" );
    setFont(label, "SansSerif-36");
    setColor(label, "LIGHT_GRAY");
    //set co-ordinates for centre, above ball starting position
    double x = (getWidth(window) - getWidth(label))/2;
    double y = (getHeight(window)/2) - (RADIUS*3);
    setLocation(label, x, y);
    add(window, label);
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // centre label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}


/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
