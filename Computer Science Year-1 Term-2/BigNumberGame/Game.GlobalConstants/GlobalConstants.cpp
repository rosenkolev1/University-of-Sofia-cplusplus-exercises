#include "GlobalConstants.h"

//const char* GlobalConstants::BAD_ALLOC_EXCEPTION = "Bad allocation of memory";
//const int GlobalConstants::something = 35;

// INTERNAL CONSTANTS
const mstring GlobalConstants::BAD_ALLOC_EXCEPTION = "Bad allocation of memory";
const mstring GlobalConstants::PLACEHOLDER = "LOREM IPSUM TEXT";

//---UI AND TEXT OUTPUT CONSTANTS
//------NOT LOGGED/GLOBAL
const mstring GlobalConstants::WELCOME_STARTSCREEN_TEXT = "Welcome to the BigNumber game!!!\nHere, you will be forced to answer some equations with BigNumbers in them. Enjoy!\n\n";
const mstring GlobalConstants::BUTTON_START = "START GAME(start)\n\n";
const mstring GlobalConstants::BUTTON_END = "END GAME(end)\n";
const mstring GlobalConstants::GAME_END = "GAME HAS ENDED!!!\nTHANK YOU FOR PLAYING";
const mstring GlobalConstants::COMMAND_INVALID = "INVALID COMMAND! TRY AGAIN";
const mstring GlobalConstants::RETURN_TEXT = "\nRETURN TO PREVIOUS SCREEN(r)";
const mstring GlobalConstants::USERNAME_PLACEHOLDER = "{username}";
//------LOGIN/REGISTER
const mstring GlobalConstants::LOGIN_OR_REGISTER = "Choose one of the following:\nLOGIN(log)\nREGISTER(reg)";
const mstring GlobalConstants::REGISTER = "Enter your username and password ({username} | {password})\nUsername is between 6 and 100 characters!\nPassword is between 6 and 100 characters!\nWhitespaces are not allowed!\n'|' character is not allowed as part of the username or password!";
const mstring GlobalConstants::REGISTER_SUCCESS = "\nSuccessfully registered user!";
const mstring GlobalConstants::REGISTER_USERNAME_TAKEN = "This username has already been taken! Sorry brother.";
const mstring GlobalConstants::LOGIN = "Enter your username and password ({username} | {password}).";
const mstring GlobalConstants::LOGIN_USERNAME_TAKEN = "Error! This user doesn't exist! Password or username is wrong!";
//------LOGGED_MAINMENU
const mstring GlobalConstants::MAINMENU_LOGGED_STARTGAME = "\nSTART GAME(s)\n";
const mstring GlobalConstants::MAINMENU_LOGGED_CONTINUEGAME = "\nCONTINUE GAME(c)\n";
const mstring GlobalConstants::MAINMENU_LOGGED_RESTARTGAME = "\nRESTART GAME(restart)\n";
const mstring GlobalConstants::MAINMENU_LOGGED_RETURN_TEXT = "\nRETURN TO PREVIOUS SCREEN AND EXIT ACCOUNT(r)";
const mstring GlobalConstants::MAINMENU_LOGGED_DELETEOWNACCOUNT = "\nDELETE YOUR OWN ACCOUNT(delete)\n";
const mstring GlobalConstants::MAINMENU_LOGGED_DELETEOWNACCOUNT_CONFIRMATION = "\nWARNING: THIS ACTION WILL DELETE YOUR ACCOUNT FOREVER. PROCEED ANYWAY?\n";
const mstring GlobalConstants::MAINMENU_LOGGED_DELETEOWNACCOUNT_CONFIRMATION_YES = "\nDELETE ACCOUNT(delete_account)\n";
const mstring GlobalConstants::MAINMENU_LOGGED_DELETEOWNACCOUNT_CONFIRMATION_NO = "\nGO BACK(r)\n";
const mstring GlobalConstants::MAINMENU_LOGGED_DELETEOWNACCOUNT_CONFIRMATION_SUCCESS = "\nACCOUNT DELETION WAS SUCCESSFUL\n";
const mstring GlobalConstants::MAINMENU_LEVEL_TEXT = "Current Level: ";
const mstring GlobalConstants::MAINMENU_LIVES_TEXT = "Lives: ";
//------ADMIN_MAINMENU
const mstring GlobalConstants::ADMIN_GETINFO = "\nGET INFO ABOUT ACCOUNT(getinfo|{username})\n";

const mstring GlobalConstants::ADMIN_DELETEACCOUNT = "\nDELETE ACCOUNT(delete|{message}|{account name})\n";
const mstring GlobalConstants::ADMIN_DELETEACCOUNT_CONFIRMATION = "\nWARNING: THIS ACTION WILL DELETE {username}'s ACCOUNT FOREVER. PROCEED ANYWAY?\n";
const mstring GlobalConstants::ADMIN_DELETEACCOUNT_CONFIRMATION_YES = "\nDELETE ACCOUNT(delete_account)\n";
const mstring GlobalConstants::ADMIN_DELETEACCOUNT_CONFIRMATION_NO = "\nGO BACK(r)\n";
const mstring GlobalConstants::ADMIN_DELETEACCOUNT_SUCCESS = "\n{username}'s ACCOUNT DELETION WAS SUCCESSFUL\n";
const mstring GlobalConstants::ADMIN_DELETEACCOUNT_ALREADY_DELETED = "{username}'s ACCOUNT HAS ALREADY BEEN DELETED!";
const mstring GlobalConstants::ADMIN_DELETEACCOUNT_DELETEADMIN_NOTALLOWED = "THIS ACCOUNT IS AN ADMIN ACCOUNT WHICH CANNOT BE DELETED!";

const mstring GlobalConstants::ADMIN_EXCLUDEFROMLEADERBOARD = "\nEXCLUDE FROM LEADERBOARD(exclude|{account name})\n";
const mstring GlobalConstants::ADMIN_ADDHELPER = "\nADD HELPER(add|{helper name})\n";

const mstring GlobalConstants::ADMIN_RECOVER = "\nRECOVER ACCOUNT(recover|{helper name})\n";
const mstring GlobalConstants::ADMIN_RECOVER_CONFIRMATION = "\nWARNING: THIS ACTION WILL RECOVER {username}'s ACCOUNT FOREVER. PROCEED ANYWAY?\n";
const mstring GlobalConstants::ADMIN_RECOVER_BANREASON = "\nREASON FOR BAN:\n";
const mstring GlobalConstants::ADMIN_RECOVER_CONFIRMATION_YES = "\nRECOVER ACCOUNT(recover_account)\n";
const mstring GlobalConstants::ADMIN_RECOVER_CONFIRMATION_NO = "\nGO BACK(r)\n";
const mstring GlobalConstants::ADMIN_RECOVER_SUCCESS = "\n{username}'s ACCOUNT RECOVERED SUCCESSFULLY\n";
const mstring GlobalConstants::ADMIN_RECOVER_NOTBANNED = "{username}'s ACCOUNT IS NOT BANNED!";

const mstring GlobalConstants::ADMIN_LOGGEDASADMIN_TEXT = "\n!!!LOGGED AS ADMIN!!!\n";
//----------------
const mstring GlobalConstants::PLAYING_RETURN_TEXT = "\nRETURN TO PREVIOUS SCREEN AND EXIT THIS LEVEL(r)! PROGRESS WILL BE SAVED AUTOMATICALLY";
//------SCREEN TITLES
const mstring GlobalConstants::STARTSCREEN_TITLE = "START UP SCREEN";
const mstring GlobalConstants::LOGINORREGISTER_TITLE = "LOGIN OR REGISTER SCREEN";
const mstring GlobalConstants::REGISTER_TITLE = "REGISTER SCREEN";
const mstring GlobalConstants::LOGIN_TITLE = "LOGIN SCREEN";
const mstring GlobalConstants::MAINMENU_TITLE = "MAIN MENU SCREEN";
const mstring GlobalConstants::DELETE_CONFIRM_TITLE = "DELETE ACCOUNT SCREEN";
const mstring GlobalConstants::RECOVER_CONFIRM_TITLE = "RECOVER ACCOUNT SCREEN";


//---USER INFO CONSTANTS
const int GlobalConstants::USERNAME_LENGTH_MAX = 100;
const int GlobalConstants::USERNAME_LENGTH_MIN = 6;
const int GlobalConstants::PASSWORD_LENGTH_MAX = 100;
const int GlobalConstants::PASSWORD_LENGTH_MIN = 6;
const mstring GlobalConstants::USER_ROLE_NORMAL = "Normal";
const mstring GlobalConstants::USER_ROLE_ADMIN = "Admin";
const int GlobalConstants::USER_ROLES_COUNT = 2;
const mstring GlobalConstants::USER_ROLES[USER_ROLES_COUNT]
{
	GlobalConstants::USER_ROLE_NORMAL,
	GlobalConstants::USER_ROLE_ADMIN
};
const mstring GlobalConstants::USER_BANNED = "You have been banned for an unknown reason!";
const mstring GlobalConstants::USER_DOES_NOT_EXIST = "Error! This user doesn't exist!";

//---COMMAND INPUT CONSTANTS
const mstring GlobalConstants::COMMAND_MAINMENU_START = "start";
const mstring GlobalConstants::COMMAND_MAINMENU_END = "end";
const mstring GlobalConstants::COMMAND_RETURN = "r";
const mstring GlobalConstants::COMMAND_LOGIN_START = "log";
const mstring GlobalConstants::COMMAND_REGISTER_START = "reg";
const char GlobalConstants::COMMAND_DELIM = '|';
const mstring GlobalConstants::COMMAND_GAME_START = "s";
const mstring GlobalConstants::COMMAND_GAME_CONTINUE = "c";
const mstring GlobalConstants::COMMAND_GAME_RESTART = "restart";

const mstring GlobalConstants::COMMAND_ACCOUNT_DELETE = "delete";
const mstring GlobalConstants::COMMAND_ACCOUNT_DELETE_CONFIRM = "delete_account";

const mstring GlobalConstants::COMMAND_ADMIN_RECOVER = "recover";
const mstring GlobalConstants::COMMAND_ACCOUNT_RECOVER_CONFIRM = "recover_account";

const mstring GlobalConstants::COMMAND_ADMIN_GETINFO = "getinfo ";
const mstring GlobalConstants::COMMAND_ADMIN_DELETE = "delete";
const mstring GlobalConstants::COMMAND_ADMIN_ADD = "add";
const mstring GlobalConstants::COMMAND_ADMIN_EXCLUDE = "exclude";

//---FILE SYSTEM CONSTANTS
const char GlobalConstants::FILESYSTEM_ENTRY_DELIMITER = '\n';
const char GlobalConstants::FILESYSTEM_COLUMN_DELIMITER = '^';
const char GlobalConstants::FILESYSTEM_WHITESPACE = ' ';
const mstring GlobalConstants::FILESYSTEM_COLUMN_NULL = "COL_NULL";
const mstring GlobalConstants::FILESYSTEM_TRUE = "TRUE";
const mstring GlobalConstants::FILESYSTEM_FALSE = "FALSE";

//---FORBIDDEN STRING SYMBOLS
const char GlobalConstants::FORBIDDEN_SYMBOLS[5] =
{
	GlobalConstants::FILESYSTEM_ENTRY_DELIMITER,
	GlobalConstants::FILESYSTEM_COLUMN_DELIMITER,
	GlobalConstants::FILESYSTEM_WHITESPACE,
	GlobalConstants::COMMAND_DELIM,
	'\0'
};
