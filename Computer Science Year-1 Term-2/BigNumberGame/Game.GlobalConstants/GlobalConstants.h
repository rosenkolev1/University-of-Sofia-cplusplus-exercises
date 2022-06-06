#pragma once

#include "..\Project.StringManipulation\MString.h"

class GlobalConstants
{
public:
	// INTERNAL CONSTANTS
	static const mstring BAD_ALLOC_EXCEPTION;
	static const mstring PLACEHOLDER;

	//---UI AND TEXT OUTPUT CONSTANTS
	//------NOT LOGGED/GLOBAL
	static const mstring WELCOME_STARTSCREEN_TEXT;
	static const mstring BUTTON_START;
	static const mstring BUTTON_END;
	static const mstring GAME_END;
	static const mstring COMMAND_INVALID;
	static const mstring RETURN_TEXT;
	//------LOGIN/REGISTER
	static const mstring LOGIN_OR_REGISTER;
	static const mstring REGISTER;
	static const mstring REGISTER_SUCCESS;
	static const mstring REGISTER_USERNAME_TAKEN;
	static const mstring LOGIN;
	static const mstring LOGIN_USERNAME_TAKEN;
	//------LOGGED_MAINMENU
	static const mstring MAINMENU_LOGGED_STARTGAME;
	static const mstring MAINMENU_LOGGED_CONTINUEGAME;
	static const mstring MAINMENU_LOGGED_RESTARTGAME;
	static const mstring MAINMENU_LOGGED_RETURN_TEXT;
	static const mstring MAINMENU_LOGGED_DELETEOWNACCOUNT;
	static const mstring MAINMENU_LOGGED_DELETEOWNACCOUNT_CONFIRMATION;
	static const mstring MAINMENU_LOGGED_DELETEOWNACCOUNT_CONFIRMATION_YES;
	static const mstring MAINMENU_LOGGED_DELETEOWNACCOUNT_CONFIRMATION_NO;
	static const mstring MAINMENU_LOGGED_DELETEOWNACCOUNT_CONFIRMATION_SUCCESS;
	static const mstring MAINMENU_LEVEL_TEXT;
	static const mstring MAINMENU_LIVES_TEXT;
	//------ADMIN_MAINMENU
	static const mstring ADMIN_GETINFO;
	static const mstring ADMIN_DELETEACCOUNT;
	static const mstring ADMIN_EXCLUDEFROMLEADERBOARD;
	static const mstring ADMIN_ADDHELPER;
	static const mstring ADMIN_RECOVER;
	static const mstring ADMIN_LOGGEDASADMIN_TEXT;
	//----------------
	static const mstring PLAYING_RETURN_TEXT;
	//------SCREEN TITLES
	static const mstring STARTSCREEN_TITLE;
	static const mstring LOGINORREGISTER_TITLE;
	static const mstring REGISTER_TITLE;
	static const mstring LOGIN_TITLE;
	static const mstring MAINMENU_TITLE;
	static const mstring DELETE_CONFIRM_TITLE;


	//---USER INFO CONSTANTS
	static const int USERNAME_LENGTH_MAX;
	static const int USERNAME_LENGTH_MIN;
	static const int PASSWORD_LENGTH_MAX;
	static const int PASSWORD_LENGTH_MIN;
	static const mstring USER_ROLE_NORMAL;
	static const mstring USER_ROLE_ADMIN;
	static const int USER_ROLES_COUNT;
	static const mstring USER_ROLES[];
	static const mstring USER_BANNED;

	//---COMMAND INPUT CONSTANTS
	static const mstring COMMAND_MAINMENU_START;
	static const mstring COMMAND_MAINMENU_END;
	static const mstring COMMAND_RETURN;
	static const mstring COMMAND_LOGIN_START;
	static const mstring COMMAND_REGISTER_START;
	static const char COMMAND_DELIM;
	static const mstring COMMAND_GAME_START;
	static const mstring COMMAND_GAME_CONTINUE;
	static const mstring COMMAND_GAME_RESTART;
	static const mstring COMMAND_ACCOUNT_DELETE;
	static const mstring COMMAND_ACCOUNT_DELETE_CONFIRM;
	static const mstring COMMAND_ADMIN_GETINFO;
	static const mstring COMMAND_ADMIN_DELETE;
	static const mstring COMMAND_ADMIN_ADD;
	static const mstring COMMAND_ADMIN_EXCLUDE;
	static const mstring COMMAND_ADMIN_RECOVER;

	//---FILE SYSTEM CONSTANTS
	static const char FILESYSTEM_ENTRY_DELIMITER;
	static const char FILESYSTEM_COLUMN_DELIMITER;
	static const char FILESYSTEM_WHITESPACE;
	static const mstring FILESYSTEM_COLUMN_NULL;
	static const mstring FILESYSTEM_TRUE;
	static const mstring FILESYSTEM_FALSE;

	//---FORBIDDEN STRING SYMBOLS
	static const char FORBIDDEN_SYMBOLS[];
};

/*
// INTERNAL CONSTANTS
	static constexpr const char* BAD_ALLOC_EXCEPTION = "Bad allocation of memory";
	static constexpr const char* PLACEHOLDER = "LOREM IPSUM TEXT";

	//---UI AND TEXT OUTPUT CONSTANTS
	//------NOT LOGGED/GLOBAL
	static constexpr const char* WELCOME_STARTSCREEN_TEXT = "Welcome to the BigNumber game!!!\nHere, you will be forced to answer some equations with BigNumbers in them. Enjoy!\n\n";
	static constexpr const char* BUTTON_START = "START GAME(start)\n\n";
	static constexpr const char* BUTTON_END = "END GAME(end)\n";
	static constexpr const char* GAME_END = "GAME HAS ENDED!!!\nTHANK YOU FOR PLAYING";
	static constexpr const char* COMMAND_INVALID = "INVALID COMMAND! TRY AGAIN";
	static constexpr const char* RETURN_TEXT = "\nRETURN TO PREVIOUS SCREEN(r)";
	//------LOGIN/REGISTER
	static constexpr const char* LOGIN_OR_REGISTER = "Choose one of the following:\nLOGIN(log)\nREGISTER(reg)";
	static constexpr const char* REGISTER = "Enter your username and password ({username} | {password})\nUsername is between 6 and 100 characters!\nPassword is between 6 and 100 characters!\nWhitespaces are not allowed!\n'|' character is not allowed as part of the username or password!";
	static constexpr const char* REGISTER_SUCCESS = "\nSuccessfully registered user!";
	static constexpr const char* REGISTER_USERNAME_TAKEN = "This username has already been taken! Sorry brother.";
	static constexpr const char* LOGIN = "Enter your username and password ({username} | {password}).";
	static constexpr const char* LOGIN_USERNAME_TAKEN = "Error! This user doesn't exist! Password or username is wrong!";
	//------LOGGED_MAINMENU
	static constexpr const char* MAINMENU_LOGGED_STARTGAME = "\nSTART GAME(s)\n";
	static constexpr const char* MAINMENU_LOGGED_CONTINUEGAME = "\nCONTINUE GAME(c)\n";
	static constexpr const char* MAINMENU_LOGGED_RESTARTGAME = "\nRESTART GAME(restart)\n";
	static constexpr const char* MAINMENU_LOGGED_RETURN_TEXT = "\nRETURN TO PREVIOUS SCREEN AND EXIT ACCOUNT(r)";
	static constexpr const char* MAINMENU_LOGGED_DELETEOWNACCOUNT = "\nDELETE YOUR OWN ACCOUNT(delete)\n";
	static constexpr const char* MAINMENU_LOGGED_DELETEOWNACCOUNT_CONFIRMATION = "\nWARNING: THIS ACTION WILL DELETE YOUR ACCOUNT FOREVER. PROCEED ANYWAY?\n";
	static constexpr const char* MAINMENU_LOGGED_DELETEOWNACCOUNT_CONFIRMATION_YES = "\nDELETE ACCOUNT(delete_account)\n";
	static constexpr const char* MAINMENU_LOGGED_DELETEOWNACCOUNT_CONFIRMATION_NO = "\nGO BACK(r)\n";
	static constexpr const char* MAINMENU_LOGGED_DELETEOWNACCOUNT_CONFIRMATION_SUCCESS = "\nACCOUNT DELETION WAS SUCCESSFUL\n";
	static constexpr const char* MAINMENU_LEVEL_TEXT = "Current Level: ";
	static constexpr const char* MAINMENU_LIVES_TEXT = "Lives: ";
	//------ADMIN_MAINMENU
	static constexpr const char* ADMIN_GETINFO = "\nGET INFO ABOUT ACCOUNT(getinfo {account name})\n";
	static constexpr const char* ADMIN_DELETEACCOUNT = "\nDELETE ACCOUNT(delete {account name})\n";
	static constexpr const char* ADMIN_EXCLUDEFROMLEADERBOARD = "\nEXCLUDE FROM LEADERBOARD(exclude {account name})\n";
	static constexpr const char* ADMIN_ADDHELPER = "\nADD HELPER(add {helper name})\n";
	static constexpr const char* ADMIN_RECOVER = "\nRECOVER ACCOUNT(recover {helper name})\n";
	static constexpr const char* ADMIN_LOGGEDASADMIN_TEXT = "\n!!!LOGGED AS ADMIN!!!\n";
	//----------------
	static constexpr const char* PLAYING_RETURN_TEXT = "\nRETURN TO PREVIOUS SCREEN AND EXIT THIS LEVEL(r)! PROGRESS WILL BE SAVED AUTOMATICALLY";
	//------SCREEN TITLES
	static constexpr const char* STARTSCREEN_TITLE = "START UP SCREEN";
	static constexpr const char* LOGINORREGISTER_TITLE = "LOGIN OR REGISTER SCREEN";
	static constexpr const char* REGISTER_TITLE = "REGISTER SCREEN";
	static constexpr const char* LOGIN_TITLE = "LOGIN SCREEN";
	static constexpr const char* MAINMENU_TITLE = "MAIN MENU SCREEN";
	static constexpr const char* DELETE_CONFIRM_TITLE = "DELETE ACCOUNT SCREEN";


	//---USER INFO CONSTANTS
	static const int USERNAME_LENGTH_MAX = 100;
	static const int USERNAME_LENGTH_MIN = 6;
	static const int PASSWORD_LENGTH_MAX = 100;
	static const int PASSWORD_LENGTH_MIN = 6;
	static constexpr const char* USER_ROLE_NORMAL = "Normal";
	static constexpr const char* USER_ROLE_ADMIN = "Admin";
	static constexpr const int USER_ROLES_COUNT = 2;
	static constexpr const char* USER_ROLES[USER_ROLES_COUNT]
	{
		GlobalConstants::USER_ROLE_NORMAL,
		GlobalConstants::USER_ROLE_ADMIN
	};
	static constexpr const char* USER_BANNED = "You have been banned for an unknown reason!";

	//---COMMAND INPUT CONSTANTS
	static constexpr const char* COMMAND_MAINMENU_START = "start";
	static constexpr const char* COMMAND_MAINMENU_END = "end";
	static constexpr const char* COMMAND_RETURN = "r";
	static constexpr const char* COMMAND_LOGIN_START = "log";
	static constexpr const char* COMMAND_REGISTER_START = "reg";
	static constexpr const char COMMAND_DELIM = '|';
	static constexpr const char* COMMAND_GAME_START = "s";
	static constexpr const char* COMMAND_GAME_CONTINUE = "c";
	static constexpr const char* COMMAND_GAME_RESTART = "restart";
	static constexpr const char* COMMAND_ACCOUNT_DELETE = "delete";
	static constexpr const char* COMMAND_ACCOUNT_DELETE_CONFIRM = "delete_account";
	static constexpr const char* COMMAND_ADMIN_GETINFO = "getinfo ";
	static constexpr const char* COMMAND_ADMIN_DELETE = "delete ";
	static constexpr const char* COMMAND_ADMIN_ADD = "add ";
	static constexpr const char* COMMAND_ADMIN_EXCLUDE = "exclude ";
	static constexpr const char* COMMAND_ADMIN_RECOVER = "recover ";

	//---FILE SYSTEM CONSTANTS
	static constexpr const char FILESYSTEM_ENTRY_DELIMITER = '\n';
	static constexpr const char FILESYSTEM_COLUMN_DELIMITER = '^';
	static constexpr const char FILESYSTEM_WHITESPACE = ' ';
	static constexpr const char* FILESYSTEM_COLUMN_NULL = "COL_NULL";
	static constexpr const char* FILESYSTEM_TRUE = "TRUE";
	static constexpr const char* FILESYSTEM_FALSE = "FALSE";

	//---FORBIDDEN STRING SYMBOLS
	static constexpr char FORDBIDDEN_SYMBOLS[10] =
	{
		GlobalConstants::FILESYSTEM_ENTRY_DELIMITER,
		GlobalConstants::FILESYSTEM_COLUMN_DELIMITER,
		GlobalConstants::FILESYSTEM_WHITESPACE,
		GlobalConstants::COMMAND_DELIM,
		'\0'
	};
*/

