#include "coin/CoinCounter.h"
#include <String.hpp>
#include "coin/CoinCollected.h"
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
    auto coins_node = get_node("../../Coins");
    auto children_count = coins_node->get_child_count();
    for(int64_t i = 0; i < children_count;i++)
    {
        auto child = coins_node->get_child(i);
        child->get_node("StateMachine/CoinCollected")->connect("coin_collected",this,"_on_coin_collected");
    }
   

}
