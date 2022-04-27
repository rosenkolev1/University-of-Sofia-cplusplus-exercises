#pragma once

class GlobalConstants
{
public:
	// INTERNAL CONSTANTS
	static constexpr const char* BAD_ALLOC_EXCEPTION = "Bad allocation of memory";

	//---UI AND TEXT OUTPUT CONSTANTS
	static constexpr const char* WELCOME_STARTSCREEN_TEXT = "Welcome to the BigNumber game!!!\nHere, you will be forced to answer some equations with BigNumbers in them. Enjoy!\n\n";
	static constexpr const char* BUTTON_START = "START GAME(start)\n\n";
	static constexpr const char* BUTTON_END = "END GAME(end)\n";
	static constexpr const char* GAME_END = "GAME HAS ENDED!!!\nTHANK YOU FOR PLAYING";
	static constexpr const char* COMMAND_INVALID = "INVALID COMMAND! TRY AGAIN";
	static constexpr const char* RETURN_TEXT = "\nRETURN TO PREVIOUS SCREEN(r)";
	static constexpr const char* LOGIN_OR_REGISTER = "Choose one of the following:\nLOGIN(log)\nREGISTER(reg)";
	static constexpr const char* REGISTER = "Enter your username and password ({username} | {password})\nUsername is between 6 and 100 characters!\nPassword is between 6 and 100 characters!\nWhitespaces are not allowed!\n'|' character is not allowed as part of the username or password!";
	static constexpr const char* REGISTER_SUCCESS = "\nSuccessfully registered user!";
	static constexpr const char* REGISTER_USERNAME_TAKEN = "This username has already been taken! Sorry brother.";
	static constexpr const char* LOGIN = "Enter your username and password ({username} | {password}).";
	static constexpr const char* LOGIN_USERNAME_TAKEN = "Error! This user doesn't exist! Password or username is wrong!";

	//---USER INFO CONSTANTS
	static const int USERNAME_LENGTH_MAX = 100;
	static const int USERNAME_LENGTH_MIN = 6;
	static const int PASSWORD_LENGTH_MAX = 100;
	static const int PASSWORD_LENGTH_MIN = 6;

	//---COMMAND INPUT CONSTANTS
	static constexpr const char* COMMAND_MAINMENU_START = "start";
	static constexpr const char* COMMAND_MAINMENU_END = "end";
	static constexpr const char* COMMAND_RETURN = "r";
	static constexpr const char* COMMAND_LOGIN_START = "log";
	static constexpr const char* COMMAND_REGISTER_START = "reg";
	static constexpr const char COMMAND_DELIM = '|';

	//---FILE SYSTEM CONSTANTS
	static constexpr const char FILESYSTEM_ENTRY_DELIMITER = '~';
	static constexpr const char FILESYSTEM_COLUMN_DELIMITER = '^';
	static constexpr const char FILESYSTEM_WHITESPACE = ' ';
	static constexpr const char* FILESYSTEM_COLUMN_NULL = "COL_NULL";
	static constexpr const int FILESYSTEM_COLUMN_COUNT = 4;

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

