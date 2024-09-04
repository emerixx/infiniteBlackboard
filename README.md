Keybinds:
  ---MODES---
  KEY_LEFT_SHIFT - Shift mode (SM)
  KEY_LEFT_CTRL - Ctrl mode (CM)
  KEY_E - Eraser mode (draws background color) (EM)
  KEY_C - Change color mode (CCM)
  KEY_D - IF CM: toggle debug mode (show debug info)
  ---MOUSE---
  MOUSE_BUTTON_RIGHT (down) - Move the drawing surface
  MOUSE_BUTTON_RIGHT (press) - IF CCM: go to next available color
  MOUSE_BUTTON_LEFT  (down) - Draw using current color
  ---KEYBOARD---
  KEY_D - IF SM: clear surface
  KEY_UP - IF CCM: next color. ELSE: move surface 1/2 window height down
  KEY_DOWN - IF CCM: prev color. ELSE: move surface 1/2 window height up
  KEY_LEFT - move surface 1/2 window width right
  KEY_RIGHT - move surface 1/2 window width left

| Type      | Keybind        | Action                                     |
| :----:    | :------------: | :----------------------------------------: |
| Mode      | KEY_LEFT_SHIFT | Shift mode (SM)                            |
| Mode      | KEY_LEFT_CTRL  | Ctrl mode (CM)                             |
| Mode      | KEY_E          | Eraser mode (draws background color) (EM)  |
| Mode      | KEY_C          | Change color mode (CCM)                    |
| Mode      | KEY_D          | IF CM: toggle debug mode (show debug info) |
| ---       | ---            | ---                                        |
| Keyboard  | KEY_D          | IF SM: clear surface                       |
| Keyboard  | KEY_UP         | IF CCM: next color. ELSE: move surface win height/2 down |
| Keyboard  | KEY_DOWN       | IF CCM: prev color. ELSE: move surface win height/2 up |
| Keyboard  | KEY_LEFT       | move surface 1/2 window width right        |
| Keyboard  | KEY_RIGHT      | move surface 1/2 window width left         |
| ---       | ---            | ---                                        |
| Mouse     | MOUSE_BUTTON_RIGHT (down)   | Move the drawing surface      |
| Mouse     | MOUSE_BUTTON_RIGHT (press)  | IF CCM: go to next available color |
| Mouse     | MOUSE_BUTTON_LEFT (down)    | Draw using current color      | 
