//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_ptrcheck.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

std::string Thing::text_a_or_an(void)
{
  TRACE_NO_INDENT();
  auto tpp = tp();
  verify(MTYPE_THING, this);
  verify(MTYPE_TP, tpp);
  if (unlikely(! tpp)) {
    return ("<no name>");
  }

  std::string out = "";

  if (is_player() || is_monst()) {
    if (is_dead) {
      out += "a dead ";
    } else if (is_dying) {
      out += "a dying ";
    } else if (is_frozen) {
      out += "a frozen ";
    } else if (is_burnt) {
      out += "a burnt ";
    }
  }

  if (out == "") {
    auto prefix = tpp->text_a_or_an();
    if (prefix == "") {
      out = tpp->text_long_name();
    } else {
      out = prefix + " " + tpp->text_long_name();
    }
  } else {
    out += tpp->text_long_name();
  }

  return (out);
}

std::string Thing::text_the(bool include_owner)
{
  TRACE_NO_INDENT();
  auto tpp = tp();
  verify(MTYPE_THING, this);
  verify(MTYPE_TP, tpp);
  if (unlikely(! tpp)) {
    return ("<no name>");
  }

  std::string out = "the ";

  //
  // "the goblin's short sword" for example
  //
  auto t_o = top_owner();
  if (include_owner) {
    if (t_o && ! t_o->is_player()) {
      out += t_o->text_long_name();
      out += "'s ";
    }
  }

  if (is_player() || is_monst()) {
    if (is_dead) {
      if (is_undead()) {
        out += "extra dead ";
      } else {
        out += "dead ";
      }
    } else if (is_dying) {
      out += "dying ";
    } else if (is_frozen) {
      out += "frozen ";
    } else if (is_burnt) {
      out += "burnt ";
    }
  }

  out += tpp->text_long_name();

  return (out);
}

std::string Thing::text_the_no_dying(bool include_owner)
{
  TRACE_NO_INDENT();
  auto tpp = tp();
  verify(MTYPE_THING, this);
  verify(MTYPE_TP, tpp);
  if (unlikely(! tpp)) {
    return ("<no name>");
  }

  std::string out = "the ";

  //
  // "the goblin's short sword" for example
  //
  auto t_o = top_owner();
  if (include_owner) {
    if (t_o && ! t_o->is_player()) {
      out += t_o->text_long_name();
      out += "'s ";
    }
  }

  out += tpp->text_long_name();

  return (out);
}

std::string Thing::text_The(void)
{
  TRACE_NO_INDENT();
  auto out = text_the();
  out[ 0 ] = toupper(out[ 0 ]);
  return (out);
}

std::string Thing::text_The_no_dying(void)
{
  TRACE_NO_INDENT();
  auto out = text_the_no_dying();
  out[ 0 ] = toupper(out[ 0 ]);
  return (out);
}

std::string Thing::text_short_a_or_an(void)
{
  TRACE_NO_INDENT();
  auto tpp = tp();
  verify(MTYPE_THING, this);
  verify(MTYPE_TP, tpp);
  if (unlikely(! tpp)) {
    return ("<no name>");
  }

  std::string out = "";

  if (is_player() || is_monst()) {
    if (is_dead) {
      out += "a dead ";
    } else if (is_dying) {
      out += "a dying ";
    } else if (is_frozen) {
      out += "a frozen ";
    } else if (is_burnt) {
      out += "a burnt ";
    }
  }

  if (out == "") {
    auto prefix = tpp->text_a_or_an();
    if (prefix == "") {
      out = tpp->text_short_name();
    } else {
      out = prefix + " " + tpp->text_short_name();
    }
  } else {
    out += tpp->text_short_name();
  }

  return (out);
}

std::string Thing::text_short_the(void)
{
  TRACE_NO_INDENT();
  auto tpp = tp();
  verify(MTYPE_THING, this);
  verify(MTYPE_TP, tpp);
  if (unlikely(! tpp)) {
    return ("<no name>");
  }

  std::string out = "the ";

  if (is_dead) {
    if (is_undead()) {
      out += "extra dead ";
    } else if (is_dying) {
      out += "dying ";
    } else {
      out += "dead ";
    }
  }

  out += tpp->text_short_name();

  return (out);
}

std::string Thing::text_short_The(void)
{
  TRACE_NO_INDENT();
  auto out = text_short_the();
  out[ 0 ] = toupper(out[ 0 ]);
  return (out);
}

std::string Thing::text_A_or_An(void)
{
  TRACE_NO_INDENT();
  auto out = text_short_a_or_an();
  out[ 0 ] = toupper(out[ 0 ]);
  return (out);
}

//
// foo bar -> Foo Bar
//
std::string Thing::text_short_capitalised(void)
{
  TRACE_NO_INDENT();
  std::string out = text_short_name();

  char *b          = (char *) out.c_str();
  char *e          = b + out.size();
  char *c          = b;
  bool  word_start = true;
  while (c < e) {
    if (word_start) {
      if (islower(*c)) {
        *c = toupper(*c);
      }
      word_start = false;
    } else if (*c == ' ') {
      word_start = true;
    }

    c++;
  }

  return out;
}

std::string Thing::text_long_capitalised(void)
{
  TRACE_NO_INDENT();
  std::string out = text_long_name();

  char *b          = (char *) out.c_str();
  char *e          = b + out.size();
  char *c          = b;
  bool  word_start = true;
  while (c < e) {
    if (word_start) {
      if (islower(*c)) {
        *c = toupper(*c);
      }
      word_start = false;
    } else if (*c == ' ') {
      word_start = true;
    }

    c++;
  }

  return out;
}

std::string Thing::text_short_and_state_capitalised(void)
{
  TRACE_NO_INDENT();
  std::string out;

  if (is_player() || is_monst()) {
    if (is_dead) {
      if (is_undead()) {
        out += "extra dead ";
      } else {
        out += "dead ";
      }
    } else if (is_dying) {
      out += "dying ";
    } else if (is_frozen) {
      out += "frozen ";
    } else if (is_burnt) {
      out += "burnt ";
    }
  }

  out += text_short_name();

  char *b          = (char *) out.c_str();
  char *e          = b + out.size();
  char *c          = b;
  bool  word_start = true;
  while (c < e) {
    if (word_start) {
      if (islower(*c)) {
        *c = toupper(*c);
      }
      word_start = false;
    } else if (*c == ' ') {
      word_start = true;
    }

    c++;
  }

  if (enchant_get()) {
    out += " +" + std::to_string(enchant_get());
  }

  return out;
}

std::string Thing::text_long_and_state_capitalised(void)
{
  TRACE_NO_INDENT();
  std::string out;

  if (is_player() || is_monst()) {
    if (is_dead) {
      if (is_undead()) {
        out += "extra dead ";
      } else {
        out += "dead ";
      }
    } else if (is_dying) {
      out += "dying ";
    }
  }

  out += text_long_name();

  char *b          = (char *) out.c_str();
  char *e          = b + out.size();
  char *c          = b;
  bool  word_start = true;
  while (c < e) {
    if (word_start) {
      if (islower(*c)) {
        *c = toupper(*c);
      }
      word_start = false;
    } else if (*c == ' ') {
      word_start = true;
    }

    c++;
  }

  if (enchant_get()) {
    out += " +" + std::to_string(enchant_get());
  }

  return out;
}

void Thing::show_botcon_description(void)
{
  TRACE_NO_INDENT();
  auto text = text_short_description();

  bool skip_showing_keys_to_use = true;
  switch (game->state) {
    case Game::STATE_CHOOSING_LEVEL: return;
    case Game::STATE_NORMAL: skip_showing_keys_to_use = false; break;
    case Game::STATE_OPTIONS_FOR_ITEM_MENU: skip_showing_keys_to_use = true; break;
    case Game::STATE_INVENTORY: // Currently managing inventory
      skip_showing_keys_to_use = false;
      break;
    case Game::STATE_COLLECTING_ITEMS: // Collecting en masse from the level
      skip_showing_keys_to_use = true;
      break;
    case Game::STATE_ENCHANTING_ITEMS: skip_showing_keys_to_use = true; break;
    case Game::STATE_CHOOSING_TARGET: // Looking to somewhere to throw at
      skip_showing_keys_to_use = true;
      break;
    case Game::STATE_LOAD_MENU: skip_showing_keys_to_use = true; break;
    case Game::STATE_SAVE_MENU: skip_showing_keys_to_use = true; break;
    case Game::STATE_QUIT_MENU: skip_showing_keys_to_use = true; break;
    case Game::STATE_KEYBOARD_MENU: skip_showing_keys_to_use = true; break;
    default: ERR("Unhandled game state"); break;
  }

  //
  // Want to show that you can drop a bag if you select it.
  //
  if (immediate_owner()) {
    if (is_droppable()) {

      text += " %%fg=orange$" + ::to_string(game->config.key_drop) + "%%fg=reset$ to drop.";
    }
  }

  //
  // Unless a bag.
  //
  if (skip_showing_keys_to_use) {
    if (text.empty()) {
      return;
    }
    BOTCON("%s", text.c_str());
    return;
  }

  if (is_weapon()) {
    text += " Damage %%fg=red$" + tp()->damage_melee_dice_str() + "%%fg=reset$.";
  }

  if (is_poisonous_danger_level()) {
    text += " Poisons. ";
  }

  if (is_necrotic_danger_level()) {
    text += " Necrotic. ";
  }

  if (immediate_owner()) {
    if (is_usable()) {
      if (is_food()) {
        text += " %%fg=green$" + ::to_string(game->config.key_eat) + "%%fg=reset$ to eat.";
      } else if (is_potion()) {
        text += " %%fg=green$" + ::to_string(game->config.key_use) + "%%fg=reset$ to drink.";
      } else if (is_wand_or_staff()) {
        text += " %%fg=green$" + ::to_string(game->config.key_use) + "%%fg=reset$ to use.";
      } else if (is_ring()) {
        text += " %%fg=green$" + ::to_string(game->config.key_use) + "%%fg=reset$ to wear.";
      } else {
        text += " %%fg=cyan$" + ::to_string(game->config.key_use) + "%%fg=reset$ to use.";
      }
    }

    if (is_throwable() && ! is_auto_throw()) {
      text += " %%fg=purple$" + ::to_string(game->config.key_throw) + "%%fg=reset$ to throw.";
    }

    if (is_bag_item_container()) {
      text += " Use mouse to drag items.";
    }
  }

  if (is_on_fire()) {
    if (is_alive_monst() || is_player()) {
      text += " %%fg=red$Is on fire!";
    }
  }

  if (! is_hidden) {
    if (is_collectable() && level->player) {
      if (curr_at == level->player->curr_at) {
        auto k = ::to_string(game->config.key_wait_or_collect);
        if (k == ".") {
          text += " Press %%fg=yellow$" + k + "%%fg=reset$ or click to collect.";
        } else {
          text += " %%fg=yellow$" + k + "%%fg=reset$ or click to collect.";
        }
      }
    }
  }

  if (text.size()) {
    if ((text[ text.size() - 1 ] == '.') || (text[ text.size() - 1 ] == '!')) {
      BOTCON("%s", text.c_str());
    } else {
      BOTCON("%s.", text.c_str());
    }
  }
}
