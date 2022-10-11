#include "Event.h"
#include "coin/CoinCounter.h"

#include <String.hpp>

void alai::CoinCounter::_register_methods()
{
    godot::register_method("_on_coin_collected", &CoinCounter::_on_coin_collected);
    godot::register_method("_ready", &CoinCounter::_ready);
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

void alai::CoinCounter::_ready()
{
    set_text("00");
    auto event = get_node<alai::Event>("/root/Event");
    event->connect("coin_collected", this, "_on_coin_collected");
}

void alai::CoinCounter::_on_coin_collected(int amount)
{
    coins = coins + amount;
    if (coins >= 100)
    {
        auto extra = coins - 100;
        coins      = extra;
    }
    godot::String coin_string = godot::String();
    if (coins <= 9)
    {
        coin_string = "0" + godot::String::num(coins);
    }
    else
    {
        coin_string = godot::String::num(coins);
    }
    set_text(coin_string);
}
