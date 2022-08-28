#include "coin/CoinCounter.h"

#include "Event.h"

#include <String.hpp>

void alai::CoinCounter::_register_methods()
{
    register_method("_on_coin_collected", &CoinCounter::_on_coin_collected);
    register_method("_ready", &CoinCounter::_ready);
}

alai::CoinCounter::CoinCounter()
{
}

alai::CoinCounter::~CoinCounter()
{
}

void alai::CoinCounter::_init()
{
    coins = 0;
}

void alai::CoinCounter::_on_coin_collected(int amount)
{
    coins = coins + amount;
    set_text(godot::String::num(coins));
}

void alai::CoinCounter::_ready()
{
    set_text("0");
    auto event = get_node<alai::Event>("/root/Event");
    event->connect("coin_collected", this, "_on_coin_collected");
}
