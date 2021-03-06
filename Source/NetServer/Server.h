#pragma once

#include <Urho3D/Network/Network.h>
#include <Urho3D/Network/NetworkEvents.h>

namespace Net
{
/**
 * Custom Parameters for Client Identity Event 
 */
URHO3D_PARAM( P_SERVERTYPE, ServerType );
URHO3D_PARAM( P_SERVERID, ServerID );

enum class ServerType
{
    Undefined,
    Master,
    Login,
    Game,
    World,
};

struct NetConnection
{
    int id_; //!< Connection ID
    unsigned int address_;   //!< Server Address
    String name_;    //!< Server Name
    String ip_;  //!< Server IP
    int port_;   //!< Server Port
    ServerType serverType_;  //!< Server Type
    int maxConnections_; //!< Max Connections
    Connection* connection_;   //!< Connection Pointer
};

const char* ServerTypeToString( const ServerType& serverType );
ServerType ServerTypeFromString( const String& str );

class Server : public Object
{
    URHO3D_OBJECT( Server, Object );
public:
    //! Constructor.
    Server( Context* context );

    //! Deconstructor.
    ~Server();

    //! Initialize Net Server.
    bool Init();

    //! UnInitialize.
    void UnInit();

    //! Start Server.
    bool Start( NetConnection* netConnection );

    //! Load Server Configuration.
    bool Load( NetConnection* netConnection );

    //! Connect with all Servers loaded.
    void ConnectAll();

    //! Get a specific connection by Server Type.
    NetConnection* GetConnection( ServerType serverType, int index = 0 ) const;

    //! Send
    void Send( ServerType serverType, int msgID, bool reliable, bool inOrder, const VectorBuffer& msg );

    //! Handle Update.
    void HandleUpdate( StringHash eventType, VariantMap& eventData );

    //! Handle Client Connection Identity.
    void HandleClientIdentity( StringHash eventType, VariantMap& eventData );

    //! Handle Client Disconnection.
    void HandleClientDisconnect( StringHash eventType, VariantMap& eventData );

    //! Handle Server Connection Status.
    void HandleConnectionStatus( StringHash eventType, VariantMap& eventData );
private:
    //! Connect with a specific Server.
    bool Connect( NetConnection* netConnection );
private:
    NetConnection* currentNetConnection_;    //!< Current net Connection.
    Vector<NetConnection*> netConnections_;  //!< Net Connections.
    Vector<NetConnection*> reconnectNetConnections_;    //!< Net Connections to reconnect.
};
}