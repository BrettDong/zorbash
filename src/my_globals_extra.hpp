//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_GLOBALS_EXTRA_HPP_
#define _MY_GLOBALS_EXTRA_HPP_

#include <map>
#include <string>
#include <vector> // linux

extern std::map< std::string, class Tile * > all_tiles;
extern std::vector< class Tile * >           all_tiles_array;

extern std::string g_opt_seed_name;
extern std::string g_opt_player_name;

extern FILE *g_log_stdout;
extern FILE *g_log_stderr;

#endif
