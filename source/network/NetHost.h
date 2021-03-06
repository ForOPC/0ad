#ifndef NETHOST_H
#define NETHOST_H

#include "../ps/CStr.h"

#include <map>

/**
 * @file
 * Various declarations shared by networking code.
 */

typedef struct _ENetPeer ENetPeer;
typedef struct _ENetPacket ENetPacket;
typedef struct _ENetHost ENetHost;
class CNetMessage;

struct PlayerAssignment
{
	/**
	 * Whether the player is currently connected and active.
	 * (We retain information on disconnected players to support rejoining,
	 * but don't transmit these to other clients.)
	 */
	bool m_Enabled;

	/// Player name
	CStrW m_Name;

	/// The player that the given host controls, or -1 if none (observer)
	i32 m_PlayerID;

	/// Status - Ready or not: 0 for not ready, 1 for ready, 2 to stay ready
	u8 m_Status;
};

typedef std::map<CStr, PlayerAssignment> PlayerAssignmentMap; // map from GUID -> assignment

/**
 * Reasons sent by server to clients in disconnection messages.
 * Must be kept in sync with binaries/data/mods/public/gui/common/network.js
 */
enum NetDisconnectReason
{
	NDR_UNKNOWN = 0,
	NDR_SERVER_SHUTDOWN,
	NDR_INCORRECT_PROTOCOL_VERSION,
	NDR_SERVER_LOADING,
	NDR_SERVER_ALREADY_IN_GAME,
	NDR_KICKED,
	NDR_BANNED,
	NDR_PLAYERNAME_IN_USE,
	NDR_SERVER_FULL,
	NDR_LOBBY_AUTH_FAILED
};

class CNetHost
{
public:
	static const int DEFAULT_CHANNEL = 0;

	/**
	 * Transmit a message to the given peer.
	 * @param message message to send
	 * @param peer peer to send to
	 * @param peerName name of peer for debug logs
	 * @return true on success, false on failure
	 */
	static bool SendMessage(const CNetMessage* message, ENetPeer* peer, const char* peerName);

	/**
	 * Construct an ENet packet by serialising the given message.
	 * @return NULL on failure
	 */
	static ENetPacket* CreatePacket(const CNetMessage* message);

	/**
	 * Initialize ENet.
	 * This must be called before any other networking code.
	 */
	static void Initialize();

	/**
	 * Deinitialize ENet.
	 */
	static void Deinitialize();
};

#endif	// NETHOST_H
