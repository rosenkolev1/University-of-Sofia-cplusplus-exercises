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
	static const mstring USERNAME_PLACEHOLDER;
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
	static const mstring ADMIN_DELETEACCOUNT_CONFIRMATION;
	static const mstring ADMIN_DELETEACCOUNT_CONFIRMATION_YES;
	static const mstring ADMIN_DELETEACCOUNT_CONFIRMATION_NO;
	static const mstring ADMIN_DELETEACCOUNT_SUCCESS;
	static const mstring ADMIN_DELETEACCOUNT_ALREADY_DELETED;


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
	static const mstring USER_DOES_NOT_EXIST;

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

