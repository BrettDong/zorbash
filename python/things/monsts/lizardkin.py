import my
import tp


def on_born(me, x, y):
    my.thing_friend(me, "lizardkin")
    my.thing_enemy(me, "dogman")


def on_you_nat_att(me, x, y):
    sound = f"hiss{my.non_pcg_randint(1, 10)}"
    my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound)


def on_you_are_hit_but_still_alive(me, hitter, real_hitter, x, y, crit, damage):
    sound = f"hiss{my.non_pcg_randint(1, 10)}"
    my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound)


def on_you_are_hit_but_dodge_it_do(me, hitter, x, y):
    sound = f"hiss{my.non_pcg_randint(1, 10)}"
    my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound)


def on_death(me, x, y):
    my.thing_msg(me, "The lizardman hisses and promptly dies!")

    sound = f"growl{my.non_pcg_randint(1, 10)}"
    if not my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound):
        my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, sound)


def on_firing_at_something(me, target, x, y):  # Return True on doing an action
    if my.pcg_randint(1, 100) < 8:
        sound = f"growl{my.non_pcg_randint(1, 10)}"
        if not my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound):
            my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, sound)
        my.thing_fire_at(me, "projectile_fire", target)
        return True
    return False


def tp_init(name, text_long_name):
    self = tp.Tp(name, text_long_name)
    # begin sort marker
    my.aggression_pct(self, 90)
    my.ai_resent_count(self, 100)
    my.ai_wanderer(self, True)
    my.attack_eater(self, True)
    my.attack_lunge(self, True)
    my.bite_amount(self, 10)
    my.collision_check(self, True)
    my.collision_hit_priority(self, 20)
    my.damage_nat_att_chance_d1000(self, 0, 100)
    my.damage_nat_att_dice(self, "1d6+1")
    my.damage_nat_att_type(self, "bite")
    my.distance_avoid(self, 4)
    my.distance_vision(self, 10)
    my.environ_avoids_acid(self, 100)
    my.environ_avoids_cold(self, 100)
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
    my.health_initial_dice(self, "2d8")
    my.hunger_clock_tick_freq(self, 50)
    my.hunger_is_insatiable(self, True)
    my.is_able_to_be_surprised(self, True)
    my.is_able_to_fall(self, True)
    my.is_able_to_fire_at(self, True)
    my.is_able_to_freeze(self, True)
    my.is_able_to_rest(self, True)
    my.is_able_to_see_in_the_dark(self, True)
    my.is_able_to_sleep(self, True)
    my.is_able_to_tire(self, True)
    my.is_air_breather(self, True)
    my.is_attackable_by_monst(self, True)
    my.is_attackable_by_player(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_swamp(self, True)
    my.is_bleeder(self, True)
    my.is_corpse_on_death(self, True)
    my.is_corpse_with_bones(self, True)
    my.is_crushable(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_eater_of_food(self, True)
    my.is_eater_of_meat(self, True)
    my.is_eater_of_red_blood(self, True)
    my.is_fearless(self, True)
    my.is_hittable(self, True)
    my.is_humanoid(self, True)
    my.is_immune_to_fire(self, True)
    my.is_interesting(self, True)
    my.is_living(self, True)
    my.is_loggable(self, True)
    my.is_meat(self, True)
    my.is_monst_class_b(self, True)
    my.is_monst(self, True)
    my.is_moveable(self, True)
    my.is_msg_allowed_is_seen(self, True)
    my.is_msg_allowed_is_surprised(self, True)
    my.is_msg_allowed_is_wounded(self, True)
    my.is_red_blooded(self, True)
    my.is_shovable(self, True)
    my.is_temperature_sensitive(self, True)
    my.is_tickable(self, True)
    my.move_speed(self, 100)
    my.noise_decibels_hearing(self, 50)
    my.normal_placement_rules(self, True)
    my.nutrition_dice(self, "1d4")
    my.on_born_do(self, "me.on_born()")
    my.on_death_do(self, "me.on_death()")
    my.on_firing_at_something_do(self, "me.on_firing_at_something()")
    my.on_you_are_hit_but_dodge_it_do(self, "me.on_you_are_hit_but_dodge_it_do()")
    my.on_you_are_hit_but_still_alive_do(self, "me.on_you_are_hit_but_still_alive()")
    my.on_you_nat_att_do(self, "me.on_you_nat_att()")
    my.rarity(self, my.RARITY_COMMON)
    my.stamina(self, 100)
    my.stat_con(self, 11)
    my.stat_def(self, 12)
    my.stat_dex(self, 12)
    my.stat_luck(self, 8)
    my.stat_str(self, 8)
    my.temperature(self, 20)
    my.text_a_or_an(self, "a")
    my.text_hits(self, "gores")
    my.text_long_description2(self, "Lizardkin hate dogmen. Something to do with barking.")
    my.text_long_description3(self, "Lizardkin do not make good pets.")
    my.text_long_description(self, "Lizardkin are a primitive and savage race and proudly eshew all forms of weaponry, believing that their claws, teeth and... devastating fire breath are all they need for home defense.")
    my.text_short_description(self, "A firey lizardkin.")
    my.thing_size(self, my.THING_SIZE_NORMAL)
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_MONST)
    # end sort marker

    delay = 900
    my.tile(self,
            ascii_fg_char="l", ascii_bg_col_name="", ascii_fg_col_name="orange",
            tile=name + ".1", delay_ms=delay, frame=1)
    my.tile(self,
            ascii_fg_char="l", ascii_bg_col_name="", ascii_fg_col_name="orange",
            tile=name + ".2", delay_ms=delay, frame=2)
    my.tile(self,
            ascii_fg_char="l", ascii_bg_col_name="", ascii_fg_col_name="orange",
            tile=name + ".3", delay_ms=delay, frame=3)
    my.tile(self,
            ascii_fg_char="l", ascii_bg_col_name="", ascii_fg_col_name="orange",
            tile=name + ".4", delay_ms=delay, frame=4)
    my.tile(self,
            ascii_fg_char="l", ascii_bg_col_name="", ascii_fg_col_name="orange",
            tile=name + ".5", delay_ms=delay, frame=5)
    my.tile(self,
            ascii_fg_char="l", ascii_bg_col_name="", ascii_fg_col_name="orange",
            tile=name + ".6", delay_ms=delay, frame=6)
    my.tile(self,
            ascii_fg_char=".", ascii_bg_col_name="", ascii_fg_col_name="orange",
            tile="lizardkin.sleeping.1", is_sleeping=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char=".", ascii_bg_col_name="", ascii_fg_col_name="orange",
            tile="lizardkin.sleeping.2", is_sleeping=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char=".", ascii_bg_col_name="", ascii_fg_col_name="gray50",
            tile="lizardkin.dead.1", is_dead=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char=".", ascii_bg_col_name="", ascii_fg_col_name="gray50",
            tile="lizardkin.dead.2", is_dead=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char=".", ascii_bg_col_name="", ascii_fg_col_name="gray50",
            tile="lizardkin.dead.3", is_dead=True, delay_ms=delay, is_end_of_anim=True)

    my.tp_update(self)


def init():
    tp_init(name="lizardkin", text_long_name="lizardkin")


init()
