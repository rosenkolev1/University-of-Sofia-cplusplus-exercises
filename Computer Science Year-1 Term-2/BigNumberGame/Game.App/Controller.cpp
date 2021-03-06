#include "Controller.h"
#include "..\Game.IOS\UserTable.h"
#include "..\Project.StringManipulation\MStringManip.h"
#include "..\Game.IOS\Seeder.h"

User* Controller::currentUser = nullptr;
bool Controller::returnToTitleScreen = false;

mstring* Controller::getLeaderboardRows(bool includeDeleted, bool getDeletedOnly, bool getIncluded, size_t& rowsCount, mstring dataDelim)
{
    //Get all the users
    size_t usersCount = 0;
    User* users = nullptr;

    //Filter out the users which are not deleted
    if (getDeletedOnly)
    {        
        users = UserTable::getDeletedUsers(usersCount);
    }
    //Filter out the users which are deleted
    else
    {     
        users = UserTable::getAllUsers(usersCount, includeDeleted);
    }

    //Filter out the users which are excluded or included from the leaderboards
    size_t includedUsersCount = 0;
    User* includedUsers = new User[usersCount];
    for (size_t i = 0; i < usersCount; i++)
    {
        if (users[i].includeHighscore == getIncluded) includedUsers[includedUsersCount++] = users[i];
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

    //Set the count of the rows
    rowsCount = sortedUsersIndex;

    mstring* leaderboardRowsInfo = new mstring[rowsCount];

    for (size_t i = 0; i < rowsCount; i++)
    {
		//Number. Username. Highscore
		leaderboardRowsInfo[i] = MStringManip::parseToString(i + 1) + dataDelim + sortedUsers[i].username + dataDelim + sortedUsers[i].getHighscoreString();
    }

    //Dealloc dynamic memory
    delete[] sortedUsers;

    return leaderboardRowsInfo;
}

void Controller::initialize()
{
    srand(time(NULL));

    //Seed database
    //Seeder::seedDatabase(false);
    Seeder::seedDatabase(true);
}

