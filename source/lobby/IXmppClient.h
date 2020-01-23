#ifndef IXMPPCLIENT_H
#define IXMPPCLIENT_H

#include "../scriptinterface/ScriptTypes.h"

class ScriptInterface;
namespace StunClient {
	struct StunEndpoint;
}

class IXmppClient
{
public:
	static IXmppClient* create(const std::string& sUsername, const std::string& sPassword, const std::string& sRoom, const std::string& sNick, const int historyRequestSize = 0, bool regOpt = false);
	virtual ~IXmppClient() {}

	virtual void connect() = 0;
	virtual void disconnect() = 0;
	virtual bool isConnected() = 0;
	virtual void recv() = 0;
	virtual void SendIqGetBoardList() = 0;
	virtual void SendIqGetProfile(const std::string& player) = 0;
	virtual void SendIqGameReport(const ScriptInterface& scriptInterface, JS::HandleValue data) = 0;
	virtual void SendIqRegisterGame(const ScriptInterface& scriptInterface, JS::HandleValue data) = 0;
	virtual void SendIqUnregisterGame() = 0;
	virtual void SendIqChangeStateGame(const std::string& nbp, const std::string& players) = 0;
	virtual void SendIqLobbyAuth(const std::string& to, const std::string& token) = 0;
	virtual void SetNick(const std::string& nick) = 0;
	virtual void GetNick(std::string& nick) = 0;
	virtual void kick(const std::string& nick, const std::string& reason) = 0;
	virtual void ban(const std::string& nick, const std::string& reason) = 0;
	virtual void SetPresence(const std::string& presence) = 0;
	virtual void GetPresence(const std::string& nickname, std::string& presence) = 0;
	virtual void GetRole(const std::string& nickname, std::string& role) = 0;
	virtual void GetSubject(std::string& subject) = 0;
	virtual void GUIGetPlayerList(const ScriptInterface& scriptInterface, JS::MutableHandleValue ret) = 0;
	virtual void ClearPresenceUpdates() = 0;
	virtual void GUIGetGameList(const ScriptInterface& scriptInterface, JS::MutableHandleValue ret) = 0;
	virtual void GUIGetBoardList(const ScriptInterface& scriptInterface, JS::MutableHandleValue ret) = 0;
	virtual void GUIGetProfile(const ScriptInterface& scriptInterface, JS::MutableHandleValue ret) = 0;
	virtual JS::Value GuiPollNewMessage(const ScriptInterface& scriptInterface) = 0;
	virtual JS::Value GuiPollHistoricMessages(const ScriptInterface& scriptInterface) = 0;
	virtual void SendMUCMessage(const std::string& message) = 0;
	virtual void SendStunEndpointToHost(StunClient::StunEndpoint* stunEndpoint, const std::string& hostJID) = 0;
};

extern IXmppClient *g_XmppClient;
extern bool g_rankedGame;

#endif // XMPPCLIENT_H
