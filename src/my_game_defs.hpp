//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_GAME_DEFS_HPP_
#define _MY_GAME_DEFS_HPP_

//
// Grid chunks are used to construct the levels and the overall dungeon
//
#define DUNGEON_GRID_CHUNK_HEIGHT  6  // Levels are split into grids. Each grid can have a room.
#define DUNGEON_GRID_CHUNK_WIDTH   6  // Rooms across and down
#define DUNGEONS_GRID_CHUNK_HEIGHT 10 // The whole underworld
#define DUNGEONS_GRID_CHUNK_WIDTH  10 //
#define DUNGEON_MAX_DEPTH          3  // Max difficulty level
#define DUNGEONS_MAX_DEPTH         8  // Max difficulty level
#define MAX_GRID_CHUNK_HEIGHT      DUNGEONS_GRID_CHUNK_HEIGHT
#define MAX_GRID_CHUNK_WIDTH       DUNGEONS_GRID_CHUNK_WIDTH

//
// How granular gas is. This divides up a single tile.
//
#define DUNGEON_GAS_RESOLUTION 4

#define LEVEL_LOUDEST_SOUND        100 // Decibels
#define LEVEL_FADE_IN_MS           500 // Level start fade animation time
#define LEVEL_FADE_OUT_MS          500 // Level end fade animation time
#define LEVEL_MONST_COUNT_INIT_MAX 25  // Monsters max per level at creation. Want more? You're mad...
#define LEVEL_MONST_COUNT_ABS_MAX  50  // Monsters max per level period.

#define MAP_BORDER_ROCK 1  // Map rock border. If changed from 1 you need to fix collision_check_only
#define MAP_BORDER_ROOM 1  // Room border padding
#define MAP_ROOM_HEIGHT 13 // Max room dimensions
#define MAP_ROOM_WIDTH  13 // Max room dimensions

#define MAP_BORDER_ASCII_AUTO_SCROLL 8 // Max room dimensions

#define LEVELS_ACROSS MAP_WIDTH // World size; no world yet...
#define LEVELS_DOWN   MAP_HEIGHT
#define LEVELS_DEEP   (DUNGEONS_GRID_CHUNK_HEIGHT * 2)

#define MAP_HEIGHT ((DUNGEON_GRID_CHUNK_HEIGHT * MAP_ROOM_HEIGHT) + (MAP_BORDER_ROOM * 2))
#define MAP_WIDTH  ((DUNGEON_GRID_CHUNK_WIDTH * MAP_ROOM_WIDTH) + (MAP_BORDER_ROOM * 2))

#define GAME_MONST_HEALTH_BAR_STEPS 16
#define GAME_MOST_ZOOMED_IN         5
#define GAME_MOST_ZOOMED_OUT        1
#define GAME_DEFAULT_UI_ZOOM        1
#define GAME_DEFAULT_PIX_ZOOM       4

//
// So the mini map looks square even though the map is not
//
#define MAP_MINI_HEIGHT (MAP_HEIGHT * (MAP_WIDTH / MAP_HEIGHT))

#define LIGHT_MAX_RAYS      180 // Max light rays cast
#define LIGHT_FLICKER_SPEED 10  // Max light rays cast
#define MAP_SLOTS           64  // Max things per map slot

#endif
