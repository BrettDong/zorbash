import my
import tp


def on_born(me, x, y):
    my.thing_friend(me, "zorb_wizard")
    my.thing_friend(me, "zorb_captain")
    my.thing_friend(me, "zorb_eldster")
    my.thing_friend(me, "zorb_necro")
    my.thing_friend(me, "zorb_pirate")
    my.thing_friend(me, "zorb_priest")
    my.thing_friend(me, "zorb_single")
    my.thing_friend(me, "zorb_soldier")
    my.thing_friend(me, "zorb_wizard")


def on_you_nat_att(me, x, y):
    sound = f"hiss{my.non_pcg_randint(1, 10)}"
    my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound)


def on_you_are_hit_but_still_alive(me, hitter, real_hitter, x, y, crit, damage):
    sound = f"hiss{my.non_pcg_randint(1, 10)}"
    if not my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound):
        my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, sound)


def on_you_are_hit_but_dodge_it_do(me, hitter, x, y):
    sound = f"hiss{my.non_pcg_randint(1, 10)}"
    if not my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound):
        my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, sound)


def on_death(me, x, y):
    if not my.thing_sound_play_channel(me, my.CHANNEL_MONST, "monst_death1"):
        my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, "monst_death1")


def tp_init(name, text_long_name):
    self = tp.Tp(name, text_long_name)
    # begin sort marker
    my.aggression_pct(self, 75)
    my.ai_detect_secret_doors(self, True)
    my.ai_resent_count(self, 20)
    my.ai_shove_chance_d1000(self, 500)
    my.ai_wanderer(self, True)
    my.attack_eater(self, True)
    my.attack_lunge(self, True)
    my.attack_meat(self, True)
    my.attack_undead(self, True)
    my.bite_amount(self, 10)
    my.capacity_height(self, 10)
    my.capacity_width(self, 10)
    my.collateral_damage_pct(self, 50)
    my.collision_check(self, True)
    my.collision_hit_priority(self, 20)
    my.damage_nat_att_dice(self, "1d4+2")
    my.damage_nat_att_type(self, "gore")
    my.distance_avoid(self, 5)
    my.distance_leader_max(self, 5)
    my.distance_vision(self, 7)
    my.environ_avoids_acid(self, 100)
    my.environ_avoids_fire(self, 10)
    my.environ_avoids_poison(self, 100)
    my.gfx_anim_use(self, "attack_claws")
    my.gfx_ascii_fade_with_dist(self, True)
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_animated_can_hflip(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_bounce_on_move(self, True)
    my.gfx_pixelart_health_bar_shown(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gfx_pixelart_show_asleep_anim(self, True)
    my.gfx_pixelart_show_outlined(self, True)
    my.gfx_pixelart_submergable(self, True)
    my.gfx_pixelart_wobbles_when_hit(self, True)
    my.health_initial_dice(self, "2d6")
    my.hunger_clock_tick_freq(self, 50)
    my.is_able_to_attack_mobs(self, True)
    my.is_able_to_be_surprised(self, True)
    my.is_able_to_break_down_doors(self, True)
    my.is_able_to_break_out_of_ice(self, True)
    my.is_able_to_break_out_of_webs(self, True)
    my.is_able_to_burn(self, True)
    my.is_able_to_change_levels(self, True)
    my.is_able_to_collect_keys(self, True)
    my.is_able_to_enchant_items(self, True)
    my.is_able_to_fall(self, True)
    my.is_able_to_follow(self, True)
    my.is_able_to_freeze(self, True)
    my.is_able_to_jump(self, True)
    my.is_able_to_learn_skills(self, True)
    my.is_able_to_move_diagonally(self, True)
    my.is_able_to_open_doors(self, True)
    my.is_able_to_rest(self, True)
    my.is_able_to_see_in_the_dark(self, True)
    my.is_able_to_shove(self, True)
    my.is_able_to_sleep(self, True)
    my.is_able_to_tire(self, True)
    my.is_able_to_use_amulet(self, True)
    my.is_able_to_use_boots(self, True)
    my.is_able_to_use_cloak(self, True)
    my.is_able_to_use_gauntlet(self, True)
    my.is_able_to_use_rings(self, True)
    my.is_able_to_use_wands_or_staffs(self, True)
    my.is_air_breather(self, True)
    my.is_attackable_by_monst(self, True)
    my.is_attackable_by_player(self, True)
    my.is_biome_dungeon(self, True)
    my.is_bleeder(self, True)
    my.is_corpse_on_death(self, True)
    my.is_corpse_with_bones(self, True)
    my.is_crushable(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_explorer(self, True)
    my.is_green_blooded(self, True)
    my.is_hittable(self, True)
    my.is_humanoid(self, True)
    my.is_interesting(self, True)
    my.is_item_carrier(self, True)
    my.is_item_collector(self, True)
    my.is_living(self, True)
    my.is_loggable(self, True)
    my.is_meat(self, True)
    my.is_monst(self, True)
    my.is_moveable(self, True)
    my.is_msg_allowed_is_seen(self, True)
    my.is_msg_allowed_is_surprised(self, True)
    my.is_msg_allowed_is_wounded(self, True)
    my.is_shovable(self, True)
    my.is_steal_item_chance_d1000(self, 50)
    my.is_temperature_sensitive(self, True)
    my.is_tickable(self, True)
    my.jump_distance(self, 3)
    my.move_speed(self, 100)
    my.noise_decibels_hearing(self, 10)
    my.noise_on_moving(self, 5)
    my.normal_placement_rules(self, True)
    my.on_born_do(self, "me.on_born()")
    my.on_death_do(self, "zorb_all.on_death()")
    my.on_death_drop_all_items(self, True)
    my.on_you_are_hit_but_dodge_it_do(self, "zorb_all.on_you_are_hit_but_dodge_it_do()")
    my.on_you_are_hit_but_still_alive_do(self, "zorb_all.on_you_are_hit_but_still_alive()")
    my.on_you_nat_att_do(self, "me.on_you_nat_att()")
    my.on_you_nat_att_do(self, "zorb_all.on_you_nat_att()")
    my.rarity(self, my.RARITY_COMMON)
    my.stamina(self, 100)
    my.stat_att_penalty_when_idle_max(self, 0)
    my.stat_att_penalty_when_idle(self, 0)
    my.stat_att_penalty_when_in_deep_water(self, 5)
    my.stat_att_penalty_when_in_shallow_water(self, 2)
    my.stat_att_penalty_when_stuck_max(self, 2)
    my.stat_att_penalty_when_stuck(self, 1)
    my.stat_con(self, 10)
    my.stat_def_penalty_when_idle_max(self, 5)
    my.stat_def_penalty_when_idle(self, 5)
    my.stat_def_penalty_when_in_deep_water(self, 5)
    my.stat_def_penalty_when_in_shallow_water(self, 2)
    my.stat_def_penalty_when_stuck_max(self, 15)
    my.stat_def_penalty_when_stuck(self, 10)
    my.stat_def(self, 10)
    my.stat_dex(self, 12)
    my.stat_luck(self, 8)
    my.stat_str(self, 8)
    my.temperature(self, 20)
    my.text_a_or_an(self, "a")
    my.text_hits(self, "claws")
    my.text_long_description(self, "Zorblins are small, green skinned beings that lair in abandoned mines, despoiled dungeons and other dismal settings, otherwise known as their homes. They spend their time defending their natural habitat from invading marauders, like you. They often carry some meagre amounts of gold, dug from the depths with bare, shaking hands.")
    my.thing_size(self, my.THING_SIZE_NORMAL)
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_MONST)
    # end sort marker
    return self
