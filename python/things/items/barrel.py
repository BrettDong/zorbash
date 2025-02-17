import my
import tp


def explode(me, x, y):
    if my.thing_is_dead(me):
        return

    my.thing_dead(me, "exploded")
    my.thing_msg(me, "The oil filled barrel explodes!")
    my.spawn_at_my_position(me, "explosion_major")
    my.spawn_fire_around_thing(me, "fire")
    my.spawn_at_my_position(me, "fire")


def on_fire(me, x, y):
    explode(me, x, y)


def on_fall(me, x, y):
    explode(me, x, y)


def on_death(me, x, y):
    explode(me, x, y)


def tp_init(name, text_long_name):
    self = tp.Tp(name, text_long_name)
    # begin sort marker
    my.ai_obstacle(self, True)
    my.appearing_chance_d1000(self, 100)
    my.collision_check(self, True)
    my.collision_hit_priority(self, 1)
    my.damage_crush_chance_d1000(self, 0, 1000)
    my.damage_crush_dice(self, "2d6")
    my.damage_drown_chance_d1000(self, 0, 1000)
    my.damage_drown_dice(self, "2d6")
    my.damage_received_doubled_from_fire(self, True)
    my.environ_avoids_fire(self, 100)
    my.gfx_ascii_fade_with_dist(self, True)
    my.gfx_ascii_shown_as_gray_in_shadow(self, True)
    my.gfx_ascii_shown_in_bg(self, True)
    my.gfx_ascii_shown(self, True)
    my.gfx_oversized_and_on_floor(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gfx_pixelart_show_outlined(self, True)
    my.gfx_pixelart_submergable(self, True)
    my.gfx_pixelart_wobbles_when_hit(self, True)
    my.is_able_to_burn(self, True)
    my.is_able_to_fall(self, True)
    my.is_always_hit(self, True)
    my.is_attackable_by_monst(self, True)
    my.is_attackable_by_player(self, True)
    my.is_barrel(self, True)
    my.is_biome_dungeon(self, True)
    my.is_cursor_can_hover_over(self, True)
    my.is_cursor_path_blocker(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_heavy(self, True)
    my.is_hittable(self, True)
    my.is_immune_to_cold(self, True)
    my.is_immune_to_draining(self, True)
    my.is_immune_to_necrosis(self, True)
    my.is_immune_to_poison(self, True)
    my.is_interesting(self, True)  # so it can be shoved
    my.is_light_blocker_for_monst(self, True)  # to give cover to the player
    my.is_loggable(self, True)
    my.is_obs_for_shoving(self, True)
    my.is_shovable(self, True)
    my.is_very_combustible(self, True)
    my.normal_placement_rules(self, True)
    my.on_death_do(self, "me.on_death()")
    my.on_fall_do(self, "me.on_fall()")
    my.on_you_are_on_fire_do(self, "me.on_fire()")
    my.text_a_or_an(self, "a")
    my.text_short_description(self, "A barrel of oil. Why? Don't ask.")
    my.thing_size(self, my.THING_SIZE_LARGE)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_BARREL)
    # end sort marker

    my.tile(self,
            ascii_fg_char="B", ascii_bg_col_name="", ascii_fg_col_name="brown",
            tile=name)

    my.tp_update(self)


def init():
    tp_init(name="barrel", text_long_name="barrel")


init()
