#pragma once

class UserManager : public ManagerImpl
{
    URHO3D_OBJECT( UserManager, ManagerImpl );
public:
    //! Constructor.
    UserManager( Context* context );

    //! Deconstructor.
    ~UserManager();

    //! Get User by Connection.
    Core::User* GetUser( Connection* connection ){ return users[connection]; }

    //! Add an user for the list.
    SharedPtr<Core::User> AddUser( Connection* connection );

    //! Del user from the list.
    void DelUser( Connection* connection );
private:
    HashMap<Connection*, SharedPtr<Core::User>> users;
};