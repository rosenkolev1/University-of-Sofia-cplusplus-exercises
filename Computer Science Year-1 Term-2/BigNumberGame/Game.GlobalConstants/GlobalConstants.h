#pragma once

class GlobalConstants
{
public:
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
	//------LOGGED
	static constexpr const char* MAINMENU_LOGGED_STARTGAME = "\nSTART GAME(s)\n";
	static constexpr const char* MAINMENU_LOGGED_CONTINUEGAME = "\nCONTINUE GAME(c)\n";
	static constexpr const char* MAINMENU_LOGGED_RESTARTGAME = "\nRESTART GAME(restart)\n";
	static constexpr const char* MAINMENU_LOGGED_RETURN_TEXT = "\nRETURN TO PREVIOUS SCREEN AND EXIT ACCOUNT(r)";
	static constexpr const char* MAINMENU_LOGGED_DELETEOWNACCOUNT = "\nDELETE YOUR OWN ACCOUNT(delete)\n";
	static constexpr const char* MAINMENU_LOGGED_DELETEOWNACCOUNT_CONFIRMATION = "\nWARNING: THIS ACTION WILL DELETE YOUR ACCOUNT FOREVER. PROCEED ANYWAY?\n";
	static constexpr const char* MAINMENU_LOGGED_DELETEOWNACCOUNT_CONFIRMATION_YES = "\nDELETE ACCOUNT(delete_account)\n";
	static constexpr const char* MAINMENU_LOGGED_DELETEOWNACCOUNT_CONFIRMATION_NO = "\nGO BACK(r)\n";
	static constexpr const char* MAINMENU_LOGGED_DELETEOWNACCOUNT_CONFIRMATION_SUCCESS = "\nACCOUNT DELETION WAS SUCCESSFUL\n";
	static constexpr const char* PLAYING_RETURN_TEXT = "\nRETURN TO PREVIOUS SCREEN AND EXIT THIS LEVEL(r)! PROGRESS WILL BE SAVED AUTOMATICALLY";


	//---USER INFO CONSTANTS
	static const int USERNAME_LENGTH_MAX = 100;
	static const int USERNAME_LENGTH_MIN = 6;
	static const int PASSWORD_LENGTH_MAX = 100;
	static const int PASSWORD_LENGTH_MIN = 6;
	static constexpr const char* USER_ROLE_NORMAL = "Normal";
	static constexpr const char* USER_ROLE_ADMIN = "Admin";
	static constexpr const char* USER_ROLES[2]
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
};

//#endif // !GLOBALCONSTANTS_H

