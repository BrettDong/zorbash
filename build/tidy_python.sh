#!/bin/bash
#
# Adds default flags to all the templates and sorts them so it is easier to
# see what is missing or needs added.
#
# Use "do" as the first arg if the output looks sane.
#

PRE=$(mktemp) || exit 1
PAYLOAD=$(mktemp) || exit 1
POST=$(mktemp) || exit 1
OUT=$(mktemp) || exit 1

for i in \
    amulets \
    armor \
    boots \
    buffs \
    debuffs \
    doors \
    dungeon \
    effects \
    food \
    gauntlets \
    internal \
    items \
    lasers \
    mobs \
    monsts \
    player \
    potions \
    projectiles \
    rings \
    skills \
    treasure \
    wands \
    weapons
do
  cp .flake8 $i/
  git add $i/.flake8
done

for IN in \
    amulets/*py \
    armor/*py \
    boots/*py \
    buffs/*py \
    debuffs/*py \
    doors/*py \
    dungeon/*py \
    effects/*py \
    food/*py \
    gauntlets/*py \
    internal/*py \
    items/*py \
    lasers/*py \
    mobs/*py \
    monsts/*py \
    player/*py \
    potions/*py \
    projectiles/*py \
    rings/*py \
    skills/*py \
    treasure/*py \
    wands/*py \
    weapons/*py
do
    echo Tidying $IN...

    grep -q is_monst_pack $IN
    if [ $? -eq 0 ]; then
        continue
    fi

    sed '1,/begin sort marker/!d' $IN > $PRE
    sed '/begin sort marker/,/end sort marker/!d' $IN | tail -n +1 - | grep -v "sort marker" | sort > $PAYLOAD
    sed '/end sort marker/,$!d' $IN | tail -n +1 - > $POST

    for arg in \
      aggression_pct \
      ai_detect_secret_doors \
      ai_obstacle \
      ai_resent_count \
      ai_wanderer \
      appearing_chance_d1000 \
      attack_eater \
      attack_humanoid \
      attack_living \
      attack_lunge \
      attack_meat \
      attack_no_msg \
      attacks_per_round \
      attack_undead \
      bite_amount \
      collateral_damage_pct \
      collision_check \
      collision_hit_180 \
      collision_hit_360 \
      collision_hit_adj \
      collision_hit_priority \
      collision_hit_two_tiles_ahead \
      damage_received_doubled_from_acid \
      damage_received_doubled_from_cold \
      damage_received_doubled_from_fire \
      damage_received_doubled_from_necrosis \
      damage_received_doubled_from_poison \
      damage_received_doubled_from_water \
      distance_leader_max \
      distance_minion_vision_shared \
      enchant_level \
      enchant_max \
      environ_avoids_acid \
      environ_avoids_fire \
      environ_avoids_necrosis \
      environ_avoids_poison \
      environ_avoids_water \
      gfx_an_animation_only \
      gfx_ascii_animated \
      gfx_ascii_bg_color_spread_blue \
      gfx_ascii_bg_color_spread_green \
      gfx_ascii_bg_color_spread_hue \
      gfx_ascii_bg_color_spread_red \
      gfx_ascii_color_is_animated \
      gfx_ascii_fade_with_dist \
      gfx_ascii_fg_color_is_animated \
      gfx_ascii_fg_color_spread_blue \
      gfx_ascii_fg_color_spread_green \
      gfx_ascii_fg_color_spread_hue \
      gfx_ascii_fg_color_spread_red \
      gfx_ascii_shown_as_gray_in_shadow \
      gfx_ascii_shown_in_bg \
      gfx_attack_anim \
      gfx_bounce_always \
      gfx_bounce_on_move \
      gfx_dead_anim \
      gfx_equip_carry_anim \
      gfx_glows \
      gfx_health_bar_autohide \
      gfx_health_bar_only_when_awake \
      gfx_health_bar_shown \
      gfx_long_shadow_caster \
      gfx_on_fire_anim \
      gfx_oversized_and_on_floor \
      gfx_pixelart_animated \
      gfx_pixelart_animated_can_hflip \
      gfx_pixelart_animated_can_vflip \
      gfx_pixelart_animated_no_dir \
      gfx_pixelart_flickers \
      gfx_pixelart_shown_in_bg \
      gfx_show_asleep \
      gfx_show_outlined \
      gfx_solid_shadow \
      gfx_very_short_shadow_caster \
      gfx_water \
      gfx_wobbles_when_hit \
      hunger_clock_tick_freq \
      hunger_is_insatiable \
      internal \
      is_able_to_attack_mobs \
      is_able_to_attack_owner \
      is_able_to_be_surprised \
      is_able_to_break_down_doors \
      is_able_to_break_out_of_ice \
      is_able_to_break_out_of_webs \
      is_able_to_burn \
      is_able_to_change_levels \
      is_able_to_collect_keys \
      is_able_to_enchant_items \
      is_able_to_fall \
      is_able_to_fire_at \
      is_able_to_follow \
      is_able_to_freeze \
      is_able_to_jump \
      is_able_to_jump_attack \
      is_able_to_jump_attack_chance_d1000 \
      is_able_to_jump_escape \
      is_able_to_jump_onto \
      is_able_to_jump_without_tiring \
      is_able_to_learn_skills \
      is_able_to_move_diagonally \
      is_able_to_open_doors \
      is_able_to_rest \
      is_able_to_see_in_the_dark \
      is_able_to_see_through_doors \
      is_able_to_shove \
      is_able_to_sleep \
      is_able_to_swim \
      is_able_to_teleport_attack \
      is_able_to_teleport_escape \
      is_able_to_teleport_without_tiring \
      is_able_to_tire \
      is_able_to_use_amulet \
      is_able_to_use_armor \
      is_able_to_use_boots \
      is_able_to_use_cloak \
      is_able_to_use_gauntlet \
      is_able_to_use_helmet \
      is_able_to_use_rings \
      is_able_to_use_shield \
      is_able_to_use_wands_or_staffs \
      is_able_to_use_weapons \
      is_able_to_walk_through_walls \
      is_acid \
      is_air_breather \
      is_alive_on_end_of_anim \
      is_always_hit \
      is_amulet \
      is_aquatic \
      is_armor \
      is_ascend_dungeon \
      is_ascend_sewer \
      is_asleep_initially \
      is_attackable_by_monst \
      is_attackable_by_player \
      is_auto_collect_item \
      is_auto_equipped \
      is_auto_throw \
      is_auto_use \
      is_bag \
      is_bag_item \
      is_bag_item_container \
      is_bag_item_not_stackable \
      is_barrel \
      is_basalt \
      is_biome_dungeon \
      is_biome_sewer \
      is_biome_swamp \
      is_biome_unused \
      is_bleeder \
      is_block_of_ice \
      is_bones \
      is_boots \
      is_brazier \
      is_bridge \
      is_brittle \
      is_buff \
      is_carnivorous_plant \
      is_carrier_of_treasure_class_a \
      is_carrier_of_treasure_class_b \
      is_carrier_of_treasure_class_c \
      is_carrier_of_weapon_class_a \
      is_carrier_of_weapon_class_b \
      is_carrier_of_weapon_class_c \
      is_chasm \
      is_cloak \
      is_cold \
      is_collectable \
      is_collected_as_gold \
      is_collected_as_keys \
      is_combustible \
      is_corpse_on_death \
      is_corpse_with_bones \
      is_corridor \
      is_cowardly \
      is_critical_to_level \
      is_crushable \
      is_crystal \
      is_cursor \
      is_cursor_can_hover_over \
      is_cursor_can_hover_over_x2_click \
      is_cursor_path \
      is_cursor_path_blocker \
      is_cursor_path_hazard \
      is_dagger \
      is_dead_on_end_of_anim \
      is_dead_on_falling \
      is_dead_on_shove \
      is_debuff \
      is_debug_path \
      is_debug_type \
      is_deep_water \
      is_deep_water_swimmer \
      is_descend_dungeon \
      is_descend_sewer \
      is_described_when_hovering_over \
      is_destroyed_on_hit_or_miss \
      is_destroyed_on_hitting \
      is_dirt \
      is_door \
      is_droppable \
      is_dry_grass \
      is_dry_grass_trampled \
      is_eater_of_amulets \
      is_eater_of_armor \
      is_eater_of_boots \
      is_eater_of_cloaks \
      is_eater_of_food \
      is_eater_of_gauntlets \
      is_eater_of_green_blood \
      is_eater_of_helmets \
      is_eater_of_jelly \
      is_eater_of_magical_items \
      is_eater_of_meat \
      is_eater_of_potions \
      is_eater_of_red_blood \
      is_eater_of_rings \
      is_eater_of_shields \
      is_eater_of_staffs \
      is_eater_of_treasure \
      is_eater_of_wands \
      is_eater_of_weapons \
      is_enchantable \
      is_enchantstone \
      is_engulfer \
      is_ethereal \
      is_ethereal_mob \
      is_exit_finder \
      is_explorer \
      is_explosion \
      is_fearless \
      is_fire \
      is_flat \
      is_floating \
      is_floor \
      is_floor_deco \
      is_flying \
      is_foilage \
      is_food \
      is_gas_blocker \
      is_gauntlet \
      is_gelatinous \
      gfx_anim_synced_with_owner \
      is_glass \
      is_gold \
      is_green_blood \
      is_green_blooded \
      is_green_splatter \
      is_hard \
      is_hazard \
      is_health_booster \
      is_heavy \
      is_helmet \
      is_hittable \
      is_humanoid \
      is_ice \
      is_immune_to_acid \
      is_immune_to_cold \
      is_immune_to_draining \
      is_immune_to_fire \
      is_immune_to_necrosis \
      is_immune_to_poison \
      is_immune_to_spiderwebs \
      is_immune_to_water \
      is_intelligent \
      is_interesting \
      is_item \
      is_item_carrier \
      is_item_collector \
      is_item_organic \
      is_item_targetted \
      is_jelly \
      is_jump_blocker \
      is_key \
      is_key_special \
      is_laser \
      is_lava \
      is_lifeless \
      is_light_blocker \
      is_light_blocker_for_monst \
      is_living \
      is_loggable \
      is_magical \
      is_map_beast \
      is_map_treasure \
      is_meat \
      is_able_to_melt \
      is_metal \
      is_minion \
      is_mob \
      is_mob_challenge_class_a \
      is_mob_challenge_class_b \
      is_monst \
      is_monst_class_a \
      is_monst_class_b \
      is_monst_class_c \
      is_monst_class_d \
      is_monst_class_e \
      is_moveable \
      is_msg \
      is_necrotic_danger_level \
      is_no_tile \
      is_obs_destructable \
      is_obs_for_shoving \
      is_obstacle_when_dead \
      is_obs_wall_or_door \
      is_openable \
      is_organic \
      is_monst_pack \
      is_pillar \
      is_pink_splatter \
      is_plant \
      is_player \
      is_poisonous_danger_level \
      is_potion \
      is_projectile \
      is_red_blood \
      is_red_blooded \
      is_red_splatter \
      is_removeable_if_out_of_slots \
      is_resurrectable \
      is_ring \
      is_ripple \
      is_rock \
      is_rusty \
      is_secret_door \
      is_sewer_wall \
      is_shallow_water \
      is_shallow_water_swimmer \
      is_shield \
      is_shovable \
      is_shovable_and_sticky \
      is_skill \
      is_skillstone \
      is_slippery \
      is_smoke \
      is_snake \
      is_soft \
      is_spawner \
      is_spider \
      is_spiderweb \
      is_staff \
      is_steam \
      is_sticky \
      is_stone \
      is_always_submerged \
      is_swimmer \
      is_sword \
      is_target_radial \
      is_target_select \
      is_temperature_change_sensitive \
      is_temperature_sensitive \
      is_the_grid \
      is_thief \
      is_throwable \
      is_throw_blocker \
      is_tickable \
      is_tireless \
      is_tmp_thing \
      is_torch \
      is_treasure \
      is_treasure_chest \
      is_treasure_class_a \
      is_treasure_class_b \
      is_treasure_class_c \
      is_treasure_type \
      is_undead \
      is_usable \
      is_used_when_thrown \
      is_very_combustible \
      is_very_hard \
      is_very_heavy \
      is_wall \
      is_wall_dungeon \
      is_wand \
      is_weapon \
      is_wooden \
      move_speed \
      is_msg_allowed_is_seen \
      is_msg_allowed_is_surprised \
      is_msg_allowed_is_wounded \
      noise_additional_on_jump_end \
      noise_additional_on_teleporting \
      noise_blocker \
      noise_decibels_hearing \
      noise_on_born \
      noise_on_dropping \
      noise_on_moving \
      noise_on_open \
      noise_on_you_are_hit_and_now_dead \
      noise_on_you_are_hit_but_still_alive \
      normal_placement_rules \
      on_death_drop_all_items \
      shove_strength \
      spawn_group_radius \
      stamina_drain_on_attacking \
      stat_att_penalty_when_idle \
      stat_att_penalty_when_idle_max \
      stat_att_penalty_when_in_deep_water \
      stat_att_penalty_when_in_shallow_water \
      stat_att_penalty_when_stuck \
      stat_att_penalty_when_stuck_max \
      stat_def_penalty_when_idle \
      stat_def_penalty_when_idle_max \
      stat_def_penalty_when_in_deep_water \
      stat_def_penalty_when_in_shallow_water \
      stat_def_penalty_when_stuck \
      stat_def_penalty_when_stuck_max \
      teleport_distance \
      temperature \
      tick_prio \
      unused_flag1 \
      unused_flag10 \
      unused_flag11 \
      unused_flag12 \
      unused_flag123 \
      unused_flag13 \
      unused_flag14 \
      unused_flag15 \
      unused_flag16 \
      unused_flag17 \
      unused_flag18 \
      unused_flag19 \
      unused_flag2 \
      unused_flag20 \
      unused_flag21 \
      unused_flag22 \
      unused_flag23 \
      unused_flag24 \
      unused_flag25 \
      unused_flag26 \
      unused_flag27 \
      unused_flag28 \
      unused_flag29 \
      unused_flag3 \
      unused_flag30 \
      unused_flag31 \
      unused_flag32 \
      unused_flag33 \
      unused_flag34 \
      unused_flag35 \
      unused_flag36 \
      unused_flag37 \
      unused_flag38 \
      unused_flag39 \
      unused_flag4 \
      unused_flag40 \
      gfx_pixelart_submergable \
      is_obs_for_jump_landing \
      gfx_pixelart_reflection \
      gfx_pixelart_shadow \
      unused_flag48 \
      unused_flag5 \
      unused_flag56 \
      unused_flag6 \
      unused_flag7 \
      unused_flag8 \
      unused_flag87 \
      unused_flag9 \
      on_death_is_open
    do
        grep -q $arg $PAYLOAD
        # Too much noise
        #if [ $? -ne 0 ]; then
        #  echo "    my.tp_$arg(self, False)" >> $PAYLOAD
        #fi
    done

    sort $PAYLOAD | uniq > $PAYLOAD.tmp
    mv $PAYLOAD.tmp $PAYLOAD

    cat $PRE $PAYLOAD $POST > $OUT

    diff $OUT $IN

    if [ "$1" = "do" ]; then
        mv $OUT $IN
    fi
done
