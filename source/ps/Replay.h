#ifndef INCLUDED_REPLAY
#define INCLUDED_REPLAY

#include "CStr.h"
#include "../scriptinterface/ScriptTypes.h"

struct SimulationCommand;
class ScriptInterface;

/**
 * Replay log recorder interface.
 * Call its methods at appropriate times during the game.
 */
class IReplayLogger
{
public:
	IReplayLogger() { }
	virtual ~IReplayLogger() { }

	/**
	 * Started the game with the given game attributes.
	 */
	virtual void StartGame(JS::MutableHandleValue attribs) = 0;

	/**
	 * Run the given turn with the given collection of player commands.
	 */
	virtual void Turn(u32 n, u32 turnLength, std::vector<SimulationCommand>& commands) = 0;

	/**
	 * Optional hash of simulation state (for sync checking).
	 */
	virtual void Hash(const std::string& hash, bool quick) = 0;

	/**
	 * Remember the directory containing the commands.txt file, so that we can save additional files to it.
	 */
	virtual OsPath GetDirectory() const = 0;
};

/**
 * Implementation of IReplayLogger that simply throws away all data.
 */
class CDummyReplayLogger : public IReplayLogger
{
public:
	virtual void StartGame(JS::MutableHandleValue UNUSED(attribs)) { }
	virtual void Turn(u32 UNUSED(n), u32 UNUSED(turnLength), std::vector<SimulationCommand>& UNUSED(commands)) { }
	virtual void Hash(const std::string& UNUSED(hash), bool UNUSED(quick)) { }
	virtual OsPath GetDirectory() const { return OsPath(); }
};

/**
 * Implementation of IReplayLogger that saves data to a file in the logs directory.
 */
class CReplayLogger : public IReplayLogger
{
	NONCOPYABLE(CReplayLogger);
public:
	CReplayLogger(const ScriptInterface& scriptInterface);
	~CReplayLogger();

	virtual void StartGame(JS::MutableHandleValue attribs);
	virtual void Turn(u32 n, u32 turnLength, std::vector<SimulationCommand>& commands);
	virtual void Hash(const std::string& hash, bool quick);
	virtual OsPath GetDirectory() const;

private:
	const ScriptInterface& m_ScriptInterface;
	std::ostream* m_Stream;
	OsPath m_Directory;
};

/**
 * Replay log replayer. Runs the log with no graphics and dumps some info to stdout.
 */
class CReplayPlayer
{
public:
	CReplayPlayer();
	~CReplayPlayer();

	void Load(const OsPath& path);
	void Replay(const bool serializationtest, const int rejointestturn, const bool ooslog, const bool testHashFull, const bool testHashQuick);

private:
	std::istream* m_Stream;
	CStr ModListToString(const std::vector<std::vector<CStr>>& list) const;
	void CheckReplayMods(const ScriptInterface& scriptInterface, JS::HandleValue attribs) const;
	void TestHash(const std::string& hashType, const std::string& replayHash, const bool testHashFull, const bool testHashQuick);
};

#endif // INCLUDED_REPLAY
