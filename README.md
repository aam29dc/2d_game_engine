[__ (9/27/2023) Learning SDL2 with modern C++__]


[__ (3/17/2022) Progress on PAUSE, as I continue to learn more openGL. __]

# 2d_game_engine alpha 0.1 (C++/openGL)

[___0.1.8___]:

  -added Collision detection to game objects in level.

[___0.1.7___]:

  -added Uniform Buffer Object for projection matrix that is constant across sprite and instance shaders. Added front face culling (CW) for less shader invokes. Added Game_object.h, an extension of Entity.h. (The OO design of classes is likely to change...)

[___0.1.6___]:

  -added drawLevel(with instanced drawing).

[___0.1.5___]:

  -added drawFPS, drawTimer, drawCrosshair, and removed/fixed Gen & Bind buffer: only one vbo is used, and it is updated with new coordinates. Removed EnableVAP, and VAP for vbo(redundant).

[___0.1.4___]:

  -added drawPlayer, a sprite animation of a player moving from keyboard input

[___0.1.3___]:

  -added player.h,.cpp, renamed files, and changed class structures

[___0.1.2___]:

  -added time.h,.cpp, added drawText to sprite renderer

[___0.1.1___]:

  -added object.h,.cpp for game objects, and drawObject with animated frames in sprite renderer

[___0.1___]:

engine has:
  resource manager: (shaders, textures, game objects),
  and sprite renderer
  
  (this is a non-animated screenshot of an early version of the engine. Yes, you can move the character around, and it is correctly animated to show movements in the direction you go in).
![pilot](https://user-images.githubusercontent.com/73267302/156921526-8f22d599-cefb-473f-b003-c8aba987a110.png)
