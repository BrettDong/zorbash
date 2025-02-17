import my
import tp


def on_you_nat_att(me, x, y):
    sound = f"hiss{my.non_pcg_randint(1, 10)}"
    my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound)


def tp_init(name, text_long_name):
    self = tp.Tp(name, text_long_name)
    # begin sort marker
    my.aggression_pct(self, 100)
    my.ai_resent_count(self, 100)
    my.ai_wanderer(self, True)
    my.attack_humanoid(self, True)
    my.attack_lunge(self, True)
    my.collision_check(self, True)
    my.collision_hit_priority(self, 20)
    my.damage_nat_att_dice(self, "1d6+6")
    my.damage_nat_att_type(self, "touch")
    my.damage_received_doubled_from_water(self, True)
    my.distance_vision(self, 7)
    my.environ_avoids_water(self, 100)
    my.gfx_anim_use(self, "scythe_swing")
    my.gfx_ascii_fade_with_dist(self, True)
    my.gfx_ascii_shown(self, True)
    my.gfx_oversized_and_on_floor(self, True)
    my.gfx_pixelart_animated_can_hflip(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_bounce_on_move(self, True)
    my.gfx_pixelart_health_bar_shown(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gfx_pixelart_wobbles_when_hit(self, True)
    my.health_initial_dice(self, "2d20+200")
    my.is_able_to_burn(self, True)
    my.is_able_to_change_levels(self, True)
    my.is_able_to_fall(self, True)
    my.is_able_to_see_in_the_dark(self, True)
    my.is_attackable_by_monst(self, True)
    my.is_attackable_by_player(self, True)
    my.is_biome_dungeon(self, True)
    my.is_corpse_on_death(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_ethereal(self, True)
    my.is_fearless(self, True)
    my.is_floating(self, True)
    my.is_hittable(self, True)
    my.is_immune_to_acid(self, True)
    my.is_immune_to_cold(self, True)
    my.is_immune_to_draining(self, True)
    my.is_immune_to_fire(self, True)
    my.is_immune_to_necrosis(self, True)
    my.is_immune_to_poison(self, True)
    my.is_immune_to_water(self, True)
    my.is_intelligent(self, True)
    my.is_interesting(self, True)
    my.is_loggable(self, True)
    my.is_monst_class_c(self, True)
    my.is_monst(self, True)
    my.is_moveable(self, True)
    my.is_msg_allowed_is_seen(self, True)
    my.is_msg_allowed_is_wounded(self, True)
    my.is_resurrectable(self, True)
    my.is_tickable(self, True)
    my.is_undead(self, True)
    my.move_speed(self, 100)
    my.noise_decibels_hearing(self, 0)
    my.normal_placement_rules(self, True)
    my.on_you_nat_att_do(self, "me.on_you_nat_att()")
    my.rarity(self, my.RARITY_VERY_RARE)
    my.resurrect_dice(self, "1d10+30")
    my.stat_con(self, 25)
    my.stat_def(self, 25)
    my.stat_dex(self, 10)
    my.stat_luck(self, 10)
    my.stat_str(self, 25)
    my.temperature(self, -10)
    my.text_a_or_an(self, "a")
    my.text_hits(self, "claws")
    my.text_long_description(self, "A lesser reaper. You cannot defeat what does not live!")
    my.text_short_description(self, "A lesser reaper. Death incarnate.")
    my.thing_size(self, my.THING_SIZE_NORMAL)
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_MONST)
    # end sort marker

    delay = 1000
    my.tile(self,
            ascii_fg_char="R", ascii_bg_col_name="", ascii_fg_col_name="gray50",
            tile=name + ".1", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="R", ascii_bg_col_name="", ascii_fg_col_name="gray50",
            tile=name + ".2", delay_ms=delay)

    delay = 20
    my.tile(self,
            ascii_fg_char="R", ascii_bg_col_name="", ascii_fg_col_name="gray50",
            tile=name + ".dead.1", is_dead=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="R", ascii_bg_col_name="", ascii_fg_col_name="gray50",
            tile=name + ".dead.2", is_dead=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="R", ascii_bg_col_name="", ascii_fg_col_name="gray50",
            tile=name + ".dead.3", is_dead=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="R", ascii_bg_col_name="", ascii_fg_col_name="gray50",
            tile=name + ".dead.4", is_dead=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="R", ascii_bg_col_name="", ascii_fg_col_name="gray50",
            tile=name + ".dead.5", is_dead=True, is_end_of_anim=True)

    my.tile(self,
            ascii_fg_char="R", ascii_bg_col_name="", ascii_fg_col_name="gray50",
            tile=name + ".dead.5", is_resurrecting=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="R", ascii_bg_col_name="", ascii_fg_col_name="gray50",
            tile=name + ".dead.4", is_resurrecting=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="R", ascii_bg_col_name="", ascii_fg_col_name="gray50",
            tile=name + ".dead.3", is_resurrecting=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="R", ascii_bg_col_name="", ascii_fg_col_name="gray50",
            tile=name + ".dead.2", is_resurrecting=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="R", ascii_bg_col_name="", ascii_fg_col_name="gray50",
            tile=name + ".dead.1",
            is_resurrecting=True,
            is_end_of_anim=True,
            is_alive_on_end_of_anim=True)

    my.tp_update(self)


def init():
    tp_init(name="reaper", text_long_name="reaper")


init()
