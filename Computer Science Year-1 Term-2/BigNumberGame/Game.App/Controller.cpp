#include "Controller.h"
#include "..\Project.StringManipulation\MStringManip.h"
#include "..\Game.IOS\FileSystem.h"

User* Controller::currentUser = nullptr;
bool Controller::returnToTitleScreen = false;
bool Controller::newHighscore = false;

mstring Controller::getLeaderboardInfo(bool includeDeleted, bool getDeletedOnly)
{
    //Get all the users
    size_t usersCount = 0;
    User* users = FileSystem::getAllUsers(usersCount);

    //Filter out the users which are excluded from the leaderboards
    size_t includedUsersCount = 0;
    User* includedUsers = new User[usersCount];
    for (size_t i = 0; i < usersCount; i++)
    {
        if (users[i].includeHighscore) includedUsers[includedUsersCount++] = users[i];
    }

    //Resize array
    User* copyOfIncludedUsers = new User[includedUsersCount];
    for (size_t i = 0; i < includedUsersCount; i++)
    {
        copyOfIncludedUsers[i] = includedUsers[i];
    }

    //Dealloc dynamic memory
    delete[] users;
    delete[] includedUsers;

    users = copyOfIncludedUsers;
    usersCount = includedUsersCount;

    //Filter out the users which are not deleted
    if(getDeletedOnly)
    {
        size_t deletedUsersIndex = 0;
        User* deletedUsers = new User[usersCount];
        for (size_t i = 0; i < usersCount; i++)
        {
            if (users[i].isDeleted) deletedUsers[deletedUsersIndex++] = users[i];
        }

        //Resize array
        User* copyOfDeletedUsers = new User[deletedUsersIndex];
        for (size_t i = 0; i < deletedUsersIndex; i++)
        {
            copyOfDeletedUsers[i] = deletedUsers[i];
        }
        //Dealloc dynamic memory
        delete[] deletedUsers;
        delete[] users;

        users = copyOfDeletedUsers;
        usersCount = deletedUsersIndex;
    }
    //Filter out the users which are deleted
    else if (!includeDeleted)
    {
        size_t nonDeletedUsersIndex = 0;
        User* nonDeletedUsers = new User[usersCount];
        for (size_t i = 0; i < usersCount; i++)
        {
            if (!users[i].isDeleted) nonDeletedUsers[nonDeletedUsersIndex++] = users[i];
        }

        //Resize array
        User* copyOfNonDeletedUsers = new User[nonDeletedUsersIndex];
        for (size_t i = 0; i < nonDeletedUsersIndex; i++)
        {
            copyOfNonDeletedUsers[i] = nonDeletedUsers[i];
        }
        //Dealloc dynamic memory
        delete[] nonDeletedUsers;
        delete[] users;

        users = copyOfNonDeletedUsers;
        usersCount = nonDeletedUsersIndex;
    }

    //Sort the array of included users
    User* sortedUsers = new User[usersCount];
    size_t sortedUsersIndex = 0;

    while (sortedUsersIndex < usersCount)
    {
        User largestUser = users[0];
        size_t largestUserIndex = 0;
        for (size_t i = 1; i < usersCount - sortedUsersIndex; i++)
        {
            if (users[i].highscore > largestUser.highscore)
            {
                largestUser = users[i];
                largestUserIndex = i;
            }
        }
        //Swap the current largest user to last place
        User copyOfLastUser = users[usersCount - sortedUsersIndex - 1];
        users[usersCount - sortedUsersIndex - 1] = largestUser;
        users[largestUserIndex] = copyOfLastUser;

        sortedUsers[sortedUsersIndex++] = largestUser;
    }

    //Dealloc dynamic memory
    delete[] users;

    mstring leaderboardInfo;

    for (size_t i = 0; i < sortedUsersIndex; i++)
    {
        mstring userInfo = MStringManip::replaceAll(GlobalConstants::LEADERBOARD_USER_TEXT, GlobalConstants::USERNAME_PLACEHOLDER, sortedUsers[i].username);
        userInfo = MStringManip::parseToString(i + 1) + MStringManip::replaceAll(userInfo, GlobalConstants::HIGHSCORE_PLACEHOLDER, MStringManip::parseToString(sortedUsers[i].highscore));
        leaderboardInfo += userInfo + "\n";
    }

    //Dealloc dynamic memory
    delete[] sortedUsers;

    return leaderboardInfo;
}
