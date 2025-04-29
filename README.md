# **cub3d**

## Description
<table>
  <tr>
    <td>
      <img src="https://github.com/ayogun/42-project-badges/blob/main/badges/cub3dm.png" alt="Cub3D 42 project badge" width="400"/>
    </td>
    <td>
      Cub3D is a 42 school team graphic design project where you need to create a 3D dynamic view in a maze, inspired by <a href="http://users.atw.hu/wolf3d/">Wolfenstein 3D</a>.
      Coding in C and using the <a href="https://github.com/42Paris/minilibx-linux">MiniLibX library</a>, an adaptation of the <a href="https://www.x.org/archive/X11R7.5/doc/libX11/libX11.html">Xlib library</a>, we must implement <strong>ray-casting</strong> algorithms.
    </td>
  </tr>
</table>

## Status
<p align="center">
  <img src="https://github.com/sponthus/assets/blob/main/42school/scores/125_outstanding.png" alt="125 grade - outstanding"/>
  <br><strong>Validated 2024-11-28</strong>
  <br>All bonuses
  <br>Outstanding :star: :star:
</p>

## Features
There are two versions of the program: mandatory part and bonus part.
### Mandatory
+ Using ray-casting algorithm and the minilibx library
+ Show different textures depending on the wall orientation (north, south, east, west)
+ Ceiling and floor colors
+ Assets depend on an infile that should be correctly formatted
+ Moving with `W`, `A`, `S`, `D` and closing with `ESC`
+ Rotate left and right with `arrow`

### Bonus
+ Wall collisions
+ Minimap system
+ Doors you can open/close with `E`
+ Animated sprited
+ Mouse directions : rotating the view in every directions using mouse
  
## Extra bonuses
+ Pause screen with `TAB`
+ Settings to change speed, colors
+ Jumping with `SPACE`
+ Crouching with `C`
+ Speeding with `SHIFT_L`

## Clone and compile
Clone the repository and enter it :
```shell
git clone https://github.com/sponthus/cub3d
cd cub3d
make
```
The minilibx library is not included in this repository, the latest version will be cloned while *making* the project.

## Maps
The program takes a map file as an argument. It should be correctly formated : 
* `.cub` format only
* Every texture file linked (`NO`, `SO`, `WE`, `EA`) - ex: `WE ./path_to_the_west_texture`
* Floor `F` and ceiling color `C`, in R,G,B range [0,255] : 0, 255, 255 - ex: `F 220,100,0`
* Map should be composed only of :
__ `0` for empty spaces
__ `1` for walls
__ `N`, `S`, `W`, `E` for the player start orientation
__ In bonus part : `D` for a door
* Elements can be mixed and separated with whitespaces

You can find maps in the [maps/ directory](maps/). Maps in [error/ directory](maps/error/) are incorrectly formatted. 
Make sure you use `_bonus` maps with bonus part only, to avoid an `error`.

## Run
From the project directory, chose your version of the project, then link the map.
```shell
./cub3d maps/basic.cub
```
or
```shell
./cub3d_bonus maps/bonus_doors.cub
```
Enjoy !
---
Made by endoliam and sponthus
