#ifndef INCLUDED_SIMULATIONCOMMAND
#define INCLUDED_SIMULATIONCOMMAND

#include "../../scriptinterface/ScriptInterface.h"
#include "../../simulation2/helpers/Player.h"

/**
 * Simulation command, typically received over the network in multiplayer games.
 */
struct SimulationCommand
{
	SimulationCommand(player_id_t player, JSContext* cx, JS::HandleValue val)
		: player(player), data(cx, val)
	{
	}

	SimulationCommand(SimulationCommand&& cmd)
		: player(cmd.player), data(cmd.data)
	{
	}

	// std::vector::insert requires the move assignment operator at compilation time,
	// but apparently never uses it (it uses the move constructor).
	SimulationCommand& operator=(SimulationCommand&& other)
	{
		this->player = other.player;
		this->data = other.data;
		return *this;
	}

	player_id_t player;
	JS::PersistentRootedValue data;
};

#endif // INCLUDED_SIMULATIONCOMMAND
