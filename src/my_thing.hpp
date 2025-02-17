//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_THING_HPP_
#define _MY_THING_HPP_

#include <array>
#include <functional> // for std::function
#include <list>

#include "my_color.hpp"
#include "my_dice.hpp"
#include "my_format_str_attribute.hpp"
#include "my_fwd.hpp"
#include "my_point.hpp"
#include "my_point3d.hpp"
#include "my_thing_ai.hpp"
#include "my_thing_defs.hpp"
#include "my_thing_id.hpp"
#include "my_time.hpp"

typedef enum {
  THING_SHOVE_TRIED_AND_FAILED,
  THING_SHOVE_TRIED_AND_PASSED,
  THING_SHOVE_NEVER_TRIED,
} ThingShoved;

typedef enum {
  THING_MOVE_REASON_MOUSE,
  THING_MOVE_REASON_AI,
} ThingMoveReason;

typedef struct {
  uint16_t tile_outline;
  uint16_t bl1_tile;
  uint16_t bot1_tile;
  uint16_t br1_tile;
  uint16_t left1_tile;
  uint16_t right1_tile;
  uint16_t tl1_tile;
  uint16_t top1_tile;
  uint16_t tr1_tile;
  uint16_t bl2_tile;
  uint16_t bot2_tile;
  uint16_t bot3_tile;
  uint16_t br2_tile;
  uint16_t left2_tile;
  uint16_t right2_tile;
  uint16_t tl2_tile;
  uint16_t top2_tile;
  uint16_t tr2_tile;
} ThingTiles;

typedef struct {
  int  preferred_equip;
  bool preferred_equip_set;
  bool radial_effect;
} UseOptions;

typedef struct {
  //
  // If given a real hitter, prefer that; for example a player slamming a door on a monster.
  // real_hitter would be the player. hitter would be the door.
  //
  Thingp real_hitter;
  //
  // Return values
  //
  bool victim_attacked;
  bool victim_overlaps;
  //
  // Allowed to hit solid rock. Normally disabled to avoid weapon damage.
  // Enabled if you click on a rock.
  //
  bool allow_hitting_walls;
  //
  // Monst is using its natural attack.
  //
  bool nat_att;
  //
  // Prefer natural attack.
  //
  bool prefer_nat_att;
  //
  // Can also shove.
  //
  bool shove_allowed;
  //
  // Critical hit.
  //
  bool crit;
  //
  // Used in moving to pass on intent to attack.
  //
  bool attack_allowed;
  //
  // If attack_at is not set, we should look around for a target.
  //
  bool attack_at_set;
  //
  // Attack types;
  //
  bool attack_water;
  bool attack_acid;
  bool attack_cold;
  bool attack_crush;
  bool attack_digest;
  bool attack_draining;
  bool attack_energy;
  bool attack_fire;
  bool attack_drown;
  bool attack_bite;
  bool attack_claw;
  bool attack_lightning;
  bool attack_natural;
  bool attack_necrosis;
  bool attack_poison;
  //
  // Set if damage is already pre calculated
  //
  bool damage_set;
  int  damage;
  //
  // For multiple attacks, which one is this?
  //
  unsigned char attack_num;
  //
  // How many attempts to find a target
  //
  unsigned char attempt;
  //
  // Where we want to attack
  //
  point attack_at;
  //
  // This is the swing animation.
  //
  std::string used_as;
} AttackOptions;

typedef class Thing_
{
private:
  //
  // As this is called a lot, probably worth the memory
  //
  Tpp mytp {};

public:
  Thing_(void);
  ~Thing_(void);

public:
  ThingInfop  _infop {};
  ThingItemsp _itemsp {};
  ThingAip    _aip {};

  Levelp level {};

  ThingId    id {}; // Unique per thing.
  ThingTiles tiles {};

  fpoint interpolated_at;

  ts_t ts_next_frame {};

  point last_at;       // Previous hop where we were.
  point curr_at;       // Grid coordinates.
  point last_attached; // Where we were last pushed onto the map/
  point last_ascii_at; // Last ascii tile on screen position
  point last_blit_br;  // Last blit coords
  point last_blit_tl;  // Offset from top left of map
  point last_blit_at;  // Center of the above

  uint16_t tile_curr {};
  uint16_t frame_count {};
  int16_t  tp_id {-1}; // Common settings

  uint8_t z_depth {};
  uint8_t laser_count {};

  int16_t temperature {TEMPERATURE_ROOM}; // Celsius

  //
  // Used for alpha fading and giving tiles slightly sifferent colors when
  // in ascii mode; to help with visibility.
  //
  color blit_bg_color;
  color blit_fg_color;

  uint64_t dir : 4 {}; // Direction

  /////////////////////////////////////////////////////////////////////////
  // Keep these sorted alphabetically to make it easier to see additions
  // and always update game_load.cpp and game_save.cpp
  //
  // | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
  // v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v
  /////////////////////////////////////////////////////////////////////////
  // begin sort marker5 {
  uint64_t corpse_cleanup                               : 1 {};
  uint64_t gfx_ascii_animated                           : 1 {};
  uint64_t gfx_pixelart_animated                        : 1 {};
  uint64_t has_attacked_player                          : 1 {};
  uint64_t has_ever_moved                               : 1 {};
  uint64_t has_light                                    : 1 {};
  uint64_t has_projectile                               : 1 {}; // current projectile being fired
  uint64_t has_seen_player_msg_shown                    : 1 {};
  uint64_t is_activated                                 : 1 {}; // this skill is activated
  uint64_t is_attached                                  : 1 {}; // is attached to the level
  uint64_t is_being_destroyed                           : 1 {};
  uint64_t is_bouncing                                  : 1 {};
  uint64_t is_burnt                                     : 1 {}; // burnt by ice and cannot move
  uint64_t is_changing_level                            : 1 {}; // is in the process of changing level
  uint64_t is_dead                                      : 1 {};
  uint64_t is_dying                                     : 1 {}; // is currently in the throes of death
  uint64_t is_facing_left                               : 1 {};
  uint64_t is_fadeup                                    : 1 {}; // for text that fades upwards
  uint64_t is_falling                                   : 1 {};
  uint64_t is_frozen                                    : 1 {}; // frozen by ice and cannot move
  uint64_t is_hidden                                    : 1 {};
  uint64_t is_hunger_level_gorged                       : 1 {};
  uint64_t is_hunger_level_hungry                       : 1 {};
  uint64_t is_hunger_level_satiated                     : 1 {};
  uint64_t is_hunger_level_starving                     : 1 {};
  uint64_t is_in_lava                                   : 1 {};
  uint64_t is_in_water                                  : 1 {};
  uint64_t is_jumping                                   : 1 {};
  uint64_t is_key_in_lock                               : 1 {}; // key stuck in rusty lock?
  uint64_t is_moving                                    : 1 {}; // is currently moving tiles
  uint64_t is_open                                      : 1 {};
  uint64_t is_resurrected                               : 1 {}; // has finished resurrecting
  uint64_t is_resurrecting                              : 1 {}; // is currently resurrecing
  uint64_t is_resurrection_blocked                      : 1 {}; // blocked from resurrection
  uint64_t is_ring2                                     : 1 {}; // for 2nd rings
  uint64_t is_scheduled_for_death                       : 1 {}; // will die in next game loop
  uint64_t is_scheduled_for_gc                          : 1 {};
  uint64_t is_scheduled_for_jump_end                    : 1 {};
  uint64_t is_seen_by_player_msg_shown                  : 1 {};
  uint64_t is_sleeping                                  : 1 {};
  uint64_t is_teleporting                               : 1 {};
  uint64_t is_the_grid                                  : 1 {}; // is the backbone of the level
  uint64_t is_the_player                                : 1 {};
  uint64_t is_visible_to_player                         : 1 {};
  uint64_t is_waiting                                   : 1 {}; // is waiting on this tick
  uint64_t is_waiting_to_ascend_dungeon                 : 1 {};
  uint64_t is_waiting_to_ascend_sewer                   : 1 {};
  uint64_t is_waiting_to_descend_dungeon                : 1 {};
  uint64_t is_waiting_to_descend_sewer                  : 1 {};
  uint64_t is_waiting_to_leave_level_has_completed_fall : 1 {};
  uint64_t is_wounded_msg                               : 1 {};
  uint64_t was_frozen                                   : 1 {}; /* was frozen at the start of the tick */
  // end sort marker5 {

  //
  // These are flags used to make sure we set or unset flags onto the level only once.
  //

  // begin sort marker6 {
  uint64_t i_set_is_able_to_burn            : 1 {}; // may produce a flame
  uint64_t i_set_is_acid                    : 1 {};
  uint64_t i_set_is_ascend_dungeon          : 1 {};
  uint64_t i_set_is_ascend_sewer            : 1 {};
  uint64_t i_set_is_barrel                  : 1 {};
  uint64_t i_set_is_basalt                  : 1 {};
  uint64_t i_set_is_block_of_ice            : 1 {};
  uint64_t i_set_is_brazier                 : 1 {};
  uint64_t i_set_is_bridge                  : 1 {};
  uint64_t i_set_is_carnivorous_plant       : 1 {};
  uint64_t i_set_is_chasm                   : 1 {};
  uint64_t i_set_is_combustible             : 1 {}; // may not produce a flame
  uint64_t i_set_is_corpse                  : 1 {};
  uint64_t i_set_is_corridor                : 1 {};
  uint64_t i_set_is_cursor_path_blocker     : 1 {};
  uint64_t i_set_is_cursor_path_hazard      : 1 {};
  uint64_t i_set_is_deep_water              : 1 {};
  uint64_t i_set_is_descend_dungeon         : 1 {};
  uint64_t i_set_is_descend_sewer           : 1 {};
  uint64_t i_set_is_dirt                    : 1 {};
  uint64_t i_set_is_door                    : 1 {};
  uint64_t i_set_is_dry_grass               : 1 {};
  uint64_t i_set_is_enchantstone            : 1 {};
  uint64_t i_set_is_fire                    : 1 {};
  uint64_t i_set_is_floor                   : 1 {};
  uint64_t i_set_is_foilage                 : 1 {};
  uint64_t i_set_is_food                    : 1 {};
  uint64_t i_set_is_gas_blocker             : 1 {};
  uint64_t i_set_is_gold                    : 1 {};
  uint64_t i_set_is_green_blood             : 1 {};
  uint64_t i_set_is_hazard                  : 1 {};
  uint64_t i_set_is_heavy                   : 1 {};
  uint64_t i_set_is_key                     : 1 {};
  uint64_t i_set_is_lava                    : 1 {};
  uint64_t i_set_is_light_blocker           : 1 {};
  uint64_t i_set_is_light_blocker_for_monst : 1 {};
  uint64_t i_set_is_mob                     : 1 {};
  uint64_t i_set_is_monst                   : 1 {};
  uint64_t i_set_is_necrotic_danger_level   : 1 {};
  uint64_t i_set_is_obs_destructable        : 1 {};
  uint64_t i_set_is_obs_for_jump_landing    : 1 {};
  uint64_t i_set_is_obs_wall_or_door        : 1 {};
  uint64_t i_set_is_poisonous_danger_level  : 1 {};
  uint64_t i_set_is_potion                  : 1 {};
  uint64_t i_set_is_red_blood               : 1 {};
  uint64_t i_set_is_ring                    : 1 {};
  uint64_t i_set_is_ripple                  : 1 {};
  uint64_t i_set_is_rock                    : 1 {};
  uint64_t i_set_is_secret_door             : 1 {};
  uint64_t i_set_is_shallow_water           : 1 {};
  uint64_t i_set_is_shovable                : 1 {};
  uint64_t i_set_is_skillstone              : 1 {};
  uint64_t i_set_is_smoke                   : 1 {};
  uint64_t i_set_is_spiderweb               : 1 {};
  uint64_t i_set_is_staff                   : 1 {};
  uint64_t i_set_is_steam                   : 1 {};
  uint64_t i_set_is_sticky                  : 1 {};
  uint64_t i_set_is_torch                   : 1 {};
  uint64_t i_set_is_treasure_type           : 1 {};
  uint64_t i_set_is_wall                    : 1 {};
  uint64_t i_set_is_wand                    : 1 {};
  uint64_t i_set_is_wet_grass               : 1 {};
  uint64_t i_set_noise_blocker              : 1 {};
  uint64_t i_set_water                      : 1 {};
  // end sort marker6 {

  /////////////////////////////////////////////////////////////////////////
  // ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^
  // | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
  //
  // Keep these sorted alphabetically to make it easier to see additions
  // and always update game_load.cpp and game_save.cpp
  /////////////////////////////////////////////////////////////////////////
  // Fields not worth saving
  uint64_t debug                 : 1 {};
  uint64_t is_being_dropped      : 1 {};
  uint64_t is_blitted            : 1 {};
  uint64_t inited_tiles          : 1 {};
  uint64_t has_external_particle : 1 {}; // current in motion particle
  uint64_t has_internal_particle : 1 {}; // current in motion particle
  uint64_t ai_tried_to_wander    : 1 {}; // tried to wander
#ifdef ENABLE_DEBUG_THING_SER
  std::string debug_str;
#endif

public:
  //
  // Walk all items and bags to get the items
  //
  std::list< Thingp > amulet_list(void);
  std::list< Thingp > armor_list(void);
  std::list< Thingp > boots_list(void);
  std::list< Thingp > cloak_list(void);
  std::list< Thingp > food_list(void);
  std::list< Thingp > gauntlet_list(void);
  std::list< Thingp > helmet_list(void);
  std::list< Thingp > carried_item_only_list(void);
  std::list< Thingp > carried_and_equipped_item_list(void);
  std::list< Thingp > ring_list(void);
  std::list< Thingp > shield_list(void);
  std::list< Thingp > treasure_list(void);
  std::list< Thingp > wand_list(void);
  std::list< Thingp > weapon_list(void);

  std::vector< Thingp > amulet_vector(void);
  std::vector< Thingp > armor_vector(void);
  std::vector< Thingp > boots_vector(void);
  std::vector< Thingp > cloak_vector(void);
  std::vector< Thingp > food_vector(void);
  std::vector< Thingp > gauntlet_vector(void);
  std::vector< Thingp > helmet_vector(void);
  std::vector< Thingp > carried_item_only_vector(void);
  std::vector< Thingp > carried_and_equipped_item_vector(void);
  std::vector< Thingp > ring_vector(void);
  std::vector< Thingp > shield_vector(void);
  std::vector< Thingp > treasure_vector(void);
  std::vector< Thingp > wand_vector(void);
  std::vector< Thingp > weapon_vector(void);

  ThingShoved try_to_shove(Thingp it, point delta, bool force = false);
  ThingShoved try_to_shove(point future_pos);
  ThingShoved try_to_shove_into_hazard(Thingp it, point delta);

  ThingId on_fire_anim_id(void);
  ThingId on_fire_anim_id_set(ThingId);

  ThingId equip_id(int equip);
  ThingId equip_id_carry_anim(int equip);
  ThingId equip_id_use_anim(int equip);

  ThingId equip_id_set(ThingId, int equip);
  ThingId equip_id_carry_anim_set(ThingId, int equip);
  ThingId equip_id_use_anim_set(ThingId, int equip);

  Thingp best_fire_at_target_get(void);
  Thingp best_visible_target_get(void);
  Thingp equip_carry_anim(int equip);
  Thingp equip_get(int equip);
  Thingp equip_use_anim(int equip);
  Thingp immediate_mob(void);
  Thingp immediate_owner(void);
  Thingp immediate_spawned_owner(void);
  Thingp in_the_way_for_firing(const point s, const point e, int x, int y);
  Thingp in_the_way_for_jumping(const point s, const point e, int x, int y);
  Thingp in_the_way_for_throwing(const point s, const point e, int x, int y);
  Thingp item_targetted_use_at(Thingp wand, point at);
  Thingp item_targetted_use_at(Thingp wand, Thingp target);
  Thingp leader(void);
  Thingp most_dangerous_adjacent_thing(void);
  Thingp most_dangerous_visible_thing(void);
  Thingp projectile_fire_at(Thingp wand, const std::string &item, point at);
  Thingp projectile_fire_at(Thingp wand, const std::string &item, Thingp target);
  Thingp spawn_at(const std::string &what);
  Thingp spawn_at(const std::string &what, point p);
  Thingp spawn_at_if_possible(const std::string &what);
  Thingp spawn_owned_thing_at_my_position(const std::string &what);
  Thingp top_mob(void);
  Thingp top_owner(void);
  Thingp top_spawned_owner(void);
  Thingp debuff_find(const std::string &);
  Thingp buff_find(const std::string &);

  std::vector< Thingp > in_the_way_for_jumping(const point s, const point e, size_t max_elems = 0);
  std::vector< Thingp > in_the_way_for_firing(const point s, const point e, size_t max_elems = 0);

  // begin sort marker1 {
  bool ai_blocked_completely(void);
  bool ai_blocked(void);
  bool ai_choose_avoid_goals(std::multiset< Goal > &avoid_goals, const Goal &goal);
  bool ai_choose_immediately_adjacent_goal(void);
  bool ai_choose_wander(point &nh);
  bool ai_create_on_fire_path(point &nh, const point start, const point end);
  bool ai_create_path(point &nh, const point start, const point end);
  bool ai_create_path_to_goal(int minx, int miny, int maxx, int maxy, int search_type = 0);
  bool ai_create_path_to_single_goal(int, int, int, int, const Goal &goal, const struct Dmap_ *saved_dmap);
  bool ai_escape(void);
  bool ai_obstacle_for_me(point);
  bool ai_obstacle(fpoint);
  bool ai_obstacle(Thingp);
  bool ai_on_fire_choose_target(point &nh);
  bool ai_on_fire(void);
  bool ai_tick(bool recursing = false);
  bool ai_wander(void);
  bool any_adjacent_monst(void);
  bool any_unfriendly_monst_visible(void);
  bool ascend_dungeon(bool force = false, point3d next_level = point3d(0, 0, 0));
  bool ascend_dungeon_tick(void);
  bool ascend(int z);
  bool ascend_sewer_tick(void);
  bool ascend_sewer(void);
  bool attack(point future_pos);
  bool attack(Thingp victim, AttackOptions *);
  bool bag_add_test(Thingp);
  bool bag_add(Thingp);
  bool bag_can_place_anywhere(Thingp item, point &pos);
  bool bag_can_place_at(Thingp item, point pos);
  bool bag_compress(void);
  bool bag_contains(Thingp item);
  bool bag_place_at(Thingp item, point pos);
  bool bag_remove_at(Thingp item, point pos);
  bool bag_remove(Thingp);
  bool bounce(float bounce_height, float bounce_fade, ts_t ms, int bounce_count);
  bool buff_add_if_not_found(Tpp what);
  bool buff_add(Thingp it);
  bool buff_add(Tpp what);
  bool buffbox_id_insert(Thingp what);
  bool buffbox_id_remove(Thingp what);
  bool buff_find_is_aquatic(void);
  bool buff_find_is_fire_proof(void);
  bool buff_find_is_slippery(void);
  bool buff_remove(Thingp it);
  bool buff_remove(Tpp what);
  bool buff_use(Thingp it);
  bool can_eat(const Thingp it);
  bool can_eat_something(void);
  bool can_enchant_something(void);
  bool can_learn_something(void);
  bool cannot_avoid(Thingp attacker);
  bool carrying_anything(void);
  bool carry(Thingp w, bool can_equip = true);
  bool change_owner(Thingp new_owner);
  bool check_anything_to_carry(bool auto_collect_allowed);
  bool close_door(Thingp door);
  bool collision_add_candidates(Thingp it, point future_pos, int x, int y, int dx, int dy);
  bool collision_check_and_handle_at(AttackOptions *);
  bool collision_check_and_handle_at(point future_pos, AttackOptions *);
  bool collision_check_and_handle_nearby(point future_pos, AttackOptions *);
  bool collision_check_and_handle(point future_pos, AttackOptions *, float radius);
  bool collision_check_and_handle(Thingp it, point future_pos, int x, int y, int dx, int dy);
  bool collision_check_do(void);
  bool collision_check_only(point future_pos);
  bool collision_check_only(Thingp it, int x, int y, int dx, int dy);
  bool collision_check_only(Thingp it, point future_pos);
  bool collision_check_only(void);
  bool collision_find_best_target(AttackOptions *attack_options);
  bool collision_obstacle(point);
  bool collision_obstacle(Thingp);
  bool consume(Thingp it);
  bool coords_get(point &blit_tl, point &blit_br, point &pre_blit_tl, point &pre_blit_br, Tilep &tile, bool refl);
  bool cursor_path_pop_first_move(ThingMoveReason);
  bool debuff_add_if_not_found(Tpp what);
  bool debuff_add(Thingp it);
  bool debuff_add(Tpp what);
  bool debuffbox_id_insert(Thingp what);
  bool debuffbox_id_remove(Thingp what);
  bool debuff_remove(Thingp it);
  bool debuff_remove(Tpp what);
  bool debuff_use(Thingp it);
  bool descend_dungeon(bool force = false, point3d next_level = point3d(0, 0, 0));
  bool descend_dungeon_tick(void);
  bool descend_sewer_tick(void);
  bool descend_sewer(void);
  bool describe_when_hovered_over_in_rightbar(void);
  bool describe_when_hovering_over(void);
  bool drop_from_ether(Thingp w);
  bool drop_into_ether(Thingp w);
  bool drop(Thingp w);
  bool drop(Thingp w, Thingp target, bool stolen = false);
  bool eat_something(void);
  bool eat(Thingp it);
  bool enchant_random_item_with_stone(void);
  bool enchant_without_stone(Thingp);
  bool enchant_with_stone(Thingp);
  bool equipped_anything(void);
  bool equip(Thingp w, int equip);
  bool equip_use(bool forced, int equip, AttackOptions *);
  bool equip_use_may_attack(int equip);
  bool equip_use_must_attack(int equip);
  bool fall_to_next_level(void);
  bool fall(void);
  bool fire_at_and_choose_target(Thingp, UseOptions *options = nullptr);
  bool fire_at_target(void);
  bool fire_at(Thingp item, Thingp target);
  bool fire_at(Thingp target);
  bool fire_choose_target(Thingp item);
  bool has_temperature(void);
  bool health_boost_would_occur(int v);
  bool hunger_boost_would_occur(int v);
  bool idle_check(void);
  bool if_matches_then_dead(const std::string &what, const point p);
  bool inventory_shortcuts_insert(Thingp what);
  bool inventory_shortcuts_remove(Thingp what);
  bool inventory_shortcuts_remove(Thingp what, Thingp target);
  bool is_blocking_terrain(const Thingp it);
  bool is_bloodied(void);
  bool is_carrying_an_item(void);
  bool is_carrying_treasure(void);
  bool is_disliked_by_me(const point p);
  bool is_disliked_by_me(const Thingp it);
  bool is_edible(const Thingp it);
  bool is_enemy(Thingp it);
  bool is_equipped(Thingp item);
  bool is_friend(Thingp it);
  bool is_hated_by_me(const point p);
  bool is_hated_by_me(const Thingp it);
  bool is_on_fire(void);
  bool is_state_sleeping(void);
  bool is_stuck_check(void);
  bool is_stuck_currently(void);
  bool is_target_select(Thingp item);
  bool is_to_be_avoided(Thingp attacker);
  bool item_choose_target(Thingp item, Thingp victim = nullptr);
  bool jump_attack(Thingp it = nullptr);
  bool laser_anim_exists(void);
  bool laser_choose_target(Thingp item, Thingp victim = nullptr);
  bool laser_fire_at(Thingp staff, const std::string &item, point at, UseOptions *use_options = nullptr);
  bool laser_fire_at(Thingp staff, const std::string &item, Thingp target, UseOptions *use_options = nullptr);
  bool learn_random_skill(void);
  bool map_offset_coords_get(point &blit_tl, point &blit_br, Tilep &tile, bool reflection);
  bool map_treasure_available(void);
  bool matches(const std::string &what);
  bool move_away_from_entrance(void);
  bool move_no_shove_attack_allowed(point future_pos);
  bool move_no_shove_no_attack(point future_pos);
  bool move(point to);
  bool move(point to, uint8_t u, uint8_t d, uint8_t l, uint8_t r, uint8_t att, uint8_t idl, AttackOptions *);
  bool move_to_or_attack_check_only(const point nh);
  bool move_to_or_attack(const point);
  bool move_to_or_escape_check_only(const point nh);
  bool move_to_or_escape(const point);
  bool move_to_try(const point, const bool escaping, bool check_only);
  bool nat_att(Thingp victim);
  bool on_fire_set(const std::string &why);
  bool on_firing_at_something(Thingp hitter);
  bool on_tick(void);
  bool open_door(Thingp door);
  bool open(Thingp it);
  bool open(void);
  bool particle_anim_exists(void);
  bool path_pop_next_move(ThingMoveReason);
  bool place(const std::string &what, const point p);
  bool player_is_ready_for_messages(std::string &why);
  bool player_is_ready_for_messages(void);
  bool player_is_ready_for_thing_info(void);
  bool possible_to_attack_at(point at);
  bool possible_to_attack(const Thingp it);
  bool projectile_anim_exists(void);
  bool projectile_choose_target(Thingp item, Thingp victim = nullptr);
  bool same_leader(Thingp it);
  bool same_mob(Thingp it);
  bool shove_ok(point future_pos);
  bool skill_add(Thingp it);
  bool skill_add(Tpp what);
  bool skillbox_id_insert(Thingp what);
  bool skillbox_id_remove(Thingp what);
  bool skill_remove(Thingp it);
  bool skill_use(Thingp it);
  bool spawn_fire(const std::string &what, int radius);
  bool spawn_gas_poison(int radius);
  bool spawn_next_to(const std::string &what);
  bool spawn_next_to_or_on_monst(const std::string &what);
  bool spawn_radius_range(const std::string &what, int rad_min, int rad_max);
  bool spawn_radius_range(Thingp parent, Thingp target, const std::string &what, int rad_min, int rad_max);
  bool state_idle(Thingp threat, int minx, int miny, int maxx, int maxy);
  bool state_moving(void);
  bool state_open_inventory(void);
  bool state_repack_inventory(void);
  bool state_resting(bool &do_something, bool &wait);
  bool state_sleeping(bool &do_something, bool &wait);
  bool state_using_enchantstone(void);
  bool state_using_skillstone(void);
  bool steal_item_from(Thingp);
  bool steal_treasure_from(Thingp);
  bool teleport_attack(Thingp it = nullptr);
  bool teleport_carefree(point to);
  bool teleport_carefree(point to, bool *too_far);
  bool teleport_carefully(point to);
  bool teleport_carefully(point to, bool *too_far);
  bool teleport(point to, bool carefully, bool *too_far);
  bool teleport_randomly_away_from_player(void);
  bool teleport_randomly_towards_player(void);
  bool teleport_randomly(void);
  bool thing_check_for_cold_damage(void);
  bool thing_check_for_heat_damage(void);
  bool thing_sound_play_channel(int chan, const std::string &alias);
  bool thing_sound_play(const std::string &alias);
  bool throw_item_choose_target(Thingp item);
  bool too_far_from_leader(point p);
  bool too_far_from_leader(point p, float delta);
  bool too_far_from_leader(void);
  bool too_far_from_mob(point p);
  bool too_far_from_mob(point p, float delta);
  bool too_far_from_mob(void);
  bool torch_tick(void);
  bool try_harder_to_jump(void);
  bool try_harder_to_teleport(void);
  bool try_to_carry_if_worthwhile_dropping_items_if_needed(Thingp it);
  bool try_to_carry(Thingp w);
  bool try_to_enchant_items(void);
  bool try_to_escape(void);
  bool try_to_jump_away_from_player(void);
  bool try_to_jump_carefree(point to);
  bool try_to_jump_carefree(point to, bool *too_far);
  bool try_to_jump_carefully(point to);
  bool try_to_jump_carefully(point to, bool *too_far);
  bool try_to_jump(point to, bool carefully, bool *too_far);
  bool try_to_jump_towards_player(void);
  bool try_to_jump(void);
  bool try_to_use_amulet(void);
  bool try_to_use_armor(void);
  bool try_to_use_boots(void);
  bool try_to_use_cloak(void);
  bool try_to_use_gauntlet(void);
  bool try_to_use_helmet(void);
  bool try_to_use_rings(void);
  bool try_to_use_shield(void);
  bool try_to_use_weapon(void);
  bool unequip(const char *why, int equip, bool allowed_to_recarry);
  bool unequip_me_from_owner(const char *why, bool allowed_to_recarry);
  bool use(Thingp w, UseOptions *options = nullptr);
  bool victim_attack_best_at(int equip, AttackOptions *);
  bool victim_attack_best(int equip, AttackOptions *);
  bool victim_attack_best_(int equip, AttackOptions *);
  bool victim_attack_swing(int equip, Thingp best, point best_hit_at, AttackOptions *attack_options);
  bool wake(const std::string &reason);
  bool will_avoid_monst(const point p);
  bool will_avoid_monst(const Thingp it);
  bool will_prefer_terrain(const Thingp it);
  bool worth_eating(const Thingp it);
  // end sort marker1 {

  std::vector< std::string > on_get_text_long_description(void);

  const Dice &damage_water_dice(void);
  const Dice &damage_acid_dice(void);
  const Dice &damage_cold_dice(void);
  const Dice &damage_crush_dice(void);
  const Dice &damage_digest_dice(void);
  const Dice &damage_draining_dice(void);
  const Dice &damage_energy_dice(void);
  const Dice &damage_fire_dice(void);
  const Dice &damage_drown_dice(void);
  const Dice &damage_bite_dice(void);
  const Dice &damage_claw_dice(void);
  const Dice &damage_lightning_dice(void);
  const Dice &damage_melee_dice(void);
  const Dice &damage_nat_att_dice(void);
  const Dice &damage_necrosis_dice(void);
  const Dice &damage_poison_dice(void);

  const Dice &gold_value_dice(void);
  const Dice &health_initial_dice(void);
  const Dice &lifespan_dice(void);
  const Dice &nutrition_dice(void);
  const Dice &on_idle_tick_freq_dice(void);
  const Dice &spawn_group_size_dice(void);
  const Dice &resurrect_dice(void);

  const ThingId &immediate_mob_id(void);
  const ThingId &leader_id(void);
  const ThingId &immediate_owner_id(void);
  const ThingId &immediate_spawned_owner_id(void);
  const ThingId &top_owner_id(void);
  const ThingId &mob_id_set(const ThingId &v);
  const ThingId &leader_id_set(const ThingId &v);
  const ThingId &owner_id_set(const ThingId &v);
  const ThingId &spawned_owner_id_set(const ThingId &v);

  const Tpp tp_slow(void);

  //
  // It's used a lot, so inline candidate
  //
  const Tpp tp(void)
  {
    if (likely(mytp != nullptr)) {
      return (mytp);
    }

    return tp_slow();
  }

  const Tpp tp_or_update(void);

  const fpoint &interpolated_at_get(void);

  const std::string damage_acid_dice_str(void);
  const std::string damage_water_dice_str(void);
  const std::string damage_cold_dice_str(void);
  const std::string damage_crush_dice_str(void);
  const std::string damage_digest_dice_str(void);
  const std::string damage_draining_dice_str(void);
  const std::string damage_energy_dice_str(void);
  const std::string damage_fire_dice_str(void);
  const std::string damage_drown_dice_str(void);
  const std::string damage_bite_dice_str(void);
  const std::string damage_claw_dice_str(void);
  const std::string damage_lightning_dice_str(void);
  const std::string damage_melee_dice_str(void);
  const std::string damage_nat_att_dice_str(void);
  const std::string damage_necrosis_dice_str(void);
  const std::string damage_poison_dice_str(void);
  const std::string danger_level_str(Thingp); // Cannot return reference
  const std::string text_long_description2(void);
  const std::string text_long_description3(void);
  const std::string text_long_description(void);

  const std::string &damage_nat_att_type(void);
  const std::string &dead_reason_get(void);
  const std::string &equip_carry_anim(void);
  const std::string &gfx_anim_use(void);
  const std::string &gold_value_dice_str(void);
  const std::string &health_initial_dice_str(void);
  const std::string &is_allied_with(void);
  const std::string &lifespan_dice_str(void);
  const std::string &light_color(void);
  const std::string &msg_get(void);
  const std::string &name(void);
  const std::string &nutrition_dice_str(void);
  const std::string &on_attacking_dmg_acid_do(void);
  const std::string &on_attacking_dmg_cold_do(void);
  const std::string &on_attacking_dmg_crush_do(void);
  const std::string &on_attacking_dmg_digest_do(void);
  const std::string &on_attacking_dmg_draining_do(void);
  const std::string &on_attacking_dmg_energy_do(void);
  const std::string &on_attacking_dmg_fire_do(void);
  const std::string &on_attacking_dmg_drown_do(void);
  const std::string &on_attacking_dmg_bite_do(void);
  const std::string &on_attacking_dmg_claw_do(void);
  const std::string &on_attacking_dmg_lightning_do(void);
  const std::string &on_attacking_dmg_melee_do(void);
  const std::string &on_attacking_dmg_nat_att_do(void);
  const std::string &on_attacking_dmg_necrosis_do(void);
  const std::string &on_attacking_dmg_poison_do(void);
  const std::string &on_attacking_dmg_stat_att_do(void);
  const std::string &on_attacking_dmg_stat_con_do(void);
  const std::string &on_attacking_dmg_stat_str_do(void);
  const std::string &on_attacking_dmg_water_do(void);
  const std::string &on_awake_do(void);
  const std::string &on_born_do(void);
  const std::string &on_death_do(void);
  const std::string &on_death_of_a_follower_do(void);
  const std::string &on_death_of_my_leader_do(void);
  const std::string &on_enchant_do(void);
  const std::string &on_equip_do(void);
  const std::string &on_fall_do(void);
  const std::string &on_final_use_do(void);
  const std::string &on_firing_at_something_do(void);
  const std::string &on_get_text_long_description_do(void);
  const std::string &on_idle_tick_freq_dice_str(void);
  const std::string &on_jump_do(void);
  const std::string &on_lifespan_tick_do(void);
  const std::string &on_move_do(void);
  const std::string &on_open_do(void);
  const std::string &on_owner_add_do(void);
  const std::string &on_owner_attack_dmg_acid_do(void);
  const std::string &on_owner_attack_dmg_cold_do(void);
  const std::string &on_owner_attack_dmg_crush_do(void);
  const std::string &on_owner_attack_dmg_digest_do(void);
  const std::string &on_owner_attack_dmg_draining_do(void);
  const std::string &on_owner_attack_dmg_energy_do(void);
  const std::string &on_owner_attack_dmg_fire_do(void);
  const std::string &on_owner_attack_dmg_drown_do(void);
  const std::string &on_owner_attack_dmg_bite_do(void);
  const std::string &on_owner_attack_dmg_claw_do(void);
  const std::string &on_owner_attack_dmg_lightning_do(void);
  const std::string &on_owner_attack_dmg_melee_do(void);
  const std::string &on_owner_attack_dmg_nat_att_do(void);
  const std::string &on_owner_attack_dmg_necrosis_do(void);
  const std::string &on_owner_attack_dmg_poison_do(void);
  const std::string &on_owner_attack_dmg_stat_att_do(void);
  const std::string &on_owner_attack_dmg_stat_con_do(void);
  const std::string &on_owner_attack_dmg_stat_str_do(void);
  const std::string &on_owner_attack_dmg_water_do(void);
  const std::string &on_owner_receive_dmg_acid_do(void);
  const std::string &on_owner_receive_dmg_cold_do(void);
  const std::string &on_owner_receive_dmg_crush_do(void);
  const std::string &on_owner_receive_dmg_digest_do(void);
  const std::string &on_owner_receive_dmg_draining_do(void);
  const std::string &on_owner_receive_dmg_energy_do(void);
  const std::string &on_owner_receive_dmg_fire_do(void);
  const std::string &on_owner_receive_dmg_drown_do(void);
  const std::string &on_owner_receive_dmg_bite_do(void);
  const std::string &on_owner_receive_dmg_claw_do(void);
  const std::string &on_owner_receive_dmg_lightning_do(void);
  const std::string &on_owner_receive_dmg_melee_do(void);
  const std::string &on_owner_receive_dmg_nat_att_do(void);
  const std::string &on_owner_receive_dmg_necrosis_do(void);
  const std::string &on_owner_receive_dmg_poison_do(void);
  const std::string &on_owner_receive_dmg_stat_att_do(void);
  const std::string &on_owner_receive_dmg_stat_con_do(void);
  const std::string &on_owner_receive_dmg_stat_str_do(void);
  const std::string &on_owner_receive_dmg_water_do(void);
  const std::string &on_owner_remove_do(void);
  const std::string &on_polymorphed_do(void);
  const std::string &on_receiving_dmg_acid_do(void);
  const std::string &on_receiving_dmg_cold_do(void);
  const std::string &on_receiving_dmg_crush_do(void);
  const std::string &on_receiving_dmg_digest_do(void);
  const std::string &on_receiving_dmg_draining_do(void);
  const std::string &on_receiving_dmg_energy_do(void);
  const std::string &on_receiving_dmg_fire_do(void);
  const std::string &on_receiving_dmg_drown_do(void);
  const std::string &on_receiving_dmg_bite_do(void);
  const std::string &on_receiving_dmg_claw_do(void);
  const std::string &on_receiving_dmg_lightning_do(void);
  const std::string &on_receiving_dmg_melee_do(void);
  const std::string &on_receiving_dmg_nat_att_do(void);
  const std::string &on_receiving_dmg_necrosis_do(void);
  const std::string &on_receiving_dmg_poison_do(void);
  const std::string &on_receiving_dmg_stat_att_do(void);
  const std::string &on_receiving_dmg_stat_con_do(void);
  const std::string &on_receiving_dmg_stat_str_do(void);
  const std::string &on_receiving_dmg_water_do(void);
  const std::string &on_resting_do(void);
  const std::string &on_stuck_do(void);
  const std::string &on_swing_do(void);
  const std::string &on_teleport_do(void);
  const std::string &on_thrown_do(void);
  const std::string &on_dropped_do(void);
  const std::string &on_tick_do(void);
  const std::string &on_unequip_do(void);
  const std::string &on_use_do(void);
  const std::string &on_waiting_do(void);
  const std::string &on_you_are_declared_a_follower_do(void);
  const std::string &on_you_are_declared_leader_do(void);
  const std::string &on_you_are_hit_and_now_dead_do(void);
  const std::string &on_you_are_hit_but_dodge_it_do(void);
  const std::string &on_you_are_hit_but_still_alive_do(void);
  const std::string &on_you_are_on_fire_do(void);
  const std::string &on_you_nat_att_do(void);
  const std::string &poison_reason_get(void);
  const std::string &resurrect_dice_str(void);
  const std::string &spawn_group_size_dice_str(void);
  const std::string &spawn_on_shoved(void);
  const std::string &str1(void);
  const std::string &str2(void);
  const std::string &str4(void);
  const std::string &target_name_laser(void);
  const std::string &target_name_projectile(void);
  const std::string &target_name_radial(void);
  const std::string &text_debuff(void);
  const std::string &text_enchant(void);
  const std::string &text_hits(void);
  const std::string &text_long_name(void);
  const std::string &text_short_description(void);
  const std::string &text_short_name(void);
  const std::string &text_skill(void);
  const std::string &text_title(void);
  const std::string &text_unused1(void);
  const std::string &text_unused2(void);
  const std::string &text_unused3(void);
  const std::string &text_unused(void);
  const std::string &title(void);

  float bounce_fade_curr(void);
  float bounce_height_curr(void);
  float bounce_curr(void);
  float distance_avoid_get(void);
  float distance_from_leader(point p);
  float distance_from_leader(void);
  float distance_from_mob(point p);
  float distance_from_mob(void);
  float distance_leader_max_float(point p);
  float distance_leader_max_float(void);
  float distance_mob_max_float(point p);
  float distance_mob_max_float(void);
  float distance_recruitment_max_float(point p);
  float distance_recruitment_max_float(void);
  float distance_throw_get(void);
  float distance_vision_get(void);
  float fadeup_fade_curr(void);
  float fadeup_height_curr(void);
  float fadeup_curr(void);
  float fall_height_curr(void);
  float fall_curr(void);
  float health_pct(void);
  float lunge_curr(void);
  float wobble_curr(void);
  float jump_distance_max_get(void);
  float jump_distance_current(void);
  float teleport_distance_max_get(void);
  float teleport_distance_with_modifiers_get(void);
  float update_wobble(void);

  // begin sort marker2 {
  int aggression_pct(void);
  int ai_detect_secret_doors(void);
  int ai_dmap_can_see_init(int minx, int miny, int maxx, int maxy, int type, bool check);
  int ai_hit_actual(Thingp hitter, Thingp real_hitter, AttackOptions *, int damage);
  int ai_obstacle(void);
  int ai_resent_count(void);
  int ai_shove_chance_d1000(void);
  int ai_wanderer(void);
  int appearing_chance_d1000(void);
  int attack_eater(void);
  int attack_engulf_chance_d1000(void);
  int attack_humanoid(void);
  int attack_living(void);
  int attack_lunge(void);
  int attack_meat(void);
  int attack_no_msg(void);
  int attacks_per_round(void);
  int attack_undead(void);
  int attack(void);
  int bite_amount(void);
  int blast_max_radius(void);
  int blast_min_radius(void);
  int bounce_count(void);
  int capacity_height(void);
  int capacity_width(void);
  int carried_amulet_count(void);
  int carried_amulet_highest_value_for_target(Thingp *out, Thingp target);
  int carried_amulet_highest_value(Thingp *out);
  int carried_amulet_least_value(Thingp *out);
  int carried_armor_count(void);
  int carried_armor_highest_value_for_target(Thingp *out, Thingp target);
  int carried_armor_highest_value(Thingp *out);
  int carried_armor_least_value(Thingp *out);
  int carried_boots_count(void);
  int carried_boots_highest_value_for_target(Thingp *out, Thingp target);
  int carried_boots_highest_value(Thingp *out);
  int carried_boots_least_value(Thingp *out);
  int carried_cloak_count(void);
  int carried_cloak_highest_value_for_target(Thingp *out, Thingp target);
  int carried_cloak_highest_value(Thingp *out);
  int carried_cloak_least_value(Thingp *out);
  int carried_food_count(void);
  int carried_food_highest_value(Thingp *out);
  int carried_food_least_value(Thingp *out);
  int carried_gauntlet_count(void);
  int carried_gauntlet_highest_value_for_target(Thingp *out, Thingp target);
  int carried_gauntlet_highest_value(Thingp *out);
  int carried_gauntlet_least_value(Thingp *out);
  int carried_helmet_count(void);
  int carried_helmet_highest_value_for_target(Thingp *out, Thingp target);
  int carried_helmet_highest_value(Thingp *out);
  int carried_helmet_least_value(Thingp *out);
  int carried_ring_count(void);
  int carried_ring_highest_value(Thingp *out);
  int carried_ring_least_value(Thingp *out);
  int carried_shield_count(void);
  int carried_shield_highest_value_for_target(Thingp *out, Thingp target);
  int carried_shield_highest_value(Thingp *out);
  int carried_shield_least_value(Thingp *out);
  int carried_wand_count(void);
  int carried_wand_highest_value_for_target(Thingp *out, Thingp target);
  int carried_wand_highest_value(Thingp *out);
  int carried_wand_least_value(Thingp *out);
  int carried_weapon_count(void);
  int carried_weapon_highest_value(Thingp *out);
  int carried_weapon_least_value(Thingp *out);
  int charge_count_decr(int);
  int charge_count_decr(void);
  int charge_count_incr(int);
  int charge_count_incr(void);
  int charge_count_set(int);
  int charge_count(void);
  int collateral_damage_pct(void);
  int collision_check(void);
  int collision_hit_180(void);
  int collision_hit_360(void);
  int collision_hit_adj(void);
  int collision_hit_priority(void);
  int collision_hit_two_tiles_ahead(void);
  int crit_chance_d10000(void);
  int damage_acid_chance_d1000(int);
  int damage_acid(void);
  int damage_bite_chance_d1000(int);
  int damage_bite(void);
  int damage_claw_chance_d1000(int);
  int damage_claw(void);
  int damage_cold_chance_d1000(int);
  int damage_cold(void);
  int damage_crush_chance_d1000(int);
  int damage_crush(void);
  int damage_current_decr(int);
  int damage_current_decr(void);
  int damage_current_incr(int);
  int damage_current_incr(void);
  int damage_current_set(int);
  int damage_current(void);
  int damaged_chance_d10000(void);
  int damaged_count_decr(int);
  int damaged_count_decr(void);
  int damaged_count_incr(int);
  int damaged_count_incr(void);
  int damaged_count_set(int);
  int damaged_count(void);
  int damage_digest_chance_d1000(int);
  int damage_digest(void);
  int damage_draining_chance_d1000(int);
  int damage_draining(void);
  int damage_drown_chance_d1000(int);
  int damage_drown(void);
  int damage_energy_chance_d1000(int);
  int damage_energy(void);
  int damage_fire_chance_d1000(int);
  int damage_fire(void);
  int damage_lightning_chance_d1000(int);
  int damage_lightning(void);
  int damage_max(void);
  int damage_melee_chance_d1000(int);
  int damage_melee(void);
  int damage_min(void);
  int damage_nat_att_chance_d1000(int);
  int damage_nat_att(void);
  int damage_necrosis_chance_d1000(int);
  int damage_necrosis(void);
  int damage_poison_chance_d1000(int);
  int damage_poison(void);
  int damage_received_doubled_from_acid(void);
  int damage_received_doubled_from_cold(void);
  int damage_received_doubled_from_fire(void);
  int damage_received_doubled_from_necrosis(void);
  int damage_received_doubled_from_poison(void);
  int damage_received_doubled_from_water(void);
  int damage_water_chance_d1000(int);
  int damage_water(void);
  int danger_current_level(Thingp);
  int danger_current_level(void);
  int danger_initial_level(Thingp);
  int danger_initial_level(void);
  int defence(void);
  int distance_leader_max(void);
  int distance_minion_vision_shared(void);
  int distance_recruitment_max(void);
  int distance_throw_decr(int);
  int distance_throw_decr(void);
  int distance_throw_incr(int);
  int distance_throw_incr(void);
  int distance_throw_set(int);
  int distance_to_player_on_different_level(void);
  int distance_to_player(void);
  int enchant_decr(int);
  int enchant_decr(void);
  int enchant_get(void);
  int enchant_incr(int);
  int enchant_incr(void);
  int enchant_max_current_decr(int);
  int enchant_max_current_decr(void);
  int enchant_max_current_get(void);
  int enchant_max_current_incr(int);
  int enchant_max_current_incr(void);
  int enchant_max_current_set(int);
  int enchant_max(void);
  int enchant_set(int);
  int enchantstone_count(void);
  int environ_avoids_acid(void);
  int environ_avoids_cold(void);
  int environ_avoids_fire(void);
  int environ_avoids_necrosis(void);
  int environ_avoids_poison(void);
  int environ_avoids_water(void);
  int follower_count_decr(int);
  int follower_count_decr(void);
  int follower_count_incr(int);
  int follower_count_incr(void);
  int follower_count_set(int);
  int follower_count(void);
  int gfx_ascii_bg_color_spread_alpha(void);
  int gfx_ascii_bg_color_spread_blue(void);
  int gfx_ascii_bg_color_spread_green(void);
  int gfx_ascii_bg_color_spread_hue(void);
  int gfx_ascii_bg_color_spread_red(void);
  int gfx_ascii_color_is_animated(void);
  int gfx_ascii_fade_with_dist(void);
  int gfx_ascii_fg_color_spread_alpha(void);
  int gfx_ascii_fg_color_spread_blue(void);
  int gfx_ascii_fg_color_spread_green(void);
  int gfx_ascii_fg_color_spread_hue(void);
  int gfx_ascii_fg_color_spread_red(void);
  int gfx_ascii_shown_as_gray_in_shadow(void);
  int gfx_ascii_shown_in_bg(void);
  int gfx_ascii_shown(void);
  int gfx_glows(void);
  int gfx_on_fire_anim(void);
  int gfx_oversized_and_on_floor(void);
  int gfx_pixelart_animated_can_hflip(void);
  int gfx_pixelart_animated_can_vflip(void);
  int gfx_pixelart_animated_no_dir(void);
  int gfx_pixelart_anim_synced_with_owner(void);
  int gfx_pixelart_bounce_always(void);
  int gfx_pixelart_bounce_on_move(void);
  int gfx_pixelart_equip_carry_anim(void);
  int gfx_pixelart_flickers(void);
  int gfx_pixelart_health_bar_autohide(void);
  int gfx_pixelart_health_bar_only_when_awake(void);
  int gfx_pixelart_health_bar_shown(void);
  int gfx_pixelart_reflection(void);
  int gfx_pixelart_shadow_long(void);
  int gfx_pixelart_shadow_short(void);
  int gfx_pixelart_shadow_solid(void);
  int gfx_pixelart_shadow_very_short(void);
  int gfx_pixelart_shadow(void);
  int gfx_pixelart_show_asleep_anim(void);
  int gfx_pixelart_shown_in_bg(void);
  int gfx_pixelart_show_outlined(void);
  int gfx_pixelart_submergable(void);
  int gfx_pixelart_wobbles_when_hit(void);
  int gfx_water(void);
  int goal_penalty_get(Thingp attacker);
  int gold_decr(int);
  int gold_decr(void);
  int gold_incr(int);
  int gold_incr(void);
  int gold_set(int);
  int gold_value(void);
  int gold(void);
  int health_boost(int v);
  int health_decr(int);
  int health_decr(void);
  int health_incr(int);
  int health_incr(void);
  int health_initial(void);
  int health_max_decr(int);
  int health_max_decr(void);
  int health_max_incr(int);
  int health_max_incr(void);
  int health_max_set(int);
  int health_max(void);
  int health_set(int);
  int health(void);
  int hunger_boost(int v);
  int hunger_clock_tick_freq(void);
  int hunger_decr(int);
  int hunger_decr(void);
  int hunger_hunger_pct(void);
  int hunger_incr(int);
  int hunger_incr(void);
  int hunger_is_hunger_level_hungry_at_pct(void);
  int hunger_is_hunger_level_starving_at_pct(void);
  int hunger_is_insatiable(void);
  int hunger_set(int);
  int hunger(void);
  int idle_count_decr(int);
  int idle_count_decr(void);
  int idle_count_incr(int);
  int idle_count_incr(void);
  int idle_count_set(int);
  int idle_count(void);
  int initial_charge_count(void);
  int initial_light_dist_get(void);
  int is_able_to_attack_mobs(void);
  int is_able_to_attack_owner(void);
  int is_able_to_be_surprised(void);
  int is_able_to_break_down_doors(void);
  int is_able_to_break_out_of_ice(void);
  int is_able_to_break_out_of_webs(void);
  int is_able_to_burn(void);
  int is_able_to_change_levels(void);
  int is_able_to_collect_keys(void);
  int is_able_to_enchant_items(void);
  int is_able_to_fall(void);
  int is_able_to_fire_at(void);
  int is_able_to_follow(void);
  int is_able_to_freeze(void);
  int is_able_to_jump_attack_chance_d1000(void);
  int is_able_to_jump_attack(void);
  int is_able_to_jump_escape(void);
  int is_able_to_jump_on_low_hp_chance_d1000(void);
  int is_able_to_jump_onto_chance_d1000(void);
  int is_able_to_jump_onto(void);
  int is_able_to_jump_randomly_chance_d1000(void);
  int is_able_to_jump(void);
  int is_able_to_jump_without_tiring(void);
  int is_able_to_learn_skills(void);
  int is_able_to_melt(void);
  int is_able_to_move_diagonally(void);
  int is_able_to_open_doors(void);
  int is_able_to_rest(void);
  int is_able_to_see_in_the_dark(void);
  int is_able_to_see_through_doors(void);
  int is_able_to_shove(void);
  int is_able_to_sleep(void);
  int is_able_to_swim(void);
  int is_able_to_teleport_attack_chance_d1000(void);
  int is_able_to_teleport_attack(void);
  int is_able_to_teleport_escape(void);
  int is_able_to_teleport_without_tiring(void);
  int is_able_to_tire(void);
  int is_able_to_use_amulet(void);
  int is_able_to_use_armor(void);
  int is_able_to_use_boots(void);
  int is_able_to_use_cloak(void);
  int is_able_to_use_gauntlet(void);
  int is_able_to_use_helmet(void);
  int is_able_to_use_rings(void);
  int is_able_to_use_shield(void);
  int is_able_to_use_wands_or_staffs(void);
  int is_able_to_use_weapons(void);
  int is_able_to_walk_through_walls(void);
  int is_acid(void);
  int is_air_breather(void);
  int is_alive_monst(void);
  int is_alive_on_end_of_anim(void);
  int is_always_hit(void);
  int is_always_submerged(void);
  int is_amulet(void);
  int is_aquatic(void);
  int is_armor(void);
  int is_ascend_dungeon(void);
  int is_ascend_sewer(void);
  int is_asleep_initially(void);
  int is_attackable_by_monst(void);
  int is_attackable_by_player(void);
  int is_attacked_with_damage_acid(Thingp hitter, Thingp real_hitter, int damage);
  int is_attacked_with_damage_bite(Thingp hitter, Thingp real_hitter, int damage);
  int is_attacked_with_damage_claw(Thingp hitter, Thingp real_hitter, int damage);
  int is_attacked_with_damage_cold(Thingp hitter, Thingp real_hitter, int damage);
  int is_attacked_with_damage_crush(Thingp hitter, Thingp real_hitter, int damage);
  int is_attacked_with_damage_digest(Thingp hitter, Thingp real_hitter, int damage);
  int is_attacked_with_damage_draining(Thingp hitter, Thingp real_hitter, int damage);
  int is_attacked_with_damage_drown(Thingp hitter, Thingp real_hitter, int damage);
  int is_attacked_with_damage_energy(Thingp hitter, Thingp real_hitter, int damage);
  int is_attacked_with_damage_fire(Thingp hitter, Thingp real_hitter, int damage);
  int is_attacked_with_damage_lightning(Thingp hitter, Thingp real_hitter, int damage);
  int is_attacked_with_damage_melee(Thingp hitter, Thingp real_hitter, int damage);
  int is_attacked_with_damage_nat_att(Thingp hitter, Thingp real_hitter, int damage);
  int is_attacked_with_damage_necrosis(Thingp hitter, Thingp real_hitter, int damage);
  int is_attacked_with_damage_poison(Thingp hitter, Thingp real_hitter, int damage);
  int is_attacked_with_damage_water(Thingp hitter, Thingp real_hitter, int damage);
  int is_auto_collect_item(void);
  int is_auto_equipped(void);
  int is_auto_throw(void);
  int is_auto_use(void);
  int is_bag_item_container(void);
  int is_bag_item_not_stackable(void);
  int is_bag_item(void);
  int is_bag(void);
  int is_barrel(void);
  int is_basalt(void);
  int is_biome_dungeon(void);
  int is_biome_sewer(void);
  int is_biome_swamp(void);
  int is_biome_unused(void);
  int is_bleeder(void);
  int is_block_of_ice(void);
  int is_blood(void);
  int is_bones(void);
  int is_boots(void);
  int is_brazier(void);
  int is_bridge(void);
  int is_brittle(void);
  int is_buff(void);
  int is_carnivorous_plant(void);
  int is_carrier_of_treasure_class_a(void);
  int is_carrier_of_treasure_class_b(void);
  int is_carrier_of_treasure_class_c(void);
  int is_carrier_of_weapon_class_a(void);
  int is_carrier_of_weapon_class_b(void);
  int is_carrier_of_weapon_class_c(void);
  int is_chasm(void);
  int is_cloak(void);
  int is_cold(void);
  int is_collectable(void);
  int is_collected_as_gold(void);
  int is_collected_as_keys(void);
  int is_combustible(void);
  int is_corpse_on_death(void);
  int is_corpse(void);
  int is_corpse_with_bones(void);
  int is_corridor(void);
  int is_cowardly(void);
  int is_critical_to_level(void);
  int is_crushable(void);
  int is_crystal(void);
  int is_cursor_can_hover_over(void);
  int is_cursor_can_hover_over_x2_click(void);
  int is_cursor_path_blocker(void);
  int is_cursor_path_hazard(void);
  int is_cursor_path(void);
  int is_cursor(void);
  int is_dagger(void);
  int is_dangerous(Thingp);
  int is_dead_check(void);
  int is_dead_on_end_of_anim(void);
  int is_dead_on_falling(void);
  int is_dead_on_shove(void);
  int is_dead_or_dying(void);
  int is_debuff(void);
  int is_debug_path(void);
  int is_debug_type(void);
  int is_deep_water_swimmer(void);
  int is_deep_water(void);
  int is_descend_dungeon(void);
  int is_descend_sewer(void);
  int is_described_when_hovering_over(void);
  int is_destroyed_on_hit_or_miss(void);
  int is_destroyed_on_hitting(void);
  int is_dirt(void);
  int is_door(void);
  int is_droppable(void);
  int is_dry_grass_trampled(void);
  int is_dry_grass(void);
  int is_eater_of_amulets(void);
  int is_eater_of_armor(void);
  int is_eater_of_boots(void);
  int is_eater_of_cloaks(void);
  int is_eater_of_food(void);
  int is_eater_of_gauntlets(void);
  int is_eater_of_green_blood(void);
  int is_eater_of_helmets(void);
  int is_eater_of_jelly(void);
  int is_eater_of_magical_items(void);
  int is_eater_of_meat(void);
  int is_eater_of_potions(void);
  int is_eater_of_red_blood(void);
  int is_eater_of_rings(void);
  int is_eater_of_shields(void);
  int is_eater_of_staffs(void);
  int is_eater_of_treasure(void);
  int is_eater_of_wands(void);
  int is_eater_of_weapons(void);
  int is_enchantable(void);
  int is_enchantstone(void);
  int is_engulfer(void);
  int is_ethereal_mob(void);
  int is_ethereal(void);
  int is_exit_finder(void);
  int is_explorer(void);
  int is_explosion(void);
  int is_fearless(void);
  int is_fire(void);
  int is_flat(void);
  int is_floating(void);
  int is_floor_deco(void);
  int is_floor(void);
  int is_flying(void);
  int is_foilage(void);
  int is_food(void);
  int is_gas_blocker(void);
  int is_gauntlet(void);
  int is_gelatinous(void);
  int is_glass(void);
  int is_gold(void);
  int is_green_blooded(void);
  int is_green_blood(void);
  int is_green_splatter(void);
  int is_hard(void);
  int is_hazard(void);
  int is_health_booster(void);
  int is_heavy(void);
  int is_helmet(void);
  int is_hittable(void);
  int is_hit(Thingp hitter, AttackOptions *, int damage);
  int is_humanoid(void);
  int is_immune_to_acid(void);
  int is_immune_to_cold(void);
  int is_immune_to_draining(void);
  int is_immune_to_fire(void);
  int is_immune_to_necrosis(void);
  int is_immune_to_poison(void);
  int is_immune_to_spiderwebs(void);
  int is_immune_to_water(void);
  int is_intelligent(void);
  int is_interesting(void);
  int is_internal(void);
  int is_item_carrier(void);
  int is_item_collector(void);
  int is_item_organic(void);
  int is_item_targetted(void);
  int is_item(void);
  int is_jelly(void);
  int is_jump_blocker(void);
  int is_key_special(void);
  int is_key(void);
  int is_laser(void);
  int is_lava(void);
  int is_lifeless(void);
  int is_light_blocker_for_monst(void);
  int is_light_blocker(void);
  int is_living(void);
  int is_loggable(void);
  int is_magical(void);
  int is_map_beast(void);
  int is_map_treasure(void);
  int is_meat(void);
  int is_metal(void);
  int is_minion(void);
  int is_mob_challenge_class_a(void);
  int is_mob_challenge_class_b(void);
  int is_mob(void);
  int is_monst_class_a(void);
  int is_monst_class_b(void);
  int is_monst_class_c(void);
  int is_monst_class_d(void);
  int is_monst_class_e(void);
  int is_monst_pack(void);
  int is_monst(void);
  int is_moveable(void);
  int is_msg_allowed_is_seen(void);
  int is_msg_allowed_is_surprised(void);
  int is_msg_allowed_is_wounded(void);
  int is_msg(void);
  int is_necrotic_danger_level(void);
  int is_no_tile(void);
  int is_obs_destructable(void);
  int is_obs_for_jump_landing(void);
  int is_obs_for_shoving(void);
  int is_obstacle_when_dead(void);
  int is_obs_wall_or_door(void);
  int is_openable(void);
  int is_organic(void);
  int is_pillar(void);
  int is_plant(void);
  int is_player(void);
  int is_poisonous_danger_level(void);
  int is_potion(void);
  int is_projectile(void);
  int is_red_blooded(void);
  int is_red_blood(void);
  int is_red_splatter(void);
  int is_removeable_if_out_of_slots(void);
  int is_resurrectable(void);
  int is_resurrected_or_resurrecting(void);
  int is_ring(void);
  int is_ripple(void);
  int is_rock(void);
  int is_rusty(void);
  int is_secret_door(void);
  int is_sewer_wall(void);
  int is_shallow_water_swimmer(void);
  int is_shallow_water(void);
  int is_shield(void);
  int is_shovable_and_sticky(void);
  int is_shovable(void);
  int is_skillstone(void);
  int is_skill(void);
  int is_slippery(void);
  int is_smoke(void);
  int is_snake(void);
  int is_soft(void);
  int is_spawner(void);
  int is_spider(void);
  int is_spiderweb(void);
  int is_staff(void);
  int is_steal_item_chance_d1000(void);
  int is_steam(void);
  int is_sticky(void);
  int is_stone(void);
  int is_swimmer(void);
  int is_sword(void);
  int is_target_radial(void);
  int is_target_select(void);
  int is_temperature_change_sensitive(void);
  int is_temperature_sensitive(void);
  int is_thief(void);
  int is_throwable(void);
  int is_throw_blocker(void);
  int is_tickable(void);
  int is_tireless(void);
  int is_tmp_thing(void);
  int is_torch(void);
  int is_treasure_chest(void);
  int is_treasure_class_a(void);
  int is_treasure_class_b(void);
  int is_treasure_class_c(void);
  int is_treasure_type(void);
  int is_treasure(void);
  int is_undead(void);
  int is_usable(void);
  int is_used_when_thrown(void);
  int is_very_combustible(void);
  int is_very_hard(void);
  int is_very_heavy(void);
  int is_wall_dungeon(void);
  int is_wall(void);
  int is_wand_or_staff(void);
  int is_wand(void);
  int is_water(void);
  int is_weapon_class_a(void);
  int is_weapon_class_b(void);
  int is_weapon_class_c(void);
  int is_weapon(void);
  int is_wet_grass(void);
  int is_wooden(void);
  int item_count_excluding_charges(Tpp item);
  int item_count_including_charges(Tpp item);
  int item_enchant_count(const uint32_t slot);
  int item_height(void);
  int item_slot_charge_count(const uint32_t slot);
  int item_width(void);
  int jump_distance_mod_decr(int);
  int jump_distance_mod_decr(void);
  int jump_distance_mod_incr(int);
  int jump_distance_mod_incr(void);
  int jump_distance_mod_set(int);
  int jump_distance_mod(void);
  int jump_distance_total(void);
  int jump_distance(void);
  int keys_decr(int);
  int keys_decr(void);
  int keys_incr(int);
  int keys_incr(void);
  int keys_set(int);
  int keys(void);
  int level_get(void);
  int lifespan_decr(int);
  int lifespan_decr(void);
  int lifespan_get(void);
  int lifespan_incr(int);
  int lifespan_incr(void);
  int lifespan_initial(void);
  int lifespan_set(int);
  int light_distance_update(void);
  int light_dist_decr(int);
  int light_dist_decr(void);
  int light_dist_get(void);
  int light_dist_incr(int);
  int light_dist_incr(void);
  int light_dist_initial(void);
  int light_dist_set(int);
  int light_dist(void);
  int map_beast_carried_count(void);
  int map_beast_count(void);
  int map_treasure_carried_count(void);
  int map_treasure_count(void);
  int melting_chance_d1000(void);
  int minion_count_decr(int);
  int minion_count_decr(void);
  int minion_count_incr(int);
  int minion_count_incr(void);
  int minion_count_set(int);
  int minion_count(void);
  int minion_limit(void);
  int move_count_decr(int);
  int move_count_decr(void);
  int move_count_incr(int);
  int move_count_incr(void);
  int move_count_set(int);
  int move_count(void);
  int move_speed_curr(void);
  int move_speed_mod_decr(int);
  int move_speed_mod_decr(void);
  int move_speed_mod_incr(int);
  int move_speed_mod_incr(void);
  int move_speed_mod_set(int);
  int move_speed_mod(void);
  int move_speed_total(void);
  int move_speed(void);
  int necrotized_amount_decr(int);
  int necrotized_amount_decr(void);
  int necrotized_amount_incr(int);
  int necrotized_amount_incr(void);
  int necrotized_amount_set(int);
  int necrotized_amount(void);
  int noise_additional_on_jump_end(void);
  int noise_additional_on_teleporting(void);
  int noise_blocker(void);
  int noise_decibels_hearing(void);
  int noise_decr(int);
  int noise_decr(void);
  int noise_incr(int);
  int noise_incr(void);
  int noise_on_born(void);
  int noise_on_dropping(void);
  int noise_on_jumping(void);
  int noise_on_moving(void);
  int noise_on_open(void);
  int noise_on_teleporting(void);
  int noise_on_you_are_hit_and_now_dead(void);
  int noise_on_you_are_hit_but_still_alive(void);
  int noise_set(int);
  int noise_total(void);
  int noise(void);
  int normal_placement_rules(void);
  int nutrition_decr(int v);
  int nutrition_get(void);
  int nutrition_init(void);
  int on_attacking_dmg_acid(Thingp victim, int damage);
  int on_attacking_dmg_bite(Thingp victim, int damage);
  int on_attacking_dmg_claw(Thingp victim, int damage);
  int on_attacking_dmg_cold(Thingp victim, int damage);
  int on_attacking_dmg_crush(Thingp victim, int damage);
  int on_attacking_dmg_digest(Thingp victim, int damage);
  int on_attacking_dmg_draining(Thingp victim, int damage);
  int on_attacking_dmg_drown(Thingp victim, int damage);
  int on_attacking_dmg_energy(Thingp victim, int damage);
  int on_attacking_dmg_fire(Thingp victim, int damage);
  int on_attacking_dmg_lightning(Thingp victim, int damage);
  int on_attacking_dmg_melee(Thingp victim, int damage);
  int on_attacking_dmg_nat_att(Thingp victim, int damage);
  int on_attacking_dmg_necrosis(Thingp victim, int damage);
  int on_attacking_dmg_poison(Thingp victim, int damage);
  int on_attacking_dmg_stat_att(Thingp victim, int damage);
  int on_attacking_dmg_stat_con(Thingp victim, int damage);
  int on_attacking_dmg_stat_str(Thingp victim, int damage);
  int on_attacking_dmg_water(Thingp victim, int damage);
  int on_death_drop_all_items(void);
  int on_death_is_open(void);
  int on_idle_tick_freq(void);
  int on_owner_attack_dmg_acid(Thingp owner, Thingp victim, int damage);
  int on_owner_attack_dmg_bite(Thingp owner, Thingp victim, int damage);
  int on_owner_attack_dmg_claw(Thingp owner, Thingp victim, int damage);
  int on_owner_attack_dmg_cold(Thingp owner, Thingp victim, int damage);
  int on_owner_attack_dmg_crush(Thingp owner, Thingp victim, int damage);
  int on_owner_attack_dmg_digest(Thingp owner, Thingp victim, int damage);
  int on_owner_attack_dmg_draining(Thingp owner, Thingp victim, int damage);
  int on_owner_attack_dmg_drown(Thingp owner, Thingp victim, int damage);
  int on_owner_attack_dmg_energy(Thingp owner, Thingp victim, int damage);
  int on_owner_attack_dmg_fire(Thingp owner, Thingp victim, int damage);
  int on_owner_attack_dmg_lightning(Thingp owner, Thingp victim, int damage);
  int on_owner_attack_dmg_melee(Thingp owner, Thingp victim, int damage);
  int on_owner_attack_dmg_nat_att(Thingp owner, Thingp victim, int damage);
  int on_owner_attack_dmg_necrosis(Thingp owner, Thingp victim, int damage);
  int on_owner_attack_dmg_poison(Thingp owner, Thingp victim, int damage);
  int on_owner_attack_dmg_stat_att(Thingp owner, Thingp victim, int damage);
  int on_owner_attack_dmg_stat_con(Thingp owner, Thingp victim, int damage);
  int on_owner_attack_dmg_stat_str(Thingp owner, Thingp victim, int damage);
  int on_owner_attack_dmg_water(Thingp owner, Thingp victim, int damage);
  int on_owner_receive_dmg_acid(Thingp owner, Thingp hitter, Thingp real_hitter, int damage);
  int on_owner_receive_dmg_bite(Thingp owner, Thingp hitter, Thingp real_hitter, int damage);
  int on_owner_receive_dmg_claw(Thingp owner, Thingp hitter, Thingp real_hitter, int damage);
  int on_owner_receive_dmg_cold(Thingp owner, Thingp hitter, Thingp real_hitter, int damage);
  int on_owner_receive_dmg_crush(Thingp owner, Thingp hitter, Thingp real_hitter, int damage);
  int on_owner_receive_dmg_digest(Thingp owner, Thingp hitter, Thingp real_hitter, int damage);
  int on_owner_receive_dmg_draining(Thingp owner, Thingp hitter, Thingp real_hitter, int damage);
  int on_owner_receive_dmg_drown(Thingp owner, Thingp hitter, Thingp real_hitter, int damage);
  int on_owner_receive_dmg_energy(Thingp owner, Thingp hitter, Thingp real_hitter, int damage);
  int on_owner_receive_dmg_fire(Thingp owner, Thingp hitter, Thingp real_hitter, int damage);
  int on_owner_receive_dmg_lightning(Thingp owner, Thingp hitter, Thingp real_hitter, int damage);
  int on_owner_receive_dmg_melee(Thingp owner, Thingp hitter, Thingp real_hitter, int damage);
  int on_owner_receive_dmg_nat_att(Thingp owner, Thingp hitter, Thingp real_hitter, int damage);
  int on_owner_receive_dmg_necrosis(Thingp owner, Thingp hitter, Thingp real_hitter, int damage);
  int on_owner_receive_dmg_poison(Thingp owner, Thingp hitter, Thingp real_hitter, int damage);
  int on_owner_receive_dmg_stat_att(Thingp owner, Thingp hitter, Thingp real_hitter, int damage);
  int on_owner_receive_dmg_stat_con(Thingp owner, Thingp hitter, Thingp real_hitter, int damage);
  int on_owner_receive_dmg_stat_str(Thingp owner, Thingp hitter, Thingp real_hitter, int damage);
  int on_owner_receive_dmg_water(Thingp owner, Thingp hitter, Thingp real_hitter, int damage);
  int on_receiving_dmg_acid(Thingp hitter, Thingp real_hitter, int damage);
  int on_receiving_dmg_bite(Thingp hitter, Thingp real_hitter, int damage);
  int on_receiving_dmg_claw(Thingp hitter, Thingp real_hitter, int damage);
  int on_receiving_dmg_cold(Thingp hitter, Thingp real_hitter, int damage);
  int on_receiving_dmg_crush(Thingp hitter, Thingp real_hitter, int damage);
  int on_receiving_dmg_digest(Thingp hitter, Thingp real_hitter, int damage);
  int on_receiving_dmg_draining(Thingp hitter, Thingp real_hitter, int damage);
  int on_receiving_dmg_drown(Thingp hitter, Thingp real_hitter, int damage);
  int on_receiving_dmg_energy(Thingp hitter, Thingp real_hitter, int damage);
  int on_receiving_dmg_fire(Thingp hitter, Thingp real_hitter, int damage);
  int on_receiving_dmg_lightning(Thingp hitter, Thingp real_hitter, int damage);
  int on_receiving_dmg_melee(Thingp hitter, Thingp real_hitter, int damage);
  int on_receiving_dmg_nat_att(Thingp hitter, Thingp real_hitter, int damage);
  int on_receiving_dmg_necrosis(Thingp hitter, Thingp real_hitter, int damage);
  int on_receiving_dmg_poison(Thingp hitter, Thingp real_hitter, int damage);
  int on_receiving_dmg_stat_att(Thingp hitter, Thingp real_hitter, int damage);
  int on_receiving_dmg_stat_con(Thingp hitter, Thingp real_hitter, int damage);
  int on_receiving_dmg_stat_str(Thingp hitter, Thingp real_hitter, int damage);
  int on_receiving_dmg_water(Thingp hitter, Thingp real_hitter, int damage);
  int owned_count_decr(int);
  int owned_count_decr(void);
  int owned_count_incr(int);
  int owned_count_incr(void);
  int owned_count_set(int);
  int owned_count(void);
  int poisoned_amount_decr(int);
  int poisoned_amount_decr(void);
  int poisoned_amount_incr(int);
  int poisoned_amount_incr(void);
  int poisoned_amount_set(int);
  int poisoned_amount(void);
  int prev_light_dist_decr(int);
  int prev_light_dist_decr(void);
  int prev_light_dist_get(void);
  int prev_light_dist_incr(int);
  int prev_light_dist_incr(void);
  int prev_light_dist_set(int);
  int range_max(void);
  int rarity(void);
  int resurrect_when(void);
  int score(void);
  int shove_strength_mod_decr(int);
  int shove_strength_mod_decr(void);
  int shove_strength_mod_incr(int);
  int shove_strength_mod_incr(void);
  int shove_strength_mod_set(int);
  int shove_strength_mod(void);
  int shove_strength_total(void);
  int shove_strength(void);
  int skill_enchant_count(const uint32_t slot);
  int skillstone_count(void);
  int sleep_count_decr(int);
  int sleep_count_decr(void);
  int sleep_count_incr(int);
  int sleep_count_incr(void);
  int sleep_count_set(int);
  int sleep_count(void);
  int spawned_count_decr(int);
  int spawned_count_decr(void);
  int spawned_count_incr(int);
  int spawned_count_incr(void);
  int spawned_count_set(int);
  int spawned_count(void);
  int spawn_group_radius(void);
  int spawn_group_size(void);
  int spawn_randomly_in_radius_range(const std::string &what, int amount, int radius_min, int radius_max);
  int stamina_decr(int);
  int stamina_decr(void);
  int stamina_drain_on_attacking(void);
  int stamina_drain_on_using(void);
  int stamina_incr(int);
  int stamina_incr(void);
  int stamina_max_decr(int);
  int stamina_max_decr(void);
  int stamina_max_incr(int);
  int stamina_max_incr(void);
  int stamina_max_set(int);
  int stamina_max(void);
  int stamina_set(int);
  int stamina(void);
  int stat_att_decr(int);
  int stat_att_decr(void);
  int stat_att_incr(int);
  int stat_att_incr(void);
  int stat_att_mod_decr(int);
  int stat_att_mod_decr(void);
  int stat_att_mod_incr(int);
  int stat_att_mod_incr(void);
  int stat_att_mod_set(int);
  int stat_att_mod(void);
  int stat_att_penalties_total(void);
  int stat_att_penalty_when_idle_max(void);
  int stat_att_penalty_when_idle(void);
  int stat_att_penalty_when_in_deep_water(void);
  int stat_att_penalty_when_in_shallow_water(void);
  int stat_att_penalty_when_stuck_max(void);
  int stat_att_penalty_when_stuck(void);
  int stat_att_set(int);
  int stat_att_total(void);
  int stat_att(void);
  int stat_con_decr(int);
  int stat_con_decr(void);
  int stat_con_incr(int);
  int stat_con_incr(void);
  int stat_con_mod_decr(int);
  int stat_con_mod_decr(void);
  int stat_con_mod_incr(int);
  int stat_con_mod_incr(void);
  int stat_con_mod_set(int);
  int stat_con_mod(void);
  int stat_con_set(int);
  int stat_con_total(void);
  int stat_con(void);
  int stat_def_decr(int);
  int stat_def_decr(void);
  int stat_def_incr(int);
  int stat_def_incr(void);
  int stat_def_mod_decr(int);
  int stat_def_mod_decr(void);
  int stat_def_mod_incr(int);
  int stat_def_mod_incr(void);
  int stat_def_mod_set(int);
  int stat_def_mod(void);
  int stat_def_penalties_total(void);
  int stat_def_penalty_when_idle_max(void);
  int stat_def_penalty_when_idle(void);
  int stat_def_penalty_when_in_deep_water(void);
  int stat_def_penalty_when_in_shallow_water(void);
  int stat_def_penalty_when_stuck_max(void);
  int stat_def_penalty_when_stuck(void);
  int stat_def_set(int);
  int stat_def_total(void);
  int stat_def(void);
  int stat_dex_decr(int);
  int stat_dex_decr(void);
  int stat_dex_incr(int);
  int stat_dex_incr(void);
  int stat_dex_mod_decr(int);
  int stat_dex_mod_decr(void);
  int stat_dex_mod_incr(int);
  int stat_dex_mod_incr(void);
  int stat_dex_mod_set(int);
  int stat_dex_mod(void);
  int stat_dex_set(int);
  int stat_dex_total(void);
  int stat_dex(void);
  int stat_luck_decr(int);
  int stat_luck_decr(void);
  int stat_luck_incr(int);
  int stat_luck_incr(void);
  int stat_luck_mod_decr(int);
  int stat_luck_mod_decr(void);
  int stat_luck_mod_incr(int);
  int stat_luck_mod_incr(void);
  int stat_luck_mod_set(int);
  int stat_luck_mod(void);
  int stat_luck_set(int);
  int stat_luck_total(void);
  int stat_luck(void);
  int stats02_decr(int);
  int stats02_decr(void);
  int stats02_incr(int);
  int stats02_incr(void);
  int stats02_set(int);
  int stats02(void);
  int stats03_decr(int);
  int stats03_decr(void);
  int stats03_incr(int);
  int stats03_incr(void);
  int stats03_set(int);
  int stats03(void);
  int stats04_decr(int);
  int stats04_decr(void);
  int stats04_incr(int);
  int stats04_incr(void);
  int stats04_set(int);
  int stats04(void);
  int stats05_decr(int);
  int stats05_decr(void);
  int stats05_incr(int);
  int stats05_incr(void);
  int stats05_set(int);
  int stats05(void);
  int stats06_decr(int);
  int stats06_decr(void);
  int stats06_incr(int);
  int stats06_incr(void);
  int stats06_set(int);
  int stats06(void);
  int stats07_decr(int);
  int stats07_decr(void);
  int stats07_incr(int);
  int stats07_incr(void);
  int stats07_set(int);
  int stats07(void);
  int stats09_decr(int);
  int stats09_decr(void);
  int stats09_incr(int);
  int stats09_incr(void);
  int stats09_set(int);
  int stats09(void);
  int stat_str_decr(int);
  int stat_str_decr(void);
  int stat_str_incr(int);
  int stat_str_incr(void);
  int stat_str_mod_decr(int);
  int stat_str_mod_decr(void);
  int stat_str_mod_incr(int);
  int stat_str_mod_incr(void);
  int stat_str_mod_set(int);
  int stat_str_mod(void);
  int stat_str_set(int);
  int stat_str_total(void);
  int stat_str(void);
  int stuck_count_decr(int);
  int stuck_count_decr(void);
  int stuck_count_incr(int);
  int stuck_count_incr(void);
  int stuck_count_set(int);
  int stuck_count(void);
  int submerged_offset_get(void);
  int teleport_distance_get(void);
  int teleport_distance(void);
  int temperature_get(void);
  int temperature_set(int);
  int thing_size(void);
  int tick_prio(void);
  int torch_count(void);
  int total_damage_for_on_attacking_dmg_acid(Thingp victim, int damage);
  int total_damage_for_on_attacking_dmg_bite(Thingp victim, int damage);
  int total_damage_for_on_attacking_dmg_claw(Thingp victim, int damage);
  int total_damage_for_on_attacking_dmg_cold(Thingp victim, int damage);
  int total_damage_for_on_attacking_dmg_crush(Thingp victim, int damage);
  int total_damage_for_on_attacking_dmg_digest(Thingp victim, int damage);
  int total_damage_for_on_attacking_dmg_draining(Thingp victim, int damage);
  int total_damage_for_on_attacking_dmg_drown(Thingp victim, int damage);
  int total_damage_for_on_attacking_dmg_energy(Thingp victim, int damage);
  int total_damage_for_on_attacking_dmg_fire(Thingp victim, int damage);
  int total_damage_for_on_attacking_dmg_lightning(Thingp victim, int damage);
  int total_damage_for_on_attacking_dmg_melee(Thingp victim, int damage);
  int total_damage_for_on_attacking_dmg_nat_att(Thingp victim, int damage);
  int total_damage_for_on_attacking_dmg_necrosis(Thingp victim, int damage);
  int total_damage_for_on_attacking_dmg_poison(Thingp victim, int damage);
  int total_damage_for_on_attacking_dmg_stat_att(Thingp victim, int damage);
  int total_damage_for_on_attacking_dmg_stat_con(Thingp victim, int damage);
  int total_damage_for_on_attacking_dmg_stat_str(Thingp victim, int damage);
  int total_damage_for_on_attacking_dmg_water(Thingp victim, int damage);
  int total_damage_for_on_receiving_dmg_acid(Thingp hitter, Thingp real_hitter, int damage);
  int total_damage_for_on_receiving_dmg_bite(Thingp hitter, Thingp real_hitter, int damage);
  int total_damage_for_on_receiving_dmg_claw(Thingp hitter, Thingp real_hitter, int damage);
  int total_damage_for_on_receiving_dmg_cold(Thingp hitter, Thingp real_hitter, int damage);
  int total_damage_for_on_receiving_dmg_crush(Thingp hitter, Thingp real_hitter, int damage);
  int total_damage_for_on_receiving_dmg_digest(Thingp hitter, Thingp real_hitter, int damage);
  int total_damage_for_on_receiving_dmg_draining(Thingp hitter, Thingp real_hitter, int damage);
  int total_damage_for_on_receiving_dmg_drown(Thingp hitter, Thingp real_hitter, int damage);
  int total_damage_for_on_receiving_dmg_energy(Thingp hitter, Thingp real_hitter, int damage);
  int total_damage_for_on_receiving_dmg_fire(Thingp hitter, Thingp real_hitter, int damage);
  int total_damage_for_on_receiving_dmg_lightning(Thingp hitter, Thingp real_hitter, int damage);
  int total_damage_for_on_receiving_dmg_melee(Thingp hitter, Thingp real_hitter, int damage);
  int total_damage_for_on_receiving_dmg_nat_att(Thingp hitter, Thingp real_hitter, int damage);
  int total_damage_for_on_receiving_dmg_necrosis(Thingp hitter, Thingp real_hitter, int damage);
  int total_damage_for_on_receiving_dmg_poison(Thingp hitter, Thingp real_hitter, int damage);
  int total_damage_for_on_receiving_dmg_stat_att(Thingp hitter, Thingp real_hitter, int damage);
  int total_damage_for_on_receiving_dmg_stat_con(Thingp hitter, Thingp real_hitter, int damage);
  int total_damage_for_on_receiving_dmg_stat_str(Thingp hitter, Thingp real_hitter, int damage);
  int total_damage_for_on_receiving_dmg_water(Thingp hitter, Thingp real_hitter, int damage);
  int unused_chance1_d1000(void);
  int unused_chance2_d1000(void);
  int unused_chance3_d1000(void);
  int unused_chance4_d1000(void);
  int unused_chance5_d1000(void);
  int unused_chance6_d1000(void);
  int unused_flag103(void);
  int unused_flag10(void);
  int unused_flag11(void);
  int unused_flag123(void);
  int unused_flag12(void);
  int unused_flag13(void);
  int unused_flag14(void);
  int unused_flag15(void);
  int unused_flag16(void);
  int unused_flag17(void);
  int unused_flag18(void);
  int unused_flag19(void);
  int unused_flag1(void);
  int unused_flag20(void);
  int unused_flag21(void);
  int unused_flag22(void);
  int unused_flag23(void);
  int unused_flag24(void);
  int unused_flag25(void);
  int unused_flag26(void);
  int unused_flag27(void);
  int unused_flag28(void);
  int unused_flag29(void);
  int unused_flag2(void);
  int unused_flag30(void);
  int unused_flag31(void);
  int unused_flag32(void);
  int unused_flag33(void);
  int unused_flag34(void);
  int unused_flag35(void);
  int unused_flag36(void);
  int unused_flag37(void);
  int unused_flag38(void);
  int unused_flag39(void);
  int unused_flag3(void);
  int unused_flag40(void);
  int unused_flag48(void);
  int unused_flag4(void);
  int unused_flag56(void);
  int unused_flag5(void);
  int unused_flag6(void);
  int unused_flag7(void);
  int unused_flag87(void);
  int unused_flag8(void);
  int unused_flag9(void);
  int value(const Thingp it);
  int weapon_damaged_pct(void);
  int weapon_damage_modify(int damage);
  int weapon_damage(void);
  int worth_collecting(const Thingp it);
  int worth_collecting(const Thingp it, Thingp *would_need_to_drop);
  // end sort marker2 {

  point3d born_get(void);

  point dest_random_get(int dist = 0);
  point dir_to_direction(void);
  point in_the_way_for_throwing(const point s, const point e);
  point lunge_to_get(void);
  point vision_source_get(void);
  point where_i_dropped_an_item_last_get(void);

  point where_i_failed_to_collect_last_get(void);
  point where_i_dropped_an_item_last_set(point);
  point where_i_failed_to_collect_last_set(point);

  std::list< Thingp > anything_to_carry(void);
  std::list< Thingp > anything_to_carry_at(point);

  std::size_t light_count(void);

  std::string text_short_and_state_capitalised(void);
  std::string text_long_and_state_capitalised(void);
  std::string text_short_capitalised(void);
  std::string text_long_capitalised(void);
  std::string text_short_a_or_an(void);
  std::string text_short_the(void);
  std::string text_short_The(void);
  std::string text_a_or_an(void);
  std::string text_A_or_An(void);
  std::string text_the(bool include_owner = false);
  std::string text_the_no_dying(bool include_owner = false);
  std::string text_The_no_dying(void);
  std::string text_The(void);
  std::string to_dbg_saved_string(void);
  std::string to_dbg_string(void);
  std::string to_short_string(void);
  std::string to_string(void);

  std::vector< Lightp > &light_get(void);

  struct AgeMap_ *age_map_get(void);
  struct AgeMap_ *seen_map_get(void);
  struct AgeMap_ *interrupt_map_get(void);

  struct Dmap_ *dmap_can_see_get(void);

  struct FovMap_ *can_see_currently(void);
  struct FovMap_ *can_see_ever(void);

  // begin sort marker3 {
  ts_t ts_anim_delay_end_decr(ts_t);
  ts_t ts_anim_delay_end_decr(void);
  ts_t ts_anim_delay_end_incr(ts_t);
  ts_t ts_anim_delay_end_incr(void);
  ts_t ts_anim_delay_end_set(ts_t);
  ts_t ts_anim_delay_end(void);
  ts_t ts_bounce_begin_decr(ts_t);
  ts_t ts_bounce_begin_decr(void);
  ts_t ts_bounce_begin_incr(ts_t);
  ts_t ts_bounce_begin_incr(void);
  ts_t ts_bounce_begin_set(ts_t);
  ts_t ts_bounce_begin(void);
  ts_t ts_bounce_end_decr(ts_t);
  ts_t ts_bounce_end_decr(void);
  ts_t ts_bounce_end_incr(ts_t);
  ts_t ts_bounce_end_incr(void);
  ts_t ts_bounce_end_set(ts_t);
  ts_t ts_bounce_end(void);
  ts_t ts_fadeup_begin_decr(ts_t);
  ts_t ts_fadeup_begin_decr(void);
  ts_t ts_fadeup_begin_incr(ts_t);
  ts_t ts_fadeup_begin_incr(void);
  ts_t ts_fadeup_begin_set(ts_t);
  ts_t ts_fadeup_begin(void);
  ts_t ts_fadeup_end_decr(ts_t);
  ts_t ts_fadeup_end_decr(void);
  ts_t ts_fadeup_end_incr(ts_t);
  ts_t ts_fadeup_end_incr(void);
  ts_t ts_fadeup_end_set(ts_t);
  ts_t ts_fadeup_end(void);
  ts_t ts_fall_begin_decr(ts_t);
  ts_t ts_fall_begin_decr(void);
  ts_t ts_fall_begin_incr(ts_t);
  ts_t ts_fall_begin_incr(void);
  ts_t ts_fall_begin_set(ts_t);
  ts_t ts_fall_begin(void);
  ts_t ts_fall_end_decr(ts_t);
  ts_t ts_fall_end_decr(void);
  ts_t ts_fall_end_incr(ts_t);
  ts_t ts_fall_end_incr(void);
  ts_t ts_fall_end_set(ts_t);
  ts_t ts_fall_end(void);
  ts_t ts_flip_start_decr(ts_t);
  ts_t ts_flip_start_decr(void);
  ts_t ts_flip_start_get(void);
  ts_t ts_flip_start_incr(ts_t);
  ts_t ts_flip_start_incr(void);
  ts_t ts_flip_start_set(ts_t);
  ts_t ts_lunge_begin_decr(ts_t);
  ts_t ts_lunge_begin_decr(void);
  ts_t ts_lunge_begin_incr(ts_t);
  ts_t ts_lunge_begin_incr(void);
  ts_t ts_lunge_begin_set(ts_t);
  ts_t ts_lunge_begin(void);
  ts_t ts_lunge_end_decr(ts_t);
  ts_t ts_lunge_end_decr(void);
  ts_t ts_lunge_end_incr(ts_t);
  ts_t ts_lunge_end_incr(void);
  ts_t ts_lunge_end_set(ts_t);
  ts_t ts_lunge_end(void);
  // end sort marker3 {

  uint32_t tick_last_location_check_decr(uint32_t);
  uint32_t tick_last_location_check_decr(void);
  uint32_t tick_last_location_check_incr(uint32_t);
  uint32_t tick_last_location_check_incr(void);
  uint32_t tick_last_location_check_set(uint32_t);
  uint32_t tick_last_location_check(void);

  uint32_t tick_last_i_was_attacked_decr(uint32_t);
  uint32_t tick_last_i_was_attacked_decr(void);
  uint32_t tick_last_i_was_attacked_incr(uint32_t);
  uint32_t tick_last_i_was_attacked_incr(void);
  uint32_t tick_last_i_was_attacked_set(uint32_t);
  uint32_t tick_last_i_was_attacked(void);

  uint32_t tick_last_i_attacked_decr(uint32_t);
  uint32_t tick_last_i_attacked_decr(void);
  uint32_t tick_last_i_attacked_incr(uint32_t);
  uint32_t tick_last_i_attacked_incr(void);
  uint32_t tick_last_i_attacked_set(uint32_t);
  uint32_t tick_last_i_attacked(void);

  uint32_t tick_last_level_change_decr(uint32_t);
  uint32_t tick_last_level_change_decr(void);
  uint32_t tick_last_level_change_incr(uint32_t);
  uint32_t tick_last_level_change_incr(void);
  uint32_t tick_last_level_change_set(uint32_t);
  uint32_t tick_last_level_change(void);

  uint32_t tick_last_did_something_decr(uint32_t);
  uint32_t tick_last_did_something_decr(void);
  uint32_t tick_last_did_something_incr(uint32_t);
  uint32_t tick_last_did_something_incr(void);
  uint32_t tick_last_did_something_set(uint32_t);
  uint32_t tick_last_did_something(void);

  uint32_t tick_last_dropped_decr(uint32_t);
  uint32_t tick_last_dropped_decr(void);
  uint32_t tick_last_dropped_incr(uint32_t);
  uint32_t tick_last_dropped_incr(void);
  uint32_t tick_last_dropped_set(uint32_t);
  uint32_t tick_last_dropped(void);

  uint32_t tick_last_escape_decr(uint32_t);
  uint32_t tick_last_escape_decr(void);
  uint32_t tick_last_escape_incr(uint32_t);
  uint32_t tick_last_escape_incr(void);
  uint32_t tick_last_escape_set(uint32_t);
  uint32_t tick_last_escape(void);

  uint32_t tick_resurrect_when_decr(int);
  uint32_t tick_resurrect_when_decr(void);
  uint32_t tick_resurrect_when_incr(int);
  uint32_t tick_resurrect_when_incr(void);
  uint32_t tick_resurrect_when_set(int);
  uint32_t tick_resurrect_when(void);

  int movement_remaining_decr(int);
  int movement_remaining_decr(void);
  int movement_remaining_incr(int);
  int movement_remaining_incr(void);
  int movement_remaining_set(int);
  int movement_remaining(void);

  int physical_training_decr(int);
  int physical_training_decr(void);
  int physical_training_incr(int);
  int physical_training_incr(void);
  int physical_training_set(int);
  int physical_training(void);

  uint8_t blit_begin_reflection_submerged(void);
  uint8_t blit_begin_submerged(void);
  uint8_t terrain_cost_get(point p);
  uint8_t is_dir_bl(void);
  uint8_t is_dir_br(void);
  uint8_t is_dir_down(void);
  uint8_t is_dir_left(void);
  uint8_t is_dir_none(void);
  uint8_t is_dir_right(void);
  uint8_t is_dir_tl(void);
  uint8_t is_dir_tr(void);
  uint8_t is_dir_up(void);
  uint8_t is_visible(void);
  uint8_t z_prio(void);

  // begin sort marker4 {
  void achieve_goals_in_death(void);
  void achieve_goals_in_life(void);
  void acid_tick(void);
  void add_avoid(Thingp attacker);
  void add_enemy(Thingp attacker, bool is_recursing = false);
  void add_enemy(Tpp attacker);
  void add_friend(Thingp attacker);
  void add_friend(Tpp attacker);
  void add_goal_penalty(Thingp attacker);
  void ai_choose_can_see_goals(std::multiset< Goal > &goals, int minx, int miny, int maxx, int maxy);
  void ai_choose_search_goals(std::multiset< Goal > &goals, int search_type);
  void ai_get_next_hop(void);
  void ai_log(const std::string &msg);
  void ai_log(const std::string &msg, Thingp it);
  void animate_choose_tile(Tilemap *tmap, std::vector< Tilep > *tiles, bool *next_frame_please);
  void animate(void);
  void avoid_tick(void);
  void awake(void);
  void barrel_tick(void);
  void blit_ascii_adjust_color(color &c, bool fg, bool leftbar);
  void blit_ascii_adjust_color_hue(color &c, bool fg);
  void blit_ascii_at(point tl, bool lit = true, bool leftbar = false);
  void blit_ascii(point tl, point br, point p, bool leftbar = false);
  void blit_end_reflection_submerged(uint8_t submerged);
  void blit_end_submerged(uint8_t submerged);
  void blit_floor_chasm(point tl, point br, const ThingTiles *tiles);
  void blit_internal(int fbo, point &blit_tl, point &blit_br, const Tilep tile, color c, const bool reflection);
  void blit_non_player_owned_shadow(const Tpp &tp, const Tilep &tile, const point tl, const point br);
  void blit_pixelart(int fbo);
  void blit_player_owned_shadow(const Tpp &tp, const Tilep &tile, const point tl, const point br);
  void blit_shadow(const Tpp &tp, const Tilep &tile, const point tl, const point br);
  void blit_text(std::string const &, color c, point tl, point br);
  void blit_upside_down(int fbo);
  void blit_wall_cladding(point tl, point br, const ThingTiles *tiles);
  void blit_wall_shadow(point tl, point br, const ThingTiles *tiles);
  void block_of_ice_tick(void);
  void born_set(point3d);
  void botcon(const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);
  void botcon_(const char *fmt, va_list args); // compile error without
  void bounce_count_set(int);
  void bounce_fade_set(float);
  void bounce_height_set(float);
  void brazier_tick(void);
  void buff_activate(Thingp what);
  void buff_deactivate(Thingp what);
  void buff_remove_all(void);
  void buff_tick(void);
  void burnt_set(void);
  void can_see(point);
  void change_state(int new_state, const std::string &why);
  void chasm_tick(void);
  void check_all_carried_items_are_owned(void);
  void check_all_carried_maps(void);
  void clear_age_map(void);
  void clear_can_see_currently(void);
  void clear_can_see_ever(void);
  void clear_dmap_can_see(void);
  void clear_interrupt_map(void);
  void clear_move_path(const std::string &why);
  void clear_seen_map(void);
  void con(const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);
  void con_(const char *fmt, va_list args); // compile error without
  void corrode_tick(void);
  void cursor_hover_over_check(void);
  void dbg_(const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);
  void dead(const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);
  void dead_(const char *fmt, va_list args); // compile error without
  void dead(const std::string &);
  void dead_reason_set(const std::string &);
  void dead_scheduled(const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);
  void dead_scheduled(const std::string &);
  void dead(Thingp defeater, const char *fmt, ...) CHECK_FORMAT_STR(printf, 3, 4);
  void dead_(Thingp defeater, const char *fmt, va_list args);
  void dead(Thingp defeater, std::string &);
  void debuff_activate(Thingp what);
  void debuff_deactivate(Thingp what);
  void debuff_remove_all(void);
  void debuff_tick(void);
  void delete_laser(void);
  void delete_lights(void);
  void delete_particle(void);
  void delete_projectile(void);
  void destroyed(void);
  void destroy_minions(Thingp defeater);
  void destroy_spawned(Thingp defeater);
  void destroy(void);
  void die(const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);
  void die_(const char *fmt, va_list args); // compile error without
  void dir_set_bl(void);
  void dir_set_br(void);
  void dir_set_down(void);
  void dir_set_left(void);
  void dir_set_none(void);
  void dir_set_right(void);
  void dir_set_tl(void);
  void dir_set_tr(void);
  void dir_set_up(void);
  void dmap_modify_terrain_cost(point p, uint8_t *d);
  void drop_all(void);
  void dump_equip(void);
  void dump(std::string prefix, std::ostream &out);
  void enchant_randomly(void);
  void enemies_tick(void);
  void equip_carry_anim_id_set(ThingId equip_carry_anim_id, int equip);
  void equip_carry_anim_set(Thingp equip_carry_anim, int equip);
  void equip_remove_anim(int equip);
  void equip_use_anim_id_set(ThingId gfx_anim_use_id, int equip);
  void equip_use_anim_set(Thingp gfx_anim_use, int equip);
  void equip_use_offset_get(int *dx, int *dy, int equip);
  void err(const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);
  void err_(const char *fmt, va_list args); // compile error without
  void fadeup_fade_set(float);
  void fadeup(float fadeup_height, float fadeup_fade, ts_t ms);
  void fadeup_height_set(float);
  void fall_height_set(float);
  void fall_into_the_void(void);
  void frozen_set(void);
  void gas_poison_tick(void);
  void gc(void);
  void goal_penalty_tick(void);
  void grass_tick(void);
  void hide(void);
  void hooks_remove(void);
  void hunger_clock_tick(void);
  void hunger_update(void);
  void inherit_from(Thingp it);
  void init_hue(void);
  void init(Levelp, const std::string &name, point at, Thingp owner = nullptr);
  void init_lights(void);
  void interpolated_at_set(fpoint v);
  void inventory_particle(Thingp what, uint32_t slot);
  void inventory_particle(Thingp what, uint32_t slot, Thingp particle_target);
  void is_stuck_update(void);
  void jump_end(void);
  void killed(Thingp defeater, const char *reason);
  void killed(Thingp defeater, const std::string &reason);
  void leader_set(Thingp leader);
  void level_change(Levelp);
  void level_enter(bool rejoin = false);
  void level_leave(void);
  void level_pop(void);
  void level_push(void);
  void level_rejoin(void);
  void lifespan_tick(void);
  void light_distance_upd_with_torch_effect(uint8_t &light_dist);
  void light_dist_including_torch_effect_get(uint8_t &light_dist);
  void location_check_me(void);
  void location_check(Thingp filter_to = nullptr);
  void log(const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);
  void log_(const char *fmt, va_list args); // compile error without
  void lunge(point tt);
  void lunge_to_set(point);
  void map_beast_check(void);
  void map_beast_count_set(int);
  void map_treasure_check(void);
  void map_treasure_count_set(int);
  void mob_set(Thingp mob);
  void move_carried_items_immediately(void);
  void move_carried_items(void);
  void move_delta(point);
  void move_finish(void);
  void move_set_dir_from_delta(point);
  void move_set_dir_from_dest_or_delta(point delta);
  void move_set_dir_from_target(Thingp target);
  void move_speed_curr_set(int);
  void move_to_immediately(point to);
  void move_to(point to);
  void msg(const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);
  void msg_set(const std::string &);
  void necrosis_tick(void);
  void new_aip(void);
  void new_infop(void);
  void new_itemsp(void);
  void new_light(point offset, int light_dist);
  void new_light(point offset, int light_dist, color col, int fbo);
  void noop(void);
  void notify_followers_of_death_of_my_leader(void);
  void notify_of_death_of_my_leader(void);
  void on_born(void);
  void on_death_of_a_follower(Thingp leader);
  void on_death_of_my_leader(void);
  void on_dropped(void);
  void on_enchant(void);
  void on_equip(Thingp what);
  void on_fall(void);
  void on_final_use(Thingp what);
  void on_final_use(Thingp what, Thingp target);
  void on_fire_unset(void);
  void on_fire(void);
  void on_jump(void);
  void on_lifespan_tick(Thingp hitter);
  void on_move(void);
  void on_open(void);
  void on_owner_add(Thingp owner);
  void on_owner_remove(Thingp owner);
  void on_polymorphed(void);
  void on_resting(void);
  void on_stuck(void);
  void on_swing(Thingp what);
  void on_teleport(void);
  void on_thrown_callback(void);
  void on_thrown(void);
  void on_unequip(Thingp what);
  void on_use(Thingp what);
  void on_use(Thingp what, Thingp target);
  void on_waiting(void);
  void on_you_are_declared_a_follower(Thingp leader);
  void on_you_are_declared_leader(void);
  void on_you_are_hit_and_now_dead(Thingp hitter, Thingp real_hitter, bool crit, int dmg);
  void on_you_are_hit_but_dodge_it_do(Thingp hitter);
  void on_you_are_hit_but_still_alive(Thingp hitter, Thingp real_hitter, bool crit, int dmg);
  void on_you_nat_att(void);
  void owner_set(Thingp owner);
  void path_shorten(std::vector< point > &path);
  void physical_training_tick(void);
  void place_blood(bool force = false);
  void plant_tick(void);
  void poisoned(void);
  void poison_reason_set(const std::string &);
  void poison_tick(void);
  void polymorph(Tpp);
  void popup(const std::string &);
  void reinit(void);
  void release_followers(void);
  void remove_all_references(void);
  void remove_leader(void);
  void remove_mob(void);
  void remove_owner(void);
  void remove_spawner_owner(void);
  void reset_goal_penalty(Thingp attacker);
  void resting(void);
  void resurrect_forced(void);
  void resurrect_tick(void);
  void resurrect(void);
  void rotting(void);
  void score_add(Thingp victim);
  void score_incr(int);
  void score_set(int);
  void secret_door_tick(void);
  void show_botcon_description(void);
  void skill_activate(Thingp what);
  void skill_deactivate(Thingp what);
  void skill_remove_all(void);
  void sleep(void);
  void solid_rock_tick(void);
  void spawned_owner_set(Thingp spawner_owner);
  void stamina_boost(int v);
  void stats_tick(void);
  void stuck(const std::string &why);
  void submerged_offset_set(int);
  void teleport_end(void);
  void temperature_decr(int);
  void temperature_decr(void);
  void temperature_incr(int);
  void temperature_incr(void);
  void temperature_tick(void);
  void throw_at(Thingp w, Thingp target);
  void tick(void);
  void tiles_get(void);
  void topcon(const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);
  void topcon_(const char *fmt, va_list args); // compile error without
  void try_to_carry(const std::list< Thingp > &items);
  void unleash_minions(void);
  void unleash_spawners_things(void);
  void unstuck(void);
  void update_all(void);
  void update_interpolated_position(void);
  void update_light(void);
  void update_pos(point, bool immediately);
  void update_tick(void);
  void update(void);
  void used(Thingp w, Thingp target, bool remove_after_use, UseOptions *options = nullptr);
  void visible(void);
  void waiting(void);
  void water_tick(void);
  void weapon_check_for_damage(Thingp weapon, Thingp victim);
  void weapon_sheath(void);
  void wobble(float wobble);
  void wobble_set(float);
  // end sort marker4 {

  const std::array< std::array< ThingId, MAX_BAG_HEIGHT >, MAX_BAG_WIDTH > *stat_const_bag(void);

  std::array< std::array< ThingId, MAX_BAG_HEIGHT >, MAX_BAG_WIDTH > *bag_get(void);

  static std::function< int(Thingp) > matches_to_func(const std::string &what);

  std::list< Thingp > all_followers_get(void);

  std::pair< Path, Path > astar_solve(const class Goal *goal, char path_debug, point s, point g, const Dmap *d);

  ThingInfop  get_or_alloc_infop(void);
  ThingItemsp get_or_alloc_itemsp(void);
  ThingAip    get_or_alloc_aip(void);

  ThingInfop  maybe_infop(void) { return _infop; }
  ThingItemsp maybe_itemsp(void) { return _itemsp; }
  ThingAip    maybe_aip(void) { return _aip; }

  ThingInfop  infop(void);
  ThingItemsp itemsp(void);
  ThingAip    aip(void);

  bool victim_attack_best_attempt_1(Thingp item, point at, Thingp *best, point *best_hit_at,
                                    std::vector< point > &all_deltas, AttackOptions *attack_options);
  bool victim_attack_best_attempt_2(Thingp item, point at, Thingp *best, point *best_hit_at,
                                    std::vector< point > &all_deltas, AttackOptions *attack_options);
  bool victim_attack_best_attempt_3(Thingp item, point at, Thingp *best, point *best_hit_at,
                                    std::vector< point > &all_deltas, AttackOptions *attack_options);
  bool victim_attack_choose_best(Thingp item, point at, Thingp *best, point *best_hit_at,
                                 AttackOptions *attack_options);
  bool victim_attack_found_best(int equip, Thingp item, Thingp best, point best_hit_at, AttackOptions *o);

  inline int is_gfx_pixelart_animated(void) { return gfx_pixelart_animated; }
  inline int is_gfx_ascii_animated(void) { return gfx_ascii_animated; }

  int gfx_pixelart_attack_anim(void);
} Thing;

bool things_overlap(Thingp t, Thingp o);
bool things_overlap(Thingp t, fpoint t_at, Thingp o);

int bag_estimate_volume(const std::list< Thingp > &items);

std::string equip_name(int equip);

extern Thingp g_debug_thing;

#endif // _MY_THING_HPP_
