#include "coin/CoinCounter.h"
#include <String.hpp>
#include "coin/CoinCollected.h"
#include "Event.h"
using namespace godot;

void CoinCounter::_register_methods()
{
    register_method("_on_coin_collected", &CoinCounter::_on_coin_collected);
    register_method("_ready", &CoinCounter::_ready);
}

CoinCounter::CoinCounter()
{
}

CoinCounter::~CoinCounter()
{
}

void CoinCounter::_init()
{

}

void CoinCounter::_on_CoinHUD_ready()
{
    

}
void CoinCounter::_on_coin_collected(int amount)
{
    coins = coins + amount;
    set_text(String::num(coins));
}
void CoinCounter::_ready()
{
    set_text("0");
    auto event = get_node<alai::Event>("/root/Event");
    event->connect("coin_collected", this, "_on_coin_collected");
   

}
