# 2d_game_engine alpha 0.1 (C++/openGL)

[___0.1.7___]:

  -added Uniform Buffer Object for projection matrix that is constant across sprite and instance shaders. Added front face culling (CW) for less shade invokes, and improved performance.

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
