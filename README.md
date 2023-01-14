# HCMUS Object-Oriented Programming Project - ROAD CROSSING GAME

## GAME DESCRIPTIONS

## ***1. INTRODUCTION***

***Cross the road*** is one of the most popular mini game topics. As the name implies, it requires the player to move a character from one side of the road to the other. But it does not mean that is always an empty road, it is certain that there are several obstacles getting in your way. If you are happened to be impacted, you will lose. One of the typical game is ***Crossy Road***. Unlike this one, this project is made with low-quality graphics (a bunch of ASCII codes printed out to the console screen) so 2D game would not be as attractive as the 3D one. But, in general, it still implements some of the mechanisms of the game.

## ***2. DESCRIPTIONS***

**1. Game starting**

- Initialize a frame representing a road with many lanes.
- Initialize a player charater which is able to move up, right, left, down.
- Render a fleet of vehicles and/or a pack of animals moving in each lane.

**2. Game control**

Unlike the original one, this project is made without allowing the player to use mouse-click or sensitive touch. Instead, players are allowed to use these keys:

- **W**, **A**, **S**, **D** and/or &uarr;, &larr;, &darr;, &rarr; on your keyboard to move *up*, *left*, *down*, *right* respectively.
- And other keys you will explore in the game

**3. Game utilities**

- The game is provided with ``Pause`` to pause your game
- Do not worry about your game progress loss if you have issues that prevent you from continuing the game, ``Save Game`` will save your current progress.
- And to proceed your game, ``Load Game`` is a choice for you.
- Every time you complete a level by crossing the road successfully, you will proceed the game with a new level until 5 levels are completed and register your achievements to the ***Leaderboard*** if you wish.
- Interestingly, in each lane of vehicles, there is a ``Traffic Light`` in order to manipulate the traffic in the game. It has almost all properties and methods just like the real one. Specifically, it has 3 colors (red, yellow, green), which have corresponding duration. It can also be color-switchable and turned on/off.

**4. End Game**
- If the character is not alive (-is collided with any obstacles), *Lose Animation* is brought forth.
- 5 Completed levels
- Press **ESC** to quit the game

## ***3. OVERVIEW OF GAME IMPLEMENTATIONS***
The main purpose of this project is to help us comprehend more the basic concepts of Object-Oriented Programming, understand the mechanisms of *Encapsulation*, *Inheritance* and *Polymorphism*. 

This game is designed with OOP style so there are many classes which were built. 
- The first class to be listed is **OBSTACLE**. It is an abstract class from which subclasses **CCAR**, **CTRUCK**, **CDINOSAUR** and **CBIRD** are derived.

- Next, we have **TrafficLight** class (its purpose is listed above)

- Essentially, to visualize a traffic flow of vehicles or stampedes, class **LANE** is designed to contain a traffic light and a *double-ended queue* (*deque* for short) of pointers to **OBSTACLE** class. Data structure *deque*  is used for picturizing a two-way road controlled by a traffic light. But, logically, animals do not abide by the traffic light rules so they can freely move in one specified direction without stopping.

- **CROAD** is a class to draw road onto the console screen.

- Primarily, class **CPEOPLE** implements the attributes and movements of a human in the game.

- Class **Level** does help to store the information of a particular level in the game.

- One of the most important classes that are built is **CGAME** which plays a primary role when it comes to game manipulation. Therefore, its components are objects listed above (road, level, array of lanes,...).

``Here is an overview of the game diagram``

![CrossingRoadDiagram](https://user-images.githubusercontent.com/102032176/212466787-6e14ecd2-2fc2-47ee-ba25-a3e725bd7b23.png)

- Besides, there are other classes for general game control:
    - In order to draw or print out to the console screen, we have created a pure static class **Graphics**. Class **Graphics** implements multiple static methods to print out many features of the game like drawing objects, the movement of an object, drawing some game utilities, animation when win/lose game,...
    - In view of adjusting the console screen, we also created a supporting class **Controller**. The job of this class is to adjust the size of the screen, get input from the user, manipulate the pop-up screen...etc.
    - Likewise, we have our own built class **Sound** for playing the sound from the background of the game.
- Last but not least, class **Menu** is used for presenting the initial interface to the console screen, which is the very first seen thing in the game. *Menu*, as the name tells, allow the user to choose his/her desired option on the menu list.

---

## IDE
- Microsoft Visual Studio
---
``How to run``
- **Prerequisite**: make sure you have already downloaded ``Microsoft Visual Studio``
- Download this source code, go to file with extension ***.sln*** and open with Microsoft Visual Studio and run your project.


# Teammates
- Me, [Luong Minh Hien](https://github.com/MinHien-git), Dinh Thien Minh and Phan Ngoc Lan.

