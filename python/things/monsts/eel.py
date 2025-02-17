import my
import tp


def on_you_nat_att(me, x, y):
    sound = f"growl{my.non_pcg_randint(1, 10)}"
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
    sound = "squeaky_toy"
    if not my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound):
        my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, sound)


def tp_init(name, text_long_name):
    self = tp.Tp(name, text_long_name)
    # begin sort marker
    my.aggression_pct(self, 100)
    my.ai_resent_count(self, 100)
    my.ai_wanderer(self, True)
    my.attack_eater(self, True)
    my.attack_humanoid(self, True)
    my.attack_lunge(self, True)
    my.attack_meat(self, True)
    my.bite_amount(self, 1)
    my.collision_check(self, True)
    my.collision_hit_priority(self, 20)
    my.damage_bite_chance_d1000(self, 0, 500)
    my.damage_bite_dice(self, "1d4")
    my.damage_nat_att_chance_d1000(self, 0, 900)
    my.damage_nat_att_dice(self, "1d3+1")
    my.damage_nat_att_type(self, "bite")
    my.distance_avoid(self, 3)
    my.distance_vision(self, 10)
    my.environ_avoids_poison(self, 100)
    my.gfx_anim_use(self, "attack_claws")
    my.gfx_ascii_fade_with_dist(self, True)
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_submergable(self, True)
    my.gfx_pixelart_wobbles_when_hit(self, True)
    my.health_initial_dice(self, "1d10")
    my.hunger_clock_tick_freq(self, 50)
    my.is_able_to_freeze(self, True)
    my.is_able_to_rest(self, True)
    my.is_able_to_see_in_the_dark(self, True)
    my.is_able_to_tire(self, True)
    my.is_air_breather(self, True)
    my.is_always_submerged(self, True)
    my.is_attackable_by_monst(self, True)
    my.is_attackable_by_player(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_sewer(self, True)
    my.is_biome_swamp(self, True)
    my.is_bleeder(self, True)
    my.is_corpse_on_death(self, True)
    my.is_corpse_with_bones(self, True)
    my.is_crushable(self, True)
    my.is_deep_water_swimmer(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_eater_of_meat(self, True)
    my.is_hittable(self, True)
    my.is_immune_to_water(self, True)
    my.is_interesting(self, True)
    my.is_loggable(self, True)
    my.is_meat(self, True)
    my.is_monst_class_a(self, True)
    my.is_monst(self, True)
    my.is_moveable(self, True)
    my.is_red_blooded(self, True)
    my.is_shallow_water_swimmer(self, True)
    my.is_soft(self, True)
    my.is_swimmer(self, True)
    my.is_temperature_sensitive(self, True)
    my.is_tickable(self, True)
    my.move_speed(self, 50)
    my.noise_decibels_hearing(self, 0)
    my.normal_placement_rules(self, True)
    my.on_death_do(self, "me.on_death()")
    my.on_you_are_hit_but_dodge_it_do(self, "me.on_you_are_hit_but_dodge_it_do()")
    my.on_you_are_hit_but_still_alive_do(self, "me.on_you_are_hit_but_still_alive()")
    my.on_you_nat_att_do(self, "me.on_you_nat_att()")
    my.rarity(self, my.RARITY_COMMON)
    my.stamina(self, 100)
    my.stat_con(self, 10)
    my.stat_def(self, 14)
    my.stat_dex(self, 15)
    my.stat_luck(self, 10)
    my.stat_str(self, 2)
    my.temperature(self, 20)
    my.text_a_or_an(self, "a")
    my.text_hits(self, "bites")
    my.text_long_description(self, "A delightfully friendly eel that just wants to hug..")
    my.text_short_description(self, "An eel.")
    my.thing_size(self, my.THING_SIZE_TINY)
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_MONST)
    # end sort marker

    delay = 70
    my.tile(self,
            ascii_fg_char="e", ascii_bg_col_name="", ascii_fg_col_name="brown",
            tile=name + ".1", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="e", ascii_bg_col_name="", ascii_fg_col_name="brown",
            tile=name + ".2", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="e", ascii_bg_col_name="", ascii_fg_col_name="brown",
            tile=name + ".3", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="e", ascii_bg_col_name="", ascii_fg_col_name="brown",
            tile=name + ".4", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="e", ascii_bg_col_name="", ascii_fg_col_name="brown",
            tile=name + ".5", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="e", ascii_bg_col_name="", ascii_fg_col_name="brown",
            tile=name + ".6", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="e", ascii_bg_col_name="", ascii_fg_col_name="brown",
            tile=name + ".7", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="e", ascii_bg_col_name="", ascii_fg_col_name="brown",
            tile=name + ".8", delay_ms=delay)

    my.tile(self,
            ascii_fg_char="e", ascii_bg_col_name="", ascii_fg_col_name="gray50",
            tile=name + ".3", is_dead=True, is_end_of_anim=True)

    my.tp_update(self)


def init():
    tp_init(name="eel", text_long_name="cuddly eel")


init()
