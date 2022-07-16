#include "coin/CoinCounter.h"
#include <Control.hpp>

using namespace godot;


void CoinCounter::_register_methods()
{
    register_method("_state_enter", &CoinCounter::_state_enter);
    register_method("_state_exit", &CoinCounter::_state_exit);
    register_method("_on_body_entered", &CoinCounter::_on_CoinHUD_ready);
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

void CoinCounter::_state_enter()
{

}

void CoinCounter::_state_exit()
{
    
}

void CoinCounter::_on_CoinHUD_ready()
{
    get_node("Coins").text() = "hola";

}


