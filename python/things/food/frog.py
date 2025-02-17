import my
import tp


def tp_init(name, text_long_name, text_short_name):
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    my.collision_hit_priority(self, 6)
    my.environ_avoids_fire(self, 100)
    my.gfx_ascii_fade_with_dist(self, True)
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_bounce_always(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gfx_pixelart_submergable(self, True)
    my.is_able_to_burn(self, True)
    my.is_able_to_fall(self, True)
    my.is_able_to_freeze(self, True)
    my.is_able_to_melt(self, True)
    my.is_bag_item(self, True)
    my.is_biome_dungeon(self, True)
    my.is_collectable(self, True)
    my.is_crushable(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_food(self, True)
    my.is_interesting(self, True)
    my.is_item(self, True)
    my.is_loggable(self, True)
    my.is_organic(self, True)
    my.is_temperature_sensitive(self, True)
    my.is_throwable(self, True)
    my.is_usable(self, True)
    my.item_height(self, 3)
    my.item_width(self, 3)
    my.melting_chance_d1000(self, 500)
    my.noise_on_dropping(self, 1)
    my.normal_placement_rules(self, True)
    my.nutrition_dice(self, "50+1d100")
    my.rarity(self, my.RARITY_UNCOMMON)
    my.text_a_or_an(self, "a")
    my.text_long_description(self, "Chocolate frogs. The food of Gods. May seem out of place in a dungeon and you'd be correct. It is rumored a helpful god left them here for brave adventurers to assist them on their path. Often found in a purple wrapper. Almost looks too good to eat.")
    my.text_short_description(self, "The food of the Gods: a chocolate frog.")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_ITEM)
    # end sort marker

    my.tile(self,
            ascii_fg_char=";", ascii_bg_col_name="", ascii_fg_col_name="brown",
            tile=name, is_hp_100_percent=True)
    my.tp_update(self)


def init():
    tp_init(name="food_frog", text_long_name="chocolate frog", text_short_name="choc frog")


init()
