#ifndef INCLUDED_WORLD
#define INCLUDED_WORLD

#include "Errors.h"
#include "../scriptinterface/ScriptInterface.h"

#ifndef ERROR_GROUP_GAME_DEFINED
#define ERROR_GROUP_GAME_DEFINED
ERROR_GROUP(Game);
#endif
ERROR_SUBGROUP(Game, World);
ERROR_TYPE(Game_World, MapLoadFailed);

class CGame;
class CUnitManager;
class CTerrain;
class CStrW;
class CMapReader;

/**
 * CWorld is a general data class containing whatever is needed to accurately represent the world.
 * This includes the map, entities, influence maps, tiles, heightmap, etc.
 **/
class CWorld
{
	NONCOPYABLE(CWorld);
	/**
	 * pointer to the CGame object representing the game.
	 **/
	CGame *m_pGame;

	/**
	 * pointer to the CTerrain object representing the height map.
	 **/
	CTerrain *m_Terrain;

	/**
	 * pointer to the CUnitManager that holds all the units in the world.
	 **/
	CUnitManager *m_UnitManager;

	CMapReader* m_MapReader;

public:
	CWorld(CGame *pGame);
	~CWorld();

	/*
	Initialize the World - load the map and all objects
	*/
	void RegisterInit(const CStrW& mapFile, JSRuntime* rt, JS::HandleValue settings, int playerID);

	/*
	Initialize the World - generate and load the random map
	*/
	void RegisterInitRMS(const CStrW& scriptFile, JSRuntime* rt, JS::HandleValue settings, int playerID);

	/**
	 * Explicitly delete m_MapReader once the map has finished loading.
	 **/
	int DeleteMapReader();

	/**
	 * Get the pointer to the terrain object.
	 *
	 * @return CTerrain * the value of m_Terrain.
	 **/
	inline CTerrain *GetTerrain()
	{	return m_Terrain; }

	/**
	 * Get a reference to the unit manager object.
	 *
	 * @return CUnitManager & dereferenced m_UnitManager.
	 **/
	inline CUnitManager &GetUnitManager()
	{	return *m_UnitManager; }
};

// rationale: see definition.
class CLightEnv;
extern CLightEnv g_LightEnv;

#endif
