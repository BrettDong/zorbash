//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_level.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_python.hpp"
#include "my_string.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

int Thing::on_owner_receive_dmg_stat_str(Thingp owner, Thingp hitter, Thingp real_hitter, int damage)
{
  TRACE_NO_INDENT();
  verify(MTYPE_THING, owner);
  if (! owner) {
    err("Cannot call owner_damage_stat_str null thing");
    return damage;
  }

  verify(MTYPE_THING, hitter);
  if (! hitter) {
    err("Cannot call owner_damage_stat_str null thing");
    return damage;
  }

  auto on_owner_receive_dmg_stat_str = on_owner_receive_dmg_stat_str_do();
  if (std::empty(on_owner_receive_dmg_stat_str)) {
    return damage;
  }

  auto t = split_tokens(on_owner_receive_dmg_stat_str, '.');
  if (t.size() == 2) {
    auto        mod   = t[ 0 ];
    auto        fn    = t[ 1 ];
    std::size_t found = fn.find("()");
    if (found != std::string::npos) {
      fn = fn.replace(found, 2, "");
    }

    if (mod == "me") {
      mod = name();
    }

    dbg("Call %s.%s(%s, %s, %s, %d)", mod.c_str(), fn.c_str(), to_short_string().c_str(),
        owner->to_short_string().c_str(), hitter->to_short_string().c_str(), damage);

    return py_call_int_fn(mod.c_str(), fn.c_str(), id.id, owner->id.id, hitter->id.id, real_hitter->id.id,
                          (unsigned int) curr_at.x, (unsigned int) curr_at.y, (unsigned int) damage);
  }

  ERR("Bad on_owner_receive_dmg_stat_str call [%s] expected mod:function, got %d elems",
      on_owner_receive_dmg_stat_str.c_str(), (int) on_owner_receive_dmg_stat_str.size());

  return damage;
}

int Thing::on_receiving_dmg_stat_str(Thingp hitter, Thingp real_hitter, int damage)
{
  TRACE_NO_INDENT();
  verify(MTYPE_THING, hitter);

  if (! hitter) {
    err("Cannot call damage_stat_str null thing");
    return damage;
  }

  auto on_receiving_dmg_stat_str = on_receiving_dmg_stat_str_do();
  if (std::empty(on_receiving_dmg_stat_str)) {
    return damage;
  }

  auto t = split_tokens(on_receiving_dmg_stat_str, '.');
  if (t.size() == 2) {
    auto        mod   = t[ 0 ];
    auto        fn    = t[ 1 ];
    std::size_t found = fn.find("()");
    if (found != std::string::npos) {
      fn = fn.replace(found, 2, "");
    }

    if (mod == "me") {
      mod = name();
    }

    dbg("Call %s.%s(%s, %s, %d)", mod.c_str(), fn.c_str(), to_short_string().c_str(),
        hitter->to_short_string().c_str(), damage);

    return py_call_int_fn(mod.c_str(), fn.c_str(), id.id, hitter->id.id, (unsigned int) curr_at.x,
                          (unsigned int) curr_at.y, (unsigned int) damage);
  }

  ERR("Bad on_receiving_dmg_stat_str call [%s] expected mod:function, got %d elems",
      on_receiving_dmg_stat_str.c_str(), (int) on_receiving_dmg_stat_str.size());

  return damage;
}

int Thing::total_damage_for_on_receiving_dmg_stat_str(Thingp hitter, Thingp real_hitter, int damage)
{
  TRACE_NO_INDENT();
  if (! maybe_itemsp()) {
    return damage;
  }

  FOR_ALL_BUFFS(item)
  {
    auto iter = level->thing_find(item.id);
    if (iter) {
      damage = iter->on_owner_receive_dmg_stat_str(this, hitter, real_hitter, damage);
    }
  }

  FOR_ALL_DEBUFFS(item)
  {
    auto iter = level->thing_find(item.id);
    if (iter) {
      damage = iter->on_owner_receive_dmg_stat_str(this, hitter, real_hitter, damage);
    }
  }

  FOR_ALL_EQUIP(e)
  {
    auto iter = equip_get(e);
    if (iter) {
      damage = iter->on_owner_receive_dmg_stat_str(this, hitter, real_hitter, damage);
    }
  }

  damage = on_receiving_dmg_stat_str(hitter, real_hitter, damage);

  return damage;
}

int Thing::on_attacking_dmg_stat_str(Thingp victim, int damage)
{
  TRACE_NO_INDENT();
  verify(MTYPE_THING, victim);
  if (! victim) {
    err("Cannot call damage_stat_str null thing");
    return damage;
  }

  auto on_attacking_dmg_stat_str = on_attacking_dmg_stat_str_do();
  if (std::empty(on_attacking_dmg_stat_str)) {
    return damage;
  }

  auto t = split_tokens(on_attacking_dmg_stat_str, '.');
  if (t.size() == 2) {
    auto        mod   = t[ 0 ];
    auto        fn    = t[ 1 ];
    std::size_t found = fn.find("()");
    if (found != std::string::npos) {
      fn = fn.replace(found, 2, "");
    }

    if (mod == "me") {
      mod = name();
    }

    dbg("Call %s.%s(%s, %s, %d)", mod.c_str(), fn.c_str(), to_short_string().c_str(),
        victim->to_short_string().c_str(), damage);

    return py_call_int_fn(mod.c_str(), fn.c_str(), id.id, victim->id.id, (unsigned int) curr_at.x,
                          (unsigned int) curr_at.y, (unsigned int) damage);
  }

  ERR("Bad on_attacking_dmg_stat_str call [%s] expected mod:function, got %d elems",
      on_attacking_dmg_stat_str.c_str(), (int) on_attacking_dmg_stat_str.size());

  return damage;
}

int Thing::on_owner_attack_dmg_stat_str(Thingp owner, Thingp victim, int damage)
{
  TRACE_NO_INDENT();
  verify(MTYPE_THING, owner);
  if (! owner) {
    err("Cannot call owner_damage_stat_str null thing");
    return damage;
  }

  verify(MTYPE_THING, victim);
  if (! victim) {
    err("Cannot call owner_damage_stat_str null thing");
    return damage;
  }

  auto on_owner_attack_dmg_stat_str = on_owner_attack_dmg_stat_str_do();
  if (std::empty(on_owner_attack_dmg_stat_str)) {
    return damage;
  }

  auto t = split_tokens(on_owner_attack_dmg_stat_str, '.');
  if (t.size() == 2) {
    auto        mod   = t[ 0 ];
    auto        fn    = t[ 1 ];
    std::size_t found = fn.find("()");
    if (found != std::string::npos) {
      fn = fn.replace(found, 2, "");
    }

    if (mod == "me") {
      mod = name();
    }

    dbg("Call %s.%s(%s, %s, %s, %d)", mod.c_str(), fn.c_str(), to_short_string().c_str(),
        owner->to_short_string().c_str(), victim->to_short_string().c_str(), damage);

    return py_call_int_fn(mod.c_str(), fn.c_str(), id.id, owner->id.id, victim->id.id, (unsigned int) curr_at.x,
                          (unsigned int) curr_at.y, (unsigned int) damage);
  }

  ERR("Bad on_owner_attack_dmg_stat_str call [%s] expected mod:function, got %d elems",
      on_owner_attack_dmg_stat_str.c_str(), (int) on_owner_attack_dmg_stat_str.size());

  return damage;
}

int Thing::total_damage_for_on_attacking_dmg_stat_str(Thingp victim, int damage)
{
  TRACE_NO_INDENT();
  if (! maybe_itemsp()) {
    return damage;
  }

  FOR_ALL_BUFFS(item)
  {
    auto iter = level->thing_find(item.id);
    if (iter) {
      damage = iter->on_owner_attack_dmg_stat_str(this, victim, damage);
    }
  }

  FOR_ALL_DEBUFFS(item)
  {
    auto iter = level->thing_find(item.id);
    if (iter) {
      damage = iter->on_owner_attack_dmg_stat_str(this, victim, damage);
    }
  }

  FOR_ALL_EQUIP(e)
  {
    auto iter = equip_get(e);
    if (iter) {
      damage = iter->on_owner_attack_dmg_stat_str(this, victim, damage);
    }
  }

  damage = on_attacking_dmg_stat_str(victim, damage);

  return damage;
}

const std::string &Thing::on_receiving_dmg_stat_str_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_receiving_dmg_stat_str_do());
}

const std::string &Thing::on_attacking_dmg_stat_str_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_attacking_dmg_stat_str_do());
}

const std::string &Thing::on_owner_attack_dmg_stat_str_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_owner_attack_dmg_stat_str_do());
}

const std::string &Thing::on_owner_receive_dmg_stat_str_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_owner_receive_dmg_stat_str_do());
}
